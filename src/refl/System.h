//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <refl/Forward.h>
#include <refl/Namespace.h>

#ifndef MUD_CPP_20
#include <vector>
#include <functional>
#endif

namespace mud
{
	export_ using cstring = const char*;
	export_ using FunctionPointer = void* (*)();
	
	export_ class MUD_REFL_EXPORT ModuleLoader
	{
	public:
		ModuleLoader();

		Module* load_module(cstring path);
		void unload_module(Module& m);
		void reload_module(Module& m);
	};

	export_ class refl_ MUD_REFL_EXPORT System
	{
	public:
		System();

		std::vector<Namespace> m_namespaces; // @todo fix reflection
		attr_ std::vector<Module*> m_modules;
		attr_ std::vector<Type*> m_types;
		//attr_ std::vector<Prototype*> m_prototypes;
		attr_ std::vector<Function*> m_functions;

		void launch_process(cstring path, cstring args);

		void load_modules(std::vector<Module*> modules);

		Module* open_module(cstring path);
		void load_module(Module& m);
		void unload_module(Module& m);
		Module& reload_module(Module& m);

		std::vector<cstring> meta_symbols();

		void dump_meta_info();
		void dump_memory_usage();

		Namespace& get_namespace(std::vector<cstring> path);
		Function& function(FunctionPointer pointer);

		Type* find_type(cstring name);
		Function* find_function(cstring name);

		static System& instance() { static System instance; return instance; }

	protected:
		ModuleLoader m_loader;
	};

	export_ func_ inline System& system() { return System::instance(); }

	export_ template <typename T_Function>
	inline Function& function(T_Function func) { return System::instance().function(reinterpret_cast<FunctionPointer>(func)); }
}
