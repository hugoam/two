#include <stl/string.h>
#include <stl/set.h>
#include <infra/Vector.h>
#include <infra/File.h>
#include <clrefl/Amalg.h>

#include <cstdio>

namespace mud
{
	class Amalgamator
	{
	public:
		class Module
		{
		public:
			Module(const string& root, const string& subdir)
				: root(root), subdir(subdir), path(root + "/" + subdir)
			{}

			string root;
			string subdir;
			string path;

			set<string> m_included;

			string m_h;
			string m_cpp;

			set<string> m_includes_h;
			set<string> m_includes_cpp;
		};

		vector<Module> m_modules;

		struct Include { Module* module = nullptr; string file; };
		Include module_include(const string& line)
		{
			if(line.substr(0, 8) != "#include")
				return {};

			string file = line.substr(line.find("<") + 1, line.rfind(">") - line.find("<") - 1);
			string subdir = file_directory(file);
			for(Module& module : m_modules)
				if(directory_contains(module.path, module.root + "/" + subdir))
				{
					return { &module, file_name(file) };
				}
			return { nullptr, file };
		}

		void process_cpp(Module& module, const string& file)
		{
			auto read_line = [&](const string& line)
			{
				Include include = module_include(line);
				if(include.module)
					module.m_includes_cpp.insert(include.module->path);
				else if(include.file != "")
					module.m_includes_cpp.insert(include.file);
				else
					module.m_cpp += line + "\n";
			};

			read_text_file(module.path + "/" + file, read_line);
		}
		
		void process_h(Module& module, const string& file)
		{
			if(module.m_included.find(file) != module.m_included.end())
				return;

			printf("processing file %s\n", file.c_str());

			module.m_included.insert(file);

			auto read_line = [&](const string& line)
			{
				Include include = module_include(line);
				if(include.module == &module)
					process_h(module, include.file);
				else if(include.module)
					module.m_includes_h.insert(include.module->path);
				else if(include.file != "")
					module.m_includes_h.insert(include.file);
				else
					module.m_h += line + "\n";
			};

			read_text_file(module.path + "/" + file, read_line);
		}

		void process(const string& root, const string& subdir)
		{
			Module& module = vector_push(m_modules, root, subdir);

			auto visit = [&](const string& path, const string& file)
			{
				string ext = file_extension(file);
				if(vector_has({ "cpp", "cxx", "cc", "c" }, ext))
					process_cpp(module, file);
				if(vector_has({ "hpp", "hh", "h" }, ext))
					process_h(module, file);
			};

			visit_files(module.path, visit);

			auto write_includes = [&](const set<string>& includes, string& file)
			{
				string header;
				for (string include : includes)
					header += "#include <" + include + ">" + "\n";
				file.insert(file.begin(), header);
			};

			write_includes(module.m_includes_h, module.m_h);
			write_includes(module.m_includes_cpp, module.m_cpp);

			update_file(module.root + "/" + subdir + ".h", module.m_h);
			update_file(module.root + "/" + subdir + ".cpp", module.m_cpp);
		}

	};
}

using namespace mud;

#if 0
int main(int argc, char *argv[])
{
	string directory = "d:/Documents/Programmation/toy/mud/src";
	Amalgamator amalgamator;
	for (string module : { "infra", "jobs", "type", "tree", "pool", "refl", "ecs", "srlz", "math", "geom", "noise", "wfc", "fract", "lang", "ctx", "ui", "uio", "snd" })
		amalgamator.process(directory, module);
	return 0;
}
#endif