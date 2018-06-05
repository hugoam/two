
#pragma once

#ifndef MUD_MODULES
#include <obj/System/System.h>

#include <obj/Generated/Module.h>
#endif
        
#include <math/Generated/Forward.h>
#include <math/Generated/Types.h>

#include <math/Axes.h>
#include <math/Axis.h>
#include <math/Clamp.h>
#include <math/Colour.h>
#include <math/Curve.h>
#include <math/Grid.h>
#include <math/Image.h>
#include <math/Interp.h>
#include <math/Math.h>
#include <math/Random.h>
#include <math/Stat.h>
#include <math/Stream.h>
#include <math/Structs.h>
#include <math/Vec.h>
#include <math/VecJson.h>
#include <math/VecMath.h>
#include <math/VecOps.h>

namespace mud
{
	export_ class MUD_MATH_EXPORT mudmath : public Module
	{
	private:
		mudmath();

	public:
		static mudmath& m() { static mudmath instance; return instance; }
	};
}

#ifdef MUD_MATH_MODULE
extern "C"
MUD_MATH_EXPORT Module& getModule();
#endif
