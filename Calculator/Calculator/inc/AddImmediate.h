#pragma once

#include "IFormatInstruction.h"

class AddImmediateUnsigned : public IFormatInstruction
{
private:
    
public:
    AddImmediateUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~AddImmediateUnsigned(void);
    
public:
    virtual void Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst);
};

class AddImmediate : public AddImmediateUnsigned
{
public:
	AddImmediate(unsigned int rs, unsigned int rt, unsigned int immediate);
	virtual ~AddImmediate();
};