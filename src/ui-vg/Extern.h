#pragma once

#include <stl/vector.h>
#include <stl/unordered_map.h>
#include <ui-vg/Api.h>

#include <vg/vg.h>

namespace tinystl
{
	using namespace mud;
	export_ extern template class vector<vg::GlyphPosition>;
	export_ extern template class unordered_map<string, vg::FontHandle>;
}
