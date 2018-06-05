//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>

#ifndef MUD_CPP_20
#include <vector>
#include <functional>
#endif

namespace mud
{
	export_ using cstring = const char*;
	export_ using FunctionPointer = void* (*)();

	export_ class _refl_ MUD_OBJ_EXPORT Module
	{
	public:
		Module(cstring name);

		virtual void handle_load(Module& m) { UNUSED(m); }
		virtual void handle_unload(Module& m) { UNUSED(m); }

		//Type& m_type;

		_attr_ cstring m_name;
		_attr_ std::vector<Type*> m_types;
		_attr_ std::vector<Function*> m_functions;

		_attr_ cstring m_path;
		void* m_handle;
		uint64_t m_last_modified;
	};

#ifdef _WIN32
	typedef Module& (__cdecl *getModule_PROC)(void);
#else
	typedef Module& (*getModule_PROC)(void);
#endif

	export_ class MUD_OBJ_EXPORT ModuleLoader
	{
	public:
		ModuleLoader();

		Module* load_module(cstring path);
		void unload_module(Module& m);
		void reload_module(Module& m);
	};

	export_ class _refl_ MUD_OBJ_EXPORT Namespace
	{
	public:
		Namespace(cstring name = nullptr, Namespace* parent = nullptr);

		bool is_root() { return m_name == nullptr; }

		cstring m_name;
		Namespace* m_parent;
		std::vector<cstring> m_path;
	};

	export_ MUD_OBJ_EXPORT Namespace& namspc(std::vector<cstring> path);

	export_ class _refl_ MUD_OBJ_EXPORT System
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
		void load_module(Module& m);
		void unload_module(Module& m);
		Module& reload_module(Module& m);

		using FileVisitor = std::function<void(cstring, cstring)>;
		bool create_directory(cstring path);
		void visit_files(cstring path, FileVisitor visit_file);
		void visit_folders(cstring path, FileVisitor visit_folder, bool ignore_symbolic = true);
		void write_file(cstring path, cstring content);

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

	export_ _func_ inline System& system() { return System::instance(); }

	export_ template <typename T_Function>
	inline Function& function(T_Function func) { return System::instance().function(reinterpret_cast<FunctionPointer>(func)); }
}
