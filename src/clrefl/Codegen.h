#pragma once

#include <clrefl/Generator.h>

#include <string>
#include <set>

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
	
	std::vector<string> params_types(const CLCallable& f)
	{
		return transform<string>(f.m_params, [](const CLParam& p) { return p.m_type.m_spelling; });
	}

	string params_def(const std::vector<CLParam>& params)
	{
		std::vector<string> decls = transform<string>(params, [](const CLParam& p) { return param_decl(p); });
		return params.size() > 0 ? "{ " + join(decls, ", ") + " }" : "{}";
	}

	string function_signature(const CLCallable& f)
	{
		return f.m_return_type.m_spelling + "(*)(" + join(params_types(f), ", ") + ")";
	}

	string method_signature(const CLMethod& m)
	{
		return m.m_return_type.m_spelling + "(" + m.m_parent->m_id + "::*)(" + join(params_types(m), ", ") + ")" + (m.m_const ? " const" : "");
	}

	string function_identity(const CLCallable& f)
	{
		return "function_id<" + function_signature(f) + ">(&" + f.m_id + ")";
	}
	
	string function_return_def(const CLCallable& f)
	{
		return type_var(f.m_return_type.m_spelling, *f.m_return_type.m_type, f.m_return_type.pointer());
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

	string method_pointer(const CLType& c, const CLMethod& m)
	{
		string pointer = "&" + c.m_id + "::" + m.m_name;
		return m.m_overloaded ? "static_cast<" + method_signature(m) + ">(" + pointer + ")" : pointer;
	}

	string field_identity(const CLType& c, const CLMember& m)
	{
		return m.m_type.reference() ? "Address()" : "member_address(&" + c.m_id + "::" + m.m_member + ")";
	}

	string member_identity(const CLType& c, const CLMember& m)
	{
		return m.m_method ? method_identity(c, *m.m_method) : field_identity(c, m);
	}

	string member_pointer(const CLType& c, const CLMember& m)
	{
		return "&" + c.m_id + "::" + m.m_member;
	}

	string member_getter(const CLType& c, const CLMember& m)
	{
		return "&" + c.m_id + "::" + m.m_member;
	}

	string member_setter(const CLType& c, const CLMember& m)
	{
		return "&" + c.m_id + "::set" + m.m_capname;
	}

	string member_flags(const CLType& c, const CLMember& m)
	{
		UNUSED(c);
		std::vector<string> flags;
		if(m.m_type.pointer()) flags.push_back("Member::Pointer");
		if(m.m_type.m_type->m_struct && !m.m_type.pointer()) flags.push_back("Member::Value");
		if(m.m_nonmutable) flags.push_back("Member::NonMutable");
		if(m.m_structure) flags.push_back("Member::Structure");
		if(m.m_component) flags.push_back("Member::Component");
		if(m.m_link || m.m_type.pointer() || m.m_type.reference()) flags.push_back("Member::Link");
		if(flags.size() == 0) return "Member::None";
		else if(flags.size() == 1) return flags[0];
		else return "Member::Flags(" + join(flags, "|") + ")";
	}
	
	string unused_args(const CLCallable& f)
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

	string member_getfunc(const CLType& c, const CLMember& m)
	{
		if(m.m_method)
			return "[](Ref object) { return Ref(" + string(!m.m_type.pointer() ? "&" : "") + "val<" + c.m_id + ">(object)." + m.m_member + "()); }";
		else if(m.m_type.reference())
			return "[](Ref object) { return Ref(&val<" + c.m_id + ">(object)." + m.m_member + "); }";
		else
			return "nullptr";
	}

	string member_setfunc_explicit(const CLType& c, const CLMember& m)
	{
		if(m.m_setter)
			return "[](Ref object, const Var& v) { val<" + c.m_id + ">(object).set" + m.m_capname + "(val<" + member_type(m) + ">(v)); }";
		else if(!m.m_nonmutable)
			return "[](Ref object, const Var& v) { val<" + c.m_id + ">(object)." + m.m_member + " = val<" + member_type(m) + ">(v); }";
		else
			return "nullptr";
	}

	string member_setfunc(const CLType& c, const CLMember& m)
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
		return type_get(c) + ", [](Ref ref, array<Var> args) { " + unused_args(constr) + "new(&val<" + c.m_id + ">(ref)) " + c.m_id + "( " + get_args(constr.m_params) + " ); }, " + params_def(constr.m_params);
	}

	string copy_constructor_decl(const CLType& c)
	{
		return type_get(c) + ", [](Ref ref, Ref other) { new(&val<" + c.m_id + ">(ref)) " + c.m_id + "(val<" + c.m_id + ">(other)); }";
	}

	string member_decl(const CLType& c, const CLMember& m)
	{
		return type_get(c) + ", " + member_identity(c, m) + ", " + type_get(*m.m_type.m_type) + ", \"" + m.m_name + "\", " + member_default(c, m) + ", " + member_flags(c, m) + ", " + member_getfunc(c, m);
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

	void write_line(string& t, int& i, const string& s, bool spaces = false, bool noendl = false)
	{
		if(s[0] == '}') --i;
		if(t.back() == '\n')
			for(size_t c = 0; c < i; ++c) t += spaces ? "    " : "\t";
		t += s;
		if(!noendl) t += "\n";
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
			p(i, "export_ template <> inline void from_string(const string& str, " + e->m_id + "& val) { val = " + e->m_id + "(enu<" + e->m_id + ">().value(str.c_str())); };");
			p(i, "export_ template <> inline void to_string(const " + e->m_id + "& val, string& str) { str = enu<" + e->m_id + ">().name(uint32_t(val)); };");
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

	string bind_embind_h_template(CLModule& m)
	{
		string t;
		auto p = [&](int& i, const string& s) {	write_line(t, i, s, true); };
		int i = 0;

		p(i, "#include <" + m.m_subdir + "/Api.h>");
		p(i, "#include <emscripten/bind.h>");
		p(i, "");
		p(i, "using namespace emscripten;");
		p(i, "");

		p(i, "EMSCRIPTEN_BINDINGS(" + m.m_id + ")");
		p(i, "{");
		p(i, "");
		p(i, "// Enums");
		for(auto& pe : m.m_enums)
			if(pe->m_reflect)
			{
				CLEnum& e = *pe;
				p(i, "enum_<" + e.m_id + ">(\"" + e.m_id + "\")");
				for(size_t j = 0; j < e.m_ids.size(); ++j)
					p(i, "    .value(\"" + e.m_ids[j] + "\", " + e.m_scoped_ids[j] + ")");
				p(i, "    ;");
			}
		p(i, "");

		p(i, "// Sequences");
		for(auto& ps : m.m_sequences)
		{
			CLSequence& s = *ps;
		}
		p(i, "");

		p(i, "// Arrays");
		for(auto& pc : m.m_classes)
			if(pc->m_reflect && pc->m_array)
			{
				CLClass& c = *pc;
				p(i, "value_array<" + c.m_id + ">(\"" + c.m_name + "\")");
				for(CLMember& m : c.m_members)
					p(i, "    .element(" + member_pointer(c, m) + ")");
				p(i, "    ;");
			}

		p(i, "");

		p(i, "// Structs");
		for(auto& pc : m.m_classes)
			if(pc->m_reflect && !pc->m_array && pc->m_struct)
			{
				CLClass& c = *pc;
				p(i, "value_object<" + c.m_id + ">(\"" + c.m_name + "\")");
				for(CLMember& m : c.m_members)
					p(i, "    .field(\"" + m.m_name + "\", " + member_pointer(c, m) + ")");
				p(i, "    ;");
			}
		p(i, "");

		p(i, "// Classes");
		for(auto& pc : m.m_classes)
			if(pc->m_reflect && !pc->m_array && !pc->m_struct)
			{
				CLClass& c = *pc;
				p(i, "class_<" + c.m_id + ">(\"" + c.m_name + "\")");

				for(CLConstructor& ctor : c.m_constructors)
					p(i, "    .constructor<" + join(params_types(ctor), ", ") + ">()");
				for(CLMember& m : c.m_members)
				{
					if(m.m_method && m.m_setter)
						p(i, "    .property(\"" + m.m_name + "\", " + member_getter(c, m) + ", " + member_setter(c, m) + ")");
					else if(m.m_method)
						p(i, "    .property(\"" + m.m_name + "\", " + member_getter(c, m) + ")");
					else
						p(i, "    .property(\"" + m.m_name + "\", " + member_pointer(c, m) + ")");
				}
				for(CLMethod& m : c.m_methods)
					p(i, "    .function(\"" + m.m_name + "\", " + method_pointer(c, m) + ")");
				for(CLStatic& m : c.m_statics)
					p(i, "    .class_property(\"" + m.m_name + "\", " + "&" + c.m_id + "::" + m.m_name + ")");
				//for(CLFunction& f : c.m_functions)
				//    p(i, "    .class_function(\"" + m.m_name + "\", " + "&" + c.m_id + "::" + f.m_name + ")");

				p(i, "    ;");
			}
		p(i, "");

		p(i, "// Functions");
		for(auto& pf : m.m_functions)
		{
			CLFunction& f = *pf;
			p(i, "function(\"" + f.m_name + "\", " + "&" + f.m_id + ");");
		}
		p(i, "");

		p(i, "}");

		return t;
	}

	string bind_webidl_h_template(CLModule& m)
	{
		string t;
		auto p = [&](int& i, const string& s) {	write_line(t, i, s, true); };
		int i = 0;

		auto idl_quals = [](const CLQualType& type) -> string
		{
			std::vector<string> quals;
			if(type.m_type->m_is_basetype) return "";
			if(type.isconst()) quals.push_back("Const");
			if(type.reference()) quals.push_back("Ref");
			else if(!type.pointer()) quals.push_back("Value");
			return quals.size() > 0 ? "[" + join(quals, ", ") + "] " : "";
		};

		struct CppToIdl { string cpp; string idl; };
		std::vector<CppToIdl> cpp_to_idl;

		auto map = [&](string cpp, string idl) { cpp_to_idl.push_back({ cpp, idl }); };
		map("bool", "boolean");
		map("float", "float");
		map("double", "double");
		map("short", "short");
		map("unsigned short", "short");
		map("uint16_t", "short");
		map("const char*", "DOMString");
		map("std::string", "DOMString");
		for(string cpp : { "int", "long", "long long" })
			map(cpp, "long");
		for(string cpp : { "unsigned int", "unsigned long", "unsigned long long"  })
			map(cpp, "long");
		for(string cpp : { "uint32_t", "size_t" })
			map(cpp, "long");

		auto idl_type = [&](const CLQualType& type) -> string { for(auto& ctoi : cpp_to_idl) { if(type.m_spelling == ctoi.cpp) return ctoi.idl; } return type.m_type->m_name;  };
		auto idl_qual_type = [&](const CLQualType& type) -> string { return idl_quals(type) + type.m_type->m_name;  };
		auto params_types_idl = [&](const CLCallable& f) -> std::vector<string> { return transform<string>(f.m_params, [&](const CLParam& p) { return idl_qual_type(p.m_type); }); };

		p(i, "// Enums");
		for(auto& pe : m.m_enums)
			if(pe->m_reflect)
			{
				CLEnum& e = *pe;
				p(i, "enum " + replace(e.m_id, "::", "_") + "{");
				for(size_t j = 0; j < e.m_ids.size(); ++j)
					p(i, "\"" + replace(e.m_scoped_ids[j], "::", "_") + "\"");
				p(i, "};");
			}
		p(i, "");

		p(i, "// Sequences");
		for(auto& ps : m.m_sequences)
		{
			CLSequence& s = *ps;
		}
		p(i, "");

		p(i, "// Classes");
		for(auto& pc : m.m_classes)
			if(pc->m_reflect && !pc->m_is_templated)
			{
				CLClass& c = *pc;
				if(c.m_parent->m_prefix != "")
					p(i, "[Prefix=\"" + c.m_parent->m_prefix + "\"]");
				p(i, "interface " + c.m_name + " {");

				for(CLConstructor& ctor : c.m_constructors)
					p(i, "void " + c.m_name + "(" + join(params_types_idl(ctor), ", ") + ");");
				for(CLMember& m : c.m_members)
				{
					if(!m.m_method)
						p(i, idl_quals(m.m_type) + "attribute " + idl_type(m.m_type) + " " + m.m_name + ";");
					else
						p(i, idl_type(m.m_type) + " " + m.m_name + "();");
					if(m.m_setter)
						p(i, "void set" + m.m_capname + "(" + idl_type(m.m_type) + ");");
				}
				for(CLMethod& m : c.m_methods)
					p(i, idl_type(m.m_return_type) + " " + m.m_name + "(" + join(params_types_idl(m), ", ") + ");");
				for(CLStatic& m : c.m_statics)
					;
				//for(CLFunction& f : c.m_functions)
				//    ;

				p(i, "};");
			}
		p(i, "");

		p(i, "// Functions");
		for(auto& pf : m.m_functions)
		{
			CLFunction& f = *pf;
			p(i, "void " + f.m_name + "(" + join(params_types_idl(f), ", ") + ");");
		}
		p(i, "");

		return t;
	}

	string amalgam_h_template(CLModule& m)
	{
		string t;
		auto p = [&](int& i, const string& s) {	write_line(t, i, s, true); };
		int i = 0;
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
		return t;
	}

	export_ template <class T>
	inline std::vector<T> vector_slice(const std::vector<T>& vector, size_t begin, size_t end)
	{
		std::vector<T> result;
		for(size_t i = begin; i < end; ++i)
			result.push_back(vector[i]);
		return result;
	}

	string amalgam_cpp_template(CLModule& m)
	{
		string t;
		auto p = [&](int& i, const string& s) {	write_line(t, i, s, true); };
		int i = 0;
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
		return t;
	}

	string js_namespace_path(const CLModule& m, const CLPrimitive& n)
	{
		if(n.m_name != "" && n.m_name != m.m_namespace)
			return js_namespace_path(m, *n.m_parent) + "['" + n.m_name + "']";
		else
			return "";
	};

	void bind_javascript(CLModule& m)
	{
		// @todo:
		// - vectors
		// - array types
		// - noncopy types
		// - pointer types (mud::Ref)
		// - handle types
		// - references to strings

		// not implemented yet
		std::vector<string> blacklist = { "std::vector", "array", "mud::Ref" };

		auto blacklist_type = [&](const CLQualType& t) { for(const string& n : blacklist) { if(t.m_spelling.find(n) != string::npos) return true; } if(t.isstring() && t.reference() && !t.isconst()) return true; return false; };
		auto blacklist_callable = [&](const CLCallable& f) { for(const CLParam& p : f.m_params) if(blacklist_type(p.m_type)) return true; if(blacklist_type(f.m_return_type)) return true; return false; };
		auto blacklist_member = [&](const CLMember& m) { if(blacklist_type(m.m_type)) return true; return false; };

		string module_js;

		string ct;
		string jst;

		int ci = 0;
		int jsi = 0;

		auto cw = [&](const string& s) { write_line(ct, ci, s); };
		auto jsw = [&](const string& s, bool noendl = false) { write_line(jst, jsi, s, true, noendl); };

		for(CLModule* d : m.m_modules)
			cw("#include <" + d->m_subdir + "/Api.h>");
		cw("");
		cw("#ifdef MUD_PLATFORM_EMSCRIPTEN");
		cw("#include <emscripten.h>");
		cw("#define DECL EMSCRIPTEN_KEEPALIVE");
		cw("#else");
		cw("#define DECL");
		cw("#endif");
		cw("");
		cw("");
		cw("extern \"C\" {");
		cw("");

#if 0
		cw("// Not using size_t for array indices as the values used by the javascript code are signed.");
		cw("void array_bounds_check(const int array_size, const int array_idx) {");
		cw("  if (array_idx < 0 || array_idx >= array_size) {");
		cw("    EM_ASM({");
		cw("      throw 'Array index ' + $0 + ' out of bounds: [0,' + $1 + ')';");
		cw("    }, array_idx, array_size);");
		cw("  }");
		cw("}");
#endif

		//js_constructor("WrapperObject");

		//jsw(module_js);

		auto address = [](const CLQualType& t) -> string {
			return (!t.isbasetype() && !t.isenum()) && (t.reference() || t.value()) ? "&" : "";
		};

		auto value = [](const CLQualType& t) -> string {
			return (!t.isbasetype() && !t.isenum()) && (t.reference() || t.value()) ? "*" : "";
		};

		auto type_to_c = [&](const CLQualType& t, bool non_pointing = false) -> string
		{
			if(t.isstring()) return "const char*";
			if(t.isenum()) return t.m_type->m_id;
			string name = !t.isbasetype() ? t.m_type->m_id + (non_pointing ? "" : "*") : t.m_type->m_name;
			return (t.isconst() && name != "const char*" ? "const " : "") + name + (t.isarray() ? "[]" : "");
		};

		/*auto type_to_cdec = [&](const CLQualType& raw)
		{
			string ret;
			string name = ret = type_to_c(raw.m_type->m_name, true);
			if(raw.isconst()) ret = "const " + ret;
			//if name not in interfaces: return ret
			if(raw.reference()) return ret + "&";
			if(raw.value()) return ret;
			return ret + "*";
		};*/

		string js_impl_methods;

		//string bind_prefix = "emscripten_bind_";
		string bind_prefix = "";

		auto clean_name = [&](const string& name) { return replace(replace(replace(name, "::", "_"), "<", "_"), ">", "_"); };
		auto binding_name_str = [&](const CLPrimitive& parent, const string& name) { return bind_prefix + replace(parent.m_id, "::", "_") + "_" + name; };
		auto binding_name = [&](const CLCallable& f) { return binding_name_str(*f.m_parent, clean_name(f.m_name)); };
		auto binding_name_n = [&](const CLCallable& f, size_t i) { return  binding_name(f) + "_" + to_string(i); };

		struct Overloads { const CLCallable* f; std::set<size_t> lengths; };
		using OverloadMap = std::map<string, Overloads>;

		auto cramfunc = [](Overloads& o, const CLCallable& f)
		{
			o.f = &f;
			for(size_t i = f.m_min_args; i <= f.m_params.size(); ++i)
				o.lengths.insert(i);
		};

		auto overload = [&](OverloadMap& overloads, const CLCallable& f)
		{
			if(overloads.find(f.m_name) == overloads.end())
			{
				cramfunc(overloads[f.m_name], f);
				return;
			}

			Overloads& o = overloads[f.m_name];
			bool clashes = false;
			for(size_t i = 0; i < o.f->m_params.size(); ++i)
				if(i < f.m_params.size() && f.m_params[i].m_type != o.f->m_params[i].m_type)
					clashes = true;
			for(size_t i = f.m_min_args; i < f.m_params.size(); ++i)
				if(o.lengths.find(i) != o.lengths.end())
					clashes = true;
			if(!clashes && f.m_params.size() > o.f->m_params.size())
				cramfunc(o, f);
			else
				printf("WARNING: can't bind %s%s (can only overload signatures of same types and different lengths)\n", f.m_parent->m_id.c_str(), f.m_name.c_str());
		};

		auto call_args = [](const CLCallable& f, size_t n)
		{
			std::vector<string> params = transform<string>(0, n, [&](size_t i) { return f.m_params[i].m_name; });
			bool method = f.m_kind == CLPrimitiveKind::Method;
			return vector_union((method ? std::vector<string>{ "self" } : std::vector<string>()), params);
		};

		auto js_namespace = [&](const CLPrimitive& n)
		{
			string path = "Module" + js_namespace_path(m, n);
			jsw(path + " = " + path + " || {};");
		};

		auto js_module_path = [&](const CLModule& m, const CLPrimitive& p)
		{
			return "Module" + js_namespace_path(m, p);
		};

		auto js_call_inner = [&](const CLCallable& f, size_t n)
		{
			return "_" + binding_name_n(f, n) + "(" + join(call_args(f, n), ", ") + ")";
		};

		auto js_call_return_wrap = [&](const CLQualType& return_type, const string& call)
		{
			if(return_type.isclass())
				return "return wrapPointer(" + call + ", " + return_type.m_type->m_name + ");";
			else if(return_type.iscstring() || return_type.isstring())
				return "return Pointer_stringify(" + call + ");";
			else if(return_type.isboolean())
				return "return !!(" + call + ");";
			else if(!return_type.isvoid())
				return "return " + call + ";";
			else
				return call + ";";
		};

		auto js_call_statement = [&](const CLCallable& f, size_t n)
		{
			if(f.m_kind == CLPrimitiveKind::Constructor)
				return js_call_inner(f, n) + ";";
			else
				return js_call_return_wrap(f.m_return_type, js_call_inner(f, n));
		};

		auto js_wrap_optional_call = [&](const CLCallable& f, size_t n, const string& call)
		{
			if(n < f.m_params.size())
				jsw("if (" + f.m_params[n].m_name + " === undefined) { " + call + (f.m_return_type.isvoid() ? " return;" : "") + " }");
			else
				jsw(call);
		};

		auto js_call_n = [&](const CLCallable& f, size_t n)
		{
			string call = f.m_kind == CLPrimitiveKind::Constructor
				? "this.ptr = " + js_call_statement(f, n) + " getCache(" + f.m_parent->m_name + ")[this.ptr] = this;"
				: js_call_statement(f, n);
			return js_wrap_optional_call(f, n, call);

		};

		auto js_call = [&](const Overloads& o)
		{
			for(size_t i : o.lengths)
				js_call_n(*o.f, i);
		};

		auto js_call_prepare = [&](const CLCallable& f)
		{
			bool prepare = false;
			for(const CLParam& p : f.m_params)
				if(p.m_type.iscstring() || p.m_type.isstring() || p.m_type.isarray())
					prepare = true;
			if(prepare)
				jsw("ensureCache.prepare();");

		};

		auto js_check_msg = [](const CLClass& c, const CLCallable& f, const CLParam& p)
		{
			return "[CHECK FAILED] " + c.m_name + "::" + f.m_name + "(arg" + to_string(p.m_index) + ":" + p.m_name + "): ";
		};

		auto js_call_check_arg = [&](const CLQualType& t, const string& a)
		{
			string msg = "";// js_check_msg(c, f, p);
			bool optional = false;
			if(optional) jsw("if(typeof " + a + " !== \"undefined\" && " + a + " !== null) {");

			if(t.isinteger())
				jsw("assert(typeof " + a + " === \"number\" && !isNaN(" + a + "), \"" + msg + "Expecting <integer>\");");
			else if(t.isfloat())
				jsw("assert(typeof " + a + " === \"number\", \"" + msg + "Expecting <number>\");");
			else if(t.isboolean())
				jsw("assert(typeof " + a + " === \"boolean\" || (typeof " + a + " === \"number\" && !isNaN(" + a + ")), \"" + msg + "Expecting <boolean>\");");
			else if(t.iscstring() || t.isstring())
				jsw("assert(typeof " + a + " === \"string\" || (" + a + " && typeof " + a + " === \"object\" && typeof " + a + ".ptr === \"number\"), \"" + msg + "Expecting <string>\");");
			else if(t.isclass())
				jsw("assert(typeof " + a + " === \"object\" && typeof " + a + ".ptr === \"number\", \"" + msg + "Expecting <pointer>\");");

			if(optional) jsw("}");
		};

		auto js_convert_arg_default = [&](const CLQualType& t, const string& a)
		{
			bool array_attribute = false;
			if(!(t.isarray() && !array_attribute))
			{
				jsw("if (" + a + " && typeof " + a + " === \"object\") " + a + " = " + a + ".ptr;");
				if(t.iscstring() || t.isstring())
					jsw("else " + a + " = ensureString(" + a + ");");
			}
			else
			{
				// an array can be received here
				string arg_type = t.m_type->m_name;
				if(arg_type == "char" || arg_type == "unsigned char")
					jsw("if (typeof " + a + " == \"object\") {{ " + a + " = ensureInt8(" + a + "); }}");
				else if(arg_type == "short" || arg_type == "unsigned short")
					jsw("if (typeof " + a + " == \"object\") {{ " + a + " = ensureInt16(" + a + "); }}");
				else if(arg_type == "int", "unsigned int")
					jsw("if (typeof " + a + " == \"object\") {{ " + a + " = ensureInt32(" + a + "); }}");
				else if(arg_type == "float")
					jsw("if (typeof " + a + " == \"object\") {{ " + a + " = ensureFloat32(" + a + "); }}");
				else if(arg_type == "double")
					jsw("if (typeof " + a + " == \"object\") {{ " + a + " = ensureFloat64(" + a + "); }}");
			}
		};

		auto js_call_convert_arg = [&](const CLQualType& t, const string& a, bool optional = false)
		{
			string inner = "";

			jsw("/* " + a + " <" + t.m_type->m_name + "> [" + inner + "] */");

			if(bool checks = false)
				js_call_check_arg(t, a);

			if(t.iscstring() || t.isstring())
			{	
				js_convert_arg_default(t, a); // legacy path is fast enough for strings.
			}
			else if(t.isclass())
			{
				if(optional)
					jsw("if(typeof " + a + " !== \"undefined\" && " + a + " !== null) {{ " + a + " = " + a + ".ptr }};");
				else
					jsw(a + " = " + a + ".ptr;"); // No checks in fast mode when the arg is required
			}
			else if(!t.isbasetype())
			{
				js_convert_arg_default(t, a);
			}
		};

		auto js_call_convert_args = [&](const CLCallable& f)
		{
			for(const CLParam& p : f.m_params)
				js_call_convert_arg(p.m_type, p.m_name, p.m_index > f.m_min_args);
		};

		// We need to avoid some closure errors on the constructors we define here.
		//string js_supress = "/** @suppress {undefinedVars, duplicate} */ ";
		string js_supress = "";

		auto js_bind_callable = [&](const Overloads& o)
		{
			const CLCallable& f = *o.f;
			bool ctor = f.m_kind == CLPrimitiveKind::Constructor;
			if(f.m_kind == CLPrimitiveKind::Method)
				jsw(f.m_parent->m_name + ".prototype[\"" + f.m_name + "\"] = " + f.m_parent->m_name + ".prototype." + f.m_name + " = ", true);
			else if(f.m_kind == CLPrimitiveKind::Function)
				jsw(js_module_path(m, f) + " = ", true);
			jsw(js_supress + "function" + (ctor ? " " + f.m_name : "") + "(" + join(call_args(f, f.m_params.size()), ", ") + ") {");
			if(!ctor) 
				jsw("var self = this.ptr;");
			js_call_prepare(f);
			js_call_convert_args(f);
			js_call(o);
			jsw("};");
		};

		auto js_getter = [&](const CLClass& c, const CLMember& m)
		{
			jsw("function() {");
			jsw("var self = this.ptr;");
			jsw(js_call_return_wrap(m.m_type, "_" + binding_name_str(c, "_get_" + m.m_name) + "(self)"));
			jsw("}", true);
		};

		auto js_setter_array = [&]()
		{};

		auto js_setter = [&](const CLClass& c, const CLMember& m)
		{
			jsw("function(value) {");
			jsw("var self = this.ptr;");
			js_call_convert_arg(m.m_type, "value", false);
			jsw("_" + binding_name_str(c, "_set_" + m.m_name) + "(self, value);");
			jsw("}");
		};

		auto js_destructor = [&](const CLClass& c)
		{
			jsw("function() {");
			jsw("var self = this.ptr;");
			jsw("_" + binding_name_str(c, "_destroy") + "(self);");
			jsw("};");
		};

		auto js_constructor = [&](const CLClass& c)
		{
			string implementing = "WrapperObject"; // = implements[name][0] if implements.get(name) else 'WrapperObject'
			jsw(c.m_name + ".prototype = Object.create(" + implementing + ".prototype);");
			jsw(c.m_name + ".prototype.constructor = " + c.m_name + ";");
			jsw(c.m_name + ".prototype.__class__ = " + c.m_name + ";");
			jsw(c.m_name + ".__cache__ = {};");
			jsw(js_module_path(m, c) + " = " + c.m_name + ";");
		};

		auto js_function = [&](const Overloads& o)
		{
			js_bind_callable(o);
		};

		auto c_call_args_n = [&](const CLCallable& f, size_t i)
		{
			return transform<string>(0, i, [&](size_t i) { return value(f.m_params[i].m_type) + f.m_params[i].m_name; });
		};

		auto c_call_n = [&](const CLCallable& f, size_t i)
		{
			if(f.m_kind == CLPrimitiveKind::Constructor)
				return "new " + f.m_parent->m_id + "(" + join(c_call_args_n(f, i), ", ") + ")";
			else if(f.m_kind == CLPrimitiveKind::Method)
				return "self->" + f.m_name + "(" + join(c_call_args_n(f, i), ", ") + ")";
			else if(f.m_kind == CLPrimitiveKind::Function)
				return f.m_id + "(" + join(c_call_args_n(f, i), ", ") + ")";
		};

		auto c_call_operator_n = [&](const CLCallable& f, size_t i, const string& op)
		{
			string cast_self = "self";
			string maybe_deref = value(f.m_params[0].m_type);
			if(op.find("=") != string::npos)
				cw("(*" + cast_self + ") " + op + " " + maybe_deref + f.m_params[0].m_name);
			else if(op == "[]")
				cw("((*" + cast_self + ")[" + maybe_deref + f.m_params[0].m_name + "])");
			else
				printf("ERROR: unfamiliar operator %s\n", op.c_str());
		};

		auto c_call_return_wrap = [&](const CLQualType& return_type, const string& call, bool ctor = false)
		{
			if(ctor)
				cw("return " + call + ";");
			else if(return_type.isvoid())
				cw(call + ";");
			else if(return_type.isstring())
				cw("return " + call + ".c_str();");
			else if(return_type.isbasetype() || return_type.isenum())
				cw("return " + call + ";");
			else if(!return_type.value() || !return_type.copyable())
				cw("return " + address(return_type) + call + ";");
			else
			{
				cw("static " + return_type.m_type->m_id + " temp;");
				cw("return (temp = " + call + ", &temp);");
			}
		};

		auto c_call_wrapped_n = [&](const CLCallable& f, size_t i)
		{
			c_call_return_wrap(f.m_return_type, c_call_n(f, i), f.m_kind == CLPrimitiveKind::Constructor);
		};

		auto c_binding_args = [&](const CLCallable& f, size_t i)
		{
			std::vector<string> c_arg_types = transform<string>(f.m_params, [&](const CLParam& p) { return type_to_c(p.m_type); });
			return join(transform<string>(0, i, [&](size_t i) { return c_arg_types[i] + " " + f.m_params[i].m_name; }), ", ");
		};

		auto c_callable_args = [&](const CLCallable& f, size_t i)
		{
			if(f.m_kind == CLPrimitiveKind::Constructor || f.m_kind == CLPrimitiveKind::Function)
				return c_binding_args(f, i);
			else if(f.m_kind == CLPrimitiveKind::Method)
				return f.m_parent->m_id + "* self" + (i > 0 ? ", " + c_binding_args(f, i) : "");
		};

		auto c_binding_body = [&]()
		{

		};

		auto c_bind_callable_n = [&](const CLCallable& f, size_t i)
		{
			//if(array_attribute)
			//  sig = [x.replace("[]", "") for x in sig] // for arrays, ignore that this is an array - our get/set methods operate on the elements

			string maybe_const = f.m_return_type.isconst() ? "const " : "";
			if(f.m_kind != CLPrimitiveKind::Constructor)
				cw(maybe_const + type_to_c(f.m_return_type) + " DECL " + binding_name_n(f, i) + "(" + c_callable_args(f, i) + ") {");
			else
				cw(f.m_parent->m_id + "* DECL " + binding_name_n(f, i) + "(" + c_callable_args(f, i) + ") {");

			c_call_wrapped_n(f, i);
			cw("}");

			/*if(!ctor)
				if(i == max_args)
				{
					std::vector<string> C_FLOATS = { "float", "double" };

					string dec_args = join(transform<string>(0, i, [&](size_t j) { return type_to_cdec(raw[j]->m_type) + ' ' + args[j]; }), ", "); ;
					string js_call_args = join(transform<string>(0, i, [&](size_t j) { return (is_interface(sig[j]) ? "(int)" : "") + take_addr_if_nonpointer(raw[j]->m_type) + args[j]; }), ", ");

					js_impl_methods += "  " + c_return_type + " " + func_name + "(" + dec_args + ") " + maybe_const + " {";
					js_impl_methods += basic_return + "EM_ASM_" + (!vector_has(C_FLOATS, c_return_type) ? "INT" : "DOUBLE") + "({";
					js_impl_methods += "var self = Module['getCache'](Module['" + class_name + "'])[$0];";
					js_impl_methods += "if (!self.hasOwnProperty('" + func_name + "')) throw 'a JSImplementation must implement all functions, you forgot " + class_name + "::" + func_name + ".';";
					js_impl_methods += "return " + return_prefix + "self['" + func_name + "'](" + join(transform<string>(1, max_args + 1, [](size_t i) { return "$" + to_string(i); }), ", ") + ")" + return_postfix + ";";
					js_impl_methods += "}, (int)this" + string(js_call_args.size() > 0 ? ", " : "") + js_call_args + ");";
				}*/
		};

		auto c_bind_callable = [&](const Overloads& o)
		{
			const CLCallable& f = *o.f;
			for(size_t i : o.lengths)
				c_bind_callable_n(f, i);
		};

		auto c_getter_array = [&](const CLClass& c, const CLMember& m)
		{
			return address(m.m_type) + "self->" + m.m_member + "[index];";
		};

		auto c_setter_array = [&](const CLClass& c, const CLMember& m)
		{
			return "self->" + m.m_member + "[index] = " + value(m.m_type) + "value;";
		};

		auto c_getter = [&](const CLClass& c, const CLMember& m)
		{
			cw(type_to_c(m.m_type) + " DECL " + binding_name_str(c, "_get_" + m.m_name) + "(" + c.m_id + "* self) {");
			c_call_return_wrap(m.m_type, "self->" + m.m_member + (m.m_method ? "()" : ""));
			cw("}");
		};

		auto c_setter = [&](const CLClass& c, const CLMember& m)
		{
			cw("void DECL " + binding_name_str(c, "_set_" + m.m_name) + "(" + c.m_id + "* self, " + type_to_c(m.m_type) + " value) {");
			if(m.m_setter)
				cw("self->" + m.m_member + "(" + value(m.m_type) + "value);");
			else
				cw("self->" + m.m_member + " = " + value(m.m_type) + "value;");
			cw("}");
		};

		auto c_destructor = [&](const CLClass& c)
		{
			cw("void DECL " + binding_name_str(c, "_destroy") + "(" + c.m_id + "* self) {");
			cw("delete self;");
			cw("}");
		};


/*for name, interface in interfaces.items():
  js_impl = interface.getExtendedAttribute('JSImplementation')
  if not js_impl: continue
  implements[name] = [js_impl[0]]*/

		for(auto& pair : m.m_context.m_namespaces)
		{
			CLNamespace& n = *pair.second;
			if(n.m_reflect_content && n.m_name != m.m_namespace)
				js_namespace(*pair.second);
		}

		for(auto& pc : m.m_classes)
			if(pc->m_reflect && !pc->m_is_templated)
			{
				CLClass& c = *pc;
				string interface = c.m_name;

				jsw("// " + c.m_name);
				cw("// " + c.m_name);

				//js_impl_methods = "";

				//js_impl = interface.getExtendedAttribute('JSImplementation')
				//if js_impl:
				//  js_impl = js_impl[0]

				OverloadMap constructors;

				for(CLConstructor& ctor : c.m_constructors)
				{
					overload(constructors, ctor);
				}

				for(auto& pairs : constructors)
				{
					Overloads& o = pairs.second;
					c_bind_callable(o);
					js_bind_callable(o);
				}

				if(c.m_constructors.empty())
				{
					// Ensure a constructor even if one is not specified.
					jsw(js_supress + "function " + c.m_name + "() { throw \"cannot construct a " + c.m_name + ", no constructor in IDL\" }");
				}

				js_constructor(c);

				OverloadMap methods;

				for(CLMethod& m : c.m_methods)
				{
					if(blacklist_callable(m)) continue;
					overload(methods, m);
				}

				for(auto& pairs : methods)
				{
					Overloads& o = pairs.second;
					c_bind_callable(o);
					js_bind_callable(o);
				}

				for(CLMember& m : c.m_members)
				{
					if(blacklist_member(m)) continue;
					if(m.m_type.m_type->m_is_templated) continue;
					if(m.m_type.value() && m.m_type.m_type->m_move_only) continue;

					if(m.m_type.isarray()) continue;
					{
						//get_sigs[1] = [Dummy({ "type": WebIDL.BuiltinTypes[WebIDL.IDLBuiltinType.Types.long] })];
						//set_sigs[2] = [Dummy({ "type": WebIDL.BuiltinTypes[WebIDL.IDLBuiltinType.Types.long] }),
						//               Dummy({ "type": m.type })];

						//if m.getExtendedAttribute("BoundsChecked"):
						//  bounds_check = "array_bounds_check(sizeof(self->%s) / sizeof(self->%s[0]), arg0)" % (attr, attr)
						//  get_call_content = "(%s, %s)" % (bounds_check, get_call_content)
						//  set_call_content = "(%s, %s)" % (bounds_check, set_call_content)
					}

					c_getter(c, m);
					if(!m.m_nonmutable)
						c_setter(c, m);

					jsw("Object.defineProperty(" + c.m_name + ".prototype, \"" + m.m_name + "\", {");
					jsw("get: ", true);
					js_getter(c, m);
					if(!m.m_nonmutable)
					{
						jsw(",");
						jsw("set: ", true);
						js_setter(c, m);
					}
					jsw("});");
				}


				if(true) //not interface.getExtendedAttribute("NoDelete"):
				{
					c_destructor(c);
					jsw(c.m_name + ".prototype[\"__destroy__\"] = " + c.m_name + ".prototype.__destroy__ = ", true);
					js_destructor(c);
				}
				
				// Emit C++ class implementation that calls into JS implementation

				/*if(js_impl != "")
				{
					pre_c += "\n";
					pre_c += "class " + c.m_name + " : public " + type_to_c(js_impl, true) + " {";
					pre_c += "public:";
					pre_c += join(js_impl_methods, "\n");
					pre_c += "};";
				}*/
			}

			OverloadMap functions;

			for(auto& pf : m.m_functions)
			{
				if(blacklist_callable(*pf)) continue;
				overload(functions, *pf);
			}

			for(auto& pairs : functions)
			{
				Overloads& o = pairs.second;
				c_bind_callable(o);
				js_bind_callable(o);
			}

			jsw("");
			jsw("(function() {");
			jsw("function setupEnums() {");
			
			//string enum_prefix = "emscripten_enum_";
			string enum_prefix = "";

			for(auto& pe : m.m_enums)
			{
				CLEnum& e = *pe;
				cw("// " + e.m_name);
				jsw("// " + e.m_name);
				if(e.m_scoped)
					js_namespace(e);
				for(size_t i = 0; i < e.m_ids.size(); ++i)
				{
					string f = enum_prefix + replace(e.m_id, "::", "_") + "_" + e.m_ids[i];
					cw(e.m_id + " DECL " + f + "() {");
					cw("return " + e.m_scoped_ids[i] + ";");
					cw("}");

					jsw(js_module_path(m, e.m_scoped ? e : *e.m_parent) + "['" + e.m_ids[i] + "'] = _" + f + "();");
				}
			}

			jsw("}");
			jsw("if (Module['calledRun']) setupEnums();");
			jsw("else addOnPreMain(setupEnums);");
			jsw("})();");

			cw("\n}\n\n");

			write_file((m.m_bind_path + "\\" + "c.cpp").c_str(), ct.c_str());
			write_file((m.m_bind_path + "\\" + "js.js").c_str(), jst.c_str());
	}
}
}
