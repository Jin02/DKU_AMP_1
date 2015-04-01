#include "Load.h"
#include "System.h"
#include "DumpLogManager.h"

/** LoadByteUnsigned **/

LoadByteUnsigned::LoadByteUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(LoadByteUnsigned);
}

LoadByteUnsigned::~LoadByteUnsigned()
{

}

bool LoadByteUnsigned::Execution()
{
    System* system = System::GetInstance();
    unsigned int rsData     = system->GetDataFromRegister(_rs);
    unsigned int memData    = system->GetDataFromMemory(rsData+_immediate);
    unsigned int toRegiData = memData & 0x000000ff;
    
    system->SetDataToRegister(_rt, toRegiData);
	{
		GlobalDumpLogManager->AddLog("R[rt] = {24'b0, M[R[rs] + SignExtImm](7:0)}", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = {0x000000, M[R[%d](0x%x) + 0x%x](7:0)} = 0x%x", _rt, _rs, rsData, _immediate, toRegiData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}

/** LoadHalfwordUnsigned **/
LoadHalfwordUnsigned::LoadHalfwordUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(LoadHalfwordUnsigned);
}

LoadHalfwordUnsigned::~LoadHalfwordUnsigned()
{
    
}

bool LoadHalfwordUnsigned::Execution()
{
    System* system = System::GetInstance();
    unsigned int rsData     = system->GetDataFromRegister(_rs);
    unsigned int memData    = system->GetDataFromMemory(rsData+_immediate);
    unsigned int toRegiData = memData & 0x0000ffff;
    
    system->SetDataToRegister(_rt, toRegiData);
	{
		GlobalDumpLogManager->AddLog("R[rt] = {16'b0, M[R[rs] + SignExtImm](15:0)}", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = {0x0000, M[R[%d](0x%x) + 0x%x](15:0)} = 0x%x", _rt, _rs, rsData, _immediate, toRegiData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}


/** LoadLinked **/

//LoadLinked::LoadLinked(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
//{
//    
//}
//
//LoadLinked::~LoadLinked()
//{
//    
//}
//
//void LoadLinked::Execution()
//{
//    System* system = System::GetInstance();
//    
//    unsigned int rsData = system->GetDataFromRegister(_rs);
//    unsigned int memData = system->GetDataFromMemory(rsData + _immediate);
//    
//    system->SetDataToRegister(_rt, memData);
//}

/** LoadUpperImmediate **/

LoadUpperImmediate::LoadUpperImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(LoadUpperImmediate);
}

LoadUpperImmediate::~LoadUpperImmediate()
{
    
}

bool LoadUpperImmediate::Execution()
{
    System* system = System::GetInstance();
    system->SetDataToRegister(_rt, _immediate & 0xffff0000);
	{
		GlobalDumpLogManager->AddLog("R[rt] = {(immediate, 16b'0)}", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = 0x%x", _rt, _immediate & 0xffff0000);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}

/** LoadWord **/

LoadWord::LoadWord(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(LoadWord);
}

LoadWord::~LoadWord()
{
    
}

bool LoadWord::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int rsData = system->GetDataFromRegister(_rs);
    unsigned int memData = system->GetDataFromMemory(rsData + _immediate);

    system->SetDataToRegister(_rt, memData);
	{
		GlobalDumpLogManager->AddLog("R[rt] = M[R[rs] + SignExtImmm]", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = M[R[%d](0x%x) + 0x%x] = 0x%x", _rt, _rs, rsData, _immediate, memData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}

/** LoadImmediate **/

LoadImmediate::LoadImmediate(unsigned int rd, unsigned int immediate)
    : Instruction(), _rd(rd), _immediate(immediate)
{
	GlobalDumpManagerAddLogClassName(LoadImmediate);
}

LoadImmediate::~LoadImmediate()
{
    
}

bool LoadImmediate::Execution()
{
    System* system = System::GetInstance();
    system->SetDataToRegister(_rd, _immediate);
	{
		GlobalDumpLogManager->AddLog("R[rd] = immediate", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = 0x%x", _rd, _immediate);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}
