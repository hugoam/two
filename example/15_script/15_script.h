//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <mud/Forward.h>
#include <mud/Shell.h>

using namespace mud;

struct ShapeInstance;

export_ class refl_ GameObject
{
public:
	GameObject(const ShapeInstance* shape, Material* material, Colour colour);
	attr_ uint32_t m_index;
	/*attr_ */const ShapeInstance* m_shape;
	attr_ Colour m_colour;
	Material* m_material;
};

void ex_15_script(Shell& app, Widget& parent, Dockbar& dockbar);
