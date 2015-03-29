#include "AddImmediate.h"
#include "System.h"
#include "DumpLogManager.h"

AddImmediate::AddImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : AddImmediateUnsigned(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName;
}
AddImmediate::~AddImmediate()
{

}

AddImmediateUnsigned::AddImmediateUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    GlobalDumpManagerAddLogClassName;
}

AddImmediateUnsigned::~AddImmediateUnsigned()
{

}

bool AddImmediateUnsigned::Execution()
{
    System* system = System::GetInstance();
    
    unsigned rsData = system->GetDataFromRegister(_rs);
    system->SetDataToRegister(_rt, rsData + _immediate);
	{
		GlobalDumpLogManager->AddLog("R[rt] = R[rs] + SignExtImm", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = R[%d](0x%x) + 0x%x = 0x%x", _rt, _rs, rsData, _immediate, rsData + _immediate);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}
