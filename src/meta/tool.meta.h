#pragma once

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef TWO_MODULES
#include <tool/Forward.h>
//#include <tool/Types.h>
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
