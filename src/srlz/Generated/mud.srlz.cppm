#include <assert.h>
#include <stdint.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <obj/Config.h>

export module mud.srlz;
import std.core;
import std.io;
import std.threading;

export import mud.obj;

#ifdef MUD_OBJ_LIB
#include <obj/Cls.h>
#include <obj/Strung.h>
#endif

#include <srlz/Generated/Module.h>

//#include <srlz/Serial.h>
