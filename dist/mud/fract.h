#pragma once

#include <mud/geom.h>
#include <mud/math.h>
#include <mud/infra.h>
#include <mud/type.h>




#ifndef MUD_FRACT_EXPORT
#define MUD_FRACT_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum class PatternSampling : unsigned int;

    class Pixircle;
    class Circlifier;
    struct Pattern;
    struct FractTab;
    class Fract;
    class FractSample;
}

#ifdef MUD_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
	export_ extern template class refl_ seque_ vector<mud::Circle>;
	export_ extern template class refl_ seque_ vector<mud::Image256>;
}
#endif

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_FRACT_EXPORT Type& type<mud::PatternSampling>();
    
    export_ template <> MUD_FRACT_EXPORT Type& type<stl::vector<mud::Image256>>();
    
    export_ template <> MUD_FRACT_EXPORT Type& type<mud::Circlifier>();
    export_ template <> MUD_FRACT_EXPORT Type& type<mud::Fract>();
    export_ template <> MUD_FRACT_EXPORT Type& type<mud::FractSample>();
    export_ template <> MUD_FRACT_EXPORT Type& type<mud::FractTab>();
    export_ template <> MUD_FRACT_EXPORT Type& type<mud::Pattern>();
}

#ifndef MUD_MODULES
#include <stl/vector.h>
#endif

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

#ifndef MUD_MODULES
#include <stl/vector.h>
#include <stl/map.h>
#include <stl/memory.h>
#endif

namespace mud
{
	MUD_FRACT_EXPORT func_ void generate_fract(uvec2 resolution, const Pattern& pattern, Image256& output_image);

	typedef uint32_t(*PatternSampler)(const Pattern&, float, float, float);

	export_ enum class refl_ PatternSampling : unsigned int
	{
		X = 0,
		XY = 1,
		Depth = 2
	};

	uint32_t sampleX(const Pattern& pattern, float x, float y, float depth);
	uint32_t sampleXY(const Pattern& pattern, float x, float y, float depth);
	uint32_t sampleZ(const Pattern& pattern, float x, float y, float depth);

	export_ struct refl_ MUD_FRACT_EXPORT Pattern
	{
	public:
		constr_ Pattern(Palette palette, PatternSampling sampling, float precision = 1.f, size_t step = 1);
		constr_ Pattern();

		uint32_t sample(float x, float y, float depth) const;

		Palette m_palette;
		float m_precision;
		size_t m_step;

	protected:
		PatternSampler m_sampler;
	};

	export_ struct refl_ MUD_FRACT_EXPORT FractTab
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

	export_ class refl_ MUD_FRACT_EXPORT Fract
	{
	public:
		constr_ Fract(size_t num_tabs = 75);

		meth_ void generate(size_t num_tabs = 75);
		meth_ void regen();
		meth_ void render(const Rect& rect, const Pattern& pattern, const uvec2& resolution, Image256& output_image);
		meth_ void render_whole(const Pattern& pattern, const uvec2& resolution, Image256& output_image);
		meth_ void render_grid(const uvec2& size, const Pattern& pattern, const uvec2& resolution, vector<Image256>& output_images);

		int inverse_point(float& x, float& y);		

		void notify_update() { ++m_update; }
		size_t update() { return m_update; }

		uint32_t inverse_colour(int x, int y, const Rect& rect, const Pattern& pattern, Image256& outputImage);

		attr_ size_t m_num_tabs;
		size_t m_update;
		vector<FractTab> m_tabs;
	};

	export_ class refl_ MUD_FRACT_EXPORT FractSample
	{
	public:
		constr_ FractSample(Fract& fract, const Rect& rect, uvec2 resolution);

		attr_ Fract& m_fract;
		attr_ Rect m_rect;
		attr_ uvec2 m_resolution;

		meth_ void render(const Pattern& pattern, Image256& outputImage);
	};
}

