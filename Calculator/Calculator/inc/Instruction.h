#pragma once

#include <vector>

class Instruction
{
public:
    Instruction();
    virtual ~Instruction(void);
    
public:
	//true��� pc���� ����ǰ�, false��� ���� �ȵ�
	//���� ��; j�� branch������ ���ٰ� ���� ��
    virtual bool Execution() = 0;
};
