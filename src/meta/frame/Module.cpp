#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.frame;
#else
#include <meta/frame/Module.h>
#endif

#ifndef MUD_MODULES
#include <meta/frame/Convert.h>
#endif
#define MUD_FRAME_REFLECTION_IMPL
#include <meta/frame/Meta.h>

namespace mud
{
	mud_frame::mud_frame()
		: Module("mud::frame", { &mud_gfx::m(), &mud_gfx_ui::m() })
	{
		// setup reflection meta data
		mud_frame_meta(*this);
	}
}

#ifdef MUD_FRAME_MODULE
extern "C"
Module& getModule()
{
		return mud_frame::m();
}
#endif
