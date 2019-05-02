//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/vector.h>
#include <type/Var.h>
#include <type/Unique.h>
#include <refl/Forward.h>
#include <refl/Call.h>

namespace two
{
	export_ class refl_ TWO_REFL_EXPORT Injector : public Call
	{
	public:
		Injector(const Constructor& constructor);
		Injector(Type& type, size_t arguments);
		Injector(Type& type, ConstructorIndex constructor = ConstructorIndex::Default);

		Type& m_object_type;
		const Constructor& m_constructor;
		
		void inject(Var& value);
		Ref inject(Pool& pool);

		Var injectvar();
		Ref injectpool();

		void destroy(Ref object);
	};

	export_ class refl_ TWO_REFL_EXPORT Creator
	{
	public:
		Creator(Type& type);

		attr_ Type& m_type;
		attr_ bool m_construct;
		attr_ Type* m_prototype;
		attr_ Injector& injector() const { return *m_injector; }

		object<Injector> m_injector;

		void set_prototype(Type& prototype);
	};
}
