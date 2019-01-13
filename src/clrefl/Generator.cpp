#include <clrefl/Generator.h>
#include <clrefl/Codegen.h>

#define PARSE_EXTERNAL 0

namespace mud
{
	void update_file(const string& path, const string& content)
	{
		string current = read_text_file(path.c_str());
		if(content != current)
			write_file(path.c_str(), content.c_str());
	}

	CLQualType qual_type(CLModule& module, CLPrimitive& parent, CXType type, bool real_type)
	{
		CLQualType qual;

		qual.m_spelling = parent.fix_template(type_name(type));
		qual.m_type_name = parent.fix_template(class_name(type));
		qual.m_unqual_type_name = parent.fix_template(unqual_type_name(type));

		if(real_type)
		{
			qual.m_type = module.get_type(parent, qual.m_type_name);
			// fixing type because of FUCKING clang.....................
			string spelling = qual.m_type->m_id;
			if(qual.pointer())   spelling = spelling + "*";
			if(qual.reference()) spelling = spelling + "&";
			if(qual.isconst())   spelling = "const " + spelling;
			qual.m_spelling = spelling;
		}

		return qual;
	}

	void parse_enum(CLModule& module, CLPrimitive& parent, CXCursor cursor)
	{
		CLEnum& e =	module.enum_type(parent, displayname(cursor));
		e.m_scoped = is_scoped(cursor);
		e.m_enum_type = spelling(enum_type(cursor));
		e.m_prefix = e.m_scoped ? e.m_id + "::" : parent.m_prefix;

		e.m_annotations = get_annotations(cursor);
		e.m_reflect = has<string>(e.m_annotations, "refl");

		visit_children(cursor, [&](CXCursor c)
		{
			if(c.kind == CXCursor_EnumConstantDecl)
			{
				e.m_ids.push_back(displayname(c));
				e.m_values.push_back(to_string(enum_value(c)));
				e.m_scoped_ids.push_back(e.m_prefix + displayname(c));
			}
		});
	}

	void find_default_value(CXCursor cursor, const string& type, bool& has_default, string& default_value)
	{
		visit_children(cursor, [&](CXCursor c)
		{
			if(c.kind == CXCursor_CXXBoolLiteralExpr || c.kind == CXCursor_FloatingLiteral || c.kind == CXCursor_IntegerLiteral || c.kind == CXCursor_StringLiteral)
			{
				has_default = true;
				default_value = first_token(c);
			}
			else if(c.kind == CXCursor_CallExpr || c.kind == CXCursor_DeclRefExpr || c.kind == CXCursor_UnexposedExpr)
			{
				has_default = true;
				visit_tokens(c, [&](CXToken t) {
					string token = spelling(c, t);
					if(ends_with(default_value + token, type)) default_value += token;
					else if(kind(t) == CXToken_Identifier && ends_with(type, token)) default_value += type;
					else if(token != "=") default_value += token;
				});
			}
		});
	}

	void parse_param(CLPrimitive& parent, CLFunction& func, CLParam& p, CXCursor cursor)
	{
		p.m_name = spelling(cursor);
		p.m_type = qual_type(*func.m_module, parent, type(cursor), !parent.m_is_template);

		p.m_output = p.m_name.substr(0, 6) == "output";

		if(p.m_type.m_type)
		{
			find_default_value(cursor, p.m_type.m_type->m_id, p.m_has_default, p.m_default);
			if(parent.m_is_templated)
				p.m_default = parent.fix_template(p.m_default);
		}
	}

	void parse_function(CLModule& module, CLPrimitive& parent, CLFunction& f, CXCursor cursor)
	{
		f.m_name = spelling(cursor);
		f.m_module = &module;

		if(has(module.m_context.m_func_templates, f.m_name))
		{
			string name = displayname(cursor);
			string template_type = clean_name(split(name.substr(name.find("(") + 1), ",")[0]);
			printf("Templated Function %s\n", template_type.c_str());
			f.m_name += "<" + template_type + ">";
			f.m_id += "<" + template_type + ">";
		}

		f.m_is_template = cursor.kind == CXCursor_FunctionTemplate || (parent.m_is_template);

		f.m_return_type = qual_type(module, parent, result_type(cursor), !f.m_is_template);

		if(!f.m_is_template)
		{
			visit_children(cursor, [&](CXCursor a)
			{
				if(a.kind == CXCursor_ParmDecl)
				{
					f.m_params.push_back(CLParam(f, f.m_params.size()));
					parse_param(parent, f, f.m_params.back(), a);
				}
			});
		}

		for(size_t i = 0; i < f.m_params.size(); ++i)
			if(!f.m_params[i].m_has_default)
				f.m_min_args = i+1;
	}

