#pragma once

#include "RFormatInstruction.h"

class ShiftRightLogical : public RFormatInstruction
{
private:
    unsigned int _shamt;
    
public:
    ShiftRightLogical(unsigned int rs, unsigned int rt, unsigned int rd, unsigned int shamt);
    virtual ~ShiftRightLogical(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
};

typedef ShiftRightLogical Add;