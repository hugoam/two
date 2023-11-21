#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_REFL_META_EXPORT
#define TWO_REFL_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_REFL_META_EXPORT two_refl : public two::Module
	{
	private:
		two_refl();
		
	public:
		static two_refl& m() { static two_refl instance; return instance; }
	};
}

#ifdef TWO_REFL_MODULE
extern "C"
TWO_REFL_META_EXPORT Module& getModule();
#endif
