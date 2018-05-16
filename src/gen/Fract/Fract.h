#pragma once

#include <obj/Proto.h>
#include <math/Colour.h>
#include <math/Image.h>
#include <math/Vec.h>
#include <geom/Shapes.h>
#include <gen/Generated/Forward.h>

#include <vector>
#include <map>
#include <memory>

namespace mud
{
	MUD_GEN_EXPORT _func_ void generate_fract(uint16_t pixelWidth, uint16_t pixelHeight, const Pattern& pattern, Image256& outputImage);

	//typedef std::function<size_t(const Pattern&, float, float, float)> PatternSampler;
	typedef size_t(*PatternSampler)(const Pattern&, float, float, float);

	enum _refl_ PatternSampling : unsigned int
	{
		PATTERN_X = 0,
		PATTERN_XY = 1,
		PATTERN_DEPTH = 2
	};

	size_t sampleX(const Pattern& pattern, float x, float y, float depth);
	size_t sampleXY(const Pattern& pattern, float x, float y, float depth);
	size_t sampleZ(const Pattern& pattern, float x, float y, float depth);

	struct _refl_ MUD_GEN_EXPORT Pattern
	{
	public:
		_constr_ Pattern(Palette palette, PatternSampling sampling, float precision = 1.f, size_t step = 1);
		_constr_ Pattern();

		size_t sample(float x, float y, float depth) const;

		Palette m_palette;
		float m_precision;
		size_t m_step;

	protected:
		PatternSampler m_sampler;
	};

	struct _refl_ MUD_GEN_EXPORT FractTab
	{
	public:
		FractTab();

		void generate(int index);
		void calcnormal();
		void setnormal();
		void transinormal();

		void genca(int steps);

	public:
		int i;

		//vec3 delta;
		float delta_a, delta_b, delta_c;

		//vec3 normal;
		vec3 normal;
		vec3 origin;
		float a, b, c;
		float normal_a, normal_b, normal_c;
		float normal_ab;

		float dist;

		float angle_t;
		float angle_a;
		float angle_p;

		float angle_offset_t;
		float angle_offset_a;
	};

	class _refl_ MUD_GEN_EXPORT Fract
	{
	public:
		_constr_ Fract(size_t numTabs = 75);

		_meth_ void generate(size_t numTabs = 75);
		_meth_ void regen();
		_meth_ void render(const Rect& rect, const Pattern& pattern, uint16_t resX, uint16_t resY, Image256& outputImage);
		_meth_ void renderWhole(const Pattern& pattern, uint16_t resX, uint16_t resY, Image256& outputImage);
		_meth_ void renderGrid(size_t size, const Pattern& pattern, uint16_t resX, uint16_t resY, std::vector<Image256>& outputImages);

		int inversePoint(float& x, float& y);		

		void notifyUpdate() { ++m_update; }
		size_t update() { return m_update; }

		size_t inverseColour(int x, int y, const Rect& rect, const Pattern& pattern, Image256& outputImage);

		_attr_ size_t m_numTabs;
		size_t m_update;
		std::vector<FractTab> m_tabs;
	};

	class _refl_ MUD_GEN_EXPORT FractSample
	{
	public:
		_constr_ FractSample(Fract& fract, const Rect& rect, uint16_t resolutionX, uint16_t resolutionY);

		_attr_ Fract& m_fract;
		_attr_ Rect m_rect;
		_attr_ uint16_t m_resolutionX;
		_attr_ uint16_t m_resolutionY;

		_meth_ void render(const Pattern& pattern, Image256& outputImage);
	};
}
