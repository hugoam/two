#include <assert.h>
#include <stdint.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <obj/Config.h>

export module ${ module.namespace }.${ module.name };
import std.core;
import std.io;
import std.threading;

% for m in module.dependencies :
export import ${ m.namespace }.${ m.name };
% endfor

#ifdef MUD_OBJ_LIB
#include <obj/Cls.h>
#include <obj/Strung.h>
#endif

#include <${ module.subdir }/Generated/Module.h>

% for header in module.headers :
//#include <${ module.subdir }/${ header }>
% endfor
