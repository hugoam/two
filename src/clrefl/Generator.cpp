#include <infra/Cpp20.h>
#include <clang-c/Index.h>
#include <cctype>
#include <cstdio>

#if defined _MSC_VER
import <string>;
import <map>;
#else
import std;
#endif
import two.clrefl;

#include <clrefl/Generator.h>
#include <clrefl/Codegen.h>

#define RESOLVE_TEMPLATES 1

#define DEBUG_CLANG_ARGS 0

namespace two
{
	using Json = json11::Json;

	// the standard headers a module importing the std module gets: the ones imported by the MSVC interfaces (.ixx), and atomic,
	// which the MSVC standard library includes with memory
	const char* c_std_headers[] = {
		"algorithm", "atomic", "cmath", "fstream", "functional", "initializer_list", "map", "memory", "mutex", "random",
		"regex", "set", "string", "thread", "tuple", "unordered_map", "unordered_set", "vector",
	};

	struct TopoSort
	{
		vector<vector<size_t>> links;
		vector<bool> perm_marks;
		vector<bool> temp_marks;
		vector<size_t> order;
		vector<size_t> sorted;
	};

	auto visit_sort_topological(TopoSort& sort, size_t n) //, T& elem)
	{
		if(sort.perm_marks[n]) return;
		if(sort.temp_marks[n]) return;
		sort.temp_marks[n] = true;
        
		for (size_t c : sort.links[n])
		{
			visit_sort_topological(sort, c);
		}
        
		sort.perm_marks[n] = true;
		sort.order[n] = sort.sorted.size();
		sort.sorted.push_back(n);
	};
    
	TopoSort sort_topological(vector<vector<size_t>> links)
	{
		TopoSort sort;
		sort.links = links;
		sort.perm_marks.resize(links.size(), false);
		sort.temp_marks.resize(links.size(), false);
		sort.order.resize(links.size());

		for(size_t n = 0; n < links.size(); ++n)
		{
			visit_sort_topological(sort, n);
		}

		return sort;
	}

	void sort_classes(vector<unique<CLClass>>& classes)
	{
		for(size_t n = 0; n < classes.size(); ++n)
		{
			classes[n]->m_index = n;
		}

		vector<vector<size_t>> links;
		links.resize(classes.size());

		for(size_t n = 0; n < classes.size(); ++n)
		{
			CLClass& item = *classes[n];
			for(CLClass* base : item.m_deep_bases)
			{
				if(base == &*classes[base->m_index])
					links[n].push_back(base->m_index);
			}
		}

		const TopoSort sort = sort_topological(links);

		stable_sort(classes, [&](const unique<CLClass>& a, const unique<CLClass>& b) { return sort.order[a->m_index] < sort.order[b->m_index]; });
	}

	const CLType& element_type(const CLType& t)
	{
		if(t.m_type_kind == CLTypeKind::Alias)
			return element_type(*((CLAlias&)t).m_target);
		if(t.m_type_kind == CLTypeKind::Class)
		{
			const CLClass& c = (CLClass&)t;
			if(c.m_sequence) return *c.m_element_type;
			else if(c.m_array) return *c.m_array_type;
		}
		return t;
	}

	const CLType& reduce_element(const CLType& t)
	{
		if(t.m_type_kind == CLTypeKind::Alias)
			return reduce_element(*((CLAlias&)t).m_target);
		if(t.m_type_kind == CLTypeKind::Class)
		{
			const CLClass& c = (CLClass&)t;
			if(c.m_sequence) return reduce_element(*c.m_element_type);
			else if(c.m_array) return reduce_element(*c.m_array_type);
		}
		return t;
	}

	bool should_visit(CXCursor cursor, CLModule& module)
	{
		auto fix_path = [](const string& path) { return replace(path, "\\", "/"); };
		string location = fix_path(file(cursor));
		return module.m_parsed_files.find(location) == module.m_parsed_files.end();
	}

	bool should_reflect(CXCursor cursor, CLModule& module)
	{
		auto fix_path = [](const string& path) { return replace(path, "\\", "/"); };
		string location = fix_path(file(cursor));
		// trailing separator, otherwise e.g. module gfx would also reflect the files of gfx-pbr
		return location.find(module.m_path + "/") == 0 && location.find("meta") == string::npos;
	}

