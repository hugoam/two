//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <cmath>
#include <cfloat>
#endif

#ifdef MUD_MODULES
#define _GLIBCXX_TYPE_TRAITS
#endif
#include <vg/vg.h>
#include <bgfx/bgfx.h>

#ifdef MUD_MODULES
module mud.ui.vg;
#else
#include <stb_image.h>
#include <stb_truetype.h>

#include <infra/File.h>
#include <math/Math.h>
#include <ui/Style/Paint.h>
#include <ui/Frame/Layer.h>
#include <math/ImageAtlas.h>
#include <ui-vg/VgVg.h>
#endif

namespace vg
{
	bool checkIntersectScissor(Context* ctx, float x, float y, float w, float h);
}

namespace mud
{
	inline vg::Color vgColour(const Colour& colour)
	{
		return vg::color4f(colour.m_r, colour.m_g, colour.m_b, colour.m_a);
	}

#define RECT_FLOATS(rect) rect.x, rect.y, rect.z, rect.w

	VgVg::VgVg(cstring resource_path, bx::AllocatorI* allocator)
		: Vg(resource_path)
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

		m_vg = vg::createContext(240, m_allocator, &config);
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

	void VgVg::begin_frame(const vec4& rect, float pixel_ratio)
	{
		bgfx::setViewRect(240, uint16_t(rect.x), uint16_t(rect.y), uint16_t(rect_w(rect)), uint16_t(rect_h(rect)));
		bgfx::setViewMode(240, bgfx::ViewMode::Sequential);
		bgfx::setViewName(240, "ui");

		vg::beginFrame(m_vg, uint16_t(rect_w(rect)), uint16_t(rect_h(rect)), pixel_ratio);
	}

	void VgVg::end_frame()
	{
		vg::endFrame(m_vg);
	}

	bool VgVg::clipped(const vec4& rect)
	{
#ifdef MUD_UI_DRAW_CACHE
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

		vec4 path_rect = { rect_offset(rect) + border * 0.5f, rect_size(rect) - border };
		if(corners == Zero4)
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
		vec4 shadow_rect = { rect_offset(rect) + shadow.d_pos - shadow.d_radius, rect_size(rect) + shadow.d_radius * 2.f };
		vec4 gradient_rect = { rect_offset(rect) + shadow.d_pos - shadow.d_spread, rect_size(rect) + shadow.d_spread * 2.f };
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
		float aeps = 0.5f / r1;	// half a pixel arc length in radians (2pi cancels out).

		for(int i = 0; i < 6; i++)
		{
			float a0 = (float)i / 6.0f * c_pi * 2.0f - aeps;
			float a1 = (float)(i + 1.0f) / 6.0f * c_pi * 2.0f + aeps;
			vg::beginPath(m_vg);
			vg::moveTo(m_vg, center.x + r0 * cosf(a0), center.y + r0 * sinf(a0));
			vg::lineTo(m_vg, center.x + r0 * cosf(a1), center.y + r0 * sinf(a1));
			vg::lineTo(m_vg, center.x + r1 * cosf(a1), center.y + r1 * sinf(a1));
			vg::lineTo(m_vg, center.x + r1 * cosf(a0), center.y + r1 * sinf(a0));

			//vg::ArcTo(center.x, center.y, a0, a1, r0); //, NVG_CW);
			//vg::ArcTo(center.x, center.y, a1, a0, r1); //, NVG_CCW);
			vg::closePath(m_vg);
			vec2 a = vec2{ cosf(a0), sinf(a0) } *(r0 + r1) * 0.5f + center;
			vec2 b = vec2{ cosf(a1), sinf(a1) } *(r0 + r1) * 0.5f + center;
			Colour colour_a = hsla_to_rgba(Colour{ a0 / (c_pi * 2.f), 1.0f, 0.55f });
			Colour colour_b = hsla_to_rgba(Colour{ a1 / (c_pi * 2.f), 1.0f, 0.55f });
			vg::GradientHandle paint = vg::createLinearGradient(m_vg, a.x, a.y, b.x, b.y, vgColour(colour_a), vgColour(colour_b));
			vg::fillPath(m_vg, paint, vg::FillFlags::ConvexAA);
		}
	}

