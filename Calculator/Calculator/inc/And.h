#pragma once

#include "RFormatInstruction.h"

class And : public RFormatInstruction
{
private:
    
public:
    And(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~And(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
};