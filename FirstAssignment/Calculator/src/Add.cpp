#include "Add.h"
#include "System.h"


Add::Add(const std::vector<Operand>& operands)
    : ArithmeticInstruction(operands)
{
}

Add::~Add(void)
{
}

int Add::Instruct(int operand0_value, int operand1_value)
{
    return operand0_value + operand1_value;
}