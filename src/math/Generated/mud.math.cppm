#include <assert.h>
#include <stdint.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <obj/Config.h>

export module mud.math;
import std.core;
import std.io;
import std.threading;

export import mud.obj;
export import mud.srlz;

#ifdef MUD_OBJ_LIB
#include <obj/Cls.h>
#include <obj/Strung.h>
#endif

#include <math/Generated/Module.h>

//#include <math/Axes.h>
//#include <math/Axis.h>
//#include <math/Clamp.h>
//#include <math/Colour.h>
//#include <math/Curve.h>
//#include <math/Grid.h>
//#include <math/Image.h>
//#include <math/Interp.h>
//#include <math/Math.h>
//#include <math/Random.h>
//#include <math/Stat.h>
//#include <math/Stream.h>
//#include <math/Structs.h>
//#include <math/Vec.h>
//#include <math/VecJson.h>
//#include <math/VecMath.h>
//#include <math/VecOps.h>
