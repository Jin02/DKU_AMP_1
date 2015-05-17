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
    _type = Type::Jump;
}

JFormatInstruction::~JFormatInstruction(void)
{
}

void JFormatInstruction::DependencyCheckWithGetTargetData(bool&, uint&, uint) const
{
}

/**** Jump Instruction ****/
Jump::Jump(unsigned int address) : JFormatInstruction(address)
{
	GlobalDumpManagerAddLogClassName(Jump);
}

Jump::~Jump(){}

void Jump::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
    System* system = System::GetInstance();
    system->SetProgramCounter(_address+4);
    {
        GlobalDumpLogManager->AddLog("PC = JumpAddr", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "PC = 0x%x", _address);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }
}

/**** JumpAndLink Instruction ****/

JumpAndLink::JumpAndLink(unsigned int address)
    : JFormatInstruction(address), _executionResult(0)
{
    GlobalDumpManagerAddLogClassName(JumpAndLink);
}

JumpAndLink::~JumpAndLink()
{

}

void JumpAndLink::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	System* system = System::GetInstance();
    _executionResult = _pc + 8;
    
    system->SetProgramCounter(_address+4);
    {
        GlobalDumpLogManager->AddLog("R[31] = PC + 8; PC = JumpAddr", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "R[31] = 0x%x; PC = 0x%x", _pc + 8, _address);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }
}

void JumpAndLink::Memory()
{

}

void JumpAndLink::WriteBack()
{
	System* system = System::GetInstance();
	system->SetReturnAddress(_executionResult);
}