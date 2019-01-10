#pragma once

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/infra/Module.h>
#include <meta/tree/Module.h>
#include <meta/type/Module.h>
#include <meta/refl/Module.h>
#include <meta/srlz/Module.h>
#include <meta/lang/Module.h>
#include <meta/math/Module.h>
#include <meta/geom/Module.h>
#include <meta/ctx/Module.h>
#include <meta/ui/Module.h>
#include <meta/uio/Module.h>
#include <meta/gfx/Module.h>
#include <meta/gfx-pbr/Module.h>
#include <meta/gfx-ui/Module.h>
#include <meta/gfx-edit/Module.h>
#endif

#include <tool/Forward.h>
#include <tool/Types.h>
#include <tool/Api.h>

#include <meta/tool/Convert.h>

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