	CLQualType qual_type(CLModule& module, const CLPrimitive& parent, CXType type, bool real_type)
	{
		//if(upointee(type).kind == CXType_Unexposed && !parent.m_is_templated)
		//	type = canonical(type);
		bool templated = parent.m_is_templated && upointee(type).kind == CXType_Unexposed;

		CLQualType t;
		auto fix = [&](const string& name) { return templated ? parent.fix_template(name) : name; };
		t.m_spelling = fix(spelling(type));
		t.m_type_name = fix(spelling(class_type(type, !templated)));
		t.m_array = type.kind == CXType_ConstantArray;
		if(!real_type) return t;

		t.m_type = templated ? module.get_type(type, t.m_type_name) : module.get_type(type);

		// fixing type names because of spellings from libclang are not always fully qualified (mostly namespaces)
		t.m_spelling = (t.isconst() ? "const " : "") + t.m_type->m_id + (t.pointer() ? "*" : "") + (t.reference() ? "&" : "");
		t.m_type_name = t.m_type->m_id;

		// substitute real aliased type only after fixing the spellings, so we see the alias types in reflection/bindings code
		if(t.m_type->m_type_kind == CLTypeKind::Alias)
			t.m_type = ((CLAlias*)t.m_type)->m_target;
		if(t.m_type->m_type_kind == CLTypeKind::Class)
			t.m_class = (CLClass*)t.m_type;

		return t;
	}

	void decl_enum(CLModule& module, CLPrimitive& parent, CXCursor cursor)
	{
		CLEnum& e = vector_emplace<CLEnum>(module.m_enums, module, parent, type(cursor));
		module.register_type(e);

		e.m_cursor = cursor;
		e.m_annotations = get_annotations(e.m_cursor);
		e.m_reflect = has(e.m_annotations, "refl") && should_reflect(cursor, module);

		module.m_has_reflected |= e.m_reflect;
	}

	void decl_callable(CLModule& module, CLPrimitive& parent, CLCallable& f, CXCursor cursor)
	{
		f.m_name = spelling(cursor);
		f.m_cursor = cursor;
		f.m_module = &module;
		f.m_reflect = should_reflect(cursor, module);

		const int template_args = clang_Cursor_getNumTemplateArguments(cursor);
		if(cursor.kind == CXCursor_FunctionDecl	&& template_args > 0)
		{
			vector<string> types;
			for(int i = 0; i < template_args; ++i)
			{
				CXType t = clang_Cursor_getTemplateArgumentType(cursor, i);
				types.push_back(module.alias_spelling(t));
				//f.m_templated_types.push_back(find_type(t));
			}

			f.m_name += "<" + comma(types) + ">";
			f.m_id += "<" + comma(types) + ">";
		}

		f.m_is_template = cursor.kind == CXCursor_FunctionTemplate || (parent.m_is_template);

		parent.m_reflect_content |= f.m_reflect;
		module.m_has_reflected |= f.m_reflect;
	}

	void decl_function(CLModule& module, CLPrimitive& parent, CXCursor cursor)
	{
		//print "Function ", cursor.displayname
		CLFunction& f = vector_emplace<CLFunction>(module.m_functions, parent, spelling(cursor));
		decl_callable(module, parent, f, cursor);
		f.m_index = module.m_functions.size() - 1;
	}

	// @todo cleanup this isn't really used, we declare specializations directly
	void decl_function_template(CLModule& module, CLPrimitive& parent, CXCursor cursor)
	{
		//printf("Function Template %s %s\n", displayname(cursor).c_str(), spelling(cursor).c_str());
		CLFunction& f = vector_emplace<CLFunction>(module.m_func_templates, parent, spelling(cursor));
		f.m_is_template = true;
		decl_callable(module, parent, f, cursor);
	}

	void decl_function_method(CLModule& module, CLPrimitive& parent, CXCursor cursor)
	{
		CLFunction& f = vector_emplace<CLFunction>(module.m_methods, parent, spelling(cursor));
		decl_callable(module, parent, f, cursor);
	}

	void resolve_templates(CLModule& module, CLClass& c)
	{
		//printf("Resolve templates for %s\n", c.m_id.c_str());

		c.m_template = &module.get_class_template(c.m_template_name);
		if(c.m_template == nullptr)
		{
			c.m_reflect = false;
			printf("[ERROR] %s - could not find template type definition\n", c.m_name.c_str());
			return;
		}

		for(size_t i = 0; i < c.m_template_types.size(); ++i)
		{
			CXType t = clang_Type_getTemplateArgumentAsType(type(c.m_cursor), i);
			CLType* type = module.find_alias(t, c.m_template_types[i]);
			if(type == nullptr)
				type = module.get_type(t);
			c.m_templated_types.push_back(type);
			bool pointer = c.m_template_types[i].find("*") != string::npos;
			c.m_template_types[i] = type->m_id + string(pointer && type->m_type_kind != CLTypeKind::VoidPtr ? "*" : "");
		}

		c.set_name(c.m_template_name + "<" + comma(c.m_template_types) + ">");

		if(c.m_sequence)
		{
			c.m_element = c.m_template_types[0];
			c.m_element_type = c.m_templated_types[0];
		}
	}

