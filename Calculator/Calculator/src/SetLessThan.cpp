#include "SetLessThan.h"
#include "System.h"
#include "DumpLogManager.h"

/** SetLessThanUnsigned **/

SetLessThanUnsigned::SetLessThanUnsigned(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(SetLessThanUnsigned);
}

SetLessThanUnsigned::~SetLessThanUnsigned(void)
{
    
}

unsigned int SetLessThanUnsigned::Instruct(unsigned int rsData, unsigned int rtData)
{
    return rsData < rtData;
}

/** SetLessThan **/

SetLessThan::SetLessThan(unsigned int rs, unsigned int rt, unsigned int rd)
: RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(SetLessThan);
}

SetLessThan::~SetLessThan(void)
{
    
}

unsigned int SetLessThan::Instruct(unsigned int rsData, unsigned int rtData)
{
    int signedRsData = rsData;
    int signedRtData = rtData;

    return signedRsData < signedRtData;
}
