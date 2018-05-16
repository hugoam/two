//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Array.h>
#include <geom/Generated/Forward.h>
#include <geom/Shapes.h>

namespace mud
{
	struct _refl_ MUD_MATH_EXPORT Aabb : public Cube
	{
	public:
		_constr_ Aabb();
		_constr_ Aabb(const vec3& center, const vec3& extents);

		_attr_ _mut_ bool m_null;

		bool intersects(const Aabb& other) const;

		void merge(const vec3& point);
		void merge(const Aabb& other);
		void mergeSafe(const Aabb& other);

		bool cull(const vec3& point) const;
		bool cull(array<vec3> points) const;

		virtual object_ptr<Shape> clone() const;
	};

	inline Aabb min_max_to_aabb(const vec3& min, const vec3& max)
	{
		vec3 extents = (max - min) / 2.f;
		return Aabb(min + extents, extents);
	}

	MUD_MATH_EXPORT Aabb face_aabb(const vec3* vertices);
	MUD_MATH_EXPORT Aabb face_aabb(const Face3& face);
}
