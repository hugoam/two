#pragma once

#include <two/ui.h>
#include <two/math.h>
#include <two/infra.h>
#include <two/type.h>



#ifndef TWO_MODULES
#include <stl/string.h>
#include <stl/map.h>
#endif

#ifndef TWO_MODULES
#include <vg/vg.h>
#include <bgfx/bgfx.h>
#endif

#ifndef TWO_UI_VG_EXPORT
#define TWO_UI_VG_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ class TWO_UI_VG_EXPORT VgVg : public Vg
	{
	public:
		VgVg(const string& resource_path, bx::AllocatorI* allocator);
		~VgVg();

		// init
		virtual void setup_context() override;
		virtual void release_context() override;

		// setup
		virtual void load_default_font() override;
		virtual void load_font(cstring name) override;
		virtual void load_image_RGBA(Image& image, const unsigned char* data) override;
		virtual void load_image(Image& image) override;
		virtual void unload_image(Image& image) override;
		virtual uint16_t load_texture(uint16_t texture) override;

		// rendering
		virtual void begin_frame(uint16_t view, const vec4& rect, float pixel_ratio, const Colour& colour = Colour(0.f)) override;
		virtual void end_frame(uint16_t view) override;

		// drawing
		virtual void begin_target() override;
		virtual void end_target() override;

		virtual void begin_layer(Layer& layer, const vec2& position, float scale) override;
		virtual void end_layer() override;

#ifdef TWO_UI_DRAW_CACHE
		virtual void begin_cached(Layer& layer) override;
		virtual void end_cached() override;

		virtual void draw_layer(Layer& layer, const vec2& position, float scale) override;
#endif

		virtual void begin_update(const vec2& position, float scale) override;
		virtual void end_update() override;

		virtual bool clipped(const vec4& rect) override;
		virtual void clip(const vec4& rect) override;
		virtual void unclip() override;

		virtual void begin_path() override;
		virtual void move_to(const vec2& p) override;
		virtual void line_to(const vec2& p) override;
		virtual void close_path() override;

		virtual void path_line(const vec2& p1, const vec2& p2) override;
		virtual void path_bezier(const vec2& p1, const vec2& c1, const vec2& c2, const vec2& p2, bool straighten = false) override;
		virtual void path_rect(const vec4& rect, const vec4& corners, float border) override;
		virtual void path_circle(const vec2& center, float r) override;

		virtual void draw_shadow(const vec4& rect, const vec4& corner, const Shadow& shadows) override;
		//virtual void draw_rect(const vec4& rect, const vec4& corners, const Paint& paint) override;
		virtual void draw_texture(uint16_t texture, const vec4& rect, const vec4& image_rect) override;
		virtual void draw_text(const vec2& offset, const char* start, const char* end, const TextPaint& paint) override;

		virtual void draw_color_wheel(const vec2& center, float r0, float r1) override;
		virtual void draw_color_triangle(const vec2& center, float r0, float hue, float s, float l) override;

		virtual void fill(const Gradient& gradient, const vec2& start, const vec2& end) override;
		virtual void fill(const Paint& paint) override;
		virtual void stroke(const Paint& paint) override;

		virtual void stroke_gradient(const Gradient& paint, float width, const vec2& start, const vec2& end) override;

		virtual void break_next_row(const char* text, const char* first, const char* end, const vec4& rect, const TextPaint& paint, TextRow& row) override;
		virtual void break_glyphs(const vec4& rect, const TextPaint& paint, TextRow& textRow) override;

		virtual float line_height(const TextPaint& paint) override;
		virtual float text_size(cstring text, size_t len, Axis dim, const TextPaint& paint) override;
		virtual vec2 text_size(cstring text, size_t len, const TextPaint& paint) override;

	private:
		uint32_t text_align(const TextPaint& paint);
		vg::TextConfig text_font(const TextPaint& paint);

#ifdef TWO_UI_DRAW_CACHE
		vg::CommandListHandle layer_cache(Layer& layer);
#endif

	protected:
		bx::AllocatorI* m_allocator = nullptr;
		vg::Context* m_vg = nullptr;

		vg::FontHandle m_default_font = { UINT16_MAX };

		map<string, vg::FontHandle> m_fonts;

		//map<Layer*, NVGdisplayList*> m_layers;
	};
}




#ifndef TWO_UI_VG_EXPORT
#define TWO_UI_VG_EXPORT TWO_IMPORT
#endif

namespace two
{
    class VgVg;
}

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#endif

#ifndef TWO_MODULES
#endif

namespace two
{
    // Exported types
    
    
}