	void decl_class(CLModule& module, CLPrimitive& parent, CLClass& c, CXCursor cursor, CXType cxtype, bool sequence)
	{
		c.m_cursor = cursor;

		c.m_annotations = get_annotations(cursor);

		c.m_struct = has(c.m_annotations, "struct") || cursor.kind == CXCursor_StructDecl;
		c.m_move_only = has(c.m_annotations, "nocopy");
		c.m_reflect = has(c.m_annotations, "refl") && should_reflect(cursor, module);
		c.m_array = has(c.m_annotations, "array");
		c.m_span = has(c.m_annotations, "span");
		c.m_sequence = has(c.m_annotations, "seque") || c.m_span;
		c.m_extern = has(c.m_annotations, "extern");

		c.m_is_template = cursor.kind == CXCursor_ClassTemplate;
		c.m_is_templated = c.m_name.find("<") != string::npos && !c.m_is_template;

		if(c.m_is_template)
			c.set_name(displayname(cursor));
		if(c.m_is_template || c.m_is_templated)
		{
			c.m_template_types = template_types(c.m_name);
			c.m_template_name = template_name(c.m_name);
		}

		parent.m_reflect_content |= c.m_reflect;
		module.m_has_reflected |= c.m_reflect;
	}

	CLClass& decl_class_type(CLModule& module, CLPrimitive& parent, CXCursor cursor)
	{
		CLClass& c = vector_emplace<CLClass>(module.m_classes, module, parent, type(cursor));
		module.register_type(c);
		decl_class(module, parent, c, cursor, type(cursor));
		return c;
	}

	CLClass& decl_sequence_type(CLModule& module, CLPrimitive& parent, CXCursor cursor)
	{
		CLClass& c = vector_emplace<CLClass>(module.m_sequences, module, parent, type(cursor));
		module.register_type(c);
		decl_class(module, parent, c, cursor, type(cursor), true);
		return c;
	}

	CLClass& decl_class_template(CLModule& module, CLPrimitive& parent, CXCursor cursor)
	{
		CLClass& c = vector_emplace<CLClass>(module.m_class_templates, module, parent, type(cursor));
		decl_class(module, parent, c, cursor, type(cursor));
		return c;
	}
	
	void parse_enum(CLModule& module, CLEnum& e)
	{
		UNUSED(module);
		e.m_scoped = is_scoped(e.m_cursor);
		e.m_enum_type = spelling(enum_type(e.m_cursor));
		e.m_prefix = e.m_scoped ? e.m_id + "::" : e.m_parent->m_prefix;

		const CXType integer_type = canonical(clang_getEnumDeclIntegerType(e.m_cursor));
		bool is_signed = has({ CXType_SChar, CXType_Short, CXType_Int, CXType_Long, CXType_LongLong }, integer_type.kind);

		visit_children(e.m_cursor, [&](CXCursor c)
		{
			if(c.kind == CXCursor_EnumConstantDecl)
			{
				e.m_ids.push_back(displayname(c));
				e.m_values.push_back(is_signed ? to_string(clang_getEnumConstantDeclValue(c))
											   : to_string(clang_getEnumConstantDeclUnsignedValue(c)));
				e.m_scoped_ids.push_back(e.m_prefix + displayname(c));
			}
		});

		e.m_count = e.m_ids.size();
	}

	void parse_static(CLModule& module, CLClass& c, CXCursor cursor)
	{
		UNUSED(module);
		CLStatic& s = push(c.m_statics, c);
		s.m_member = spelling(cursor);
		s.m_name = replace(spelling(cursor), "m_", "");
	}
	
	void find_default_value(CXCursor cursor, CLType& value_type, bool& has_default, string& default_value)
	{
		if(type(cursor).kind == CXType_ConstantArray)
			return;

		visit_children(cursor, [&](CXCursor c)
		{
			if(has({ CXCursor_CXXBoolLiteralExpr, CXCursor_FloatingLiteral, CXCursor_IntegerLiteral, CXCursor_StringLiteral }, c.kind))
			{
				has_default = true;
				default_value = first_token(c);
			}
			else if(has({ CXCursor_BinaryOperator, CXCursor_UnaryOperator, CXCursor_CallExpr, CXCursor_DeclRefExpr, CXCursor_UnexposedExpr, CXCursor_ParenExpr }, c.kind))
			{
				has_default = true;
				visit_tokens(c, [&](CXToken t) {
					string token = spelling(c, t);
					if(ends_with(default_value + token, value_type.m_name))
						default_value += token;
					else if(kind(t) == CXToken_Identifier && value_type.m_name == token) default_value += value_type.m_id;
					else if(token != "=") default_value += token;
				});
			}
		});

		// an expression expanded from a macro (e.g. UINT32_MAX) has no tokens, the default is the macro as written
		if(has_default && default_value == "")
			default_value = last_token(cursor);
	}

