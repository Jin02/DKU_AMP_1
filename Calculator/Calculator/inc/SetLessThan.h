#pragma once

#include "RFormatInstruction.h"

class SetLessThanUnsigned : public RFormatInstruction
{
private:
    
public:
    SetLessThanUnsigned(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~SetLessThanUnsigned(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
};


class SetLessThan : public RFormatInstruction
{
private:
    
public:
    SetLessThan(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~SetLessThan(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
};
