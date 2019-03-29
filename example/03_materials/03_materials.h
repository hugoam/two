//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <frame/Forward.h>
#include <infra/StringOps.h>

using namespace mud;

Material& phong_white(GfxSystem& gfx, const string& name = "milky_white");
Material& milky_white(GfxSystem& gfx, const string& name = "milky_white");
Material& mirror(GfxSystem& gfx);
Material& fabric_08(GfxSystem& gfx);
Material& paving_stones_08(GfxSystem& gfx);
Material& paving_stones_11(GfxSystem& gfx);
Material& rocks_01(GfxSystem& gfx);
Material& wood_floor_05(GfxSystem& gfx);

void ex_03_materials(Shell& app, Widget& parent, Dockbar& dockbar);
