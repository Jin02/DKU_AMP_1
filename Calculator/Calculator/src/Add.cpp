#include "Add.h"
#include "System.h"

/** Add Unsigned **/

AddUnsigned::AddUnsigned(unsigned int rs, unsigned int rt, unsigned int rd)
    : RFormatInstruction(rs, rt, rd)
{
    
}

AddUnsigned::~AddUnsigned(void)
{
    
}

unsigned int AddUnsigned::Instruct(unsigned int rs, unsigned int rt)
{
    return rs + rt;
}

/** Add **/

//Add::Add(unsigned int rs, unsigned int rt, unsigned int rd)
//: RFormatInstruction(rs, rt, rd)
//{
//    
//}
//
//Add::~Add(void)
//{
//    
//}
//
//unsigned int Add::Instruct(unsigned int rs, unsigned int rt)
//{
//    int signedRs = rs;
//    int signedRt = rt;
//    
//    return rs + rt;
//}