	void parse_param(CLModule& module, CLPrimitive& parent, CLCallable& f, CLParam& p, CXCursor cursor)
	{
		p.m_name = spelling(cursor);
		p.m_type = qual_type(module, parent, type(cursor), !parent.m_is_template);

		p.m_output = p.m_name.substr(0, 6) == "output";

		if(p.m_type.m_type)
		{
			find_default_value(cursor, *p.m_type.m_type, p.m_has_default, p.m_default);
			if(parent.m_is_templated)
				p.m_default = parent.fix_template_expression(parent.fix_template(p.m_default));
		}
	}

	void parse_callable(CLModule& module, CLCallable& f)
	{
		//printf("Parsing %s\n", f.m_name.c_str());
		f.m_return_type = qual_type(module, *f.m_parent, result_type(f.m_cursor), !f.m_is_template);

		visit_children(f.m_cursor, [&](CXCursor a)
		{
			if(a.kind == CXCursor_ParmDecl)
			{
				f.m_params.push_back(CLParam(f, f.m_params.size()));
				parse_param(module, *f.m_parent, f, f.m_params.back(), a);
			}
		});

		// the default arguments of a template specialization are the ones of its template
		size_t index = 0;
		if(f.m_cursor.kind == CXCursor_FunctionDecl)
			visit_children(clang_getSpecializedCursorTemplate(f.m_cursor), [&](CXCursor a)
			{
				if(a.kind != CXCursor_ParmDecl || index >= f.m_params.size())
					return;
				CLParam& p = f.m_params[index++];
				if(!p.m_has_default && p.m_type.m_type)
					find_default_value(a, *p.m_type.m_type, p.m_has_default, p.m_default);
			});

		for(size_t i = 0; i < f.m_params.size(); ++i)
			if(!f.m_params[i].m_has_default)
				f.m_min_args = i + 1;
	}

	void parse_constructor(CLModule& module, CLClass& c, CXCursor cursor)
	{
		CLConstructor& ctor = push(c.m_constructors, c, spelling(cursor));
		decl_callable(module, c, ctor, cursor);
		parse_callable(module, ctor);
		ctor.m_overload_index = c.m_constructors.size() - 1;

		// a constructor without parameters is the default constructor, which is reflected separately
		if(ctor.m_params.empty())
		{
			c.m_default_constructor = make_unique<CLConstructor>(c, ctor.m_name);
			c.m_default_constructor->m_module = &module;
			c.m_constructors.pop_back();
		}
	}

	void parse_method(CLModule& module, CLClass& c, CLMethod& m, CXCursor cursor)
	{
		decl_callable(module, c, m, cursor);
		parse_callable(module, m);
		m.m_const = is_const_method(cursor);
	}

	void parse_method(CLModule& module, CLClass& c, CXCursor cursor)
	{
		CLMethod& m = push(c.m_methods, c, spelling(cursor));
		parse_method(module, c, m, cursor);
	}

	void parse_function_method(CLModule& module, CLFunction& f)
	{
		parse_callable(module, f);
		CLClass& c = *f.m_params[0].m_type.m_class;
		
		//parse_method(module, c, f.m_cursor);

		CLMethod& m = push(c.m_methods, c, f.m_name);
		decl_callable(module, c, m, f.m_cursor);
		m.m_return_type = f.m_return_type;
		m.m_params = vector<CLParam>(f.m_params.begin() + 1, f.m_params.end());
		m.m_function = &f;
	}

	void parse_member(CLModule& module, CLClass& c, CXCursor cursor)
	{
		CLMember& m = push(c.m_members, c);

		m.m_member = spelling(cursor);
		m.m_name = replace(spelling(cursor), "m_", "");
		m.m_capname = string(1, char(toupper(m.m_name[0]))) + m.m_name.substr(1, string::npos);

		CXType member_type = type(cursor);

		if(cursor.kind == CXCursor_CXXMethod)
		{
			m.m_method = make_unique<CLMethod>(c, spelling(cursor));
			parse_method(module, c, *m.m_method, cursor);
			member_type = result_type(cursor);
		}

		m.m_type = qual_type(module, c, member_type, !c.m_is_template);

		m.m_annotations = get_annotations(cursor);
		m.m_nonmutable = has(m.m_annotations, "nomut");
		m.m_structure = has(m.m_annotations, "graph");
		m.m_link = has(m.m_annotations, "link");
		m.m_component = has(m.m_annotations, "comp");

		if(!c.m_is_template)
		{
			m.m_nonmutable |= m.m_type.reference();
			m.m_nonmutable |= !m.m_type.pointer() && (m.m_type.isconst() || !m.m_type.m_type->copyable());
			m.m_nonmutable |= !m.m_setter && m.m_method;
		}

		visit_children(cursor, [&](CXCursor s)
		{
			if(s.kind == CXCursor_CXXMethod && spelling(s) == "set" + m.m_capname || spelling(s) == "set_" + m.m_name)
			{
				m.m_setter = make_unique<CLMethod>(c, spelling(s));
				parse_method(module, c, *m.m_setter, s);
			}
		});

		if(m.m_type.m_type)
		{
			find_default_value(cursor, *m.m_type.m_type, m.m_has_default, m.m_default);
			if(c.m_is_templated)
				m.m_default = c.fix_template_expression(c.fix_template(m.m_default));
		}
	}

