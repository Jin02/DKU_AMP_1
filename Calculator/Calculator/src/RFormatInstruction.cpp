#include "RFormatInstruction.h"
#include "System.h"
#include <string>
#include "DumpLogManager.h"

RFormatInstruction::RFormatInstruction(unsigned int rs, unsigned int rt, unsigned int rd) 
	: Instruction(), _rd(rd), _rs(rs), _rt(rt)
{
	System* system = System::GetInstance();

	_rsData = system->GetDataFromRegister(rs);
    _rtData = system->GetDataFromRegister(rt);

	char buff[256] = {0, };
	sprintf(buff, "R Type\t\t\t| rsData = 0x%x = register[rs=0x%x]  / rtData = 0x%x = register[rt=0x%x]", _rsData, rs, _rtData, rt);
	GlobalDumpLogManager->AddLog(buff, true);
}

RFormatInstruction::~RFormatInstruction(void)
{
}

void RFormatInstruction::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);
	Forwarding(prev2stepInst, prev1stepInst, _rtData, _rt);

	_executionResult = Instruct(_rsData, _rtData);
}

void RFormatInstruction::Memory(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
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

void RFormatInstruction::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outRdData, uint compareRegiIdx) const
{
    hasDependency   = (compareRegiIdx == _rd);
    outRdData       = _executionResult;
}