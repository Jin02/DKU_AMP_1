#include "BranchLessThan.h"
#include "System.h"

/** BranchLessThan **/
BranchLessThan::BranchLessThan(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

BranchLessThan::~BranchLessThan()
{
    
}

void BranchLessThan::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int rsData = system->GetDataFromRegister(_rs);
    unsigned int rtData = system->GetDataFromRegister(_rt);
    unsigned int pc = system->GetProgramCounter();
    
    if(rsData < rtData)
        system->SetProgramCounter(pc + 4 + _immediate);
}


/** BranchesLessThanOrEqual **/
BranchesLessThanOrEqual::BranchesLessThanOrEqual(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

BranchesLessThanOrEqual::~BranchesLessThanOrEqual()
{
    
}

void BranchesLessThanOrEqual::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int rsData = system->GetDataFromRegister(_rs);
    unsigned int rtData = system->GetDataFromRegister(_rt);
    unsigned int pc = system->GetProgramCounter();
    
    if(rsData <= rtData)
        system->SetProgramCounter(pc + 4 + _immediate);
}