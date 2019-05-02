//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.


#include <ui-nanovg/VgNano.h>

#include <obj/Serial/Serial.h>
#include <math/Math.h>

#include <ui/Style/Paint.h>
#include <ui/Frame/Layer.h>

#include <ui/ImageAtlas.h>

#include <nanovg.h>

#include <cmath>

namespace two
{
	inline NVGcolor nvgColour(const Colour& colour)
	{
		return nvgRGBAf(colour.m_r, colour.m_g, colour.m_b, colour.m_a);
	}

#define RECT_FLOATS(rect) rect.x, rect.y, rect.z, rect.w

	VgNano::VgNano(cstring resource_path)
		: VgRenderer(resource_path)
		, m_ctx(nullptr)
	{}

	object_ptr<UiTarget> VgNano::create_render_target(Layer& layer)
	{
		return make_object<UiTarget>(*this, layer, false);
	}

	void VgNano::load_default_font()
	{
		if(m_null) return;
		this->load_font("dejavu");
		nvgFontSize(m_ctx, 14.0f);
		nvgFontFace(m_ctx, "dejavu");
	}

	void VgNano::load_font(cstring name)
	{
		cstring path = this->font_path(name);
		nvgCreateFont(m_ctx, name, path);
	}

	void VgNano::load_image_RGBA(Image& image, const unsigned char* data)
	{
		if(m_null) return;
		image.d_handle = nvgCreateImageRGBA(m_ctx, image.d_size.x, image.d_size.y, image.d_filtering ? 0 : NVG_IMAGE_NEAREST, data);
	}

	void VgNano::load_image(Image& image)
	{
		if(m_null) return;
		image.d_handle = nvgCreateImage(m_ctx, image.d_path.c_str(), image.d_tile ? (NVG_IMAGE_REPEATX | NVG_IMAGE_REPEATY) : 0);
	}

	void VgNano::unload_image(Image& image)
	{
		if(m_null) return;
		nvgDeleteImage(m_ctx, image.d_handle);
		image.d_handle = 0;
	}

	uint16_t VgNano::load_texture(uint16_t texture)
	{
		return texture;
	}

	void VgNano::begin_frame(UiTarget& target)
	{
#ifdef TWO_RENDERER_BGFX
		bgfx::setViewRect(250, 0, 0, uint16_t(target.m_layer.m_frame.m_size.x), uint16_t(target.m_layer.m_frame.m_size.y));
		bgfx::setViewMode(250, bgfx::ViewMode::Sequential);
		bgfx::setViewName(250, "ui");
#endif

		float pixelRatio = 1.f;
		nvgBeginFrame(m_ctx, int(target.m_layer.m_frame.m_size.x), int(target.m_layer.m_frame.m_size.y), pixelRatio);
	}

	void VgNano::end_frame()
	{
		nvgEndFrame(m_ctx);
	}

	bool VgNano::clipped(const vec4& rect)
	{
		vec4 scissor;
		nvgCurrentScissor(m_ctx, value_ptr(scissor));

		if(rect_w(scissor) < 0.f || rect_h(scissor) < 0.f)
			return false;

		return !rect_intersects(rect, scissor);
	}

	void VgNano::clip(const vec4& rect)
	{
		nvgIntersectScissor(m_ctx, RECT_FLOATS(rect));
	}

	void VgNano::unclip()
	{
		nvgResetScissor(m_ctx);
	}

	void VgNano::path_line(const vec2& p1, const vec2& p2)
	{
		nvgBeginPath(m_ctx);
		nvgMoveTo(m_ctx, p1.x, p1.y);
		nvgLineTo(m_ctx, p2.x, p2.y);
	}

	void VgNano::path_bezier(const vec2& p1, const vec2& c1, const vec2& c2, const vec2& p2, bool straighten)
	{
		nvgBeginPath(m_ctx);
		nvgMoveTo(m_ctx, p1.x, p1.y);
		if(straighten)
		{
			nvgLineTo(m_ctx, c1.x, c1.y);
			nvgLineTo(m_ctx, c2.x, c2.y);
			nvgLineTo(m_ctx, p2.x, p2.y);
		}
		else
			nvgBezierTo(m_ctx, c1.x, c1.y, c2.x, c2.y, p2.x, p2.y);
	}

	void VgNano::path_rect(const vec4& rect, const vec4& corners, float border)
	{
		nvgBeginPath(m_ctx);

		vec4 path_rect = { rect_offset(rect) + border * 0.5f, rect_size(rect) - border };
		if(corners == Zero4)
			nvgRect(m_ctx, RECT_FLOATS(path_rect));
		else
			nvgRoundedRectVarying(m_ctx, RECT_FLOATS(path_rect), RECT_FLOATS(corners));
	}

