#include "SetLessThanImmediate.h"
#include "System.h"
#include "DumpLogManager.h"

SetLessThanImmediateUnsigned::SetLessThanImmediateUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(SetLessThanImmediateUnsigned);
}

SetLessThanImmediateUnsigned::~SetLessThanImmediateUnsigned()
{
    
}

void SetLessThanImmediateUnsigned::Execution()
{
	_executionResult = _rsData < _immediate; 
	GlobalDumpManagerAddExecutionLog(_executionResult);
}



SetLessThanImmediate::SetLessThanImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(SetLessThanImmediate);
}

SetLessThanImmediate::~SetLessThanImmediate()
{
    
}

void SetLessThanImmediate::Execution()
{
	int signedRsData = _rsData;
	int signedImm = _immediate;

	_executionResult = signedRsData < signedImm; 
	GlobalDumpManagerAddExecutionLog(_executionResult);
}
