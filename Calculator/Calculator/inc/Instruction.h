#pragma once

#include <vector>
#include "Common.h"

class Instruction
{
public:
    Instruction();
    virtual ~Instruction(void);
    
public:
	//true��� pc���� ����ǰ�, false��� ���� �ȵ�
	//���� ��; j�� branch������ ���ٰ� ���� ��
    virtual void Execution() = 0;
};
