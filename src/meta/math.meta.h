#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#include <math/Forward.h>
//#include <math/Types.h>

#ifndef TWO_MATH_REFL_EXPORT
#define TWO_MATH_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_MATH_REFL_EXPORT two_math : public two::Module
	{
	private:
		two_math();
		
	public:
		static two_math& m() { static two_math instance; return instance; }
	};
}

#ifdef TWO_MATH_MODULE
extern "C"
TWO_MATH_REFL_EXPORT Module& getModule();
#endif
