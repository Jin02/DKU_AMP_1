#pragma once

#include <vector>
#include "Common.h"

class Instruction
{
public:
    Instruction();
    virtual ~Instruction(void);
    
public:
    virtual void Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst) = 0;
    virtual void Forwarding(bool& hasDependency, uint& outTargetData, uint compareRegiIdx) const = 0;
};
