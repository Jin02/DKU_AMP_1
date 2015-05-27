#pragma once

#include <vector>
#include "Common.h"
#include <string>

class Instruction
{
public:
    enum class Type
    {
        Common,
        Jump,
        Branch
    };
    
protected:
    Type _type;
	std::string _name;
    
public:
    Instruction();
    virtual ~Instruction(void);
    
public:
	virtual void Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst) = 0;
    virtual void Memory() = 0;
    virtual void WriteBack() = 0;

	virtual void DependencyCheckWithGetTargetData(bool& hasDependency, uint& outTargetData, uint compareRegiIdx) const = 0;
	bool Forwarding(const Instruction* prev2stepInst, const Instruction* prev1stepInst, uint& outRegiData, uint regiIdx);
    
public:
    GET_ACCESSOR(Type, Type, _type);
	GET_ACCESSOR(Name, const std::string&, _name);
};