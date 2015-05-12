#pragma once

#include "IFormatInstruction.h"

/** StoreByte **/
class StoreByte : public IFormatInstruction
{
private:
    
public:
    StoreByte(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~StoreByte(void);
    
public:
    virtual void Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst);
    virtual void Memory();
};

/** StoreConditional **/
class StoreConditional : public IFormatInstruction
{
private:
    
public:
    StoreConditional(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~StoreConditional(void);
    
public:
    virtual void Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst);
    virtual void Memory();
};

/** StoreHalfword **/
class StoreHalfword : public IFormatInstruction
{
private:
    
public:
    StoreHalfword(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~StoreHalfword(void);
    
public:
    virtual void Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst);
    virtual void Memory();
};

/** StoreWord **/
class StoreWord : public IFormatInstruction
{
private:
    
public:
    StoreWord(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~StoreWord(void);
    
public:
    virtual void Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst);    
    virtual void Memory();
};