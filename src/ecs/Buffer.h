#pragma once

#define TWO_ECS_TYPED

#ifndef TWO_MODULES
#include <stl/swap.h>
#include <stl/vector.h>
#ifdef TWO_ECS_TYPED
#include <type/Ref.h>
#endif
#endif
#include <ecs/Forward.h>

namespace two
{
	class Buffer
	{
	public:
		virtual ~Buffer() {}

#ifdef TWO_ECS_TYPED
		Type* m_type = nullptr;
#endif
		virtual void clear() = 0;
		virtual void create() = 0;
		virtual void create(uint32_t count) = 0;
		virtual void remove(uint32_t index) = 0;
#ifdef TWO_ECS_TYPED
		virtual Ref get(uint32_t index) = 0;
#endif
	};

	template <class T>
	class TBuffer : public Buffer
	{
	public:
		TBuffer() {}
#ifdef TWO_ECS_TYPED
		TBuffer(Type& type, int capacity = 1 << 10)
#else
		TBuffer(int capacity = 1 << 10)
#endif
		{
#ifdef TWO_ECS_TYPED
			m_type = &type;
#endif
			m_data.reserve(capacity);
		}

		TBuffer(const TBuffer& other) = delete;
		TBuffer& operator=(const TBuffer& other) = delete;

		virtual void clear() override {	m_data.clear(); }
		virtual void create() override { m_data.emplace_back(); }
		virtual void create(uint32_t count) override { m_data.resize(m_data.size() + count); }
		virtual void remove(uint32_t index) override { swap_pop(m_data, index); }

#ifdef TWO_ECS_TYPED
		virtual Ref get(uint32_t index) override { return Ref(&m_data[index], *m_type); }
#endif

		vector<T> m_data;
	};
}