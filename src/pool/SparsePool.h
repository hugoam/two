//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/unordered_map.h>
#include <stl/vector.h>
#include <pool/Forward.h>

#include <stdint.h>

namespace two
{
	export_ class refl_ TWO_POOL_EXPORT HandlePool
	{
	public:
		virtual ~HandlePool() {}
		virtual void clear() = 0;
	};

	template <class T>
	class SparsePool;

	export_ template <class T>
	struct refl_ struct_ SparseHandle
	{
		SparseHandle();
		SparseHandle(SparsePool<T>& pool, uint32_t handle);

		explicit operator bool() const;

		void destroy();

		operator T&();
		operator const T&() const;

		T* operator->();
		T& operator*();
		const T* operator->() const;
		const T& operator*() const;

		SparsePool<T>* m_pool = nullptr;
		uint32_t m_handle = UINT32_MAX;
	};

	template <class T>
	struct OwnedHandle;

	template <class T>
	struct DestroyHandle
	{
		static void destroy(const OwnedHandle<T>& handle) { UNUSED(handle); }
	};

	export_ template <class T>
	struct refl_ struct_ nocopy_ OwnedHandle : public SparseHandle<T>
	{
		OwnedHandle();
		OwnedHandle(SparsePool<T>& pool, uint32_t handle);
		~OwnedHandle();

		OwnedHandle(OwnedHandle& other) = delete;
		OwnedHandle& operator=(OwnedHandle& other) = delete;

		OwnedHandle(OwnedHandle&& other);
		OwnedHandle& operator=(OwnedHandle&& other);

		void swap(OwnedHandle& other);

		operator SparseHandle<T>() const;
	};

	export_ class TWO_POOL_EXPORT SparseHandles
	{
	public:
		SparseHandles();

		void ensure(uint32_t capacity);

		uint32_t alloc();
		uint32_t alloc(uint32_t count);
		void add(uint32_t handle);

		uint32_t create();
		uint32_t create(uint32_t count);
		uint32_t remove(uint32_t handle);

		void clear();

		uint32_t& operator[](uint32_t at);

		uint32_t size() const;
		uint32_t count() const;

		uint32_t reverse(uint32_t index) const;
		uint32_t handle(uint32_t index) const;

	private:
		vector<uint32_t> m_indices;
		vector<uint32_t> m_handles;
	};

	export_ template <class T>
	class SparsePool : public HandlePool
	{
	public:
		SparsePool();
		~SparsePool();

		template <class... Types>
		inline OwnedHandle<T> create(Types&&... args);

		void destroy(uint32_t handle);
		T& get(uint32_t handle);

		virtual void clear();

	public:
		SparseHandles m_handles;
		vector<T> m_objects;
		vector<uint32_t> m_available;
	};
}
