#pragma once

#include "ArithmeticInstruction.h"

class Sub : public ArithmeticInstruction
{
private:
    
    
public:
    Sub(const std::vector<Operand>& operands);
    virtual ~Sub(void);
    
public:
    virtual int Instruct(int operand0_value, int operand1_value);

#ifdef USE_OUTPUT_DUMP_LOG
    virtual char GetDumpLogSymbol() { return '-'; }
#endif
    
};