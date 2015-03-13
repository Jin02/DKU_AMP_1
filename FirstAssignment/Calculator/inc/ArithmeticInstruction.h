#pragma once

#include "Instruction.h"

class ArithmeticInstruction : public Instruction
{
private:
    
public:
    ArithmeticInstruction(const std::vector<Operand>& operands);
    virtual ~ArithmeticInstruction(void);
    
protected:
    virtual unsigned int Instruct(unsigned int operand0_value, unsigned int operand1_value) = 0;
    
public:
    virtual void Work();
    
#ifdef USE_OUTPUT_DUMP_LOG
    virtual char GetDumpLogSymbol() = 0;
#endif
};
