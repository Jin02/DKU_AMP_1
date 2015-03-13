#pragma once

#include <vector>
#include "Common.h"

class Operand
{
public:
    enum class Type
    {
        Register,
        Value
    };
    
public:
    Operand(Type type) :_value(0), _type(type){}
    ~Operand(void){}
    
public:
    GET_SET_ACCESSOR(Data, unsigned int, _value);
    GET_ACCESSOR(Type, Type, _type);
    
private:
    unsigned int	_value;
    Type			_type;
};
