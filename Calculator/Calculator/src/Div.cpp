#include "Div.h"
#include "System.h"

Div::Div(const std::vector<Operand>& operands)
    : ArithmeticInstruction(operands)
{
}

Div::~Div(void)
{
}

int Div::Instruct(int operand0_value, int operand1_value)
{
    return operand0_value / operand1_value;
}