#pragma once

#include "ArithmeticInstruction.h"

class Div : public ArithmeticInstruction
{
private:
    
    
public:
    Div(const std::vector<Operand>& operands);
    virtual ~Div(void);
    
public:
    virtual unsigned int Instruct(unsigned int operand0_value, unsigned int operand1_value);

#ifdef USE_OUTPUT_DUMP_LOG
    virtual char GetDumpLogSymbol() { return '/'; }
#endif
    
};
