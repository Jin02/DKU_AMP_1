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

void AndImmediate::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);

	_executionResult = _rsData & _immediate; 

    std::string equ = "R[rs] & ZeroExtImm";
    char buff[256] = {0, };
    sprintf(buff, "ExecutionResult = 0x%x / ExecutionResult = ", _executionResult);
    GlobalDumpLogManager->AddLog(buff+equ, true);
}