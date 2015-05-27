#pragma once

#include "Common.h"
#include "Singleton.h"

#include <string>
#include <typeinfo>

class DumpLogManager : public Mips::Singleton<DumpLogManager>
{
private:
    std::string         _buffer;
    
private:
    DumpLogManager(void);
    ~DumpLogManager(void);
    
public:
    void AddLog(const std::string& log, bool addNewLine = false);
    void Print();
    void WriteFile(const std::string& path);
    
public:
    GET_ACCESSOR(Buffer, const std::string&, _buffer);
    
    friend class Mips::Singleton<DumpLogManager>;
};

#define GlobalDumpLogManager							DumpLogManager::GetInstance()
#define GlobalDumpManagerAddLogNewLine(log)	GlobalDumpLogManager->AddLog(log, true)

#define GlobalDumpManagerAddLogClassName(N) { _name = #N; std::string name = #N; GlobalDumpLogManager->AddLog("Instruction\t| " + name + "\n", true); }
#define GlobalDumpManagerAddLog3NewLine {	GlobalDumpLogManager->AddLog("\n\n", true); }
#define GlobalDumpManagerAddExecutionLog(Value){char buff[256] = {0, };sprintf(buff, "ExecutionResult = 0x%x", Value);GlobalDumpLogManager->AddLog(buff, true);}