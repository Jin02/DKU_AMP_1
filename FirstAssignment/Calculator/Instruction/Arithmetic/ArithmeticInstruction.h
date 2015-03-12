#pragma once

#include "Instruction.h"

namespace Instruction
{
	class ArithmeticInstruction : private Instruction
	{
	private:

	public:
		ArithmeticInstruction(void);
		virtual ~ArithmeticInstruction(void);

    protected:
        virtual unsigned int Instruct(unsigned int operand0_value, unsigned int operand1_value) = 0;
        
	public:
		virtual void Work();
	};
}