	void parse_function(CLModule& module, CLPrimitive& parent, CXCursor cursor)
	{
		//print "Function ", cursor.displayname
		CLFunction& func = vector_emplace<CLFunction>(module.m_functions, parent, spelling(cursor));
		parse_function(module, parent, func, cursor);
	}

	void parse_function_template(CLModule& module, CLPrimitive& parent, CXCursor cursor)
	{
		//print "Function Template ", cursor.displayname
		CLFunction& func = vector_emplace<CLFunction>(module.m_func_templates, parent, spelling(cursor));
		parse_function(module, parent, func, cursor);
		module.m_context.m_func_templates[func.m_name] = &func;
	}

	void parse_static(CLClass& c, CXCursor cursor)
	{
		CLStatic& s = vector_push(c.m_statics, c);
		s.m_member = spelling(cursor);
		s.m_name = replace(spelling(cursor), "m_", "");
	}

	void parse_constructor(CLClass& c, CXCursor cursor)
	{
		CLConstructor& ctor = vector_push(c.m_constructors, c, spelling(cursor));
		parse_function(*c.m_module, c, ctor, cursor);
		ctor.m_expected_params = ctor.m_params;
	}

	void parse_method(CLClass& c, CLMethod& m, CXCursor cursor)
	{
		parse_function(*c.m_module, c, m, cursor);
		m.m_expected_params = m.m_params;
		m.m_const = is_const_method(cursor);
	}

	void parse_method(CLClass& c, CXCursor cursor)
	{
		CLMethod& m = vector_push(c.m_methods, c, spelling(cursor));
		parse_method(c, m, cursor);
	}

	void parse_member(CLClass& c, CXCursor cursor)
	{
		CLMember& m = vector_push(c.m_members, c);
		CXType member_type = type(cursor);

		if(cursor.kind == CXCursor_CXXMethod)
		{
			m.m_method = make_unique<CLMethod>(c, spelling(cursor));
			parse_method(c, *m.m_method, cursor);
			member_type = result_type(cursor);
		}

		m.m_type = qual_type(*c.m_module, c, member_type, !c.m_is_template);

		m.m_member = spelling(cursor);
		m.m_name = replace(spelling(cursor), "m_", "");
		m.m_capname = char(toupper(m.m_name[0])) + m.m_name.substr(1, string::npos);

		m.m_annotations = get_annotations(cursor);
		m.m_nonmutable = has<string>(m.m_annotations, "nomut");
		m.m_structure = has<string>(m.m_annotations, "graph");
		m.m_link = has<string>(m.m_annotations, "link");
		m.m_component = has<string>(m.m_annotations, "comp");

		visit_children(cursor, [&](CXCursor s)
		{
			if((s.kind == CXCursor_CXXMethod && spelling(s) == "set" + m.m_capname || spelling(s) == "set_" + m.m_name))
			{
				m.m_setter = make_unique<CLMethod>(c, spelling(s));
				parse_method(c, *m.m_setter, s);
			}
		});

		if(m.m_type.m_type)
		{
			find_default_value(cursor, m.m_type.m_type->m_id, m.m_has_default, m.m_default);
			if(c.m_is_templated)
				m.m_default = c.fix_template(m.m_default);
		}
	}

