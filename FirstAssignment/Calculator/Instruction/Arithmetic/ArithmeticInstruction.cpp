#include "ArithmeticInstruction.h"
#include "System.h"

using namespace Instruction;

ArithmeticInstruction::ArithmeticInstruction(void)
{
}

ArithmeticInstruction::~ArithmeticInstruction(void)
{
}

void ArithmeticInstruction::Work()
{
	ASSERT_COND_MSG(_operands.size() != 2, "Error, can not support current instruction yet");
	{
		Core::System* system = Core::System::GetInstance();
		unsigned int registerIndex = 0;
        
		const Operand* operand0 = _operands[0];
        unsigned int operand1Data = GetData(_operands[1]);
        
        unsigned int result = 0;
        
        if( operand0->GetType() == Operand::Type::Register)
		{
			registerIndex = operand0->GetData();
            result = Instruct(GetData(operand0), operand1Data);
		}
		else if( operand0->GetType() == Operand::Type::Value )
		{
            registerIndex = 0; //R0
            result = Instruct(operand0->GetData(), operand1Data);
        }

        system->SetDataToRegister(registerIndex, result);
	}
}