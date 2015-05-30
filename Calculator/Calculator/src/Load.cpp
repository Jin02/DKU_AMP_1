#include "Load.h"
#include "System.h"
#include "DumpLogManager.h"

/** LoadByteUnsigned **/

LoadByteUnsigned::LoadByteUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate), _toRegiMemValue(0)
{
	GlobalDumpManagerAddLogClassName(LoadByteUnsigned);
}

LoadByteUnsigned::~LoadByteUnsigned()
{

}

void LoadByteUnsigned::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);

    _executionResult = _rsData + _immediate;
	GlobalDumpManagerAddExecutionLog(_executionResult);
}

void LoadByteUnsigned::Memory(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
    System* system = System::GetInstance();
    unsigned int memData    = system->GetDataFromMemory(_executionResult);
    _toRegiMemValue = memData & 0x000000ff;
}

void LoadByteUnsigned::WriteBack()
{
    System* system = System::GetInstance();
    
    system->SetDataToRegister(_rt, _toRegiMemValue);
    {
        GlobalDumpLogManager->AddLog("R[rt] = {24'b0, M[R[rs] + SignExtImm](7:0)}", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "R[%d] = {0x000000, M[R[%d](0x%x) + 0x%x](7:0)} = 0x%x", _rt, _rs, _rsData, _immediate, _toRegiMemValue);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }
}

void LoadByteUnsigned::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outRdData, uint compareRegiIdx) const
{
    hasDependency   = (compareRegiIdx == _rt);
    outRdData       = _toRegiMemValue;
}

/** LoadHalfwordUnsigned **/
LoadHalfwordUnsigned::LoadHalfwordUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate), _toRegiMemValue(0)
{
	GlobalDumpManagerAddLogClassName(LoadHalfwordUnsigned);
}

LoadHalfwordUnsigned::~LoadHalfwordUnsigned()
{
    
}

void LoadHalfwordUnsigned::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{	
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);

    _executionResult = _rsData + _immediate;
	GlobalDumpManagerAddExecutionLog(_executionResult);
}

void LoadHalfwordUnsigned::Memory(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
    System* system = System::GetInstance();
    unsigned int memData    = system->GetDataFromMemory(_executionResult);
    _toRegiMemValue = memData & 0x0000ffff;
}

void LoadHalfwordUnsigned::WriteBack()
{
    System* system = System::GetInstance();
    system->SetDataToRegister(_rt, _toRegiMemValue);
    {
        GlobalDumpLogManager->AddLog("R[rt] = {16'b0, M[R[rs] + SignExtImm](15:0)}", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "R[%d] = {0x0000, M[R[%d](0x%x) + 0x%x](15:0)} = 0x%x", _rt, _rs, _rsData, _immediate, _toRegiMemValue);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }

}

void LoadHalfwordUnsigned::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outRdData, uint compareRegiIdx) const
{
    hasDependency   = (compareRegiIdx == _rt);
    outRdData       = _toRegiMemValue;
}

/** LoadLinked **/
LoadLinked::LoadLinked(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate), _toRegiMemValue(0)
{
    GlobalDumpManagerAddLogClassName(LoadLinked);
}

LoadLinked::~LoadLinked()
{
    
}

void LoadLinked::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);
	_executionResult = _rsData + _immediate;
	GlobalDumpManagerAddExecutionLog(_executionResult);
}

void LoadLinked::Memory(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
    System* system = System::GetInstance();
    _toRegiMemValue = system->GetDataFromMemory(_executionResult);
}

void LoadLinked::WriteBack()
{
    System* system = System::GetInstance();
    system->SetDataToRegister(_rt, _toRegiMemValue);
    {
        GlobalDumpLogManager->AddLog("R[rt] = M[R[rs] + SignExtImmm]", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "R[%d] = M[R[%d](0x%x) + 0x%x] = 0x%x", _rt, _rs, _rsData, _immediate, _toRegiMemValue);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }
}

void LoadLinked::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outRdData, uint compareRegiIdx) const
{
    hasDependency   = (compareRegiIdx == _rt);
    outRdData       = _toRegiMemValue;
}

/** LoadUpperImmediate **/
LoadUpperImmediate::LoadUpperImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(LoadUpperImmediate);
}

LoadUpperImmediate::~LoadUpperImmediate()
{
    
}

void LoadUpperImmediate::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
    _executionResult = _immediate & 0xffff0000;
	GlobalDumpManagerAddExecutionLog(_executionResult);
}

void LoadUpperImmediate::Memory(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
}

void LoadUpperImmediate::WriteBack()
{
    System* system = System::GetInstance();
    system->SetDataToRegister(_rt, _executionResult);
    {
        GlobalDumpLogManager->AddLog("R[rt] = {(immediate, 16b'0)}", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "R[%d] = 0x%x", _rt, _executionResult);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }
}

void LoadUpperImmediate::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outRdData, uint compareRegiIdx) const
{
    hasDependency   = (compareRegiIdx == _rt);
    outRdData       = _executionResult;
}


/** LoadWord **/
LoadWord::LoadWord(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate), _toRegiMemValue(0)
{
	GlobalDumpManagerAddLogClassName(LoadWord);
}

LoadWord::~LoadWord()
{
    
}

void LoadWord::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);
    _executionResult = _rsData + _immediate;
	GlobalDumpManagerAddExecutionLog(_executionResult);
}

void LoadWord::Memory(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
    System* system = System::GetInstance();
    _toRegiMemValue = system->GetDataFromMemory(_executionResult);
}

void LoadWord::WriteBack()
{
    System* system = System::GetInstance();
    system->SetDataToRegister(_rt, _toRegiMemValue);
    {
        GlobalDumpLogManager->AddLog("R[rt] = M[R[rs] + SignExtImmm]", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "R[%d] = M[R[%d](0x%x) + 0x%x] = 0x%x", _rt, _rs, _rsData, _immediate, _executionResult);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }
}

void LoadWord::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outRdData, uint compareRegiIdx) const
{
    hasDependency   = (compareRegiIdx == _rt);
    outRdData       = _toRegiMemValue;
}

/** LoadImmediate **/
LoadImmediate::LoadImmediate(unsigned int rd, unsigned int immediate)
    : Instruction(), _rd(rd), _immediate(immediate)
{
	GlobalDumpManagerAddLogClassName(LoadImmediate);
}

LoadImmediate::~LoadImmediate()
{
    
}

void LoadImmediate::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
    
}

void LoadImmediate::Memory(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
}

void LoadImmediate::WriteBack()
{
    System* system = System::GetInstance();
    system->SetDataToRegister(_rd, _immediate);
    {
        GlobalDumpLogManager->AddLog("R[rd] = immediate", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "R[%d] = 0x%x", _rd, _immediate);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }
}

void LoadImmediate::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outRdData, uint compareRegiIdx) const
{
    hasDependency   = (compareRegiIdx == _rd);
    outRdData       = _immediate;
}