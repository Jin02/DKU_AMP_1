#pragma once

#include <vector>
#include "Common.h"
#include <functional>

class Instruction
{
public:
    Instruction();
    virtual ~Instruction(void);
    
    
public:
    typedef std::function<void(bool& hasDependency, uint& outWriteTargetData, uint registerIdx)> ForwardingFuncType;
    
public:
    virtual void Execution(const ForwardingFuncType& prev2stepInst, const ForwardingFuncType& prev1stepInst) = 0;
    virtual void Forwarding(bool& hasDependency, uint& outTargetData, uint compareRegiIdx) const = 0;
};
