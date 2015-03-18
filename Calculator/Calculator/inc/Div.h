#pragma once

#include "ArithmeticInstruction.h"

class Div : public ArithmeticInstruction
{
private:
    
    
public:
    Div(const std::vector<Operand>& operands);
    virtual ~Div(void);
    
public:
    virtual int Instruct(int operand0_value, int operand1_value);

#ifdef USE_OUTPUT_DUMP_LOG
    virtual char GetDumpLogSymbol() { return '/'; }
#endif
    
};
