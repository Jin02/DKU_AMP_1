#pragma once

#include "Instruction.h"

class IFormatInstruction : public Instruction
{
protected:
    uint    _rs, _rsData, _rt, _rtData, _immediate;
	uint	_executionResult;
    
public:
    IFormatInstruction(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~IFormatInstruction(void);

public:
	virtual void WriteBack();	
	virtual void Memory(const Instruction* prev2stepInst, const Instruction* prev1stepInst){}
    
    virtual void DependencyCheckWithGetTargetData(bool& hasDependency, uint& outTargetData, uint compareRegiIdx) const;    
};
