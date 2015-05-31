#include "Multiply.h"
#include "System.h"
#include "DumpLogManager.h"

/** Multiply32BitRes **/

Multiply32BitRes::Multiply32BitRes(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(Multiply32BitRes);
}

Multiply32BitRes::~Multiply32BitRes(void)
{

}

unsigned int Multiply32BitRes::Instruct(unsigned int rsData, unsigned int rtData)
{
    std::string equ = "R[rs] * R[rt]";
    char buff[256] = {0, };
    sprintf(buff, "ExecutionResult = 0x%x / ExecutionResult = ", rsData + rtData);
    GlobalDumpLogManager->AddLog(buff+equ, true);
    
    return rsData * rtData;
}

/** Multiply **/

Multiply::Multiply(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd), _multyplyExecutionResult(0)
{
	GlobalDumpManagerAddLogClassName(Multiply);
}

Multiply::~Multiply(void)
{

}

unsigned int Multiply::Instruct(unsigned int rsData, unsigned int rtData)
{
	return 0;
}

void Multiply::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);
	Forwarding(prev2stepInst, prev1stepInst, _rtData, _rt);

	_multyplyExecutionResult = _rsData * _rtData;
    {
        char buff[256] = {0, };
        sprintf(buff, "ExecutionResult = 0x%llx", _multyplyExecutionResult);
        GlobalDumpLogManager->AddLog(buff, true);
    }

}

void Multiply::WriteBack()
{
	System* system = System::GetInstance();
	
	uint hiData = (_multyplyExecutionResult & 0xffffffff00000000) >> 32;
	uint loData = _multyplyExecutionResult & 0x00000000ffffffff;

	system->SetHiRegister( hiData );
	system->SetLoRegister( loData );
	{
		char buff[256] = {0, };	
		sprintf(buff, "Hi = 0x%x / Lo = 0x%x", hiData, loData);
		GlobalDumpLogManager->AddLog(buff, true);
	}
}

/** Multiply Unsigned **/

MultiplyUnsigned::MultiplyUnsigned(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd), _multyplyExecutionResult(0)
{
	GlobalDumpManagerAddLogClassName(MultiplyUnsigned);
}

MultiplyUnsigned::~MultiplyUnsigned(void)
{

}

unsigned int MultiplyUnsigned::Instruct(unsigned int rsData, unsigned int rtData)
{
    return 0;
}

void MultiplyUnsigned::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);
	Forwarding(prev2stepInst, prev1stepInst, _rtData, _rt);

	_multyplyExecutionResult = _rsData * _rtData;	
    {
        char buff[256] = {0, };
        sprintf(buff, "ExecutionResult = 0x%llx", _multyplyExecutionResult);
        GlobalDumpLogManager->AddLog(buff, true);
    }
}

void MultiplyUnsigned::WriteBack()
{
	System* system = System::GetInstance();
	
	uint hiData = (_multyplyExecutionResult & 0xffffffff00000000) >> 32;
	uint loData = _multyplyExecutionResult & 0x00000000ffffffff;

	system->SetHiRegister( hiData );
	system->SetLoRegister( loData );
	{
		char buff[256] = {0, };	
		sprintf(buff, "Hi = 0x%x / Lo = 0x%x", hiData, loData);
		GlobalDumpLogManager->AddLog(buff, true);
	}
}