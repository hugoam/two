
#pragma once

#ifndef MUD_MODULES
#include <obj/System/System.h>

#include <obj/Generated/Module.h>
#include <srlz/Generated/Module.h>
#include <math/Generated/Module.h>
#include <geom/Generated/Module.h>
#include <ui/Generated/Module.h>
#include <gfx/Generated/Module.h>
#include <edit/Generated/Module.h>
#endif
        
#include <gen/Generated/Forward.h>
#include <gen/Generated/Types.h>

#include <gen/Structs.h>
#include <gen/Fract/Circle.h>
#include <gen/Fract/Fract.h>
#include <gen/Noise/Noise.h>
#include <gen/Wfc/Tileblock.h>
#include <gen/Wfc/wfc.h>

namespace mud
{
	export_ class MUD_GEN_EXPORT mudgen : public Module
	{
	private:
		mudgen();

	public:
		static mudgen& m() { static mudgen instance; return instance; }
	};
}

#ifdef MUD_GEN_MODULE
extern "C"
MUD_GEN_EXPORT Module& getModule();
#endif
