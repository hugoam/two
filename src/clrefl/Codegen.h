#pragma once

#include <clrefl/Generator.h>

#include <string>

using std::string;

namespace mud
{
namespace clgen
{
	std::vector<string> location(const CLPrimitive& e)
	{
		if(e.m_parent->m_id == "") return {};
		else return split(e.m_parent->m_id, "::");
	}
	
	string namespace_begin(CLPrimitive& n)
	{
		if(n.m_name != "")
			return namespace_begin(*n.m_parent) + "namespace " + n.m_name + " {\n";
		else
			return "";
	}

	string namespace_end(CLPrimitive& n)
	{
		if(n.m_name != "")
			return namespace_end(*n.m_parent) + "}\n";
		else
			return "";
	}

	string clnamespace(const CLPrimitive& e)
	{
		if(e.m_parent->m_id == "")
			return "&namspc({})";
		else
			return "&namspc({ \"" + join(location(e), "\", \"") + "\" })";
	}

	string type_get(const CLType& c) { return "type<" + c.m_id + ">()"; }
	string type_get_pt(const CLType& c) { return "&type<" + c.m_id + ">()"; }

	string base_offset_get(const CLType& c, const CLType& base) { return "base_offset<" + c.m_id + ", " + base.m_id + ">()"; }
	
	string type_var(string name, const CLType& c, bool pointer, string value = "")
	{
		if(name == "void")
			return "Var()";
		else if(name == "mud::Ref")
			return "Ref()";
		else if(pointer || !c.m_struct)
			return "Ref(" + type_get(c) + ")";
		else if(value == "")
			return "var(" + c.m_id + "())";
		else if(value[0] == '{')
			return "var(" + c.m_id + value + ")";
		else if(starts_with(value, c.m_id))
			return "var(" + value + ")";
		else
			return "var(" + c.m_id + "(" + value + "))";
	}
	
	string value_var(const CLType& c, bool pointer, string value = "")
	{
		if(c.m_id == "mud::Ref")
			return value;
		else if(c.m_struct && !pointer)
			return "var(" + value + ")";
		else
			return "Ref(" + string(pointer ? "" : "&") + value + ")";
	}
	
	string value_assign(const CLType& c, string var, bool pointer, string value)
	{
		if(c.m_id == "mud::Ref")
			return var + " = " + value;
		else if(c.m_struct && !pointer)
			return "val<" + c.m_id + ">(" + var + ") = " + value;
		else
			return var + " = Ref(" + string(pointer ? "" : "&") + value + ")";
	}
   
	string param_default(const CLParam& p)
	{
		return type_var(p.m_type.m_type->m_id, *p.m_type.m_type, p.m_type.pointer(), p.m_default);
	}

	string param_refget(const CLParam& p, size_t index)
	{
		if(p.m_type.m_type->m_id == "mud::Ref")
			return "args[" + to_string(index) + "]";
		else
			return string(p.m_type.pointer() && !p.m_type.m_type->m_pointer ? "&" : "") + "val<" + p.m_type.m_type->m_id + ">(args[" + to_string(index) + "])";
	}
	
	string param_forward(const CLParam& p, size_t index)
	{
		if(p.m_type.m_type->m_id == "toy::OCollider")
			int i = 0;
		bool move = p.m_type.m_type->m_move_only && p.m_type.value();
		return move ? "std::move(" + param_refget(p, index) + ")" : param_refget(p, index);
	}

	string param_flags(const CLParam& p)
	{
		std::vector<string> flags;
		if(p.m_type.nullable()) flags.push_back("Param::Nullable");
		if(p.m_output) flags.push_back("Param::Output");
		if(p.m_has_default) flags.push_back("Param::Default");
		if(flags.size() == 0) return "";
		else if(flags.size() == 1) return ", " + flags[0];
		else return ", Param::Flags(" + join(flags, "|") + ")";
	 }

	string param_decl(const CLParam& p)
	{
		return "{ \"" + p.m_name + "\", " + param_default(p) + param_flags(p) + " }";
	}
	
	std::vector<string> function_args_types(const CLFunction& f)
	{
		return transform<string>(f.m_params, [](const CLParam& p) { return p.m_type.m_spelling; });
	}

	string function_signature(const CLFunction& f)
	{
		return f.m_return_type.m_spelling + "(*)(" + join(function_args_types(f), ", ") + ")";
	}

