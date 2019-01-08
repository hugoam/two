#include <clrefl/Generator.h>
#include <clrefl/Codegen.h>

namespace mud
{
	CLMember::CLMember(CLClass& parent, CXCursor cursor)
		: m_parent(parent)
	{
		CXType member_type = type(cursor);
		if(cursor.kind == CXCursor_CXXMethod)
		{
			m_function = make_unique<CLMethod>(parent, cursor);
			member_type = result_type(cursor);
		}

		m_clsname = parent.fix_template(class_name(member_type, parent.m_is_template || parent.m_is_templated));
		m_type = parent.fix_template(type_name(member_type, parent.m_is_template || parent.m_is_templated));

		m_member = spelling(cursor);
		m_name = replace(spelling(cursor), "m_", "");
		m_capname = char(toupper(m_name[0])) + m_name.substr(1, string::npos);

		m_pointer = m_type.back() == '*';
		m_reference = m_type.back() == '&' && m_type.find("const") != string::npos;

		m_annotations = get_annotations(cursor);
		m_nonmutable = has<string>(m_annotations, "nonmutable_attr");
		m_structure = has<string>(m_annotations, "structure_attr");
		m_link = has<string>(m_annotations, "link_attr");
		//m_component = has<string>(m_annotations, "component");

		if(!parent.m_is_template)
			m_cls = m_parent.m_module->get_type(parent, m_clsname);

		m_setter = !m_nonmutable && m_function;

		visit_children(cursor, [&](CXCursor c) {
			if((c.kind == CXCursor_CXXMethod && spelling(c) == "set" + m_capname))
				m_setter = true;
		});

#if 0
		#print "Member", m_name, m_type
        
		find_default_value(m_cls, cursor)
#endif
	}


	CLParam::CLParam(CLFunction& func, CXCursor cursor, size_t index, CLPrimitive& parent)
		: m_func(&func)
		, m_index(index)
	{
		m_name = spelling(cursor);
		m_type = type_name(type(cursor), parent.m_is_template || parent.m_is_templated);
		m_clsname = class_name(type(cursor), parent.m_is_template || parent.m_is_templated);

		m_type = parent.fix_template(m_type);
		m_clsname = parent.fix_template(m_clsname);
        
		m_pointer = m_type.back() == '*';
		m_reference = m_type.back() == '&' && m_type.find("const") == string::npos;
		m_const_pointer = m_type.substr(0, 5) == "const" && m_type.back() == '*';
		m_const_reference = m_type.substr(0, 5) == "const" && m_type.back() == '&';
        
		m_nullable = m_pointer || m_type == "mud::Ref";
		m_output = m_name.substr(0, 6) == "output";
		m_input = !m_output;
        
		m_has_default = false;
		m_default = "";
         
		//if(! parent || ! parent.is_template:
		if(!parent.m_is_template)
		{
			m_cls = m_func->m_module.get_type(parent, m_clsname);
				// fixing type because of FUCKING clang.....................
			m_type = m_cls->m_id;
			if(m_pointer)
				m_type = m_type + "*";
			if(m_reference)
				m_type = m_type + "&";
			if(m_const_pointer)
				m_type = "const" + m_type + "*";
			if(m_const_reference)
				m_type = "const " + m_type + "&";
		}

		//find_default_value(m_cls, cursor)
	}

	CLFunction::CLFunction(CLModule& module, CXCursor cursor, CLPrimitive& parent)
		: m_module(module)
		, m_parent(parent)
	{
		m_name = spelling(cursor);
		m_id = parent.m_prefix + m_name;
		m_idstr = replace(m_id, "::", "_");

		/*if(module.m_context.m_func_templates.find(m_name))
		{
			string dname = displayname(cursor);
			string template_type = clean_name(split(dname.substr(dname.find("(") + 1), ",")[0])
			print "Templated Function", template_type
			m_name += "<" + template_type + ">"
			m_id += "<" + template_type + ">"
			m_idstr += "_" + template_type
		 }*/

		m_returnType = type_name(result_type(cursor));
		m_returnPointer = m_returnType.back() == '*';
		m_returnClsName = class_name(result_type(cursor));
		m_unqualReturnType = unqual_type_name(result_type(cursor));
		m_is_function = cursor.kind == CXCursor_FunctionDecl;
		m_is_template = cursor.kind == CXCursor_FunctionTemplate || (parent.m_is_template);

		if(!m_is_template)
		{
			visit_children(cursor, [&](CXCursor a) {
				if(a.kind == CXCursor_ParmDecl)
					m_params.push_back(CLParam(*this, a, m_params.size(), parent));
			});

			m_returnCls = m_module.get_type(parent, m_returnClsName);
		}
	}

