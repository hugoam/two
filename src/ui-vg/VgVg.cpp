//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
#include <vg/vg.h>
#include <bgfx/bgfx.h>
#include <stb_image.h>
#include <stb_truetype.h>
module two.ui.vg;

#define ANGLED_WHEEL 0

namespace vg
{
	bool checkIntersectScissor(Context* ctx, float x, float y, float w, float h);
}

namespace two
{
	inline vg::Color vgColour(const Colour& colour)
	{
		return vg::color4f(colour.r, colour.g, colour.b, colour.a);
	}

#define RECT_FLOATS(rect) rect.x, rect.y, rect.z, rect.w

	VgVg::VgVg(const string& resource_path, bx::AllocatorI* allocator)
		: Vg(resource_path.c_str())
		, m_allocator(allocator)
	{}

	VgVg::~VgVg()
	{}

	void VgVg::setup_context()
	{
		// @todo m_MaxImagePatterns has a very annoying limitation with command lists because each one allocates its own patterns
		static const vg::ContextConfig config =
		{
			256,								// m_MaxGradients
			2048,								// m_MaxImagePatterns
			8,									// m_MaxFonts
			256,								// m_MaxStateStackSize
			16,									// m_MaxImages
			256,								// m_MaxCommandLists
			65536,								// m_MaxVBVertices
			vg::ImageFlags::Filter_Bilinear,	// m_FontAtlasImageFlags
			16									// m_MaxCommandListDepth
		};

		m_vg = vg::createContext(m_allocator, &config);
	}

	void VgVg::release_context()
	{
		vg::destroyContext(m_vg);
	}

	void VgVg::load_default_font()
	{
		if(m_null) return;
		this->load_font("dejavu");
		m_default_font = m_fonts["dejavu"];
	}

	void VgVg::load_font(cstring name)
	{
		string path = this->font_path(name);
		vector<uint8_t> buffer = read_binary_file(path);
		m_fonts[name] = vg::createFont(m_vg, name, buffer.data(), uint32_t(buffer.size()), 0);
	}

	void VgVg::load_image_RGBA(Image& image, const unsigned char* data)
	{
		if(m_null) return;
		vg::ImageHandle vgimage = vg::createImage(m_vg, uint16_t(image.d_size.x), uint16_t(image.d_size.y), image.d_filtering ? vg::ImageFlags::Enum(0) : vg::ImageFlags::Filter_Nearest, data);
		image.d_handle = vgimage.idx;
	}

	void VgVg::load_image(Image& image)
	{
		if(m_null) return;
		int w, h, n;
		stbi_set_unpremultiply_on_load(1);
		stbi_convert_iphone_png_to_rgb(1);
		unsigned char* img = stbi_load(image.d_path.c_str(), &w, &h, &n, 4);
		vg::ImageHandle vgimage = vg::createImage(m_vg, uint16_t(image.d_size.x), uint16_t(image.d_size.y), image.d_filtering ? vg::ImageFlags::Enum(0) : vg::ImageFlags::Filter_Nearest, img);
		image.d_handle = vgimage.idx;
		stbi_image_free(img);
	}

	void VgVg::unload_image(Image& image)
	{
		if(m_null) return;
		vg::destroyImage(m_vg, { uint16_t(image.d_handle) });
		image.d_handle = 0;
	}

	uint16_t VgVg::load_texture(uint16_t texture)
	{
		vg::ImageHandle vgimage = vg::createImage(m_vg, vg::ImageFlags::Filter_Nearest, { texture });
		return vgimage.idx;
	}

	void VgVg::begin_frame(uint16_t view, const vec4& rect, float pixel_ratio, const Colour& colour)
	{
		bgfx::setViewClear(view, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, to_rgba(colour), 1.0f, 0);
		bgfx::setViewRect(view, uint16_t(rect.x), uint16_t(rect.y), uint16_t(rect.width), uint16_t(rect.height));
		bgfx::setViewMode(view, bgfx::ViewMode::Sequential);
		bgfx::setViewName(view, "ui");

		vg::begin(m_vg, view, uint16_t(rect.width), uint16_t(rect.height), pixel_ratio);
	}

	void VgVg::end_frame(uint16_t view)
	{
		UNUSED(view);
		vg::end(m_vg);
		vg::frame(m_vg);
	}

	bool VgVg::clipped(const vec4& rect)
	{
#ifdef TWO_UI_DRAW_CACHE
		UNUSED(rect);
		return false;
#else
		return !vg::checkIntersectScissor(m_vg, RECT_FLOATS(rect));
#endif
	}

