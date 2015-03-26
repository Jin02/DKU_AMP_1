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
    system->SetDataToRegister(_rd, Instruct(_rs, _rt));
}