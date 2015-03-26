#include "RFormatInstruction.h"
#include "System.h"
#include <string>

RFormatInstruction::RFormatInstruction(unsigned int rs, unsigned int rt, unsigned int rd)
:_rs(rs), _rt(rt), _rd(rd)
{
    
}

RFormatInstruction::~RFormatInstruction(void)
{
}

void RFormatInstruction::Execution()
{
    System* system = System::GetInstance();
    
    unsigned rsData = system->GetDataFromRegister(_rs);
    unsigned rtData = system->GetDataFromRegister(_rt);
    
    system->SetDataToRegister(_rd, Instruct(rsData, rtData));
}