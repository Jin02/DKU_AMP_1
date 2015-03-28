#include "Divide.h"
#include "System.h"

/** Divide **/

Divide::Divide(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
    
}

Divide::~Divide(void)
{

}

unsigned int Divide::Instruct(unsigned int rsData, unsigned int rtData)
{
	return 0;
}

bool Divide::Execution()
{
	System* system = System::GetInstance();

	int rsData = system->GetDataFromRegister(_rs);
	int rtData = system->GetDataFromRegister(_rt);

	system->SetLoRegister(rsData / rtData);
	system->SetHiRegister(rsData % rtData);

	return true;
}

/** Divide Unsigned **/

DivideUnsigned::DivideUnsigned(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
    
}

DivideUnsigned::~DivideUnsigned(void)
{

}

unsigned int DivideUnsigned::Instruct(unsigned int rsData, unsigned int rtData)
{
    return 0;
}

bool DivideUnsigned::Execution()
{
	System* system = System::GetInstance();

	uint rsData = system->GetDataFromRegister(_rs);
	uint rtData = system->GetDataFromRegister(_rt);

	system->SetLoRegister(rsData / rtData);
	system->SetHiRegister(rsData % rtData);

	return true;
}