	void parse_class_child(CLModule& module, CLClass& c, CXCursor cursor)
	{
		const vector<string> annotations = get_annotations(cursor);

		if(cursor.kind == CXCursor_TemplateTypeParameter)
			c.m_template_types.push_back(spelling(cursor));

		else if(cursor.kind == CXCursor_CXXBaseSpecifier)
		{
			const string name = spelling(type(cursor));

			//if(c.m_is_templated && name.find("<") != string::npos)
			//	name = c.fix_template(name);

			if(!c.m_is_templated && name.find("<") == string::npos)
			{
				CLType* base = module.find_type(name);
				if(base && base->m_type_kind == CLTypeKind::Alias)
					base = static_cast<CLAlias*>(base)->m_target;
				if(base && (base->m_reflect || has(base->m_annotations, "refl")))
				{
					CLClass* basecls = static_cast<CLClass*>(base);
					c.m_bases.push_back(basecls);
					c.m_deep_bases.push_back(basecls);
					extend(c.m_deep_bases, basecls->m_bases);
				}
			}
		}

		else if(cursor.kind == CXCursor_Constructor && has(annotations, "constr"))
			parse_constructor(module, c, cursor);
		else if(cursor.kind == CXCursor_CXXMethod && has(annotations, "attr"))
			parse_member(module, c, cursor);
		else if(cursor.kind == CXCursor_CXXMethod && has(annotations, "meth"))
			parse_method(module, c, cursor);
		else if(cursor.kind == CXCursor_FieldDecl && has(annotations, "attr"))
			parse_member(module, c, cursor);
		else if(cursor.kind == CXCursor_VarDecl && has(annotations, "attr"))
			parse_static(module, c, cursor);
		else if(cursor.kind == CXCursor_UnionDecl || cursor.kind == CXCursor_StructDecl)
		{
			if(clang_Cursor_isAnonymous(cursor))
				visit_children(cursor, [&](CXCursor a) {
					parse_class_child(module, c, a);
				});
		}
	}

	void parse_class(CLModule& module, CLClass& c)
	{
		//printf("Parsing %s\n", c.m_id.c_str());
		CXCursor cursor = c.m_cursor;

#if !RESOLVE_TEMPLATES
		if(c.m_is_templated)
			resolve_templates(module, c);
#endif

		if(c.m_is_templated && c.m_template) // && is_template_decl(cursor))
			cursor = c.m_template->m_cursor;

		visit_children(cursor, [&](CXCursor a) {
			parse_class_child(module, c, a);
		});

		if(c.m_array)
		{
			c.m_array_size = c.m_members.size();
			c.m_array_type = c.m_members[0].m_type.m_type;
		}

		set<string> method_names;
		for(CLMethod& method : c.m_methods)
		{
			if(method_names.find(method.m_name) != method_names.end())
				method.m_overloaded = true;
			method_names.insert(method.m_name);
		}

		if(c.m_struct && c.m_constructors.empty() && !c.m_default_constructor)
		{
			c.m_default_constructor = make_unique<CLConstructor>(c, c.m_name);
			c.m_default_constructor->m_module = &module;
		}
	}

	void parse_sequence(CLModule& module, CLClass& c)
	{
		parse_class(module, c);
		c.m_name = c.m_template_name + "<" + c.m_element + ">";
	}

