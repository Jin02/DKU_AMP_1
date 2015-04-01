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
	{
		GlobalDumpLogManager->AddLog("R[rd] = (R[rs] < R[rt]) ? 1 : 0", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = (R[%d](0x%x) < R[%d](0x%x)) ? 1 : 0 = %d", _rd, _rs, rsData, _rt, rtData, rsData < rtData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

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
    
	{
		GlobalDumpLogManager->AddLog("R[rd] = (R[rs] < R[rt]) ? 1 : 0", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = (R[%d](0x%x) < R[%d](0x%x)) ? 1 : 0 = %d", _rd, _rs, signedRsData, _rt, signedRtData, signedRsData < signedRtData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

    return signedRsData < signedRtData;
}
