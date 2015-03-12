#pragma once

#include "ArithmeticInstruction.h"

namespace Instruction
{
	namespace Arithmetic
	{
		class Sub : public ArithmeticInstruction
		{
		private:


		public:
            Sub(void);
            virtual ~Sub(void);

        public:
            virtual unsigned int Instruct(unsigned int operand0_value, unsigned int operand1_value);
        };
	}
}