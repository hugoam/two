#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#include <geom/Forward.h>
//#include <geom/Types.h>

#ifndef TWO_GEOM_REFL_EXPORT
#define TWO_GEOM_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_GEOM_REFL_EXPORT two_geom : public two::Module
	{
	private:
		two_geom();
		
	public:
		static two_geom& m() { static two_geom instance; return instance; }
	};
}

#ifdef TWO_GEOM_MODULE
extern "C"
TWO_GEOM_REFL_EXPORT Module& getModule();
#endif
