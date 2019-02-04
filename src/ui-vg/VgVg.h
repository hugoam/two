//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <stl/string.h>
#include <stl/map.h>
#endif
#include <ui/Forward.h>
#include <ui/Render/UiRenderer.h>

#ifndef MUD_MODULES
#include <vg/vg.h>
#include <bgfx/bgfx.h>
#endif

#ifndef MUD_UI_VG_EXPORT
#define MUD_UI_VG_EXPORT MUD_IMPORT
#endif

namespace mud
{
	export_ class MUD_UI_VG_EXPORT VgVg : public Vg
	{
	public:
		VgVg(const string& resource_path, bx::AllocatorI* allocator);
		~VgVg();

		// init
		virtual void setup_context() final;
		virtual void release_context() final;

		// setup
		virtual void load_default_font() final;
		virtual void load_font(cstring name) final;
		virtual void load_image_RGBA(Image& image, const unsigned char* data) final;
		virtual void load_image(Image& image) final;
		virtual void unload_image(Image& image) final;
		virtual uint16_t load_texture(uint16_t texture) final;

		// rendering
		virtual void begin_frame(const vec4& rect, float pixel_ratio) final;
		virtual void end_frame() final;

		// drawing
		virtual void begin_target() final;
		virtual void end_target() final;

		virtual void begin_layer(Layer& layer, const vec2& position, float scale) final;
		virtual void end_layer() final;

#ifdef MUD_UI_DRAW_CACHE
		virtual void begin_cached(Layer& layer) final;
		virtual void end_cached() final;

		virtual void draw_layer(Layer& layer, const vec2& position, float scale) final;
#endif

		virtual void begin_update(const vec2& position, float scale) final;
		virtual void end_update() final;

		virtual bool clipped(const vec4& rect) final;
		virtual void clip(const vec4& rect) final;
		virtual void unclip() final;

		virtual void path_line(const vec2& p1, const vec2& p2) final;
		virtual void path_bezier(const vec2& p1, const vec2& c1, const vec2& c2, const vec2& p2, bool straighten = false) final;
		virtual void path_rect(const vec4& rect, const vec4& corners, float border) final;
		virtual void path_circle(const vec2& center, float r) final;

		virtual void draw_shadow(const vec4& rect, const vec4& corner, const Shadow& shadows) final;
		//virtual void draw_rect(const vec4& rect, const vec4& corners, const Paint& paint) final;
		virtual void draw_texture(uint16_t texture, const vec4& rect, const vec4& image_rect) final;
		virtual void draw_text(const vec2& offset, const char* start, const char* end, const TextPaint& paint) final;

		virtual void draw_color_wheel(const vec2& center, float r0, float r1) final;
		virtual void draw_color_triangle(const vec2& center, float r0, float hue, float s, float l) final;

		virtual void fill(const Gradient& gradient, const vec2& start, const vec2& end) final;
		virtual void fill(const Paint& paint) final;
		virtual void stroke(const Paint& paint) final;

		virtual void stroke_gradient(const Gradient& paint, float width, const vec2& start, const vec2& end) final;

		virtual void break_next_row(const char* text, const char* first, const char* end, const vec4& rect, const TextPaint& paint, TextRow& row) final;
		virtual void break_glyphs(const vec4& rect, const TextPaint& paint, TextRow& textRow) final;

		virtual float line_height(const TextPaint& paint) final;
		virtual float text_size(cstring text, size_t len, Dim dim, const TextPaint& paint) final;
		virtual vec2 text_size(cstring text, size_t len, const TextPaint& paint) final;

	private:
		uint32_t text_align(const TextPaint& paint);
		vg::TextConfig text_font(const TextPaint& paint);

#ifdef MUD_UI_DRAW_CACHE
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
