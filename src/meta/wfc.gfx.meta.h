#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_MODULES
#include <wfc-gfx/Forward.h>
//#include <wfc-gfx/Types.h>
#endif

#ifndef TWO_WFC_GFX_META_EXPORT
#define TWO_WFC_GFX_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_WFC_GFX_META_EXPORT two_wfc_gfx : public two::Module
	{
	private:
		two_wfc_gfx();
		
	public:
		static two_wfc_gfx& m() { static two_wfc_gfx instance; return instance; }
	};
}

#ifdef TWO_WFC_GFX_MODULE
extern "C"
TWO_WFC_GFX_META_EXPORT Module& getModule();
#endif
