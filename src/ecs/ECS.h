
#pragma once

#include <cstdint>

namespace mud
{
	using EntFlags = uint64_t;

	struct EntityData
	{
		EntFlags m_flags = 0;
		uint16_t m_stream = 0;

		EntityData() {}
		EntityData(EntFlags flags, uint16_t stream) : m_flags(flags), m_stream(stream) {}
		
		bool operator<(EntityData& other) const { return m_flags < other.m_flags; }
	};
}