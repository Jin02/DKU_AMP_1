#pragma once

#include <assert.h>

#define SET_ACCESSOR(name, type, variable)	inline void Set##name(type t)	{ variable = t; }
#define GET_ACCESSOR(name, type, variable)	inline type Get##name() const	{ return variable; }
#define GET_SET_ACCESSOR(name, type, variable)\
	SET_ACCESSOR(name, type, variable) GET_ACCESSOR(name, type, variable)

#define SAFE_DELETE(x) { if(x){ delete x; x = nullptr; } }
#define SAFE_DELETE_ARRAY(x) { if(x){ delete[] x; x = nullptr; } }

#define ASSERT_MSG(MSG) assert(!MSG)
#define ASSERT_COND_MSG(CONDITION, MSG) if(!(CONDITION)){assert(!MSG);}

#define USE_OUTPUT_DUMP_LOG

typedef unsigned int uint;

enum class Opcode : unsigned int
{
	AddImmediate					= 0x08,
	AddImmediateUnsigned			= 0x09,
	AndImmediate					= 0x0c,
	BranchOnEqual					= 0x04,
	BranchOnNotEqual				= 0x05,
	Jump							= 0x02,
	JumpAndLink						= 0x03,
	LoadByteUnsigned				= 0x24,
	LoadHalfwordUnsigned			= 0x25,
	LoadLinked						= 0x30,
	LoadUpperImmediate				= 0x0f,
	LoadWord						= 0x23,
	OrImmediate						= 0x0d,
	SetLessThanImmediate			= 0x0a,
	SetLessThanImmediateUnsigned	= 0x0b,
	StoreByte						= 0x28,
	StoreConditional				= 0x38,
	StoreHalfword					= 0x29,
	StoreWord                       = 0x2b,
	Add								= 0x00,
	AddUnsigned						= 0x00,
	And								= 0x00,
	JumpRegister					= 0x00,
	Nor								= 0x00,
	Or								= 0x00,
	SetLessThan						= 0x00,
	SetLessThanUnsigned				= 0x00,
	ShiftLeftLogical				= 0x00,
	ShiftRightLogical				= 0x00,
	Subtract						= 0x00,
	SubtractUnsigned				= 0x00,
};

enum class Funct : unsigned int
{
	Add						= 0x20,
	AddUnsigned				= 0x21,
	And						= 0x24,
	JumpRegister			= 0x08,
	Nor						= 0x27,
	Or						= 0x25,
	SetLessThan				= 0x2a,
	SetLessThanUnsigned		= 0x2b,
	ShiftLeftLogical		= 0x00,
	ShiftRightLogical		= 0x02,
	Subtract				= 0x22,
	SubtractUnsigned		= 0x23,
};