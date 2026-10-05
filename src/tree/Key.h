//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <infra/Config.h>

#ifndef TWO_STD_MODULES
#include <cstdint>
#include <source_location>
#endif

#ifndef TWO_TREE_EXPORT
#define TWO_TREE_EXPORT TWO_IMPORT
#endif

namespace two
{
	// identifies a node of a graph among its siblings: by default, the location in the code where it's declared
	// an empty key falls back to identifying the node by its position among its siblings
	export_ struct refl_ TWO_TREE_EXPORT NodeKey
	{
		attr_ uint64_t m_value = 0;
	};

	export_ constexpr uint64_t key_mix(uint64_t hash, uint64_t value) { return (hash ^ value) * 1099511628211ull; }

#ifdef TWO_KEY_HASH
	// the key is a hash of the location, computed at compile time
	consteval uint64_t key_hash(std::source_location location)
	{
		uint64_t hash = 14695981039346656037ull;
		for(const char* c = location.file_name(); *c; ++c)
			hash = key_mix(hash, uint8_t(*c));
		return key_mix(key_mix(hash, location.line()), location.column());
	}

	export_ consteval NodeKey key(std::source_location location = std::source_location::current())
	{
		return { key_hash(location) };
	}
#else
	// the key is a mix of the address of the file name, the line and the column of the location, computed at runtime
	export_ inline NodeKey key(std::source_location location = std::source_location::current())
	{
		uint64_t hash = key_mix(14695981039346656037ull, uint64_t(uintptr_t(location.file_name())));
		return { key_mix(key_mix(hash, location.line()), location.column()) };
	}
#endif

	// keys of the nodes declared at a same location, e.g in a loop: by index, or by the object they represent
	export_ inline NodeKey key(uint64_t index, NodeKey base = key())
	{
		return { key_mix(base.m_value, index) };
	}

	export_ template <class T>
	inline NodeKey key(T* object, NodeKey base = key())
	{
		return { key_mix(base.m_value, uint64_t(uintptr_t(object))) };
	}

	// the conversions to a key from a number, e.g an index given by a script, and from nullptr, which is no key
	export_ TWO_TREE_EXPORT void register_tree_conversions();
}
