#pragma once

#include <two/snd.h>
#include <two/refl.h>
#include <two/infra.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

//#include <snd/Types.h>

#ifndef TWO_SND_REFL_EXPORT
#define TWO_SND_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_SND_REFL_EXPORT two_snd : public two::Module
	{
	private:
		two_snd();
		
	public:
		static two_snd& m() { static two_snd instance; return instance; }
	};
}

#ifdef TWO_SND_MODULE
extern "C"
TWO_SND_REFL_EXPORT Module& getModule();
#endif


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	
}
