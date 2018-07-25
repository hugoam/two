//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Unique.h>
#include <math/Timer.h>
#endif
#include <ui/Forward.h>
#include <ui/Frame/Caption.h>

namespace mud
{
	using cstring = const char*;

	export_ class MUD_UI_EXPORT Vg
	{
	public:
		Vg(cstring resource_path);
		virtual ~Vg();

		// init
		virtual void setup_context() = 0;
		virtual void release_context() = 0;

		// setup
		virtual void load_default_font() = 0;
		virtual void load_font(cstring name) = 0;
		virtual void load_image_RGBA(Image& image, const unsigned char* data) = 0;
		virtual void load_image(Image& image) = 0;
		virtual void unload_image(Image& image) = 0;
		virtual uint16_t load_texture(uint16_t texture) = 0;

		// rendering
		virtual void begin_frame(const vec4& rect, float pixel_ratio = 1.f) = 0;
		virtual void end_frame() = 0;

		// drawing
		virtual void begin_target() = 0;
		virtual void end_target() = 0;

#ifdef MUD_UI_DRAW_CACHE
		virtual void begin_cached(Layer& layer) = 0;
		virtual void end_cached() = 0;

		virtual void draw_layer(Layer& layer, const vec2& position = Zero2, float scale = 1.f) = 0;
#endif

		virtual void begin_layer(Layer& layer, const vec2& position = Zero2, float scale = 1.f) = 0;
		virtual void end_layer() = 0;

		virtual void begin_update(const vec2& position, float scale) = 0;
		virtual void end_update() = 0;

		virtual bool clipped(const vec4& rect) = 0;
		virtual void clip(const vec4& rect) = 0;
		virtual void unclip() = 0;

		virtual void path_line(const vec2& p1, const vec2& p2) = 0;
		virtual void path_bezier(const vec2& p1, const vec2& c1, const vec2& c2, const vec2& p2, bool straighten = false) = 0;
		virtual void path_rect(const vec4& rect, const vec4& corners, float border) = 0;
		virtual void path_circle(const vec2& center, float r) = 0;

		virtual void fill(const Gradient& gradient, const vec2& start, const vec2& end) = 0;
		virtual void fill(const Paint& paint) = 0;
		virtual void stroke(const Paint& paint) = 0;

		virtual void stroke_gradient(const Gradient& paint, float width, const vec2& start, const vec2& end) = 0;

		virtual void draw_shadow(const vec4& rect, const vec4& corner, const Shadow& shadows) = 0;
		virtual void draw_texture(uint16_t texture, const vec4& rect, const vec4& image_rect) = 0;
		virtual void draw_text(const vec2& offset, const char* start, const char* end, const TextPaint& paint) = 0;

		virtual void draw_color_wheel(const vec2& center, float r0, float r1) = 0;
		virtual void draw_color_triangle(const vec2& center, float r0, float hue, float s, float l) = 0;

		virtual void debug_rect(const vec4& rect, const Colour& colour);

		virtual void break_text(cstring text, size_t len, const vec2& space, const TextPaint& paint, std::vector<TextRow>& rows);

		void fill_text(cstring text, size_t len, const vec4& rect, const TextPaint& paint, TextRow& row);
		void break_text_width(const char* text, const char* start, const char* end, const vec4& rect, const TextPaint& paint, TextRow& textRow);
		void break_text_returns(const char* text, const char* start, const char* end, const vec4& rect, const TextPaint& paint, TextRow& textRow);

		virtual void break_next_row(const char* text, const char* first, const char* end, const vec4& rect, const TextPaint& paint, TextRow& row) = 0;
		virtual void break_glyphs(const vec4& rect, const TextPaint& paint, TextRow& textRow) = 0;

		virtual float line_height(const TextPaint& paint) = 0;
		virtual float text_size(cstring text, size_t len, Dim dim, const TextPaint& paint) = 0;
		virtual vec2 text_size(cstring text, size_t len, const TextPaint& paint) = 0;

		void draw_rect(const vec4& rect, const Paint& paint, const vec4& corners = Zero4);

		cstring font_path(cstring font);

	protected:
		struct Impl;
		unique_ptr<Impl> m_impl;

		bool m_null = false;
	};

	export_ class MUD_UI_EXPORT UiRenderer
	{
	public:
		UiRenderer(Vg& vg);
		virtual ~UiRenderer();

		void render(Layer& layer);

		// drawing implementation
		void render_layer(Layer& layer);

		void begin_layer(Frame& frame);
		void begin_frame(Frame& frame);
		void render_frame(Frame& frame);
		void end_frame(Frame& frame);
		void end_layer(Frame& frame);
		void draw_frame(const Frame& frame);
		void draw_frame(const Frame& frame, const vec4& rect);

		vec4 select_corners(const Frame& frame);
		float content_pos(const Frame& frame, const vec2& content, const vec4& padded_rect, Dim dim);
		void draw_content(const Frame& frame, const vec4& rect, const vec4& padded_rect, const vec4& content_rect);
		void draw_background(const Frame& frame, const vec4& rect, const vec4& padded_rect, const vec4& content_rect);
		void draw_rect(const vec4& rect, const vec4& corners, const InkStyle& inkstyle);
		void draw_image(const Image& image, const vec4& rect);
		void draw_image_stretch(const Image& image, const vec4& rect, const vec2& stretch = { 1.f, 1.f });
		void draw_skin_image(const Frame& frame, int section, vec4 rect);

		void log_FPS();

	protected:
		Vg& m_vg;
		size_t m_debug_batch = 0;

		struct Impl;
		unique_ptr<Impl> m_impl;

		Clock m_clock;
	};
}
