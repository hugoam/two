module;
#include <infra/Cpp20.h>
#include <infra/Config.h>

export module two.infra;

// clang only finds the std operators by argument-dependent lookup when std is visible, so it's
// re-exported to the units importing two, like the headers re-exported by the .ixx interface
export import std;

#include <infra/Api.h>
