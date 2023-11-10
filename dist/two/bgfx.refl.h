#pragma once

#include <two/bgfx.h>
#include <two/refl.h>
#include <two/infra.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

//#include <bgfx/Types.h>

#ifndef TWO_BGFX_REFL_EXPORT
#define TWO_BGFX_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_BGFX_REFL_EXPORT two_bgfx : public two::Module
	{
	private:
		two_bgfx();
		
	public:
		static two_bgfx& m() { static two_bgfx instance; return instance; }
	};
}

#ifdef TWO_BGFX_MODULE
extern "C"
TWO_BGFX_REFL_EXPORT Module& getModule();
#endif


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	
}
