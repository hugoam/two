#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_MODULES
#include <math/Forward.h>
//#include <math/Types.h>
#endif

#ifndef TWO_MATH_META_EXPORT
#define TWO_MATH_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_MATH_META_EXPORT two_math : public two::Module
	{
	private:
		two_math();
		
	public:
		static two_math& m() { static two_math instance; return instance; }
	};
}

#ifdef TWO_MATH_MODULE
extern "C"
TWO_MATH_META_EXPORT Module& getModule();
#endif
