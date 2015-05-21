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
    return rsData & rtData;
}