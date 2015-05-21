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

void OrImmediate::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);

	_executionResult = _rsData | _immediate; 
	GlobalDumpManagerAddExecutionLog(_executionResult);
}