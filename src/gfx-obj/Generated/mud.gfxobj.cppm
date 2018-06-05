#include <assert.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <obj/Config.h>

export module mud.gfxobj;
import std.core;
import std.io;
import std.threading;
import std.regex;

export import mud.obj;
export import mud.srlz;
export import mud.math;
export import mud.geom;
export import mud.gfx;

#ifdef MUD_OBJ_LIB
#include <obj/Cls.h>
#include <obj/Strung.h>
#endif

#include <gfx-obj/Generated/Module.h>

//#include <gfx-obj/ImporterObj.h>
