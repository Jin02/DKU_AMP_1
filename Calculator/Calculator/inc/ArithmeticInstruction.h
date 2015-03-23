#pragma once

#include "Instruction.h"

class ArithmeticInstruction : public Instruction
{
public:
    ArithmeticInstruction(const std::vector<Operand>& operands);
    virtual ~ArithmeticInstruction(void);
    
protected:
    virtual int Instruct(const Operand& rs, const Operand& rt) = 0;
    
public:
    virtual void Work();
};
