#pragma once

#ifndef MUD_MODULES
#include <meta/infra/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
	void mud_infra_meta(Module& m)
	{
		
		// Base Types
		
		// Enums
		{
			static Meta meta = { type<mud::ThreadPriority>(), &namspc({ "mud" }), "ThreadPriority", sizeof(mud::ThreadPriority), TypeClass::Enum };
			static Enum enu = { type<mud::ThreadPriority>(),
				false
				{ "Normal", "Display", "UrgentDisplay" },
				{ 0, 1, 2 },
				{ var(mud::Normal), var(mud::Display), var(mud::UrgentDisplay) }
			};
			meta_enum<mud::ThreadPriority>();
		}
		
		// Sequences
		
		m.m_types.push_back(&type<mud::array<T>>());
		m.m_types.push_back(&type<mud::ThreadPriority>());
	}
}
