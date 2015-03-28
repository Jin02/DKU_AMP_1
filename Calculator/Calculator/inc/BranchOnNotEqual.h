#pragma once

#include "IFormatInstruction.h"

class BranchOnNotEqual : public IFormatInstruction
{
private:
    
public:
    BranchOnNotEqual(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~BranchOnNotEqual(void);
    
public:
    virtual void Execution();
};