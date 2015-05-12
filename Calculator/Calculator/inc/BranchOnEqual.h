#pragma once

#include "IFormatInstruction.h"

class BranchOnEqual : public IFormatInstruction
{
private:
    bool _isBranchSuccess;
    
public:
    BranchOnEqual(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~BranchOnEqual(void);
    
public:
    virtual void Forwarding(bool&, uint&, uint ) const;
    
public:
    GET_ACCESSOR(IsBranchSuccess, bool, _isBranchSuccess);
};