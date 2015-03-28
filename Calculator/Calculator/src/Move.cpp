#include "Move.h"
#include "System.h"

Move::Move(unsigned int rs, unsigned int rd) : Instruction(), _rs(rs), _rd(rd)
{
    
}

Move::~Move()
{
    
}

bool Move::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int rsData = system->GetDataFromRegister(_rs);
    system->SetDataToRegister(_rd, rsData);

	return true;
}