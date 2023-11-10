//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/vector.h>
#endif
#include <refl/Forward.h>
#include <refl/Namespace.h>

namespace two
{
	export_ using cstring = const char*;
	export_ using FunctionPointer = void* (*)();
	
	export_ TWO_REFL_EXPORT Module* load_module(cstring path);
	export_ TWO_REFL_EXPORT void unload_module(Module& m);
	export_ TWO_REFL_EXPORT void reload_module(Module& m);
	export_ TWO_REFL_EXPORT FunctionPointer module_function(Module& module, cstring name);

	export_ class refl_ TWO_REFL_EXPORT System
	{
	public:
		System();

		vector<Namespace> m_namespaces; // @todo fix reflection
		attr_ vector<Module*> m_modules;
		attr_ vector<Type*> m_types;
		attr_ vector<Alias*> m_aliases;
		attr_ vector<Function*> m_functions;

		void launch_process(cstring path, cstring args);

		void load_modules(span<Module*> modules);

		Module* open_module(cstring path);
		void load_module(Module& m);
		void unload_module(Module& m);
		Module& reload_module(Module& m);
		bool has_module(Module& m);

		vector<cstring> meta_symbols();

		void dump_meta_info();
		void dump_memory_usage();

		Namespace& get_namespace(span<cstring> path);
		Function& function(FunctionPointer pointer);

		Type* find_type(cstring name);
		Function* find_function(cstring name);
		Function* find_function(cstring nemespace, cstring name);

		static System& instance() { static System instance; return instance; }
	};

	export_ func_ inline System& system() { return System::instance(); }

	export_ template <class T_Function>
	inline Function& func(T_Function func) { return System::instance().function(reinterpret_cast<FunctionPointer>(func)); }
}
