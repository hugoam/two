#include <mud/geom.h>
#include <mud/math.h>
#include <mud/fract.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifdef MUD_MODULES
module mud.fract;
#else
#endif

#include <algorithm>

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
		std::sort(sorted.begin(), sorted.end(), [](Pixircle& lhs, Pixircle& rhs) { return rhs < lhs; });

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

#ifndef MUD_CPP_20
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#endif

#ifdef MUD_MODULES
module mud.fract;
#else
#endif

#define PI 3.14159f
#define COEFF_TRANS 1.5f
#define COEFF_ROTATION 15
#define COEFF_V 0.004

#ifndef MUD_CPP_20
#include <cstdio>
#include <stl/string.h>
#endif

float rnd_float()
{
	return (float)rand() / RAND_MAX;
	//rand()/RAND_MAX;
}

namespace mud
{
	void generate_fract(uvec2 resolution, const Pattern& pattern, Image256& output_image)
	{
		Fract fract;
		fract.generate();

		fract.render_whole(pattern, resolution, output_image);
	}

	FractTab::FractTab()
		: delta_a(0.f)
		, delta_b(0.f)
		, delta_c(0.f)
	{}

	void FractTab::generate(int index)
	{
		i = index;

		dist = rnd_float() / 2.f;

		angle_p = rnd_float() * PI * 2.f;

		angle_t = rnd_float() * PI * 2.f;
		angle_offset_t = (.5f - rnd_float())*PI*.025f*COEFF_TRANS;
		angle_t = angle_t + angle_offset_t;

		angle_a = rnd_float() * PI * 2.f;
		angle_offset_a = (.5f - rnd_float())*PI*.0025f*.5f*COEFF_TRANS;
		angle_a = angle_a + angle_offset_a * .31f;

		this->setnormal();
	}

	void FractTab::calcnormal()
	{
		//float ptt = dist + cos(angle_t)*.01f*dist * dist;
		//float pa = angle_p + cos(angle_a)*.05f;

		normal_c = cos(angle_t);
		//normal_c = 1 / (sqrt(1 + ptt*ptt)); // length of normal Z component = c
		normal_ab = sqrt(1 - normal_c*normal_c); // length of normal XY component = ab

		normal_a = normal_ab*cos(angle_a);
		normal_b = normal_ab*sin(angle_a);

		//normal_a = normal_ab*cos(pa);
		//normal_b = normal_ab*sin(pa);

		/*printf("AXIS" );
		printf(cos(angle_t) );
		printf("dist : " << dist );
		printf("normal_c : " << normal_c );
		printf("ptt : " << ptt );
		printf("normal_ab : " << normal_ab << ", ptt/pt : " << ptt / dist );*/

	}

	void FractTab::setnormal()
	{
		this->calcnormal();
		
		a = normal_a;
		b = normal_b;
		c = normal_c;
		
		normal = vec3(a, b, 0.f);
		if(normal == Zero3)
			normal = X3;
		else
			normal = normalize(normal);

		origin = normal * dist;
	}

	void FractTab::genca(int steps)
	{
		// nouveaux param
		dist = (i + 10)*rnd_float() / 2;
		angle_a = rnd_float() * PI * 2;
		// élab premier pas de nvx param (+it inut??)

		this->calcnormal();

		//calcul des deltas...
		delta_a = (normal_a - a) / steps;
		delta_b = (normal_b - b) / steps;
		delta_c = (normal_c - c) / steps;
	}

	void FractTab::transinormal()
	{
		//normal += delta;
		//normal.normalize();

		a += delta_a;
		b += delta_b;
		c += delta_c;
		float length = sqrtf(a*a + b*b + c*c);
		a /= length;
		b /= length;
		c /= length;
	}

	Fract::Fract(size_t num_tabs)
		: m_update(0)
	{
		int seed = int(time(nullptr));
		srand(seed);

		this->generate(num_tabs);
	}

	void Fract::generate(size_t num_tabs)
	{
		m_num_tabs = num_tabs;

		m_tabs.clear();

		m_tabs.resize(num_tabs);

		for(size_t i = 0; i < m_tabs.size(); ++i)
			m_tabs[i].generate(int(i));

		m_update++;
	}

	void Fract::regen()
	{
		for(size_t i = 0; i < m_tabs.size(); ++i)
			m_tabs[i].generate(int(i));

		m_update++;
	}

	int Fract::inverse_point(float& x, float& y)
	{
		float cx, cy, h;

		int numReflects = 0;
		for(FractTab& tab : m_tabs)
		{
			h = ((x - tab.origin.x) * tab.normal.x + (y - tab.origin.y) * tab.normal.y) * 2;

			cx = x - tab.normal.x * h;
			cy = y - tab.normal.y * h;

			if(cx*cx + cy*cy < x*x + y*y)
			{
				x = cx;
				y = cy;
				++numReflects;
			}
		}

		return numReflects;
	}

