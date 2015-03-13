#include "ArithmeticInstruction.h"
#include "System.h"
#include "DumpLogManager.h"
#include <string>

ArithmeticInstruction::ArithmeticInstruction(const std::vector<const Operand>& operands)
    : Instruction(operands)
{
}

ArithmeticInstruction::~ArithmeticInstruction(void)
{
}

void ArithmeticInstruction::Work()
{
	ASSERT_COND_MSG(_operands.size() == 2, "Error, can not support current instruction yet");
	{
		System* system = System::GetInstance();
		unsigned int registerIndex = 0;
        
		const Operand& operand0 = _operands[0];
        unsigned int operand1Data = GetData(_operands[1]);
        
        unsigned int result = 0;
        
        if( operand0.GetType() == Operand::Type::Register)
		{
			registerIndex = operand0.GetData();
            result = Instruct(GetData(operand0), operand1Data);
		}
		else if( operand0.GetType() == Operand::Type::Value )
		{
            registerIndex = 0; //R0
            result = Instruct(operand0.GetData(), operand1Data);
        }
        
#ifdef USE_OUTPUT_DUMP_LOG
        unsigned int operand0Data = GetData(_operands[0]);
        char buffer[256] = {0, };
        sprintf(buffer, "R%d : %2d = %2d %2c %2d", registerIndex, result, operand0Data, GetDumpLogSymbol(), operand1Data);
        
        DumpLogManager::GetInstance()->AddLog(buffer, true);
#endif
        
        system->SetDataToRegister(registerIndex, result);
	}
}