	void parse_class(CLModule& module, CLPrimitive& parent, CLClass& c, CXCursor cursor)
	{
		c.m_name = clean_name(displayname(cursor));
		c.m_is_template = cursor.kind == CXCursor_ClassTemplate;

		c.m_annotations = get_annotations(cursor);

		c.m_struct = has<string>(c.m_annotations, "struct") || cursor.kind == CXCursor_StructDecl;
		c.m_move_only = has<string>(c.m_annotations, "nocopy");
		c.m_reflect = has<string>(c.m_annotations, "refl");
		c.m_extern = has<string>(c.m_annotations, "extern");

		c.m_is_templated = c.m_name.find("<") != string::npos && !c.m_is_template;
		if(c.m_is_template || c.m_is_templated)
		{
			c.m_template_types = template_types(c.m_name);
			c.m_template_name = template_name(c.m_name);
		}
		if(c.m_is_templated)
			c.m_template = module.m_context.m_class_templates[c.m_template_name];

		//#if(m_is_templated && is_template_decl(cursor):
		//#    m_template.template_used = true
	}

	CLClass& decl_class_type(CLModule& module, CLPrimitive& parent, CXCursor cursor)
	{
		CLClass& cls = vector_emplace<CLClass>(module.m_classes, module, parent, clean_name(displayname(cursor)));
		parse_class(module, parent, cls, cursor);
		module.register_type(cls);
		return cls;
	}

	CLClass& decl_class_template(CLModule& module, CLPrimitive& parent, CXCursor cursor)
	{
		CLClass& cls = vector_emplace<CLClass>(module.m_class_templates, module, parent, clean_name(displayname(cursor)));
		parse_class(module, parent, cls, cursor);
		module.register_type(cls);
		module.m_context.m_class_templates[cls.m_template_name] = &cls;
		return cls;
	}

	void parse_class_child(CLClass& c, CXCursor cursor)
	{
		std::vector<string> annotations = get_annotations(cursor);

		if(cursor.kind == CXCursor_TemplateTypeParameter)
			c.m_template_types.push_back(spelling(cursor));

		else if(cursor.kind == CXCursor_CXXBaseSpecifier)
		{
			string name = class_name(type(cursor));

			if(name.find("<") != string::npos)
				name = c.fix_template(name);

			//CLType* base = m_module->get_type(*m_parent, name, false);
			CLType* base = c.m_module->m_context.m_types[name];
			if(base && base->m_reflect)
			{
				c.m_bases.push_back(base);
				c.m_deep_bases.push_back(base);
				vector_extend(c.m_deep_bases, base->m_bases);
			}
		}

		else if(cursor.kind == CXCursor_Constructor && has<string>(annotations, "constr"))
			parse_constructor(c, cursor);
		else if(cursor.kind == CXCursor_CXXMethod && has<string>(annotations, "attr"))
			parse_member(c, cursor);
		else if(cursor.kind == CXCursor_CXXMethod && has<string>(annotations, "meth"))
			parse_method(c, cursor);
		else if(cursor.kind == CXCursor_FieldDecl && has<string>(annotations, "attr"))
			parse_member(c, cursor);
		else if(cursor.kind == CXCursor_VarDecl && has<string>(annotations, "attr"))
			parse_static(c, cursor);
		else if(cursor.kind == CXCursor_UnionDecl || cursor.kind == CXCursor_StructDecl)
		{
			visit_children(cursor, [&](CXCursor a) {
				parse_class_child(c, a);
			});
		}
	}

	void parse_class_contents(CLClass& c, CXCursor cursor)
	{
		printf("Parsing %s\n", c.m_id.c_str());
		c.m_cursor = cursor;

		if(c.m_is_templated) // && is_template_decl(cursor))
			cursor = c.m_template->m_cursor;

		visit_children(cursor, [&](CXCursor a) {
			parse_class_child(c, a);
		});

		if(has<string>(c.m_annotations, "array"))
		{
			c.m_array = true;
			c.m_array_size = c.m_members.size();
			c.m_array_type = c.m_members[0].m_type.m_type;
		}

		std::set<string> method_names;
		for(CLMethod& method : c.m_methods)
		{
			if(method_names.find(method.m_name) != method_names.end())
				method.m_overloaded = true;
			method_names.insert(method.m_name);
		}

		if(c.m_struct && c.m_constructors.empty())
		{
			CLConstructor& ctor = vector_push(c.m_constructors, c, c.m_name);
			ctor.m_module = c.m_module;
		}
	}

