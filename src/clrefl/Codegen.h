#pragma once

#include <clrefl/Generator.h>

#include <string>

using std::string;

namespace mud
{
namespace clgen
{
	template <class U, class T, class F>
	std::vector<U> transform(const std::vector<T>& vector, F func)
	{
		std::vector<U> result;
		for(const T& value : vector)
			result.push_back(func(value));
		return result;
	}

	//string join(array<string> strings, string separator)
	string join(const std::vector<string>& strings, string separator)
	{
		if(strings.size() == 0) return "";
		string result;
		for(const string& s : strings)
		{
			result += s;
			result += separator;
		}
		result.erase(result.size() - separator.size(), separator.size());
		return result;
	}

	std::vector<string> location(const CLPrimitive& e)
	{
		if(e.m_parent->m_id == "") return {};
		else return split_string(e.m_parent->m_id, "::");
	}
	
#if 0
def namespace_begin(n):
    if n.name != '' :
        return namespace_begin(n.parent) + 'namespace ' + n.name + ' {\n'
    else:
        return ''
    
def namespace_end(n):
    if n.name != '' :
        return namespace_end(n.parent) + '}\n'
    else:
        return ''
#endif

	string namespace_begin(const CLNamespace& e)
	{
		string str = "";
		const CLPrimitive* n = &e;
		while(n->m_parent && n->m_parent->m_name != "")
		{
			str += "namespace {\n";
			n = n->m_parent;
		}
		return str;
	}

