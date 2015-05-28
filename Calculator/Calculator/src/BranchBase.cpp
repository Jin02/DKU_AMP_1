#include "BranchBase.h"
#include "DumpLogManager.h"

BranchBase::BranchBase(unsigned int rs, unsigned int rt, unsigned int immediate)
	: IFormatInstruction(rs, rt, immediate)
{
	_isBranchSuccess = false;
	_pc = 0;

    _type = Type::Branch;
}

BranchBase::~BranchBase()
{

}

void BranchBase::DependencyCheckWithGetTargetData(bool& c, uint&, uint ) const
{
    c = false;
}