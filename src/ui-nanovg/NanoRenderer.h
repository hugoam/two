//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
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
	class NanoRenderer : public VgRenderer
	{
	public:
		NanoRenderer(cstring resource_path);

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

		// rendering
		virtual void beginFrame(UiRenderTarget& target) final;
		virtual void endFrame() final;

		// drawing
		virtual void beginTarget() final;
		virtual void endTarget() final;

#ifdef MUD_UI_DRAW_CACHE
		NVGdisplayList* layerCache(Layer& layer);

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
		virtual void drawText(const vec2& offset, const char* start, const char* end, const TextPaint& paint) final;

		virtual void drawColorWheel(const vec2& center, float r0, float r1) final;
		virtual void drawColorTriangle(const vec2& center, float r0, float hue, float s, float l) final;

		//virtual void debugRect(const vec4& rect, const Colour& colour) final;

		virtual void fill(const Gradient& gradient, const vec2& start, const vec2& end) final;
		virtual void fill(const Paint& paint) final;
		virtual void stroke(const Paint& paint) final;

		virtual void strokeGradient(const Gradient& paint, float width, const vec2& start, const vec2& end) final;

		virtual void breakText(cstring text, size_t len, const vec2& space, const TextPaint& paint, std::vector<TextRow>& textRows) final;

		virtual void breakNextRow(const char* first, const char* end, const vec4& rect, const TextPaint& paint, TextRow& row) final;
		virtual void breakGlyphs(const vec4& rect, const TextPaint& paint, TextRow& textRow) final;

		virtual float lineHeight(const TextPaint& paint) final;
		virtual float textSize(cstring text, size_t len, Dim dim, const TextPaint& paint) final;
		virtual vec2 textSize(cstring text, size_t len, const TextPaint& paint) final;

	private:
		void setupText(const TextPaint& paint);

		void drawImage(uint16_t image, const vec4& rect, const vec4& imageRect);

	protected:
		NVGcontext* m_ctx;

		float m_lineHeight;

		std::map<const Layer*, NVGdisplayList*> m_layers;
	};
}