	void VgVg::clip(const vec4& rect)
	{
		vg::intersectScissor(m_vg, RECT_FLOATS(rect));
	}

	void VgVg::unclip()
	{
		vg::resetScissor(m_vg);
	}

	void VgVg::begin_path()
	{
		vg::beginPath(m_vg);
	}

	void VgVg::move_to(const vec2& p)
	{
		vg::moveTo(m_vg, p.x, p.y);
	}

	void VgVg::line_to(const vec2& p)
	{
		vg::lineTo(m_vg, p.x, p.y);
	}
	
	void VgVg::close_path()
	{
		vg::closePath(m_vg);
	}

	void VgVg::path_line(const vec2& p1, const vec2& p2)
	{
		vg::beginPath(m_vg);
		vg::moveTo(m_vg, p1.x, p1.y);
		vg::lineTo(m_vg, p2.x, p2.y);
	}

	void VgVg::path_bezier(const vec2& p1, const vec2& c1, const vec2& c2, const vec2& p2, bool straighten)
	{
		vg::beginPath(m_vg);
		vg::moveTo(m_vg, p1.x, p1.y);
		if(straighten)
		{
			vg::lineTo(m_vg, c1.x, c1.y);
			vg::lineTo(m_vg, c2.x, c2.y);
			vg::lineTo(m_vg, p2.x, p2.y);
		}
		else
			vg::cubicTo(m_vg, c1.x, c1.y, c2.x, c2.y, p2.x, p2.y);
	}

	void VgVg::path_rect(const vec4& rect, const vec4& corners, float border)
	{
		vg::beginPath(m_vg);

		vec4 path_rect = { rect.pos + border * 0.5f, rect.size - border };
		if(corners == vec4(0.f))
			vg::rect(m_vg, RECT_FLOATS(path_rect));
		else
			vg::roundedRectVarying(m_vg, RECT_FLOATS(path_rect), RECT_FLOATS(corners));
	}

	void VgVg::path_circle(const vec2& center, float r)
	{
		vg::beginPath(m_vg);
		vg::circle(m_vg, center.x, center.y, r);
	}

	void VgVg::draw_shadow(const vec4& rect, const vec4& corners, const Shadow& shadow)
	{
		const vec4 shadow_rect = { rect.pos + shadow.d_pos - shadow.d_radius, rect.size + shadow.d_radius * 2.f };
		const vec4 gradient_rect = { rect.pos + shadow.d_pos - shadow.d_spread, rect.size + shadow.d_spread * 2.f };
		vg::GradientHandle shadowPaint = vg::createBoxGradient(m_vg, RECT_FLOATS(gradient_rect), corners[0] + shadow.d_spread, shadow.d_blur, vgColour(shadow.d_colour), vg::Colors::Transparent);
		vg::beginPath(m_vg);
		vg::rect(m_vg, RECT_FLOATS(shadow_rect));
		vg::fillPath(m_vg, shadowPaint, vg::FillFlags::ConvexAA);
	}

	void VgVg::fill(const Gradient& gradient, const vec2& start, const vec2& end)
	{
		vg::GradientHandle paint = vg::createLinearGradient(m_vg, start.x, start.y, end.x, end.y, vgColour(gradient.m_start), vgColour(gradient.m_end));
		vg::fillPath(m_vg, paint, vg::FillFlags::ConvexAA);
	}

	void VgVg::fill(const Paint& paint)
	{
		vg::fillPath(m_vg, vgColour(paint.m_fill_colour), vg::FillFlags::ConvexAA);
	}

	void VgVg::stroke(const Paint& paint)
	{
		vg::strokePath(m_vg, vgColour(paint.m_stroke_colour), paint.m_stroke_width, vg::StrokeFlags::ButtMiterAA);
	}

	void VgVg::stroke_gradient(const Gradient& paint, float width, const vec2& start, const vec2& end)
	{
		vg::GradientHandle gradient = vg::createLinearGradient(m_vg, start.x, start.y, end.x, end.y, vgColour(paint.m_start), vgColour(paint.m_end));
		vg::strokePath(m_vg, gradient, width, vg::StrokeFlags::ButtMiterAA);
	}

	void VgVg::draw_texture(uint16_t image, const vec4& rect, const vec4& image_rect)
	{
		vg::ImagePatternHandle pattern = vg::createImagePattern(m_vg, RECT_FLOATS(image_rect), 0.0f, { image });
		vg::beginPath(m_vg);
		vg::rect(m_vg, RECT_FLOATS(rect));
		vg::fillPath(m_vg, pattern, vg::Colors::White, vg::FillFlags::ConvexAA);
	}

