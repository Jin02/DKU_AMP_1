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
	{
		GlobalDumpLogManager->AddLog("R[rd] = R[rs] & R[rt]", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = R[%d](0x%x) & R[%d](0x%x) = 0x%x", _rd, _rs, rsData, _rt, rtData, rsData & rtData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

    return rsData & rtData;
}