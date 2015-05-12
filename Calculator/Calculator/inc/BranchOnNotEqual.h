#pragma once

#include "IFormatInstruction.h"

class BranchOnNotEqual : public IFormatInstruction
{
private:
    bool _isBranchSuccess;
    
public:
    BranchOnNotEqual(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~BranchOnNotEqual(void);
    
public:
    virtual void Forwarding(bool&, uint&, uint ) const;
    
public:
    GET_ACCESSOR(IsBranchSuccess, bool, _isBranchSuccess);    
};