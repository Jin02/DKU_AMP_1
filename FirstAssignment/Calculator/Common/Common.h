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