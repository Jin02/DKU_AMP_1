#pragma once

#include <array>
#include <vector>

#include "Common.h"
#include "Singleton.h"

#include "Instruction.h"

//8192 = 0x8000 / 4
#define MAX_PROCESSOR_MEMORY 8192

class System : public Singleton<System>
{
private:
    std::array<unsigned int, MAX_PROCESSOR_MEMORY>	_processorMemory;
	std::array<unsigned int, 32>					_registers;
    unsigned int                                    _programCounter;

private:
    System(void);
    ~System(void);
    
private:
    unsigned int Fetch();
    Instruction* Decode(unsigned int instruction);

	// if next instruction is nop, return value is true else false.
    bool Execution(Instruction* inst);
    
public:
    void Load(const std::string& path);

	void RunCycle();
    void Run();

    inline unsigned int GetDataFromRegister(int index) { return _registers[index]; }
    inline void SetDataToRegister(int index, unsigned int value) { _registers[index] = value; }
    
    unsigned int GetDataFromMemory(int address);
    void SetDataToMemory(int address, unsigned int data);
    
public:
	GET_SET_ACCESSOR(ReturnAddress, unsigned int, _registers[31]);
	GET_SET_ACCESSOR(FramePointer,	unsigned int, _registers[30]);
	GET_SET_ACCESSOR(StackPointer,	unsigned int, _registers[29]);
	GET_SET_ACCESSOR(GlobalPointer, unsigned int, _registers[28]);
    
    GET_SET_ACCESSOR(ProgramCounter, unsigned int, _programCounter);
    
    

    friend class Singleton<System>;
};
