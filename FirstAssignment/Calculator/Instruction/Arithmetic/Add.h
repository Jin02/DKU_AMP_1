#pragma once

#include "ArithmeticInstruction.h"

namespace Instruction
{
	namespace Arithmetic
	{
		class Add : public ArithmeticInstruction
		{
		private:


		public:
			Add(void);
			virtual ~Add(void);

		public:
            virtual unsigned int Instruct(unsigned int operand0_value, unsigned int operand1_value);
		};
	}
}