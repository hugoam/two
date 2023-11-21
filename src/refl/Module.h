//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>

namespace two
{
	export_ using cstring = const char*;

	export_ struct refl_ TWO_REFL_EXPORT Alias
	{
		Type* m_type;
		Namespace* m_namespace;
		cstring m_name;
	};

	export_ class refl_ TWO_REFL_EXPORT Module
	{
	public:
		Module(cstring name, vector<Module*> deps);

		attr_ cstring m_name;
		attr_ vector<Module*> m_deps;
		attr_ vector<Type*> m_types;
		attr_ vector<Alias*> m_aliases;
		attr_ vector<Function*> m_functions;

		attr_ cstring m_path;
		void* m_handle;
		uint64_t m_last_modified;
	};

#ifdef _WIN32
	typedef Module& (__cdecl *GetModule)(void);
#else
	typedef Module& (*GetModule)(void);
#endif
}
