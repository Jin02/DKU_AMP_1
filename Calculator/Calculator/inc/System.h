#pragma once

#include <array>
#include <vector>

#include "Common.h"
#include "Singleton.h"

//8192 = 0x8000 / 4
#define MAX_PROCESSOR_MEMORY 8192

class System : public Singleton<System>
{
private:
    std::array<unsigned int, MAX_PROCESSOR_MEMORY>	_processorMemory;
	std::array<unsigned int, 32>					_registers;

private:
    System(void);
    ~System(void);
    
public:
    void Load(const std::string& path);

	void RunCycle(int procMemIndex);
	inline unsigned int Fetch(int procMemIndex) { return _processorMemory[procMemIndex]; }
	void Decode(unsigned int instruction);
	void Execution();

public:
	GET_SET_ACCESSOR(ReturnAddress, unsigned int, _registers[31]);
	GET_SET_ACCESSOR(FramePointer,	unsigned int, _registers[30]);
	GET_SET_ACCESSOR(StackPointer,	unsigned int, _registers[29]);
	GET_SET_ACCESSOR(GlobalPointer, unsigned int, _registers[28]);

    friend class Singleton<System>;
};
