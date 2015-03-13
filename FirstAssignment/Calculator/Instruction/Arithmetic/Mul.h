#pragma once

#include "ArithmeticInstruction.h"

class Mul : public ArithmeticInstruction
{
private:
    
    
public:
    Mul(const std::vector<const Operand>& operands);
    virtual ~Mul(void);
    
public:
    virtual unsigned int Instruct(unsigned int operand0_value, unsigned int operand1_value);

#ifdef USE_OUTPUT_DUMP_LOG
    virtual char GetDumpLogSymbol() { return '*'; }
#endif
    
};
