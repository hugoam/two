#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#include <gfx-ui/Forward.h>
//#include <gfx-ui/Types.h>

#ifndef TWO_GFX_UI_REFL_EXPORT
#define TWO_GFX_UI_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_GFX_UI_REFL_EXPORT two_gfx_ui : public two::Module
	{
	private:
		two_gfx_ui();
		
	public:
		static two_gfx_ui& m() { static two_gfx_ui instance; return instance; }
	};
}

#ifdef TWO_GFX_UI_MODULE
extern "C"
TWO_GFX_UI_REFL_EXPORT Module& getModule();
#endif
