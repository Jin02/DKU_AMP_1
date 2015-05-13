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

public:
    PipelineStage() : _instruction(nullptr), _instructionValue(0)
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
    void            RunStage(const PipelineStage* prev2step, const PipelineStage* prev1step);
    
public:
    GET_ACCESSOR(State, State, _state);
    GET_ACCESSOR(Instruction, Instruction*, _instruction);
};