	void build_classes(CXCursor cursor, CLModule& module, CLPrimitive& parent)
	{
		visit_children(cursor, [&](CXCursor c)
		{
			if(!should_visit(c, module)) return;

			vector<string> annotations = get_annotations(c);
			
			if(c.kind == CXCursor_Namespace)
			{
				CLNamespace& ns = module.get_namespace(spelling(c), parent);
				build_classes(c, module, ns);
			}
			else if(c.kind == CXCursor_VarDecl && has(annotations, "base"))
			{
				module.base_type(type(c));
			}
			else if(c.kind == CXCursor_TypeAliasDecl || c.kind == CXCursor_TypedefDecl)
			{
				CXType cxalias = type(c);
				CXType cxtarget = canonical(type(c));
				CLType* target = module.find_type(cxtarget);
				if(target && !target->iscstring() && parent.m_kind == CLPrimitiveKind::Namespace)
				{
					CLAlias& t = vector_emplace<CLAlias>(module.m_aliases, module, parent, cxalias, cxtarget);
					//printf("aliased %s to %s\n", t.m_id.c_str(), target->m_id.c_str());
					t.m_target = target;
					t.m_target_spelling = spelling(clang_getTypedefDeclUnderlyingType(c));
					t.m_reflect = should_reflect(c, module);
					module.register_type(t);
				}
			}
			else if(is_definition(c) && has(annotations, "refl"))
			{
				if(c.kind == CXCursor_EnumDecl)
					decl_enum(module, parent, c);
				else if((c.kind == CXCursor_ClassDecl || c.kind == CXCursor_StructDecl))
				{
					CLClass& cl = has(annotations, "seque") || has(annotations, "span")
						? decl_sequence_type(module, parent, c)
						: decl_class_type(module, parent, c);
					build_classes(c, module, cl);
				}
				else if(c.kind == CXCursor_ClassTemplate)
				{
					CLClass& cl = decl_class_template(module, parent, c);
					build_classes(c, module, cl);
				}
			}
			else if(c.kind == CXCursor_FunctionTemplate && has(annotations, "func"))
				decl_function_template(module, parent, c);
			// a function is reflected once, not again at its redeclarations (e.g. the definition of an explicit specialization)
			else if(c.kind == CXCursor_FunctionDecl && has(annotations, "func") && should_reflect(c, module) && module.m_function_usrs.insert(clang_string(clang_getCursorUSR(c))).second)
				decl_function(module, parent, c);
			else if(c.kind == CXCursor_FunctionDecl && has(annotations, "meth") && should_reflect(c, module))
				decl_function_method(module, parent, c);
		});
	}

	class CLGenerator
	{
	public:
		CLGenerator() {}

		vector<unique<CLModule>> m_modules = {};
		vector<CLModule*> m_generator_queue = {};

		CLModule& module(const string& id)
		{
			for(auto& module : m_modules)
				if(id == module->m_id)
					return *module;
			printf("[ERROR] fetching inexistent module\n");
			static CLModule invalid; return invalid;
		}

