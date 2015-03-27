#include "BranchOnEqual.h"
#include "System.h"


BranchOnEqual::BranchOnEqual(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

BranchOnEqual::~BranchOnEqual()
{

}

void BranchOnEqual::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int rsData = system->GetDataFromRegister(_rs);
    unsigned int rtData = system->GetDataFromRegister(_rt);
    unsigned int pc = system->GetProgramCounter();
    
    if(rsData == rtData)
        system->SetProgramCounter(pc + 4 + _immediate);
}
