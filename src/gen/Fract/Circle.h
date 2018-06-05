#pragma once

#ifndef MUD_MODULES
#include <math/Grid.h>
#include <geom/Shape.h>
#endif
#include <gen/Generated/Forward.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ class MUD_GEN_EXPORT Pixircle
	{
	public:
		Pixircle() : radius(0), culled(false) {}

		inline bool	operator < (const Pixircle & rhs) const { return radius <  rhs.radius; }

		size_t index;
		size_t colour;
		size_t radius;
		bool culled;
	};

	export_ class _refl_ MUD_GEN_EXPORT Circlifier
	{
	public:
		_constr_ Circlifier(Image256& image);

		_meth_ std::vector<Circle> compute(const Colour& colour, float scale = 1.f);

		void cull(size_t colour);
		void grow(size_t colour);
		bool cangrow(Pixircle& circle);

	protected:
		Image256& m_image;
		size_t m_size;
		size_t m_last;
		Grid<Pixircle> m_pixircles;
	};
}
