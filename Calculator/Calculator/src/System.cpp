#include "System.h"

#include <memory.h>
#include <fstream>
#include <string>

System::System()
{
	std::fill(_processorMemory.begin(), _processorMemory.end(), 0);
	std::fill(_registers.begin(), _registers.end(), 0);

	SetStackPointer(0x8000);
	SetReturnAddress(0xffffffff);
}

System::~System()
{
}

void System::Load(const std::string& path)
{
	std::ifstream file(path, std::ios::in | std::ios::binary | std::ios::ate);
    ASSERT_COND_MSG(file.is_open() && file.good(), "Error, strange file");

	int length = file.tellg();
	file.seekg(0, file.beg);

	unsigned char* buffer = new unsigned char[length];
	{
		file.read((char*)buffer, length);
		std::copy((unsigned int*)buffer, (unsigned int*)&buffer[length - sizeof(unsigned int)], _processorMemory.begin());
	}
	delete buffer;

    file.close();

	auto IsLittleEndian = []()
	{
		union{
			int a;
			char b;
		}Test;

		Test.a = 1;
		return Test.b;
	};
	auto LittleEndianToBigEndian = [](unsigned int x)
	{
		return x = ( x >> 24 ) | (( x << 8) & 0x00ff0000 )| ((x >> 8) & 0x0000ff00) | ( x << 24); 
	};

	if(IsLittleEndian())
	{
		for(int i=0; i<length / 4; ++i)
			_processorMemory[i] = LittleEndianToBigEndian(_processorMemory[i]);
	}
}

void System::RunCycle(int procMemIndex)
{

}

void System::Fetch(int procMemIndex)
{

}

void System::Decode(unsigned int instruction)
{
	unsigned int opCode = (instruction & 0xFC000000) >> 26;

	if(opCode == 0) // R
	{
	}
	else if(opCode == (uint)Opcode::Jump || opCode == (uint)Opcode::JumpAndLink) // J
	{
	}
	else // I
	{

	}

}

void System::Execution()
{
}