	CLMethod::CLMethod(CLType& parent, CXCursor cursor)
		: CLFunction(*parent.m_module, cursor, parent)
	{
		m_expected_params = m_params;
	}

	CLClass::CLClass(CLModule& module, CXCursor cursor, CLPrimitive& parent)
		: CLType(module, clean_name(displayname(cursor)), parent, cursor.kind == CXCursor_ClassTemplate)
	{
		m_idstr = replace(replace(m_name, "<", ""), ">", "");

		m_annotations = get_annotations(cursor);

		m_struct = has<string>(m_annotations, "struct") || cursor.kind == CXCursor_StructDecl;
		m_reflect = has<string>(m_annotations, "reflect");
		m_extern = has<string>(m_annotations, "external");

		m_template_name = template_name(m_name);
		m_is_templated = m_name.find("<") != string::npos && !m_is_template;
		m_template = m_is_templated ? module.m_context.m_class_templates[m_template_name] : nullptr;
		m_template_types = template_types(m_name);

		//#if(m_is_templated && is_template_decl(cursor):
		//#    m_template.template_used = true
	}

	void CLClass::parse_contents(CXCursor cursor)
	{
		printf("Parsing %s\n", m_id.c_str());
		m_cursor = cursor;

		if(m_is_templated && is_template_decl(cursor))
			cursor = m_template->m_cursor;

		visit_children(cursor, [&](CXCursor c) {
			this->parse_child(c);
		});

		if(has<string>(m_annotations, "array_object"))
		{
			m_array = true;
			m_array_size = m_members.size();
			m_array_type = m_members[0].m_cls;
		}
	}

	void CLClass::parse_child(CXCursor cursor)
	{
		std::vector<string> annotations = get_annotations(cursor);

		if(cursor.kind == CXCursor_TemplateTypeParameter)
			m_template_types.push_back(spelling(cursor));

		if(cursor.kind == CXCursor_CXXBaseSpecifier)
		{
			string name = class_name(type(cursor));

			if(name.find("<") != string::npos)
				name = this->fix_template(name);

			//else if(name == "mud::Complex")
			//	m_isModular = true;
			//else if(name == "mud::Construct")
			//	m_isProto = true;

			if(name == "array<T>")
				int i = 0;

			CLType* base = m_module->get_type(*m_parent, name, false);
			if(base && base->m_reflect)
			{
				m_bases.push_back(base);
				m_deep_bases.push_back(base);
				vector_extend(m_deep_bases, base->m_bases);
			}
		}

		else if(cursor.kind == CXCursor_Constructor)
		{
			if(has<string>(annotations, "constructor"))
				m_constructors.push_back(CLConstructor(*this, cursor));
		}
		else if(cursor.kind == CXCursor_CXXMethod)
		{
			if(has<string>(annotations, "attribute"))
				m_members.push_back(CLMember(*this, cursor));
			if(has<string>(annotations, "method"))
				m_methods.push_back(CLMethod(*this, cursor));
		}
		else if(cursor.kind == CXCursor_FieldDecl)
		{
			if(has<string>(annotations, "attribute"))
				m_members.push_back(CLMember(*this, cursor));
			//if(has("component", annotations))
			//{
			//	m = Member(cursor);
			//	m_parts.push_back(m.cls);
			//}
		}
		else if(cursor.kind == CXCursor_VarDecl)
		{
			if(has<string>(annotations, "attribute"))
				m_statics.push_back(CLStatic(*this, cursor));
		}
		else if(cursor.kind == CXCursor_UnionDecl
			|| cursor.kind == CXCursor_StructDecl)
		{
			visit_children(cursor, [&](CXCursor c) {
				this->parse_child(c);
			});
		}
	}
	void register_classes(CXCursor cursor, const string& file, CLModule& module, CLPrimitive& parent)
	{
		visit_children(cursor, [&](CXCursor c)
		{
			bool visit = true; // os.path.normpath(c.location.file.name).find(os.path.normpath(module.path)) == 0 && c.location.file.name.find("Generated") == string::npos
			if(visit)
			{
				std::vector<string> annotations = get_annotations(c);

				if(c.kind == CXCursor_Namespace)
				{
					CLNamespace& ns = module.get_namespace(spelling(c), parent);
					register_classes(c, file, module, ns);
				}
				else if(is_definition(c))
				{
					if(!has<string>(annotations, "reflect")) return;

					if(c.kind == CXCursor_ClassDecl || c.kind == CXCursor_StructDecl)
					{
						CLClass& cl = module.class_type(c, parent);
						register_classes(c, file, module, cl);
					}
					else if(c.kind == CXCursor_ClassTemplate)
					{
						CLClass& cl = module.class_template(c, parent);
						register_classes(c, file, module, cl);
					}
					else if(c.kind == CXCursor_EnumDecl)
					{
						module.enum_type(c, parent);
					}
				}
			}
		});
	}

