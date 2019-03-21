#include <stl/string.h>
#include <stl/set.h>
#include <stl/algorithm.h>
#include <infra/Vector.h>
#include <infra/File.h>
#include <infra/StringOps.h>
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
			Module(const string& root, const string& dist, const string& nemespace, const string& name)
				: m_root(root), m_dist(dist), m_nemespace(nemespace), m_name(name), m_dotname(replace(name, "-", "."))
			{
				m_preproc_name = to_upper(nemespace + "_" + replace(m_dotname, ".", "_"));
			}

			string m_root;
			string m_dist;
			string m_nemespace;
			string m_name;
			string m_dotname;

			vector<string> m_files;

			string m_preproc_name;

			set<string> m_included_h;
			set<string> m_included_cpp;

			string m_h;
			string m_cpp;

			//set<string> m_includes_h;
			//set<string> m_includes_cpp;

			set<string> m_deps_h;
			set<string> m_deps_cpp;

			string dest_h() { return m_nemespace + "/" + m_dotname + ".h"; }
			string dest_cpp() { return m_nemespace + "/" + m_dotname + ".cpp"; }

			string dest_hpp() { return m_nemespace + "/" + m_dotname + ".hpp"; }

			string include(bool header_only) { return header_only ? this->dest_hpp() : this->dest_h(); }
		};

		vector<string> m_filter;
		vector<Module> m_modules;

		bool filter(const string& line)
		{
			if(line == "#pragma once") return true;
			return has(m_filter, line);
		}

		struct Include { Module* module = nullptr; string file; };
		Include module_include(const string& line)
		{
			string clean = replace(replace(line, " ", ""), "\t", "");
			if(clean.substr(0, 8) != "#include")
				return {};

			string file = line.substr(line.find("<") + 1, line.rfind(">") - line.find("<") - 1);
			for(Module& module : m_modules)
				if(has(module.m_files, file))
				{
					return { &module, file };
				}
			return { nullptr, file };
		}

		void process_cpp(Module& module, const string& file, bool header_only)
		{
			if(module.m_included_cpp.find(file) != module.m_included_cpp.end())
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
						module.m_deps_cpp.insert(include.module->include(header_only));
					else
						process_cpp(module, include.file, header_only);
				}
				//else if(include.file != "")
				//	module.m_includes_cpp.insert(include.file);
				else if(filter(line))
					;
				else
					module.m_cpp += line + "\n";

				return true;
			};

			read_text_file(module.m_root + "/" + file, read_line);
		}
		
		void process_h(Module& module, const string& file, bool header_only)
		{
			if(module.m_included_h.find(file) != module.m_included_h.end())
				return;

			printf("processing file %s\n", file.c_str());

			module.m_included_h.insert(file);

			auto read_line = [&](const string& line)
			{
				Include include = module_include(line);
				if(include.module == &module)
					process_h(module, include.file, header_only);
				else if(include.module)
					module.m_deps_h.insert(include.module->include(header_only));
				//else if(include.file != "")
				//	module.m_includes_h.insert(include.file);
				else if(filter(line))
					;
				else
					module.m_h += line + "\n";

				return true;
			};

			read_text_file(module.m_root + "/" + file, read_line);
		}

		void add(const string& root, const string& dist, const string& nemespace, const string& name, const string& subdir, bool refl = true)
		{
			Module& m = push(m_modules, root, dist, nemespace, name);

			auto add_file = [&](const string& file) { m.m_files.push_back(subdir + "/" + file); };
			visit_files_recursive(root + "/" + subdir, add_file);

			if(refl)
			{
				Module& refl = push(m_modules, root, dist, nemespace, name + ".refl");

				string meta_h = "meta/" + replace(name, "-", ".") + ".meta.h";
				string conv_h = "meta/" + replace(name, "-", ".") + ".conv.h";
				string meta_cpp = "meta/" + replace(name, "-", ".") + ".meta.cpp";

				refl.m_files = { meta_h, conv_h, meta_cpp };
			}
		}

		void run(bool header_only)
		{
			for(Module& module : m_modules)
				this->process(module, header_only);
		}

		void process(Module& module, bool header_only)
		{
			module.m_h = {};
			module.m_cpp = {};
			module.m_included_h = {};
			module.m_included_cpp = {};
			module.m_deps_h = {};
			module.m_deps_cpp = {};

			for(const string& file : module.m_files)
			{
				string ext = file_extension(file);
				if(has({ "cpp", "cxx", "cc", "c" }, ext))
					process_cpp(module, file, header_only);
				if(has({ "hpp", "hh", "h" }, ext))
					process_h(module, file, header_only);
			}

			auto write_includes = [&](const set<string>& includes, bool pragma, string& file)
			{
				string header;
				if(pragma)
					header += "#pragma once\n\n";
				for(string include : includes)
					header += "#include <" + include + ">" + "\n";
				header += "\n";
				file.insert(size_t(0), header);
			};

			//write_includes(module.m_includes_h, module.m_h);
			//write_includes(module.m_includes_cpp, module.m_cpp);

			write_includes(module.m_deps_h, true, module.m_h);
			write_includes(module.m_deps_cpp, false, module.m_cpp);

			if(header_only)
			{
				string hpp = module.m_h;

				hpp += "\n";
				hpp += "#ifdef " + module.m_preproc_name + "_IMPL\n";
				hpp += module.m_cpp;
				hpp += "#endif\n";

				update_file(module.m_dist + "/" + module.dest_hpp(), hpp);
			}
			else
			{
				update_file(module.m_dist + "/" + module.dest_h(), module.m_h);
				update_file(module.m_dist + "/" + module.dest_cpp(), module.m_cpp);
			}

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

	string mudsrc  = "d:/Documents/Programmation/toy/mud/src";
	string muddist = "d:/Documents/Programmation/toy/mud/dist";
	string toysrc  = "d:/Documents/Programmation/toy/src";
	string toydist = "d:/Documents/Programmation/toy/dist";

	Amalgamator amalgamator;
	amalgamator.m_filter = filter;

	for(string module : { "infra", "jobs", "type", "tree", "pool", "refl", "ecs", "srlz", "math", "geom", "noise", "wfc", "fract", "lang", "ctx", "ui", "uio", "snd" })
		amalgamator.add(mudsrc, muddist, "mud", module, module);
	for(string module : { "ctx-glfw", "ctx-wasm", "ctx-win" })
		amalgamator.add(mudsrc, muddist, "mud", module, module);
	for(string module : { "ui-vg", "ui-nvg" })
		amalgamator.add(mudsrc, muddist, "mud", module, module);
	for(string module : { "bgfx", "gfx", "gltf", "gfx-pbr", "gfx-obj", "gfx-gltf", "gfx-ui", "gfx-edit", "tool", "wfc-gfx", "frame" })
		amalgamator.add(mudsrc, muddist, "mud", module, module);
	for(string module : { "util", "core", "visu", "block", "edit", "shell" })
		amalgamator.add(toysrc, toydist, "toy", module, module);

	//amalgamator.run(true);
	amalgamator.run(false);

	return 0;
}