	string method_signature(const CLMethod& m)
	{
		return m.m_return_type.m_spelling + "(" + m.m_parent->m_id + "::*)(" + join(function_args_types(m), ", ") + ")" + (m.m_const ? " const" : "");
	}

	string function_identity(const CLFunction& f)
	{
		return "function_id<" + function_signature(f) + ">(&" + f.m_id + ")";
	}
	
	string function_return_def(const CLFunction& f)
	{
		return type_var(f.m_return_type.m_spelling, *f.m_return_type.m_type, f.m_return_type.pointer());
	}

	string params_def(const std::vector<CLParam>& params)
	{
		std::vector<string> decls = transform<string>(params, [](const CLParam& p) { return param_decl(p); });
		return params.size() > 0 ? "{ " + join(decls, ", ") + " }" : "{}";
	}

	string get_args(const std::vector<CLParam>& params)
	{
		std::vector<string> decls = transform<string>(params, [](const CLParam& p) { return param_forward(p, p.m_index); });
		return join(decls, ", ");
	}

	string method_identity(const CLType& c, const CLMethod& m)
	{
		string signature = m.m_overloaded || true ? "<" + method_signature(m) + ">" : "";
		return "member_address" + signature + "(&" + c.m_id + "::" + m.m_name + ")";
	}

	string field_identity(const CLType& c, const CLMember& m)
	{
		return m.m_type.reference() ? "Address()" : "member_address(&" + c.m_id + "::" + m.m_member + ")";
	}

	string member_identity(const CLType& c, const CLMember& m)
	{
		return m.m_method ? method_identity(c, *m.m_method) : field_identity(c, m);
	}
	
	string member_flags(const CLType& c, const CLMember& m)
	{
		UNUSED(c);
		std::vector<string> flags;
		if(m.m_type.pointer()) flags.push_back("Member::Pointer");
		if(m.m_type.m_type->m_struct && !m.m_type.pointer()) flags.push_back("Member::Value");
		if(m.m_nonmutable || m.m_type.reference()) flags.push_back("Member::NonMutable");
		if(m.m_structure) flags.push_back("Member::Structure");
		if(m.m_component) flags.push_back("Member::Component");
		if(m.m_link || m.m_type.pointer() || m.m_type.reference()) flags.push_back("Member::Link");
		if(flags.size() == 0) return "Member::None";
		else if(flags.size() == 1) return flags[0];
		else return "Member::Flags(" + join(flags, "|") + ")";
	}
	
	string unused_args(const CLFunction& f)
	{
		return f.m_params.size() == 0 ? "UNUSED(args); " : "";
	}

	string type_class(const CLType& c)
	{
		if(c.m_struct)
			return "TypeClass::Struct";
		else
			return "TypeClass::Object";
	}

	string member_type(const CLMember& m)
	{
		return m.m_type.m_type->m_id + (m.m_type.pointer() ? "*" : "");
	}

	string member_getter(const CLType& c, const CLMember& m)
	{
		if(m.m_method)
			return "[](Ref object) { return Ref(" + string(!m.m_type.pointer() ? "&" : "") + "val<" + c.m_id + ">(object)." + m.m_member + "()); }";
		else if(m.m_type.reference())
			return "[](Ref object) { return Ref(&val<" + c.m_id + ">(object)." + m.m_member + "); }";
		else
			return "nullptr";
	}

	string member_setter_explicit(const CLType& c, const CLMember& m)
	{
		if(m.m_setter)
			return "[](Ref object, const Var& v) { val<" + c.m_id + ">(object).set" + m.m_capname + "(val<" + member_type(m) + ">(v)); }";
		else if(!m.m_nonmutable)
			return "[](Ref object, const Var& v) { val<" + c.m_id + ">(object)." + m.m_member + " = val<" + member_type(m) + ">(v); }";
		else
			return "nullptr";
	}

	string member_setter(const CLType& c, const CLMember& m)
	{
		if(m.m_setter)
			return "member_setter<" + member_type(m) + ">(&" + c.m_id + "::set" + m.m_capname + ")";
		else if(!m.m_nonmutable)
			return "member_setter<" + member_type(m) + ">(&" + c.m_id + "::" + m.m_member + ")";
		else
			return "nullptr";
	}