	void VgVg::draw_color_triangle(const vec2& center, float r0, float hue, float s, float l)
	{
		UNUSED(s); UNUSED(l);
		vg::transformTranslate(m_vg, center.x, center.y);
		vg::transformRotate(m_vg, hue * c_pi * 2);

		float r = r0 - 6;
		vec2 a = vec2{ cosf(120.0f / 180.0f * c_pi), sinf(120.0f / 180.0f * c_pi) } *r;
		vec2 b = vec2{ cosf(-120.0f / 180.0f * c_pi), sinf(-120.0f / 180.0f * c_pi) } *r;

		vg::beginPath(m_vg);
		vg::moveTo(m_vg, r, 0);
		vg::lineTo(m_vg, a.x, a.y);
		vg::lineTo(m_vg, b.x, b.y);
		vg::closePath(m_vg);

		Colour colour = hsla_to_rgba(Colour{ hue, 1.0f, 0.5f });
		vg::GradientHandle paint1 = vg::createLinearGradient(m_vg, r, 0, a.x, a.y, vgColour(colour), vg::Colors::White);
		vg::fillPath(m_vg, paint1, vg::FillFlags::ConvexAA);
		vg::GradientHandle paint2 = vg::createLinearGradient(m_vg, (r + a.x) * 0.5f, (0 + a.y) * 0.5f, b.x, b.y, vg::Colors::Transparent, vg::Colors::Black);
		vg::fillPath(m_vg, paint2, vg::FillFlags::ConvexAA);

		vg::strokePath(m_vg, vg::color4ub(0, 0, 0, 64), 1.f, vg::StrokeFlags::ButtMiterAA);
	}

	uint32_t VgVg::text_align(const TextPaint& paint)
	{
		if(paint.m_align.x == CENTER)
			return vg::TextAlign::Center | vg::TextAlign::Top;
		else if(paint.m_align.x == Right)
			return vg::TextAlign::Right | vg::TextAlign::Top;
		else
			return vg::TextAlign::Left | vg::TextAlign::Top;
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
		size_t numGlyphs = textRow.m_end - textRow.m_start;
		vector<vg::GlyphPosition> glyphs(numGlyphs);
		textRow.m_glyphs.resize(numGlyphs);

		vg::textGlyphPositions(m_vg, text_font(paint), rect.x, rect.y, textRow.m_start, textRow.m_end, &glyphs.front(), int(glyphs.size()));

		for(size_t i = 0; i < glyphs.size(); ++i)
		{
			textRow.m_glyphs[i].m_position = textRow.m_start + i;
			textRow.m_glyphs[i].m_rect = vec4{ glyphs[i].minx, textRow.m_rect.y, glyphs[i].maxx - glyphs[i].minx, rect_h(textRow.m_rect) };
		}
	}

	void VgVg::draw_text(const vec2& offset, const char* start, const char* end, const TextPaint& paint)
	{
		if(paint.m_text_break)
			vg::textBox(m_vg, text_font(paint), offset.x, offset.y, FLT_MAX, start, end);
		else
			vg::text(m_vg, text_font(paint), offset.x, offset.y, start, end);
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

#ifdef MUD_UI_DRAW_CACHE
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
		float bounds[4];
		if(paint.m_text_break)
			vg::measureTextBox(m_vg, text_font(paint), 0, 0, FLT_MAX, text, text + len, bounds, 0); //vg::TextBreakFlags::SpacesAsChars
		else
			vg::measureText(m_vg, text_font(paint), 0, 0, text, text + len, bounds);
		return { bounds[2] - bounds[0], bounds[3] - bounds[1] };
	}

	float VgVg::text_size(cstring text, size_t len, Dim dim, const TextPaint& paint)
	{
		return dim == DIM_X ? text_size(text, len, paint).x : text_size(text, len, paint).y;
	}
}
