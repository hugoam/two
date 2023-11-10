#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_MODULES
#include <type/Forward.h>
//#include <type/Types.h>
#endif

#ifndef TWO_TYPE_META_EXPORT
#define TWO_TYPE_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_TYPE_META_EXPORT two_type : public two::Module
	{
	private:
		two_type();
		
	public:
		static two_type& m() { static two_type instance; return instance; }
	};
}

#ifdef TWO_TYPE_MODULE
extern "C"
TWO_TYPE_META_EXPORT Module& getModule();
#endif
