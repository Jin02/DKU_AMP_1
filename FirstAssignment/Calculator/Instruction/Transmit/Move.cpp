#include "Move.h"
#include "System.h"

using namespace Instruction::Transmit;

Move::Move(void)
{
}

Move::~Move(void)
{
}

void Move::Work()
{
    ASSERT_COND_MSG(_operands.size() != 2, "Error, can not support current instruction yet");
    {
        Core::System* system = Core::System::GetInstance();
        unsigned int registerIndex = 0;
        
        const Operand* operand0 = _operands[0];
        unsigned int operand1Data = GetData(_operands[1]);
        
        if( operand0->GetType() == Operand::Type::Register)
        {
            registerIndex = operand0->GetData();
            system->SetDataToRegister(registerIndex, operand1Data - operand0->GetData());
        }
        else if( operand0->GetType() == Operand::Type::Value )
        {
            registerIndex = 0; //R0
            unsigned int operand0Data = operand0->GetData();
            system->SetDataToRegister(0, operand0Data - operand1Data);
        }
    }
}