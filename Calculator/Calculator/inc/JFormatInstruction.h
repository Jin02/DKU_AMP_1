#pragma once

#include "Instruction.h"

class JFormatInstruction : public Instruction
{
protected:
    unsigned int _address;
    
public:
    JFormatInstruction(unsigned int address);
    virtual ~JFormatInstruction(void);
    
public:
    virtual void DependencyCheckWithGetTargetData(bool& c, uint&, uint ) const;
};

class Jump : public JFormatInstruction
{
public:
    Jump(unsigned int address);
    ~Jump();

public:
	virtual void Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst);
	virtual void WriteBack(){}
	virtual void Memory(const Instruction* prev2stepInst, const Instruction* prev1stepInst){}
};

class JumpAndLink : public JFormatInstruction
{
private:
	uint _executionResult;
    uint _pc;

public:
    JumpAndLink(unsigned int address);
    ~JumpAndLink();

public:
	virtual void Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst);
	virtual void Memory(const Instruction* prev2stepInst, const Instruction* prev1stepInst);
	virtual void WriteBack();
    
public:
    SET_ACCESSOR(PC, uint, _pc);
};
