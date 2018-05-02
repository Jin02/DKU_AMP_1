#include "And.h"
#include "System.h"
#include "DumpLogManager.h"

And::And(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(And);
}

And::~And(void)
{
    
}

unsigned int And::Instruct(unsigned int rsData, unsigned int rtData)
{
    std::string equ = "R[rs] & R[rt]";
    char buff[256] = {0, };
    sprintf(buff, "ExecutionResult = 0x%x / ExecutionResult = ", rsData + rtData);
    GlobalDumpLogManager->AddLog(buff+equ, true);
    
    return rsData & rtData;
}