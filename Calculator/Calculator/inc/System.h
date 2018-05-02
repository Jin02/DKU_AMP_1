#pragma once

#include <array>
#include <vector>

#include "Common.h"
#include "Singleton.h"

#include "Instruction.h"
#include "Pipeline.h"

#include "SOCHashMap.h"
#include <deque>
#include <queue>
#include <list>
#include <functional>

#include "NSetCache.h"

//8192 = 0x8000 / 4
#define MAX_PROCESSOR_MEMORY			0x100000
#define MAX_BRANCH_PREDICTION_CANCEL	2

class System : public Mips::Singleton<System>
{
public:
	//first value is cycle
	struct PipelineInfo
	{
		uint			 cycle;
		Pipeline*		pip;
		bool			isEnd;
		PipelineInfo() : cycle(0), pip(nullptr), isEnd(false) {}
		~PipelineInfo() {}
	};

private:
    std::array<unsigned int, MAX_PROCESSOR_MEMORY>          _processorMemory;
	std::array<unsigned int, 32>                            _registers;
    unsigned int                                            _programCounter;

	unsigned int                                            _hi, _lo;
    unsigned int                                            _cycle;
    
	SOCHashMap<uint, Pipeline*>				                _pipelineMap;
	std::deque<PipelineInfo>								_pipelineQueue;
	std::queue<uint>                                        _removePipelineKeys;

    NSetCache*                                              _cache;
    
private:
    System(void);
    ~System(void);

private:
	//cancel prev stages.
	void CancelInstructionController(uint currentCycle);

public:
    void InitializeCache(uint cacheSize, uint cacheBlockSize, uint nWay, uint hitTime, uint missPenalty);
    void CreateCache(uint cacheSize, uint cacheBlockSize, uint nWay, uint hitTime, uint missPenalty);
	void Load(const std::string& path);

	void RunCycle(const PipelineInfo& stage);
    void Run();

    inline unsigned int GetDataFromRegister(int index) { return _registers[index]; }
    inline void SetDataToRegister(int index, unsigned int value) { _registers[index] = value; }
    
    unsigned int GetDataFromMemory(uint address);
    void SetDataToMemory(uint address, unsigned int data);
	bool CheckAllEndInst();
    
public:
	GET_SET_ACCESSOR(HiRegister, unsigned int, _hi);
	GET_SET_ACCESSOR(LoRegister, unsigned int, _lo);

	GET_SET_ACCESSOR(ReturnAddress, unsigned int, _registers[31]);
	GET_SET_ACCESSOR(FramePointer,	unsigned int, _registers[30]);
	GET_SET_ACCESSOR(StackPointer,	unsigned int, _registers[29]);
	GET_SET_ACCESSOR(GlobalPointer, unsigned int, _registers[28]);
    
	GET_ACCESSOR(ProgramCounter, uint, _programCounter);
	SET_ACCESSOR(ProgramCounter, uint, _programCounter);

	GET_ACCESSOR(IsPipelineEmpty, bool, _pipelineQueue.empty());

    friend class Mips::Singleton<System>;
};
