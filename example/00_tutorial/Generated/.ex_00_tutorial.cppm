#include <assert.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <obj/Config.h>

export module .ex_00_tutorial;
import std.core;
import std.io;
import std.threading;
import std.regex;

export import mud.obj;
export import mud.math;
export import mud.ui;
export import mud.uio;
export import mud.gfx;
export import mud.edit;
export import mud.gen;

#ifdef MUD_OBJ_LIB
#include <obj/Cls.h>
#include <obj/Strung.h>
#endif

#include <00_tutorial/Generated/Module.h>

//#include <00_tutorial/00_tutorial.h>
