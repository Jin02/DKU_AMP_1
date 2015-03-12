#include "Div.h"
#include "System.h"

using namespace Instruction::Arithmetic;

Div::Div(void)
{
}

Div::~Div(void)
{
}

unsigned int Div::Instruct(unsigned int operand0_value, unsigned int operand1_value)
{
    return operand0_value / operand1_value;
}