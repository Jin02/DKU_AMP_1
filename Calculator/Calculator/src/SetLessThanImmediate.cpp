#include "SetLessThanImmediate.h"
#include "System.h"
#include "DumpLogManager.h"

SetLessThanImmediateUnsigned::SetLessThanImmediateUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(SetLessThanImmediateUnsigned);
}

SetLessThanImmediateUnsigned::~SetLessThanImmediateUnsigned()
{
    
}

bool SetLessThanImmediateUnsigned::Execution()
{
    System* system = System::GetInstance();
    unsigned int rsData = system->GetDataFromRegister(_rs);
    system->SetDataToRegister(_rt, rsData < _immediate);
	{
		GlobalDumpLogManager->AddLog("R[rt] = (R[rs] < SignExtImm) ? 1 : 0", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = (R[%d](0x%x) < 0x%x) ? 1 :0 = %d", _rt, _rs, rsData, _immediate, rsData < _immediate);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}




SetLessThanImmediate::SetLessThanImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(SetLessThanImmediate);
}

SetLessThanImmediate::~SetLessThanImmediate()
{
    
}

bool SetLessThanImmediate::Execution()
{
    System* system = System::GetInstance();
    
    int     signedRsData      = system->GetDataFromRegister(_rs);
    int     signedImm         = _immediate;
    
    system->SetDataToRegister(_rt, signedRsData < signedImm);
	{
		GlobalDumpLogManager->AddLog("R[rt] = (R[rs] < SignExtImm) ? 1 : 0", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = (R[%d](0x%x) < 0x%x) ? 1 :0 = %d", _rt, _rs, signedRsData, _immediate, signedRsData < signedImm);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}


	return true;
}



