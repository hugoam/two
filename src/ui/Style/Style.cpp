//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.ui;
#else
#include <infra/StringConvert.h>
#include <infra/Reverse.h>
#include <ui/Style/Style.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Skin.h>
#include <ui/Widget.h>
#include <ui/Input.h>
#include <ui/UiWindow.h>
#endif

namespace mud
{
	ImageSkin::ImageSkin(Image& image, int left, int top, int right, int bottom, int margin, Dim stretch)
		: d_image(&image)
		, d_left(left), d_top(top), d_right(right), d_bottom(bottom)
		, m_margin(margin)
		, d_stretch(stretch)
		, d_size(image.d_size)
		, d_solid_size(image.d_size - uvec2(uint(margin + margin)))
		, d_fill_size(uvec2(image.d_size.x - d_left - d_right, image.d_size.y - d_top - d_bottom))
		, d_images()
	{
		for(Image& subimage : d_images)
			subimage = *d_image;

		m_min_size.x = d_stretch == DIM_X ? float(d_solid_size.x) : 0.f;
		m_min_size.y = d_stretch == DIM_Y ? float(d_solid_size.y) : 0.f;

		vec4 coords[Count] = {};
		this->stretch_coords(Zero2, vec2(image.d_size), array<vec4>{ coords, Count });
		for(size_t s = 0; s < Count; ++s)
		{
			this->d_images[s].d_coord = this->d_image->d_coord + uvec2(rect_offset(coords[s]));
			this->d_images[s].d_size = uvec2(rect_size(coords[s]));
		}
	}

	ImageSkin::ImageSkin(Image& image, const ImageSkin& ref)
		: ImageSkin(image, ref.d_left, ref.d_top, ref.d_right, ref.d_bottom, ref.m_margin, ref.d_stretch)
	{}

	ImageSkin::ImageSkin()
		: d_image(nullptr)
	{}

	void ImageSkin::stretch_coords(vec2 offset, vec2 size, array<vec4> coords) const
	{
		vec2 fill = { size.x - d_left - d_right, size.y - d_top - d_bottom };

		coords[TopLeft] = { offset.x, offset.y, float(d_left), float(d_top) };
		coords[TopRight] = { offset.x + fill.x + d_left, offset.y, float(d_right), float(d_top) };
		coords[BottomRight] = { offset.x + fill.x + d_left, offset.y + fill.y + d_top, float(d_right), float(d_bottom) };
		coords[BottomLeft] = { offset.x, offset.y + fill.y + d_top, float(d_left), float(d_bottom) };

		coords[Top] = { offset.x + d_left, offset.y, fill.x, float(d_top) };
		coords[Right] = { offset.x + fill.x + d_left, offset.y + d_top, float(d_right), fill.y };
		coords[Bottom] = { offset.x + d_left, offset.y + fill.y + d_top, fill.x, float(d_bottom) };
		coords[Left] = { offset.x, offset.y + d_top, float(d_left), fill.y };

		coords[Fill] = { offset.x + d_left, offset.y + d_top, fill.x, fill.y };
	}

	Styles& styles() { static Styles styles; return styles; }

	struct Style::Impl
	{
		string m_name;
		Layout m_layout;
		InkStyle m_skin;
		vector<InkStyle> m_skins;
	};

	Style::Style(cstring name, Style* base, LayoutDef layout, InkStyleDef skin, StyleDef style)
		: m_base(base)
		, m_impl(make_unique<Impl>())
	{
		if(UiWindow::s_styles[name] == nullptr)
			UiWindow::s_styles[name] = this;

		m_impl->m_name = name;
		m_impl->m_layout = { name };
		m_impl->m_skin = { name };
		m_impl->m_skins = {};

		if(m_base)
		{
			m_impl->m_layout = m_base->m_impl->m_layout;
			m_impl->m_layout.m_name = name;
		}

		if(layout)
			layout(m_impl->m_layout);
		if(skin)
			skin(m_impl->m_skin);
		if(style)
			style(*this);
	}

	Style::~Style()
	{}

	Style::Style(const Style& other)
		: m_base(other.m_base)
		, m_impl(make_unique<Impl>())
	{
		*this = other;
	}

	Style& Style::operator=(const Style& other)
	{
		m_impl->m_layout = other.m_impl->m_layout;
		m_impl->m_skin = other.m_impl->m_skin;
		m_impl->m_skins = other.m_impl->m_skins;
		return *this;
	}

	cstring Style::name() { return m_impl->m_name.c_str(); }
	Layout& Style::layout() { return m_impl->m_layout; }
	InkStyle& Style::skin() { return m_impl->m_skin; }

	void Style::prepare()
	{
		m_impl->m_skin.prepare();
		for(InkStyle& skin : m_impl->m_skins)
			skin.prepare();
	}

	InkStyle& Style::state_skin(WidgetState state)
	{
		// turn off non-skinnable state flags
		state = static_cast<WidgetState>(state & ~(CREATED | ACTIVATED | CLOSED));
		for(InkStyle& skin : reverse_adapt(m_impl->m_skins))
			if(state == skin.m_state) // exact match
				return skin;
		for(InkStyle& skin : reverse_adapt(m_impl->m_skins))
			if(state & skin.m_state) // partial match
				return skin;
		return m_impl->m_skin;
	}

	InkStyle& Style::decline_skin(WidgetState state)
	{
		for(InkStyle& skin : m_impl->m_skins)
			if(state == skin.m_state)
				return skin;

		m_impl->m_skins.emplace_back(m_impl->m_skin);
		m_impl->m_skins.back().m_name = m_impl->m_name + ":" + to_lower(flags_to_string<WidgetState, 9>(state));
		m_impl->m_skins.back().m_state = state;
		return m_impl->m_skins.back();
	}
}
