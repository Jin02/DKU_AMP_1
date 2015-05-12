#pragma once

#include "IFormatInstruction.h"

/** LoadByteUnsigned **/
class LoadByteUnsigned : public IFormatInstruction
{
private:
    uint _toRegiMemValue;
    
public:
    LoadByteUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~LoadByteUnsigned(void);
    
public:
    virtual void Execution();
    virtual void Memory();
    virtual void WriteBuffer();
};

/** LoadHalfwordUnsigned **/
class LoadHalfwordUnsigned : public IFormatInstruction
{
private:
    uint _toRegiMemValue;
    
public:
    LoadHalfwordUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~LoadHalfwordUnsigned(void);
    
public:
    virtual void Execution();
    
    virtual void Memory();
    virtual void WriteBuffer();
};

/** LoadLinked **/
class LoadLinked : public IFormatInstruction
{
private:
    uint _toRegiMemValue;
    
public:
    LoadLinked(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~LoadLinked(void);
    
public:
    virtual void Execution();
    virtual void Memory();
    virtual void WriteBuffer();
};

/** LoadUpperImmediate **/
class LoadUpperImmediate : public IFormatInstruction
{
public:
    LoadUpperImmediate(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~LoadUpperImmediate(void);
    
public:
    virtual void Execution();
    virtual void Memory();
    virtual void WriteBuffer();
};


/** LoadWord **/
class LoadWord : public IFormatInstruction
{
private:
    uint _toRegiMemValue;

    
public:
    LoadWord(unsigned int rs, unsigned int rt, unsigned int immediate);
    virtual ~LoadWord(void);
    
public:
    virtual void Execution();
    virtual void Memory();
    virtual void WriteBuffer();
};

/** LoadImmediate **/
class LoadImmediate : public Instruction
{
private:
    unsigned int _rd, _immediate;
    
public:
    LoadImmediate(unsigned int rd, unsigned int immediate);
    virtual ~LoadImmediate(void);
    
public:
    virtual void Execution();
    virtual void Memory();
    virtual void WriteBuffer();
};
