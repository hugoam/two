//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <map>
#include <string>
#endif

#ifdef MUD_MODULES
module mud.ui;
#else
#include <math/Clamp.h>
#include <ui/Render/Renderer.h>
#include <ui/Frame/Layer.h>
#include <ui/Frame/Solver.h>
#include <ui/Widget.h>
#include <ui/Sheet.h>
#include <ui/Edit/TypeIn.h>
#include <ui/Style/Skin.h>
#include <math/ImageAtlas.h>
#endif

namespace mud
{
	using std::clamp;
	using string = std::string;

	inline Colour offset_colour(const Colour& colour, float delta)
	{
		float offset = delta / 255.0f;
		return Colour(clamp(colour.m_r + offset, 0.f, 1.f),
					  clamp(colour.m_g + offset, 0.f, 1.f),
					  clamp(colour.m_b + offset, 0.f, 1.f),
					  colour.m_a);
	}

	struct Vg::Impl
	{
		string m_resource_path;
		std::map<string, string> m_font_sources;
	};

	Vg::Vg(cstring resource_path)
		: m_impl(make_unique<Impl>())
	{
		m_impl->m_resource_path = resource_path;

		Frame::s_vg = this;
		Text::s_vg = this;

		m_impl->m_font_sources["dejavu"] = string(resource_path) + "interface/fonts/DejaVuSans.ttf";
		m_impl->m_font_sources["consolas"] = string(resource_path) + "interface/fonts/Consolas.ttf";
		m_impl->m_font_sources["consolas-bold"] = string(resource_path) + "interface/fonts/Consolas-Bold.ttf";
		m_impl->m_font_sources["inconsolata"] = string(resource_path) + "interface/fonts/Inconsolata-Regular.ttf";
		m_impl->m_font_sources["inconsolata-bold"] = string(resource_path) + "interface/fonts/Inconsolata-Bold.ttf";
		m_impl->m_font_sources["veramono"] = string(resource_path) + "interface/fonts/VeraMono.ttf";
		m_impl->m_font_sources["veramono-bold"] = string(resource_path) + "interface/fonts/VeraMono-Bold.ttf";
	}

	Vg::~Vg()
	{}

	cstring Vg::font_path(cstring font)
	{
		return m_impl->m_font_sources[string(font)].c_str();
	}

	void Vg::draw_rect(const vec4& rect, const Paint& paint, const vec4& corners)
	{
		this->path_rect(rect, corners, paint.m_stroke_width);

		if(!paint.m_fill_colour.null())
			this->fill(paint);
		if(paint.m_stroke_width > 0.f)
			this->stroke(paint);
	}

	void Vg::debug_rect(const vec4& rect, const Colour& colour)
	{
		Paint paint = { Colour::None, colour, 1.f };
		this->draw_rect(rect, paint);
	}

	void Vg::fill_text(cstring text, size_t len, const vec4& rect, const TextPaint& paint, TextRow& row)
	{
		row = text_row(text, text, text + len, { rect.x, rect.y, this->text_size(text, len, DIM_X, paint), line_height(paint) });
		this->break_glyphs(rect, paint, row);
	}

	void Vg::break_text_width(const char* text, const char* first, const char* end, const vec4& rect, const TextPaint& paint, TextRow& row)
	{
		this->break_next_row(text, first, end, rect, paint, row);

		if(row.m_start != row.m_end)
			this->break_glyphs(rect, paint, row);
	}

	void Vg::break_text_returns(const char* text, const char* first, const char* end, const vec4& rect, const TextPaint& paint, TextRow& row)
	{
		const char* iter = first;

		while(*iter != '\n' && iter < end)
			++iter;

		row = text_row(text, first, iter, vec4{ rect.x, rect.y, this->text_size(first, iter - first, DIM_X, paint), line_height(paint) });
		this->break_glyphs(rect, paint, row);

		// @kludge because text_size doesn't report the correct size when there is a space at the end : investigate (vg-renderer, nanovg)
		if(!row.m_glyphs.empty())
			row.m_rect = vec4{ rect.x, rect.y, row.m_glyphs.back().m_rect.x + rect_w(row.m_glyphs.back().m_rect), line_height(paint) };
	}

