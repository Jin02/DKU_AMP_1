#include "JumpRegister.h"
#include "System.h"
#include "DumpLogManager.h"

JumpRegister::JumpRegister(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(JumpRegister);
    _type = Type::Jump;
}

JumpRegister::~JumpRegister(void)
{
    
}

unsigned int JumpRegister::Instruct(unsigned int rsData, unsigned int rtData)
{
    return 0;
}

void JumpRegister::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outTargetData, uint compareRegiIdx) const
{
    hasDependency = false;
    outTargetData = -1;
}

void JumpRegister::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
    System* system = System::GetInstance();
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);

	system->SetProgramCounter(_rsData);
    {
        GlobalDumpLogManager->AddLog("PC = R[rs]", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "PC = R[%d](0x%x)", _rs, _rsData);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }
}

void JumpRegister::WriteBack()
{

}