	void build_classes(CXCursor cursor, const string& file, CLModule& module, CLPrimitive& parent)
	{
		visit_children(cursor, [&](CXCursor c)
		{
			bool visit = true; // os.path.normpath(c.location.file.name).find(os.path.normpath(module.path)) == 0 && c.location.file.name.find("Generated") == string::npos
			if(visit)
			{
				std::vector<string> annotations = get_annotations(c);

				if(c.kind == CXCursor_Namespace)
				{
					CLNamespace ns = module.get_namespace(spelling(c), parent);
					build_classes(c, file, module, ns);
				}
				else if(is_definition(c))
				{
					if(has<string>(annotations, "reflect"))
					{
						if(c.kind == CXCursor_ClassDecl || c.kind == CXCursor_StructDecl) // || displayname(c).find("<") != string::npos
						{
							CLClass& cls = module.get_class(parent.m_prefix + clean_name(displayname(c)));
							cls.parse_contents(c);
							build_classes(c, file, module, cls);
						}
						else if(c.kind == CXCursor_ClassTemplate)
						{
							CLClass& cls = module.get_class_template(template_name(displayname(c)));
							cls.parse_contents(c);
						}
					}
				}
				else if(c.kind == CXCursor_FunctionDecl && has<string>(annotations, "function"))
				{
					module.function(c, parent);
				}
				else if(c.kind == CXCursor_FunctionTemplate && has<string>(annotations, "function"))
				{
					module.function_template(c, parent);
				}
			}
		});
	}

	class CLGenerator
	{
	public:
		CLGenerator() {}

		std::vector<unique_ptr<CLModule>> m_modules = {};
		std::vector<CLModule*> m_generator_queue = {};
		CLContext m_context;
	
		CLModule& module(const string& id)
		{
			for(auto& module : m_modules)
				if(id == module->m_id)
					return *module;
		}

