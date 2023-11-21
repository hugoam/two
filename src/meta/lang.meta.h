#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_LANG_META_EXPORT
#define TWO_LANG_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_LANG_META_EXPORT two_lang : public two::Module
	{
	private:
		two_lang();
		
	public:
		static two_lang& m() { static two_lang instance; return instance; }
	};
}

#ifdef TWO_LANG_MODULE
extern "C"
TWO_LANG_META_EXPORT Module& getModule();
#endif
