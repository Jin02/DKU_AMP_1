#include "Store.h"
#include "System.h"
#include "DumpLogManager.h"

/** StoreByte **/
StoreByte::StoreByte(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(StoreByte);
}

StoreByte::~StoreByte()
{
    
}

void StoreByte::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);

    _executionResult = _rsData + _immediate;
}

void StoreByte::Memory()
{
    System* system = System::GetInstance();
    
    uint toMemRtData    = _rtData & 0x000000ff;
    uint memData        = system->GetDataFromMemory(_rsData + _immediate);
    
    memData = (memData & 0xffffff00) | (toMemRtData);
    system->SetDataToMemory(_executionResult, memData);
    {
        GlobalDumpLogManager->AddLog("M[R[rs] + SignExtImm](7:0) = R[rt](7:0)", true);
        
        char buff[256] = {0, };
        sprintf(buff, "M[(R[%d](0x%x) + 0x%x) = 0x%x](7:0) = R[%d](0x%x)(7:0)", _rs, _rsData, _immediate, _executionResult, _rt, toMemRtData);
        
        GlobalDumpLogManager->AddLog(buff, true);
    }
}

void StoreByte::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outRdData, uint compareRegiIdx) const
{
	hasDependency = false;
}

/** StoreConditional **/

StoreConditional::StoreConditional(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    GlobalDumpManagerAddLogClassName(StoreConditional);
}

StoreConditional::~StoreConditional()
{
    
}

void StoreConditional::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);

    _executionResult = _rsData + _immediate;
}

void StoreConditional::Memory()
{
    System* system = System::GetInstance();
    
    system->SetDataToMemory(_executionResult, _rtData);
    {
        GlobalDumpLogManager->AddLog("M[R[rs] + SignExtImm] = R[rt]", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "M[(R[%d](0x%x) + 0x%x) = 0x%x] = R[%d](0x%x)", _rs, _rsData, _immediate, _executionResult, _rt, _rtData);
        GlobalDumpLogManager->AddLog(logBuffer, true);
    }
}

void StoreConditional::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outRdData, uint compareRegiIdx) const
{
	hasDependency = false;
}

/** StoreUpperImmediate **/

StoreHalfword::StoreHalfword(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(StoreHalfword);
}

StoreHalfword::~StoreHalfword()
{
    
}

void StoreHalfword::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);

    _executionResult = _rsData + _immediate;
}

void StoreHalfword::Memory()
{
    System* system = System::GetInstance();
    
    unsigned int toMemRtData = _rtData & 0x0000ffff;
    unsigned int rsData = _rsData;
    unsigned int memData = system->GetDataFromMemory(rsData + _immediate);
    
    memData = (memData & 0xffff0000) | (toMemRtData);
    system->SetDataToMemory(_executionResult, memData);
    {
        GlobalDumpLogManager->AddLog("M[R[rs] + SignExtImm](15:0) = R[rt](15:0)", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "M[(R[%d](0x%x) + 0x%x) = 0x%x](15:0) = R[%d](0x%x)(15:0)", _rs, rsData, _immediate, _executionResult, _rt, toMemRtData);
        GlobalDumpLogManager->AddLog(logBuffer, true);
    }
}

void StoreHalfword::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outRdData, uint compareRegiIdx) const
{
	hasDependency = false;
}


/** StoreWord **/

StoreWord::StoreWord(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
	GlobalDumpManagerAddLogClassName(StoreWord);
}

StoreWord::~StoreWord()
{
    
}

void StoreWord::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
{
	Forwarding(prev2stepInst, prev1stepInst, _rsData, _rs);

    _executionResult = _rsData + _immediate;
}

void StoreWord::Memory()
{
    System* system = System::GetInstance();
    
    unsigned int toMemRtData = _rtData;
    unsigned int rsData = _rsData;
    system->SetDataToMemory(_executionResult, toMemRtData);
    {
        GlobalDumpLogManager->AddLog("M[R[rs] + SignExtImm] = R[rt]", true);
        
        char logBuffer[64] = {0, };
        sprintf(logBuffer, "M[(R[%d](0x%x) + 0x%x) = 0x%x] = R[%d](0x%x)", _rs, rsData, _immediate, _executionResult, _rt, toMemRtData);
        GlobalDumpLogManager->AddLog(logBuffer, true);
        GlobalDumpManagerAddLog3NewLine;
    }
}

void StoreWord::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outRdData, uint compareRegiIdx) const
{
	hasDependency = false;
}