		void parse_through(CLModule& module, std::function<void(CXCursor, const string&, CLModule&, CLPrimitive&)> func)
		{
			printf("Module path : %s\n", module.m_path.c_str());

			// the code generator can deal with the problem of the includes in two ways :
			//   - forward-declare everything that can be && skip all the includes
			//   - parse all the includes, which means also all the includes of the dependencies which then need to be passed to this generator

			// for now we are doing a hybrid approach, just skipping the includes of the external dependencies by wrapping them in a ifdef MUD_GENERATOR_SKIP_INCLUDES block

			bool debug_diagnostic = true;

			std::vector<string> compiler_args = {
				"-x",
				"c++",
				"-std=c++14",
				"-fdelayed-template-parsing",
				"-fms-compatibility",
				"-fms-extensions",
				"-fmsc-version=1900",
				"-Wmicrosoft",
				"-Drefl_=__attribute__((annotate(\"reflect\")))",
				"-Dstruct_=__attribute__((annotate(\"struct\")))",
				"-Dextern_=__attribute__((annotate(\"external\")))",
				"-Dserial_=__attribute__((annotate(\"serialize\")))",
				"-Darray_=__attribute__((annotate(\"array_object\")))",
				"-Dcomp_=__attribute__((annotate(\"component\")))",
				"-Dconstr_=__attribute__((annotate(\"constructor\")))",
				"-Dmeth_=__attribute__((annotate(\"method\")))",
				"-Dfunc_=__attribute__((annotate(\"function\")))",
				"-Dattr_=__attribute__((annotate(\"attribute\")))",
				"-Dnomut_=__attribute__((annotate(\"nonmutable_attr\")))",
				"-Dgraph_=__attribute__((annotate(\"structure_attr\")))",
				"-Dlink_=__attribute__((annotate(\"link_attr\")))",
				"-DMUD_META_GENERATOR"
				//"-DMUD_GENERATOR_SKIP_INCLUDES"
			};

			for(string dir : module.m_includedirs)
				compiler_args.push_back("-I" + dir);

			for(CLModule* m : module.m_modules)
				compiler_args.push_back("-I" + m->m_rootdir);

#if 0
			printf("Parsing with compiler args: \n");
			for(string arg : compiler_args)
				printf("%s\n", arg.c_str());
#endif

			auto parse_file = [&](const string& path, const string& file, const std::vector<cstring>& compiler_args, bool debug = false)
			{
				string fullpath = path + "\\" + file;
				CXIndex index = clang_createIndex(0, 0);

				printf("Parsing %s\n", file.c_str());

				// only for debugging : these two ways of parsing don"t give the correct output, but can give more diagnostics as to what might be wrong
				// options = 0;
				// options = CXTranslationUnit_SkipFunctionBodies;

				int options = CXTranslationUnit_SkipFunctionBodies | CXTranslationUnit_Incomplete;
				CXTranslationUnit translation_unit = clang_parseTranslationUnit(index, fullpath.c_str(), compiler_args.data(), int(compiler_args.size()), nullptr, 0, options);

				if(debug)
				{
					size_t num_diagnostics = clang_getNumDiagnostics(translation_unit);
					for(size_t i = 0; i < num_diagnostics; ++i)
					{
						CXDiagnostic diagnostic = clang_getDiagnostic(translation_unit, i);
						CXDiagnosticSeverity severity = clang_getDiagnosticSeverity(diagnostic);
						CXSourceLocation location = clang_getDiagnosticLocation(diagnostic);

						CXString filename;
						unsigned int line;
						unsigned int column;

						clang_getPresumedLocation(location, &filename, &line, &column);

						printf("severity: %i, ", int(severity));
						printf("location: %s (%i, %i), ", clang_getCString(filename), line, column);
						printf("%s\n", clang_getCString(clang_getDiagnosticSpelling(diagnostic)));
						//print diag.option

						clang_disposeString(filename);
					}
				}

				func(cursor(translation_unit), fullpath, module, module.m_context.m_root_namespace);
			};

			std::vector<cstring> compiler_cargs;
			for(const string& arg : compiler_args)
				compiler_cargs.push_back(arg.c_str());

			parse_file(module.m_path, "Api.h", compiler_cargs, debug_diagnostic);
		}

