//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <cassert>
#include <gfx/Cpp20.h>
module two.gfx;
#else
#include <cassert>
#include <gfx/Buffer.h>
#endif

namespace two
{
	static size_t data_type_to_size(GpuBuffer::Element element) noexcept
	{
		using ET = GpuBuffer::ElementType;
		switch (element.type)
		{
			case ET::UINT8:  return element.size * sizeof(uint8_t);
			case ET::INT8:   return element.size * sizeof(int8_t);
			case ET::UINT16: return element.size * sizeof(uint16_t);
			case ET::INT16:  return element.size * sizeof(int16_t);
			case ET::UINT32: return element.size * sizeof(uint32_t);
			case ET::INT32:  return element.size * sizeof(int32_t);
			//case ET::HALF:   return element.size * sizeof(math::half);
			case ET::FLOAT:  return element.size * sizeof(float);
			default: return 0;
		}
	}

	static bgfx::TextureFormat::Enum data_type_to_texture_format(GpuBuffer::Element element) noexcept
	{
		using TF = bgfx::TextureFormat;
		static const TF::Enum formats[8][4] =
		{
			{ TF::R8U,   TF::RG8U,   TF::RGB8U,   TF::RGBA8U },
			{ TF::R8I,   TF::RG8I,   TF::RGB8I,   TF::RGBA8I },
			{ TF::R16U,  TF::RG16U,  TF::Unknown, TF::RGBA16U },
			{ TF::R16I,  TF::RG16I,  TF::Unknown, TF::RGBA16I },
			{ TF::R32U,  TF::RG32U,  TF::Unknown, TF::RGBA32U },
			{ TF::R32I,  TF::RG32I,  TF::Unknown, TF::RGBA32I },
			{ TF::R16F,  TF::RG16F,  TF::Unknown, TF::RGBA16F },
			{ TF::R32F,  TF::RG32F,  TF::Unknown, TF::RGBA32F },
		};

		size_t index = size_t(element.type);
		assert(index < 8 && element.size > 0 && element.size <= 4);
		return formats[index][element.size - 1];
	}

	GpuBuffer::GpuBuffer(Element element, size_t row_size, size_t row_count)
		: m_element(element)
		, m_size(uint32_t(data_type_to_size(element) * row_size * row_count))
		, m_width(uint16_t(row_size))
		, m_height(uint16_t(row_count))
		, m_row_size(uint16_t(data_type_to_size(element) * row_size))
	{
		m_format = data_type_to_texture_format(element);
		m_texture = { uvec2(m_width, m_height), false, TextureFormat(m_format) };
		//m_buffer = bgfx::createDynamicVertexBuffer(m_clusters.m_memory, decl);
	}

	GpuBuffer::~GpuBuffer()
	{
		bgfx::destroy(m_texture);
	}

	void GpuBuffer::commit(const bgfx::Memory* memory) noexcept
	{
		bgfx::updateTexture2D(m_texture, 0, 0, 0, 0, m_width, m_height, memory);

		/*const uintptr_t size = uintptr_t(end) - uintptr_t(begin);
		assert(size <= m_row_size * m_height);

		for(auto const& range : mDirtyRanges)
		{
			bgfx::updateTexture2D(m_texture, 1, 0, 0, range.start, m_width, range.size, memory);
		}*/
	}

	void GpuBuffer::invalidate() noexcept
	{
		//invalidate(0, m_height);
	}

	void GpuBuffer::invalidate(size_t row, size_t count) noexcept
	{
		UNUSED(row); UNUSED(count);
		//mDirtyRanges.set(uint32_t(row), uint32_t(count));
	}

}
