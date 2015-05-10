#include "Add.h"
#include "System.h"
#include "DumpLogManager.h"

/** Add Unsigned **/

AddUnsigned::AddUnsigned(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(AddUnsigned);
}

AddUnsigned::~AddUnsigned(void)
{

}

unsigned int AddUnsigned::Instruct(unsigned int rsData, unsigned int rtData)
{
    return rsData + rtData;
}

Add::Add(unsigned int rs, unsigned int rt, unsigned int rd) : AddUnsigned(rs, rt, rd)
{
	GlobalDumpManagerAddLogClassName(Add);
}

Add::~Add()
{
}