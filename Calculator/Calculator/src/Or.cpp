#include "Or.h"
#include "System.h"
#include "DumpLogManager.h"

/** Or **/

Or::Or(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(Or);
}

Or::~Or(void)
{
    
}

unsigned int Or::Instruct(unsigned int rsData, unsigned int rtData)
{
    std::string equ = "R[rs] | R[rt]";
    char buff[256] = {0, };
    sprintf(buff, "ExecutionResult = 0x%x / ExecutionResult = ", rsData + rtData);
    GlobalDumpLogManager->AddLog(buff+equ, true);
    
    return rsData | rtData;
}

/** Nor **/

Nor::Nor(unsigned int rs, unsigned int rt, unsigned int rd)
: RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(Nor);
}

Nor::~Nor(void)
{
    
}

unsigned int Nor::Instruct(unsigned int rsData, unsigned int rtData)
{
    std::string equ = "~(R[rs] | R[rt])";
    char buff[256] = {0, };
    sprintf(buff, "ExecutionResult = 0x%x / ExecutionResult = ", rsData + rtData);
    GlobalDumpLogManager->AddLog(buff+equ, true);
    
    return ~(rsData | rtData);
}