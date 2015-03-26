#include "OrImmediate.h"
#include "System.h"

OrImmediate::OrImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

OrImmediate::~OrImmediate()
{
    
}

void OrImmediate::Instruct(unsigned int rs, unsigned int rt, unsigned int immediate)
{
    System* system = System::GetInstance();
    unsigned int rsData = system->GetDataFromRegister(rs);
    system->SetDataToRegister(rt, rsData | immediate);
}
