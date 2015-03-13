#include "Move.h"
#include "System.h"

Move::Move(const std::vector<const Operand>& operands)
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
        
        unsigned int inputData = GetData(operand1);
        system->SetDataToRegister(operand0.GetData(), inputData);
#ifdef USE_OUTPUT_DUMP_LOG
        printf("R%d : %2d\n", operand0.GetData(), inputData);
#endif
    }
}