	string member_default(const CLType& c, const CLMember& m)
	{
		UNUSED(c);
		return type_var(m.m_type.m_type->m_id, *m.m_type.m_type, m.m_type.pointer(), m.m_default);
		//if(m.m_type.m_type->m_struct && !m.m_type.pointer())
		//	return "var(" + member_type(m) + "(" + m.m_default + "))";
		//else
		//	return "Ref(" + type_get(*m.m_type.m_type) + ")";
	}

	string method_func(const CLType& c, const CLMethod& m)
	{
		string call = "val<" + c.m_id + ">(object)." + m.m_name + "(" + get_args(m.m_params) + ")";
		if(m.m_return_type.m_spelling == "void")
			return "[](Ref object, array<Var> args, Var& result) { UNUSED(result); " + unused_args(m) + call + "; }";
		else
			return "[](Ref object, array<Var> args, Var& result) { " + unused_args(m) + value_assign(*m.m_return_type.m_type, "result", m.m_return_type.pointer(), call) + "; }";
	}

	string constructor_decl(const CLType& c, const CLConstructor& constr)
	{
		return type_get(c) + ", [](Ref ref, array<Var> args) { " + unused_args(constr) + "new(&val<" + c.m_id + ">(ref)) " + c.m_id + "( " + get_args(constr.m_params) + " ); }, " + params_def(constr.m_expected_params);
	}

	string copy_constructor_decl(const CLType& c)
	{
		return type_get(c) + ", [](Ref ref, Ref other) { new(&val<" + c.m_id + ">(ref)) " + c.m_id + "(val<" + c.m_id + ">(other)); }";
	}

	string member_decl(const CLType& c, const CLMember& m)
	{
		return type_get(c) + ", " + member_identity(c, m) + ", " + type_get(*m.m_type.m_type) + ", \"" + m.m_name + "\", " + member_default(c, m) + ", " + member_flags(c, m) + ", " + member_getter(c, m);
	}

	string method_decl(const CLType& c, const CLMethod& m)
	{
		return type_get(c) + ", \"" + m.m_name + "\", " + method_identity(c, m) + ", " + method_func(c, m) + ", " + params_def(m.m_params) + ", " + function_return_def(m);
	}

	string static_decl(const CLType& c, const CLStatic& m)
	{
		return type_get(c) + ", \"" + m.m_name + "\", Ref(&" + c.m_id + "::" + m.m_member + ")";
	}

	string meta_decl(const CLType& c, const string& type_class)
	{
		string size = c.m_name == "void" ? "0" : "sizeof(" + c.m_id + ")";
		return "static Meta meta = { " + type_get(c) + ", " + clnamespace(c) + ", \"" + c.m_name + "\", " + size + ", " + type_class + " };";
	}

	void write_line(string& t, int& i, const string& s, bool spaces = false)
	{
		if(s[0] == '}') --i;
		for(size_t c = 0; c < i; ++c) t += spaces ? "    " : "\t";
		t += s;
		t += "\n";
		for(size_t c = 1; c < s.size(); ++c) { if(s[c] == '{') ++i; if(s[c] == '}') --i; }
		if(s[0] == '{') ++i;
	}

