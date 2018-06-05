//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef MUD_CPP_20
#include <obj/Cpp20.h>
#include <dirent.h>
#else
#include <fstream>
#include <string>
#include <dirent.h>
#endif

#ifdef MUD_MODULES
module mud.obj;
#else
#include <obj/Config.h>
#include <obj/System/System.h>
#include <obj/Vector.h>
#include <obj/Reflect/Class.h>
#endif

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

namespace mud
{
	using string = std::string;

	void copyfile(const string& source, const string& dest)
	{
		std::ifstream file(source, std::ios::binary);
		std::ofstream destFile(dest, std::ios::binary);
		destFile << file.rdbuf();
	}

	Module::Module(cstring name)
		//: m_type(type)
		: m_name(name)
	{}

	ModuleLoader::ModuleLoader()
	{}

	Module* ModuleLoader::load_module(cstring path)
	{
		string module_path = string(path) + BUILD_SUFFIX + MODULE_EXT;
		string loaded_path = string(path) + BUILD_SUFFIX + "_loaded" + MODULE_EXT;

		if(!std::ifstream(module_path, std::ios::binary).good())
		{
			printf("ERROR: Module %s not found\n", module_path.c_str());
			return nullptr;
		}

		copyfile(module_path, loaded_path);

#ifdef _WIN32
		HMODULE module_handle = LoadLibraryA(loaded_path.c_str());
#else
		void* module_handle = dlopen(loaded_path.c_str(), RTLD_NOW);
#endif

#ifdef _WIN32
		getModule_PROC get_module = (getModule_PROC)GetProcAddress(module_handle, "getModule");
#else
		getModule_PROC get_module = (getModule_PROC)dlsym(module_handle, "getModule");
#endif

		Module& m = get_module();

		m.m_handle = module_handle;
		m.m_path = module_path.c_str();

		return &m;
	}

	void ModuleLoader::unload_module(Module& m)
	{
#ifdef _WIN32
		int result = FreeLibrary((HMODULE) m.m_handle);
#else
		int result = dlclose(m.m_handle);
#endif
		UNUSED(result);
	}

	void ModuleLoader::reload_module(Module& m)
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

	System::System()
	{
		m_namespaces.reserve(100);
	}

	void System::visit_files(cstring path, FileVisitor visit_file)
	{
		DIR* dir = opendir(path);
		dirent* ent;

		while ((ent = readdir(dir)) != NULL)
			if (ent->d_type & DT_REG)
			{
				visit_file(path, ent->d_name);
			}


		closedir(dir);
	}

	void System::visit_folders(cstring path, FileVisitor visit_file, bool ignore_symbolic)
	{
		DIR* dir = opendir(path);
		dirent* ent;

		while((ent = readdir(dir)) != NULL)
			if(ent->d_type & DT_DIR)
			{
				bool is_symbolic = string(ent->d_name) == "." || string(ent->d_name) == "..";
				if(!is_symbolic || !ignore_symbolic)
					visit_file(path, ent->d_name);
			}

		closedir(dir);
	}

	void System::write_file(cstring path, cstring content)
	{
		std::ofstream out(path);
		out << content;
	}

	void System::launch_process(cstring path, cstring args)
	{
		string binary_path = string(path) + BUILD_SUFFIX + BINARY_EXT;

#ifdef _WIN32
		STARTUPINFO startupInfo = { sizeof(startupInfo) };
		PROCESS_INFORMATION processInfo = {};

		string cmd = string(path) + " " + string(args);
		std::vector<char> mutcmd(cmd.c_str(), cmd.c_str() + cmd.length() + 1);

		CreateProcess(path, mutcmd.data(), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo);

		WaitForSingleObject(processInfo.hProcess, INFINITE);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
#else
		UNUSED(binary_path); UNUSED(args);
#endif
	}

	void System::load_modules(std::vector<Module*> modules)
	{
		for(Module* m : modules)
			this->load_module(*m);
	}

	Module* System::open_module(cstring path)
	{
		return m_loader.load_module(path);
	}

	void System::load_module(Module& m)
	{
		m_modules.push_back(&m);

		for(Type* type : m.m_types)
			m_types.push_back(type);

		for(Function* function : m.m_functions)
			m_functions.push_back(function);

		for(Module* depend : m_modules)
			depend->handle_load(m);
	}

	void System::unload_module(Module& m)
	{
		for(Module* depend : m_modules)
			depend->handle_unload(m);

		vector_remove(m_modules, &m);

		for(Type* type : m.m_types)
			vector_remove(m_types, type);

		for(Function* function : m.m_functions)
			vector_remove(m_functions, function);

		m_loader.unload_module(m);
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

	Function& System::function(FunctionPointer identity)
	{
		for(Function* func : m_functions)
			if(func->m_identity == identity)
			{
				return *func;
			}
		printf("ERROR: retrieving function\n");
		return *m_functions[0];
	}

	std::vector<cstring> System::meta_symbols()
	{
		std::vector<cstring> symbols;

		for(Function* function : System::instance().m_functions)
			symbols.push_back(function->m_name);

		for(Type* type : System::instance().m_types)
			symbols.push_back(type->m_name);

		return symbols;
	}

	void System::dump_meta_info()
	{
		for(Function* function : System::instance().m_functions)
			printf("INFO: Meta function %s\n", function->m_name);

		for(Type* type : System::instance().m_types)
		{
			printf("INFO: Meta type %s\n", type->m_name);

			if(!type->m_class)
				continue;

			for(Member& member : type->m_class->m_members)
				if(member.m_object_type == type)
					printf("      Meta member %s::%s\n", member.m_object_type->m_name, member.m_name);
			for(Method& method : type->m_class->m_methods)
				if(method.m_object_type == type)
					printf("      Meta method %s::%s\n", method.m_object_type->m_name, method.m_name);
			for(Static& static_member : type->m_class->m_static_members)
				printf("      Meta static member %s::%s\n", static_member.m_value.m_type->m_name, static_member.m_name);
		}
	}

	void System::dump_memory_usage()
	{
		printf("LOG: memory usage\n");
		printf("-----------------\n");
		for(Type* type : m_types)
		{
			if(type->debugTotalCount == 0)
				continue;
			printf("Type : %s\n", type->m_name);
			printf(" ----- Objects : %zu\n", type->debugTotalCount);
			printf(" ----- Memory : %zu\n", type->debugTotalMemory);
		}
	}

	Namespace::Namespace(cstring name, Namespace* parent)
		: m_name(name)
		, m_parent(parent)
	{
		if(parent)
		{
			m_path = parent->m_path;
			m_path.push_back(name);
		}
	}

	bool compare(const std::vector<cstring>& first, const std::vector<cstring>& second)
	{
		if(first.size() != second.size())
			return false;
		for(size_t i = 0; i < first.size(); ++i)
			if(strcmp(first[i], second[i]) != 0)
				return false;
		return true;
	}

	Namespace& System::get_namespace(std::vector<cstring> path)
	{
		for(Namespace& location : m_namespaces)
			if(compare(location.m_path, path))
			{
				return location;
			}

		Namespace* parent = nullptr;
		cstring name = nullptr;

		if(!path.empty())
		{
			name = vector_pop(path);
			parent = &namspc(path);
		}

		m_namespaces.push_back(Namespace{ name, parent });
		return m_namespaces.back();
	}

	Namespace& namspc(std::vector<cstring> path)
	{
		return system().get_namespace(path);
	}

}
