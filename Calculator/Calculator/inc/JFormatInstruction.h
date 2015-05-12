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
    virtual void Forwarding(bool&, uint&, uint ) const;
};

class Jump : public JFormatInstruction
{
public:
    Jump(unsigned int address);
    ~Jump();
};

class JumpAndLink : public JFormatInstruction
{
public:
    JumpAndLink(unsigned int address);
    ~JumpAndLink();
};