	string meta_h_template(CLModule& m)
	{
		string t;
		auto p = [&](int& i, const string& s) {	write_line(t, i, s, true); };
		int i = 0;

		p(i, "#pragma once");
		p(i, "");
		p(i, "#ifndef MUD_MODULES");
		p(i, "#include <meta/" + m.m_subdir + "/Module.h>");
		p(i, "");
		p(i, "#include <type/Any.h>");
		p(i, "#include <type/Vector.h>");
		p(i, "#include <refl/MetaDecl.h>");
		p(i, "#include <refl/Module.h>");
		p(i, "#endif");
		p(i, "");
		p(i, "namespace mud");
		p(i, "{");

		p(i, "void " + m.m_id + "_meta(Module& m)");
		p(i, "{");

		i--;

		p(i, "");

		p(i, "// Base Types");
		for(auto& pb : m.m_basetypes)
		{
			CLBaseType& b = *pb;
			p(i, "{");
			p(i, meta_decl(b, "TypeClass::BaseType"));
			p(i, "meta_basetype<" + b.m_name + ">();");
			p(i, "}");
		}
		p(i, "");

	
		p(i, "// Enums");
		for(auto& pe : m.m_enums)
			if(pe->m_reflect)
			{
				CLEnum& e = *pe;
				p(i, "{");
				p(i, meta_decl(e, "TypeClass::Enum"));
				p(i, "static Enum enu = { " + type_get(e) + ",");
				p(i, string(e.m_scoped ? "true" : "false") + ",");
				p(i, "{ \"" + join(e.m_ids, "\", \"") + "\" },");
				p(i, "{ " + join(e.m_values, ", ") + " },");
				p(i, "{ var(" + join(e.m_scoped_ids, "), var(") + ") }");
				p(i, "};");
				p(i, "meta_enum<" + e.m_id + ">();");
				p(i, "}");
			}
		p(i, "");

		p(i, "// Sequences");
		for(auto& ps : m.m_sequences)
		{
			CLSequence& s = *ps;
			p(i, "{");
			p(i, meta_decl(s, "TypeClass::Sequence"));
			p(i, "static Class cls = { " + type_get(s) + " };");
			p(i, "cls.m_content = " + type_get_pt(*s.m_contentcls) + ";");
			p(i, "meta_sequence<" + s.m_id + ", " + s.m_content + ">();");
			p(i, "}");
		}
		p(i, "");

		for(auto& pc : m.m_classes)
			if(pc->m_reflect)
			{
				CLClass& c = *pc;
				p(i, "// " + c.m_id);
				p(i, "{");
				p(i, meta_decl(c, type_class(c)));
				p(i, "static Class cls = { " + type_get(c) + ",");
				p(i, "// bases");
				p(i, "{ " + join(transform<string>(c.m_bases, [&](CLType* base) { return type_get_pt(*base); }), ", ") + " },");
				p(i, "{ " + join(transform<string>(c.m_bases, [&](CLType* base) { return base_offset_get(c, *base); }), ", ") + " },");
				p(i, "// constructors");
				p(i, "{");
				for(CLConstructor& constr : c.m_constructors)
					p(i, "{ " + constructor_decl(c, constr) + " }" + (&constr == &c.m_constructors.back() ? "" : ","));
				p(i, "},");
				p(i, "// copy constructor");
				p(i, "{");
				if(c.m_struct && !c.m_move_only)
					p(i, "{ " + copy_constructor_decl(c) + " }");
				p(i, "},");
				p(i, "// members");
				p(i, "{");
				for(CLMember& m : c.m_members)
					p(i, "{ " + member_decl(c, m) + " }" + (&m == &c.m_members.back() ? "" : ","));
				p(i, "},");
				p(i, "// methods");
				p(i, "{");
				for(CLMethod& m : c.m_methods)
					p(i, "{ " + method_decl(c, m) + " }" + (&m == &c.m_methods.back() ? "" : ","));
				p(i, "},");
				p(i, "// static members");
				p(i, "{");
				for(CLStatic& m : c.m_statics)
					p(i, "{ " + static_decl(c, m) + " }" + (&m == &c.m_statics.back() ? "" : ","));
				p(i, "}");
				p(i, "};");
				if(c.m_constructors.size() > 0 && !c.m_struct)
					p(i, "init_pool<" + c.m_id + ">();");
				if(c.m_array)
					p(i, "init_string<" + c.m_id + ">();");
				p(i, "meta_class<" + c.m_id + ">();");
				p(i, "}");
			}

		i++;

		for(CLType* t : m.m_types)
			if(t->m_reflect)
				p(i, "m.m_types.push_back(&" + type_get(*t) + ");");
       
		for(auto& pf : m.m_functions)
		{
			CLFunction& f = *pf;
			p(i, "{");
			if(f.m_return_type.m_spelling == "void")
				p(i, "auto func = [](array<Var> args, Var& result) { UNUSED(result); " + unused_args(f) + " " + f.m_id + "(" + get_args(f.m_params) + "); };");
			else
				p(i, "auto func = [](array<Var> args, Var& result) { " + unused_args(f) + " " + value_assign(*f.m_return_type.m_type, "result", f.m_return_type.pointer(), f.m_id + "(" + get_args(f.m_params) + ")") + "; };");
			p(i, "std::vector<Param> params = " + params_def(f.m_params) + ";");
			p(i, "static Function f = { " + clnamespace(f) + ", \"" + f.m_name + "\", " + function_identity(f) + ", func, params, " + function_return_def(f) + " };");
			p(i, "m.m_functions.push_back(&f);");
			p(i, "}");
		}

		p(i, "}");
		p(i, "}");

		return t;
	}

