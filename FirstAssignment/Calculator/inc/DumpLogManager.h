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
