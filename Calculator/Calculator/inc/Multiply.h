#pragma once

#include "RFormatInstruction.h"


class Multiply32BitRes : public RFormatInstruction
{
private:
    
public:
    Multiply32BitRes(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~Multiply32BitRes(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
};


class Multiply : public RFormatInstruction
{
private:
	long long _multyplyExecutionResult;
    
public:
    Multiply(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~Multiply(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
    virtual bool Execution();
	virtual void WriteBuffer();
};



class MultiplyUnsigned : public RFormatInstruction
{
private:
	unsigned long long _multyplyExecutionResult;

public:
    MultiplyUnsigned(unsigned int rs, unsigned int rt, unsigned int rd);
    virtual ~MultiplyUnsigned(void);
    
public:
    virtual unsigned int Instruct(unsigned int rsData, unsigned int rtData);
    virtual bool Execution();
	virtual void WriteBuffer();
};