	bool should_visit(CXCursor cursor, CLModule& module)
	{
		auto fix_path = [](const string& path) { return replace(path, "\\", "/"); };
		string location = fix_path(file(cursor));
#if PARSE_EXTERNAL
		return module.m_context.m_parsed_files.find(location) == module.m_context.m_parsed_files.end();
#else
		return location.find(module.m_path) == 0 && location.find("meta") == string::npos;
#endif
	}

	void register_classes(CXCursor cursor, CLModule& module, CLPrimitive& parent)
	{
		visit_children(cursor, [&](CXCursor c)
		{
			if(should_visit(c, module))
			{
				std::vector<string> annotations = get_annotations(c);

				if(c.kind == CXCursor_Namespace)
				{
					CLNamespace& ns = module.get_namespace(spelling(c), parent);
					register_classes(c, module, ns);
				}
				else if(c.kind == CXCursor_UsingDeclaration)
				{
					// dump_ast(c);
				}
				else if(is_definition(c))
				{
					if(!has<string>(annotations, "refl")) return;

					if(c.kind == CXCursor_ClassDecl || c.kind == CXCursor_StructDecl)
					{
						CLClass& cl = decl_class_type(module, parent, c);
						register_classes(c, module, cl);
					}
					else if(c.kind == CXCursor_ClassTemplate)
					{
						CLClass& cl = decl_class_template(module, parent, c);
						register_classes(c, module, cl);
					}
					else if(c.kind == CXCursor_EnumDecl)
						parse_enum(module, parent, c);
				}
			}
		});
	}

	void build_classes(CXCursor cursor, CLModule& module, CLPrimitive& parent)
	{
		visit_children(cursor, [&](CXCursor c)
		{
			if(should_visit(c, module))
			{
				std::vector<string> annotations = get_annotations(c);

				if(c.kind == CXCursor_Namespace)
				{
					CLNamespace& ns = module.get_namespace(spelling(c), parent);
					build_classes(c, module, ns);
				}
				else if(is_definition(c))
				{
					if((c.kind == CXCursor_ClassDecl || c.kind == CXCursor_StructDecl) && has<string>(annotations, "refl"))
					{
						CLClass& cls = module.get_class(parent.m_prefix + clean_name(displayname(c)));
						parse_class_contents(cls, c);
						build_classes(c, module, cls);
					}
					else if(c.kind == CXCursor_ClassTemplate && has<string>(annotations, "refl"))
					{
						CLClass& cls = module.get_class_template(template_name(displayname(c)));
						parse_class_contents(cls, c);
					}
				}
				else if(c.kind == CXCursor_FunctionDecl && has<string>(annotations, "func"))
					parse_function(module, parent, c);
				else if(c.kind == CXCursor_FunctionTemplate && has<string>(annotations, "func"))
					parse_function_template(module, parent, c);
			}
		});
	}

	class CLGenerator
	{
	public:
		CLGenerator() : m_context() {}

		std::vector<unique_ptr<CLModule>> m_modules = {};
		std::vector<CLModule*> m_generator_queue = {};
		CLContext m_context;

		CLModule& module(const string& id)
		{
			for(auto& module : m_modules)
				if(id == module->m_id)
					return *module;
		}

		void parse_through(CLModule& module, std::function<void(CXCursor, CLModule&, CLPrimitive&)> func)
		{
			printf("Module path : %s\n", module.m_path.c_str());

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
				"-DMUD_META_GENERATOR",
			};

			for(string attr : { "refl", "struct", "nocopy", "extern", "array", "comp", "constr", "meth", "func", "attr", "nomut", "graph", "link" })
				compiler_args.push_back("-D" + attr + "_=__attribute__((annotate(\"" + attr + "\")))");

			for(string dir : module.m_includedirs)
				compiler_args.push_back("-I" + dir);

			for(CLModule* m : module.m_modules)
				compiler_args.push_back("-I" + m->m_rootdir);

#ifdef DEBUG_CLANG_ARGS
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
				// int options = 0;
				// int options = CXTranslationUnit_SkipFunctionBodies;

