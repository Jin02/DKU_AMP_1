#include "System.h"

#include <memory.h>
#include <fstream>
#include <string>

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

System::System() : _programCounter(0), _hi(0), _lo(0), _cycle(0)
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
	while(_programCounter != 0xffffffff)
    {
        GlobalDumpLogManager->AddLog("Cycle Num\t| " + std::to_string(_cycle++), true);
		RunCycle();
    }

	char buff[128] = {0,};
	sprintf(buff, "Final Return Value is 0x%x(v0)", _registers[2]);
	GlobalDumpLogManager->AddLog(buff, true); 
}

void System::RunCycle()
{
	uint inst		= Fetch();
	auto instObj	= Decode(inst);

}

unsigned int System::Fetch()
{
    ASSERT_COND_MSG( (_programCounter % 4) == 0, "Error, pc must has word multiplier" );
    return _processorMemory[_programCounter / 4];
}

Instruction* System::Decode(unsigned int instruction)
{
//    char buff[256] = {0, };
//
//    unsigned int opCode     = (instruction & 0xFC000000) >> 26;
//	unsigned int funct		= (instruction & 0x0000003F);
//	unsigned int immediate  = (instruction & 0x0000ffff);
//
//	uint rd		= (instruction & 0x0000f800) >> 11;
//	uint rs		= (instruction & 0x03e00000) >> 21;
//    uint rt		= (instruction & 0x001f0000) >> 16;    
//    uint shamt  = (instruction & 0x000007c0) >> 6;
//
//    auto FillBit = [&](unsigned int from, unsigned int to, unsigned int pos)
//    {
//        bool setBit = (1 << pos) & immediate;
//        unsigned int ret = 0x00000000;
//        for(unsigned int i = from; i <= to; ++i)
//            ret |= (uint)setBit << i;
//        
//        return ret;
//    };
//    
//	if(opCode == 0) // R
//	{
//        sprintf(buff, "R Type\t\t| rd 0x%x / rs 0x%x / rt 0x%x / shamt 0x%x / funct 0x%x", rd, rs, rt, shamt, funct);
//        GlobalDumpLogManager->AddLog(buff, true);
//        
//        if(funct == (uint)Funct::Add)
//            return new Add(rs, rt, rd);
//		else if(funct == (uint)Funct::AddUnsigned)
//            return new AddUnsigned(rs, rt, rd);
//		else if(funct == (uint)Funct::And)
//            return new And(rs, rt, rd);
//		else if(funct == (uint)Funct::JumpRegister)
//            return new JumpRegister(rs, rt, rd);
//		else if(funct == (uint)Funct::Nor)
//            return new Nor(rs, rt, rd);
//		else if(funct == (uint)Funct::Or)
//            return new Or(rs, rt, rd);
//		else if(funct == (uint)Funct::SetLessThan)
//            return new SetLessThan(rs, rt, rd);
//		else if(funct == (uint)Funct::SetLessThanUnsigned)
//            return new SetLessThanUnsigned(rs, rt, rd);
//		else if(funct == (uint)Funct::ShiftLeftLogical)
//            return new ShiftLeftLogical(rs, rt, rd, shamt);
//		else if(funct == (uint)Funct::ShiftRightLogical)
//            return new ShiftRightLogical(rs,rt, rd, shamt);
//		else if(funct == (uint)Funct::Subtract)
//            return new Subtract(rs, rt, rd);
//		else if(funct == (uint)Funct::SubtractUnsigned)
//            return new SubtractUnsigned(rs, rt, rd);
//		else if(funct == (uint)Funct::Multiply)
//			return new Multiply(rs,rt, rd);
//		else if(funct == (uint)Funct::MultiplyUnsigned)
//			return new MultiplyUnsigned(rs, rt, rd);
//		else if(funct == (uint)Funct::Divide)
//			return new Divide(rs, rt, rd);
//		else if(funct == (uint)Funct::DivideUnsigned)
//			return new DivideUnsigned(rs, rt, rd);
//		else if(funct == (uint)Funct::MoveFromHi)
//			return new MoveFromHi(rd);
//		else if(funct == (uint)Funct::MoveToHi)
//			return new MoveToHi(rs);
//		else if(funct == (uint)Funct::MoveFromLo)
//			return new MoveFromLo(rd);
//		else if(funct == (uint)Funct::MoveToLo)
//			return new MoveToLo(rs);
//
//
//		else ASSERT_MSG("can not support r format this instruction");
//	}
//	else if(opCode == (uint)Opcode::Jump || opCode == (uint)Opcode::JumpAndLink) // J
//	{
//        unsigned int address = instruction & 0x03FFFFFF;
//
//        uint pc = GetProgramCounter() + 4;
//        uint jumpAddr = (pc & 0xf0000000) | (address << 2);
//
//        sprintf(buff, "J Type\t\t| opcode 0x%x / address 0x%x", opCode, jumpAddr);
//        GlobalDumpLogManager->AddLog(buff, true);
//
//        if(opCode == (uint)Opcode::Jump)
//            return new Jump(jumpAddr);
//        else if(opCode == (uint)Opcode::JumpAndLink)
//            return new JumpAndLink(jumpAddr);
//        else ASSERT_MSG("cant support j foramt this instruction");
//	}
//	else // I
//	{
//        uint mask           = FillBit(15, 31, 15);
//        uint signExtImm     = mask | immediate;
//        uint zeroExtImm     = immediate;
//
//		mask				= FillBit(17, 31, 15);
//        uint branchAddr     = FillBit(17, 31, 15) | (immediate << 2);
//        
//        sprintf(buff, "I Type\t\t| opcode 0x%x / signExtImm 0x%x / zeroExtImm 0x%x / branchAddr 0x%x", opCode, signExtImm, zeroExtImm, branchAddr);
//        GlobalDumpLogManager->AddLog(buff, true);
//        
//        if(opCode == (uint)Opcode::AddImmediate)
//            return new AddImmediate(rs, rt, signExtImm);
//        else if(opCode == (uint)Opcode::AddImmediateUnsigned)
//            return new AddImmediateUnsigned(rs, rt, signExtImm);
//        else if(opCode == (uint)Opcode::AndImmediate)
//            return new AndImmediate(rs, rt, zeroExtImm);
//        else if(opCode == (uint)Opcode::BranchOnEqual)
//            return new BranchOnEqual(rs, rt, branchAddr);
//        else if(opCode == (uint)Opcode::BranchOnNotEqual)
//            return new BranchOnNotEqual(rs, rt, branchAddr);
//        else if(opCode == (uint)Opcode::LoadByteUnsigned)
//            return new LoadByteUnsigned(rs, rt, signExtImm);
//        else if(opCode == (uint)Opcode::LoadHalfwordUnsigned)
//            return new LoadHalfwordUnsigned(rs, rt, signExtImm);
//        else if(opCode == (uint)Opcode::LoadLinked)
//            return new LoadLinked(rs, rt, signExtImm);
//        else if(opCode == (uint)Opcode::LoadUpperImmediate)
//            return new LoadUpperImmediate(rs, rt, immediate);
//        else if(opCode == (uint)Opcode::LoadWord)
//            return new LoadWord(rs, rt, signExtImm);
//        else if(opCode == (uint)Opcode::OrImmediate)
//            return new OrImmediate(rs, rt, zeroExtImm);
//        else if(opCode == (uint)Opcode::SetLessThanImmediate)
//            return new SetLessThanImmediate(rs, rt, zeroExtImm);
//        else if(opCode == (uint)Opcode::SetLessThanImmediateUnsigned)
//            return new SetLessThanImmediateUnsigned(rs, rt, zeroExtImm);
//        else if(opCode == (uint)Opcode::StoreByte)
//            return new StoreByte(rs, rt, zeroExtImm);
//        else if(opCode == (uint)Opcode::StoreConditional)
//            return new StoreConditional(rs, rt, zeroExtImm);
//        else if(opCode == (uint)Opcode::StoreHalfword)
//            return new StoreHalfword(rs, rt, zeroExtImm);
//        else if(opCode == (uint)Opcode::StoreWord)
//            return new StoreWord(rs, rt, zeroExtImm);
//		else if((opCode == (uint)Opcode::Multiply32BitRes) && (funct == (uint)Funct::Multiply32BitRes))
//        {
//            GlobalDumpLogManager->AddLog(" / funct 0x%x", funct);
//			return new Multiply32BitRes(rs, rt, rd);
//        }
//        
//        else ASSERT_MSG("cant support i foramt this inst");
//    }
//
//    ASSERT_MSG("Error!, not found inst");
    return nullptr;
}

bool System::Execution(Instruction* inst)
{
	return false;
}

void System::Memory()
{

}

void System::WriteBack()
{

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