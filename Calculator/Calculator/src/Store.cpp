#include "Store.h"
#include "System.h"
#include "DumpLogManager.h"

/** StoreByte **/
StoreByte::StoreByte(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(StoreByte);
}

StoreByte::~StoreByte()
{
    
}

bool StoreByte::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int toMemRtData = system->GetDataFromRegister(_rt) & 0x0000000f;
    unsigned int rsData = system->GetDataFromRegister(_rs);
    unsigned int memData = system->GetDataFromMemory(rsData + _immediate);

    memData = (memData & 0xfffffff0) | (toMemRtData);
    system->SetDataToMemory(rsData + _immediate, memData);
	{
		GlobalDumpLogManager->AddLog("M[R[rs] + SignExtImm](7:0) = R[rt](7:0)", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "M[(R[%d](0x%x) + 0x%x) = 0x%x](7:0) = R[%d](0x%x)(7:0)", _rs, rsData, _immediate, rsData + _immediate, _rt, toMemRtData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}


/** StoreConditional **/

//StoreConditional::StoreConditional(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
//{
//    
//}
//
//StoreConditional::~StoreConditional()
//{
//    
//}
//
//void StoreConditional::Execution()
//{
//}

/** StoreUpperImmediate **/

StoreHalfword::StoreHalfword(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(StoreHalfword);
}

StoreHalfword::~StoreHalfword()
{
    
}

bool StoreHalfword::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int toMemRtData = system->GetDataFromRegister(_rt) & 0x0000ffff;
    unsigned int rsData = system->GetDataFromRegister(_rs);
    unsigned int memData = system->GetDataFromMemory(rsData + _immediate);
    
    memData = (memData & 0xffff0000) | (toMemRtData);
    system->SetDataToMemory(rsData + _immediate, memData);
	{
		GlobalDumpLogManager->AddLog("M[R[rs] + SignExtImm](15:0) = R[rt](15:0)", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "M[(R[%d](0x%x) + 0x%x) = 0x%x](15:0) = R[%d](0x%x)(15:0)", _rs, rsData, _immediate, rsData + _immediate, _rt, toMemRtData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}

/** StoreWord **/

StoreWord::StoreWord(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(StoreWord);
}

StoreWord::~StoreWord()
{
    
}

bool StoreWord::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int toMemRtData = system->GetDataFromRegister(_rt);
    unsigned int rsData = system->GetDataFromRegister(_rs);
    system->SetDataToMemory(rsData + _immediate, toMemRtData);
	{
		GlobalDumpLogManager->AddLog("M[R[rs] + SignExtImm] = R[rt]", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "M[(R[%d](0x%x) + 0x%x) = 0x%x] = R[%d](0x%x)", _rs, rsData, _immediate, rsData + _immediate, _rt, toMemRtData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}
