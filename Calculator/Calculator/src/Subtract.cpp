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
    return rsData - rtData;
}

Subtract::Subtract(unsigned int rs, unsigned int rt, unsigned int rd) : SubtractUnsigned(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(Subtract);
}

Subtract::~Subtract()
{
}