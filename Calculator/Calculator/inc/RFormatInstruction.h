#pragma once

#include "Instruction.h"


class RFormatInstruction : public Instruction
{
protected:
    uint _rsData, _rtData, _rd;
	uint _executionResult;
    
public:
    RFormatInstruction(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~RFormatInstruction(void);
    
protected:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData) = 0;
    
public:
    virtual void Execution();
	virtual void Memory();
	virtual void WriteBuffer();
};
