#pragma once

#include <vector>
#include "Operand.h"

namespace Instruction
{
	class Instruction
	{
	public:
		Instruction(void)	{}
		virtual ~Instruction(void)	{}

	public:
		virtual void Work() = 0;

	protected:
		std::vector<Operand*>	_operands;
	};
}