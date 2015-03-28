#include "Move.h"
#include "System.h"

/** Move **/
Move::Move(unsigned int rs, unsigned int rd) : Instruction(), _rs(rs), _rd(rd){}
Move::~Move(){}
bool Move::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int rsData = system->GetDataFromRegister(_rs);
    system->SetDataToRegister(_rd, rsData);

	return true;
}

/** MoveFromHi **/
MoveFromHi::MoveFromHi(unsigned int rd) : Instruction(), _rd(rd){}
MoveFromHi::~MoveFromHi(){}
bool MoveFromHi::Execution()
{
    System* system = System::GetInstance();
    
	uint hi = system->GetHiRegister();
	system->SetDataToRegister(_rd, hi);

	return true;
}

/** MoveToHi **/
MoveToHi::MoveToHi(unsigned int rs) : Instruction(), _rs(rs){}
MoveToHi::~MoveToHi(){}
bool MoveToHi::Execution()
{
    System* system = System::GetInstance();

	uint rsData = system->GetDataFromRegister(_rs);
	system->SetHiRegister(rsData);

	return true;
}

/** MoveFromLo **/
MoveFromLo::MoveFromLo(unsigned int rd) : Instruction(), _rd(rd){}
MoveFromLo::~MoveFromLo(){}
bool MoveFromLo::Execution()
{
    System* system = System::GetInstance();
    
	uint lo = system->GetLoRegister();
	system->SetDataToRegister(_rd, lo);

	return true;
}

/** MoveToLo **/
MoveToLo::MoveToLo(unsigned int rs) : Instruction(), _rs(rs){}
MoveToLo::~MoveToLo(){}
bool MoveToLo::Execution()
{
    System* system = System::GetInstance();

	uint rsData = system->GetDataFromRegister(_rs);
	system->SetLoRegister(rsData);

	return true;
}