	void Vg::break_text(cstring text, size_t len, const vec2& space, const TextPaint& paint, std::vector<TextRow>& textRows)
	{
		float line_height = this->line_height(paint);

		textRows.clear();

		if(!paint.m_text_break)
		{
			textRows.resize(1);

			vec4 rect(0.f, 0.f, space.x, line_height);
			this->fill_text(text, len, rect, paint, textRows[0]);
			return;
		}

		const char* first = text;
		const char* end = first + len;

		while(first < end)
		{
			size_t index = textRows.size();
			textRows.resize(index + 1);
			TextRow& row = textRows.back();

			vec4 rect(0.f, index * line_height, space.x, 0.f);
			if(paint.m_text_wrap)
				this->break_text_width(text, first, end, rect, paint, row);
			else
				this->break_text_returns(text, first, end, rect, paint, row);

			first = row.m_end + 1;
		}
	}

	struct UiRenderer::Impl
	{
		string m_debug_filter = "";
		bool m_debug_frame_rect = false;
		bool m_debug_fadded_rect = false;
		bool m_debug_fontent_rect = false;
		bool m_debug_flip_rect = false;
	};

	UiRenderer::UiRenderer(Vg& vg)
		: m_vg(vg)
		, m_impl(make_unique<Impl>())
	{
		Frame::s_vg = &m_vg;
		Text::s_vg = &m_vg;
	}

	UiRenderer::~UiRenderer()
	{}

	void UiRenderer::render(Layer& target)
	{
		this->log_FPS();

		m_debug_batch = 0;
		static size_t prevBatch = 0;

		m_vg.begin_frame({ vec2(0.f), target.m_frame.m_size });

#ifdef MUD_UI_DRAW_CACHE
		target.visit([&](Layer& layer) {
			if(layer.redraw() || layer.forceRedraw())
				this->render_layer(layer);
		});

		target.visit([&](Layer& layer) {
			m_vg.draw_layer(layer, Zero2, 1.f);
		});
#else
		target.visit([&](Layer& layer)
		{
			this->render_layer(layer);
		});
#endif

		if(m_debug_batch > 1 && m_debug_batch != prevBatch)
		{
			prevBatch = m_debug_batch;
			//printf("DEBUG: Render Frame : %i frames redrawn\n", m_debug_batch);
		}

		m_vg.end_frame();
	}

	void UiRenderer::render_layer(Layer& layer)
	{
		if(layer.master())
			m_vg.begin_target();

#ifdef MUD_UI_DRAW_CACHE
		m_vg.begin_cached(layer);
#endif

		if(layer.m_frame.d_parent)
			this->begin_layer(*layer.m_frame.d_parent);

		m_vg.begin_layer(layer);

		this->render_frame(layer.m_frame);

		m_vg.end_layer();
		layer.endRedraw();

		if(layer.m_frame.d_parent)
			this->end_layer(*layer.m_frame.d_parent);

#ifdef MUD_UI_DRAW_CACHE
		m_vg.end_cached();
#endif

		if(layer.master())
			m_vg.end_target();
	}

	inline bool flow(const Frame& frame) { return frame.d_style->layout().m_flow == FLOW; }
	inline bool clip(const Frame& frame) { return frame.d_style->layout().m_clipping == CLIP; }
	inline bool unclip(const Frame& frame) { return frame.d_style->layout().m_clipping == UNCLIP; }

	void UiRenderer::begin_frame(Frame& frame)
	{
		m_vg.begin_update(floor(frame.m_position), frame.m_scale);

		if(clip(frame))
		{
			m_vg.clip(frame.content_rect());
		}

		if(unclip(frame))
			m_vg.unclip();
	}

	void UiRenderer::end_frame(Frame& frame)
	{
		UNUSED(frame);
		m_vg.end_update();
	}

	void UiRenderer::begin_layer(Frame& frame)
	{
		if(frame.d_parent)
			this->begin_layer(*frame.d_parent);

		this->begin_frame(frame);
	}

	void UiRenderer::end_layer(Frame& frame)
	{
		this->end_frame(frame);

		if(frame.d_parent)
			this->end_layer(*frame.d_parent);
	}

	void UiRenderer::render_frame(Frame& frame)
	{
		this->begin_frame(frame);

		this->draw_frame(frame);

		for(auto& widget : frame.d_widget.m_nodes)
			if(!widget->m_frame.m_layer)
				this->render_frame(widget->m_frame);

		this->end_frame(frame);
	}

