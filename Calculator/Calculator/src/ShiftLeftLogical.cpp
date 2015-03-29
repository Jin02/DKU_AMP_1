#include "ShiftLeftLogical.h"
#include "System.h"
#include "DumpLogManager.h"

ShiftLeftLogical::ShiftLeftLogical(unsigned int rs, unsigned int rt, unsigned int rd, unsigned int shamt)
    : RFormatInstruction(rs, rt, rd), _shamt(shamt)
{
	GlobalDumpManagerAddLogClassName;
}

ShiftLeftLogical::~ShiftLeftLogical(void)
{
    
}

unsigned int ShiftLeftLogical::Instruct(unsigned int rsData, unsigned int rtData)
{
	{
		GlobalDumpLogManager->AddLog("R[rd] = R[rt] << shamt", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = R[%d](0x%x) << shamt(0x%x) = 0x%x", _rd, _rt, rtData, _shamt, rtData << _shamt);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

    return rtData << _shamt;
}