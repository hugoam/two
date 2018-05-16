//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Reflect/Method.h>

#include <vector>

namespace mud
{
	class _refl_ MUD_OBJ_EXPORT Module
	{
	public:
		Module(cstring name);

		virtual void handleLoad(Module& module) { UNUSED(module); }
		virtual void handleUnload(Module& module) { UNUSED(module); }

		//Type& m_type;

		_attr_ cstring m_name;
		_attr_ std::vector<Type*> m_types;
		std::vector<Function> m_functions;

		_attr_ cstring m_path;
		void* m_handle;
		uint64_t m_last_modified;
	};

#ifdef _WIN32
	typedef Module& (__cdecl *getModule_PROC)(void);
#else
	typedef Module& (*getModule_PROC)(void);
#endif

	class MUD_OBJ_EXPORT ModuleLoader
	{
	public:
		ModuleLoader();

		Module* load_module(cstring path);
		void unload_module(Module& module);
		void reload_module(Module& module);
	};

	class _refl_ MUD_OBJ_EXPORT Namespace
	{
	public:
		Namespace(cstring name = nullptr, Namespace* parent = nullptr);

		bool is_root() { return m_name == nullptr; }

		cstring m_name;
		Namespace* m_parent;
		std::vector<cstring> m_path;
	};

	MUD_OBJ_EXPORT Namespace& namspc(std::vector<cstring> path);

	class _refl_ MUD_OBJ_EXPORT System
	{
	public:
		System();

		std::vector<Namespace> m_namespaces; // @todo fix reflection
		_attr_ std::vector<Module*> m_modules;
		_attr_ std::vector<Type*> m_types;
		_attr_ std::vector<Prototype*> m_prototypes;
		_attr_ std::vector<Function*> m_functions;

		void launch_process(cstring path, cstring args);

		void load_modules(std::vector<Module*> modules);

		Module* open_module(cstring path);
		void load_module(Module& module);
		void unload_module(Module& module);
		Module& reload_module(Module& module);

		bool create_directory(cstring path);

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

	_func_ inline System& system() { return System::instance(); }

	template <typename T_Function>
	Function& function(T_Function func) { return System::instance().function(function_id(func)); }
}
