#include "IFormatInstruction.h"
#include "System.h"
#include <string>

IFormatInstruction::IFormatInstruction(unsigned int rs, unsigned int rt, unsigned int immediate) :_immediate(immediate), _rs(rs), _rt(rt)
{
    
}

IFormatInstruction::~IFormatInstruction(void)
{
}

void IFormatInstruction::Execution()
{
    Instruct(_rs, _rt, _immediate);
}