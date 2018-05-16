//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Unique.h>
#include <math/Vec.h>
#include <geom/Generated/Forward.h>

namespace mud
{
	class _refl_ MUD_MATH_EXPORT Shape
	{
	public:
		Shape(Type& type) : m_type(type), m_center(Zero3) {}
		Shape(Type& type, const vec3& center) : m_type(type), m_center(center) {}

		Shape(const Shape& other) : m_type(other.m_type) { *this = other; }
		Shape& operator=(const Shape& other) { m_center = other.m_center; return *this; }

		_attr_ Type& m_type;
		// @todo add this to reflection need to fix serialization (must either be an argument of child constructors or init members directly)
		vec3 m_center;

		virtual object_ptr<Shape> clone() const = 0;
	};

	struct _refl_ MUD_MATH_EXPORT ShapeVar
	{
	public:
		_constr_ ShapeVar() : m_shape() {}
		_constr_ ShapeVar(const Shape& shape) : m_shape(shape.clone()) {}

		ShapeVar(const ShapeVar& other) { *this = other; }
		ShapeVar& operator=(const ShapeVar& other) { if(other.m_shape) m_shape = other.m_shape->clone(); return *this; }

		_attr_ Shape& shape() { return *m_shape; }

		operator Shape&() { return *m_shape; }
		operator const Shape&() const { return *m_shape; }
		Shape& operator*() const { return *m_shape; }

		object_ptr<Shape> m_shape;
	};
}
