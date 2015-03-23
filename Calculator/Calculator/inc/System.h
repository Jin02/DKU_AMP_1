#pragma once

#include <array>
#include <vector>
#include <map>

#include "Common.h"
#include "Singleton.h"

#include "Instruction.h"

#define MAX_DATA_REGISTER_NUM 32

class System : public Singleton<System>
{
private:
    std::array<int, MAX_DATA_REGISTER_NUM>      _registers;
    std::map<std::string, int>                  _jumpAddrs;
    std::vector<Instruction*>                   _instructions;
    
    //또 뭐? 점프요. 아 씨 -_-;
    
private:
    System(void);
    ~System(void);
    
public:
    void ParseAssemblyDumpFile(const std::string& dumpFileFullPath);
    void Run(int start);

public:
    inline void	SetDataToRegister(int index, int data) { _registers[index] = data; }
    inline int GetDataFromRegister(int index) { return _registers[index]; }
    
public:
    void ClearAllDataRegisters();
    void ClearRegister(int index);
    
    
    friend class Singleton<System>;
};
