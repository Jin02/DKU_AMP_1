#pragma once

#include "RFormatInstruction.h"

class AddUnsigned : public RFormatInstruction
{
private:
    
public:
    AddUnsigned(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~AddUnsigned(void);
    
public:
    virtual unsigned int Instruct(unsigned int rs, unsigned int rt);
};

typedef AddUnsigned Add;