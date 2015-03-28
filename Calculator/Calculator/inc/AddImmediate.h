#pragma once

#include "IFormatInstruction.h"

class AddImmediateUnsigned : public IFormatInstruction
{
private:
    
public:
    AddImmediateUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~AddImmediateUnsigned(void);
    
public:
    virtual bool Execution();
};

typedef AddImmediateUnsigned AddImmediate;