	void VgNano::path_circle(const vec2& center, float r)
	{
		nvgBeginPath(m_ctx);
		nvgCircle(m_ctx, center.x, center.y, r);
	}
	
	void VgNano::draw_shadow(const vec4& rect, const vec4& corners, const Shadow& shadow)
	{
		vec4 shadow_rect = { rect_offset(rect) + shadow.d_pos - shadow.d_radius, rect_size(rect) + shadow.d_radius * 2.f };
		vec4 gradient_rect = { rect_offset(rect) + shadow.d_pos - shadow.d_spread, rect_size(rect) + shadow.d_spread * 2.f };
		NVGpaint shadowPaint = nvgBoxGradient(m_ctx, RECT_FLOATS(gradient_rect), corners[0] + shadow.d_spread, shadow.d_blur, nvgColour(shadow.d_colour), nvgRGBA(0, 0, 0, 0));
		nvgBeginPath(m_ctx);
		nvgRect(m_ctx, RECT_FLOATS(shadow_rect));
		if(corners == Zero4)
			nvgRect(m_ctx, RECT_FLOATS(rect));
		else
			nvgRoundedRectVarying(m_ctx, RECT_FLOATS(rect), RECT_FLOATS(corners));
		nvgPathWinding(m_ctx, NVG_HOLE);
		nvgFillPaint(m_ctx, shadowPaint);
		nvgFill(m_ctx);
	}

	void VgNano::fill(const Gradient& gradient, const vec2& start, const vec2& end)
	{
		nvgFillPaint(m_ctx, nvgLinearGradient(m_ctx, start.x, start.y, end.x, end.y, nvgColour(gradient.m_start), nvgColour(gradient.m_end)));
		nvgFill(m_ctx);
	}

	void VgNano::fill(const Paint& paint)
	{
		nvgFillColor(m_ctx, nvgColour(paint.m_fill_colour));
		nvgFill(m_ctx);
	}

	void VgNano::stroke(const Paint& paint)
	{
		nvgStrokeWidth(m_ctx, paint.m_stroke_width);
		nvgStrokeColor(m_ctx, nvgColour(paint.m_stroke_colour));
		nvgStroke(m_ctx);
	}

	void VgNano::stroke_gradient(const Gradient& paint, float width, const vec2& start, const vec2& end)
	{
		NVGcolor first = nvgColour(paint.m_start);
		NVGcolor second = nvgColour(paint.m_end);

		nvgStrokeWidth(m_ctx, width);
		nvgStrokePaint(m_ctx, nvgLinearGradient(m_ctx, start.x, start.y, end.x, end.y, first, second));
		nvgStroke(m_ctx);
	}

	void VgNano::draw_texture(uint16_t image, const vec4& rect, const vec4& imageRect)
	{
		NVGpaint imgPaint = nvgImagePattern(m_ctx, RECT_FLOATS(imageRect), 0.0f / 180.0f * NVG_PI, image, 1.f);
		nvgBeginPath(m_ctx);
		nvgRect(m_ctx, RECT_FLOATS(rect));
		nvgFillPaint(m_ctx, imgPaint);
		nvgFill(m_ctx);
	}

	void VgNano::draw_color_wheel(const vec2& center, float r0, float r1)
	{
		float aeps = 0.5f / r1;	// half a pixel arc length in radians (2pi cancels out).

		for(int i = 0; i < 6; i++)
		{
			float a0 = (float)i / 6.0f * M_PI * 2.0f - aeps;
			float a1 = (float)(i + 1.0f) / 6.0f * M_PI * 2.0f + aeps;
			nvgBeginPath(m_ctx);
			nvgMoveTo(m_ctx, center.x + r0 * cosf(a0), center.y + r0 * sinf(a0));
			nvgLineTo(m_ctx, center.x + r0 * cosf(a1), center.y + r0 * sinf(a1));
			nvgLineTo(m_ctx, center.x + r1 * cosf(a1), center.y + r1 * sinf(a1));
			nvgLineTo(m_ctx, center.x + r1 * cosf(a0), center.y + r1 * sinf(a0));
			//nvgArc(m_ctx, center.x, center.y, r0, a0, a1, NVG_CW);
			//nvgArc(m_ctx, center.x, center.y, r1, a1, a0, NVG_CCW);
			nvgClosePath(m_ctx);
			vec2 a = vec2{ cosf(a0), sinf(a0) } * (r0 + r1) * 0.5f + center;
			vec2 b = vec2{ cosf(a1), sinf(a1) } * (r0 + r1) * 0.5f + center;
			NVGpaint paint = nvgLinearGradient(m_ctx, a.x, a.y, b.x, b.y, nvgHSLA(a0 / (M_PI * 2), 1.0f, 0.55f, 255), nvgHSLA(a1 / (M_PI * 2), 1.0f, 0.55f, 255));
			nvgFillPaint(m_ctx, paint);
			nvgFill(m_ctx);
		}

#if 0
		nvgBeginPath(vg);
		renderer.path_circle(center, r0 - 0.5f);
		renderer.path_circle(center, r0 + 0.5f);
		renderer.stroke({ Colour::None, Colour(0.f, 0.f, 0.f, 64 / 255.f) , 1.0f });
#endif
	}

