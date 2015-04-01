#include "Multiply.h"
#include "System.h"
#include "DumpLogManager.h"

/** Multiply32BitRes **/

Multiply32BitRes::Multiply32BitRes(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(Multiply32BitRes);
}

Multiply32BitRes::~Multiply32BitRes(void)
{

}

unsigned int Multiply32BitRes::Instruct(unsigned int rsData, unsigned int rtData)
{
	{
		GlobalDumpLogManager->AddLog("R[rd] = R[rs] * R[rt]", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = R[%d](0x%x) * R[%d](0x%x) = 0x%x", _rd, _rs, rsData, _rt, rtData,rsData + rtData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

    return rsData * rtData;
}

/** Multiply **/

Multiply::Multiply(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(Multiply);
}

Multiply::~Multiply(void)
{

}

unsigned int Multiply::Instruct(unsigned int rsData, unsigned int rtData)
{
	return 0;
}

bool Multiply::Execution()
{
	System* system = System::GetInstance();

	int rsData = system->GetDataFromRegister(_rs);
	int rtData = system->GetDataFromRegister(_rt);

	long long result = rsData * rtData;
	system->SetHiRegister( (result & 0xffffffff00000000) >> 32 );
	system->SetLoRegister( (result & 0x00000000ffffffff) );

	{
		GlobalDumpLogManager->AddLog("Hi = (R[rs] * R[rt])(63:32); Lo = (R[rs] * R[rt])(31:0)", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "Hi = {R[%d](0x%x) * R[%d](0x%x)}(63:32) = 0x%x; // Lo = {R[%d](0x%x) * R[%d](0x%x)}(31:0) = 0x%x", _rs, rsData, _rt, rtData, (uint)((result & 0xffffffff00000000) >> 32), _rs, rsData, _rt, rtData, (uint)(result & 0x00000000ffffffff));
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}

/** Multiply Unsigned **/

MultiplyUnsigned::MultiplyUnsigned(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(MultiplyUnsigned);
}

MultiplyUnsigned::~MultiplyUnsigned(void)
{

}

unsigned int MultiplyUnsigned::Instruct(unsigned int rsData, unsigned int rtData)
{
    return 0;
}

bool MultiplyUnsigned::Execution()
{
	System* system = System::GetInstance();

	uint rsData = system->GetDataFromRegister(_rs);
	uint rtData = system->GetDataFromRegister(_rt);

	unsigned long long result = rsData * rtData;
	system->SetHiRegister( (result & 0xffffffff00000000) >> 32 );
	system->SetLoRegister(result & 0x00000000ffffffff);
	{
		GlobalDumpLogManager->AddLog("Hi = (R[rs] * R[rt])(63:32); Lo = (R[rs] * R[rt])(31:0)", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "Hi = {R[%d](0x%x) * R[%d](0x%x)}(63:32) = 0x%x; // Lo = {R[%d](0x%x) * R[%d](0x%x)}(31:0) = 0x%x", _rs, rsData, _rt, rtData, (uint)((result & 0xffffffff00000000) >> 32), _rs, rsData, _rt, rtData, (uint)(result & 0x00000000ffffffff));
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}