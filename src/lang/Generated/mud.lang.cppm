#include <assert.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <obj/Config.h>

export module mud.lang;
import std.core;
import std.io;
import std.threading;
import std.regex;

export import mud.obj;

#ifdef MUD_OBJ_LIB
#include <obj/Cls.h>
#include <obj/Strung.h>
#endif

#include <lang/Generated/Module.h>

//#include <lang/Lua.h>
//#include <lang/Script.h>
//#include <lang/Stream.h>
//#include <lang/VisualBlocks.h>
//#include <lang/VisualScript.h>
