//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <core/Forward.h>
#include <infra/Array.h>
#include <geom/Shape.h>

#include <vector>

using namespace mud;

struct ShapeInstance { size_t index = 0; };

std::vector<ShapeInstance> create_shape_grid(size_t size_x, size_t size_y, const std::vector<ShapeVar> shapes);

void shape_grid(Gnode& parent, array_2d<ShapeInstance> shape_grid, const Symbol& symbol, const std::vector<ShapeVar> shapes, bool rotate = true, Material* material = nullptr);

void ex_01_shapes(Shell& app, Widget& parent, Dockbar& dockbar);