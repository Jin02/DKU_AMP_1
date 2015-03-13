#include "Div.h"
#include "System.h"

Div::Div(const std::vector<const Operand>& operands)
    : ArithmeticInstruction(operands)
{
}

Div::~Div(void)
{
}

unsigned int Div::Instruct(unsigned int operand0_value, unsigned int operand1_value)
{
    return operand0_value / operand1_value;
}