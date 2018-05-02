//#include "Move.h"
//#include "System.h"
//#include "DumpLogManager.h"
//
///** MoveFromHi **/
//MoveFromHi::MoveFromHi(unsigned int rd) : Instruction(), _rd(rd)
//{
//    GlobalDumpManagerAddLogClassName(MoveFromHi);
//
//    System* system = System::GetInstance();
//    _hiData = system->GetHiRegister();
//}
//
//MoveFromHi::~MoveFromHi()
//{
//}
//
//void MoveFromHi::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
//{
//    
//}
//
//void MoveFromHi::WriteBack()
//{
//    System* system = System::GetInstance();
//	system->SetDataToRegister(_rd, _hiData);
//	{
//		GlobalDumpLogManager->AddLog("R[rd] = Hi", true);
//
//		char logBuffer[64] = {0, };
//		sprintf(logBuffer, "R[%d] = Hi(0x%x)", _rd, _hiData);
//		GlobalDumpLogManager->AddLog(logBuffer, true);
//		GlobalDumpManagerAddLog3NewLine;
//	}
//}
//
//void MoveFromHi::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outTargetData, uint compareRegiIdx) const
//{
//    hasDependency = (_rd == compareRegiIdx);
//    outTargetData = _hiData;
//}
//
///** MoveToHi **/
//MoveToHi::MoveToHi(unsigned int rs) : Instruction(), _rs(rs)
//{
//    GlobalDumpManagerAddLogClassName(MoveToHi);
//
//    System* system = System::GetInstance();
//    _rsData = system->GetDataFromRegister(_rs);
//}
//
//MoveToHi::~MoveToHi()
//{
//}
//
//void MoveToHi::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
//{
//    
//}
//
//void MoveToHi::WriteBack()
//{
//    System* system = System::GetInstance();
//	system->SetHiRegister(_rsData);
//	{
//		GlobalDumpLogManager->AddLog("Hi = R[rs]", true);
//
//		char logBuffer[64] = {0, };
//		sprintf(logBuffer, "Hi = R[%d](0x%x)", _rs, _rsData);
//		GlobalDumpLogManager->AddLog(logBuffer, true);
//		GlobalDumpManagerAddLog3NewLine;
//	}
//}
//
//void MoveToHi::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outTargetData, uint compareRegiIdx) const
//{
//    
//}
//
///** MoveFromLo **/
//MoveFromLo::MoveFromLo(unsigned int rd) : Instruction(), _rd(rd)
//{
//    GlobalDumpManagerAddLogClassName(MoveFromLo);
//    
//    System* system = System::GetInstance();
//    _loData = system->GetLoRegister();;
//}
//
//MoveFromLo::~MoveFromLo()
//{
//}
//
//void MoveFromLo::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
//{
//    
//}
//
//void MoveFromLo::WriteBack()
//{
//    System* system = System::GetInstance();
//	system->SetDataToRegister(_rd, _loData);
//	{
//		GlobalDumpLogManager->AddLog("R[rd] = Lo", true);
//
//		char logBuffer[64] = {0, };
//		sprintf(logBuffer, "R[%d] = Lo(0x%x)", _rd, _loData);
//		GlobalDumpLogManager->AddLog(logBuffer, true);
//		GlobalDumpManagerAddLog3NewLine;
//	}
//}
//
//void MoveFromLo::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outTargetData, uint compareRegiIdx) const
//{
//    hasDependency = (_rd == compareRegiIdx);
//    outTargetData = _loData;
//}
//
//
///** MoveToLo **/
//MoveToLo::MoveToLo(unsigned int rs) : Instruction(), _rs(rs)
//{
//    GlobalDumpManagerAddLogClassName(MoveToLo);
//
//    System* system = System::GetInstance();
//    _rsData = system->GetDataFromRegister(_rs);
//}
//
//MoveToLo::~MoveToLo()
//{
//}
//
//void MoveToLo::Execution(const Instruction* prev2stepInst, const Instruction* prev1stepInst)
//{
//    
//}
//
//void MoveToLo::WriteBack()
//{
//    System* system = System::GetInstance();
//	system->SetLoRegister(_rsData);
//	{
//		GlobalDumpLogManager->AddLog("Lo = R[rs]", true);
//
//		char logBuffer[64] = {0, };
//		sprintf(logBuffer, "Lo = R[%d](0x%x)", _rs, _rsData);
//		GlobalDumpLogManager->AddLog(logBuffer, true);
//		GlobalDumpManagerAddLog3NewLine;
//	}
//}
//
//void MoveToLo::DependencyCheckWithGetTargetData(bool& hasDependency, uint& outTargetData, uint compareRegiIdx) const
//{
//
//}
