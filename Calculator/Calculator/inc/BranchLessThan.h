#pragma once

#include "IFormatInstruction.h"

/** BranchLessThan **/
class BranchLessThan : public IFormatInstruction
{
private:
    
public:
    BranchLessThan(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~BranchLessThan(void);
    
public:
    virtual bool Execution();
};


/** BranchLessThanOrEqual **/
class BranchesLessThanOrEqual : public IFormatInstruction
{
private:
    
public:
    BranchesLessThanOrEqual(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~BranchesLessThanOrEqual(void);
    
public:
    virtual bool Execution();
};