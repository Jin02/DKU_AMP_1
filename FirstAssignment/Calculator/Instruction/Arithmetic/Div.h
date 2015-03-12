#pragma once

#include "ArithmeticInstruction.h"

namespace Instruction
{
	namespace Arithmetic
	{
		class Div : public ArithmeticInstruction
		{
		private:


		public:
            Div(void);
            virtual ~Div(void);

        public:
            virtual unsigned int Instruct(unsigned int operand0_value, unsigned int operand1_value);
		};
	}
}