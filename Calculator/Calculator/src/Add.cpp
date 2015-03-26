#include "Add.h"
#include "System.h"


Add::Add(TypeFlag flag, const std::vector<Operand>& operands)
    : ArithmeticInstruction(operands), _flag(flag)
{
    
}

Add::~Add(void)
{
}

int Add::Instruct(const Operand& rs, const Operand& rt)
{
    bool immediate = (_flag & (unsigned char)Type::Immediate) != 0;
    if( immediate )
    {
        if(rt.GetType() == Operand::Type::Value)
            ASSERT_MSG("third operand must SignExtImm");
    }
    
    return GetData(rs) + GetData(rt);
}