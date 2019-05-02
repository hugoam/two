#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#include <noise/Forward.h>
//#include <noise/Types.h>

#ifndef TWO_NOISE_REFL_EXPORT
#define TWO_NOISE_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_NOISE_REFL_EXPORT two_noise : public two::Module
	{
	private:
		two_noise();
		
	public:
		static two_noise& m() { static two_noise instance; return instance; }
	};
}

#ifdef TWO_NOISE_MODULE
extern "C"
TWO_NOISE_REFL_EXPORT Module& getModule();
#endif
