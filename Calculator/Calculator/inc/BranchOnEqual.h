#pragma once

#include "BranchBase.h"

class BranchOnEqual : public BranchBase
{    
public:
    BranchOnEqual(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~BranchOnEqual(void);
    
public:
    virtual void Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst);
	virtual void Memory(){}
	virtual void WriteBack(){}
};