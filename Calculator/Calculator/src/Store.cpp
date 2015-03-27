#include "Store.h"
#include "System.h"

/** StoreByte **/

StoreByte::StoreByte(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

StoreByte::~StoreByte()
{
    
}

void StoreByte::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int toMemRtData = system->GetDataFromRegister(_rt) & 0x0000000f;
    unsigned int rsData = system->GetDataFromRegister(_rs);
    unsigned int memData = system->GetDataFromMemory(rsData + _immediate);

    memData = (memData & 0xfffffff0) | (toMemRtData);
    system->SetDataToMemory(rsData + _immediate, memData);
}


/** StoreConditional **/

//StoreConditional::StoreConditional(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
//{
//    
//}
//
//StoreConditional::~StoreConditional()
//{
//    
//}
//
//void StoreConditional::Execution()
//{
//}

/** StoreUpperImmediate **/

StoreHalfword::StoreHalfword(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

StoreHalfword::~StoreHalfword()
{
    
}

void StoreHalfword::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int toMemRtData = system->GetDataFromRegister(_rt) & 0x0000ffff;
    unsigned int rsData = system->GetDataFromRegister(_rs);
    unsigned int memData = system->GetDataFromMemory(rsData + _immediate);
    
    memData = (memData & 0xffff0000) | (toMemRtData);
    system->SetDataToMemory(rsData + _immediate, memData);
}

/** StoreWord **/

StoreWord::StoreWord(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

StoreWord::~StoreWord()
{
    
}

void StoreWord::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int toMemRtData = system->GetDataFromRegister(_rt);
    unsigned int rsData = system->GetDataFromRegister(_rs);
    system->SetDataToMemory(rsData + _immediate, toMemRtData);
}
