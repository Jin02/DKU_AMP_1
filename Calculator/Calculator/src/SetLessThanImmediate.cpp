#include "SetLessThanImmediate.h"
#include "System.h"

SetLessThanImmediateUnsigned::SetLessThanImmediateUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

SetLessThanImmediateUnsigned::~SetLessThanImmediateUnsigned()
{
    
}

bool SetLessThanImmediateUnsigned::Execution()
{
    System* system = System::GetInstance();
    unsigned int rsData = system->GetDataFromRegister(_rs);
    system->SetDataToRegister(_rt, rsData < _immediate);

	return true;
}




SetLessThanImmediate::SetLessThanImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

SetLessThanImmediate::~SetLessThanImmediate()
{
    
}

bool SetLessThanImmediate::Execution()
{
    System* system = System::GetInstance();
    
    int     signedRsData      = system->GetDataFromRegister(_rs);
    int     signedImm         = _immediate;
    
    system->SetDataToRegister(_rt, signedRsData < signedImm);
	return true;
}



