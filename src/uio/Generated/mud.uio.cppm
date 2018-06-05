#include <assert.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <obj/Config.h>

export module mud.uio;
import std.core;
import std.io;
import std.threading;
import std.regex;

export import mud.obj;
export import mud.lang;
export import mud.ui;

#ifdef MUD_OBJ_LIB
#include <obj/Cls.h>
#include <obj/Strung.h>
#endif

#include <uio/Generated/Module.h>

//#include <uio/Dropper.h>
//#include <uio/Unode.h>
//#include <uio/Edit/Canvas.h>
//#include <uio/Edit/Indexer.h>
//#include <uio/Edit/Injector.h>
//#include <uio/Edit/Inspector.h>
//#include <uio/Edit/Method.h>
//#include <uio/Edit/Reflection.h>
//#include <uio/Edit/Script.h>
//#include <uio/Edit/Section.h>
//#include <uio/Edit/Structure.h>
//#include <uio/Edit/UiEdit.h>
//#include <uio/Edit/Value.h>
