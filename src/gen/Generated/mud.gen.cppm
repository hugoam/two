#include <assert.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <obj/Config.h>

export module mud.gen;
import std.core;
import std.io;
import std.threading;
import std.regex;

export import mud.obj;
export import mud.srlz;
export import mud.math;
export import mud.geom;
export import mud.ui;
export import mud.gfx;
export import mud.edit;

#ifdef MUD_OBJ_LIB
#include <obj/Cls.h>
#include <obj/Strung.h>
#endif

#include <gen/Generated/Module.h>

//#include <gen/Structs.h>
//#include <gen/Fract/Circle.h>
//#include <gen/Fract/Fract.h>
//#include <gen/Noise/Noise.h>
//#include <gen/Wfc/Tileblock.h>
//#include <gen/Wfc/wfc.h>
