//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <frame/Forward.h>
#include <stl/span.h>
#include <geom/Shape.h>

#include <vector>

using namespace two;

struct ShapeInstance { ShapeVar shape; Colour colour; Symbol symbol; };

vector<ShapeInstance> create_shape_grid(size_t size_x, size_t size_y, span<ShapeVar> shapes, bool plain = true);

void shape_grid(Gnode& parent, span2d<ShapeInstance> shape_grid, const Symbol* symbol = nullptr, bool rotate = true, Material* material = nullptr);

void ex_01_shapes(Shell& app, Widget& parent, Dockbar& dockbar);