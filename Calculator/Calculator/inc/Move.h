#pragma once

#include "Instruction.h"

class MoveFromHi : public Instruction
{
private:
    unsigned int _rd, _hiData;
    
public:
    MoveFromHi(unsigned int rd);
    virtual ~MoveFromHi(void);
    
public:
    virtual void WriteBack();
};


class MoveToHi : public Instruction
{
private:
    unsigned int _rs, _rsData;
    
public:
    MoveToHi(unsigned int rs);
    virtual ~MoveToHi(void);
    
public:
    virtual void WriteBack();
};


class MoveFromLo : public Instruction
{
private:
    unsigned int _rd, _loData;
    
public:
    MoveFromLo(unsigned int rd);
    virtual ~MoveFromLo(void);
    
public:
    virtual void WriteBack();
};

class MoveToLo : public Instruction
{
private:
    unsigned int _rs, _rsData;
    
public:
    MoveToLo(unsigned int rs);
    virtual ~MoveToLo(void);
    
public:
    virtual void WriteBack();
};
