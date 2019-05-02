#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#include <wfc/Forward.h>
//#include <wfc/Types.h>

#ifndef TWO_WFC_REFL_EXPORT
#define TWO_WFC_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_WFC_REFL_EXPORT two_wfc : public two::Module
	{
	private:
		two_wfc();
		
	public:
		static two_wfc& m() { static two_wfc instance; return instance; }
	};
}

#ifdef TWO_WFC_MODULE
extern "C"
TWO_WFC_REFL_EXPORT Module& getModule();
#endif
