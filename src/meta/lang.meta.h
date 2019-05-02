#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#include <lang/Forward.h>
//#include <lang/Types.h>

#ifndef TWO_LANG_REFL_EXPORT
#define TWO_LANG_REFL_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_LANG_REFL_EXPORT two_lang : public two::Module
	{
	private:
		two_lang();
		
	public:
		static two_lang& m() { static two_lang instance; return instance; }
	};
}

#ifdef TWO_LANG_MODULE
extern "C"
TWO_LANG_REFL_EXPORT Module& getModule();
#endif
