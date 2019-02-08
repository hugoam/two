#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <lang/Forward.h>
//#include <lang/Types.h>

#ifndef MUD_LANG_REFL_EXPORT
#define MUD_LANG_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_LANG_REFL_EXPORT mud_lang : public mud::Module
	{
	private:
		mud_lang();
		
	public:
		static mud_lang& m() { static mud_lang instance; return instance; }
	};
}

#ifdef MUD_LANG_MODULE
extern "C"
MUD_LANG_REFL_EXPORT Module& getModule();
#endif