				//int options = CXTranslationUnit_SkipFunctionBodies | CXTranslationUnit_Incomplete;
				int options = CXTranslationUnit_SkipFunctionBodies | CXTranslationUnit_KeepGoing;
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
						printf("location: %s (%i, %i), ", clang_string(filename).c_str(), line, column);
						printf("%s\n", clang_string(clang_getDiagnosticSpelling(diagnostic)).c_str());
						//print diag.option

						clang_disposeString(filename);
					}
				}

				func(cursor(translation_unit), module, module.m_context.m_root_namespace);
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

			//string forward_h = clgen::forward_h_template(module);
			//update_file((module.m_path + "\\" + "Forward.h").c_str(), forward_h.c_str());

			this->parse_through(module, build_classes);
        
			auto cmp_types = [](CLType& a, CLType& b) -> int
			{
				// negative means a before b, positive means a after b
				int bases = 0;// cmp(first.deep_bases, other.deep_bases)
				if(false)
					;
				else if(b.m_deep_bases.size() > 0 && a.m_deep_bases.size() == 0)
					return -1;
				else if(a.m_deep_bases.size() > 0 && b.m_deep_bases.size() == 0)
					return 1;
				else if(b.m_deep_bases.size() > 0 && a.m_deep_bases.size() > 0 && bases != 0)
					return bases;
				else if(has(b.m_deep_bases, &a))
					return -1;
				else if(has(a.m_deep_bases, &b))
					return 1;
				else
					return a.m_name.compare(b.m_name);
			};

			sort(module.m_types, [&](CLType* a, CLType* b) { return cmp_types(*a, *b) < 0; });

			sort(module.m_classes, [&](const unique_ptr<CLClass>& a, const unique_ptr<CLClass>& b) { return cmp_types(*a, *b) < 0; });
			sort(module.m_enums, [&](const unique_ptr<CLEnum>& a, const unique_ptr<CLEnum>& b) { return cmp_types(*a, *b) < 0; });
			sort(module.m_sequences, [&](const unique_ptr<CLSequence>& a, const unique_ptr<CLSequence>& b) { return cmp_types(*a, *b) < 0; });
			sort(module.m_basetypes, [&](const unique_ptr<CLBaseType>& a, const unique_ptr<CLBaseType>& b) { return cmp_types(*a, *b) < 0; });
            
			//if(module.m_classes.size() == 0 && module.m_enums.size() == 0)
			//	return;

			if(!directory_exists(module.m_refl_path.c_str()))
				create_directory_tree(module.m_refl_path.c_str());
            
			printf("Generating meta reflection files for %s:\n", module.m_name.c_str());

			string types_h = clgen::types_h_template(module);
			update_file((module.m_path + "\\" + "Types.h").c_str(), types_h.c_str());

			string types_cpp = clgen::types_cpp_template(module);
			update_file((module.m_path + "\\" + "Types.cpp").c_str(), types_cpp.c_str());

			string meta_h = clgen::meta_h_template(module);
			update_file((module.m_refl_path + "\\" + "Meta.h").c_str(), meta_h.c_str());

			string module_h = clgen::module_h_template(module);
			update_file((module.m_refl_path + "\\" + "Module.h").c_str(), module_h.c_str());

			string module_cpp = clgen::module_cpp_template(module);
			update_file((module.m_refl_path + "\\" + "Module.cpp").c_str(), module_cpp.c_str());

			string convert_h = clgen::convert_h_template(module);
			update_file((module.m_refl_path + "\\" + "Convert.h").c_str(), convert_h.c_str());

			printf("Generating bindings files for %s:\n", module.m_name.c_str());

			if(!directory_exists(module.m_bind_path.c_str()))
				create_directory_tree(module.m_bind_path.c_str());

			//string embind_cpp = clgen::bind_embind_h_template(module);
			//update_file((module.m_bind_path + "\\" + "Embind.cpp").c_str(), embind_cpp.c_str());

			//string module_idl = clgen::bind_webidl_h_template(module);
			//update_file((module.m_bind_path + "\\" + "Module.idl").c_str(), module_idl.c_str());

			clgen::bind_javascript(module);
		}

		void add_module(const Json& m)
		{
			std::vector<CLModule*> dependencies = {};
			for(const Json& dep : m["dependencies"].array_items())
			{
				dependencies.push_back(&this->module(dep.string_value()));
			}

			std::vector<string> includedirs = {};
			for(const Json& inc : m["includedirs"].array_items())
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

		void generate_module(const string& id)
		{
			CLModule& module = this->module(id);
			this->generate_module(module);
		}

		void generate_all_modules()
		{
			for(CLModule* module : m_generator_queue)
				this->generate_module(*module);
		}
	};

}

