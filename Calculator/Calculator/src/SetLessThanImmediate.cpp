#include "SetLessThanImmediate.h"
#include "System.h"

SetLessThanImmediateUnsigned::SetLessThanImmediateUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

SetLessThanImmediateUnsigned::~SetLessThanImmediateUnsigned()
{
    
}

void SetLessThanImmediateUnsigned::Execution()
{
    System* system = System::GetInstance();
    unsigned int rsData = system->GetDataFromRegister(_rs);
    system->SetDataToRegister(_rt, rsData < _immediate);
}




SetLessThanImmediate::SetLessThanImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

SetLessThanImmediate::~SetLessThanImmediate()
{
    
}

void SetLessThanImmediate::Execution()
{
    System* system = System::GetInstance();
    
    int     signedRsData      = system->GetDataFromRegister(_rs);
    int     signedImm         = _immediate;
    
    system->SetDataToRegister(_rt, signedRsData < signedImm);
}



