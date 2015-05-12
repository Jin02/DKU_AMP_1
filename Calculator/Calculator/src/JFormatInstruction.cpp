#include "JFormatInstruction.h"
#include "System.h"
#include <string>
#include "DumpLogManager.h"

/**** JForamt ****/
JFormatInstruction::JFormatInstruction(unsigned int address)
    : Instruction(), _address(address)
{
    char buff[256] = {0, };
    sprintf(buff, "J Type\t\t| address = 0x%x", address);
    GlobalDumpLogManager->AddLog(buff, true);
}

JFormatInstruction::~JFormatInstruction(void)
{
}

/**** Jump Instruction ****/
Jump::Jump(unsigned int address) : JFormatInstruction(address)
{
	GlobalDumpManagerAddLogClassName(Jump);
    
    System* system = System::GetInstance();
    system->SetProgramCounter(_address);
    {
        GlobalDumpLogManager->AddLog("PC = JumpAddr", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "PC = 0x%x", _address);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }
}

Jump::~Jump(){}

/**** JumpAndLink Instruction ****/

JumpAndLink::JumpAndLink(unsigned int address) : JFormatInstruction(address)
{
    GlobalDumpManagerAddLogClassName(JumpAndLink);

    System* system = System::GetInstance();
    
    unsigned int currentProgramCounter = system->GetProgramCounter();
    system->SetReturnAddress(currentProgramCounter + 8);
    
    system->SetProgramCounter(_address);
    {
        GlobalDumpLogManager->AddLog("R[31] = PC + 8; PC = JumpAddr", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "R[31] = 0x%x; PC = 0x%x", currentProgramCounter + 8, _address);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }
}
JumpAndLink::~JumpAndLink()
{

}
