#pragma once

#include "RFormatInstruction.h"

class DivideUnsigned : public RFormatInstruction
{
private:
	uint _executionHiResult;
	uint _executionLoResult;

public:
    DivideUnsigned(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~DivideUnsigned(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
    virtual bool Execution();
	virtual void WriteBuffer();
};


class Divide : public RFormatInstruction
{
private:
   	int _executionHiResult;
	int _executionLoResult;

public:
    Divide(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~Divide(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
    virtual bool Execution();
	virtual void WriteBuffer();
};

