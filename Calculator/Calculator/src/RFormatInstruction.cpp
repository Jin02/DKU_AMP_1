#include "RFormatInstruction.h"
#include "System.h"
#include <string>
#include "DumpLogManager.h"

RFormatInstruction::RFormatInstruction(unsigned int rs, unsigned int rt, unsigned int rd) 
	: Instruction(), _rd(rd)
{
	System* system = System::GetInstance();

	_rsData = system->GetDataFromRegister(rs);
    _rtData = system->GetDataFromRegister(rt);

	char buff[256] = {0, };
	sprintf(buff, "R Type\t\t| rsData = 0x%x = register[rs=0x%x]  / rtData = 0x%x = register[rt=0x%x]", _rsData, rs, _rtData, rt);
	GlobalDumpLogManager->AddLog(buff, true);
}

RFormatInstruction::~RFormatInstruction(void)
{
}

void RFormatInstruction::Execution(const ForwardingFuncType& prev2stepInst, const ForwardingFuncType& prev1stepInst)
{
	_executionResult = Instruct(_rsData, _rtData);
	GlobalDumpManagerAddExecutionLog(_executionResult);
}

void RFormatInstruction::Memory()
{
	//null
}

void RFormatInstruction::WriteBack()
{
	System* system = System::GetInstance();
	system->SetDataToRegister(_rd, _executionResult);
	{
		char buff[256] = {0, };	
		sprintf(buff, "R[rd=0x%x] = 0x%x", _rd, _executionResult);
		GlobalDumpLogManager->AddLog(buff, true);
	}
}

void RFormatInstruction::Forwarding(bool& hasDependency, uint& outRdData, uint compareRegiIdx) const
{
    hasDependency   = (compareRegiIdx == _rd);
    outRdData       = _executionResult;
}