#include "Sub.h"
#include "System.h"

Sub::Sub(const std::vector<Operand>& operands)
    : ArithmeticInstruction(operands)
{

}

Sub::~Sub(void)
{
}

int Sub::Instruct(int operand0_value, int operand1_value)
{
    return operand0_value - operand1_value;
}