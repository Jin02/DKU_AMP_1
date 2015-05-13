#include "BranchOnEqual.h"
#include "System.h"
#include "DumpLogManager.h"

BranchOnEqual::BranchOnEqual(unsigned int rs, unsigned int rt, unsigned int immediate)
	: IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(BranchOnEqual);
    _type = Type::Branch;
}

BranchOnEqual::~BranchOnEqual()
{

}

void BranchOnEqual::DependencyCheckWithGetTargetData(bool&, uint&, uint ) const
{
    
}

void BranchOnEqual::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
    System* system = System::GetInstance();
    uint pc = system->GetProgramCounter();

	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);
	Forwarding(prev2stepInst, prev1stepInst, _rtData, _rt);

    GlobalDumpLogManager->AddLog("if(R[rs] == R[rt])\tPC = PC + 4 + BranchAddr", true);
    {
        char logBuffer[128] = {0, };
        sprintf(logBuffer, "if(R[%d](0x%x) == R[%d](0x%x))\tPC = {0x%x + 4 + 0x%x}(0x%x)", _rs, _rsData, _rt, _rtData, pc, _immediate, pc + 4 + _immediate);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }
    
    if(_rsData == _rtData)
    {
        _isBranchSuccess = true;
        system->SetProgramCounter(pc + 4 + _immediate);
    }
}