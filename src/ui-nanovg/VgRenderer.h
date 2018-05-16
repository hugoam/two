//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Generated/Forward.h>
#include <ui/Render/Renderer.h>

#include <map>
#include <string>

/* vg-renderer */
#include <vg/vg.h>
#include <bgfx/bgfx.h>

namespace mud
{
	using string = std::string;

	class vgRenderer : public VgRenderer
	{
	public:
		vgRenderer(cstring resource_path, bx::AllocatorI* allocator);

		// init
		virtual void setupContext() final;
		virtual void releaseContext() final;

		// targets
		virtual object_ptr<UiRenderTarget> createRenderTarget(Layer& layer);

		// setup
		virtual void loadDefaultFont() final;
		virtual void loadFont(cstring name) final;
		virtual void loadImageRGBA(Image& image, const unsigned char* data) final;
		virtual void loadImage(Image& image) final;
		virtual void unloadImage(Image& image) final;
		virtual uint16_t loadTexture(uint16_t texture) final;

		// rendering
		virtual void beginFrame(UiRenderTarget& target) final;
		virtual void endFrame() final;

		// drawing
		virtual void beginTarget() final;
		virtual void endTarget() final;

#ifdef MUD_UI_DRAW_CACHE
		vg::CommandListHandle layerCache(Layer& layer);
		virtual void drawLayer(Layer& layer, const vec2& position, float scale) final;
#endif

		virtual void beginLayer(Layer& layer, const vec2& position, float scale) final;
		virtual void endLayer() final;

		virtual void beginUpdate(const vec2& position, float scale) final;
		virtual void endUpdate() final;

		virtual bool clipped(const vec4& rect) final;
		virtual void clip(const vec4& rect) final;
		virtual void unclip() final;

		virtual void pathLine(const vec2& p1, const vec2& p2) final;
		virtual void pathBezier(const vec2& p1, const vec2& c1, const vec2& c2, const vec2& p2, bool straighten = false) final;
		virtual void pathRect(const vec4& rect, const vec4& corners, float border) final;
		virtual void pathCircle(const vec2& center, float r) final;

		virtual void drawShadow(const vec4& rect, const vec4& corner, const Shadow& shadows) final;
		//virtual void drawRect(const vec4& rect, const vec4& corners, const Paint& paint) final;
		virtual void drawImage(const Image& image, const vec4& rect) final;
		virtual void drawImageStretch(const Image& image, const vec4& rect, const vec2& stretch = { 1.f, 1.f }) final;
		virtual void drawTexture(uint16_t texture, const vec4& rect, const vec4& image_rect) final;
		virtual void drawText(const vec2& offset, const char* start, const char* end, const TextPaint& paint) final;

		virtual void drawColorWheel(const vec2& center, float r0, float r1) final;
		virtual void drawColorTriangle(const vec2& center, float r0, float hue, float s, float l) final;

		//virtual void debugRect(const vec4& rect, const Colour& colour) final;

		virtual void fill(const Gradient& gradient, const vec2& start, const vec2& end) final;
		virtual void fill(const Paint& paint) final;
		virtual void stroke(const Paint& paint) final;

		virtual void strokeGradient(const Gradient& paint, float width, const vec2& start, const vec2& end) final;

		virtual void breakNextRow(const char* first, const char* end, const vec4& rect, const TextPaint& paint, TextRow& row) final;
		virtual void breakGlyphs(const vec4& rect, const TextPaint& paint, TextRow& textRow) final;

		virtual float lineHeight(const TextPaint& paint) final;
		virtual float textSize(cstring text, size_t len, Dim dim, const TextPaint& paint) final;
		virtual vec2 textSize(cstring text, size_t len, const TextPaint& paint) final;

	private:
		uint32_t text_align(const TextPaint& paint);
		vg::TextConfig text_font(const TextPaint& paint);

	protected:
		bx::AllocatorI* m_allocator = nullptr;
		vg::Context* m_vg = nullptr;

		vg::FontHandle m_default_font = { UINT16_MAX };

		std::map<string, vg::FontHandle> m_fonts;

		//std::map<Layer*, NVGdisplayList*> m_layers;
	};
}
