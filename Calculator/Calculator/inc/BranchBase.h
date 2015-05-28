#pragma once

#include "IFormatInstruction.h"

class BranchBase: public IFormatInstruction
{
protected:
    bool        _isBranchSuccess;
    uint        _pc;
    
public:
    BranchBase(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~BranchBase(void);
    
public:
     virtual void DependencyCheckWithGetTargetData(bool& c, uint&, uint ) const;
    
public:
    GET_ACCESSOR(IsBranchSuccess, bool, _isBranchSuccess);
    SET_ACCESSOR(PC, uint, _pc);
};