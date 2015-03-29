#pragma once

#include "RFormatInstruction.h"

class SubtractUnsigned : public RFormatInstruction
{
private:
    
public:
    SubtractUnsigned(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~SubtractUnsigned(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
};

class Subtract : public SubtractUnsigned
{
public:
	Subtract(unsigned int rs, unsigned int rt, unsigned int rd);
	virtual ~Subtract();
};