	void UiRenderer::draw_frame(const Frame& frame)
	{
		vec4 rect = frame.content_rect();

		if(m_vg.clipped(rect))
			return;

		if(frame.d_inkstyle->m_empty)
			return;

		if(frame.d_widget.m_custom_draw)
			return frame.d_widget.m_custom_draw(frame, rect, m_vg);

		if(frame.d_inkstyle->m_custom_draw)
			return frame.d_inkstyle->m_custom_draw(frame, rect, m_vg);
	
		this->draw_frame(frame, rect);
	}

	void UiRenderer::draw_frame(const Frame& frame, const vec4& rect)
	{
		vec4 padded_rect = { floor(rect_offset(frame.d_inkstyle->m_padding)),
							 floor(frame.m_size - rect_sum(frame.d_inkstyle->m_padding)) };

		vec2 content = frame.m_content;
		if(frame.d_inkstyle->m_stretch.x)
			content.x = rect_w(padded_rect);
		if(frame.d_inkstyle->m_stretch.y)
			content.y = rect_h(padded_rect);

		vec2 content_pos = { this->content_pos(frame, content, padded_rect, DIM_X), this->content_pos(frame, content, padded_rect, DIM_Y) };
		vec4 content_rect = { content_pos, content };
		
#if 0 // DEBUG
		if(frame.d_style->m_name == m_debug_filter)
			this->debug_rect(rect, Colour::Red);
		if(m_debug_frame_rect)
			this->debug_rect(rect, Colour::Red);
		if(m_debug_padded_rect)
			this->debug_rect(padded_rect, Colour::Green);
		if(m_debug_content_rect)
			this->debug_rect(content_rect, Colour::Blue);
#endif

		this->draw_background(frame, rect, padded_rect, content_rect);
		this->draw_content(frame, rect, padded_rect, content_rect);
	}

	float UiRenderer::content_pos(const Frame& frame, const vec2& content, const vec4& padded_rect, Dim dim)
	{
		if(frame.d_inkstyle->m_align[dim] == CENTER)
			return padded_rect[dim] + padded_rect[dim + 2] / 2.f - content[dim] / 2.f;
		else if(frame.d_inkstyle->m_align[dim] == RIGHT)
			return padded_rect[dim] + padded_rect[dim + 2] - content[dim];
		else
			return padded_rect[dim];
	}

	vec4 UiRenderer::select_corners(const Frame& frame)
	{
		Frame& parent = *frame.d_parent;

		const vec4& corners = parent.d_inkstyle->m_corner_radius;
		if(parent.first(frame))
			return parent.m_solver->d_length == DIM_X ? vec4(corners[0], 0.f, 0.f, corners[3]) : vec4(corners[0], corners[1], 0.f, 0.f);
		else if(parent.last(frame))
			return parent.m_solver->d_length == DIM_X ? vec4(0.f, corners[1], corners[2], 0.f) : vec4(0.f, 0.f, corners[2], corners[3]);
		else
			return vec4();
	}

	void UiRenderer::draw_background(const Frame& frame, const vec4& rect, const vec4& padded_rect, const vec4& content_rect)
	{
		m_debug_batch++;

		InkStyle& inkstyle = *frame.d_inkstyle;

		// Shadow
		if(!inkstyle.m_shadow.d_null)
		{
			m_vg.draw_shadow(rect, inkstyle.m_corner_radius, inkstyle.m_shadow);
		}

		// Rect
		if(inkstyle.m_border_width.x || !inkstyle.m_background_colour.null())
		{
			vec4 corners = inkstyle.m_weak_corners ? this->select_corners(frame) : inkstyle.m_corner_radius;
			this->draw_rect(rect, corners, inkstyle);
		}

		// ImageSkin
		ImageSkin& image_skin = inkstyle.m_image_skin;
		if(!image_skin.null())
		{
			float margin = image_skin.m_margin * 2.f;
			vec4 skin_rect = { rect_offset(rect), rect_size(rect) + margin };

			if(image_skin.d_stretch == DIM_X)
				skin_rect = { rect.x, content_rect.y + margin, rect.z + margin, image_skin.d_size.y };
			else if(image_skin.d_stretch == DIM_Y)
				skin_rect = { content_rect.x + image_skin.m_margin, rect.y, image_skin.d_size.x, rect.w + margin };

			vec4 sections[ImageSkin::Count];
			image_skin.stretch_coords(rect_offset(skin_rect), rect_size(skin_rect), { sections, ImageSkin::Count });

			for(size_t s = 0; s < ImageSkin::Count; ++s)
				this->draw_skin_image(frame, s, sections[s]);
		}

		// Image
		if(inkstyle.m_overlay)
			this->draw_image(*inkstyle.m_overlay, padded_rect);
		if(inkstyle.m_tile)
			this->draw_image(*inkstyle.m_tile, rect);
	}

