#include "DumpLogManager.h"
#include <fstream>

DumpLogManager::DumpLogManager()
{
    
}

DumpLogManager::~DumpLogManager()
{
    
}

void DumpLogManager::AddLog(const std::string& log, bool addNewLine)
{
    _buffer += log + (addNewLine ? "\n" : "");
}

void DumpLogManager::Print()
{
    printf("%s\n", _buffer.c_str());
}

void DumpLogManager::WriteFile(const std::string& path)
{
    std::ofstream outFile(path);
    outFile.write(_buffer.c_str(), _buffer.length());
    outFile.close();
}