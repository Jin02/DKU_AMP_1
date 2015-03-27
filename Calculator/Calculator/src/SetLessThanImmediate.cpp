#include "SetLessThanImmediate.h"
#include "System.h"

SetLessThanImmediateUnsigned::SetLessThanImmediateUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

SetLessThanImmediateUnsigned::~SetLessThanImmediateUnsigned()
{
    
}

void SetLessThanImmediateUnsigned::Instruct(unsigned int rs, unsigned int rt, unsigned int immediate)
{
    System* system = System::GetInstance();
    unsigned int rsData = system->GetDataFromRegister(rs);
    system->SetDataToRegister(rt, rsData < immediate);
}




SetLessThanImmediate::SetLessThanImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

SetLessThanImmediate::~SetLessThanImmediate()
{
    
}

void SetLessThanImmediate::Instruct(unsigned int rs, unsigned int rt, unsigned int immediate)
{
    System* system = System::GetInstance();
    
    int     signedRsData      = system->GetDataFromRegister(rs);
    int     signedImm         = immediate;
    
    system->SetDataToRegister(rt, signedRsData < signedImm);
}



