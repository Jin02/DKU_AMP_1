#include "Move.h"
#include "System.h"
#include "DumpLogManager.h"

Move::Move(const std::vector<Operand>& operands)
    : TransmitInstruction(operands)
{
}

Move::~Move(void)
{
}

void Move::Instruct(const Operand& operand0, const Operand& operand1)
{
    ASSERT_COND_MSG(operand0.GetType() == Operand::Type::Register, "Error, operand0 must has register type");
    {
        System* system = System::GetInstance();
        
        int inputData = GetData(operand1);
        system->SetDataToRegister(operand0.GetData(), inputData);
#ifdef USE_OUTPUT_DUMP_LOG
        char buffer[256] = {0, };
        sprintf(buffer, "R%d : %2d", operand0.GetData(), inputData);
        DumpLogManager::GetInstance()->AddLog(buffer, true);
#endif
    }
}