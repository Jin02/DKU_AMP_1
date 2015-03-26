#pragma once

#include "Instruction.h"

class IFormatInstruction : public Instruction
{
private:
    unsigned int    _rs, _rt;
    unsigned int    _immediate;
    
public:
    IFormatInstruction(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~IFormatInstruction(void);
    
protected:
    virtual unsigned int Instruct(unsigned int rs, unsigned int rt, unsigned int immediate) = 0;
    
public:
    virtual void Execution();
};
