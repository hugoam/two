//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Array.h>
#include <ui/Generated/Forward.h>
#include <ui/Frame/Dim.h>
#include <ui/Image.h>

namespace mud
{
	struct _refl_ MUD_UI_EXPORT ImageSkin
	{
	public:
		enum Section
		{
			TopLeft = 0, // Corners
			TopRight = 1,
			BottomRight = 2,
			BottomLeft = 3,
			Top = 4, // Borders
			Right = 5,
			Bottom = 6,
			Left = 7,
			Fill = 8, // Fill
			Count
		};

	public:
		_constr_ ImageSkin(Image& image, int left, int top, int right, int bottom, int margin = 0, Dim stretch = DIM_NONE);
		ImageSkin(Image& image, const ImageSkin& ref);
		ImageSkin();

		bool null() const { return d_image == nullptr; }

		void stretch_coords(vec2 offset, vec2 size, array<vec4> coords) const;

		_attr_ _mut_ Image* d_image = nullptr;

		_attr_ _mut_ int d_left = 0;
		_attr_ _mut_ int d_top = 0;
		_attr_ _mut_ int d_right = 0;
		_attr_ _mut_ int d_bottom = 0;
		_attr_ _mut_ int m_margin = 0;
		_attr_ _mut_ Dim d_stretch = DIM_NONE;

		vec2 d_size;
		vec2 d_solid_size;
		vec2 d_fill_size;
		vec2 m_min_size;

		Image d_images[9];
	};
}
