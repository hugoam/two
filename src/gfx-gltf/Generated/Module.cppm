#include <assert.h>
#include <stdint.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <obj/Config.h>

export module mud.gfxgltf;
import std.core;
import std.io;
import std.threading;

export import mud.obj;
export import mud.math;
export import mud.geom;
export import mud.gfx;

#ifdef MUD_OBJ_LIB
#include <obj/Cls.h>
#include <obj/Strung.h>
#endif

#include <gfx-gltf/Generated/Module.h>

//#include <gfx-gltf/ImporterGltf.h>
