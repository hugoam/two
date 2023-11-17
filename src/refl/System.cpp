//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
#include <cstdio>
#include <cstring>

#ifdef _WIN32
	#include <windows.h>
	#define BINARY_EXT ".exe"
	#define MODULE_EXT ".dll"
#else
	#include <dlfcn.h>
	#define BINARY_EXT ""
	#define MODULE_EXT ".so"
#endif

#ifdef _DEBUG
	#define BUILD_SUFFIX "_d"
#else
	#define BUILD_SUFFIX ""
#endif

module two.refl;

namespace two
{
	Module* load_module(cstring path)
	{
		string module_path = string(path) + BUILD_SUFFIX + MODULE_EXT;
		string loaded_path = string(path) + BUILD_SUFFIX + "_loaded" + MODULE_EXT;
		
		if(!file_exists(module_path))
		{
			error("refl - module %s not found", module_path.c_str());
			return nullptr;
		}

		copy_file(module_path, loaded_path);

#ifdef _WIN32
		HMODULE module_handle = LoadLibraryA(loaded_path.c_str());
#else
		void* module_handle = dlopen(loaded_path.c_str(), RTLD_NOW);
#endif

#ifdef _WIN32
		GetModule get_module = (GetModule)GetProcAddress(module_handle, "getModule");
#else
		GetModule get_module = (GetModule)dlsym(module_handle, "getModule");
#endif

		Module& m = get_module();

		m.m_handle = module_handle;
		m.m_path = module_path.c_str();

		return &m;
	}

	void unload_module(Module& m)
	{
#ifdef _WIN32
		int result = FreeLibrary((HMODULE) m.m_handle);
#else
		int result = dlclose(m.m_handle);
#endif
		UNUSED(result);
	}

	void reload_module(Module& m)
	{
#ifdef _WIN32
		HANDLE module_file = CreateFile(m.m_path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(module_file == INVALID_HANDLE_VALUE)
			return;

		uint64_t last_modified;
		GetFileTime(module_file, NULL, NULL, (FILETIME*)&last_modified);

		if(m.m_last_modified < last_modified)
		{
			// do reload
		}

		CloseHandle(module_file);
#else
		UNUSED(m);
#endif
	}

	FunctionPointer module_function(Module& module, cstring name)
	{
#ifdef _WIN32
		return (FunctionPointer)GetProcAddress((HMODULE)module.m_handle, name);
#else
		return (FunctionPointer)dlsym(module.m_handle, name);
#endif
	}

	System::System()
	{
		m_namespaces.reserve(100);
	}

	void System::launch_process(cstring path, cstring args)
	{
		string binary_path = string(path) + BUILD_SUFFIX + BINARY_EXT;

#ifdef _WIN32
		STARTUPINFO startupInfo = { sizeof(startupInfo) };
		PROCESS_INFORMATION processInfo = {};

		string cmd = string(path) + " " + string(args);
		vector<char> mutcmd(cmd.c_str(), cmd.c_str() + cmd.size() + 1);

		CreateProcess(path, mutcmd.data(), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo);

		WaitForSingleObject(processInfo.hProcess, INFINITE);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
#else
		UNUSED(binary_path); UNUSED(args);
#endif
	}

	void System::load_modules(span<Module*> modules)
	{
		for(Module* m : modules)
			this->load_module(*m);
	}

	bool System::has_module(Module& m)
	{
		return has(m_modules, &m);
	}

	Module* System::open_module(cstring path)
	{
		return two::load_module(path);
	}

	void System::load_module(Module& m)
	{
		if(has(m_modules, &m))
			return;

		m_modules.push_back(&m);

		for(Module* dep : m.m_deps)
			load_module(*dep);

		for(Type* type : m.m_types)
			m_types.push_back(type);
		for(Alias* alias : m.m_aliases)
			m_aliases.push_back(alias);

		for(Function* function : m.m_functions)
			m_functions.push_back(function);

		for(Type* type : m.m_types)
			if(g_class[type->m_id])
				cls(*type).setup_class();
	}

	void System::unload_module(Module& m)
	{
		remove(m_modules, &m);

		for(Type* type : m.m_types)
			remove(m_types, type);
		for(Alias* alias : m.m_aliases)
			remove(m_aliases, alias);

		for(Function* function : m.m_functions)
			remove(m_functions, function);

		two::unload_module(m);
	}

	Module& System::reload_module(Module& m)
	{
		cstring path = m.m_path;
		this->unload_module(m);
		Module& reloaded = *this->open_module(path);
		this->load_module(reloaded);
		return reloaded;
	}

	Type* System::find_type(cstring name)
	{
		for(Type* type : m_types)
			if(strcmp(type->m_name, name) == 0)
				return type;
		return nullptr;
	}

	Function* System::find_function(cstring name)
	{
		for(Function* function : m_functions)
			if(strcmp(function->m_name, name) == 0)
				return function;
		return nullptr;
	}

	Function* System::find_function(cstring nemespace, cstring name)
	{
		for(Function* function : m_functions)
			if(function->m_namespace->m_name == string(nemespace) && function->m_name == string(name))
				return function;
		return nullptr;
	}

	Function& System::function(FunctionPointer identity)
	{
		for(Function* func : m_functions)
			if(func->m_identity == identity)
			{
				return *func;
			}
		error("retrieving function");
		return *m_functions[0];
	}

	vector<cstring> System::meta_symbols()
	{
		vector<cstring> symbols;

		for(Function* function : System::instance().m_functions)
			symbols.push_back(function->m_name);

		for(Type* type : System::instance().m_types)
			symbols.push_back(type->m_name);

		return symbols;
	}

	void System::dump_meta_info()
	{
		for(Function* function : System::instance().m_functions)
			info("meta function %s", function->m_name);

		for(Type* type : System::instance().m_types)
		{
			info("meta type %s", type->m_name);

			if(!g_class[type->m_id])
				continue;

			for(Member& member : cls(*type).m_members)
				if(member.m_object_type == type)
					printf("      Meta member %s::%s\n", member.m_object_type->m_name, member.m_name);
			for(Method& method : cls(*type).m_methods)
				if(method.m_object_type == type)
					printf("      Meta method %s::%s\n", method.m_object_type->m_name, method.m_name);
			for(Static& static_member : cls(*type).m_static_members)
				printf("      Meta static member %s::%s\n", static_member.m_value.m_type->m_name, static_member.m_name);
		}
	}

	void System::dump_memory_usage()
	{
		printf("LOG: memory usage\n");
		printf("-----------------\n");
		for(Type* type : m_types)
		{
			if(type->m_debug_count == 0)
				continue;
			printf("Type : %s\n", type->m_name);
			printf(" ----- Objects : %zu\n", type->m_debug_count);
			printf(" ----- Memory : %zu\n", type->m_debug_memory);
		}
	}

	Namespace& System::get_namespace(span<cstring> path)
	{
		auto compare = [](span<cstring> first, span<cstring> second)
		{
			if(first.size() != second.size())
				return false;
			for(size_t i = 0; i < first.size(); ++i)
				if(strcmp(first[i], second[i]) != 0)
					return false;
			return true;
		};

		for(Namespace& location : m_namespaces)
			if(compare(location.m_path, path))
			{
				return location;
			}

		Namespace* parent = nullptr;
		cstring name = "";

		if(!path.empty())
		{
			name = path[path.size() - 1];
			parent = &namspc({ path.data(), path.size() - 1 });
		}

		m_namespaces.push_back({ name, parent });
		return m_namespaces.back();
	}
}
