#include "Mul.h"
#include "System.h"

Mul::Mul(const std::vector<Operand>& operands)
    : ArithmeticInstruction(operands)
{
}

Mul::~Mul(void)
{
}

int Mul::Instruct(int operand0_value, int operand1_value)
{
    return operand0_value * operand1_value;
}