		void generate_module(CLModule& module)
		{
			if(!file_exists((module.m_path + "\\" + "Types.h").c_str()))
			{
				//with open(os.path.join(module.path, "Types.h"), "w") as f :
				//	pass
			}

			this->parse_through(module, register_classes);
        
			printf("NUM CLASSES : %i\n", int(module.m_classes.size()));
			//this->render_mako(module, "Forward.h", false)
        
			this->parse_through(module, build_classes);
        
			auto cmp_types = [](CLType& first, CLType& other)
			{
				// negative means self before other, positive means self after other
				int bases = 0;// cmp(first.deep_bases, other.deep_bases)
				if(false)
					;
				else if(other.m_deep_bases.size() > 0 && first.m_deep_bases.size() == 0)
					return -1;
				else if(first.m_deep_bases.size() > 0 && other.m_deep_bases.size() == 0)
					return 1;
				else if(other.m_deep_bases.size() > 0 && first.m_deep_bases.size() > 0 && bases != 0)
					return bases;
				else if(has(other.m_deep_bases, &first))
					return -1;
				else if(has(first.m_deep_bases, &other))
					return 1;
				else
					return strcmp(first.m_name.c_str(), other.m_name.c_str());
			};

			sort(module.m_types, [&](CLType* a, CLType* b) { return cmp_types(*a, *b); });

			sort(module.m_classes, [&](const unique_ptr<CLClass>& a, const unique_ptr<CLClass>& b) { return cmp_types(*a, *b); });
			sort(module.m_enums, [&](const unique_ptr<CLEnum>& a, const unique_ptr<CLEnum>& b) { return cmp_types(*a, *b); });
			sort(module.m_sequences, [&](const unique_ptr<CLSequence>& a, const unique_ptr<CLSequence>& b) { return cmp_types(*a, *b); });
			sort(module.m_basetypes, [&](const unique_ptr<CLBaseType>& a, const unique_ptr<CLBaseType>& b) { return cmp_types(*a, *b); });
            
			if(module.m_classes.size() == 0 && module.m_enums.size() == 0)
				return;

			if(!directory_exists(module.m_refl_path.c_str()))
				create_file_tree(module.m_refl_path.c_str());
            
			printf("Generating output templates :");

			string types_h = clgen::types_h_template(module);
			write_file((module.m_path + "\\" + "Types.h").c_str(), types_h.c_str());

			string types_cpp = clgen::types_cpp_template(module);
			write_file((module.m_path + "\\" + "Types.cpp").c_str(), types_cpp.c_str());

			string meta_h = clgen::meta_h_template(module);
			write_file((module.m_refl_path + "\\" + "Meta.h").c_str(), meta_h.c_str());

			string module_h = clgen::module_h_template(module);
			write_file((module.m_refl_path + "\\" + "Module.h").c_str(), module_h.c_str());

			string module_cpp = clgen::module_cpp_template(module);
			write_file((module.m_refl_path + "\\" + "Module.cpp").c_str(), module_cpp.c_str());

			//string convert_h = clgen::convert_h_template(module);
			//write_file((module.m_refl_path + "\\" + "Convert.h").c_str(), convert_h.c_str());
		}

		void add_module(const Json& m)
		{
			std::vector<CLModule*> dependencies = {};
			for(const Json& dep : m["dependencies"].array_items())
			{
				dependencies.push_back(&this->module(dep.string_value()));
			}

			std::vector<string> includedirs = {};
			for(const Json& inc : m["dependencies"].array_items())
			{
				includedirs.push_back(inc.string_value());
			}

			CLModule& module = vector_emplace<CLModule>(m_modules, m_context, m["namespace"].string_value(), m["name"].string_value(), m["dotname"].string_value(), m["idname"].string_value(),
																   m["root"].string_value(), m["subdir"].string_value(), m["path"].string_value(), includedirs, dependencies);
			m_generator_queue.push_back(&module);

			for(const Json& ty : m["basetypes"].array_items())
				module.base_type(ty.string_value(), m_context.m_root_namespace);

			for(const auto& key_value : m["aliases"].object_items())
				m_context.m_types[key_value.first] = m_context.m_types[key_value.second.string_value()];
		}

		void generate_all_modules()
		{
			for(CLModule* module : m_generator_queue )
				this->generate_module(*module);
		}
	};

}

using namespace mud;

