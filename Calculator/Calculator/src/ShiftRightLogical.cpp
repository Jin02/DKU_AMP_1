#include "ShiftRightLogical.h"
#include "System.h"

ShiftRightLogical::ShiftRightLogical(unsigned int rs, unsigned int rt, unsigned int rd, unsigned int shamt)
    : RFormatInstruction(rs, rt, rd), _shamt(shamt)
{
    
}

ShiftRightLogical::~ShiftRightLogical(void)
{
    
}

unsigned int ShiftRightLogical::Instruct(unsigned int rsData, unsigned int rtData)
{
    return rtData >> _shamt;
}