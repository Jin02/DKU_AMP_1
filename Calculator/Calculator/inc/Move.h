#pragma once

#include "TransmitInstruction.h"

class Move : public TransmitInstruction
{
private:
    
    
public:
    Move(const std::vector<Operand>& operands);
    ~Move(void);
    
protected:
    virtual void Instruct(const Operand& operand0, const Operand& operand1);
};