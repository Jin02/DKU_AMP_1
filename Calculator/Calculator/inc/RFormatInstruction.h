#pragma once

#include "Instruction.h"


class RFormatInstruction : public Instruction
{
protected:
    unsigned int _rs, _rt, _rd;
    
public:
    RFormatInstruction(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~RFormatInstruction(void);
    
protected:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData) = 0;
    
public:
    virtual bool Execution();
};
