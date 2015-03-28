#pragma once

#include <vector>

class Instruction
{
public:
    Instruction();
    virtual ~Instruction(void);
    
public:
	//true라면 pc값이 변경되고, false라면 변경 안됨
	//거의 뭐; j랑 branch때문에 쓴다고 보면 됨
    virtual bool Execution() = 0;
};
