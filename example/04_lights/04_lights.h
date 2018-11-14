//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <mud/Forward.h>

using namespace mud;

struct LightInstance { Colour colour; };

std::vector<LightInstance> create_light_grid(size_t size_x, size_t size_y);

void light_grid(Gnode& parent, array_2d<LightInstance> light_grid, bool moving, LightType light_type, float range = 9.f, float attenuation = 0.4f, float spot_angle = 0.f, float spot_attenuation = 0.f);

#ifdef DOCKBAR
void ex_04_lights(Shell& app, Widget& parent, Dockbar& dockbar);
#else
void ex_04_lights(Shell& app, Widget& parent);
#endif
