#pragma once

#include "Instruction.h"

class TransmitInstruction : public Instruction
{
private:
    
public:
    TransmitInstruction(const std::vector<Operand>& operands);
    virtual ~TransmitInstruction(void);
    
protected:
    virtual void Instruct(const Operand& operand0, const Operand& operand1) = 0;
    
public:
    virtual void Work();
};