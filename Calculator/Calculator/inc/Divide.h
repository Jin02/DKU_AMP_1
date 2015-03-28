#pragma once

#include "RFormatInstruction.h"

class Divide : public RFormatInstruction
{
private:
    
public:
    Divide(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~Divide(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
    virtual bool Execution();
};



class DivideUnsigned : public RFormatInstruction
{
private:
    
public:
    DivideUnsigned(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~DivideUnsigned(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
    virtual bool Execution();
};