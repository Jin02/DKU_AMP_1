#pragma once

#include "IFormatInstruction.h"

class BranchOnEqual : public IFormatInstruction
{
private:
    bool        _isBranchSuccess;
    uint        _pc;
    
public:
    BranchOnEqual(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~BranchOnEqual(void);
    
public:
    virtual void Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst);
    virtual void DependencyCheckWithGetTargetData(bool&, uint&, uint ) const;
    
public:
    GET_ACCESSOR(IsBranchSuccess, bool, _isBranchSuccess);
    SET_ACCESSOR(PC, uint, _pc);
};