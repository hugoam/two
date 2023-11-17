#pragma once

#include <two/infra.h>
#include <two/refl.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

#ifndef TWO_GFX_OBJ_META_EXPORT
#define TWO_GFX_OBJ_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_GFX_OBJ_META_EXPORT two_gfx_obj : public two::Module
	{
	private:
		two_gfx_obj();
		
	public:
		static two_gfx_obj& m() { static two_gfx_obj instance; return instance; }
	};
}

#ifdef TWO_GFX_OBJ_MODULE
extern "C"
TWO_GFX_OBJ_META_EXPORT Module& getModule();
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	
}
