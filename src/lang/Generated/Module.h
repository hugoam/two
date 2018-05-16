
#pragma once

#include <obj/System/System.h>

#include <obj/Generated/Module.h>
        
#include <lang/Generated/Forward.h>
#include <lang/Generated/Types.h>

#include <lang/Lua.h>
#include <lang/Script.h>
#include <lang/Stream.h>
#include <lang/VisualBlocks.h>
#include <lang/VisualScript.h>

namespace mud
{
	class MUD_LANG_EXPORT mudlang : public Module
	{
	private:
		mudlang();

	public:
		static mudlang& module() { static mudlang instance; return instance; }
	};
}

#ifdef MUD_LANG_MODULE
extern "C"
MUD_LANG_EXPORT Module& getModule();
#endif
