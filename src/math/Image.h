//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/string.h>
#include <math/Vec.h>
#include <math/Forward.h>

namespace two
{
	export_ using cstring = const char*;

	export_ struct refl_ TWO_MATH_EXPORT Image
	{
	public:
		Image(const string& name = "", const string& path = "", const uvec2& size = {})
			: d_name(name), d_path(path), d_size(size)
		{}

		attr_ string d_name;
		attr_ string d_path;
		uvec2 d_size;
		uvec2 d_coord = uvec2(0U);

		int d_handle = -1;
		ImageAtlas* d_atlas = nullptr;

		bool d_tile = false;
		bool d_stretch = false;
		bool d_filtering = true;
	};

}
