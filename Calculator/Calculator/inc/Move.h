#pragma once

#include "Instruction.h"

class Move : public Instruction
{
private:
    unsigned int _rs, _rd;
    
public:
    Move(unsigned int rs, unsigned int rd);
    virtual ~Move(void);
    
public:
    virtual bool Execution();
};

class MoveFromHi : public Instruction
{
private:
    unsigned int _rd;
    
public:
    MoveFromHi(unsigned int rd);
    virtual ~MoveFromHi(void);
    
public:
    virtual bool Execution();
};


class MoveToHi : public Instruction
{
private:
    unsigned int _rs;
    
public:
    MoveToHi(unsigned int rs);
    virtual ~MoveToHi(void);
    
public:
    virtual bool Execution();
};


class MoveFromLo : public Instruction
{
private:
    unsigned int _rd;
    
public:
    MoveFromLo(unsigned int rd);
    virtual ~MoveFromLo(void);
    
public:
    virtual bool Execution();
};

class MoveToLo : public Instruction
{
private:
    unsigned int _rs;
    
public:
    MoveToLo(unsigned int rs);
    virtual ~MoveToLo(void);
    
public:
    virtual bool Execution();
};
