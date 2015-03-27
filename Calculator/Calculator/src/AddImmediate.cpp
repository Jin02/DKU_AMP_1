#include "AddImmediate.h"
#include "System.h"


AddImmediateUnsigned::AddImmediateUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

AddImmediateUnsigned::~AddImmediateUnsigned()
{

}

void AddImmediateUnsigned::Execution()
{
    System* system = System::GetInstance();
    
    unsigned rsData = system->GetDataFromRegister(_rs);
    system->SetDataToRegister(_rt, rsData + _immediate);
}
