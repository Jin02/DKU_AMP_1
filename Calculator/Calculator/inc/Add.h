#pragma once

#include "ArithmeticInstruction.h"

class Add : public ArithmeticInstruction
{
public:
    enum class Type : unsigned char
    {
        None        = 0,
        Immediate   = 1,
        Unsigned    = 2
    };
    
    // involved Add::Type
    typedef unsigned char TypeFlag;
    
private:
    TypeFlag        _flag;
    
public:
    Add(TypeFlag flag, const std::vector<Operand>& operands);
    virtual ~Add(void);
    
public:
    virtual int Instruct(const Operand& rs, const Operand& rt);
};