	void VgNano::draw_color_triangle(const vec2& center, float r0, float hue, float s, float l)
	{
		nvgTranslate(m_ctx, center.x, center.y);
		nvgRotate(m_ctx, hue * M_PI * 2);

		UNUSED(s); UNUSED(l);
#if 0
		// Circle marker
		float r1 = r0 + 20.f;
		nvgStrokeWidth(m_ctx, 2.0f);
		nvgBeginPath(m_ctx);
		nvgRect(m_ctx, r0 - 1, -3, r1 - r0 + 2, 6);
		nvgStrokeColor(m_ctx, nvgRGBA(255, 255, 255, 192));
		nvgStroke(m_ctx);

		paint = nvgBoxGradient(vg, r0 - 3, -5, r1 - r0 + 6, 10, 2, 4, nvgRGBA(0, 0, 0, 128), nvgRGBA(0, 0, 0, 0));
		nvgBeginPath(vg);
		nvgRect(vg, r0 - 2 - 10, -4 - 10, r1 - r0 + 4 + 20, 8 + 20);
		nvgRect(vg, r0 - 2, -4, r1 - r0 + 4, 8);
		nvgPathWinding(vg, NVG_HOLE);
		nvgFillPaint(vg, paint);
		nvgFill(vg); */

#endif

		float r = r0 - 14.f;
		vec2 a = vec2{ cosf(120.0f / 180.0f * M_PI), sinf(120.0f / 180.0f * M_PI) } *r;
		vec2 b = vec2{ cosf(-120.0f / 180.0f * M_PI), sinf(-120.0f / 180.0f * M_PI) } *r;

		nvgBeginPath(m_ctx);
		nvgMoveTo(m_ctx, r, 0);
		nvgLineTo(m_ctx, a.x, a.y);
		nvgLineTo(m_ctx, b.x, b.y);
		nvgClosePath(m_ctx);

		NVGpaint paint1 = nvgLinearGradient(m_ctx, r, 0, a.x, a.y, nvgHSLA(hue, 1.0f, 0.5f, 255), nvgRGBA(255, 255, 255, 255));
		nvgFillPaint(m_ctx, paint1);
		nvgFill(m_ctx);
		NVGpaint paint2 = nvgLinearGradient(m_ctx, (r + a.x)*0.5f, (0 + a.y)*0.5f, b.x, b.y, nvgRGBA(0, 0, 0, 0), nvgRGBA(0, 0, 0, 255));
		nvgFillPaint(m_ctx, paint2);
		nvgFill(m_ctx);

		nvgStrokeColor(m_ctx, nvgRGBA(0, 0, 0, 64));
		nvgStroke(m_ctx);

		// Select circle on triangle
		float ax = cosf(120.0f / 180.0f*NVG_PI) * r*0.3f;
		float ay = sinf(120.0f / 180.0f*NVG_PI) * r*0.4f;
		nvgStrokeWidth(m_ctx, 2.0f);
		nvgBeginPath(m_ctx);
		nvgCircle(m_ctx, ax, ay, 5);
		nvgStrokeColor(m_ctx, nvgRGBA(255, 255, 255, 192));
		nvgStroke(m_ctx);

		NVGpaint paint3 = nvgRadialGradient(m_ctx, ax, ay, 7, 9, nvgRGBA(0, 0, 0, 64), nvgRGBA(0, 0, 0, 0));
		nvgBeginPath(m_ctx);
		nvgRect(m_ctx, ax - 20, ay - 20, 40, 40);
		nvgCircle(m_ctx, ax, ay, 7);
		nvgPathWinding(m_ctx, NVG_HOLE);
		nvgFillPaint(m_ctx, paint3);
		nvgFill(m_ctx);
	}

	void VgNano::setup_text(const TextPaint& paint)
	{
		NVGalign alignH = NVG_ALIGN_LEFT;
		if(paint.m_align.x == CENTER)
			alignH = NVG_ALIGN_CENTER;
		else if(paint.m_align.x == RIGHT)
			alignH = NVG_ALIGN_RIGHT;

		nvgFontSize(m_ctx, paint.m_size);
		nvgFontFace(m_ctx, paint.m_font);
		nvgTextAlign(m_ctx, alignH | NVG_ALIGN_BOTTOM);

		m_line_height = 0.f;
		nvgTextMetrics(m_ctx, nullptr, nullptr, &m_line_height);
	}

