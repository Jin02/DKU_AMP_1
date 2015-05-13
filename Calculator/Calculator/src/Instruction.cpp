#include "Instruction.h"
#include "System.h"

Instruction::Instruction()
{
    _type = Type::Common;
}

Instruction::~Instruction()
{
}

bool Instruction::Forwarding(const Instruction* prev2stepInst, const Instruction* prev1stepInst, uint& outRegiData, uint regiIdx)
{
	bool dependency = false;
	uint prevInstRsData = 0;

    if(prev1stepInst)
    {
        prev1stepInst->DependencyCheckWithGetTargetData(dependency, prevInstRsData, regiIdx);
        if(dependency)
        {
            outRegiData = prevInstRsData;
            return true;
        }
    }

    if(prev2stepInst)
    {
        prev2stepInst->DependencyCheckWithGetTargetData(dependency, prevInstRsData, regiIdx);
        if(dependency)
        {
            outRegiData = prevInstRsData;
            return true;
        }
    }

	return false;
}
