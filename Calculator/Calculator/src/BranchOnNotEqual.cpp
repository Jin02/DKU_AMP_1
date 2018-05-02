#include "BranchOnNotEqual.h"
#include "System.h"
#include "DumpLogManager.h"

BranchOnNotEqual::BranchOnNotEqual(unsigned int rs, unsigned int rt, unsigned int immediate) 
	: BranchBase(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(BranchOnNotEqual);
}

BranchOnNotEqual::~BranchOnNotEqual()
{

}

void BranchOnNotEqual::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
    System* system = System::GetInstance();
    
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);
	Forwarding(prev2stepInst, prev1stepInst, _rtData, _rt);
    
    GlobalDumpLogManager->AddLog("if(R[rs] != R[rt])\t\tPC = PC + 4 + BranchAddr", true);
    {
        char logBuffer[128] = {0, };
        sprintf(logBuffer, "if(R[%d](0x%x) != R[%d](0x%x))\t\tPC = {0x%x + 4 + 0x%x}(0x%x)", _rs, _rsData, _rt, _rtData, _pc, _immediate, _pc + 4 + _immediate);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }
    
    if(_rsData != _rtData)
    {
        _isBranchSuccess = true;
        system->SetProgramCounter(_pc + 4 + _immediate);
    }
}