	void VgVg::draw_color_wheel(const vec2& center, float r0, float r1)
	{
		const float aeps = 0.5f / r1; // half a pixel arc length in radians (2pi cancels out).

		for(int i = 0; i < 6; i++)
		{
			const float a0 = float(i) / 6.0f * c_2pi - aeps;
			const float a1 = (float(i) + 1.0f) / 6.0f * c_2pi + aeps;

			vg::beginPath(m_vg);
#if ANGLED_WHEEL
			vg::moveTo(m_vg, center.x + r0 * cosf(a0), center.y + r0 * sinf(a0));
			vg::lineTo(m_vg, center.x + r0 * cosf(a1), center.y + r0 * sinf(a1));
			vg::lineTo(m_vg, center.x + r1 * cosf(a1), center.y + r1 * sinf(a1));
			vg::lineTo(m_vg, center.x + r1 * cosf(a0), center.y + r1 * sinf(a0));
#else
			vg::arc(m_vg, center.x, center.y, r0, a0, a1, vg::Winding::CW);
			vg::arc(m_vg, center.x, center.y, r1, a1, a0, vg::Winding::CCW);
			//vg::arc(m_vg, center.x, center.y, r1, a0, a1, vg::Winding::CCW);
#endif
			vg::closePath(m_vg);

			const vec2 a = vec2(cosf(a0), sinf(a0)) * (r0 + r1) * 0.5f + center;
			const vec2 b = vec2(cosf(a1), sinf(a1)) * (r0 + r1) * 0.5f + center;
			const Colour cola = hsl(a0 / c_2pi, 1.0f, 0.55f);
			const Colour colb = hsl(a1 / c_2pi, 1.0f, 0.55f);

			vg::GradientHandle paint = vg::createLinearGradient(m_vg, a.x, a.y, b.x, b.y, vgColour(cola), vgColour(colb));
			vg::fillPath(m_vg, paint, vg::FillFlags::ConcaveAA);
			//vg::strokePath(m_vg, paint, 1.f, vg::FillFlags::ConcaveAA);
		}
	}

	void VgVg::draw_color_triangle(const vec2& center, float r0, float hue, float s, float l)
	{
		UNUSED(s); UNUSED(l);
		vg::transformTranslate(m_vg, center.x, center.y);
		vg::transformRotate(m_vg, hue * c_2pi);

		const float r = r0 - 6;
		const vec2 a = vec2(cosf(120.0f / 180.0f * c_pi), sinf(120.0f / 180.0f * c_pi)) * r;
		const vec2 b = vec2(cosf(-120.0f / 180.0f * c_pi), sinf(-120.0f / 180.0f * c_pi)) * r;

		vg::beginPath(m_vg);
		vg::moveTo(m_vg, r, 0);
		vg::lineTo(m_vg, a.x, a.y);
		vg::lineTo(m_vg, b.x, b.y);
		vg::closePath(m_vg);

		const Colour colour = hsl(hue, 1.0f, 0.5f);
		vg::GradientHandle paint1 = vg::createLinearGradient(m_vg, r, 0, a.x, a.y, vgColour(colour), vg::Colors::White);
		vg::fillPath(m_vg, paint1, vg::FillFlags::ConvexAA);
		vg::GradientHandle paint2 = vg::createLinearGradient(m_vg, (r + a.x) * 0.5f, (0 + a.y) * 0.5f, b.x, b.y, vg::Colors::Transparent, vg::Colors::Black);
		vg::fillPath(m_vg, paint2, vg::FillFlags::ConvexAA);

		//vg::strokePath(m_vg, vg::color4ub(0, 0, 0, 64), 1.f, vg::StrokeFlags::ButtMiterAA);
	}

	uint32_t VgVg::text_align(const TextPaint& paint)
	{
		const uint32_t yalign = vg::TextAlign::Middle; //vg::TextAlign::Top;
		if(paint.m_align.x == Align::Center)
			return vg::TextAlign::Center | yalign;
		else if(paint.m_align.x == Align::Right)
			return vg::TextAlign::Right | yalign;
		else
			return vg::TextAlign::Left | yalign;
	}

	vg::TextConfig VgVg::text_font(const TextPaint& paint)
	{
		if(m_fonts.find(paint.m_font) == m_fonts.end())
			this->load_font(paint.m_font);
		return { m_fonts[paint.m_font], paint.m_size, text_align(paint), vgColour(paint.m_colour) };
	}

