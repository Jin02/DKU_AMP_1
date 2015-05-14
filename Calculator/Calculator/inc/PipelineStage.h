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

    Instruction*    _prev2stepInst;
    Instruction*    _prev1stepInst;
    
    uint            _instructionValue;

public:
    PipelineStage() : _instruction(nullptr), _instructionValue(0),_prev2stepInst(nullptr), _prev1stepInst(nullptr)
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

    GET_SET_ACCESSOR(Prev2StepInst, Instruction*, _prev2stepInst);
    GET_SET_ACCESSOR(Prev1StepInst, Instruction*, _prev1stepInst);
};