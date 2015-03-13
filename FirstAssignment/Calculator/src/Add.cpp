#include "Add.h"
#include "System.h"


Add::Add(const std::vector<Operand>& operands)
    : ArithmeticInstruction(operands)
{
}

Add::~Add(void)
{
}

unsigned int Add::Instruct(unsigned int operand0_value, unsigned int operand1_value)
{
    return operand0_value + operand1_value;
}