	string forward_h_template(CLModule& m)
	{
		string t;
		auto p = [&](int& i, const string& s) {	write_line(t, i, s); };
		int i = 0;

		p(i, "#pragma once");

		p(i, "#include <infra/Config.h>");

		for(CLModule* d : m.m_dependencies)
			p(i, "#include <" + d->m_subdir + "/Forward.h>");

		p(i, "#ifndef " + m.m_export);
		p(i, "#define " + m.m_export + " MUD_IMPORT");
		p(i, "#endif");

		for(auto& key_namespace : m.m_context.m_namespaces)
		{
			CLNamespace& n = *key_namespace.second;
			
			p(i, namespace_begin(n));
			for(auto& e : m.m_enums)
				if(e->m_parent == &n)
					p(i, "enum " + e->m_scoped ? "class " : "" + e->m_name + " : " + e->m_enum_type + ";");
        
			for(auto& c : m.m_class_templates)
				if(c->m_parent == &n && c->m_template_used)
					p(i, "template <class T> " + string(c->m_struct ? "struct" : "class") + " } " + c->m_template_name + ";");

			for(auto& c : m.m_classes)
				if(c->m_parent == &n && !c->m_nested && !c->m_is_templated && !c->m_extern)
					p(i, string(c->m_struct ? "struct" : "class") + " " + c->m_name + ";");
				else if(c->m_is_template)
					p(i, "template <class T> " + string(c->m_struct ? "struct" : "class") + " " + c->m_id + ";");

			p(i, namespace_end(n));
		}

		return t;
	}

	string convert_h_template(CLModule& m)
	{
		string t;
		auto p = [&](int& i, const string& s) {	write_line(t, i, s); };
		int i = 0;

		p(i, "#pragma once");
		p(i, "");
		p(i, "#include <" + m.m_subdir + "/Types.h>");
		p(i, "");
		p(i, "#if !defined MUD_MODULES || defined MUD_TYPE_LIB");
		p(i, "#include <refl/Meta.h>");
		p(i, "#include <refl/Enum.h>");
		p(i, "#include <infra/StringConvert.h>");
		p(i, "#endif");
		p(i, "");
		p(i, "namespace mud");
		p(i, "{");
		for(auto& e : m.m_enums)
		if(e->m_reflect)
		{
			p(i, "export_ template <> inline void from_string(const string& str, " + e->m_id + "& val) { val = static_cast<" + e->m_id + ">(enu<" + e->m_id + ">().value(str.c_str())); };");
			p(i, "export_ template <> inline void to_string(const " + e->m_id + "& val, string& str) { str = enu<" + e->m_id + ">().m_map[size_t(val)]; };");
			p(i, "");
		}
		p(i, "");
		for(auto& c : m.m_classes)
		if(c->m_array)
		{
			p(i, "export_ template <> inline void from_string(const string& str, " + c->m_id + "& val) { string_to_fixed_vector<" + c->m_id + ", " + c->m_array_type->m_id + ">(str, val); };");
			p(i, "export_ template <> inline void to_string(const " + c->m_id + "& val, string& str) { fixed_vector_to_string<" + c->m_id + ", " + to_string(c->m_array_size) + ">(val, str); };");
			p(i, "");
		}
		p(i, "}");

		return t;
	}

