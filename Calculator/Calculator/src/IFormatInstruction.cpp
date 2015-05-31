#include "IFormatInstruction.h"
#include "System.h"
#include <string>
#include "DumpLogManager.h"

IFormatInstruction::IFormatInstruction(unsigned int rs, unsigned int rt, unsigned int immediate) 
	: Instruction(), _immediate(immediate), _rt(rt), _rs(rs)
{
	System* system = System::GetInstance();

	_rsData = system->GetDataFromRegister(rs);
    _rtData = system->GetDataFromRegister(rt);

	char buff[256] = {0, };
	sprintf(buff, "I Type\t\t| rsData = 0x%x = register[rs=0x%x]  / rt = 0x%x / immediate = 0x%x", _rsData, rs, rt, immediate);
	GlobalDumpLogManager->AddLog(buff, true);
}

IFormatInstruction::~IFormatInstruction(void)
{
}

void IFormatInstruction::WriteBack()
{
	System* system = System::GetInstance();
	system->SetDataToRegister(_rt, _executionResult);
	{
		char buff[256] = {0, };	
		sprintf(buff, "R[rt=0x%x] = 0x%x / ExecutionResult ", _rt, _executionResult);
		GlobalDumpLogManager->AddLog(buff, true);
	}
}

void IFormatInstruction::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outRdData, uint compareRegiIdx) const
{
    hasDependency   = (compareRegiIdx == _rt);
    outRdData       = _executionResult;
}