#pragma once

#include <array>
#include <vector>

#include "Common.h"
#include "SingleTon.h"

#include "Instruction.h"

#define MAX_DATA_REGISTER_NUM 32

class System : public Singleton<System>
{
private:
    std::array<unsigned int, MAX_DATA_REGISTER_NUM>		_dataRegisters;
    
    std::vector<std::string>                            _inst_reg_string;
    std::vector<Instruction*>                           _instructions;
    
public:
    System(void);
    ~System(void);
    
public:
    void ParseAssemblyDumpFile(const std::string& dumpFileFullPath);
    void Run(unsigned int start);

public:
    inline void	SetDataToRegister(unsigned int index, unsigned int data) { _dataRegisters[index] = data; }
    inline unsigned int GetDataFromRegister(unsigned int index) { return _dataRegisters[index]; }
    
public:
    void ClearAllDataRegisters();
    void ClearRegister(unsigned int index);
    
    void ClearAllInstruction();
    void ClearInstruction(unsigned int index);
    
    void ClearAllInstructionStr();
    void ClearInstructionStr(unsigned int index);
};
