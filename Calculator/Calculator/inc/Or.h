#pragma once

#include "RFormatInstruction.h"



class Or : public RFormatInstruction
{
private:
    
public:
    Or(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~Or(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
};



class Nor : public RFormatInstruction
{
private:
    
public:
    Nor(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~Nor(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
};