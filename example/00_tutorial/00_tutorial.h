//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <mud/Forward.h>

using namespace mud;

export_ enum class _refl_ ShapeType : unsigned int
{
	Circle,
	Sphere,
	Cube
};

export_ class _refl_ MyObject
{
public:
	_constr_ MyObject(ShapeType shape, Colour colour);
	MyObject() {}

	_meth_ int method();

	// simple types
	_attr_ _mut_ bool m_visible = true;
	_attr_ _mut_ int m_number = 0;
	_attr_ _mut_ std::string m_name = "";

	// advanced types
	_attr_ _mut_ ShapeType m_shape = ShapeType::Sphere;
	_attr_ _mut_ mud::vec3 m_position = Zero3;
	_attr_ _mut_ mud::Colour m_colour = Colour::Pink;

	// vector types
	_attr_ _mut_ std::vector<float> m_floats;
};

_func_ void foo(int arg);
_func_ void bar(MyObject& object);

void ex_00_tutorial_pump(Shell& app, Widget& parent, Dockbar& dockbar);