int main(int argc, char *argv[])
{
	string args = "d:/Documents/Programmation/toy/build/refl/mud_infra_refl.json d:/Documents/Programmation/toy/build/refl/mud_jobs_refl.json d:/Documents/Programmation/toy/build/refl/mud_type_refl.json d:/Documents/Programmation/toy/build/refl/mud_tree_refl.json d:/Documents/Programmation/toy/build/refl/mud_pool_refl.json d:/Documents/Programmation/toy/build/refl/mud_refl_refl.json d:/Documents/Programmation/toy/build/refl/mud_ecs_refl.json d:/Documents/Programmation/toy/build/refl/mud_srlz_refl.json d:/Documents/Programmation/toy/build/refl/mud_math_refl.json d:/Documents/Programmation/toy/build/refl/mud_geom_refl.json d:/Documents/Programmation/toy/build/refl/mud_noise_refl.json d:/Documents/Programmation/toy/build/refl/mud_wfc_refl.json d:/Documents/Programmation/toy/build/refl/mud_fract_refl.json d:/Documents/Programmation/toy/build/refl/mud_lang_refl.json d:/Documents/Programmation/toy/build/refl/mud_ctx_refl.json d:/Documents/Programmation/toy/build/refl/mud_ui_refl.json d:/Documents/Programmation/toy/build/refl/mud_uio_refl.json d:/Documents/Programmation/toy/build/refl/mud_snd_refl.json d:/Documents/Programmation/toy/build/refl/mud_clrefl_refl.json d:/Documents/Programmation/toy/build/refl/mud_ctx_glfw_refl.json d:/Documents/Programmation/toy/build/refl/mud_ui_vg_refl.json d:/Documents/Programmation/toy/build/refl/mud_ui_nanovg_refl.json d:/Documents/Programmation/toy/build/refl/mud_ui_nanovg_bgfx_refl.json d:/Documents/Programmation/toy/build/refl/mud_bgfx_refl.json d:/Documents/Programmation/toy/build/refl/mud_gfx_refl.json d:/Documents/Programmation/toy/build/refl/mud_gfx_pbr_refl.json d:/Documents/Programmation/toy/build/refl/mud_gfx_obj_refl.json d:/Documents/Programmation/toy/build/refl/mud_gfx_gltf_refl.json d:/Documents/Programmation/toy/build/refl/mud_gfx_ui_refl.json d:/Documents/Programmation/toy/build/refl/mud_gfx_edit_refl.json d:/Documents/Programmation/toy/build/refl/mud_tool_refl.json d:/Documents/Programmation/toy/build/refl/mud_wfc_gfx_refl.json d:/Documents/Programmation/toy/build/refl/mud_core_refl.json d:/Documents/Programmation/toy/build/refl/toy_util_refl.json d:/Documents/Programmation/toy/build/refl/toy_core_refl.json d:/Documents/Programmation/toy/build/refl/toy_visu_refl.json d:/Documents/Programmation/toy/build/refl/toy_edit_refl.json d:/Documents/Programmation/toy/build/refl/toy_block_refl.json d:/Documents/Programmation/toy/build/refl/toy_shell_refl.json d:/Documents/Programmation/toy/build/refl/_test_refl.json d:/Documents/Programmation/toy/build/refl/_minimal_refl.json d:/Documents/Programmation/toy/build/refl/_boids_refl.json d:/Documents/Programmation/toy/build/refl/_space_refl.json d:/Documents/Programmation/toy/build/refl/_platform_refl.json d:/Documents/Programmation/toy/build/refl/_blocks_refl.json d:/Documents/Programmation/toy/build/refl/_wren_refl.json d:/Documents/Programmation/toy/build/refl/_godot_refl.json";
	
	CLGenerator generator;

	std::vector<string> locations = split(args, " ");

	for(int i = 0; i < argc; ++i)
		locations.push_back(argv[i]);

	locations.resize(5);

	for(string loc : locations)
	{
		string errors;
		string text_module = read_text_file(loc);
		Json json_module = Json::parse(text_module, errors);
		generator.add_module(json_module);
	}

	generator.generate_all_modules();
	return 0;
}