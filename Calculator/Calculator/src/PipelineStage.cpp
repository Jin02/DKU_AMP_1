#include "PipelineStage.h"
#include "System.h"

#include "JFormatInstruction.h"
#include "Move.h"
#include "ShiftLeftLogical.h"
#include "ShiftRightLogical.h"
#include "SetLessThan.h"
#include "JumpRegister.h"
#include "Or.h"
#include "And.h"
#include "Subtract.h"
#include "Add.h"
#include "Multiply.h"
#include "Divide.h"

#include "Store.h"
#include "Load.h"
#include "BranchOnEqual.h"
#include "BranchOnNotEqual.h"
#include "SetLessThanImmediate.h"
#include "OrImmediate.h"
#include "AndImmediate.h"
#include "AddImmediate.h"

#include "DumpLogManager.h"

#include <sstream>

PipelineStage::PipelineStage() : _instruction(nullptr), _instructionValue(0), _prev1StepPip(nullptr), _prev2StepPip(nullptr), _isCancel(false)
{
    _state = State::Fetch;
}

PipelineStage::~PipelineStage()
{
    
}

void PipelineStage::NextState()
{
    _state = (State)((uint)_state + 1);
    if(_state > State::Stall)
        _state = State::Stall;
}

void PipelineStage::Cancel()
{
    _isCancel = true;
	_instructionValue = 0;
	_pc = 0;
}

void PipelineStage::Clear()
{
    _state = State::Fetch;
    _pc = 0;
    SAFE_DELETE(_instruction);
    _instructionValue = 0;
    _prev1StepPip = _prev2StepPip = nullptr;
}

uint PipelineStage::Fetch()
{
    _pc = System::GetInstance()->GetProgramCounter();
	if(_pc == 0xffffffff)
	{
		return 0;
	}

    ASSERT_COND_MSG( (_pc % 4) == 0, "Error, pc must has word multiplier" );
	
	System::GetInstance()->SetProgramCounter(_pc + 4);

    return System::GetInstance()->GetDataFromMemory(_pc);
}


