#pragma once

#include "Instruction.h"

class IFormatInstruction : public Instruction
{
protected:
    unsigned int    _rs, _rt;
    unsigned int    _immediate;
    
public:
    IFormatInstruction(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~IFormatInstruction(void);
};
