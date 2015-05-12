#include "AndImmediate.h"
#include "System.h"
#include "DumpLogManager.h"

AndImmediate::AndImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(AndImmediate);
}

AndImmediate::~AndImmediate()
{

}

void AndImmediate::Execution(const ForwardingFuncType& prev2stepInst, const ForwardingFuncType& prev1stepInst)
{
	_executionResult = _rsData & _immediate; 
	GlobalDumpManagerAddExecutionLog(_executionResult);
}