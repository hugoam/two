#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_MODULES
#include <infra/Forward.h>
//#include <infra/Types.h>
#endif

#ifndef TWO_INFRA_META_EXPORT
#define TWO_INFRA_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_INFRA_META_EXPORT two_infra : public two::Module
	{
	private:
		two_infra();
		
	public:
		static two_infra& m() { static two_infra instance; return instance; }
	};
}

#ifdef TWO_INFRA_MODULE
extern "C"
TWO_INFRA_META_EXPORT Module& getModule();
#endif
