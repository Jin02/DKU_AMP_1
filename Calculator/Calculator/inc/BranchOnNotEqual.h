#pragma once

#include "BranchBase.h"

class BranchOnNotEqual : public BranchBase
{    
public:
    BranchOnNotEqual(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~BranchOnNotEqual(void);
    
public:
    virtual void Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst);
};