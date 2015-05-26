#pragma once

#include <array>
#include <vector>

#include "Common.h"
#include "Singleton.h"

#include "Instruction.h"
#include "PipelineStage.h"

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
	struct PipelineStageInfo
	{
		uint			 cycle;
		PipelineStage	*pip;
		bool			isEnd;
		PipelineStageInfo() : cycle(0), pip(nullptr), isEnd(false) {}
		~PipelineStageInfo() {}
	};

private:
    std::array<unsigned int, MAX_PROCESSOR_MEMORY>	_processorMemory;
	std::array<unsigned int, 32>					_registers;
    unsigned int                                    _programCounter;

	unsigned int									_hi, _lo;
    unsigned int                                    _cycle;
    
	SOCHashMap<uint, PipelineStage*>				_hashMap;

	std::list<PipelineStageInfo>					_insts;

	std::queue<uint>                                _removePipelineKeys;

private:
    System(void);
    ~System(void);

private:
	//cancel prev stages.
	void CancelPipelineStage(uint currentCycle);

public:
    void Load(const std::string& path);

	void RunCycle(const PipelineStageInfo& stage);
    void Run(const std::function<void(const PipelineStageInfo& stageInfo, uint indexInList)>& visualizationFunc);

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
    
    GET_SET_ACCESSOR(ProgramCounter, unsigned int, _programCounter);

	GET_ACCESSOR(IsPipelineEmpty, bool, _insts.empty());

    friend class Mips::Singleton<System>;
};
