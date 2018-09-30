//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>
#include <type/Any.h>
#include <infra/Vector.h>

#ifndef MUD_CPP_20
#include <functional>
#endif

namespace mud
{
	export_ template <class T>
	class VectorIterable : public Iterable
	{
	public:
		VectorIterable(const std::vector<T>& vec) : m_vector(vec) {}

		virtual size_t size() const { return m_vector.size(); }
		virtual void iterate(const std::function<void(Ref)>& callback) const { for(const T& value : m_vector) callback(ref(value)); }
		virtual bool has(Ref ref) const { for(const T& value : m_vector) if(any_compare<T>(val<T>(ref), value)) return true; return false; }

	protected:
		const std::vector<T>& m_vector;
	};

	export_ template <class T>
	typename std::enable_if<is_comparable<T>::value, void>::type vector_remove_any(std::vector<T>& vector, T value) { vector_remove(vector, value); }

	export_ template <class T>
	typename std::enable_if<!is_comparable<T>::value, void>::type vector_remove_any(std::vector<T>& vector, T& value) { vector_remove_object(vector, value); }

	export_ template <class T>
	class VectorSequence : public Sequence
	{
	public:
		VectorSequence(std::vector<T>& vec) : m_vector(vec) {}

		virtual size_t size() const { return m_vector.size(); }
		virtual void iterate(const std::function<void(Ref)>& callback) const { for(const T& value : m_vector) callback(ref(value)); }
		virtual bool has(Ref ref) const { for(const T& value : m_vector) if(any_compare<T>(val<T>(ref), value)) return true; return false; }

		virtual void add(Ref ref)
		{
			T value = val<T>(ref);
			m_vector.push_back(value);
		}
		virtual void remove(Ref ref) { vector_remove_any(m_vector, val<T>(ref)); }

	protected:
		std::vector<T>& m_vector;
	};
}
