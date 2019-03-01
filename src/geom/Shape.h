//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <type/Unique.h>
#include <math/Vec.h>
#endif
#include <geom/Forward.h>

namespace mud
{
	export_ class refl_ MUD_GEOM_EXPORT Shape
	{
	public:
		Shape(Type& type) : m_type(type), m_center(vec3(0.f)) {}
		Shape(Type& type, const vec3& center) : m_type(type), m_center(center) {}
		virtual ~Shape() {}

		Shape(const Shape& other) : m_type(other.m_type) { *this = other; }
		Shape& operator=(const Shape& other) { m_center = other.m_center; return *this; }

		attr_ Type& m_type;
		// @todo add this to reflection need to fix serialization (must either be an argument of child constructors or init members directly)
		vec3 m_center;

		virtual object<Shape> clone() const = 0;
	};

	export_ class refl_ MUD_GEOM_EXPORT ShapeVar
	{
	public:
		constr_ ShapeVar() : m_shape() {}
		constr_ ShapeVar(const Shape& shape) : m_shape(shape.clone()) {}

		ShapeVar(const ShapeVar& other) { *this = other; }
		ShapeVar& operator=(const ShapeVar& other) { if(other.m_shape) m_shape = other.m_shape->clone(); return *this; }

		attr_ Shape& shape() { return *m_shape; }

		operator Shape&() { return *m_shape; }
		operator const Shape&() const { return *m_shape; }
		Shape& operator*() const { return *m_shape; }

		object<Shape> m_shape;
	};
}
