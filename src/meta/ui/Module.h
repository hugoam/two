#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <ui/Forward.h>
#include <ui/Types.h>

#ifndef MUD_UI_REFL_EXPORT
#define MUD_UI_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_UI_REFL_EXPORT mud_ui : public Module
	{
	private:
		mud_ui();
		
	public:
		static mud_ui& m() { static mud_ui instance; return instance; }
	};
}

#ifdef MUD_UI_MODULE
extern "C"
MUD_UI_REFL_EXPORT Module& getModule();
#endif
