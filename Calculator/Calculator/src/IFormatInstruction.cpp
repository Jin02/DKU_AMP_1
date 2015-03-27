#include "IFormatInstruction.h"
#include "System.h"
#include <string>

IFormatInstruction::IFormatInstruction(unsigned int rs, unsigned int rt, unsigned int immediate) : Instruction(), _immediate(immediate), _rs(rs), _rt(rt)
{
    
}

IFormatInstruction::~IFormatInstruction(void)
{
}