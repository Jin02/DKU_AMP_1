#include "Move.h"
#include "System.h"
#include "DumpLogManager.h"

/** Move **/
Move::Move(unsigned int rs, unsigned int rd) : Instruction(), _rs(rs), _rd(rd){GlobalDumpManagerAddLogClassName(Move);}
Move::~Move(){}
bool Move::Execution()
{
    System* system = System::GetInstance();
    
    unsigned int rsData = system->GetDataFromRegister(_rs);
    system->SetDataToRegister(_rd, rsData);
	{
		GlobalDumpLogManager->AddLog("R[rd] = R[rs]", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = R[%d](0x%x)", _rd, _rs, rsData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}

/** MoveFromHi **/
MoveFromHi::MoveFromHi(unsigned int rd) : Instruction(), _rd(rd){GlobalDumpManagerAddLogClassName(MoveFromHi);}
MoveFromHi::~MoveFromHi(){}
bool MoveFromHi::Execution()
{
    System* system = System::GetInstance();
    
	uint hi = system->GetHiRegister();
	system->SetDataToRegister(_rd, hi);
	{
		GlobalDumpLogManager->AddLog("R[rd] = Hi", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = Hi(0x%x)", _rd, hi);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}

/** MoveToHi **/
MoveToHi::MoveToHi(unsigned int rs) : Instruction(), _rs(rs){GlobalDumpManagerAddLogClassName(MoveToHi);}
MoveToHi::~MoveToHi(){}
bool MoveToHi::Execution()
{
    System* system = System::GetInstance();

	uint rsData = system->GetDataFromRegister(_rs);
	system->SetHiRegister(rsData);
	{
		GlobalDumpLogManager->AddLog("Hi = R[rs]", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "Hi = R[%d](0x%x)", _rs, rsData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}

/** MoveFromLo **/
MoveFromLo::MoveFromLo(unsigned int rd) : Instruction(), _rd(rd){GlobalDumpManagerAddLogClassName(MoveFromLo);}
MoveFromLo::~MoveFromLo(){}
bool MoveFromLo::Execution()
{
    System* system = System::GetInstance();
    
	uint lo = system->GetLoRegister();
	system->SetDataToRegister(_rd, lo);
	{
		GlobalDumpLogManager->AddLog("R[rd] = Lo", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "R[%d] = Lo(0x%x)", _rd, lo);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}

/** MoveToLo **/
MoveToLo::MoveToLo(unsigned int rs) : Instruction(), _rs(rs){GlobalDumpManagerAddLogClassName(MoveToLo);}
MoveToLo::~MoveToLo(){}
bool MoveToLo::Execution()
{
    System* system = System::GetInstance();

	uint rsData = system->GetDataFromRegister(_rs);
	system->SetLoRegister(rsData);
	{
		GlobalDumpLogManager->AddLog("Lo = R[rs]", true);

		char logBuffer[64] = {0, };
		sprintf(logBuffer, "Lo = R[%d](0x%x)", _rs, rsData);
		GlobalDumpLogManager->AddLog(logBuffer, true);
		GlobalDumpManagerAddLog3NewLine;
	}

	return true;
}