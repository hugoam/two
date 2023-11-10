#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_MODULES
#include <pool/Forward.h>
//#include <pool/Types.h>
#endif

#ifndef TWO_POOL_META_EXPORT
#define TWO_POOL_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_POOL_META_EXPORT two_pool : public two::Module
	{
	private:
		two_pool();
		
	public:
		static two_pool& m() { static two_pool instance; return instance; }
	};
}

#ifdef TWO_POOL_MODULE
extern "C"
TWO_POOL_META_EXPORT Module& getModule();
#endif
