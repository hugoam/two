#pragma once

#define MUD_ECS_TYPED

#include <stl/swap.h>
#include <stl/vector.h>
#ifdef MUD_ECS_TYPED
#include <type/Ref.h>
#endif
#include <ecs/Forward.h>

namespace mud
{
	class Buffer
	{
	public:
		virtual ~Buffer() {}

#ifdef MUD_ECS_TYPED
		Type* m_type = nullptr;
#endif
		virtual void clear() = 0;
		virtual void add() = 0;
		virtual void remove(uint32_t index) = 0;
#ifdef MUD_ECS_TYPED
		virtual Ref get(uint32_t index) = 0;
#endif
	};

	template <class T>
	class TBuffer : public Buffer
	{
	public:
		TBuffer() {}
#ifdef MUD_ECS_TYPED
		TBuffer(Type& type, int capacity = 1 << 10)
#else
		TBuffer(int capacity = 1 << 10)
#endif
		{
#ifdef MUD_ECS_TYPED
			m_type = &type;
#endif
			m_data.reserve(capacity);
		}

		TBuffer(const TBuffer& other) = delete;
		TBuffer& operator=(const TBuffer& other) = delete;

		virtual void clear() override {	m_data.clear(); }
		virtual void add() override { m_data.emplace_back(); }
		virtual void remove(uint32_t index) override { swap_pop(m_data, index); }

#ifdef MUD_ECS_TYPED
		virtual Ref get(uint32_t index) override { return Ref(&m_data[index], *m_type); }
#endif

		vector<T> m_data;
	};
}