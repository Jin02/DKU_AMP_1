#pragma once

#include "IFormatInstruction.h"

class AndImmediate : public IFormatInstruction
{
private:
    
public:
    AndImmediate(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~AndImmediate(void);
    
public:
    virtual void Execution(const ForwardingFuncType& prev2stepInst, const ForwardingFuncType& prev1stepInst);
};