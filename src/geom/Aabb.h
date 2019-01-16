//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <infra/Array.h>
#endif
#include <geom/Forward.h>
#include <geom/Shapes.h>

namespace mud
{
	export_ struct refl_ MUD_GEOM_EXPORT Aabb : public Cube
	{
	public:
		constr_ Aabb();
		constr_ Aabb(const vec3& center, const vec3& extents);

		attr_ bool m_empty;

		vec3 bmin() const { return m_center - m_extents; }
		vec3 bmax() const { return m_center + m_extents; }

		bool intersects(const Aabb& other) const;

		void merge(const vec3& point);
		void merge(const Aabb& other);
		void mergeSafe(const Aabb& other);

		bool cull(const vec3& point) const;
		bool cull(array<vec3> points) const;

		virtual object<Shape> clone() const;
	};

	export_ inline Aabb aabb(const vec3& min, const vec3& max)
	{
		vec3 extents = (max - min) / 2.f;
		return Aabb(min + extents, extents);
	}

	export_ MUD_GEOM_EXPORT Aabb face_aabb(const vec3* vertices);
	export_ MUD_GEOM_EXPORT Aabb face_aabb(const Face3& face);
}
