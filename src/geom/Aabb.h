//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/span.h>
#include <math/Vec.h>
#endif
#include <geom/Forward.h>
//#include <geom/Shapes.h>

namespace two
{
	export_ struct refl_ TWO_GEOM_EXPORT Aabb
	{
	public:
		constr_ Aabb();
		constr_ Aabb(const vec3& center, const vec3& extents);

		attr_ vec3 m_center;
		attr_ vec3 m_extents;
		attr_ bool m_empty;

		vec3 bmin() const;
		vec3 bmax() const;

		bool intersects(const Aabb& other) const;

		void merge(const vec3& point);
		void merge(const Aabb& other);

		bool cull(const vec3& point) const;
		bool cull(span<vec3> points) const;
	};

	export_ TWO_GEOM_EXPORT Aabb aabb(const vec3& min, const vec3& max);

	export_ TWO_GEOM_EXPORT Aabb face_aabb(const vec3* vertices);
	export_ TWO_GEOM_EXPORT Aabb face_aabb(const Face3& face);
}
