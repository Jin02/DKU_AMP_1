#pragma once

#include "Common.h"
#include <string>

class DumpLogManager
{
private:
    std::string				_buffer;
	static DumpLogManager*	_instance;
    
private:
    DumpLogManager(void);
    ~DumpLogManager(void);
    
public:
	static DumpLogManager* GetInstance();
	static void Destory();

    void AddLog(const std::string& log, bool addNewLine = false);
    void Print();
    void WriteFile(const std::string& path);
    
public:
    GET_ACCESSOR(Buffer, const std::string&, _buffer);
};
