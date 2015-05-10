#include "ShiftLeftLogical.h"
#include "System.h"
#include "DumpLogManager.h"

ShiftLeftLogical::ShiftLeftLogical(unsigned int rs, unsigned int rt, unsigned int rd, unsigned int shamt)
    : RFormatInstruction(rs, rt, rd), _shamt(shamt)
{
	GlobalDumpManagerAddLogClassName(ShiftLeftLogical);
}

ShiftLeftLogical::~ShiftLeftLogical(void)
{
    
}

unsigned int ShiftLeftLogical::Instruct(unsigned int rsData, unsigned int rtData)
{
    return rtData << _shamt;
}