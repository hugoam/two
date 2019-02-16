//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stdint.h>
#include <stl/vector.h>
#include <type/Forward.h>
#include <type/Ref.h>
#include <type/Type.h>
#include <type/Unique.h>

namespace mud
{
	export_ class refl_ MUD_TYPE_EXPORT Indexer
	{
	public:
		Indexer(const Type& type) : m_type(&type), m_objects(1, Ref{ type }), m_count(0), m_next(0) {}

		attr_ const Type* m_type;
		attr_ vector<Ref> m_objects;

		inline uint32_t alloc() { return m_next++; }
		inline void add(uint32_t id, Ref object) { this->resize(id); m_objects[id] = object; ++m_count; }
		inline uint32_t index(uint32_t id, Ref object) { if(id == UINT32_MAX) id = this->alloc(); this->add(id, object); return id; }
		inline uint32_t index(Ref object) { uint32_t id = this->alloc(); this->add(id, object); return id; }
		inline void remove(uint32_t id) { m_objects[id] = Ref(m_type); --m_count; }

		inline void resize(uint32_t id) { if(id >= m_objects.size()) m_objects.resize(id+1); }

		template <class Visitor>
		inline void iterate(Visitor visitor) const { for(Ref object : m_objects) if(object.m_value) visitor(object); }
		inline bool has(uint32_t id) const { return m_objects[id].m_value != nullptr; }

		inline void clear() { m_objects.clear(); m_count = 0; }

	public:
		size_t m_count;
		uint32_t m_next;
	};

	export_ class refl_ MUD_TYPE_EXPORT Index //
	{
	public:
		Index() : m_indexers(c_max_types) {}

		Index(const Index& other) = delete;
		Index& operator=(const Index& other) = delete;

		meth_ Indexer& indexer(const Type& type)
		{
			if(!m_indexers[type.m_id])
				m_indexers[type.m_id] = make_unique<Indexer>(type);
			return *m_indexers[type.m_id];
		}

		vector<unique<Indexer>> m_indexers;

		attr_ static Index me;
	};

	export_ inline Indexer& indexer(const Type& type) { return Index::me.indexer(type); }
	export_ inline uint32_t index(const Type& type, uint32_t id, Ref object) { return Index::me.indexer(type).index(id, object); }
	export_ inline uint32_t index(const Type& type, Ref object) { return Index::me.indexer(type).index(object); }
	export_ inline void unindex(const Type& type, uint32_t id) { Index::me.indexer(type).remove(id); }

	export_ func_ inline Ref indexed(const Type& type, uint32_t id) { return Index::me.indexer(type).m_objects[id]; }
}
