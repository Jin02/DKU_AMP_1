#pragma once

#include "IFormatInstruction.h"

class AddImmediateUnsigned : public IFormatInstruction
{
private:
    
public:
    AddImmediateUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~AddImmediateUnsigned(void);
    
public:
    virtual void Instruct(unsigned int rs, unsigned int rt, unsigned int immediate);
};

typedef AddImmediateUnsigned AddImmediate;