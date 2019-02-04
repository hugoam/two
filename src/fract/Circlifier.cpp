//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.fract;
#else
#include <infra/Sort.h>
#include <math/Colour.h>
#include <math/Image256.h>
#include <geom/Shapes.h>
#include <fract/Circlifier.h>
#endif

namespace mud
{
	Circlifier::Circlifier(Image256& image)
		: m_image(image)
		, m_size(image.m_width * image.m_height)
		, m_last(0)
		, m_pixircles(image.m_width, image.m_height, 1)
	{
		for(size_t i = 0; i < m_size; ++i)
		{
			m_pixircles[i].index = i;
			m_pixircles[i].colour = m_image.m_pixels[i];
		}
	}

	vector<Circle> Circlifier::compute(const Colour& colour, float scale)
	{
		size_t colourIndex = m_image.m_palette.find_colour(colour);
		this->grow(colourIndex);
		this->cull(colourIndex);

		vector<Circle> circles;
		for(Pixircle& circle : m_pixircles)
			if(circle.colour == colourIndex && !circle.culled && circle.radius > 0)
			{
				size_t x = m_pixircles.x(circle.index);
				size_t y = m_pixircles.y(circle.index);

				circles.push_back({ circle.radius * scale });
				circles.back().m_center = { float(x) * scale, 0.f, float(y) * scale };
			}

		return circles;
	}

	bool Circlifier::cangrow(Pixircle& circle)
	{
		bool fits = circle.radius < m_pixircles.m_x && circle.radius < m_pixircles.m_y;
		return fits && m_pixircles.visit_near_dist(circle.index, circle.radius + 1, [&](Pixircle& nb) {
			return nb.colour == circle.colour;
		});
	}

	void Circlifier::grow(size_t colour)
	{
		for(Pixircle& circle : m_pixircles)
			if(circle.colour == colour)
				while(cangrow(circle))
					circle.radius = circle.radius + 1;
	}

	void Circlifier::cull(size_t colour)
	{
		vector<Pixircle> sorted(m_pixircles.begin(), m_pixircles.end());
		quicksort<Pixircle>(sorted, [](const Pixircle& lhs, const Pixircle& rhs) { return rhs < lhs; });

		for(Pixircle& circle : sorted)
			if(circle.colour == colour)
				if(!m_pixircles[circle.index].culled)
				{
					m_pixircles.visit_near_2d(circle.index, circle.radius, [](Pixircle& nb) {
						nb.culled = true; return true;
					});
				}
	}
}