void PipelineStage::Decode(uint instruction)
{
	if(instruction == 0x00) //nop
	{
		_isCancel = true;
		return;
	}

    char buff[256] = {0, };
    
    unsigned int opCode     = (instruction & 0xFC000000) >> 26;
    unsigned int funct		= (instruction & 0x0000003F);
    unsigned int immediate  = (instruction & 0x0000ffff);
    
    uint rd		= (instruction & 0x0000f800) >> 11;
    uint rs		= (instruction & 0x03e00000) >> 21;
    uint rt		= (instruction & 0x001f0000) >> 16;
    uint shamt  = (instruction & 0x000007c0) >> 6;
    
    auto FillBit = [&](unsigned int from, unsigned int to, unsigned int pos)
    {
        bool setBit = (1 << pos) & immediate;
        unsigned int ret = 0x00000000;
        for(unsigned int i = from; i <= to; ++i)
            ret |= (uint)setBit << i;
        
        return ret;
    };
    
    if(opCode == 0) // R
    {
        sprintf(buff, "R Type\t\t| rd 0x%x / rs 0x%x / rt 0x%x / shamt 0x%x / funct 0x%x", rd, rs, rt, shamt, funct);
        GlobalDumpLogManager->AddLog(buff, true);
        
        if(funct == (uint)Funct::Add)
            _instruction = new Add(rs, rt, rd);
        else if(funct == (uint)Funct::AddUnsigned)
            _instruction = new AddUnsigned(rs, rt, rd);
        else if(funct == (uint)Funct::And)
            _instruction = new And(rs, rt, rd);
        else if(funct == (uint)Funct::JumpRegister)
            _instruction = new JumpRegister(rs, rt, rd);
        else if(funct == (uint)Funct::Nor)
            _instruction = new Nor(rs, rt, rd);
        else if(funct == (uint)Funct::Or)
            _instruction = new Or(rs, rt, rd);
        else if(funct == (uint)Funct::SetLessThan)
            _instruction = new SetLessThan(rs, rt, rd);
        else if(funct == (uint)Funct::SetLessThanUnsigned)
            _instruction = new SetLessThanUnsigned(rs, rt, rd);
        else if(funct == (uint)Funct::ShiftLeftLogical)
            _instruction = new ShiftLeftLogical(rs, rt, rd, shamt);
        else if(funct == (uint)Funct::ShiftRightLogical)
            _instruction = new ShiftRightLogical(rs,rt, rd, shamt);
        else if(funct == (uint)Funct::Subtract)
            _instruction = new Subtract(rs, rt, rd);
        else if(funct == (uint)Funct::SubtractUnsigned)
            _instruction = new SubtractUnsigned(rs, rt, rd);
        else if(funct == (uint)Funct::Multiply)
            _instruction = new Multiply(rs,rt, rd);
        else if(funct == (uint)Funct::MultiplyUnsigned)
            _instruction = new MultiplyUnsigned(rs, rt, rd);
        else if(funct == (uint)Funct::Divide)
            _instruction = new Divide(rs, rt, rd);
        else if(funct == (uint)Funct::DivideUnsigned)
            _instruction = new DivideUnsigned(rs, rt, rd);
        
        
        else ASSERT_MSG("can not support r format this instruction");
    }
    else if(opCode == (uint)Opcode::Jump || opCode == (uint)Opcode::JumpAndLink) // J
    {
        unsigned int address = instruction & 0x03FFFFFF;
   
        uint pc = _pc + 4;
        uint jumpAddr = (pc & 0xf0000000) | (address << 2);
		std::string backCode = " " + std::to_string(jumpAddr);

        sprintf(buff, "J Type\t\t| opcode 0x%x / address 0x%x", opCode, jumpAddr);
        GlobalDumpLogManager->AddLog(buff, true);
        
        if(opCode == (uint)Opcode::Jump)
            _instruction = new Jump(jumpAddr);
        else if(opCode == (uint)Opcode::JumpAndLink)
        {
            _instruction = new JumpAndLink(jumpAddr);
            ((JumpAndLink*)_instruction)->SetPC(_pc);
        }
        else ASSERT_MSG("cant support j foramt this instruction");
		backCode.insert(0, _instruction->GetName());
    }
    else // I
    {
        uint mask           = FillBit(15, 31, 15);
        uint signExtImm     = mask | immediate;
        uint zeroExtImm     = immediate;
        
        mask				= FillBit(17, 31, 15);
        uint branchAddr     = FillBit(17, 31, 15) | (immediate << 2);
        
        sprintf(buff, "I Type\t\t| opcode 0x%x / signExtImm 0x%x / zeroExtImm 0x%x / branchAddr 0x%x", opCode, signExtImm, zeroExtImm, branchAddr);
        GlobalDumpLogManager->AddLog(buff, true);
        
		std::string backCode = " $" + std::to_string(rt) + ", $" + std::to_string(rs) + ", " + std::to_string((short)immediate);

        if(opCode == (uint)Opcode::AddImmediate)
            _instruction = new AddImmediate(rs, rt, signExtImm);
        else if(opCode == (uint)Opcode::AddImmediateUnsigned)
            _instruction = new AddImmediateUnsigned(rs, rt, signExtImm);
        else if(opCode == (uint)Opcode::AndImmediate)
            _instruction = new AndImmediate(rs, rt, zeroExtImm);
        else if(opCode == (uint)Opcode::BranchOnEqual)
        {
			_instruction = new BranchOnEqual(rs, rt, branchAddr);
			BranchOnEqual* branch = dynamic_cast<BranchOnEqual*>(_instruction);//->SetPC(_pc);
			branch->SetPC(_pc);
        }
        else if(opCode == (uint)Opcode::BranchOnNotEqual)
        {
			_instruction = new BranchOnNotEqual(rs, rt, branchAddr);
			BranchOnNotEqual* branch = dynamic_cast<BranchOnNotEqual*>(_instruction);//->SetPC(_pc);
			branch->SetPC(_pc);
        }
        else if(opCode == (uint)Opcode::LoadByteUnsigned)
            _instruction = new LoadByteUnsigned(rs, rt, signExtImm);
        else if(opCode == (uint)Opcode::LoadHalfwordUnsigned)
            _instruction = new LoadHalfwordUnsigned(rs, rt, signExtImm);
        else if(opCode == (uint)Opcode::LoadLinked)
            _instruction = new LoadLinked(rs, rt, signExtImm);
        else if(opCode == (uint)Opcode::LoadUpperImmediate)
            _instruction = new LoadUpperImmediate(rs, rt, immediate);
        else if(opCode == (uint)Opcode::LoadWord)
            _instruction = new LoadWord(rs, rt, signExtImm);
        else if(opCode == (uint)Opcode::OrImmediate)
            _instruction = new OrImmediate(rs, rt, zeroExtImm);
        else if(opCode == (uint)Opcode::SetLessThanImmediate)
            _instruction = new SetLessThanImmediate(rs, rt, zeroExtImm);
        else if(opCode == (uint)Opcode::SetLessThanImmediateUnsigned)
            _instruction = new SetLessThanImmediateUnsigned(rs, rt, zeroExtImm);
        else if(opCode == (uint)Opcode::StoreByte)
            _instruction = new StoreByte(rs, rt, zeroExtImm);
        else if(opCode == (uint)Opcode::StoreConditional)
            _instruction = new StoreConditional(rs, rt, zeroExtImm);
        else if(opCode == (uint)Opcode::StoreHalfword)
            _instruction = new StoreHalfword(rs, rt, zeroExtImm);
        else if(opCode == (uint)Opcode::StoreWord)
            _instruction = new StoreWord(rs, rt, zeroExtImm);
        else if((opCode == (uint)Opcode::Multiply32BitRes) && (funct == (uint)Funct::Multiply32BitRes))
        {
            GlobalDumpLogManager->AddLog(" / funct 0x%x", funct);
            _instruction = new Multiply32BitRes(rs, rt, rd);
        }
        
        else ASSERT_MSG("cant support i foramt this inst");
		backCode.insert(0, _instruction->GetName());
    }
}

