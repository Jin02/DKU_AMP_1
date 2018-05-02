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
    std::string equ = "R[rs] < R[rt]";
    char buff[256] = {0, };
    sprintf(buff, "ExecutionResult = 0x%x / ExecutionResult = ", rsData + rtData);
    GlobalDumpLogManager->AddLog(buff+equ, true);
    
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

    std::string equ = "R[rs] < R[rt]";
    char buff[256] = {0, };
    sprintf(buff, "ExecutionResult = 0x%x / ExecutionResult = ", rsData + rtData);
    GlobalDumpLogManager->AddLog(buff+equ, true);
    
    return signedRsData < signedRtData;
}
