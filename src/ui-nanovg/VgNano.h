//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Generated/Forward.h>
#include <ui/Render/Renderer.h>

#include <map>

struct NVGcontext;
struct NVGdisplayList;

namespace mud
{
	class VgNano : public VgRenderer
	{
	public:
		VgNano(cstring resource_path);

		// targets
		virtual object_ptr<UiTarget> create_render_target(Layer& layer);

		// setup
		virtual void load_default_font() final;
		virtual void load_font(cstring name) final;
		virtual void load_image_RGBA(Image& image, const unsigned char* data) final;
		virtual void load_image(Image& image) final;
		virtual void unload_image(Image& image) final;
		virtual uint16_t load_texture(uint16_t texture) final;

		// rendering
		virtual void begin_frame(UiTarget& target) final;
		virtual void end_frame() final;

		// drawing
		virtual void begin_target() final;
		virtual void end_target() final;

#ifdef MUD_UI_DRAW_CACHE
		virtual void begin_cached(Layer& layer) final;
		virtual void end_cached() final;

		virtual void draw_layer(Layer& layer, const vec2& position, float scale) final;
#endif
		virtual void begin_layer(Layer& layer, const vec2& position, float scale) final;
		virtual void end_layer() final;

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

		virtual void break_next_row(const char* first, const char* end, const vec4& rect, const TextPaint& paint, TextRow& row) final;
		virtual void break_glyphs(const vec4& rect, const TextPaint& paint, TextRow& textRow) final;
		
		virtual float line_height(const TextPaint& paint) final;
		virtual float text_size(cstring text, size_t len, Dim dim, const TextPaint& paint) final;
		virtual vec2 text_size(cstring text, size_t len, const TextPaint& paint) final;

		virtual void break_text(cstring text, size_t len, const vec2& space, const TextPaint& paint, std::vector<TextRow>& text_rows) final;

	private:
		void setup_text(const TextPaint& paint);

#ifdef MUD_UI_DRAW_CACHE
		NVGdisplayList* layer_cache(Layer& layer);
#endif

	protected:
		NVGcontext* m_ctx;

		float m_line_height;

		std::map<const Layer*, NVGdisplayList*> m_layers;
	};
}
