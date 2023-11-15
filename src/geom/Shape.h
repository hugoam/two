//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <type/Unique.h>
#include <math/Vec.h>
#endif
#include <geom/Forward.h>

namespace two
{
	export_ class refl_ TWO_GEOM_EXPORT Shape
	{
	public:
		inline Shape(Type& type) : m_type(type), m_center(vec3(0.f)) {}
		inline Shape(Type& type, const vec3& center) : m_type(type), m_center(center) {}
		virtual ~Shape() {}

		inline Shape(const Shape& other) : m_type(other.m_type) { *this = other; }
		inline Shape& operator=(const Shape& other) { m_center = other.m_center; return *this; }

		attr_ Type& m_type;
		// @todo add this to reflection need to fix serialization (must either be an argument of child constructors or init members directly)
		vec3 m_center;

		virtual object<Shape> clone() const = 0;
	};

	export_ class refl_ TWO_GEOM_EXPORT ShapeVar
	{
	public:
		constr_ inline ShapeVar() : m_shape() {}
		constr_ inline ShapeVar(const Shape& shape) : m_shape(shape.clone()) {}

		inline ShapeVar(const ShapeVar& other) { *this = other; }
		inline ShapeVar& operator=(const ShapeVar& other) { if(other.m_shape) m_shape = other.m_shape->clone(); return *this; }

		attr_ inline Shape& shape() { return *m_shape; }

		inline operator Shape&() { return *m_shape; }
		inline operator const Shape&() const { return *m_shape; }
		inline Shape& operator*() const { return *m_shape; }

		object<Shape> m_shape;
	};
}