		void print_diagnostics(CXTranslationUnit tu)
		{
			uint num_diagnostics = clang_getNumDiagnostics(tu);
			for(uint i = 0; i < num_diagnostics; ++i)
			{
				CXDiagnostic diagnostic = clang_getDiagnostic(tu, i);
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

		// C++20 module name -> path of its interface
		// the interfaces of the compiler the generator runs along are preferred: on Windows the MSVC ones (.ixx), which
		// import the std headers they use, elsewhere the clang/gcc ones (.cppm), which import the whole std module
#ifdef _WIN32
		const string m_preferred_interface = "ixx";
#else
		const string m_preferred_interface = "cppm";
#endif
		map<string, string> m_module_interfaces;

		void find_module_interfaces(const string& dir)
		{
			visit_files(dir, [&](const string& file)
			{
				const string extension = file_extension(file);
				if(extension != "ixx" && extension != "cppm")
					return;
				const string path = dir + "/" + file;
				read_text_file(path, [&](const string& line)
				{
					const string prefix = "export module ";
					if(line.rfind(prefix, 0) != 0)
						return true;
					const string name = line.substr(prefix.size(), line.find(';') - prefix.size());
					if(extension == m_preferred_interface || m_module_interfaces.find(name) == m_module_interfaces.end())
						m_module_interfaces[name] = path;
					return false;
				});
			});

			visit_folders(dir, [&](const string& folder)
			{
				if(folder != "meta" && folder != "unused")
					this->find_module_interfaces(dir + "/" + folder);
			});
		}

		// Module headers don't include the headers of their dependencies, they get them from the imports of the module
		// interface. To parse a module with libclang, its interface is flattened into a plain header: imported modules are
		// expanded recursively in place, imported header units become includes, includes and defines are kept as is.
		void flatten_module_interface(const string& name, set<string>& visited, string& source)
		{
			if(visited.find(name) != visited.end())
				return;
			visited.insert(name);

			auto it = m_module_interfaces.find(name);
			if(it == m_module_interfaces.end())
			{
				printf("[warning] no interface found for imported module %s\n", name.c_str());
				return;
			}

			read_text_file(it->second, [&](const string& raw)
			{
				const size_t start = raw.find_first_not_of(" \t");
				string line = start == string::npos ? "" : raw.substr(start);
				if(line.rfind("#include", 0) == 0 || line.rfind("#define", 0) == 0)
					source += line + "\n";

				if(line.rfind("export ", 0) == 0)
					line = line.substr(7);
				if(line.rfind("import ", 0) != 0)
					return true;

				const string imported = line.substr(7, line.find(';') - 7);
				if(imported[0] == '<')
					source += "#include " + imported + "\n";
				// the std module is the whole standard library
				else if(imported == "std")
				{
					if(visited.find(imported) == visited.end())
						for(const char* header : c_std_headers)
							source += "#include <" + string(header) + ">\n";
					visited.insert(imported);
				}
				// the old MSVC std modules, and the meta modules which are generated from what we parse here
				else if(imported.rfind("std.", 0) == 0 || file_extension(imported) == "meta")
					;
				else
					this->flatten_module_interface(imported, visited, source);
				return true;
			});
		}

		CXTranslationUnit parse(CLModule& module)
		{
			printf("Module path : %s\n", module.m_path.c_str());

			if(m_module_interfaces.empty())
				this->find_module_interfaces(module.m_rootdir);

			set<string> visited;
			string source;
			this->flatten_module_interface(module.module_name(), visited, source);
			if(source.empty())
			{
				// no module interface, parse the headers directly
				source = "#include <" + module.m_subdir + "/Api.h>\n";
			}

			bool debug_diagnostic = true;

			vector<string> compiler_args = {
				"-x",
				"c++",
				"-std=c++20",
				"-ferror-limit=0",
#ifdef _WIN32
				"-fdelayed-template-parsing",
				"-fms-compatibility",
				"-fms-extensions",
				"-Wmicrosoft",
				// MSVC and Windows SDK include paths and the MSVC version are detected by the clang driver
				// the MSVC STL refuses clang versions older than the one it ships with, the generator only parses declarations
				"-D_ALLOW_COMPILER_AND_STL_VERSION_MISMATCH",
#endif
				"-DTWO_META_GENERATOR",
				// same configuration as the module builds (see two_module() in two.lua), minus USE_STL: the generated code names the stl:: containers
				"-DTWO_MODULES",
				"-DTWO_STD_MODULES",
				"-DTWO_STATIC",
				"-DBX_CONFIG_DEBUG=0",
				//"-DTWO_NO_GLM", // @todo
			};

			for(string attr : { "base", "refl", "struct", "nocopy", "extern", "gpu", "array", "span", "seque", "comp", "constr", "meth", "func", "attr", "nomut", "graph", "link" })
				compiler_args.push_back("-D" + attr + "_=__attribute__((annotate(\"" + attr + "\")))");

			for(string dir : module.m_includedirs)
				compiler_args.push_back("-I" + dir);

			for(CLModule* m : module.m_modules)
				compiler_args.push_back("-I" + m->m_rootdir);

#if DEBUG_CLANG_ARGS
			printf("Parsing with compiler args: \n");
			for(string arg : compiler_args)
				printf("%s\n", arg.c_str());
#endif

			vector<cstring> compiler_cargs;
			for(const string& arg : compiler_args)
				compiler_cargs.push_back(arg.c_str());

			// the flattened interface is handed to libclang as an in-memory file, it only holds includes and defines
			string path = module.m_path + "/" + module.module_name() + ".clrefl.h";
			CXUnsavedFile unsaved = { path.c_str(), source.c_str(), (unsigned long)source.size() };
			CXIndex index = clang_createIndex(0, 0);

			printf("Parsing %s\n", module.module_name().c_str());

			// only for debugging : these two ways of parsing don"t give the correct output, but can give more diagnostics as to what might be wrong
			// int options = 0;
			// int options = CXTranslationUnit_SkipFunctionBodies;

			//int options = CXTranslationUnit_SkipFunctionBodies | CXTranslationUnit_Incomplete;
			int options = CXTranslationUnit_SkipFunctionBodies | CXTranslationUnit_KeepGoing;
			CXTranslationUnit translation_unit = clang_parseTranslationUnit(index, path.c_str(), compiler_cargs.data(), int(compiler_cargs.size()), &unsaved, 1, options);

			constexpr bool debug = true;
			if(debug)
				print_diagnostics(translation_unit);

			return translation_unit;
		}

		void generate_module(CLModule& module)
		{
			if(!file_exists(module.m_path + "/" + "Types.h"))
			{
				//with open(os.path.join(module.path, "Types.h"), "w") as f :
				//	pass
			}

			printf("NUM CLASSES : %i\n", int(module.m_classes.size()));

			//string forward_h = clgen::forward_h_template(module);
			//update_file((module.m_path + "/" + "Forward.h", forward_h);

			CXTranslationUnit tu = this->parse(module);
			g_printing_policy = clang_getCursorPrintingPolicy(cursor(tu));
			clang_PrintingPolicy_setProperty(g_printing_policy, CXPrintingPolicy_FullyQualifiedName, 1);
			build_classes(cursor(tu), module, module.m_global);

#if RESOLVE_TEMPLATES
			for(auto& c : module.m_classes)
				if(c->m_is_templated)
					resolve_templates(module, *c);

			for(auto& c : module.m_sequences)
				if(c->m_is_templated)
					resolve_templates(module, *c);
#endif

			for(auto& e : module.m_enums)
				parse_enum(module, *e);
			for(auto& c : module.m_classes)
				parse_class(module, *c);
			for(auto& c : module.m_sequences)
				parse_sequence(module, *c);
			for(auto& f : module.m_functions)
				parse_callable(module, *f);
			for(auto& f : module.m_methods)
				parse_function_method(module, *f);

			clang_PrintingPolicy_dispose(g_printing_policy);
			g_printing_policy = nullptr;
			clang_disposeTranslationUnit(tu);

			auto cmp_types = [](CLType& a, CLType& b) -> int
			{
				int result = a.m_name.compare(b.m_name);
				return result < 0;
			};

			stable_sort(module.m_types, [&](CLType* a, CLType* b) { return cmp_types(*a, *b) < 0; });

			stable_sort(module.m_enums, [&](const unique<CLEnum>& a, const unique<CLEnum>& b) { return cmp_types(*a, *b) < 0; });
			stable_sort(module.m_sequences, [&](const unique<CLClass>& a, const unique<CLClass>& b) { return cmp_types(*a, *b) < 0; });
			stable_sort(module.m_basetypes, [&](const unique<CLBaseType>& a, const unique<CLBaseType>& b) { return cmp_types(*a, *b) < 0; });

			sort_classes(module.m_classes);

			//if(module.m_classes.size() == 0 && module.m_enums.size() == 0)
			//	return;

			if(!directory_exists(module.m_refl_path))
				create_directory_tree(module.m_refl_path);
            
			printf("Generating meta reflection files for %s:\n", module.m_name.c_str());

			string types_h = clgen::types_h_template(module);
			update_file(module.m_path + "/" + "Types.h", types_h);

			if(!module.m_notypes)
			{
				string types_cpp = clgen::types_cpp_template(module);
				update_file(module.m_path + "/" + module.m_dotname + ".types.cpp", types_cpp);
			}

			string module_h = clgen::module_h_template(module);
			update_file(module.m_refl_path + "/" + module.m_dotname + ".meta.h", module_h);

			string module_cpp = clgen::module_cpp_template(module);
			update_file(module.m_refl_path + "/" + module.m_dotname + ".meta.cpp", module_cpp);

			string module_ixx = clgen::module_meta_ixx_template(module);
			update_file(module.m_refl_path + "/" + module.m_dotname + ".meta.ixx", module_ixx);

			string module_cppm = clgen::module_meta_ixx_template(module, true);
			update_file(module.m_refl_path + "/" + module.m_dotname + ".meta.cppm", module_cppm);

			string convert_h = clgen::convert_h_template(module);
			update_file(module.m_refl_path + "/" + module.m_dotname + ".conv.h", convert_h);

			printf("Generating bindings files for %s:\n", module.m_name.c_str());

			if(!directory_exists(module.m_bind_path))
				create_directory_tree(module.m_bind_path);

			clgen::bind_javascript(module);
		}

		void add_module(const Json& m)
		{
			auto tos = [](const Json& j) -> string { return j.string_value().c_str(); };

			vector<CLModule*> dependencies = {};
			for(const Json& dep : m["dependencies"].array_items())
			{
				dependencies.push_back(&this->module(tos(dep)));
			}

			vector<string> includedirs = {};
			for(const Json& inc : m["includedirs"].array_items())
			{
				includedirs.push_back(tos(inc));
			}

			CLModule& module = vector_emplace<CLModule>(m_modules, tos(m["namespace"]), tos(m["name"]), tos(m["dotname"]), tos(m["idname"]),
																   tos(m["root"]), tos(m["subdir"]), tos(m["path"]), includedirs, dependencies);
			if(m["notypes"].bool_value())
				module.m_notypes = true;
			m_generator_queue.push_back(&module);

			if(module.m_name == "type")
				module.m_decl_basetypes = true;
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

using namespace two;

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		printf("usage: clrefl <module_refl.json>...\n");
		printf("  module descriptions are written by the GENie reflect action, in dependency order\n");
		return 1;
	}

	CLGenerator generator;

	for(int i = 1; i < argc; ++i)
	{
		const string location = argv[i];
		if(!file_exists(location))
		{
			printf("ERROR: module description %s not found\n", location.c_str());
			return 1;
		}

		std::string errors;
		string text_module = read_text_file(location);
		Json json_module = Json::parse(text_module.c_str(), errors);
		if(!errors.empty())
		{
			printf("ERROR: parsing module description %s: %s\n", location.c_str(), errors.c_str());
			return 1;
		}
		generator.add_module(json_module);
	}

	generator.generate_all_modules();
	return 0;
}