	string namespace_end(const CLNamespace& e)
	{
		string str = "";
		const CLPrimitive* n = &e;
		while(n->m_parent && n->m_parent->m_name != "")
		{
			str += "}\n";
			n = n->m_parent;
		}
		return str;
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
   
	string param_default(const CLParam& param)
	{
		return type_var(param.m_cls->m_id, *param.m_cls, param.m_pointer, param.m_default);
	}

	string param_refget(const CLParam& param, size_t index)
	{
		if(param.m_cls->m_id == "mud::Ref")
			return "args[" + to_string(index) + "]";
		else if(param.m_pointer)
			return "&val<" + param.m_cls->m_id + ">(args[" + to_string(index) + "])";
		else
			return "val<" + param.m_cls->m_id + ">(args[" + to_string(index) + "])";
	}
	
	string param_forward(const CLParam& param, size_t index)
	{
		bool unique = param.m_type.find("unique_ptr") != string::npos || param.m_type.find("object_ptr") != string::npos;
		return unique ? "std::move(" + param_refget(param, index) + ")" : param_refget(param, index);
	}

	string param_flags(const CLParam& param)
	{
		std::vector<string> flags;
		if(param.m_nullable) flags.push_back("Param::Nullable");
		if(param.m_output) flags.push_back("Param::Output");
		if(param.m_has_default) flags.push_back("Param::Default");
		if(flags.size() == 0) return "";
		else if(flags.size() == 1) return ", " + flags[0];
		else return ", Param::Flags(" + join(flags, "|") + ")";
	 }

	string param_decl(const CLParam& param)
	{
		return "{ "" + param.name + "", " + param_default(param) + param_flags(param) + " }";
	}
	
	string function_signature(const CLFunction& func)
	{
		std::vector<string> types;
		for(const CLParam& param : func.m_params)
			types.push_back(param.m_type);
		return func.m_returnType + "(*)(" + join(types, ", ") + ")";
	}

	string function_identity(const CLFunction& func)
	{
		return "function_id<" + function_signature(func) + ">(&" + func.m_id + ")";
	}
	
	string function_return_def(const CLFunction& func)
	{
		return type_var(func.m_returnType, *func.m_returnCls, func.m_returnPointer);
	}

	string params_def(const std::vector<CLParam>& params)
	{
		// [param_decl(param) for param in params]
		std::vector<string> decls;
		for(const CLParam& param : params)
			decls.push_back(param_decl(param));
		return params.size() > 0 ? "{ " + join(decls, ", ") + " }" : "{}";
	}

	string get_args(const std::vector<CLParam>& params)
	{
		std::vector<string> decls;
		for(const CLParam& param : params)
			decls.push_back(param_forward(param, param.m_index));
		return join(decls, ", ");
	}

	string method_identity(const CLType& c, const CLMethod& method)
	{
		return "member_address(&" + c.m_id + "::" + method.m_name + ")";
	}

	string field_identity(const CLType& c, const CLMember& member)
	{
		return member.m_reference ? "Address()" : "member_address(&" + c.m_id + "::" + member.m_member;
	}

	string member_identity(const CLType& c, const CLMember& member)
	{
		return member.m_function ? method_identity(c, *member.m_function) : field_identity(c, member);
	}
	
	string member_flags(const CLType& c, const CLMember& member)
	{
		UNUSED(c);
		std::vector<string> flags;
		if(member.m_pointer) flags.push_back("Member::Pointer");
		if(member.m_cls->m_struct && !member.m_pointer) flags.push_back("Member::Value");
		if(member.m_nonmutable || member.m_reference) flags.push_back("Member::NonMutable");
		if(member.m_structure) flags.push_back("Member::Structure");
		//if(member.m_component) flags.push_back("Member::Component");
		if(member.m_link || member.m_pointer || member.m_reference) flags.push_back("Member::Link");
		if(flags.size() == 0) return "Member::None";
		else if(flags.size() == 1) return flags[0];
		else return "Member::Flags(" + join(flags, "|") + ")";
	}
	
	string unused_args(const CLFunction& func)
	{
		return func.m_params.size() == 0 ? "UNUSED(args);" : "";
	}

	string type_class(const CLType& c)
	{
		if(c.m_struct)
			return "TypeClass::Struct";
		//else if(c.isModular)
		//	return "TypeClass::Complex";
		else
			return "TypeClass::Object";
	}

	string member_type(const CLMember& member)
	{
		return member.m_cls->m_id + (member.m_pointer ? "*" : "");
	}

	string member_getter(const CLType& c, const CLMember& member)
	{
		if(member.m_function)
			return "[](Ref object) { return Ref(" + string(!member.m_pointer ? "&" : "") + "val<" + c.m_id + ">(object)." + member.m_member + "()); }";
		else if(member.m_reference)
			return "[](Ref object) { return Ref(&val<" + c.m_id + ">(object)." + member.m_member + "); }";
		else
			return "nullptr";
	}

	string member_setter_explicit(const CLType& c, const CLMember& member)
	{
		if(member.m_setter)
			return "[](Ref object, const Var& v) { val<" + c.m_id + ">(object).set" + member.m_capname + "(val<" + member_type(member) + ">(v)); }";
		else if(!member.m_nonmutable)
			return "[](Ref object, const Var& v) { val<" + c.m_id + ">(object)." + member.m_member + " = val<" + member_type(member) + ">(v); }";
		else
			return "nullptr";
	}

	string member_setter(const CLType& c, const CLMember& member)
	{
		if(member.m_setter)
			return "member_setter<" + member_type(member) + ">(&" + c.m_id + "::set" + member.m_capname + ")";
		else if(!member.m_nonmutable)
			return "member_setter<" + member_type(member) + ">(&" + c.m_id + "::" + member.m_member + ")";
		else
			return "nullptr";
	}

	string member_default(const CLType& c, const CLMember& member)
	{
		UNUSED(c);
		if(member.m_cls->m_struct && !member.m_pointer)
			return "var(" + member_type(member) + "(" + member.m_default + "))";
		else
			return "Ref(" + type_get(*member.m_cls) + ")";
	}

	string method_func(const CLType& c, const CLMethod& method)
	{
		string call = "val<" + c.m_id + ">(object)." + method.m_name + "(" + get_args(method.m_params) + ")";
		if(method.m_returnType == "void")
			return "[](Ref object, array<Var> args, Var& result) { UNUSED(result); " + unused_args(method) + call + "; }";
		else
			return "[](Ref object, array<Var> args, Var& result) { " + unused_args(method) + value_assign(*method.m_returnCls, "result", method.m_returnPointer, call) + "; }";
	}

	string constructor_decl(const CLType& c, const CLConstructor& constr)
	{
		return type_get(c) + ", [](Ref ref, array<Var> args) { " + unused_args(constr) + "new(&val<" + c.m_id + ">(ref)) " + c.m_id + "( " + get_args(constr.m_params) + "); }, " + params_def(constr.m_expected_params);
	}

	string copy_constructor_decl(const CLType& c)
	{
		return type_get(c) + ", [](Ref ref, Ref other) { new(&val<" + c.m_id + ">(ref)) " + c.m_id + "(val<" + c.m_id + ">(other)); }";
	}

	string member_decl(const CLType& c, const CLMember& m)
	{
		return type_get(c) + ", " + member_identity(c, m) + ", " + type_get(*m.m_cls) + ", \"" + m.m_name + "\", " + member_default(c, m) + ", " + member_flags(c, m) + ", " + member_getter(c, m);
	}

	string method_decl(const CLType& c, const CLMethod& m)
	{
		return type_get(c) + ", \"" + m.m_name + "\", " + method_identity(c, m) + ", " + method_func(c, m) = ", " + params_def(m.m_params) + ", " + function_return_def(m);
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

	void write_line(string& t, int& i, const string& s)
	{
		if(s[0] == '}') --i;
		for(size_t c = 0; c < i; ++c) t += "\t";
		t += s;
		t += "\n";
		for(size_t c = 1; c < s.size(); ++c) { if(s[c] == '{') ++i; if(s[c] == '}') --i; }
		if(s[0] == '{') ++i;
	}

	string meta_h_template(CLModule& m)
	{
		string t;
		auto p = [&](int& i, const string& s) {	write_line(t, i, s); };
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
				p(i, e.m_scoped ? "true" : "false");
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
				if(c.m_struct)
					p(i, "{" + copy_constructor_decl(c) + "}");
				p(i, "},");
				p(i, "// members");
				p(i, "{");
				for(CLMember& m : c.m_members)
					p(i, "{ " + member_decl(c, m) + " }" + (&m == &c.m_members.back() ? "" : ", "));
				p(i, "},");
				p(i, "// methods");
				p(i, "{");
				for(CLMethod& m : c.m_methods)
					p(i, "{ " + method_decl(c, m) + " }" + (&m == &c.m_methods.back() ? "" : ", "));
				p(i, "},");
				p(i, "// static members");
				p(i, "{");
				for(CLStatic& m : c.m_statics)
					p(i, "{ " + static_decl(c, m) + " }" + (&m == &c.m_statics.back() ? "" : ", "));
				p(i, "}");
				p(i, "};");
				if(c.m_constructors.size() > 0 && !c.m_struct)
					p(i, "init_pool<" + c.m_id + ">();");
				if(c.m_array)
					p(i, "init_string<" + c.m_id + ">();");
				p(i, "meta_class<" + c.m_id + ">();");
				p(i, "}");
			}

		for(CLType* t : m.m_types)
			if(t->m_reflect)
				p(i, "m.m_types.push_back(&" + type_get(*t) + ");");
       
		for(auto& pf : m.m_functions)
		{
			CLFunction& f = *pf;
			p(i, "{");
			if(f.m_returnType == "void")
				p(i, "auto func = [](array<Var> args, Var& result) { UNUSED(result); " + unused_args(f) + " " + f.m_id + "(" + get_args(f.m_params) + "); };");
			else
				p(i, "auto func = [](array<Var> args, Var& result) { " + unused_args(f) + " " + value_assign(*f.m_returnCls, "result", f.m_returnPointer, f.m_id + "(" + get_args(f.m_params) + ")") + "; };");
			p(i, "std::vector<Param> params = " + params_def(f.m_params) + ";");
			//p(i, "static Function f = { " + clnamespace(f) + ", \"" + f.m_name + "\", " + function_identity(f) + ", func, params, " + function_return_def(f) + " };");
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
			CLNamespace& n = key_namespace.second;
			
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

	string module_h_template(CLModule& m)
	{
		string t;
		auto p = [&](int& i, const string& s) {	write_line(t, i, s); };
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
		p(i, "private:");
		p(i, m.m_id + "();");
		p(i, "");
		p(i, "public:");
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

		auto deps = [&](){ return join(transform<string>(m.m_dependencies, [](CLModule* d) { return "&" + d->m_name + "::m()"; }), ", "); };

		p(i, "#include <infra/Cpp20.h>");
		p(i, "");
		p(i, "#ifdef MUD_MODULES");
		p(i, "module " + m.m_namespace + "." + m.m_name + ";");
		p(i, "#else");
		p(i, "#include <meta/" + m.m_subdir + "/m.h>");
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
		p(i, ": Module(\"" + string(m.m_namespace != "" ? m.m_namespace + "::" : "") + m.m_name + "\", {" + deps() + "})");
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
		auto p = [&](int& i, const string& s) {	write_line(t, i, s); };
		int i = 0;
		#pragma once

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
		auto p = [&](int& i, const string& s) {	write_line(t, i, s); };
		int i = 0;

		p(i, "#include <infra/Cpp20.h>");
		p(i, "");
		p(i, "#ifdef MUD_MODULES");
		p(i, "module " + m.m_namespace + "." + m.m_name + ";");
		p(i, "#else");
		p(i, "#include <" + m.m_subdir + "/Types.h>");
		p(i, "#include <" + m.m_subdir + "/Api.h>");
		p(i, "#include <type/Vector.h>");
		p(i, "//#include <ecs/Proto.h>");
		p(i, "#endif");
		p(i, "");
		p(i, "namespace mud");
		p(i, "{");
		p(i, "// Exported types");
		for(auto& b : m.m_basetypes)
			p(i, "template <> " + m.m_export + " Type& type<" + b->m_name + ">() { static Type ty(\"" + b->m_name + "\"); return ty; }");
		for(auto& e : m.m_enums)
			p(i, "template <> " + m.m_export + " Type& type<" + e->m_id + ">() { static Type ty(\"" + e->m_id + "\"); return ty; }");
		p(i, "");
		for(auto& c : m.m_classes)
			if(c->m_reflect && !c->m_nested && c->m_id != "mud::Type")
				p(i, "template <> " + m.m_export + " Type& type<" + c->m_id + ">() { static Type ty(\"" + c->m_name + "\"" + (", " + c->m_bases.size() > 0 ? type_get(*c->m_bases[0]) : "") + "); return ty; }");
		p(i, "}");

		return t;
	}
}
}
