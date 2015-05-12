#pragma once

#include "RFormatInstruction.h"

class JumpRegister : public RFormatInstruction
{
private:
    
public:
    JumpRegister(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~JumpRegister(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
};