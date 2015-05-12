#pragma once

#include "IFormatInstruction.h"

class OrImmediate : public IFormatInstruction
{
private:
    
public:
    OrImmediate(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~OrImmediate(void);
    
public:
    virtual void Execution();
};