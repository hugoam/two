//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Frame/Dim.h>

namespace two
{
	export_ struct refl_ TWO_UI_EXPORT ImageSkin
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
		constr_ ImageSkin(Image& image, int left, int top, int right, int bottom, int margin = 0, Axis stretch = Axis::None);
		ImageSkin(Image& image, const ImageSkin& ref);
		ImageSkin();

		bool null() const { return d_image == nullptr; }

		void stretch_coords(vec2 offset, vec2 size, span<vec4> coords) const;

		attr_ Image* d_image = nullptr;

		attr_ int d_left = 0;
		attr_ int d_top = 0;
		attr_ int d_right = 0;
		attr_ int d_bottom = 0;
		attr_ int m_margin = 0;
		attr_ Axis d_stretch = Axis::None;

		vec2 d_size;
		vec2 d_solid_size;
		vec2 d_fill_size;
		vec2 m_min_size;

		Image d_images[9];
	};
}
