#include <infra/Config.h>
#include <infra/Pool.h>

#include <cmath>
#include <random>
#include <algorithm>

namespace mud
{
	FreeListBase::Node* FreeListBase::init(void* begin, void* end, size_t elementSize, size_t alignment, size_t extra)
	{
		void* const p = pointermath::align(begin, alignment, extra);
		void* const n = pointermath::align(pointermath::add(p, elementSize), alignment, extra);
		assert(p >= begin && p < end);
		assert(n >= begin && n < end && n > p);

		const size_t d = uintptr_t(n) - uintptr_t(p);
		const size_t num = (uintptr_t(end) - uintptr_t(p)) / d;

		// set first entry
		Node* head = static_cast<Node*>(p);

		// next entry
		Node* cur = head;
		for(size_t i = 1; i<num; ++i)
		{
			Node* next = pointermath::add(cur, d);
			cur->next = next;
			cur = next;
		}
		assert(cur < end);
		assert(pointermath::add(cur, d) <= end);
		cur->next = nullptr;
		return head;
	}

	FreeList::FreeList(void* begin, void* end, size_t elementSize, size_t alignment, size_t extra)
		: m_head(init(begin, end, elementSize, alignment, extra))
#ifndef NDEBUG
		, m_begin(begin), m_end(end)
#endif
	{}

	AtomicFreeList::AtomicFreeList(void* begin, void* end, size_t elementSize, size_t alignment, size_t extra)
		: m_head(init(begin, end, elementSize, alignment, extra))
	{}
}
