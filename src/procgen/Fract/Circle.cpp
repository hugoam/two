//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <algorithm>
#endif

#ifdef MUD_MODULES
module mud.procgen;
#else
#include <math/Colour.h>
#include <math/Image.h>
#include <geom/Shapes.h>
#include <procgen/Fract/Circle.h>
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

	std::vector<Circle> Circlifier::compute(const Colour& colour, float scale)
	{
		size_t colourIndex = m_image.m_palette.findColour(colour);
		this->grow(colourIndex);
		this->cull(colourIndex);

		std::vector<Circle> circles;
		for(Pixircle& circle : m_pixircles)
			if(circle.colour == colourIndex && !circle.culled && circle.radius > 0)
			{
				size_t x = m_pixircles.x(circle.index);
				size_t y = m_pixircles.y(circle.index);

				circles.emplace_back(circle.radius * scale);
				circles.back().m_center = { float(x) * scale, 0.f, float(y) * scale };
			}

		return circles;
	}

	bool Circlifier::cangrow(Pixircle& circle)
	{
		bool fits = circle.radius < m_pixircles.m_x && circle.radius < m_pixircles.m_y;
		return fits && m_pixircles.iterateDistNeighbours(circle.index, circle.radius + 1, [&](Pixircle& nb) {
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
		std::vector<Pixircle> sorted(m_pixircles.begin(), m_pixircles.end());
		std::sort(sorted.begin(), sorted.end(), [](Pixircle& lhs, Pixircle& rhs) { return rhs < lhs; });

		for(Pixircle& circle : sorted)
			if(circle.colour == colour)
				if(!m_pixircles[circle.index].culled)
				{
					m_pixircles.iterateFlatNeighbours(circle.index, circle.radius, [](Pixircle& nb) {
						nb.culled = true; return true;
					});
				}
	}
}
