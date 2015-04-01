#include "Or.h"
#include "System.h"
#include "DumpLogManager.h"

/** Or **/

Or::Or(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(Or);
}

Or::~Or(void)
{
    
}

unsigned int Or::Instruct(unsigned int rsData, unsigned int rtData)
{
	{
		GlobalDumpLogManager->AddLog("R[rd] = R[rs] | R[rt]", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = R[%d](0x%x) | R[%d](0x%x) = 0x%x", _rd, _rs, rsData, _rt, rtData, rsData | rtData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

    return rsData | rtData;
}

/** Nor **/

Nor::Nor(unsigned int rs, unsigned int rt, unsigned int rd)
: RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(Nor);
}

Nor::~Nor(void)
{
    
}

unsigned int Nor::Instruct(unsigned int rsData, unsigned int rtData)
{
	{
		GlobalDumpLogManager->AddLog("R[rd] = ~(R[rs] | R[rt])", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = ~(R[%d](0x%x) | R[%d](0x%x)) = 0x%x", _rd, _rs, rsData, _rt, rtData, ~(rsData | rtData));
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

    return ~(rsData | rtData);
}