#include "AddImmediate.h"
#include "System.h"


AddImmediateUnsigned::AddImmediateUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

AddImmediateUnsigned::~AddImmediateUnsigned()
{

}

void AddImmediateUnsigned::Instruct(unsigned int rs, unsigned int rt, unsigned int immediate)
{
    System* system = System::GetInstance();
    
    unsigned rsData = system->GetDataFromRegister(rs);
    system->SetDataToRegister(rt, rsData + immediate);
}
