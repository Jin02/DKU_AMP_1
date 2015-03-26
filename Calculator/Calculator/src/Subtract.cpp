#include "Subtract.h"
#include "System.h"

SubtractUnsigned::SubtractUnsigned(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
    
}

SubtractUnsigned::~SubtractUnsigned(void)
{
    
}

unsigned int SubtractUnsigned::Instruct(unsigned int rsData, unsigned int rtData)
{
    return rsData - rtData;
}
