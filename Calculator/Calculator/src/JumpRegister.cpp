#include "JumpRegister.h"
#include "System.h"
#include "DumpLogManager.h"

JumpRegister::JumpRegister(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(JumpRegister);

    System* system = System::GetInstance();
    system->SetProgramCounter(_rsData);
    {
        GlobalDumpLogManager->AddLog("PC = R[rs]", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "PC = R[%d](0x%x)", rs, _rsData);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }
}

JumpRegister::~JumpRegister(void)
{
    
}

unsigned int JumpRegister::Instruct(unsigned int rsData, unsigned int rtData)
{
    return 0;
}