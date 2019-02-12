#pragma once

#include <mud/tool.h>
#include <mud/refl.h>
#include <mud/infra.h>


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

//#include <tool/Types.h>

#ifndef MUD_TOOL_REFL_EXPORT
#define MUD_TOOL_REFL_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_TOOL_REFL_EXPORT mud_tool : public mud::Module
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


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

namespace mud
{
	export_ template <> inline void to_value(const string& str, mud::ToolState& val) { val = mud::ToolState(enu<mud::ToolState>().value(str.c_str())); };
	export_ template <> inline void to_string(const mud::ToolState& val, string& str) { str = enu<mud::ToolState>().name(uint32_t(val)); };
	
	
}
