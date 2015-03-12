#pragma once

#include <vector>
#include "Operand.h"

namespace Instruction
{
	class Instruction
	{
	public:
        Instruction(void);
        virtual ~Instruction(void);

    protected:
        unsigned int GetData(const Operand* operand);
        
	protected:
		virtual void Work() = 0;

	protected:
		std::vector<Operand*>	_operands;
	};
}