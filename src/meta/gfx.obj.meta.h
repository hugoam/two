#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#include <gfx-obj/Forward.h>
//#include <gfx-obj/Types.h>

#ifndef TWO_GFX_OBJ_REFL_EXPORT
#define TWO_GFX_OBJ_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_GFX_OBJ_REFL_EXPORT two_gfx_obj : public two::Module
	{
	private:
		two_gfx_obj();
		
	public:
		static two_gfx_obj& m() { static two_gfx_obj instance; return instance; }
	};
}

#ifdef TWO_GFX_OBJ_MODULE
extern "C"
TWO_GFX_OBJ_REFL_EXPORT Module& getModule();
#endif
