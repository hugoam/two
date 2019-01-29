#pragma once

#include <stl/vector.h>
#include <stl/unordered_map.h>
#include <ui-vg/Api.h>

#include <vg/vg.h>

using namespace mud;
namespace tinystl
{
	export_ extern template class vector<vg::GlyphPosition>;
	export_ extern template class unordered_map<string, vg::FontHandle>;
}
