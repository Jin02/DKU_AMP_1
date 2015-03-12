#include "System.h"
#include <memory.h>

using namespace Core;

System::System()
{
	ClearAllDataRegisters();
}

System::~System()
{
}

void System::ClearAllDataRegisters()
{
	std::fill(_dataRegisters.begin(), _dataRegisters.end(), 0);
}

void System::ClearRegister(unsigned int index)
{
	_dataRegisters[index] = 0;
}
