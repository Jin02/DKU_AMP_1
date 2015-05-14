#pragma once

#include "Common.h"
#include "Instruction.h"

class PipelineStage
{
public:
    enum class State : uint
    {
        Fetch, Decode, Execution, Memory, WriteBack, Stall, Num = Stall
    };
    
private:
    State           _state;
    uint            _pc;

    Instruction*    _instruction;    
    uint            _instructionValue;

	PipelineStage*	_prev1StepPip;
	PipelineStage*	_prev2StepPip;

public:
    PipelineStage() : _instruction(nullptr), _instructionValue(0),
		_prev1StepPip(nullptr), _prev2StepPip(nullptr)
    {
        _state = State::Fetch;
    }
    
    ~PipelineStage()
    {
        
    }
    
public:
    void NextState()
    {
        _state = (State)((uint)_state + 1);
    }
    
    void Cancel()
    {
        _state = State::Stall;
    }

	void Clear()
	{
		_state = State::Fetch;
		_pc = 0;
		SAFE_DELETE(_instruction);
		_instructionValue = 0;
		_prev1StepPip = _prev2StepPip = nullptr;
	}
    
private:
    uint            Fetch();
    void            Decode(uint instValue);
    void            Execution(const PipelineStage* prev2step, const PipelineStage* prev1step);
    void            Memory();
    void            WriteBack();
    
public:
    void            RunStage();
    
public:
    GET_ACCESSOR(State, State, _state);
    GET_ACCESSOR(Instruction, Instruction*, _instruction);
	GET_ACCESSOR(ProgramCounter,  uint, _pc);

	SET_ACCESSOR(Prev2StepPip, PipelineStage*, _prev2StepPip);
	SET_ACCESSOR(Prev1StepPip, PipelineStage*, _prev1StepPip);
};