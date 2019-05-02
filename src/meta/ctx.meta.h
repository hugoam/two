#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#include <ctx/Forward.h>
//#include <ctx/Types.h>

#ifndef TWO_CTX_REFL_EXPORT
#define TWO_CTX_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_CTX_REFL_EXPORT two_ctx : public two::Module
	{
	private:
		two_ctx();
		
	public:
		static two_ctx& m() { static two_ctx instance; return instance; }
	};
}

#ifdef TWO_CTX_MODULE
extern "C"
TWO_CTX_REFL_EXPORT Module& getModule();
#endif
