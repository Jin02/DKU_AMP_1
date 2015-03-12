#include "Add.h"
#include "System.h"

using namespace Instruction::Arithmetic;

Add::Add(void)
{
}

Add::~Add(void)
{
}

unsigned int Add::Instruct(unsigned int operand0_value, unsigned int operand1_value)
{
    return operand0_value + operand1_value;
}