#pragma once

#include <two/refl.h>
#include <two/wfc.gfx.h>
#include <two/infra.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

//#include <wfc-gfx/Types.h>

#ifndef TWO_WFC_GFX_REFL_EXPORT
#define TWO_WFC_GFX_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_WFC_GFX_REFL_EXPORT two_wfc_gfx : public two::Module
	{
	private:
		two_wfc_gfx();
		
	public:
		static two_wfc_gfx& m() { static two_wfc_gfx instance; return instance; }
	};
}

#ifdef TWO_WFC_GFX_MODULE
extern "C"
TWO_WFC_GFX_REFL_EXPORT Module& getModule();
#endif


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	
}
