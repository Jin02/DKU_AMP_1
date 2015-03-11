#pragma once

#include <array>

#include "Common.h"
#include "SingleTon.h"

#define MAX_DATA_REGISTER_NUM 32

namespace Core
{
	class System : public Singleton<System>
	{
	private:
		std::array<unsigned int, MAX_DATA_REGISTER_NUM>		_dataRegisters;

	private:
		System(void);
		~System(void);

	public:
		void ClearAllDataRegisters();
		void ClearRegister(unsigned int index);

		inline void	SetDataToRegister(unsigned int index, unsigned int data);
		inline unsigned int GetDataFromRegister(unsigned int index);
	};
}