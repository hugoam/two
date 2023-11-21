#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_CTX_META_EXPORT
#define TWO_CTX_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_CTX_META_EXPORT two_ctx : public two::Module
	{
	private:
		two_ctx();
		
	public:
		static two_ctx& m() { static two_ctx instance; return instance; }
	};
}

#ifdef TWO_CTX_MODULE
extern "C"
TWO_CTX_META_EXPORT Module& getModule();
#endif
