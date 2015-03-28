#include "OrImmediate.h"
#include "System.h"

OrImmediate::OrImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

OrImmediate::~OrImmediate()
{
    
}

bool OrImmediate::Execution()
{
    System* system = System::GetInstance();
    unsigned int rsData = system->GetDataFromRegister(_rs);

    system->SetDataToRegister(_rt, rsData | _immediate);
	return true;
}
