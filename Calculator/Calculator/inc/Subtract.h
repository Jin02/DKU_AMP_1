#pragma once

#include "RFormatInstruction.h"

class SubtractUnsigned : public RFormatInstruction
{
private:
    
public:
    SubtractUnsigned(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~SubtractUnsigned(void);
    
public:
    virtual unsigned int Instruct(unsigned int rs, unsigned int rt);
};

typedef SubtractUnsigned Subtract;