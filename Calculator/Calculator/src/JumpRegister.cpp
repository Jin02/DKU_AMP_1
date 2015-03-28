#include "JumpRegister.h"
#include "System.h"

/** Add Unsigned **/

JumpRegister::JumpRegister(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
    
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

	return false;
}