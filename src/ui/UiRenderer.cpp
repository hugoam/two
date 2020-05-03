//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.ui;
#else
#include <stl/string.h>
#include <stl/map.h>
#include <infra/Log.h>
#include <math/Vec.hpp>
#include <ui/UiRenderer.h>
#include <ui/Frame/Layer.h>
#include <ui/Frame/Solver.h>
#include <ui/Widget.h>
#include <ui/Sheet.h>
#include <ui/Edit/TypeIn.h>
#include <ui/Style/Skin.h>
#include <math/ImageAtlas.h>
#endif

#include <cstdio>

namespace two
{
	inline Colour offset_colour(const Colour& colour, float delta)
	{
		float offset = delta / 255.0f;
		return Colour(clamp(colour.r + offset, 0.f, 1.f),
					  clamp(colour.g + offset, 0.f, 1.f),
					  clamp(colour.b + offset, 0.f, 1.f),
					  colour.a);
	}

	struct Vg::Impl
	{
		string m_resource_path;
		map<string, string> m_font_sources;
	};

	Vg::Vg(cstring resource_path)
		: m_impl(make_unique<Impl>())
	{
		m_impl->m_resource_path = resource_path;

		Frame::s_vg = this;
		Text::s_vg = this;

		m_impl->m_font_sources["dejavu"] = string(resource_path) + "/interface/fonts/DejaVuSans.ttf";
		m_impl->m_font_sources["consolas"] = string(resource_path) + "/interface/fonts/Consolas.ttf";
		m_impl->m_font_sources["proggy"] = string(resource_path) + "/interface/fonts/ProggyClean.ttf";
		//m_impl->m_font_sources["consolas-bold"] = string(resource_path) + "/interface/fonts/Consolas-Bold.ttf";
		//m_impl->m_font_sources["inconsolata"] = string(resource_path) + "/interface/fonts/Inconsolata-Regular.ttf";
		//m_impl->m_font_sources["inconsolata-bold"] = string(resource_path) + "/interface/fonts/Inconsolata-Bold.ttf";
		//m_impl->m_font_sources["veramono"] = string(resource_path) + "/interface/fonts/VeraMono.ttf";
		//m_impl->m_font_sources["veramono-bold"] = string(resource_path) + "/interface/fonts/VeraMono-Bold.ttf";
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
		row = text_row(text, text, text + len, { rect.x, rect.y, this->text_size(text, len, Axis::X, paint), line_height(paint) });
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

		row = text_row(text, first, iter, { rect.x, rect.y, this->text_size(first, iter - first, Axis::X, paint), line_height(paint) });
		this->break_glyphs(rect, paint, row);

		// @kludge because text_size doesn't report the correct size when there is a space at the end : investigate (vg-renderer, nanovg)
		if(!row.m_glyphs.empty())
			row.m_rect = { rect.x, rect.y, row.m_glyphs.back().m_rect.x + row.m_glyphs.back().m_rect.width, line_height(paint) };
	}

	void Vg::break_text(cstring text, size_t len, const vec2& space, const TextPaint& paint, vector<TextRow>& textRows)
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

