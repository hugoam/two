//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Unique.h>
#include <obj/Strung.h>
#include <obj/Util/Timer.h>
#include <ui/Generated/Forward.h>
#include <ui/Frame/Caption.h>

#define MUD_UI_IMMEDIATE

namespace mud
{
	class _refl_ MUD_UI_EXPORT UiRenderTarget
	{
	public:
		UiRenderTarget(VgRenderer& renderer, Layer& layer, bool gammaCorrected);

		VgRenderer& m_renderer;
		Layer& m_layer;
		bool m_gammaCorrected;

		void render();
	};

	class MUD_UI_EXPORT VgRenderer
	{
	public:
		VgRenderer(cstring resource_path);
		virtual ~VgRenderer();

		// drawing implementation
		void render_layer(Layer& layer);

		void begin_layer(Frame& frame);
		void begin_frame(Frame& frame);
		void render_frame(Frame& frame);
		void end_frame(Frame& frame);
		void end_layer(Frame& frame);
		void draw_frame(const Frame& frame);

		vec4 selectCorners(const Frame& frame);
		float contentPos(const Frame& frame, const vec4& padded_rect, Dim dim);
		void drawContent(const Frame& frame, const vec4& rect, const vec4& padded_rect, const vec4& content_rect);
		void drawBackground(const Frame& frame, const vec4& rect, const vec4& padded_rect, const vec4& content_rect);
		void drawRect(const vec4& rect, const vec4& corners, const InkStyle& inkstyle);
		void drawSkinImage(const Frame& frame, int section, vec4 rect);

		void logFPS();

		// render
		virtual void render(UiRenderTarget& target);

		// init
		virtual void setupContext() = 0;
		virtual void releaseContext() = 0;

		// targets
		virtual object_ptr<UiRenderTarget> createRenderTarget(Layer& masterLayer) = 0;

		// setup
		virtual void loadDefaultFont() = 0;
		virtual void loadFont(cstring name) = 0;
		virtual void loadImageRGBA(Image& image, const unsigned char* data) = 0;
		virtual void loadImage(Image& image) = 0;
		virtual void unloadImage(Image& image) = 0;
		virtual uint16_t loadTexture(uint16_t texture) = 0;

		// rendering
		virtual void beginFrame(UiRenderTarget& target) = 0;
		virtual void endFrame() = 0;

		// drawing
		virtual void beginTarget() = 0;
		virtual void endTarget() = 0;

#ifdef MUD_UI_DRAW_CACHE
		virtual void drawLayer(Layer& layer, const vec2& position = Zero2, float scale = 1.f) = 0;
#endif
		virtual void beginLayer(Layer& layer, const vec2& position = Zero2, float scale = 1.f) = 0;
		virtual void endLayer() = 0;

		virtual void beginUpdate(const vec2& position, float scale) = 0;
		virtual void endUpdate() = 0;

		virtual bool clipped(const vec4& rect) = 0;
		virtual void clip(const vec4& rect) = 0;
		virtual void unclip() = 0;

		virtual void pathLine(const vec2& p1, const vec2& p2) = 0;
		virtual void pathBezier(const vec2& p1, const vec2& c1, const vec2& c2, const vec2& p2, bool straighten = false) = 0;
		virtual void pathRect(const vec4& rect, const vec4& corners, float border) = 0;
		virtual void pathCircle(const vec2& center, float r) = 0;

		virtual void fill(const Gradient& gradient, const vec2& start, const vec2& end) = 0;
		virtual void fill(const Paint& paint) = 0;
		virtual void stroke(const Paint& paint) = 0;

		virtual void strokeGradient(const Gradient& paint, float width, const vec2& start, const vec2& end) = 0;

		virtual void drawShadow(const vec4& rect, const vec4& corner, const Shadow& shadows) = 0;
		virtual void drawText(const vec2& offset, const char* start, const char* end, const TextPaint& paint) = 0;

		virtual void drawImage(const Image& image, const vec4& rect) = 0;
		virtual void drawImageStretch(const Image& image, const vec4& rect, const vec2& stretch = { 1.f, 1.f }) = 0;
		virtual void drawTexture(uint16_t texture, const vec4& rect, const vec4& image_rect) = 0;

		virtual void drawColorWheel(const vec2& center, float r0, float r1) = 0;
		virtual void drawColorTriangle(const vec2& center, float r0, float hue, float s, float l) = 0;

		virtual void debugRect(const vec4& rect, const Colour& colour);

		virtual void breakText(cstring text, size_t len, const vec2& space, const TextPaint& paint, std::vector<TextRow>& rows);

		void fillText(cstring text, size_t len, const vec4& rect, const TextPaint& paint, TextRow& row);
		void breakTextWidth(const char* string, const char* end, const vec4& rect, const TextPaint& paint, TextRow& textRow);
		void breakTextReturns(const char* string, const char* end, const vec4& rect, const TextPaint& paint, TextRow& textRow);

		virtual void breakNextRow(const char* first, const char* end, const vec4& rect, const TextPaint& paint, TextRow& row) = 0;
		virtual void breakGlyphs(const vec4& rect, const TextPaint& paint, TextRow& textRow) = 0;

		virtual float lineHeight(const TextPaint& paint) = 0;
		virtual float textSize(cstring text, size_t len, Dim dim, const TextPaint& paint) = 0;
		virtual vec2 textSize(cstring text, size_t len, const TextPaint& paint) = 0;

		void drawRect(const vec4& rect, const Paint& paint, const vec4& corners = Zero4);

		cstring fontPath(cstring font);

	protected:
		strung m_resource_path;
		size_t m_debug_batch = 0;

		struct Impl;
		unique_ptr<Impl> m_impl;

		Clock m_clock;

		bool m_null = false;
	};
}
