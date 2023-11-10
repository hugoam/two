//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <bgfx/bgfx.h>
#include <stl/vector.h>
#include <math/Vec.hpp>
#endif
#include <gfx/Forward.h>
#include <gfx/Texture.h>

namespace two
{

	class GpuBuffer
	{
	public:
		enum class ElementType : uint8_t
		{
			UINT8,
			INT8,
			UINT16,
			INT16,
			UINT32,
			INT32,
			HALF,
			FLOAT
		};

		struct Element
		{
			Element(ElementType type, uint8_t size) : type(type), size(size) {}
			ElementType type;
			uint8_t     size;
		};

		GpuBuffer() = default;

		GpuBuffer(Element element, size_t row_size, size_t row_count);
		~GpuBuffer();

		GpuBuffer(const GpuBuffer&) = delete;
		GpuBuffer& operator=(const GpuBuffer&) = delete;
		GpuBuffer(GpuBuffer&&) = default;
		GpuBuffer& operator=(GpuBuffer&&) = default;

		Texture m_texture;
		//utils::RangeSet<4> mDirtyRanges;
		Element m_element;
		uint32_t m_size = 0;
		uint16_t m_width = 0;
		uint16_t m_height = 0;
		uint16_t m_row_size = 0;
		bgfx::TextureFormat::Enum m_format;
	
		//vector<Range<float>> m_dirty_ranges;

		void invalidate() noexcept;
		void invalidate(size_t row, size_t count) noexcept;

		//bool dirty() const noexcept { return !mDirtyRanges.isEmpty(); }

		void commit(const bgfx::Memory* memory) noexcept;
	};

}
