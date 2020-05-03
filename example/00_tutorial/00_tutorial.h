//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <frame/Forward.h>
#include <mud/frame.h>

using namespace mud;

export_ enum class refl_ ShapeType : unsigned int
{
	Circle,
	Sphere,
	Cube
};

export_ class refl_ MyObject
{
public:
	constr_ MyObject(ShapeType shape, Colour colour);
	MyObject() {}

	meth_ int method();

	// simple types
	attr_ bool m_visible = true;
	attr_ int m_number = 0;
	attr_ std::string m_name = "";

	// advanced types
	attr_ ShapeType m_shape = ShapeType::Sphere;
	attr_ two::vec3 m_position = Zero3;
	attr_ two::Colour m_colour = Colour::Pink;

	// vector types
	attr_ std::vector<float> m_floats;
};

func_ void foo(int arg);
func_ void bar(MyObject& object);

void ex_00_tutorial_pump(Shell& app, Widget& parent, Dockbar& dockbar);
