#include "Or.h"
#include "System.h"

/** Or **/

Or::Or(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
    
}

Or::~Or(void)
{
    
}

unsigned int Or::Instruct(unsigned int rsData, unsigned int rtData)
{
    return rsData | rtData;
}

/** Nor **/

Nor::Nor(unsigned int rs, unsigned int rt, unsigned int rd)
: RFormatInstruction(rs, rt, rd)
{
    
}

Nor::~Nor(void)
{
    
}

unsigned int Nor::Instruct(unsigned int rsData, unsigned int rtData)
{
    return ~(rsData | rtData);
}