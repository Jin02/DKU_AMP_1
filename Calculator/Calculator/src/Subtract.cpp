#include "Subtract.h"
#include "System.h"
#include "DumpLogManager.h"

SubtractUnsigned::SubtractUnsigned(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(SubtractUnsigned);
}

SubtractUnsigned::~SubtractUnsigned(void)
{
    
}

unsigned int SubtractUnsigned::Instruct(unsigned int rsData, unsigned int rtData)
{
    std::string equ = "R[rs] - R[rt]";
    char buff[256] = {0, };
    sprintf(buff, "ExecutionResult = 0x%x / ExecutionResult = ", rsData + rtData);
    GlobalDumpLogManager->AddLog(buff+equ, true);
    
    return rsData - rtData;
}

Subtract::Subtract(unsigned int rs, unsigned int rt, unsigned int rd) : SubtractUnsigned(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(Subtract);
}

Subtract::~Subtract()
{
}