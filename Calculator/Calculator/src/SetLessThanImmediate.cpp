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

void SetLessThanImmediateUnsigned::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);

	_executionResult = (_rsData < _immediate) ? 1 : 0; 
	GlobalDumpManagerAddExecutionLog(_executionResult);
}



SetLessThanImmediate::SetLessThanImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(SetLessThanImmediate);
}

SetLessThanImmediate::~SetLessThanImmediate()
{
    
}

void SetLessThanImmediate::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);

	int signedRsData = _rsData;
	int signedImm = _immediate;

	_executionResult = (signedRsData < signedImm) ? 1 : 0; 
	GlobalDumpManagerAddExecutionLog(_executionResult);
}
