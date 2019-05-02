#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#include <gfx-edit/Forward.h>
//#include <gfx-edit/Types.h>

#ifndef TWO_GFX_EDIT_REFL_EXPORT
#define TWO_GFX_EDIT_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_GFX_EDIT_REFL_EXPORT two_gfx_edit : public two::Module
	{
	private:
		two_gfx_edit();
		
	public:
		static two_gfx_edit& m() { static two_gfx_edit instance; return instance; }
	};
}

#ifdef TWO_GFX_EDIT_MODULE
extern "C"
TWO_GFX_EDIT_REFL_EXPORT Module& getModule();
#endif
