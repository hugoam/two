#pragma once

#include <two/infra.h>
#include <two/refl.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

#ifndef TWO_GFX_GLTF_META_EXPORT
#define TWO_GFX_GLTF_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_GFX_GLTF_META_EXPORT two_gfx_gltf : public two::Module
	{
	private:
		two_gfx_gltf();
		
	public:
		static two_gfx_gltf& m() { static two_gfx_gltf instance; return instance; }
	};
}

#ifdef TWO_GFX_GLTF_MODULE
extern "C"
TWO_GFX_GLTF_META_EXPORT Module& getModule();
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	
}
