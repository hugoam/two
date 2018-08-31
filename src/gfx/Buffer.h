//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <math/VecOps.h>
#include <gfx/Forward.h>

#include <bgfx/bgfx.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
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
        ElementType type : 3;
        uint8_t     size : 3; // 1 to 4 allowed
    };

    GpuBuffer() = default;

    GpuBuffer(Element element, size_t row_size, size_t row_count);
	~GpuBuffer();

    GpuBuffer(const GpuBuffer&) = delete;
    GpuBuffer& operator=(const GpuBuffer&) = delete;
    GpuBuffer(GpuBuffer&&) = default;
    GpuBuffer& operator=(GpuBuffer&&) = default;

	bgfx::TextureHandle m_texture;
	//utils::RangeSet<4> mDirtyRanges;
	uint32_t m_size = 0;
	uint16_t m_width;
	uint16_t m_height;
	uint16_t m_row_size;
	Element m_element;
	bgfx::TextureFormat::Enum m_format;
	
	std::vector<Range<float>> m_dirty_ranges;

    void invalidate() noexcept;
    void invalidate(size_t row, size_t count) noexcept;

    //bool dirty() const noexcept { return !mDirtyRanges.isEmpty(); }

    void commit(const bgfx::Memory* memory) noexcept;
};

}
