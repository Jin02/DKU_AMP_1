#pragma once

#include "Common.h"
#include "Instruction.h"

class InstructionController
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

	InstructionController*	_prev1StepPip;
	InstructionController*	_prev2StepPip;

	bool			_isCancel;

public:
    InstructionController();
    ~InstructionController();
    
public:
    void NextState();
    void Cancel();
    void Clear();
    
public:
    uint            Fetch();
	void            Decode(uint instValue);
    void            Execution(const InstructionController* prev2step, const InstructionController* prev1step);
    void            Memory(const InstructionController* prev2step, const InstructionController* prev1step);
    void            WriteBack();
    
public:
    void            RunStage();
    
public:
    GET_ACCESSOR(State, State, _state);
    GET_ACCESSOR(Instruction, Instruction*, _instruction);
	//GET_SET_ACCESSOR(ProgramCounter,  uint, _pc);
	GET_ACCESSOR(ProgramCounter, uint, _pc);
	void SetProgramCounter(uint v)
	{
		_pc = v;
	}

	SET_ACCESSOR(Prev2StepPip, InstructionController*, _prev2StepPip);
	SET_ACCESSOR(Prev1StepPip, InstructionController*, _prev1StepPip);

	GET_ACCESSOR(IsCancel, bool, _isCancel);
};