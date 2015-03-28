#include "AndImmediate.h"
#include "System.h"


AndImmediate::AndImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

AndImmediate::~AndImmediate()
{

}

bool AndImmediate::Execution()
{
    System* system = System::GetInstance();
    unsigned int rsData = system->GetDataFromRegister(_rs);

    system->SetDataToRegister(_rt, rsData & _immediate);
	return true;
}
