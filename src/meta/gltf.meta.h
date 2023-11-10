#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_MODULES
#include <gltf/Forward.h>
//#include <gltf/Types.h>
#endif

#ifndef TWO_GLTF_META_EXPORT
#define TWO_GLTF_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_GLTF_META_EXPORT two_gltf : public two::Module
	{
	private:
		two_gltf();
		
	public:
		static two_gltf& m() { static two_gltf instance; return instance; }
	};
}

#ifdef TWO_GLTF_MODULE
extern "C"
TWO_GLTF_META_EXPORT Module& getModule();
#endif
