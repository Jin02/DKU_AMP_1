#include "System.h"

#include <memory.h>
#include <fstream>
#include <string>

#include "DumpLogManager.h"
#include "BranchBase.h"

System::System()
    : _programCounter(0), _hi(0), _lo(0), _cycle(0), _cache(nullptr)
{
	std::fill(_processorMemory.begin(), _processorMemory.end(), 0);
	std::fill(_registers.begin(), _registers.end(), 0);

	SetStackPointer(MAX_PROCESSOR_MEMORY);
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
	for(auto iter : _insts)
		SAFE_DELETE(iter.pip);

    SAFE_DELETE(_cache);
	_insts.clear();
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
    
    return;
}

void System::InitializeCache(uint cacheSize, uint cacheBlockSize, uint nWay, uint hitTime, uint missPenalty)
{
    SAFE_DELETE(_cache);
    
    GlobalDumpLogManager->AddLog("Cache Size\t\t| " + std::to_string(cacheSize) + "\nCache Block Size\t| " + std::to_string(cacheBlockSize) + "\nCache Ways\t\t| " + std::to_string(nWay) + "\n");

    _cache = new NSetCache(cacheSize, cacheBlockSize, nWay, _processorMemory.data(), hitTime, missPenalty);
}

void System::Run()
{
	while((_programCounter != 0xffffffff) || (_insts.empty() == false))
    {
		GlobalDumpLogManager->AddLog("-----------------------------------------------", true);
		{
			bool end = (_programCounter == 0xffffffff);
			GlobalDumpLogManager->AddLog("Cycle Num\t\t| " + std::to_string(_cycle++), true);

			if(end == false)
			{
				InstructionControllerInfo info;
				{
					info.cycle = _cycle;
					info.pip = new InstructionController;
					info.pip->SetProgramCounter(_programCounter); //just.. using visualization. this line code is nothing.
					info.isEnd = end;
					if(end)
						info.pip->Cancel();
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
		GlobalDumpLogManager->AddLog("-----------------------------------------------", true);
    }

	char buff[128] = {0,};
	sprintf(buff, "Final Return Value is 0x%x(v0)", _registers[2]);
	GlobalDumpLogManager->AddLog(buff, true);
    printf("%s\n", buff);
    
    _cache->HitAndAMATLog();
}

void System::RunCycle(const InstructionControllerInfo& stage)
{
	InstructionController* pip = stage.pip;
	InstructionController::State	state	= pip->GetState();
	
	bool isCancelPip = pip->GetIsCancel();
	if(isCancelPip == false)
	{
		if(state == InstructionController::State::Fetch)
		{
			uint key = _programCounter;
			_hashMap.insert( std::make_pair(key, pip) );
		}
		else if(state == InstructionController::State::Execution)
		{
			auto FindObjectFromHashMap = [&](uint key)
			{
				auto findIter = _hashMap.find(key);
				InstructionController* ret = nullptr;

				if(findIter != _hashMap.end()) //found!
					ret = findIter->second;

				return ret;
			};

			uint pc = pip->GetProgramCounter();
			InstructionController* prev1Step = FindObjectFromHashMap( pc - 4 );
			InstructionController* prev2Step = FindObjectFromHashMap( pc - 8 );

			pip->SetPrev1StepPip(prev1Step);
			pip->SetPrev2StepPip(prev2Step);
		}
	}

	pip->RunStage();

	if(state == InstructionController::State::Execution && (isCancelPip == false))
	{
		Instruction::Type instType = pip->GetInstruction()->GetType();
		if(instType == Instruction::Type::Jump)
		{
			CancelInstructionController(stage.cycle);
		}
		else if(instType == Instruction::Type::Branch)
		{
			BranchBase* branchInst = dynamic_cast<BranchBase*>(pip->GetInstruction());
			if(branchInst->GetIsBranchSuccess())
				CancelInstructionController(stage.cycle);
        }			
	}

	pip->NextState();

	if(pip->GetState() == InstructionController::State::Stall)
		_removePipelineKeys.push(pip->GetProgramCounter());
}

unsigned int System::GetDataFromMemory(uint address)
{
    ASSERT_COND_MSG((address % 4) == 0, "strange address");
    return _cache ? _cache->FetchData(address) : _processorMemory[address/4];
}

void System::SetDataToMemory(uint address, unsigned int data)
{
    ASSERT_COND_MSG((address % 4) == 0, "strange address");

    if(_cache)
    {
        _cache->InputData(address, data);
    }
    else
    {
        _processorMemory[address/4] = data;
    }
}

void System::CancelInstructionController(uint currentCycle)
{
	for(auto info : _insts)
	{
		for(int i = 1; i <= MAX_BRANCH_PREDICTION_CANCEL; ++i)
		{
			if( (info.cycle - i) == currentCycle )
			{
				info.pip->Cancel();
			}
		}
	}
}

bool System::CheckAllEndInst()
{
	if(_insts.size() == 0)
		return false;

	for(auto iter : _insts)
	{
		if(iter.isEnd == false)
			return false;
	}

	return true;
}

void System::CreateCache(uint cacheSize, uint cacheBlockSize, uint nWay, uint hitTime, uint missPenalty)
{
    _cache = new NSetCache(cacheSize, cacheBlockSize, nWay, _processorMemory.data(), hitTime, missPenalty);
}
