#pragma once

#include "ArithmeticInstruction.h"

class Add : public ArithmeticInstruction
{
private:
    
    
public:
    Add(const std::vector<Operand>& operands);
    virtual ~Add(void);
    
public:
    virtual unsigned int Instruct(unsigned int operand0_value, unsigned int operand1_value);
    
#ifdef USE_OUTPUT_DUMP_LOG
    virtual char GetDumpLogSymbol() { return '+'; }
#endif
};
