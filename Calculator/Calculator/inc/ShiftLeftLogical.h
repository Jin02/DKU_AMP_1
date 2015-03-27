#pragma once

#include "RFormatInstruction.h"

class ShiftLeftLogical : public RFormatInstruction
{
private:
    unsigned int    _shamt;
    
public:
    ShiftLeftLogical(unsigned int rs, unsigned int rt, unsigned int rd, unsigned int shamt);
    virtual ~ShiftLeftLogical(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
};