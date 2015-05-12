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

void AddImmediateUnsigned::Execution(const ForwardingFuncType& prev2stepInst, const ForwardingFuncType& prev1stepInst)
{
	_executionResult = _rsData + _immediate; 
	GlobalDumpManagerAddExecutionLog(_executionResult);
}