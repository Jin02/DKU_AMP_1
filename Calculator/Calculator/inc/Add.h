#pragma once

#include "ArithmeticInstruction.h"

class Add : public ArithmeticInstruction
{
private:
    
    
public:
    Add(const std::vector<Operand>& operands);
    virtual ~Add(void);
    
public:
    virtual int Instruct(int operand0_value, int operand1_value);
    
#ifdef USE_OUTPUT_DUMP_LOG
    virtual char GetDumpLogSymbol() { return '+'; }
#endif
};
