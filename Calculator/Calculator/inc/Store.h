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
    virtual bool Execution();
};

/** StoreConditional **/
class StoreConditional : public IFormatInstruction
{
private:
    
public:
    StoreConditional(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~StoreConditional(void);
    
public:
    virtual bool Execution();
};

/** StoreHalfword **/
class StoreHalfword : public IFormatInstruction
{
private:
    
public:
    StoreHalfword(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~StoreHalfword(void);
    
public:
    virtual bool Execution();
};

/** StoreWord **/
class StoreWord : public IFormatInstruction
{
private:
    
public:
    StoreWord(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~StoreWord(void);
    
public:
    virtual bool Execution();
};