#include "Add.h"
#include "System.h"

/** Add Unsigned **/

AddUnsigned::AddUnsigned(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
    
}

AddUnsigned::~AddUnsigned(void)
{
    
}

unsigned int AddUnsigned::Instruct(unsigned int rsData, unsigned int rtData)
{
    return rsData + rtData;
}