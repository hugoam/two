module;
#include <cpp/preimport.h>
#include <infra/Config.h>

export module two.lang;
import std.core;
import std.threading;
import std.regex;

export import two.infra;
export import two.type;
export import two.pool;
export import two.refl;

#include <lang/Api.h>

