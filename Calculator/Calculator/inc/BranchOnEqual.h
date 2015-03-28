#pragma once

#include "IFormatInstruction.h"

class BranchOnEqual : public IFormatInstruction
{
private:
    
public:
    BranchOnEqual(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~BranchOnEqual(void);
    
public:
    virtual bool Execution();
};