	string module_h_template(CLModule& m)
	{
		string t;
		auto p = [&](int& i, const string& s) {	write_line(t, i, s); };
		auto s = [&](int& i, const string& s) { i--; write_line(t, i, s); i++; };
		int i = 0;

		p(i, "#pragma once");
		p(i, "");
		p(i, "#if !defined MUD_MODULES || defined MUD_TYPE_LIB");
		p(i, "#include <refl/Module.h>");
		p(i, "#endif");
		p(i, "");
		p(i, "#ifndef MUD_MODULES");
		for(CLModule* d : m.m_dependencies)
			p(i, "#include <meta/" + d->m_subdir + "/Module.h>");
		p(i, "#endif");
		p(i, "");
		p(i, "#include <" + m.m_subdir + "/Forward.h>");
		p(i, "#include <" + m.m_subdir + "/Types.h>");
		p(i, "#include <" + m.m_subdir + "/Api.h>");
		p(i, "");
		p(i, "#include <meta/" + m.m_subdir + "/Convert.h>");
		p(i, "");
		p(i, "#ifndef " + m.m_refl_export);
		p(i, "#define " + m.m_refl_export + " MUD_IMPORT");
		p(i, "#endif");
		p(i, "");
		if(m.m_namespace != "")
		{
			p(i, "namespace " + m.m_namespace);
			p(i, "{");
		}
		p(i, "export_ class " + m.m_refl_export + " " + m.m_id + " : public Module");
		p(i, "{");
		s(i, "private:");
		p(i, m.m_id + "();");
		p(i, "");
		s(i, "public:");
		p(i, "static " + m.m_id + "& m() { static " + m.m_id + " instance; return instance; }");
		p(i, "};");
		if(m.m_namespace != "")
			p(i, "}");
		p(i, "");
		p(i, "#ifdef " + m.m_preproc_name + "_MODULE");
		p(i, "extern \"C\"");
		p(i, m.m_refl_export + " Module& getModule();");
		p(i, "#endif");

		return t;
	}

	string module_cpp_template(CLModule& m)
	{
		string t;
		auto p = [&](int& i, const string& s) {	write_line(t, i, s); };
		int i = 0;

		auto deps = [&](){ return join(transform<string>(m.m_dependencies, [](CLModule* d) { return "&" + d->m_id + "::m()"; }), ", "); };

		p(i, "#include <infra/Cpp20.h>");
		p(i, "");
		p(i, "#ifdef MUD_MODULES");
		p(i, "module " + m.m_namespace + "." + m.m_name + ";");
		p(i, "#else");
		p(i, "#include <meta/" + m.m_subdir + "/Module.h>");
		p(i, "#endif");
		p(i, "");
		p(i, "#ifndef MUD_MODULES");
		p(i, "#include <meta/" + m.m_subdir + "/Convert.h>");
		p(i, "#endif");
		p(i, "#define " + m.m_preproc_name + "_REFLECTION_IMPL");
		p(i, "#include <meta/" + m.m_subdir + "/Meta.h>");
		p(i, "");
		if(m.m_namespace != "")
		{
			p(i, "namespace " + m.m_namespace);
			p(i, "{");
		}
		p(i, m.m_id + "::" + m.m_id + "()");
		p(i, "\t: Module(\"" + string(m.m_namespace != "" ? m.m_namespace + "::" : "") + m.m_name + "\", { " + deps() + " })");
		p(i, "{");
		p(i, "// setup reflection meta data");
		p(i, m.m_id + "_meta(*this);");
		p(i, "}");
		if(m.m_namespace != "")
			p(i, "}");
		p(i, "");
		p(i, "#ifdef " + m.m_preproc_name + "_MODULE");
		p(i, "extern \"C\"");
		p(i, "Module& getModule()");
		p(i, "{");
		p(i, "	return " + m.m_id + "::m();");
		p(i, "}");
		p(i, "#endif");

		return t;
	}

	string types_h_template(CLModule& m)
	{
		string t;
		auto p = [&](int& i, const string& s) {	write_line(t, i, s, true); };
		int i = 0;

		p(i, "#pragma once");
		p(i, "");
		p(i, "#include <" + m.m_subdir + "/Forward.h>");
		p(i, "");
		p(i, "#if !defined MUD_MODULES || defined MUD_TYPE_LIB");
		p(i, "#include <type/Type.h>");
		p(i, "#include <type/Vector.h>");
		p(i, "#endif");
		p(i, "");
		p(i, "#ifndef MUD_MODULES");
		for(auto& d : m.m_dependencies)
			p(i, "#include <" + d->m_subdir + "/Types.h>");
		p(i, "#endif");
		p(i, "");
		p(i, "#ifndef MUD_CPP_20");
		p(i, "#include <string>");
		p(i, "#include <cstdint>");
		p(i, "#include <vector>");
		p(i, "#endif");
		p(i, "");
		if(m.m_has_structs)
			p(i, "#include <" + m.m_subdir + "/Structs.h>");
		p(i, "");
		p(i, "namespace mud");
		p(i, "{");
		p(i, "// Exported types");
		for(auto& b : m.m_basetypes)
			p(i, "export_ template <> " + m.m_export + " Type& type<" + b->m_name + ">();");
		for(auto& e : m.m_enums)
			if(!e->m_nested || e->m_reflect)
				p(i, "export_ template <> " + m.m_export + " Type& type<" + e->m_id + ">();");
		p(i, "");
		for(auto& c : m.m_classes)
			if(c->m_reflect && !c->m_nested && c->m_id != "mud::Type")
				p(i, "export_ template <> " + m.m_export + " Type& type<" + c->m_id + ">();");
		p(i, "");
		for(auto& c : m.m_classes)
			if(c->m_reflect && !c->m_nested && c->m_id != "mud::Type")
				p(i, "export_ template struct " + m.m_export + " Typed<std::vector<" + c->m_id + "*>>;");
		p(i, "}");

		return t;
	}

