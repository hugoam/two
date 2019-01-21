#pragma once

#include <stl/unordered_map.h>
#include <stl/vector.h>
#include <ecs/ECS.h>

namespace mud
{
	template <bool Dense = false>
	class SparseIndices
	{
	public:
		SparseIndices(size_t capacity = 1 << 10) : m_indices(capacity, UINT32_MAX) {}

		void clear() { m_indices.resize(m_indices.size(), UINT32_MAX); }

		void erase(uint32_t handle) { m_indices[handle] = UINT32_MAX; }

		void ensure(size_t capacity) { m_indices.resize(capacity, UINT32_MAX); }

		uint32_t& operator[](uint32_t at) { return m_indices[at]; }

	private:
		vector<uint32_t> m_indices;
	};

	template <>
	class SparseIndices<true>
	{
	public:
		SparseIndices(size_t capacity = 1 << 10) /*: m_indices(4)*/ { UNUSED(capacity); }

		void clear() { m_indices.clear(); }

		void erase(uint32_t handle) { m_indices.erase(handle); }

		void ensure(size_t capacity) { UNUSED(capacity); }

		uint32_t& operator[](uint32_t at) { return m_indices[at]; }

	private:
		unordered_map<uint32_t, uint32_t> m_indices;
	};
}