	void VgNano::break_text(cstring text, size_t len, const vec2& space, const TextPaint& paint, vector<TextRow>& text_rows)
	{
		this->setup_text(paint);
		VgRenderer::break_text(text, len, space, paint, text_rows);
	}

	void VgNano::break_next_row(const char* first, const char* end, const vec4& rect, const TextPaint& paint, TextRow& row)
	{
		UNUSED(paint);
		NVGtextRow nvgTextRow;
		nvgTextBreakLines(m_ctx, first, end, rect.z, &nvgTextRow, 1);

		row.m_start = nvgTextRow.start;
		row.m_end = nvgTextRow.end;
		row.m_rect = vec4{ rect.x, rect.y, nvgTextRow.width, m_line_height };
	}

	void VgNano::break_glyphs(const vec4& rect, const TextPaint& paint, TextRow& textRow)
	{
		UNUSED(paint);
		size_t numGlyphs = textRow.m_end - textRow.m_start;
		vector<NVGglyphPosition> glyphs(numGlyphs);
		textRow.m_glyphs.resize(numGlyphs);

		nvgTextGlyphPositions(m_ctx, rect.x, rect.y, textRow.m_start, textRow.m_end, &glyphs.front(), glyphs.size());

		for(size_t i = 0; i < glyphs.size(); ++i)
		{
			textRow.m_glyphs[i].m_position = textRow.m_start + i;
			textRow.m_glyphs[i].m_rect = vec4{ glyphs[i].minx, textRow.m_rect.y, glyphs[i].maxx - glyphs[i].minx, rect_h(textRow.m_rect) };
		}
	}

	void VgNano::draw_text(const vec2& offset, const char* start, const char* end, const TextPaint& paint)
	{
		this->setup_text(paint);

		nvgFillColor(m_ctx, nvgColour(paint.m_colour));
		nvgText(m_ctx, offset.x, offset.y + m_line_height, start, end);
	}

	void VgNano::begin_target()
	{
		nvgSave(m_ctx);
		nvgResetTransform(m_ctx);
		nvgResetScissor(m_ctx);
	}

	void VgNano::end_target()
	{
		nvgRestore(m_ctx);
	}

#ifdef TWO_UI_DRAW_CACHE
	NVGdisplayList* VgNano::layer_cache(Layer& layer)
	{
		if(m_layers.find(&layer) == m_layers.end())
			m_layers[&layer] = nvgCreateDisplayList(-1);

		return m_layers[&layer];
	}

	void VgNano::begin_cached(Layer& layer)
	{
		nvgResetDisplayList(this->layer_cache(layer));
		nvgBindDisplayList(m_ctx, this->layer_cache(layer));
	}

	void VgNano::end_cached()
	{
		nvgBindDisplayList(m_ctx, nullptr);
	}

	void VgNano::draw_layer(Layer& layer, const vec2& position, float scale)
	{
		nvgSave(m_ctx);
		nvgTranslate(m_ctx, position.x, position.y);
		nvgScale(m_ctx, scale, scale);
		nvgDrawDisplayList(m_ctx, this->layer_cache(layer));
		nvgRestore(m_ctx);
	}

#endif

	void VgNano::begin_layer(Layer& layer, const vec2& position, float scale)
	{
		UNUSED(layer);
		nvgSave(m_ctx);
		nvgTranslate(m_ctx, position.x, position.y);
		nvgScale(m_ctx, scale, scale);
	}

	void VgNano::end_layer()
	{
		nvgRestore(m_ctx);
	}

	void VgNano::begin_update(const vec2& position, float scale)
	{
		nvgSave(m_ctx);
		nvgTranslate(m_ctx, position.x, position.y);
		nvgScale(m_ctx, scale, scale);
	}

	void VgNano::end_update()
	{
		nvgRestore(m_ctx);
	}

	float VgNano::line_height(const TextPaint& paint)
	{
		this->setup_text(paint);
		return m_line_height;
	}

	vec2 VgNano::text_size(cstring text, size_t len, const TextPaint& paint)
	{
		this->setup_text(paint);

		float bounds[4];
		nvgTextBounds(m_ctx, 0.f, 0.f, text, text + len, bounds);

		return { bounds[2] - bounds[0], m_line_height };
	}

	float VgNano::text_size(cstring text, size_t len, Dim dim, const TextPaint& paint)
	{
		return dim == DIM_X ? text_size(text, len, paint).x : text_size(text, len, paint).y;
	}
}
