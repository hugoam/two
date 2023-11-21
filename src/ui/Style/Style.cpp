//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <cstdio>
#include <infra/Cpp20.h>
module two.ui;

namespace two
{
	template <> inline void to_string(const two::WidgetState& val, string& str)
	{
		if(val == NOSTATE) str = "NOSTATE";
		else if(val == CREATED) str = "CREATED";
		else if(val == HOVERED) str = "HOVERED";
		else if(val == PRESSED) str = "PRESSED";
		else if(val == ACTIVATED) str = "ACTIVATED";
		else if(val == ACTIVE) str = "ACTIVE";
		else if(val == SELECTED) str = "SELECTED";
		else if(val == DISABLED) str = "DISABLED";
		else if(val == DRAGGED) str = "DRAGGED";
		else if(val == FOCUSED) str = "FOCUSED";
		else if(val == CLOSED) str = "CLOSED";
	};

	ImageSkin::ImageSkin(Image& image, int left, int top, int right, int bottom, int margin, Axis stretch)
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

		m_min_size.x = d_stretch == Axis::X ? float(d_solid_size.x) : 0.f;
		m_min_size.y = d_stretch == Axis::Y ? float(d_solid_size.y) : 0.f;

		vec4 coords[Count] = {};
		this->stretch_coords(vec2(0.f), vec2(image.d_size), span<vec4>{ coords, Count });
		for(size_t s = 0; s < Count; ++s)
		{
			this->d_images[s].d_coord = this->d_image->d_coord + uvec2(coords[s].pos);
			this->d_images[s].d_size = uvec2(coords[s].size);
		}
	}

	ImageSkin::ImageSkin(Image& image, const ImageSkin& ref)
		: ImageSkin(image, ref.d_left, ref.d_top, ref.d_right, ref.d_bottom, ref.m_margin, ref.d_stretch)
	{}

	ImageSkin::ImageSkin()
		: d_image(nullptr)
	{}

	void ImageSkin::stretch_coords(vec2 offset, vec2 size, span<vec4> coords) const
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

	void register_styles(span<Style*> styles)
	{
		for(Style* style : styles)
			g_styles[style->m_name] = style;
	}

	Style::Style()
		: Style("Unnamed", nullptr, {})
	{}

	Style::Style(const string& name, Style* base, LayoutDef layout, InkStyleDef skin, StyleDef style)
		: m_base(base)
		, m_name(name)
		, m_layout(name)
		, m_skin(name)
	{
		if(m_base)
		{
			m_layout = m_base->m_layout;
			m_layout.m_name = name;
		}

		if(layout)
			layout(m_layout);
		if(skin)
			skin(m_skin);
		if(style)
			style(*this);
	}

	Style::~Style()
	{}

	void Style::prepare()
	{
		m_skin.prepare();
		for(Subskin& subskin : m_skins)
		{
			subskin.skin.prepare();
			subskin.skin.m_name = m_name + ":" + to_lower(flags_to_string<WidgetState, 9>(subskin.state));
		}
	}

	InkStyle& Style::state_skin(WidgetState state)
	{
		// turn off non-skinnable state flags
		state = static_cast<WidgetState>(state & ~(CREATED | ACTIVATED | CLOSED));
		for(Subskin& subskin : reverse_adapt(m_skins))
			if(state == subskin.state) // exact match
				return subskin.skin;
		for(Subskin& subskin : reverse_adapt(m_skins))
			if(state & subskin.state) // partial match
				return subskin.skin;
		return m_skin;
	}

	InkStyle& Style::decline_skin(WidgetState state, bool inherit)
	{
		UNUSED(inherit);
		for(Subskin& subskin : m_skins)
			if(state == subskin.state)
			{
				return subskin.skin;
			}

		Subskin& subskin = push(m_skins);
		subskin.state = state;
		subskin.skin = m_skin;
		subskin.skin.m_name = m_name + ":" + to_lower(flags_to_string<WidgetState, 9>(state));
		return subskin.skin;
	}
}
