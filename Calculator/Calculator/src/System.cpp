#include "System.h"

#include <memory.h>
#include <fstream>
#include <string>

#include "DumpLogManager.h"
#include "BranchBase.h"

System::System() : _programCounter(0), _hi(0), _lo(0), _cycle(0), _addStallCount(0)
{
	std::fill(_processorMemory.begin(), _processorMemory.end(), 0);
	std::fill(_registers.begin(), _registers.end(), 0);

	SetStackPointer(0x8000);
	SetReturnAddress(0xffffffff);

	GlobalDumpLogManager->AddLog("all clear register", true);
	GlobalDumpLogManager->AddLog("all clear memory", true);

	char buff[64] = {0, };
	sprintf(buff, "sp : 0x%x", GetStackPointer());
	GlobalDumpLogManager->AddLog(buff, true);

	sprintf(buff, "ra : 0x%x", GetReturnAddress());
	GlobalDumpLogManager->AddLog(buff, true);
}

System::~System()
{
}

void System::Load(const std::string& path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
    ASSERT_COND_MSG(file.is_open() && file.good(), "Error, strange file");

	long long length = file.tellg();
	file.seekg(0, file.beg);

	unsigned char* buffer = new unsigned char[length];
	{
		file.read((char*)buffer, length);
		std::copy((unsigned int*)buffer, (unsigned int*)&buffer[length], _processorMemory.begin());
	}
	delete buffer;

    file.close();

	auto IsLittleEndian = []()
	{
		union{
			int a;
			char b;
		}Test;

		Test.a = 1;
		return Test.b;
	};
	auto LittleEndianToBigEndian = [](unsigned int x)
	{
		return x = ( x >> 24 ) | (( x << 8) & 0x00ff0000 )| ((x >> 8) & 0x0000ff00) | ( x << 24); 
	};

	if(IsLittleEndian())
	{
		GlobalDumpManagerAddLogNewLine("This system is based little endian. so, I will convert this data to big endian format");

		for(int i=0; i<length / 4; ++i)
			_processorMemory[i] = LittleEndianToBigEndian(_processorMemory[i]);
	}
}

void System::Run()
{
	while(_programCounter != 0xffffffff || (_insts.empty() == false) )
    {
		bool end = (_programCounter == 0xffffffff);
        GlobalDumpLogManager->AddLog("Cycle Num\t| " + std::to_string(_cycle++), true);

		if(_insts.size() < 5 && (end == false))
		{
			PipelineStageInfo info;
			info.cycle = _cycle;
			info.pip = new PipelineStage;

			if(_addStallCount)
			{
				info.pip->Cancel();
				_addStallCount--;
			}

			_insts.push_front(info); 
		}

		for(auto iter = _insts.rbegin(); iter != _insts.rend(); ++iter)
			RunCycle((*iter));

		if((_insts.size() == 5) || end)
			_insts.pop_back();

        if( _removePipelineKeys.size() > 2 )
        {
            uint key = _removePipelineKeys.front();
            auto findIter = _hashMap.find(key);
            if(findIter != _hashMap.end())
            {
                SAFE_DELETE(findIter->second);
                _hashMap.erase(findIter);
            }
            
            _removePipelineKeys.pop();
        }
    }

	char buff[128] = {0,};
	sprintf(buff, "Final Return Value is 0x%x(v0)", _registers[2]);
	GlobalDumpLogManager->AddLog(buff, true);
}

void System::RunCycle(const PipelineStageInfo& stage)
{
	PipelineStage* pip = stage.pip;
	PipelineStage::State	state	= pip->GetState();
	
	bool isCancelPip = pip->GetIsCancel();
	if(isCancelPip == false)
	{
		if(state == PipelineStage::State::Fetch)
		{
			uint key = _programCounter;
			_hashMap.insert( std::make_pair(key, pip) );
		}
		else if(state == PipelineStage::State::Execution)
		{
			auto FindObjectFromHashMap = [&](uint key)
			{
				auto findIter = _hashMap.find(key);
				PipelineStage* ret = nullptr;

				if(findIter != _hashMap.end()) //found!
					ret = findIter->second;

				return ret;
			};

			uint pc = pip->GetProgramCounter();
			PipelineStage* prev1Step = FindObjectFromHashMap( pc - 4 );
			PipelineStage* prev2Step = FindObjectFromHashMap( pc - 8 );

			pip->SetPrev1StepPip(prev1Step);
			pip->SetPrev2StepPip(prev2Step);
		}
	}

	if( (pip->GetProgramCounter() == 0x3c) || 
		(pip->GetProgramCounter() == 0x8c) ||
		(pip->GetProgramCounter() == 28))
	{
		int a = 5;
		a=3;
	}
	pip->RunStage();

    bool isJumpSuccess = false;
	if(state == PipelineStage::State::Execution && (isCancelPip == false))
	{
		Instruction::Type instType = pip->GetInstruction()->GetType();
		if(instType == Instruction::Type::Jump)
		{
			_addStallCount = 2;
		}
		else if(instType == Instruction::Type::Branch)
		{
			BranchBase* branchInst = dynamic_cast<BranchBase*>(pip->GetInstruction());
			isJumpSuccess = branchInst->GetIsBranchSuccess();
        }

		if(isJumpSuccess)
			CancelPipelineStage(stage.cycle);
	}

	pip->NextState();

	if(pip->GetState() == PipelineStage::State::Stall)
		_removePipelineKeys.push(pip->GetProgramCounter());
}

unsigned int System::GetDataFromMemory(int address)
{
    ASSERT_COND_MSG((address % 4) == 0, "strange address");
    return _processorMemory[address/4];
}

void System::SetDataToMemory(int address, unsigned int data)
{
    ASSERT_COND_MSG((address % 4) == 0, "strange address");
    _processorMemory[address/4] = data;
}

void System::CancelPipelineStage(uint currentCycle)
{
	for(auto info : _insts)
	{
		for(int i = 0; i < MAX_BRANCH_PREDICTION_CANCEL; ++i)
		{
			if( (info.cycle - i) == currentCycle )
				info.pip->Cancel();
		}
	}
}