void PipelineStage::Execution(const PipelineStage* prev2step, const PipelineStage* prev1step)
{
	Instruction* prev2StepInst = prev2step ? prev2step->GetInstruction() : nullptr;	
	Instruction* prev1StepInst = prev1step ? prev1step->GetInstruction() : nullptr;

	if(_instruction)
		_instruction->Execution(prev2StepInst, prev1StepInst);
}

void PipelineStage::Memory(const PipelineStage* prev2step, const PipelineStage* prev1step)
{
	Instruction* prev2StepInst = prev2step ? prev2step->GetInstruction() : nullptr;	
	Instruction* prev1StepInst = prev1step ? prev1step->GetInstruction() : nullptr;

	if(_instruction)
		_instruction->Memory(prev2StepInst, prev1StepInst);
}

void PipelineStage::WriteBack()
{
	if(_instruction)
		_instruction->WriteBack();
}

void PipelineStage::RunStage()
{
    if(_isCancel)
        return;
    
    if(_state == State::Fetch)
	{
        _instructionValue = Fetch();
		GlobalDumpLogManager->AddLog("Fetch State\t| instruction Value is 0x" + GlobalDumpLogManager->UIntToHexString(_instructionValue), true);
	}
    else if(_state == State::Decode)
	{
		GlobalDumpLogManager->AddLog("Decode State\t| instruction Value is 0x" + GlobalDumpLogManager->UIntToHexString(_instructionValue), true);
		Decode(_instructionValue);
	}
    else if(_state == State::Execution)
	{
		GlobalDumpLogManager->AddLog("Execution State\t| instruction is " + _instruction->GetName(), true);
		Execution(_prev2StepPip, _prev1StepPip);
		GlobalDumpLogManager->AddLog("\n");
	}
    else if(_state == State::Memory)
	{		
		GlobalDumpLogManager->AddLog("Memory State\t| instruction is " + _instruction->GetName(), true);
		Memory(_prev2StepPip, _prev1StepPip);
		GlobalDumpLogManager->AddLog("\n");
	}
    else if(_state == State::WriteBack)
	{
		GlobalDumpLogManager->AddLog("WriteBack State\t| instruction is " + _instruction->GetName(), true);
		WriteBack();
		GlobalDumpLogManager->AddLog("\n");
	}
}