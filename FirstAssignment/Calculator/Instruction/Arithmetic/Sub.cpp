#include "Sub.h"
#include "System.h"

Sub::Sub(const std::vector<const Operand>& operands)
    : ArithmeticInstruction(operands)
{

}

Sub::~Sub(void)
{
}

unsigned int Sub::Instruct(unsigned int operand0_value, unsigned int operand1_value)
{
    return operand0_value - operand1_value;
}