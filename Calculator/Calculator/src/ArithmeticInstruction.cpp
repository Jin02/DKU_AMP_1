#include "ArithmeticInstruction.h"
#include "System.h"
#include "DumpLogManager.h"
#include <string>

ArithmeticInstruction::ArithmeticInstruction(const std::vector<Operand>& operands)
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
        
        int operand0Data = GetData(_operands[0]);		
		int operand1Data = GetData(_operands[1]);        
        int result = Instruct(operand0Data, operand1Data);
        
#ifdef USE_OUTPUT_DUMP_LOG
        char buffer[256] = {0, };
        sprintf(buffer, "R%d : %2d = %2d %2c %2d", 0, result, operand0Data, GetDumpLogSymbol(), operand1Data);
        
        DumpLogManager::GetInstance()->AddLog(buffer, true);
#endif
        
        system->SetDataToRegister(0, result);
	}
}