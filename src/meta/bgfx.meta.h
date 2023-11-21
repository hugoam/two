#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_BGFX_META_EXPORT
#define TWO_BGFX_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_BGFX_META_EXPORT two_bgfx : public two::Module
	{
	private:
		two_bgfx();
		
	public:
		static two_bgfx& m() { static two_bgfx instance; return instance; }
	};
}

#ifdef TWO_BGFX_MODULE
extern "C"
TWO_BGFX_META_EXPORT Module& getModule();
#endif
