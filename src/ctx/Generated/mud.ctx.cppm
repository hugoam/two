#include <assert.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <obj/Config.h>

export module mud.ctx;
import std.core;
import std.io;
import std.threading;
import std.regex;

export import mud.obj;
export import mud.srlz;
export import mud.math;

#ifdef MUD_OBJ_LIB
#include <obj/Cls.h>
#include <obj/Strung.h>
#endif

#include <ctx/Generated/Module.h>

//#include <ctx/Context.h>
//#include <ctx/ControlNode.h>
//#include <ctx/InputDevice.h>
//#include <ctx/InputDispatcher.h>
//#include <ctx/InputEvent.h>
//#include <ctx/KeyCode.h>
