#include "JFormatInstruction.h"
#include "System.h"
#include <string>

/**** JForamt ****/
JFormatInstruction::JFormatInstruction(unsigned int address) : _address(address)
{
    
}

JFormatInstruction::~JFormatInstruction(void)
{
}

/**** Jump Instruction ****/
Jump::Jump(unsigned int address) : JFormatInstruction(address){}
Jump::~Jump(){}

bool Jump::Execution()
{
    System* system = System::GetInstance();
    system->SetProgramCounter(_address);

	return false;
}


/**** JumpAndLink Instruction ****/

JumpAndLink::JumpAndLink(unsigned int address) : JFormatInstruction(address){}
JumpAndLink::~JumpAndLink(){}

bool JumpAndLink::Execution()
{
    System* system = System::GetInstance();

    unsigned int currentProgramCounter = system->GetProgramCounter();
    system->SetReturnAddress(currentProgramCounter + 8);
    
    system->SetProgramCounter(_address);

	return false;
}
