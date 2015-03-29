#include "JumpRegister.h"
#include "System.h"
#include "DumpLogManager.h"

JumpRegister::JumpRegister(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName;
}

JumpRegister::~JumpRegister(void)
{
    
}

unsigned int JumpRegister::Instruct(unsigned int rsData, unsigned int rtData)
{
    return 0;
}

bool JumpRegister::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int rsData = system->GetDataFromRegister(_rs);
    system->SetProgramCounter(rsData);
	{
		GlobalDumpLogManager->AddLog("PC = R[rs]", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "PC = R[%d](0x%x)", _rs, rsData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}


	return false;
}