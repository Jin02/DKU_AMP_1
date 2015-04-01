#include "BranchOnNotEqual.h"
#include "System.h"
#include "DumpLogManager.h"

BranchOnNotEqual::BranchOnNotEqual(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(BranchOnNotEqual);
}

BranchOnNotEqual::~BranchOnNotEqual()
{

}

bool BranchOnNotEqual::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int rsData = system->GetDataFromRegister(_rs);
    unsigned int rtData = system->GetDataFromRegister(_rt);
    unsigned int pc = system->GetProgramCounter();
    
	GlobalDumpLogManager->AddLog("if(R[rs] != R[rt])\tPC = PC + 4 + BranchAddr", true);
	{
		char logBuffer[128] = {0, };
		sprintf(logBuffer, "if(R[%d](0x%x) != R[%d](0x%x))\tPC = {0x%x + 4 + 0x%x}(0x%x)", _rs, rsData, _rt, rtData, pc, _immediate, pc + 4 + _immediate);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

    if(rsData != rtData)
	{
        system->SetProgramCounter(pc + 4 + _immediate);
		return false;
	}

	return true;
}
