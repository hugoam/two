#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#include <fract/Forward.h>
//#include <fract/Types.h>

#ifndef TWO_FRACT_REFL_EXPORT
#define TWO_FRACT_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_FRACT_REFL_EXPORT two_fract : public two::Module
	{
	private:
		two_fract();
		
	public:
		static two_fract& m() { static two_fract instance; return instance; }
	};
}

#ifdef TWO_FRACT_MODULE
extern "C"
TWO_FRACT_REFL_EXPORT Module& getModule();
#endif
