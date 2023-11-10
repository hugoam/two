module;
#include <cpp/preimport.h>
#include <infra/Config.h>

export module two.ecs;
import std.core;
import std.threading;
import std.regex;

export import two.infra;
export import two.pool;
export import two.type;

#include <ecs/Api.h>

