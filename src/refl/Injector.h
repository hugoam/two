//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Any.h>
#include <obj/Unique.h>
#include <infra/NonCopy.h>
#include <refl/Forward.h>
#include <refl/Method.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ class refl_ MUD_REFL_EXPORT Injector
	{
	public:
		Injector(Type& type, const Constructor& constructor);
		Injector(Type& type, size_t arguments);
		Injector(Type& type, ConstructorIndex constructor = ConstructorIndex::Default);

		attr_ Type& m_type;
		const Constructor& m_constructor;
		std::vector<Var> m_args;

#ifdef MUD_PROTO
		array<Var> args(Type& type);
#endif

		void inject(Var& value);
		Ref inject(Pool& pool);

		Var injectvar();
		Ref injectpool();

	protected:
#ifdef MUD_PROTO
		Prototype* m_proto;
#endif
		std::vector<size_t> m_partIndex;
	};

	export_ class refl_ MUD_REFL_EXPORT Creator : public NonCopy
	{
	public:
		Creator(Type& type);

		attr_ Type& m_type;
		attr_ bool m_construct;
		attr_ Type* m_prototype;
		attr_ Injector& injector() const { return *m_injector; }

		void setPrototype(Type& prototype);

		Ref create();
		void destroy(Ref object);

		template <class T>
		T& create() { return val<T>(create()); }

	protected:
		object_ptr<Injector> m_injector;
	};
}
