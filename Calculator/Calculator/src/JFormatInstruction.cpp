#include "JFormatInstruction.h"
#include "System.h"
#include <string>
#include "DumpLogManager.h"

/**** JForamt ****/
JFormatInstruction::JFormatInstruction(unsigned int address) : _address(address)
{
    
}

JFormatInstruction::~JFormatInstruction(void)
{
}

/**** Jump Instruction ****/
Jump::Jump(unsigned int address) : JFormatInstruction(address)
{
	GlobalDumpManagerAddLogClassName(Jump);
}
Jump::~Jump(){}

bool Jump::Execution()
{
    System* system = System::GetInstance();
    system->SetProgramCounter(_address);
	{
		GlobalDumpLogManager->AddLog("PC = JumpAddr", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "PC = 0x%x", _address);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return false;
}


/**** JumpAndLink Instruction ****/

JumpAndLink::JumpAndLink(unsigned int address) : JFormatInstruction(address)
{
	GlobalDumpManagerAddLogClassName(JumpAndLink);
}
JumpAndLink::~JumpAndLink()
{

}

bool JumpAndLink::Execution()
{
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
	return false;
}
