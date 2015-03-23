#include "ArithmeticInstruction.h"
#include "System.h"
#include "DumpLogManager.h"
#include <string>

ArithmeticInstruction::ArithmeticInstruction(const std::vector<Operand>& operands) : Instruction(operands)
{
    
}

ArithmeticInstruction::~ArithmeticInstruction(void)
{
}

void ArithmeticInstruction::Work()
{
	ASSERT_COND_MSG(_operands.size() == 3, "Error, can not support current instruction yet");
	{
        Operand::Type rdType = _operands[0].GetType();
        ASSERT_COND_MSG(rdType == Operand::Type::Register, "rd type must has register");
        {
            int result = Instruct(_operands[1], _operands[2]);
        
            System* system = System::GetInstance();
            system->SetDataToRegister(0, result);
        }
	}
}