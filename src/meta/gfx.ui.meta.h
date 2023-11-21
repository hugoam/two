#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_GFX_UI_META_EXPORT
#define TWO_GFX_UI_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_GFX_UI_META_EXPORT two_gfx_ui : public two::Module
	{
	private:
		two_gfx_ui();
		
	public:
		static two_gfx_ui& m() { static two_gfx_ui instance; return instance; }
	};
}

#ifdef TWO_GFX_UI_MODULE
extern "C"
TWO_GFX_UI_META_EXPORT Module& getModule();
#endif
