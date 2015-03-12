#pragma once

#include "ArithmeticInstruction.h"

namespace Instruction
{
	namespace Arithmetic
	{
		class Mul : public ArithmeticInstruction
		{
		private:


		public:
            Mul(void);
            virtual ~Mul(void);

        public:
            virtual unsigned int Instruct(unsigned int operand0_value, unsigned int operand1_value);
		};
	}
}