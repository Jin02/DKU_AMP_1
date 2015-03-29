#include "Subtract.h"
#include "System.h"
#include "DumpLogManager.h"

SubtractUnsigned::SubtractUnsigned(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName;
}

SubtractUnsigned::~SubtractUnsigned(void)
{
    
}

unsigned int SubtractUnsigned::Instruct(unsigned int rsData, unsigned int rtData)
{
	{
		GlobalDumpLogManager->AddLog("R[rd] = R[rs] - R[rt]", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = R[%d](0x%x) - R[%d](0x%x) = 0x%x", _rd, _rs, rsData, _rt, rtData, rsData - rtData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

    return rsData - rtData;
}

Subtract::Subtract(unsigned int rs, unsigned int rt, unsigned int rd) : SubtractUnsigned(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName;
}

Subtract::~Subtract()
{
}