using namespace mud;

int main(int argc, char *argv[])
{
	string args = "d:/Documents/Programmation/toy/build/refl/mud_infra_refl.json d:/Documents/Programmation/toy/build/refl/mud_jobs_refl.json d:/Documents/Programmation/toy/build/refl/mud_type_refl.json d:/Documents/Programmation/toy/build/refl/mud_tree_refl.json d:/Documents/Programmation/toy/build/refl/mud_pool_refl.json d:/Documents/Programmation/toy/build/refl/mud_refl_refl.json d:/Documents/Programmation/toy/build/refl/mud_ecs_refl.json d:/Documents/Programmation/toy/build/refl/mud_srlz_refl.json d:/Documents/Programmation/toy/build/refl/mud_math_refl.json d:/Documents/Programmation/toy/build/refl/mud_geom_refl.json d:/Documents/Programmation/toy/build/refl/mud_noise_refl.json d:/Documents/Programmation/toy/build/refl/mud_wfc_refl.json d:/Documents/Programmation/toy/build/refl/mud_fract_refl.json d:/Documents/Programmation/toy/build/refl/mud_lang_refl.json d:/Documents/Programmation/toy/build/refl/mud_ctx_refl.json d:/Documents/Programmation/toy/build/refl/mud_ui_refl.json d:/Documents/Programmation/toy/build/refl/mud_uio_refl.json d:/Documents/Programmation/toy/build/refl/mud_snd_refl.json d:/Documents/Programmation/toy/build/refl/mud_bgfx_refl.json d:/Documents/Programmation/toy/build/refl/mud_gfx_refl.json d:/Documents/Programmation/toy/build/refl/mud_gltf_refl.json d:/Documents/Programmation/toy/build/refl/mud_gfx_pbr_refl.json d:/Documents/Programmation/toy/build/refl/mud_gfx_obj_refl.json d:/Documents/Programmation/toy/build/refl/mud_gfx_gltf_refl.json d:/Documents/Programmation/toy/build/refl/mud_gfx_ui_refl.json d:/Documents/Programmation/toy/build/refl/mud_gfx_edit_refl.json d:/Documents/Programmation/toy/build/refl/mud_tool_refl.json d:/Documents/Programmation/toy/build/refl/mud_wfc_gfx_refl.json d:/Documents/Programmation/toy/build/refl/toy_util_refl.json d:/Documents/Programmation/toy/build/refl/toy_core_refl.json d:/Documents/Programmation/toy/build/refl/toy_visu_refl.json d:/Documents/Programmation/toy/build/refl/toy_edit_refl.json d:/Documents/Programmation/toy/build/refl/toy_block_refl.json d:/Documents/Programmation/toy/build/refl/toy_shell_refl.json d:/Documents/Programmation/toy/build/refl/_test_refl.json d:/Documents/Programmation/toy/build/refl/_minimal_refl.json d:/Documents/Programmation/toy/build/refl/_boids_refl.json d:/Documents/Programmation/toy/build/refl/_space_refl.json d:/Documents/Programmation/toy/build/refl/_platform_refl.json d:/Documents/Programmation/toy/build/refl/_blocks_refl.json d:/Documents/Programmation/toy/build/refl/_wren_refl.json d:/Documents/Programmation/toy/build/refl/_godot_refl.json";
	
	CLGenerator generator;

	std::vector<string> locations = split(args, " ");

	for(int i = 1; i < argc; ++i)
		locations.push_back(argv[i]);

	for(string loc : locations)
	{
		string errors;
		string text_module = read_text_file(loc);
		Json json_module = Json::parse(text_module, errors);
		generator.add_module(json_module);
	}

	//generator.generate_module("mud_geom");
	//generator.generate_module("mud_gfx");
	generator.generate_all_modules();
	return 0;
}