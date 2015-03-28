#pragma once

#include "Instruction.h"

class Move : public Instruction
{
private:
    unsigned int _rs, _rd;
    
public:
    Move(unsigned int rs, unsigned int rd);
    virtual ~Move(void);
    
public:
    virtual bool Execution();
};