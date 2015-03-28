#pragma once

#include "IFormatInstruction.h"

/** BranchGreaterThan **/
class BranchGreaterThan : public IFormatInstruction
{
private:
    
public:
    BranchGreaterThan(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~BranchGreaterThan(void);
    
public:
    virtual bool Execution();
};


/** BranchGreaterThanOrEqual **/
class BranchesGreaterThanOrEqual : public IFormatInstruction
{
private:
    
public:
    BranchesGreaterThanOrEqual(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~BranchesGreaterThanOrEqual(void);
    
public:
    virtual bool Execution();
};