	void UiRenderer::render(Layer& target, uint16_t view, float pixel_ratio, const Colour& colour)
	{
		m_debug_batch = 0;
		static size_t prevBatch = 0;

		m_vg.begin_frame(view, vec4(vec2(0.f), target.m_frame.m_size), pixel_ratio, colour);

#ifdef TWO_UI_DRAW_CACHE
		target.visit([&](Layer& layer) {
			if(layer.redraw() || layer.forceRedraw())
				this->render_layer(layer);
		});

		target.visit([&](Layer& layer) {
			m_vg.draw_layer(layer, vec2(0.f), 1.f);
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
			//printf("[debug] Render Frame : %i frames redrawn\n", m_debug_batch);
		}

		m_vg.end_frame(view);
	}

	void UiRenderer::render_layer(Layer& layer)
	{
		if(layer.master())
			m_vg.begin_target();

#ifdef TWO_UI_DRAW_CACHE
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

#ifdef TWO_UI_DRAW_CACHE
		m_vg.end_cached();
#endif

		if(layer.master())
			m_vg.end_target();
	}

	void UiRenderer::begin_frame(Frame& frame)
	{
		m_vg.begin_update(floor(frame.m_position), frame.m_scale);

		if(frame.d_layout->m_clipping == Clip::Clip)
		{
			m_vg.clip(frame.content_rect());
		}

		if(frame.d_layout->m_clipping == Clip::Unclip)
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

		//m_vg.debug_rect(rect, Colour::Red);

		if(frame.d_inkstyle->m_empty)
			return;

		if(frame.d_widget.m_custom_draw)
			return frame.d_widget.m_custom_draw(frame, rect, m_vg);

		if(frame.d_inkstyle->m_custom_draw)
			return frame.d_inkstyle->m_custom_draw(frame, rect, m_vg);
	
		two::draw_frame(m_vg, frame, rect);
	}

	void draw_frame(Vg& vg, const Frame& frame, const vec4& rect)
	{
		const vec2 padded_pos = floor(frame.d_inkstyle->m_padding.pos);
		const vec2 padded_size = floor(frame.m_size - rect_sum(frame.d_inkstyle->m_padding));
		const vec4 padded_rect = { padded_pos, padded_size };

		vec2 content = frame.m_content;
		if(frame.d_inkstyle->m_stretch.x)
			content.x = padded_size.x;
		if(frame.d_inkstyle->m_stretch.y)
			content.y = padded_size.y;

		const vec2 content_pos = { content_position(frame, content, padded_pos, padded_size, Axis::X), content_position(frame, content, padded_pos, padded_size, Axis::Y) };
		const vec4 content_rect = { content_pos, content };

		draw_background(vg, frame, rect, padded_rect, content_rect);
		draw_content(vg, frame, rect, padded_rect, content_rect);

		//vg.debug_rect(rect, Colour::Red);
		//vg.debug_rect(padded_rect, Colour::Green);
		//vg.debug_rect(content_rect, Colour::Blue);
	}

	float content_position(const Frame& frame, const vec2& content, const vec2& padded_pos, const vec2& padded_size, Axis dim)
	{
		if(frame.d_inkstyle->m_align[dim] == Align::Center)
			return padded_pos[dim] + padded_size[dim] / 2.f - content[dim] / 2.f;
		else if(frame.d_inkstyle->m_align[dim] == Align::Right)
			return padded_pos[dim] + padded_size[dim] - content[dim];
		else
			return padded_pos[dim];
	}

	vec4 select_corners(const Frame& frame)
	{
		Frame& parent = *frame.d_parent;

		const vec4& corners = parent.d_inkstyle->m_corner_radius;
		if(parent.first(frame))
			return parent.m_solver->d_length == Axis::X ? vec4(corners[0], 0.f, 0.f, corners[3]) : vec4(corners[0], corners[1], 0.f, 0.f);
		else if(parent.last(frame))
			return parent.m_solver->d_length == Axis::X ? vec4(0.f, corners[1], corners[2], 0.f) : vec4(0.f, 0.f, corners[2], corners[3]);
		else
			return vec4();
	}

	void draw_background(Vg& vg, const Frame& frame, const vec4& rect, const vec4& padded_rect, const vec4& content_rect)
	{
		//m_debug_batch++;

		InkStyle& inkstyle = *frame.d_inkstyle;

		// Shadow
		if(!inkstyle.m_shadow.d_null)
		{
			vg.draw_shadow(rect, inkstyle.m_corner_radius, inkstyle.m_shadow);
		}

		// Rect
		if(inkstyle.m_border_width.x || !inkstyle.m_background_colour.null())
		{
			vec4 corners = inkstyle.m_weak_corners ? select_corners(frame) : inkstyle.m_corner_radius;
			draw_rect(vg, rect, corners, inkstyle);
		}

		// ImageSkin
		ImageSkin& image_skin = inkstyle.m_image_skin;
		if(!image_skin.null())
		{
			const float margin = image_skin.m_margin * 2.f;
			vec4 skin_rect = { rect.pos, rect.size + margin };

			if(image_skin.d_stretch == Axis::X)
				skin_rect = { rect.x, content_rect.y + margin, rect.z + margin, image_skin.d_size.y };
			else if(image_skin.d_stretch == Axis::Y)
				skin_rect = { content_rect.x + image_skin.m_margin, rect.y, image_skin.d_size.x, rect.w + margin };

			vec4 sections[ImageSkin::Count];
			image_skin.stretch_coords(skin_rect.pos, skin_rect.size, { sections, ImageSkin::Count });

			for(int s = 0; s < ImageSkin::Count; ++s)
				draw_skin_image(vg, frame, s, sections[s]);
		}

		// Image
		if(inkstyle.m_overlay)
			draw_image(vg, *inkstyle.m_overlay, padded_rect);
		if(inkstyle.m_tile)
			draw_image(vg, *inkstyle.m_tile, rect);
	}

	void draw_image(Vg& vg, const Image& image, const vec4& rect)
	{
		if(image.d_atlas)
		{
			vec4 image_rect = { rect.pos - vec2(image.d_coord), vec2(image.d_atlas->m_image.d_size) };
			vg.draw_texture(uint16_t(image.d_atlas->m_image.d_handle), rect, image_rect);
		}
		else
		{
			vg.draw_texture(uint16_t(image.d_handle), rect, rect);
		}
	}

	void draw_image_stretch(Vg& vg, const Image& image, const vec4& rect, const vec2& stretch)
	{
		if(image.d_atlas)
		{
			const vec4 image_rect = { rect.pos - vec2(image.d_coord) * stretch, vec2(image.d_atlas->m_image.d_size) * stretch };
			vg.draw_texture(uint16_t(image.d_atlas->m_image.d_handle), rect, image_rect);
		}
		else
		{
			const vec4 image_rect = { rect.pos, vec2(image.d_size) * stretch };
			vg.draw_texture(uint16_t(image.d_handle), rect, image_rect);
		}
	}

	void draw_skin_image(Vg& vg, const Frame& frame, int section, vec4 rect)
	{
		ImageSkin& imageSkin = frame.d_inkstyle->m_image_skin;
		rect.x = rect.x - imageSkin.m_margin;
		rect.y = rect.y - imageSkin.m_margin;

		const vec2 divided = rect.size / imageSkin.d_fill_size;
		vec2 ratio = { 1.f, 1.f };

		if(section == ImageSkin::Top || section == ImageSkin::Bottom || section == ImageSkin::Fill)
			ratio.x = divided.x;
		if(section == ImageSkin::Left || section == ImageSkin::Right || section == ImageSkin::Fill)
			ratio.y = divided.y;

		draw_image_stretch(vg, imageSkin.d_images[section], rect, ratio);
	}

	void draw_content(Vg& vg, const Frame& frame, const vec4& rect, const vec4& padded_rect, const vec4& content_rect)
	{
		UNUSED(rect);

		if(frame.empty() || padded_rect.z <= 0.f || padded_rect.w <= 0.f)
			return;

		//this->clip(rect);

		if(frame.icon())
			draw_image(vg, *frame.icon(), content_rect);

		if(frame.caption())
			vg.draw_text(padded_rect.pos, frame.caption(), nullptr, text_paint(*frame.d_inkstyle));

		if(frame.m_text)
		{
			const vec2 padding = floor(frame.d_inkstyle->m_padding.pos);
			draw_text(vg, padding, *frame.m_text);
		}
	}

	void draw_rect(Vg& vg, const vec4& rect, const vec4& corners, const InkStyle& inkstyle)
	{
		vg.path_rect(rect, corners, inkstyle.m_border_width.x);

		if(!inkstyle.m_background_colour.null())
		{
			if(inkstyle.m_linear_gradient == vec2(0.f))
			{
				vg.fill({ inkstyle.m_background_colour, inkstyle.m_border_colour, inkstyle.m_border_width.x });
			}
			else
			{
				Colour first = offset_colour(inkstyle.m_background_colour, inkstyle.m_linear_gradient.x);
				Colour second = offset_colour(inkstyle.m_background_colour, inkstyle.m_linear_gradient.y);
				if(inkstyle.m_linear_gradient_dim == Axis::X)
					vg.fill({ first, second }, { rect.x, rect.y }, { rect.x + rect.width, rect.y });
				else
					vg.fill({ first, second }, { rect.x, rect.y }, { rect.x, rect.y + rect.height });
			}

		}
		if(inkstyle.m_border_width.x > 0.f)
			vg.stroke({ inkstyle.m_background_colour, inkstyle.m_border_colour, inkstyle.m_border_width.x });
	}

	void UiRenderer::log_FPS()
	{
		static size_t frames = 0;
		static double prevtime;

		double time = m_clock.read();
		if(time - prevtime >= 4.f)
		{
			info("frame %.2f", ((time - prevtime) / frames) * 1000.f);
			info("fps %f", (frames / (time - prevtime)));
			prevtime = time;
			frames = 0;
		}

		++frames;
	}
}
