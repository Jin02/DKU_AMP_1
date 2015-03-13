#pragma once

#include <vector>
#include "Operand.h"

class Instruction
{
public:
    Instruction(const std::vector<Operand>& operands);
    virtual ~Instruction(void);
    
protected:
    unsigned int GetData(const Operand& operand);
    
public:
    virtual void Work() = 0;
    
protected:
    std::vector<Operand>      _operands;
};
