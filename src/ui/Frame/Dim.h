//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/stddef.h>
#include <stl/table.h>
#include <math/Vec.h>
#include <ui/Forward.h>

namespace mud
{
	//export_ enum class refl_ Dim : unsigned int
	//{
	//	X = 0,
	//	Y = 1,
	//	None = 2,
	//	Count
	//};

	inline Axis flip(Axis dim) { return dim == Axis::X ? Axis::Y : Axis::X; }

	export_ enum class refl_ FlowAxis : unsigned int
	{
		Reading = 0,
		Paragraph = 1,
		Same = 2,
		Flip = 3,
		None = 4,
	};

	export_ enum class refl_ Pivot : unsigned int
	{
		Forward = 0,
		Reverse = 1
	};

	export_ enum class refl_ Align : unsigned int
	{
		Left = 0,
		Center = 1,
		Right = 2,
		OutLeft = 3,
		OutRight = 4,
		Count
	};

	extern table<Align, float> c_align_extent;
	extern table<Align, float> c_align_space;

	export_ enum class refl_ Solver : unsigned int
	{
		Frame = 0,
		Row = 1,
		Grid = 2,
		Table = 3,
	};

	export_ enum class refl_ AutoLayout : unsigned int
	{
		None = 0,
		Size = 1,
		Layout = 2
	};

	export_ enum class refl_ LayoutFlow : unsigned int
	{
		Flow = 0,			// AutoLayout::Layout
		Overlay = 1,		// AutoLayout::Size
		Align = 2,			// AutoLayout::Position
		Free = 3			// AutoLayout::None
	};

	export_ enum class refl_ Sizing : unsigned int
	{
		Fixed,
		Shrink,
		Wrap,
		Expand
	};

	export_ enum class refl_ Preset : unsigned int
	{
		Sheet,   // Paragraph   direction, Sizing::Wrap   length, Sizing::Wrap   depth
		Flex,	 // Same		direction, Sizing::Wrap   length, Sizing::Wrap   depth
		Item,    // Reading     direction, Sizing::Shrink length, Sizing::Shrink depth
		Unit,    // Paragraph   direction, Sizing::Shrink length, Sizing::Shrink depth
		Block,   // Paragraph   direction, Sizing::Fixed  length, Sizing::Fixed  depth
		Line,	 // Reading     direction, Sizing::Wrap   length, Sizing::Shrink depth
		Stack,   // Paragraph   direction, Sizing::Shrink length, Sizing::Wrap   depth 
		Div,	 // Flip        direction, Sizing::Wrap   length, Sizing::Shrink depth
		Spacer,  // Same        direction, Sizing::Wrap   length, Sizing::Shrink depth
		Board,   // Reading     direction, Sizing::Expand length, Sizing::Expand depth
		Layout   // Paragraph   direction, Sizing::Expand length, Sizing::Expand depth
	};

	export_ struct refl_ MUD_UI_EXPORT Space
	{
		attr_ FlowAxis direction;
		attr_ Sizing sizingLength;
		attr_ Sizing sizingDepth;

		Space(FlowAxis dir, Sizing length, Sizing depth) : direction(dir), sizingLength(length), sizingDepth(depth) {}
		Space(Preset preset = Preset::Flex) { *this = Space::preset(preset); }

		bool operator==(const Space& other) const { return direction == other.direction && sizingLength == other.sizingLength && sizingDepth == other.sizingDepth; }

		static Space preset(Preset preset);
	};

	extern Space SpacePresets[11];

	export_ enum class refl_ Clip : unsigned int
	{
		None = 0,
		Clip = 1,
		Unclip = 2
	};

	export_ enum class refl_ Opacity : unsigned int
	{
		Opaque = 0,
		Clear = 1,
		Hollow = 2
	};

	export_ extern template struct refl_ array_ struct_ v2<bool>;
	export_ extern template struct refl_ array_ struct_ v2<size_t>;
	export_ extern template struct refl_ array_ struct_ v2<AutoLayout>;
	export_ extern template struct refl_ array_ struct_ v2<Sizing>;
	export_ extern template struct refl_ array_ struct_ v2<Align>;
	export_ extern template struct refl_ array_ struct_ v2<Pivot>;
}
