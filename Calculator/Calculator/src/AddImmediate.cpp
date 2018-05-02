#include "AddImmediate.h"
#include "System.h"
#include "DumpLogManager.h"

AddImmediate::AddImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) 
	: AddImmediateUnsigned(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(AddImmediate);
}
AddImmediate::~AddImmediate()
{

}

AddImmediateUnsigned::AddImmediateUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) 
	: IFormatInstruction(rs, rt, immediate)
{
    GlobalDumpManagerAddLogClassName(AddImmediateUnsigned);
}

AddImmediateUnsigned::~AddImmediateUnsigned()
{

}

void AddImmediateUnsigned::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);

	_executionResult = _rsData + _immediate; 

    std::string equ = "R[rs] + SignExtImmediate";
    char buff[256] = {0, };
    sprintf(buff, "ExecutionResult = 0x%x / ExecutionResult = ", _executionResult);
    GlobalDumpLogManager->AddLog(buff+equ, true);    
}