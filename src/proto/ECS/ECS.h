
#pragma once

#include <cstdint>

namespace toy
{
	using EntIdx = int32_t;
	using EntFlags = uint64_t;
	using EntTags = uint64_t;

	struct EntityData
	{
		EntFlags m_flags = UINT64_MAX;
		//EntTags m_tags = 0;

		EntityData() {}
		EntityData(EntFlags flags) : m_flags(flags) {}
		//EntityData(EntFlags flags, EntTags tags) : m_flags(flags), m_tags(tags) {}

		bool operator<(EntityData& other) const { return m_flags < other.m_flags; }
	};

	struct EntitySlice
	{
		EntFlags m_prototype;
		size_t m_begin;
		size_t m_end;
	};
}