	uint32_t Fract::inverse_colour(int x, int y, const Rect& rect, const Pattern& pattern, Image256& image)
	{
		float ox = float(x) / float(image.m_width) * rect.m_size.x + rect.m_position.x - 0.5f;
		float oy = float(y) / float(image.m_height) * rect.m_size.y + rect.m_position.y - 0.5f;

		float px = ox;
		float py = oy;

		int num_reflects = this->inverse_point(px, py);

		px *= image.m_width / rect.m_size.x;
		py *= image.m_height / rect.m_size.y;

		uint32_t color = pattern.sample(px, py, float(num_reflects));

		return color;
	}

	void Fract::render(const Rect& rect, const Pattern& pattern, uvec2 resolution, Image256& image)
	{
		image.resize(uint16_t(resolution.x), uint16_t(resolution.y));

		image.m_palette = pattern.m_palette;

		size_t index = 0;
		for(uint y = 0; y < resolution.y; ++y)
			for(uint x = 0; x < resolution.x; ++x, ++index)
				image.m_pixels[index] = this->inverse_colour(x, y, rect, pattern, image);

		++m_update;
	}

	void Fract::render_whole(const Pattern& pattern, uvec2 resolution, Image256& image)
	{
		Rect rect(0.f, 0.f, 1.f, 1.f);
		this->render(rect, pattern, resolution, image);
	}

	void Fract::render_grid(uvec2 subdiv, const Pattern& pattern, uvec2 resolution, vector<Image256>& images)
	{
		for(size_t y = 0; y < subdiv.y; ++y)
			for(size_t x = 0; x < subdiv.x; ++x)
			{
				Rect rect(float(x) / float(subdiv.x), float(y) / float(subdiv.y), 1.f / float(subdiv.x), 1.f / float(subdiv.y));
				images.emplace_back();
				this->render(rect, pattern, resolution, images.back());
			}
	}

	Pattern::Pattern()
		: m_sampler()
	{}

	Pattern::Pattern(Palette palette, PatternSampling sampling, float precision, size_t step)
		: m_palette(palette)
		, m_precision(precision)
		, m_step(step)
	{
		if(sampling == PatternSampling::X)
			m_sampler = sampleX;
		else if(sampling == PatternSampling::XY)
			m_sampler = sampleXY;
		else if(sampling == PatternSampling::Depth)
			m_sampler = sampleZ;
	}

	uint32_t Pattern::sample(float x, float y, float depth) const
	{
		return m_sampler(*this, x, y, depth);
	}

	uint32_t sampleX(const Pattern& pattern, float x, float y, float depth)
	{
		UNUSED(x); UNUSED(depth);
		//int px = int(x * pattern.m_precision);
		int py = int(y * pattern.m_precision);
		
		int colourId = int(py);
		
		uint32_t color = colourId;
		color = color % pattern.m_palette.m_colours.size();

		return color;
	}

	uint32_t sampleZ(const Pattern& pattern, float x, float y, float depth)
	{
		UNUSED(x); UNUSED(y);
		uint32_t color = uint32_t(depth);
		color = color % pattern.m_palette.m_colours.size();

		return color;
	}

	uint32_t sampleXY(const Pattern& pattern, float x, float y, float depth)
	{
		return sampleX(pattern, x, y, depth);
	}

	FractSample::FractSample(Fract& fract, const Rect& rect, uvec2 resolution)
		: m_fract(fract)
		, m_rect(rect)
		, m_resolution(resolution)
	{}

	void FractSample::render(const Pattern& pattern, Image256& image)
	{
		m_fract.render(m_rect, pattern, m_resolution, image);
	}
}

#ifdef MUD_MODULES
module mud.fract;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_FRACT_EXPORT Type& type<mud::PatternSampling>() { static Type ty("mud::PatternSampling", sizeof(mud::PatternSampling)); return ty; }
    
    template <> MUD_FRACT_EXPORT Type& type<mud::Circlifier>() { static Type ty("Circlifier", sizeof(mud::Circlifier)); return ty; }
    template <> MUD_FRACT_EXPORT Type& type<mud::Fract>() { static Type ty("Fract", sizeof(mud::Fract)); return ty; }
    template <> MUD_FRACT_EXPORT Type& type<mud::FractSample>() { static Type ty("FractSample", sizeof(mud::FractSample)); return ty; }
    template <> MUD_FRACT_EXPORT Type& type<mud::FractTab>() { static Type ty("FractTab", sizeof(mud::FractTab)); return ty; }
    template <> MUD_FRACT_EXPORT Type& type<mud::Pattern>() { static Type ty("Pattern", sizeof(mud::Pattern)); return ty; }
}