	void UiRenderer::draw_image(const Image& image, const vec4& rect)
	{
		if(image.d_atlas)
		{
			vec4 image_rect = { rect_offset(rect) - vec2(image.d_coord), vec2(image.d_atlas->m_image.d_size) };
			m_vg.draw_texture(uint16_t(image.d_atlas->m_image.d_handle), rect, image_rect);
		}
		else
		{
			m_vg.draw_texture(uint16_t(image.d_handle), rect, rect);
		}
	}

	void UiRenderer::draw_image_stretch(const Image& image, const vec4& rect, const vec2& stretch)
	{
		if(image.d_atlas)
		{
			vec4 image_rect = { rect_offset(rect) - vec2(image.d_coord) * stretch, vec2(image.d_atlas->m_image.d_size) * stretch };
			m_vg.draw_texture(uint16_t(image.d_atlas->m_image.d_handle), rect, image_rect);
		}
		else
		{
			vec4 image_rect = { rect_offset(rect), vec2(image.d_size) * stretch };
			m_vg.draw_texture(uint16_t(image.d_handle), rect, image_rect);
		}
	}

	void UiRenderer::draw_skin_image(const Frame& frame, int section, vec4 rect)
	{
		ImageSkin& imageSkin = frame.d_inkstyle->m_image_skin;
		rect.x = rect.x - imageSkin.m_margin;
		rect.y = rect.y - imageSkin.m_margin;

		vec2 divided = rect_size(rect) / imageSkin.d_fill_size;
		vec2 ratio = { 1.f, 1.f };

		if(section == ImageSkin::Top || section == ImageSkin::Bottom || section == ImageSkin::Fill)
			ratio.x = divided.x;
		if(section == ImageSkin::Left || section == ImageSkin::Right || section == ImageSkin::Fill)
			ratio.y = divided.y;

		this->draw_image_stretch(imageSkin.d_images[section], rect, ratio);
	}

	inline TextPaint text_paint(InkStyle& inkstyle)
	{
		return { inkstyle.m_text_font.c_str(), inkstyle.m_text_colour, inkstyle.m_text_size, inkstyle.m_align, inkstyle.m_text_break, inkstyle.m_text_wrap };
	}

	void UiRenderer::draw_content(const Frame& frame, const vec4& rect, const vec4& padded_rect, const vec4& content_rect)
	{
		UNUSED(rect);

		if(frame.empty() || padded_rect.z <= 0.f || padded_rect.w <= 0.f)
			return;

		//this->clip(rect);

		if(frame.icon())
			this->draw_image(*frame.icon(), content_rect);

		if(frame.caption())
			m_vg.draw_text(rect_offset(padded_rect), frame.caption(), nullptr, text_paint(*frame.d_inkstyle));
	}

	void UiRenderer::draw_rect(const vec4& rect, const vec4& corners, const InkStyle& inkstyle)
	{
		m_vg.path_rect(rect, corners, inkstyle.m_border_width.x);

		if(!inkstyle.m_background_colour.null())
		{
			if(inkstyle.m_linear_gradient == Zero2)
			{
				m_vg.fill({ inkstyle.m_background_colour, inkstyle.m_border_colour, inkstyle.m_border_width.x });
			}
			else
			{
				Colour first = offset_colour(inkstyle.m_background_colour, inkstyle.m_linear_gradient.x);
				Colour second = offset_colour(inkstyle.m_background_colour, inkstyle.m_linear_gradient.y);
				if(inkstyle.m_linear_gradient_dim == DIM_X)
					m_vg.fill({ first, second }, { rect.x, rect.y }, { rect.x + rect_w(rect), rect.y });
				else
					m_vg.fill({ first, second }, { rect.x, rect.y }, { rect.x, rect.y + rect_h(rect) });
			}

		}
		if(inkstyle.m_border_width.x > 0.f)
			m_vg.stroke({ inkstyle.m_background_colour, inkstyle.m_border_colour, inkstyle.m_border_width.x });
	}

	void UiRenderer::log_FPS()
	{
		static size_t frames = 0;
		static double prevtime;

		double time = m_clock.read();
		if(time - prevtime >= 4.f)
		{
			printf("INFO: fps %f\n", (frames / (time - prevtime)));
			prevtime = time;
			frames = 0;
		}

		++frames;
	}
}
