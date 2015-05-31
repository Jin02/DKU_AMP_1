#include "ShiftRightLogical.h"
#include "System.h"
#include "DumpLogManager.h"

ShiftRightLogical::ShiftRightLogical(unsigned int rs, unsigned int rt, unsigned int rd, unsigned int shamt)
    : RFormatInstruction(rs, rt, rd), _shamt(shamt)
{
	GlobalDumpManagerAddLogClassName(ShiftRightLogical);
}

ShiftRightLogical::~ShiftRightLogical(void)
{
    
}

unsigned int ShiftRightLogical::Instruct(unsigned int rsData, unsigned int rtData)
{
    std::string equ = "R[rs] >> R[rt]";
    char buff[256] = {0, };
    sprintf(buff, "ExecutionResult = 0x%x / ExecutionResult = ", rsData + rtData);
    GlobalDumpLogManager->AddLog(buff+equ, true);
    
    return rtData >> _shamt;
}