#include "AndImmediate.h"
#include "System.h"
#include "DumpLogManager.h"

AndImmediate::AndImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName;
}

AndImmediate::~AndImmediate()
{

}

bool AndImmediate::Execution()
{
    System* system = System::GetInstance();
    unsigned int rsData = system->GetDataFromRegister(_rs);

    system->SetDataToRegister(_rt, rsData & _immediate);
	{
		GlobalDumpLogManager->AddLog("R[rt] = R[rs] & ZeroExtImm", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = R[%d](0x%x) & 0x%x = %d", _rt, _rs, rsData, _immediate, rsData & _immediate);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}
