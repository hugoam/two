#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_MODULES
#include <gfx-pbr/Forward.h>
//#include <gfx-pbr/Types.h>
#endif

#ifndef TWO_GFX_PBR_META_EXPORT
#define TWO_GFX_PBR_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_GFX_PBR_META_EXPORT two_gfx_pbr : public two::Module
	{
	private:
		two_gfx_pbr();
		
	public:
		static two_gfx_pbr& m() { static two_gfx_pbr instance; return instance; }
	};
}

#ifdef TWO_GFX_PBR_MODULE
extern "C"
TWO_GFX_PBR_META_EXPORT Module& getModule();
#endif
