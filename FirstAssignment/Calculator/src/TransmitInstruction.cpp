#include "TransmitInstruction.h"
#include "System.h"

TransmitInstruction::TransmitInstruction(const std::vector<Operand>& operands) : Instruction(operands)
{
}

TransmitInstruction::~TransmitInstruction(void)
{
}

void TransmitInstruction::Work()
{
	ASSERT_COND_MSG(_operands.size() == 2, "Error, can not support current instruction yet");
	{
        //아직 뭐, Move말고 다른게 나온게 없으니 세세히 구현하지 않아도 될듯
        Instruct(_operands[0], _operands[1]);
	}
}