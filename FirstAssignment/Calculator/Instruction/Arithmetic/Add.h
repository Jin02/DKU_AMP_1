#pragma once

#include "Instruction.h"

namespace Instruction
{
	namespace Arithmetic
	{
		class Add : public Instruction
		{
		private:


		public:
			Add(void);
			~Add(void);

		public:
			virtual void Work();
		};
	}
}