#pragma once

#include <array>
#include <vector>

#include "Common.h"
#include "Singleton.h"

#include "Instruction.h"

#define MAX_DATA_REGISTER_NUM 32

class System : public Singleton<System>
{
private:
    std::array<int, MAX_DATA_REGISTER_NUM>		_dataRegisters;
    
    std::vector<std::string>                            _inst_reg_string;
    std::vector<Instruction*>                           _instructions;
    
private:
    System(void);
    ~System(void);
    
public:
    void ParseAssemblyDumpFile(const std::string& dumpFileFullPath);
    void Run(int start);

public:
    inline void	SetDataToRegister(int index, int data) { _dataRegisters[index] = data; }
    inline int GetDataFromRegister(int index) { return _dataRegisters[index]; }
    
public:
    void ClearAllDataRegisters();
    void ClearRegister(int index);
    
    void ClearAllInstruction();
    void ClearInstruction(int index);
    
    void ClearAllInstructionStr();
    void ClearInstructionStr(int index);
    
    friend class Singleton<System>;
};
