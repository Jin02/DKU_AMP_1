#include "BranchBase.h"
#include "DumpLogManager.h"

BranchBase::BranchBase(unsigned int rs, unsigned int rt, unsigned int immediate)
	: IFormatInstruction(rs, rt, immediate)
{
    _type = Type::Branch;
}

BranchBase::~BranchBase()
{

}

void BranchBase::DependencyCheckWithGetTargetData(bool&, uint&, uint ) const
{
    
}