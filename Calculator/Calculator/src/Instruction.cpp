#include "Instruction.h"
#include "System.h"

Instruction::Instruction()
{
}

Instruction::~Instruction()
{
}

bool Instruction::Forwarding(const Instruction* prev2stepInst, const Instruction* prev1stepInst, uint& outRegiData, uint regiIdx)
{
	bool dependency = false;
	uint prevInstRsData = 0;
	prev1stepInst->DependencyCheckWithGetTargetData(dependency, prevInstRsData, regiIdx);
	if(dependency)
	{
		outRegiData = prevInstRsData;
		return true;
	}

	prev2stepInst->DependencyCheckWithGetTargetData(dependency, prevInstRsData, regiIdx);
	if(dependency)
	{
		outRegiData = prevInstRsData;
		return true;
	}

	return false;
}
