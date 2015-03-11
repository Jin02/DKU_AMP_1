#include "Add.h"
#include "System.h"

using namespace Instruction::Arithmetic;

Add::Add(void)
{
}

Add::~Add(void)
{
}

void Add::Work()
{
	ASSERT_COND_MSG(_operands.size() != 2, "Error, can not support current instruction yet");
	{
		Core::System* system = Core::System::GetInstance();
		unsigned int registerIndex = 0;

		const Operand* operand0 = _operands[0];
		if( operand0->GetType() == Operand::Type::Register)
		{
			registerIndex = operand0->GetData();
		}
		else if( operand0->GetType() == Operand::Type::Value )
		{

		}
	}
}