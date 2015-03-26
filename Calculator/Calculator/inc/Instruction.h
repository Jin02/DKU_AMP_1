#pragma once

#include <vector>

class Instruction
{
public:
    Instruction();
    virtual ~Instruction(void);
    
public:
    virtual void Execution() = 0;
};
