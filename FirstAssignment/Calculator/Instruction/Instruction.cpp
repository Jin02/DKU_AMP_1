#include "Instruction.h"
#include "System.h"

namespace Instruction
{
    Instruction::Instruction()
    {
    }

    Instruction::~Instruction()
    {
    
    }

    unsigned int Instruction::GetData(const Operand* operand)
    {
		Core::System* system = Core::System::GetInstance();
        
        if(operand->GetType() == Operand::Type::Register)
            return system->GetDataFromRegister(operand->GetData());
        else if(operand->GetType() == Operand::Type::Value)
            return operand->GetData();
    
        ASSERT_MSG("Error, cant support current operand type");
        return 0;
    }
}