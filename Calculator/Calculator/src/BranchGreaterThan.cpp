#include "BranchGreaterThan.h"
#include "System.h"

/** BranchGreaterThan **/
BranchGreaterThan::BranchGreaterThan(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

BranchGreaterThan::~BranchGreaterThan()
{
    
}

void BranchGreaterThan::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int rsData = system->GetDataFromRegister(_rs);
    unsigned int rtData = system->GetDataFromRegister(_rt);
    unsigned int pc = system->GetProgramCounter();
    
    if(rsData > rtData)
        system->SetProgramCounter(pc + 4 + _immediate);
}


/** BranchesGreaterThanOrEqual **/
BranchesGreaterThanOrEqual::BranchesGreaterThanOrEqual(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

BranchesGreaterThanOrEqual::~BranchesGreaterThanOrEqual()
{
    
}

void BranchesGreaterThanOrEqual::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int rsData = system->GetDataFromRegister(_rs);
    unsigned int rtData = system->GetDataFromRegister(_rt);
    unsigned int pc = system->GetProgramCounter();
    
    if(rsData >= rtData)
        system->SetProgramCounter(pc + 4 + _immediate);
}