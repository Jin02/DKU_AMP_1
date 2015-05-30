#pragma once

#include <array>
#include <vector>

#include "Common.h"
#include "Singleton.h"

#include "Instruction.h"
#include "InstructionController.h"

#include "SOCHashMap.h"
#include <deque>
#include <queue>
#include <list>
#include <functional>

//8192 = 0x8000 / 4
#define MAX_PROCESSOR_MEMORY			8192
#define MAX_BRANCH_PREDICTION_CANCEL	2

class System : public Mips::Singleton<System>
{
public:
	//first value is cycle
	struct InstructionControllerInfo
	{
		uint			 cycle;
		InstructionController	*pip;
		bool			isEnd;
		InstructionControllerInfo() : cycle(0), pip(nullptr), isEnd(false) {}
		~InstructionControllerInfo() {}
	};

private:
    std::array<unsigned int, MAX_PROCESSOR_MEMORY>	_processorMemory;
	std::array<unsigned int, 32>					_registers;
    unsigned int                                    _programCounter;

	unsigned int									_hi, _lo;
    unsigned int                                    _cycle;
    
	SOCHashMap<uint, InstructionController*>				_hashMap;

	std::list<InstructionControllerInfo>					_insts;

	std::queue<uint>                                _removePipelineKeys;

private:
    System(void);
    ~System(void);

private:
	//cancel prev stages.
	void CancelInstructionController(uint currentCycle);

public:
	void Load(const std::string& path);

	void RunCycle(const InstructionControllerInfo& stage);
    void Run();

    inline unsigned int GetDataFromRegister(int index) { return _registers[index]; }
    inline void SetDataToRegister(int index, unsigned int value) { _registers[index] = value; }
    
    unsigned int GetDataFromMemory(int address);
    void SetDataToMemory(int address, unsigned int data);
	bool CheckAllEndInst();
    
public:
	GET_SET_ACCESSOR(HiRegister, unsigned int, _hi);
	GET_SET_ACCESSOR(LoRegister, unsigned int, _lo);

	GET_SET_ACCESSOR(ReturnAddress, unsigned int, _registers[31]);
	GET_SET_ACCESSOR(FramePointer,	unsigned int, _registers[30]);
	GET_SET_ACCESSOR(StackPointer,	unsigned int, _registers[29]);
	GET_SET_ACCESSOR(GlobalPointer, unsigned int, _registers[28]);
    
	GET_ACCESSOR(ProgramCounter, uint, _programCounter);
	void SetProgramCounter(uint v)
	{
		_programCounter = v;
	}

	GET_ACCESSOR(IsPipelineEmpty, bool, _insts.empty());

    friend class Mips::Singleton<System>;
};
