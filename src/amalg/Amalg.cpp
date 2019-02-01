#include <stl/string.h>
#include <stl/set.h>
#include <infra/Vector.h>
#include <infra/File.h>
#include <infra/String.h>
#include <amalg/Amalg.h>

#include <stl/string.hpp>
#include <stl/vector.hpp>
#include <stl/unordered_set.hpp>
#include <stl/unordered_map.hpp>

#include <cstdio>

namespace stl
{
	template class unordered_set<string>;
}

namespace mud
{
	class Amalgamator
	{
	public:
		class Module
		{
		public:
			Module(const string& root, const string& nemespace, const string& name, const string& subdir)
				: root(root), nemespace(nemespace), name(name), dotname(replace(name, "-", ".")), subdir(subdir), path(root + "/" + subdir)
			{}

			string root;
			string nemespace;
			string name;
			string dotname;
			string subdir;
			string path;

			set<string> m_included_h;
			set<string> m_included_cpp;

			string m_h;
			string m_cpp;

			set<string> m_includes_h;
			set<string> m_includes_cpp;

			set<string> m_deps_h;
			set<string> m_deps_cpp;

			string dest_h() { return nemespace + "/" + dotname + ".h"; }
			string dest_cpp() { return nemespace + "/" + dotname + ".cpp"; }
		};

		vector<string> m_filter;
		vector<Module> m_modules;

		bool filter(const string& line)
		{
			if (line == "#pragma once") return true;
			return vector_has(m_filter, line);
		}

		struct Include { Module* module = nullptr; string file; };
		Include module_include(const string& line)
		{
			string clean = replace(replace(line, " ", ""), "\t", "");
			if(clean.substr(0, 8) != "#include")
				return {};

			string file = line.substr(line.find("<") + 1, line.rfind(">") - line.find("<") - 1);
			for(Module& module : m_modules)
				if(is_subpath(module.root + "/" + file, module.path + "/")
				&& file_exists(module.root + "/" + file))
				{
					string relative = relative_to(module.root + "/" + file, module.path);
					return { &module, relative };
				}
			return { nullptr, file };
		}

		void process_cpp(Module& module, const string& file)
		{
			if (module.m_included_cpp.find(file) != module.m_included_cpp.end())
				return;

			printf("processing file %s\n", file.c_str());

			module.m_included_cpp.insert(file);

			auto read_line = [&](const string& line)
			{
				Include include = module_include(line);
				if(include.module)
				{
					if(file_extension(include.file) == "h"
					|| file_extension(include.file) == "hpp")
						module.m_deps_cpp.insert(include.module->dest_h());
					else
						process_cpp(module, include.file);
				}
				//else if(include.file != "")
				//	module.m_includes_cpp.insert(include.file);
				else if(filter(line))
					;
				else
					module.m_cpp += line + "\n";
			};

			read_text_file(module.path + "/" + file, read_line);
		}
		
		void process_h(Module& module, const string& file)
		{
			if(module.m_included_h.find(file) != module.m_included_h.end())
				return;

			printf("processing file %s\n", file.c_str());

			module.m_included_h.insert(file);

			auto read_line = [&](const string& line)
			{
				Include include = module_include(line);
				if(include.module == &module)
					process_h(module, include.file);
				else if(include.module)
					module.m_deps_h.insert(include.module->dest_h());
				//else if(include.file != "")
				//	module.m_includes_h.insert(include.file);
				else if (filter(line))
					;
				else
					module.m_h += line + "\n";
			};

			read_text_file(module.path + "/" + file, read_line);
		}

		void add(const string& root, const string& nemespace, const string& name, const string& subdir, bool refl = true)
		{
			m_modules.push_back({ root, nemespace, name, subdir });
			if(refl)
				m_modules.push_back({ root, nemespace, name + ".refl", "meta/" + subdir });
		}

		void run()
		{
			for(Module& module : m_modules)
				this->process(module);
		}

		void process(Module& module)
		{
			if(!directory_exists(module.path))
				return;

			auto visit = [&](const string& file)
			{
				string ext = file_extension(file);
				if(vector_has({ "cpp", "cxx", "cc", "c" }, ext))
					process_cpp(module, file);
				if(vector_has({ "hpp", "hh", "h" }, ext))
					process_h(module, file);
			};

			visit_files_recursive(module.path, visit);

			auto write_includes = [&](const set<string>& includes, bool pragma, string& file)
			{
				string header;
				if(pragma)
					header += "#pragma once\n\n";
				for (string include : includes)
					header += "#include <" + include + ">" + "\n";
				file.insert(size_t(0), header);
			};

			//write_includes(module.m_includes_h, module.m_h);
			//write_includes(module.m_includes_cpp, module.m_cpp);

			write_includes(module.m_deps_h, true, module.m_h);
			write_includes(module.m_deps_cpp, false, module.m_cpp);

			update_file(module.root + "/" + module.dest_h(), module.m_h);
			update_file(module.root + "/" + module.dest_cpp(), module.m_cpp);
		}

	};
}

using namespace mud;

int main(int argc, char *argv[])
{
	vector<string> filter = {
		"//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net",
		"//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.",
		"//  This notice and the license may not be removed or altered from any source distribution.",
		"//  This software is licensed  under the terms of the GNU General Public License v3.0.",
		"//  See the attached LICENSE.txt file or https://www.gnu.org/licenses/gpl-3.0.en.html.",
	};

	string mudsrc = "d:/Documents/Programmation/toy/mud/src";
	string toysrc = "d:/Documents/Programmation/toy/src";

	Amalgamator amalgamator;
	amalgamator.m_filter = filter;

	for (string module : { "infra", "jobs", "type", "tree", "pool", "refl", "ecs", "srlz", "math", "geom", "noise", "wfc", "fract", "lang", "ctx", "ui", "uio", "snd" })
		amalgamator.add(mudsrc, "mud", module, module);
	for (string module : { "ctx-glfw", "ctx-wasm", "ctx-win" })
		amalgamator.add(mudsrc, "mud", module, module);
	for (string module : { "ui-vg", "ui-nvg" })
		amalgamator.add(mudsrc, "mud", module, module);
	for (string module : { "bgfx", "gfx", "gltf", "gfx-pbr", "gfx-obj", "gfx-gltf", "gfx-ui", "gfx-edit", "tool", "wfc-gfx", "frame" })
		amalgamator.add(mudsrc, "mud", module, module);
	for (string module : { "util", "core", "visu", "block", "edit", "shell" })
		amalgamator.add(toysrc, "toy", module, module);

	amalgamator.run();

	return 0;
}
