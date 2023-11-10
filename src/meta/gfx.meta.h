#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_MODULES
#include <gfx/Forward.h>
//#include <gfx/Types.h>
#endif

#ifndef TWO_GFX_META_EXPORT
#define TWO_GFX_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_GFX_META_EXPORT two_gfx : public two::Module
	{
	private:
		two_gfx();
		
	public:
		static two_gfx& m() { static two_gfx instance; return instance; }
	};
}

#ifdef TWO_GFX_MODULE
extern "C"
TWO_GFX_META_EXPORT Module& getModule();
#endif
