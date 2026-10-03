module;
#include <infra/Cpp20.h>
#include <infra/Config.h>
// third party headers are kept out of the module purview
#include <FastNoise.h>

export module two.noise;

import std;

export import two.infra;
export import two.type;
export import two.math;
export import two.geom;

#include <noise/Api.h>
