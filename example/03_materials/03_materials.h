//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <mud/Forward.h>
#include <infra/String.h>

using namespace mud;

Material& milky_white(GfxSystem& gfx_system, const string& name = "milky_white");
Material& mirror(GfxSystem& gfx_system);
Material& fabric_08(GfxSystem& gfx_system);
Material& paving_stones_08(GfxSystem& gfx_system);
Material& paving_stones_11(GfxSystem& gfx_system);
Material& rocks_01(GfxSystem& gfx_system);
Material& wood_floor_05(GfxSystem& gfx_system);

void ex_03_materials(Shell& app, Widget& parent, Dockbar& dockbar);
