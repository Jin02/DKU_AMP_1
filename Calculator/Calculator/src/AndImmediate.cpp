#include "AndImmediate.h"
#include "System.h"


AndImmediate::AndImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

AndImmediate::~AndImmediate()
{

}

void AndImmediate::Instruct(unsigned int rs, unsigned int rt, unsigned int immediate)
{
    System* system = System::GetInstance();
    unsigned int rsData = system->GetDataFromRegister(rs);
    system->SetDataToRegister(rt, rsData & immediate);
}