	void VgVg::break_next_row(const char* text, const char* first, const char* end, const vec4& rect, const TextPaint& paint, TextRow& row)
	{
		vg::TextRow vgTextRow;
		vg::textBreakLines(m_vg, text_font(paint), first, end, rect.z, &vgTextRow, 1, 0);

		row = text_row(text, vgTextRow.start, vgTextRow.end, { rect.x, rect.y, vgTextRow.width, line_height(paint) });
	}

	void VgVg::break_glyphs(const vec4& rect, const TextPaint& paint, TextRow& textRow)
	{
		const size_t numGlyphs = textRow.m_end - textRow.m_start;
		vector<vg::GlyphPosition> glyphs(numGlyphs);
		textRow.m_glyphs.resize(numGlyphs);

		vg::textGlyphPositions(m_vg, text_font(paint), rect.x, rect.y, textRow.m_start, textRow.m_end, &glyphs.front(), int(glyphs.size()));

		for(size_t i = 0; i < glyphs.size(); ++i)
		{
			textRow.m_glyphs[i].m_position = textRow.m_start + i;
			textRow.m_glyphs[i].m_rect = { glyphs[i].minx, textRow.m_rect.y, glyphs[i].maxx - glyphs[i].minx, textRow.m_rect.height };
		}
	}

	void VgVg::draw_text(const vec2& offset, const char* start, const char* end, const TextPaint& paint)
	{
		const float yoff = ceil(paint.m_size * 0.5f);// + 1;
		if(paint.m_text_break)
			vg::textBox(m_vg, text_font(paint), offset.x, offset.y + yoff, FLT_MAX, start, end, 0); // vg::TextBoxFlags::KeepSpaces);
		else
			vg::text(m_vg, text_font(paint), offset.x, offset.y + yoff, start, end);
	}

	void VgVg::begin_target()
	{
		vg::pushState(m_vg);
		vg::transformIdentity(m_vg);
		//vg::resetScissor(m_vg);
	}

	void VgVg::end_target()
	{
		vg::popState(m_vg);
	}

#ifdef TWO_UI_DRAW_CACHE
	vg::CommandListHandle VgVg::layer_cache(Layer& layer)
	{
		if(layer.d_handle == SIZE_MAX)
			//layer.d_handle = vg::createCommandList(m_vg, vg::CommandListFlags::Cacheable).idx;
			layer.d_handle = vg::createCommandList(m_vg, 0).idx;
		return { uint16_t(layer.d_handle) };
	}

	void VgVg::begin_cached(Layer& layer)
	{
		vg::resetCommandList(m_vg, this->layer_cache(layer));
		vg::beginCommandList(m_vg, this->layer_cache(layer));
		vg::transformIdentity(m_vg);
	}

	void VgVg::end_cached()
	{
		vg::endCommandList(m_vg);
	}

	void VgVg::draw_layer(Layer& layer, const vec2& position, float scale)
	{
		UNUSED(position); UNUSED(scale);
		vg::pushState(m_vg);
		vg::setGlobalAlpha(m_vg, 1.f);
		vg::transformIdentity(m_vg);
		vg::submitCommandList(m_vg, this->layer_cache(layer));
		vg::popState(m_vg);
	}
#endif

	void VgVg::begin_layer(Layer& layer, const vec2& position, float scale)
	{
		UNUSED(layer);
		vg::pushState(m_vg);
		//vg::transformIdentity(m_vg);
		vg::transformTranslate(m_vg, position.x, position.y);
		vg::transformScale(m_vg, scale, scale);
	}

	void VgVg::end_layer()
	{
		vg::popState(m_vg);
	}

	void VgVg::begin_update(const vec2& position, float scale)
	{
		vg::pushState(m_vg);
		vg::transformTranslate(m_vg, position.x, position.y);
		vg::transformScale(m_vg, scale, scale);
	}

	void VgVg::end_update()
	{
		vg::popState(m_vg);
	}

	float VgVg::line_height(const TextPaint& paint)
	{
		return vg::getTextLineHeight(m_vg, text_font(paint));
	}

	vec2 VgVg::text_size(cstring text, size_t len, const TextPaint& paint)
	{
		vec4 bounds;
		if(paint.m_text_break)
			vg::measureTextBox(m_vg, text_font(paint), 0, 0, FLT_MAX, text, text + len, bounds.f, 0); //vg::TextBreakFlags::SpacesAsChars
		else
			vg::measureText(m_vg, text_font(paint), 0, 0, text, text + len, bounds.f);
		return vec2(bounds.width - bounds.x, bounds.height - bounds.y);
	}

	float VgVg::text_size(cstring text, size_t len, Axis dim, const TextPaint& paint)
	{
		return dim == Axis::X ? text_size(text, len, paint).x : text_size(text, len, paint).y;
	}
}
