#pragma once

#include "IFormatInstruction.h"

class SetLessThanImmediateUnsigned : public IFormatInstruction
{
private:
    
public:
    SetLessThanImmediateUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~SetLessThanImmediateUnsigned(void);
    
public:
    virtual void Execution();
};


class SetLessThanImmediate : public IFormatInstruction
{
private:
    
public:
    SetLessThanImmediate(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~SetLessThanImmediate(void);
    
public:
    virtual void Execution();
};