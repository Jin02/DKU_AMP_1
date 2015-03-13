#include "Instruction.h"
#include "System.h"

Instruction::Instruction(const std::vector<Operand>& operands) : _operands(operands)
{
    
}

Instruction::~Instruction()
{
    
}

unsigned int Instruction::GetData(const Operand& operand)
{
    System* system = System::GetInstance();
    
    if(operand.GetType() == Operand::Type::Register)
        return system->GetDataFromRegister(operand.GetData());
    else if(operand.GetType() == Operand::Type::Value)
        return operand.GetData();
    
    ASSERT_MSG("Error, cant support current operand type");
    return 0;
}
