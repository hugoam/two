module;
#include <cpp/preimport.h>
#include <infra/Config.h>

export module two.bgfx;
import std.core;
import std.threading;
import std.regex;

export import two.infra;
export import two.type;
export import two.math;
export import two.ctx;

#include <bgfx/Api.h>

