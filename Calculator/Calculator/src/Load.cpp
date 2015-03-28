#include "Load.h"
#include "System.h"

/** LoadByteUnsigned **/

LoadByteUnsigned::LoadByteUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

LoadByteUnsigned::~LoadByteUnsigned()
{

}

bool LoadByteUnsigned::Execution()
{
    System* system = System::GetInstance();
    unsigned int rsData     = system->GetDataFromRegister(_rs);
    unsigned int memData    = system->GetDataFromMemory(rsData+_immediate);
    unsigned int toRegiData = memData & 0x000000ff;
    
    system->SetDataToRegister(_rt, toRegiData);

	return true;
}

/** LoadHalfwordUnsigned **/
LoadHalfwordUnsigned::LoadHalfwordUnsigned(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

LoadHalfwordUnsigned::~LoadHalfwordUnsigned()
{
    
}

bool LoadHalfwordUnsigned::Execution()
{
    System* system = System::GetInstance();
    unsigned int rsData     = system->GetDataFromRegister(_rs);
    unsigned int memData    = system->GetDataFromMemory(rsData+_immediate);
    unsigned int toRegiData = memData & 0x0000ffff;
    
    system->SetDataToRegister(_rt, toRegiData);

	return true;
}


/** LoadLinked **/

//LoadLinked::LoadLinked(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
//{
//    
//}
//
//LoadLinked::~LoadLinked()
//{
//    
//}
//
//void LoadLinked::Execution()
//{
//    System* system = System::GetInstance();
//    
//    unsigned int rsData = system->GetDataFromRegister(_rs);
//    unsigned int memData = system->GetDataFromMemory(rsData + _immediate);
//    
//    system->SetDataToRegister(_rt, memData);
//}

/** LoadUpperImmediate **/

LoadUpperImmediate::LoadUpperImmediate(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

LoadUpperImmediate::~LoadUpperImmediate()
{
    
}

bool LoadUpperImmediate::Execution()
{
    System* system = System::GetInstance();
    system->SetDataToRegister(_rt, _immediate & 0xffff0000);

	return true;
}

/** LoadWord **/

LoadWord::LoadWord(unsigned int rs, unsigned int rt, unsigned int immediate) : IFormatInstruction(rs, rt, immediate)
{
    
}

LoadWord::~LoadWord()
{
    
}

bool LoadWord::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int rsData = system->GetDataFromRegister(_rs);
    unsigned int memData = system->GetDataFromMemory(rsData + _immediate);

    system->SetDataToRegister(_rt, memData);
	return true;
}

/** LoadImmediate **/

LoadImmediate::LoadImmediate(unsigned int rd, unsigned int immediate)
    : Instruction(), _rd(rd), _immediate(immediate)
{
    
}

LoadImmediate::~LoadImmediate()
{
    
}

bool LoadImmediate::Execution()
{
    System* system = System::GetInstance();
    system->SetDataToRegister(_rd, _immediate);

	return true;
}
