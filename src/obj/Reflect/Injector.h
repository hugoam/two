//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Any.h>
#include <obj/Unique.h>
#include <obj/NonCopy.h>
#include <obj/Reflect/Method.h>

#ifndef MUD_CPP_20
#include <vector>
#endif

namespace mud
{
	export_ class _refl_ MUD_OBJ_EXPORT Injector
	{
	public:
		Injector(Type& type, const Constructor& constructor);
		Injector(Type& type, size_t arguments);
		Injector(Type& type, ConstructorIndex constructor = ConstructorIndex::Default);

		_attr_ Type& m_type;
		const Constructor& m_constructor;
		std::vector<Var> m_args;

		array<Var> args(Type& type);

		void inject(Var& value);
		Ref inject(Pool& pool);

		Var injectvar();
		Ref injectpool();

	protected:
		Prototype* m_proto;
		std::vector<size_t> m_partIndex;
	};

	export_ class _refl_ MUD_OBJ_EXPORT Creator : public NonCopy
	{
	public:
		Creator(Type& type);

		_attr_ Type& m_type;
		_attr_ bool m_construct;
		_attr_ Type* m_prototype;
		_attr_ Injector& injector() const { return *m_injector; }

		void setPrototype(Type& prototype);

		Ref create();
		void destroy(Ref object);

		template <class T>
		T& create() { return val<T>(create()); }

	protected:
		object_ptr<Injector> m_injector;
	};
}
