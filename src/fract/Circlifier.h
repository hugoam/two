#pragma once

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <math/Grid.h>
#include <geom/Shape.h>
#endif
#include <fract/Forward.h>

namespace mud
{
	export_ class MUD_FRACT_EXPORT Pixircle
	{
	public:
		Pixircle() : radius(0), culled(false) {}

		inline bool	operator < (const Pixircle & rhs) const { return radius <  rhs.radius; }

		size_t index;
		size_t colour;
		size_t radius;
		bool culled;
	};

	export_ class refl_ MUD_FRACT_EXPORT Circlifier
	{
	public:
		constr_ Circlifier(Image256& image);

		meth_ vector<Circle> compute(const Colour& colour, float scale = 1.f);

		void cull(size_t colour);
		void grow(size_t colour);
		bool cangrow(Pixircle& circle);

	protected:
		Image256& m_image;
		size_t m_size;
		size_t m_last;
		vector2d<Pixircle> m_pixircles;
	};
}
