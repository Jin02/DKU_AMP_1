#pragma once

#include "BranchBase.h"

class BranchOnEqual : public BranchBase
{
private:
    bool        _isBranchSuccess;
    uint        _pc;
    
public:
    BranchOnEqual(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~BranchOnEqual(void);
    
public:
    virtual void Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst);
};