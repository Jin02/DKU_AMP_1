#pragma once

#include "ArithmeticInstruction.h"

class Mul : public ArithmeticInstruction
{
private:
    
    
public:
    Mul(const std::vector<Operand>& operands);
    virtual ~Mul(void);
    
public:
    virtual int Instruct(int operand0_value, int operand1_value);

#ifdef USE_OUTPUT_DUMP_LOG
    virtual char GetDumpLogSymbol() { return '*'; }
#endif
    
};
