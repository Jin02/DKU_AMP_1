#include "OrImmediate.h"
#include "System.h"
#include "DumpLogManager.h"

OrImmediate::OrImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(OrImmediate);
}

OrImmediate::~OrImmediate()
{
    
}

bool OrImmediate::Execution()
{
	_executionResult = _rsData | _immediate; 
	GlobalDumpManagerAddExecutionLog(_executionResult);

	return true;
}