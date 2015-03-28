#include "Multiply.h"
#include "System.h"

/** Multiply32BitRes **/

Multiply32BitRes::Multiply32BitRes(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
    
}

Multiply32BitRes::~Multiply32BitRes(void)
{

}

unsigned int Multiply32BitRes::Instruct(unsigned int rsData, unsigned int rtData)
{
    return rsData * rtData;
}

/** Multiply **/

Multiply::Multiply(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
    
}

Multiply::~Multiply(void)
{

}

unsigned int Multiply::Instruct(unsigned int rsData, unsigned int rtData)
{
	return 0;
}

bool Multiply::Execution()
{
	System* system = System::GetInstance();

	int rsData = system->GetDataFromRegister(_rs);
	int rtData = system->GetDataFromRegister(_rt);

	long long result = rsData * rtData;
	system->SetHiRegister( (result & 0xffffffff00000000) >> 32 );
	system->SetLoRegister( (result & 0x00000000ffffffff) );

	return true;
}

/** Multiply Unsigned **/

MultiplyUnsigned::MultiplyUnsigned(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
    
}

MultiplyUnsigned::~MultiplyUnsigned(void)
{

}

unsigned int MultiplyUnsigned::Instruct(unsigned int rsData, unsigned int rtData)
{
    return 0;
}

bool MultiplyUnsigned::Execution()
{
	System* system = System::GetInstance();

	uint rsData = system->GetDataFromRegister(_rs);
	uint rtData = system->GetDataFromRegister(_rt);

	unsigned long long result = rsData * rtData;
	system->SetHiRegister( (result & 0xffffffff00000000) >> 32 );
	system->SetLoRegister(result & 0x00000000ffffffff);

	return true;
}