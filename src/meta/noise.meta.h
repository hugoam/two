#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_MODULES
#include <noise/Forward.h>
//#include <noise/Types.h>
#endif

#ifndef TWO_NOISE_META_EXPORT
#define TWO_NOISE_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_NOISE_META_EXPORT two_noise : public two::Module
	{
	private:
		two_noise();
		
	public:
		static two_noise& m() { static two_noise instance; return instance; }
	};
}

#ifdef TWO_NOISE_MODULE
extern "C"
TWO_NOISE_META_EXPORT Module& getModule();
#endif