	string types_cpp_template(CLModule& m)
	{
		string t;
		auto p = [&](int& i, const string& s) {	write_line(t, i, s, true); };
		int i = 0;

		p(i, "#include <infra/Cpp20.h>");
		p(i, "");
		p(i, "#ifdef MUD_MODULES");
		p(i, "module " + m.m_namespace + "." + m.m_name + ";");
		p(i, "#else");
		p(i, "#include <" + m.m_subdir + "/Types.h>");
		p(i, "#include <" + m.m_subdir + "/Api.h>");
		p(i, "#include <type/Vector.h>");
		p(i, "#endif");
		p(i, "");
		p(i, "namespace mud");
		p(i, "{");
		p(i, "// Exported types");
		for(auto& b : m.m_basetypes)
			p(i, "template <> " + m.m_export + " Type& type<" + b->m_name + ">() { static Type ty(\"" + b->m_name + "\"" + (b->m_name == "void" ? "" : ", sizeof(" + b->m_name + ")") + "); return ty; }");
		for(auto& e : m.m_enums)
			p(i, "template <> " + m.m_export + " Type& type<" + e->m_id + ">() { static Type ty(\"" + e->m_id + "\", sizeof(" + e->m_id + ")); return ty; }");
		p(i, "");
		for(auto& c : m.m_classes)
			if(c->m_reflect && !c->m_nested && c->m_id != "mud::Type")
				p(i, "template <> " + m.m_export + " Type& type<" + c->m_id + ">() { static Type ty(\"" + c->m_name + "\"" + (c->m_bases.size() > 0 ? ", " + type_get(*c->m_bases[0]) : "") + ", sizeof(" + c->m_id + ")); return ty; }");
		p(i, "}");

		return t;
	}

	void amalgam_h_template(CLModule& m)
	{
#if 0
{
	"project": "${ module.namespace }${ module.name }.h",
	"target": "${ module.namespace }${ module.name }.h",
	"sources": [
% for h in module.headers :
		"${ module.subdir }/${ h }"${ "," if not loop.last else "" }
% endfor
	],
	"include_paths": [
		""
	],
	"includes_map": {
% for m in module.dependencies :
		"${ m.name }/": "${ m.namespace }${ m.name }.h"${ "," if not loop.last else "" }
% endfor
	},
	"ignore": [
		"Generated"
	],
	"clean_strings": [
		"//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net",
		"//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.",
		"//  This notice and the license may not be removed or altered from any source distribution.",
		"/* mud */"
	]
}
#endif
	}

	void amalgam_cpp_template(CLModule& m)
	{
#if 0
{
	"project": "${ module.namespace }${ module.name }.cpp",
	"target": "${ module.namespace }${ module.name }.cpp",
	"sources": [
% for s in module.sources :
		"${ module.subdir }/${ s }"${ "," if not loop.last else "" }
% endfor
	],
	"include_paths": [
        ""
	],
    "includes_map": {
		"${ module.name }/": "${ module.namespace }${ module.name }.h"${ "," if len(module.dependencies) > 0 else "" }
% for m in module.dependencies :
		"${ m.name }/": "${ m.namespace }${ m.name }.h"${ "," if not loop.last else "" }
% endfor
    },
	"clean_strings": [
		"//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net",
		"//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.",
		"//  This notice and the license may not be removed or altered from any source distribution.",
		"/* mud */"
	]
}
#endif
	}
}
}
