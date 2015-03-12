#pragma once

#include "Instruction.h"

namespace Instruction
{
	namespace Transmit
	{
		class Move : public Instruction
		{
		private:


		public:
            Move(void);
            ~Move(void);

		public:
            virtual void Work();
        };
	}
}