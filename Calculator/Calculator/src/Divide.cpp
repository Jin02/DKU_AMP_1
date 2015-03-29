#include "Divide.h"
#include "System.h"
#include "DumpLogManager.h"

/** Divide **/

Divide::Divide(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName;
}

Divide::~Divide(void)
{

}

unsigned int Divide::Instruct(unsigned int rsData, unsigned int rtData)
{
	return 0;
}

bool Divide::Execution()
{
	System* system = System::GetInstance();

	int rsData = system->GetDataFromRegister(_rs);
	int rtData = system->GetDataFromRegister(_rt);

	system->SetLoRegister(rsData / rtData);
	system->SetHiRegister(rsData % rtData);	
	{
		GlobalDumpLogManager->AddLog("Lo = R[rs] / R[rt]; Hi = R[rs] % R[rt]", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "Lo = R[%d](0x%x) / R[%d](0x%x) = 0x%x  //  Hi = R[%d](0x%x) % R[%d](0x%x) = 0x%x", _rs, rsData, _rt, rtData, rsData / rtData, _rs, rsData, _rt, rtData, rsData % rtData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}

/** Divide Unsigned **/

DivideUnsigned::DivideUnsigned(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName;
}

DivideUnsigned::~DivideUnsigned(void)
{

}

unsigned int DivideUnsigned::Instruct(unsigned int rsData, unsigned int rtData)
{
    return 0;
}

bool DivideUnsigned::Execution()
{
	System* system = System::GetInstance();

	uint rsData = system->GetDataFromRegister(_rs);
	uint rtData = system->GetDataFromRegister(_rt);

	system->SetLoRegister(rsData / rtData);
	system->SetHiRegister(rsData % rtData);
	{
		GlobalDumpLogManager->AddLog("Lo = R[rs] / R[rt]; Hi = R[rs] % R[rt]", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "Lo = R[%d](0x%x) / R[%d](0x%x) = 0x%x  //  Hi = R[%d](0x%x) % R[%d](0x%x) = 0x%x", _rs, rsData, _rt, rtData, rsData / rtData, _rs, rsData, _rt, rtData, rsData % rtData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}