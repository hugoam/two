//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Cpp20.h>
#ifndef MUD_CPP_20
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#endif

#ifdef MUD_MODULES
module mud.procgen;
#else
#include <math/Colour.h>
#include <procgen/Fract/Fract.h>
#endif

#define PI 3.14159f
#define COEFF_TRANS 1.5f
#define COEFF_ROTATION 15
#define COEFF_V 0.004

#ifndef MUD_CPP_20
#include <cstdio>
#include <string>
#endif

float rnd_float()
{
	return (float)rand() / RAND_MAX;
	//rand()/RAND_MAX;
}

namespace mud
{
	void generate_fract(uint16_t pixelWidth, uint16_t pixelHeight, const Pattern& pattern, Image256& outputImage)
	{
		Fract fract;
		fract.generate();

		fract.renderWhole(pattern, pixelWidth, pixelHeight, outputImage);
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

		/*std::cerr << "AXIS" << std::endl;
		std::cerr << cos(angle_t) << std::endl;
		std::cerr << "dist : " << dist << std::endl;
		std::cerr << "normal_c : " << normal_c << std::endl;
		std::cerr << "ptt : " << ptt << std::endl;
		std::cerr << "normal_ab : " << normal_ab << ", ptt/pt : " << ptt / dist << std::endl;*/

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

	Fract::Fract(size_t numTabs)
		: m_update(0)
	{
		int seed = int(time(nullptr));
		srand(seed);

		this->generate(numTabs);
	}

	void Fract::generate(size_t numTabs)
	{
		m_numTabs = numTabs;

		m_tabs.clear();

		m_tabs.resize(numTabs);

		for(size_t i = 0; i < m_tabs.size(); ++i)
			m_tabs[i].generate(i);

		m_update++;
	}

	void Fract::regen()
	{
		for(size_t i = 0; i < m_tabs.size(); ++i)
			m_tabs[i].generate(i);

		m_update++;
	}

	int Fract::inversePoint(float& x, float& y)
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

	size_t Fract::inverseColour(int x, int y, const Rect& rect, const Pattern& pattern, Image256& image)
	{
		float ox = float(x) / float(image.m_width) * rect.m_size.x + rect.m_position.x - 0.5f;
		float oy = float(y) / float(image.m_height) * rect.m_size.y + rect.m_position.y - 0.5f;

		float px = ox;
		float py = oy;

		int num_reflects = this->inversePoint(px, py);

		px *= image.m_width / rect.m_size.x;
		py *= image.m_height / rect.m_size.y;

		size_t color = pattern.sample(px, py, float(num_reflects));

		return color;
	}

	void Fract::render(const Rect& rect, const Pattern& pattern, uint16_t resX, uint16_t resY, Image256& image)
	{
		image.resize(resX, resY);

		image.m_palette = pattern.m_palette;

		size_t index = 0;
		for(size_t y = 0; y < resY; ++y)
			for(size_t x = 0; x < resX; ++x, ++index)
				image.m_pixels[index] = this->inverseColour(x, y, rect, pattern, image);

		++m_update;
	}

	void Fract::renderWhole(const Pattern& pattern, uint16_t resX, uint16_t resY, Image256& image)
	{
		Rect rect(0.f, 0.f, 1.f, 1.f);
		this->render(rect, pattern, resX, resY, image);
	}

	void Fract::renderGrid(size_t size, const Pattern& pattern, uint16_t resX, uint16_t resY, std::vector<Image256>& images)
	{
		for(size_t y = 0; y < size; ++y)
			for(size_t x = 0; x < size; ++x)
			{
				Rect rect(float(x) / float(size), float(y) / float(size), 1.f / float(size), 1.f / float(size));
				images.emplace_back();
				this->render(rect, pattern, resX, resY, images.back());
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
		if(sampling == PATTERN_X)
			m_sampler = sampleX;
		else if(sampling == PATTERN_XY)
			m_sampler = sampleXY;
		else if(sampling == PATTERN_DEPTH)
			m_sampler = sampleZ;
	}

	size_t Pattern::sample(float x, float y, float depth) const
	{
		return m_sampler(*this, x, y, depth);
	}

	size_t sampleX(const Pattern& pattern, float x, float y, float depth)
	{
		UNUSED(x); UNUSED(depth);
		//int px = int(x * pattern.m_precision);
		int py = int(y * pattern.m_precision);
		
		int colourId = int(py);
		
		size_t color = colourId;
		color = color % pattern.m_palette.m_colours.size();

		return color;
	}

	size_t sampleZ(const Pattern& pattern, float x, float y, float depth)
	{
		UNUSED(x); UNUSED(y);
		size_t color = size_t(depth);
		color = color % pattern.m_palette.m_colours.size();

		return color;
	}

	size_t sampleXY(const Pattern& pattern, float x, float y, float depth)
	{
		return sampleX(pattern, x, y, depth);
	}

	FractSample::FractSample(Fract& fract, const Rect& rect, uint16_t resolutionX, uint16_t resolutionY)
		: m_fract(fract)
		, m_rect(rect)
		, m_resolutionX(resolutionX)
		, m_resolutionY(resolutionY)
	{}

	void FractSample::render(const Pattern& pattern, Image256& image)
	{
		m_fract.render(m_rect, pattern, m_resolutionX, m_resolutionY, image);
	}
}
