#pragma once

#include <two/infra.h>
#include <two/refl.h>


#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

#ifndef TWO_TOOL_META_EXPORT
#define TWO_TOOL_META_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_TOOL_META_EXPORT two_tool : public two::Module
	{
	private:
		two_tool();
		
	public:
		static two_tool& m() { static two_tool instance; return instance; }
	};
}

#ifdef TWO_TOOL_MODULE
extern "C"
TWO_TOOL_META_EXPORT Module& getModule();
#endif

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

namespace two
{
	export_ template <> inline void to_value(const string& str, two::ToolState& val) { val = two::ToolState(enu<two::ToolState>().value(str.c_str())); };
	export_ template <> inline void to_string(const two::ToolState& val, string& str) { str = enu<two::ToolState>().name(uint32_t(val)); };
	
	
}
