#pragma once

#include "Common.h"
#include "Singleton.h"

#include <string>

class DumpLogManager : public Singleton<DumpLogManager>
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
    
    friend class Singleton<DumpLogManager>;
};

#define GlobalDumpLogManager							DumpLogManager::GetInstance()
#define GlobalDumpManagerAddLogNewLine(log)	GlobalDumpLogManager->AddLog(log, true)
#define GlobalDumpManagerAddLogClassName {	std::string className = typeid(this).name(); className.replace(0, 5, "* Instruction"); GlobalDumpLogManager->AddLog(className + "\n", true); }
#define GlobalDumpManagerAddLog3NewLine {	GlobalDumpLogManager->AddLog("\n\n", true); }