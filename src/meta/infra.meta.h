#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#include <infra/Forward.h>
//#include <infra/Types.h>

#ifndef TWO_INFRA_REFL_EXPORT
#define TWO_INFRA_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_INFRA_REFL_EXPORT two_infra : public two::Module
	{
	private:
		two_infra();
		
	public:
		static two_infra& m() { static two_infra instance; return instance; }
	};
}

#ifdef TWO_INFRA_MODULE
extern "C"
TWO_INFRA_REFL_EXPORT Module& getModule();
#endif
