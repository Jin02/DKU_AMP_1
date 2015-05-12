#pragma once

#include "Instruction.h"


class RFormatInstruction : public Instruction
{
protected:
    uint _rsData, _rtData, _rd, _rs, _rt;
	uint _executionResult;
    
public:
    RFormatInstruction(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~RFormatInstruction(void);
    
protected:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData) = 0;
    
public:
    virtual void DependencyCheckWithGetTargetData(bool& hasDependency, uint& outTargetData, uint compareRegiIdx) const;

public:
    virtual void Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst);
	virtual void Memory();
	virtual void WriteBack();
};
