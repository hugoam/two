#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#include <tool/Forward.h>
#include <tool/Types.h>

#ifndef MUD_TOOL_REFL_EXPORT
#define MUD_TOOL_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_TOOL_REFL_EXPORT mud_tool : public Module
	{
	private:
		mud_tool();
		
	public:
		static mud_tool& m() { static mud_tool instance; return instance; }
	};
}

#ifdef MUD_TOOL_MODULE
extern "C"
MUD_TOOL_REFL_EXPORT Module& getModule();
#endif
