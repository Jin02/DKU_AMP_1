#pragma once

#include "Instruction.h"

class JFormatInstruction : public Instruction
{
protected:
    unsigned int _address;
    
public:
    JFormatInstruction(unsigned int address);
    virtual ~JFormatInstruction(void);
    
public:
    virtual bool Execution() = 0;
};

class Jump : public JFormatInstruction
{
public:
    Jump(unsigned int address);
    ~Jump();
    
public:
    virtual bool Execution();
};

class JumpAndLink : public JFormatInstruction
{
public:
    JumpAndLink(unsigned int address);
    ~JumpAndLink();
    
public:
    virtual bool Execution();
};
