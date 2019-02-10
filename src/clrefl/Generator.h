#pragma once

#include <clang-c/Index.h>

#include <stl/string.h>
#include <stl/vector.h>
#include <stl/set.h>
#include <stl/map.h>
#include <stl/memory.h>
#include <stl/function.h>
#include <infra/Sort.h>
#include <infra/StringOps.h>
#include <infra/File.h>
#include <infra/Vector.h>
//#include <refl/Api.h>

#include <cstdio>
#include <algorithm>

namespace mud
{
	// todo:
	// - add error/warning for member of non reflected type
	// - handle aliases of known types (either by parsing using/typedef, or by checking canonical type always)
	// - allow precompilation of separate modules

	template <class T, class... Args>
	inline T& vector_emplace(vector<unique<T>>& vector, Args&&... args)
	{
		vector.push_back(construct<T>(static_cast<Args&&>(args)...));
		return static_cast<T&>(*vector.back());
	}

	template <class T, class U>
	bool has(const unordered_map<T, U>& map, const T& key)
	{
		return map.find(key) != map.end();
	}

	template <class T, class Pred>
	void sort(T& vec, Pred pred)
	{
		std::sort(vec.begin(), vec.end(), pred);
	}

	class CLModule;
	class CLParam;
	class CLCallable;
	class CLFunction;
	class CLPrimitive;
	class CLType;
	class CLMember;
	class CLMethod;
	class CLClass;
	class CLEnum;

	static CXTypeKind c_base_types[] = { CXType_Void, CXType_Bool, CXType_Char_S, CXType_SChar, CXType_UChar, CXType_Short, CXType_Int, CXType_Long, CXType_LongLong,
										 CXType_UShort, CXType_UInt, CXType_ULong, CXType_ULongLong, CXType_Float, CXType_Double, CXType_LongDouble };

	void visit_tokens(CXCursor cursor, const function<void(CXToken)>& visitor);
	void visit_children(CXCursor cursor, const function<void(CXCursor)>& visitor);
	void dump_ast(CXCursor cursor, int level = 0);

	CXCursor cursor(CXTranslationUnit tu) { return clang_getTranslationUnitCursor(tu); }

	string clang_string(CXString s) { string result = clang_getCString(s); clang_disposeString(s); return result; }

	string file(CXCursor cursor)
	{
		CXSourceLocation location = clang_getCursorLocation(cursor);
		CXFile file; unsigned line, column, offset;
		clang_getFileLocation(location, &file, &line, &column, &offset);
		return clang_string(clang_getFileName(file));
	}

	CXTokenKind kind(CXToken token) { return clang_getTokenKind(token); }

	string clean_name(const string& name)
	{
		return replace(replace(replace(name, " *", "*"), " &", "&"), "> >", ">>");
	}

	string spelling(CXCursor cursor, CXToken token) { CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor); return clean_name(clang_string(clang_getTokenSpelling(tu, token))); }
	string spelling(CXCursor cursor) { return clean_name(clang_string(clang_getCursorSpelling(cursor))); }
	string spelling(CXType type) { return clean_name(clang_string(clang_getTypeSpelling(type))); }

	string displayname(CXCursor cursor) { return clean_name(clang_string(clang_getCursorDisplayName(cursor))); }

	CXType enum_type(CXCursor cursor) { return clang_getEnumDeclIntegerType(cursor); }
	long long enum_value(CXCursor cursor) { return clang_getEnumConstantDeclValue(cursor); }
	bool is_scoped(CXCursor cursor) { return clang_EnumDecl_isScoped(cursor); }

	CXType type(CXCursor cursor) { CXType t = clang_getCursorType(cursor); return t.kind == CXType_Elaborated ? clang_Type_getNamedType(t) : t; }
	//CXType actual_type(CXCursor cursor) { CXType t = type(cursor); return t.kind == CXType_Elaborated ? clang_Type_getNamedType(t) : t; }
	CXType result_type(CXCursor cursor) { return clang_getCursorResultType(cursor); }

	CXType pointee(CXType type)
	{
		if(type.kind == CXType_Pointer || type.kind == CXType_LValueReference) return clang_getPointeeType(type);
		if(type.kind == CXType_ConstantArray) return clang_getElementType(type);
		else return type;
	}

	CXType canonical(CXType type) { return clang_getCanonicalType(type); }

	// @kludge @hack: clears the last bit of CXType data, which holds the const qualifier
	// proper solution is to request libclang to implement clang_getUnqualifiedType
	CXType unqual(CXType type) { CXType result = type; result.data[0] = (void*)(ullong(result.data[0]) & ~(1)); return result; }
	CXType upointee(CXType type) { return unqual(pointee(type)); }

	bool is_definition(CXCursor cursor) { return clang_isCursorDefinition(cursor); }

	bool is_const_method(CXCursor cursor) { return clang_CXXMethod_isConst(cursor); }

	void dump_ast(CXCursor cursor, int level)
	{
		visit_tokens(cursor, [&](CXToken t) {
			for(int i = 0; i < level; ++i) printf("    ");
			printf("+-- token %s\n", spelling(cursor, t).c_str());
		});

		visit_children(cursor, [&](CXCursor c) {
			for(int i = 0; i < level; ++i) printf("    ");
			printf("+-- %s %s %s\n", clang_string(clang_getCursorKindSpelling(c.kind)).c_str(), spelling(c).c_str(), spelling(type(c)).c_str());
			dump_ast(c, level + 1);
		});
	}

	void visit_tokens(CXCursor cursor, const function<void(CXToken)>& visitor)
	{
		CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
		CXSourceRange extent = clang_getCursorExtent(cursor);
		
		CXToken* tokens = nullptr;
		unsigned int num_tokens = 0;
		clang_tokenize(tu, extent, &tokens, &num_tokens);

		for(size_t i = 0; i < num_tokens; ++i)
			visitor(tokens[i]);
	}

	void visit_children(CXCursor cursor, const function<void(CXCursor)>& visitor)
	{
		CXCursorVisitor cxvisitor = [](CXCursor cursor, CXCursor parent, CXClientData client_data) -> CXChildVisitResult
		{
			UNUSED(parent);
			function<void(CXCursor)>& func = *(function<void(CXCursor)>*)client_data;
			func(cursor);
			return CXChildVisit_Continue;
		};

		clang_visitChildren(cursor, cxvisitor, (CXClientData)&visitor);
	}

	void get_tokens(CXTranslationUnit tu, CXSourceRange extent)
	{
		CXToken* tokens = nullptr;
		unsigned int num_tokens = 0;
		clang_tokenize(tu, extent, &tokens, &num_tokens);
	}

	string first_token(CXCursor cursor)
	{
		string result = "";
		visit_tokens(cursor, [&](CXToken token)
		{
			if(result == "")
				result = spelling(cursor, token);
		});
		return result;
	}

	vector<string> get_annotations(CXCursor cursor)
	{
		vector<string> annotations;
		visit_children(cursor, [&](CXCursor c)
		{
			if(c.kind == CXCursor_AnnotateAttr)
				annotations.push_back(displayname(c));
		});
		return annotations;
	}

	string template_name(const string& name)
	{
		return name.substr(0, name.find("<"));
	}

	vector<string> template_types(const string& name)
	{
		return split(name.substr(name.find("<") + 1, name.rfind(">") - name.find("<") - 1), ",");
	}

	CXType class_type(CXType type, bool canon = true)
	{
		if(pointee(type).kind == CXType_Void)
			return type;
		else if(type.kind == CXType_Pointer || type.kind == CXType_LValueReference || type.kind == CXType_ConstantArray)
			return unqual(canon ? canonical(pointee(type)) : pointee(type));
		else
			return unqual(canon ? canonical(type) : type);
	}

	void decl_enum(CLModule& module, CLPrimitive& parent, CXCursor cursor);
	void decl_callable(CLModule& module, CLPrimitive& parent, CLCallable& f, CXCursor cursor);
	void decl_function(CLModule& module, CLPrimitive& parent, CXCursor cursor);
	void decl_function_template(CLModule& module, CLPrimitive& parent, CXCursor cursor);
	void decl_class(CLModule& module, CLPrimitive& parent, CLClass& c, CXCursor cursor, CXType cxtype);
	CLClass& decl_class_type(CLModule& module, CLPrimitive& parent, CXCursor cursor);
	CLClass& decl_class_template(CLModule& module, CLPrimitive& parent, CXCursor cursor);

	void parse_enum(CLModule& module, CLEnum& e);
	void parse_static(CLModule& module, CLClass& c, CXCursor cursor);
	void parse_param(CLModule& module, CLPrimitive& parent, CLCallable& f, CLParam& p, CXCursor cursor);
	void parse_callable(CLModule& module, CLCallable& f);
	void parse_constructor(CLModule& module, CLClass& c, CXCursor cursor);
	void parse_method(CLModule& module, CLClass& c, CLMethod& m, CXCursor cursor);
	void parse_method(CLModule& module, CLClass& c, CXCursor cursor);
	void parse_member(CLModule& module, CLClass& c, CXCursor cursor);
	void parse_class(CLModule& module, CLClass& c);
	void parse_sequence(CLModule& module, CLClass& c);

	enum class CLPrimitiveKind
	{
		Namespace,
		Type,
		Function,
		Constructor,
		Method
	};

	class CLPrimitive
	{
	public:
		CLPrimitive(CLPrimitiveKind kind, const string& name, CLPrimitive* parent = nullptr)
			: m_kind(kind)
			, m_name(name)
			, m_id(parent ? parent->m_prefix + name : name)
			, m_parent(parent)
			, m_module(parent ? parent->m_module : nullptr)
			, m_prefix(m_id == "" ? "" : m_id + "::")
		{}

		void set_name(const string& name)
		{
			m_name = name;
			m_id = m_parent ? m_parent->m_prefix + name : name;
			m_prefix = m_id == "" ? "" : m_id + "::";
		}

		CLPrimitiveKind m_kind;
		string m_name;
		string m_id;
		CLPrimitive* m_parent = nullptr;
		CLModule* m_module = nullptr;
		string m_prefix;

		CXCursor m_cursor;

		bool m_reflect = false;
		bool m_reflect_content = false;

		bool m_is_template = false;
		bool m_is_templated = false;

		vector<string> m_annotations;

		virtual string fix_template(const string& name) const { return name; };
	};

	class CLNamespace : public CLPrimitive
	{
	public:
		CLNamespace(const string& name = "", CLPrimitive* parent = nullptr)
			: CLPrimitive(CLPrimitiveKind::Namespace, name, parent)
		{}
	};

	enum class CLTypeKind
	{
		Unknown,
		Void,
		VoidPtr,
		Boolean,
		Char,
		Integer,
		Float,
		CString,
		String,
		Enum,
		Class,
		Array,
		Alias
	};

	string type_name(CLPrimitive& parent, CXType type)
	{
		//return replace(spelling(type), parent.m_prefix, "");
		string name = spelling(type);
		if(starts_with(name, parent.m_prefix))
			name.erase(0, parent.m_prefix.size());
		return name;
	}

	class CLType : public CLPrimitive
	{
	public:
		CLType(CLModule& module, CLPrimitive& parent, CXType cxtype)
			: CLPrimitive(CLPrimitiveKind::Type, type_name(parent, cxtype), &parent) // spelling(cxtype), 
			, m_cxtype(cxtype)
		{
			m_module = &module;
			//m_nested = parent.m_kind == CLPrimitiveKind::Class;

			if(m_id.back() == '*')
				m_pointer = true;
		}

		CXType m_cxtype;
		CLTypeKind m_type_kind;
		bool m_nested = false;
		bool m_struct = true;
		bool m_move_only = false;
		bool m_pointer = false;

		vector<CLType*> m_bases;
		vector<CLType*> m_deep_bases;
		vector<string> m_aliases;
	};

	class CLAlias : public CLType
	{
	public:
		CLAlias(CLModule& module, CLPrimitive& parent, CXType alias, CXType target)
			: CLType(module, parent, alias)
			, m_cxtarget(target)
		{
			m_type_kind = CLTypeKind::Alias;
			if(m_name.find("string") != string::npos)
				m_type_kind = CLTypeKind::String;
		}

		CXType m_cxtarget;
		CLType* m_target = nullptr;
	};

	struct CLQualType
	{
		CLType* m_type = nullptr;
		string m_spelling;
		string m_type_name;
		bool m_array = false;

		bool operator==(const CLQualType& o) const { return m_type == o.m_type && m_spelling == o.m_spelling; }
		bool operator!=(const CLQualType& o) const { return !(*this == o); }

		bool pointer() const { return m_spelling.back() == '*'; }
		bool reference() const { return m_spelling.back() == '&'; }
		bool isconst() const { return m_spelling.substr(0, 5) == "const"; }
		bool value() const { return !this->pointer() && !this->reference(); }
		bool memvalue() const { return m_type->m_struct && !this->pointer(); }
		bool nullable() const { return this->pointer() || m_type_name == "mud::Ref"; }
		bool copyable() const { return this->isbasetype() || this->isenum() || m_type->m_struct; }

		bool isarray() const { return m_array; }
		bool isvoid() const { return !m_type || m_type->m_type_kind == CLTypeKind::Void; }
		bool isvoidptr() const { return m_type->m_type_kind == CLTypeKind::VoidPtr; }
		bool isboolean() const { return m_type->m_type_kind == CLTypeKind::Boolean; }
		bool isinteger() const { return m_type->m_type_kind == CLTypeKind::Integer; }
		bool isfloat() const { return m_type->m_type_kind == CLTypeKind::Float; }
		bool iscstring() const { return m_type->m_type_kind == CLTypeKind::CString; }
		bool isstring() const { return m_type->m_type_kind == CLTypeKind::String; }
		bool isenum() const { return m_type->m_type_kind == CLTypeKind::Enum; }
		bool isclass() const { return m_type->m_type_kind == CLTypeKind::Class; }
		bool isbasetype() const { return m_type->m_type_kind != CLTypeKind::Class && m_type->m_type_kind != CLTypeKind::Enum; }
		bool istypedptr() const { return m_type_name == "mud::Ref"; }

		//explicit operator CLType&() { return *m_type; }
		//explicit operator const CLType&() const { return *m_type; }
	};

	template<typename T, size_t N>
	constexpr size_t array_size(T(&array)[N]) { return N; }

	class CLBaseType : public CLType
	{
	public:
		CLBaseType(CLModule& module, CLPrimitive& parent, CXType cxtype, CLTypeKind type_kind)
			: CLType(module, parent, cxtype)
		{
			m_type_kind = type_kind;

			struct Shorten { CXTypeKind type; cstring shortened; };
			const Shorten shorten[] = { { CXType_SChar, "schar" }, { CXType_UChar, "uchar" }, { CXType_LongLong, "llong" }, { CXType_UShort, "ushort" },
										{ CXType_UInt, "uint" }, { CXType_ULong, "ulong" }, { CXType_ULongLong, "ullong" }, { CXType_LongDouble, "ldouble" } };

			for(const Shorten& s : shorten)
				if(cxtype.kind == s.type)
					this->set_name(s.shortened);
		}
	};

	class CLEnum : public CLType
	{
	public:
		CLEnum(CLModule& module, CLPrimitive& parent, CXType cxtype)
			: CLType(module, parent, cxtype)
		{
			m_type_kind = CLTypeKind::Enum;
		}

		bool m_scoped = false;
		string m_enum_type;
		size_t m_count = 0;
		vector<string> m_ids;
		vector<string> m_values;

		vector<string> m_scoped_ids;
	};
	
	class CLParam
	{
	public:
		CLParam(CLCallable& func, size_t index)
			: m_index(index)
		{}

		size_t m_index;
		string m_name;
		CLQualType m_type;

		bool m_output;

		bool m_has_default = false;
		string m_default = "";
	};

	class CLCallable : public CLPrimitive
	{
	public:
		CLCallable(CLPrimitiveKind kind, CLPrimitive& parent, const string& name)
			: CLPrimitive(kind, name, &parent)
		{}

		CLQualType m_return_type;
		vector<CLParam> m_params;
		size_t m_min_args = 0;
		bool m_overloaded = false;
		uint32_t m_overload_index = 0;
	};

	class CLFunction : public CLCallable
	{
	public:
		CLFunction(CLPrimitive& parent, const string& name)
			: CLCallable(CLPrimitiveKind::Function, parent, name)
		{}

		uint32_t m_index;
	};

	class CLMethod : public CLCallable
	{
	public:
		CLMethod(CLType& parent, const string& name)
			: CLCallable(CLPrimitiveKind::Method, parent, name)
		{}

		bool m_const = false;
	};

	class CLConstructor : public CLCallable
	{
	public:
		CLConstructor(CLType& parent, const string& name)
			: CLCallable(CLPrimitiveKind::Constructor, parent, name)
		{}
	};
	
	class CLStatic
	{
	public:
		CLStatic(CLClass& parent)
			: m_parent(parent)
		{}

		CLClass& m_parent;
		string m_member;
		string m_name;
	};

	class CLMember
	{
	public:
		CLMember(CLClass& parent)
			: m_parent(&parent)
		{}

		CLClass* m_parent;
		CLQualType m_type;

		unique<CLMethod> m_method = {};
		unique<CLMethod> m_setter = {};

		string m_member;
		string m_name;
		string m_capname;

		vector<string> m_annotations;

		bool m_nonmutable = false;
		bool m_structure = false;
		bool m_link = false;
		bool m_component = false;

		bool m_has_default = false;
		string m_default = "";
	};

	class CLClass : public CLType
	{
	public:
		CLClass(CLModule& module, CLPrimitive& parent, CXType cxtype)
			: CLType(module, parent, cxtype)
		{
			m_type_kind = CLTypeKind::Class;
			//this->set_alias(displayname(cursor));
		}

		vector<CLConstructor> m_constructors;
		vector<CLMember> m_members;
		vector<CLMethod> m_methods;
		vector<CLStatic> m_statics;

		bool m_array = false;
		size_t m_array_size = 0;
		CLType* m_array_type = nullptr;
		bool m_extern = false;

		bool m_sequence = false;
		CLType* m_element_type = nullptr;
		string m_element = "";

		string m_template_name;
		CLClass* m_template = nullptr;
		vector<string> m_template_types;
		vector<CLType*> m_templated_types;

		CLType* templated_type(const string& name) const
		{
			//printf("substituting %s\n", name.c_str());
			size_t pos = index_of(m_template->m_template_types, name);
			return pos < m_templated_types.size() ? m_templated_types[pos] : nullptr;
		}

		virtual string fix_template(const string& name) const override
		{
			// fix type itself in case it is a template parameter
			if(CLType* templated = this->templated_type(name))
				return templated->m_id;

			// fix nested template types
			string result = name;
			for(const string& t : template_types(name))
				if(CLType* templated = this->templated_type(t))
					result = replace(result, t, templated->m_id);
			return result;
			// printf("substituted template base name: %s\n", name.c_str);
		}
	};

	class CLModule
	{
	public:
		CLModule() : m_global("") {}
		CLModule(const string& nemespace, const string& name, const string& dotname, const string& id, 
				 const string& rootdir, const string& subdir, const string& path, vector<string> includedirs, vector<CLModule*> dependencies)
			: m_namespace(nemespace), m_name(name), m_dotname(dotname), m_id(id), m_rootdir(rootdir), m_subdir(subdir), m_path(path)
			, m_includedirs(includedirs), m_dependencies(dependencies)
			, m_global("")
		{
			m_dotname = replace(m_dotname, nemespace + ".", "");

			m_modules = dependencies;
			m_modules.push_back(this);

			m_preproc_name = to_upper(id);
			m_export = m_preproc_name + "_EXPORT";
			m_refl_export = m_preproc_name + "_REFL_EXPORT";

			m_refl_path = m_rootdir + "/" + "meta";
			m_bind_path = m_rootdir + "/" + "bind";

			m_has_structs = file_exists(m_path + "/" + "Structs.h");
		}

		string m_namespace;
		string m_name;
		string m_dotname;
		string m_id;
		string m_rootdir;
		string m_subdir;
		string m_path;

		vector<string> m_includedirs;
		vector<CLModule*> m_dependencies;

		string m_preproc_name;
		string m_export;
		string m_refl_export;
		bool m_decl_basetypes = false;

		vector<CLModule*> m_modules;

		string m_refl_path;
		string m_bind_path;

		bool m_has_structs = false;
		bool m_has_reflected = false;

		set<string> m_parsed_files;

		CLNamespace m_global;

		map<string, unique<CLNamespace>> m_namespaces;

		vector<CLType*> m_types;

		vector<unique<CLBaseType>> m_basetypes = {};
		vector<unique<CLEnum>> m_enums = {};
		vector<unique<CLClass>> m_classes = {};
		vector<unique<CLClass>> m_class_templates = {};
		vector<unique<CLClass>> m_sequences = {};
		vector<unique<CLType>> m_extern_types = {};

		vector<unique<CLFunction>> m_functions = {};
		vector<unique<CLFunction>> m_func_templates = {};

		vector<unique<CLAlias>> m_aliases = {};

		CLNamespace& get_namespace(const string& name, CLPrimitive& parent)
		{
			string full_name = parent.m_prefix + name;
			if(m_namespaces.find(full_name) == m_namespaces.end())
				m_namespaces[full_name] = make_unique<CLNamespace>(name, &parent);
			return *m_namespaces[full_name];
		}

		CLClass* find_class_template(const string& name)
		{
			auto result = find_if(m_class_templates, [&](unique<CLClass>& c) { return c->m_template_name == name || c->m_parent->m_prefix + c->m_template_name == name; });
			return result == m_class_templates.end() ? nullptr : &**result;
		}

		CLClass& get_class_template(const string& name)
		{
			return *find_class_template(name);
		}

		CLType* find_type(const string& name)
		{
			auto result = find_if(m_types, [&](CLType* t) { return t->m_id == name; });
			return result == m_types.end() ? nullptr : *result;
		}

		CLClass& get_class(const string& name)
		{
			return (CLClass&)*this->find_type(name);
		}

		void register_type(CLType& type)
		{
			if(!type.m_is_template)
			{
				printf("Type %s\n", type.m_id.c_str());
				m_types.push_back(&type);
			}
		}

		CLType& proxy_type(CXType cxtype, CLTypeKind type_kind)
		{
			CLType& type = vector_emplace<CLType>(m_extern_types, *this, m_global, cxtype);
			type.m_type_kind = type_kind;
			register_type(type);
			return type;
		}

		CLType& unknown_type(CXType cxtype)
		{
			return this->proxy_type(cxtype, CLTypeKind::Unknown);
		}

		CLType& base_type(CXType cxtype, CLTypeKind type_kind)
		{
			CLType& type = vector_emplace<CLBaseType>(m_basetypes, *this, m_global, cxtype, type_kind);
			type.m_reflect = m_decl_basetypes && type.m_type_kind != CLTypeKind::Unknown;
			register_type(type);
			return type;
		}

		CLType& base_type(CXType cxtype)
		{
			const CXType cxbase = pointee(cxtype);
			const bool pointer = cxtype.kind == CXType_Pointer;

			if(cxtype.kind == CXType_Elaborated)
				cxtype = clang_Type_getNamedType(cxtype);

			CLTypeKind type_kind = CLTypeKind::Unknown;

			if(has({ CXType_Void }, cxbase.kind))
				type_kind = pointer ? CLTypeKind::VoidPtr : CLTypeKind::Void;
			else if(has({ CXType_Bool }, cxbase.kind))
				type_kind = CLTypeKind::Boolean;
			else if(has({ CXType_Char_S, CXType_SChar, CXType_UChar }, cxbase.kind))
				type_kind = pointer ? CLTypeKind::CString : CLTypeKind::Char;
			else if(has({ CXType_Short, CXType_Int, CXType_Long, CXType_LongLong, CXType_UShort, CXType_UInt, CXType_ULong, CXType_ULongLong }, cxbase.kind))
				type_kind = CLTypeKind::Integer;
			else if(has({ CXType_Float, CXType_Double, CXType_LongDouble }, cxbase.kind))
				type_kind = CLTypeKind::Float;
			else if(spelling(cxtype).find("string") != string::npos)
				type_kind = CLTypeKind::String;

			return this->base_type(cxtype, type_kind);
		}

		CLType* basic_type(CXType cxtype)
		{
			cxtype = canonical(cxtype);
			if(has({ c_base_types }, upointee(cxtype).kind))
				return &this->base_type(cxtype);
			return nullptr;
		}

		CLType* instantiate_type(CXType cxtype)
		{
			CXType cl = class_type(cxtype);
			if(clang_Type_getNumTemplateArguments(cl) > 0)
			{
				string type_name = spelling(cxtype);
				CLClass* templatee = this->find_class_template(template_name(type_name));
				CXCursor cursor = clang_getTypeDeclaration(cl);
				if(!templatee)
					return nullptr;
				CLClass* templated = &decl_class_type(*this, *templatee->m_parent, cursor);
				parse_class(*this, *templated);
				printf("instantiated template %s (requested %s)\n", templated->m_id.c_str(), type_name.c_str());
				return templated;
			}
			return nullptr;
		}

		CLType& register_type(CXType cxtype)
		{
			if(CLType* type = this->basic_type(cxtype))
				return *type;
			if(CLType* type = this->instantiate_type(cxtype))
				return *type;

			CXType cl = class_type(cxtype);
			int g = clang_Type_getNumTemplateArguments(cl);

			printf("WARNING: unknown type %s\n", spelling(cxtype).c_str());
			return this->unknown_type(cxtype);
		}

		CLType* find_type(CXType cxtype)
		{
			auto alias = find_if(m_aliases, [&](const unique<CLAlias>& a) { return clang_equalTypes(a->m_cxtype, cxtype); });
			if(alias != m_aliases.end()) return &**alias;
			auto type = find_if(m_types, [&](CLType* t) { return clang_equalTypes(t->m_cxtype, cxtype); });
			if(type != m_types.end()) return *type;
			if(has({ c_base_types }, cxtype.kind))
				return &this->base_type(cxtype);
			return nullptr;
		}

		CLType* get_type(CXType cxtype)
		{
			if(CLType* cl = this->find_type(cxtype))
				return cl;
			if(CLType* cl = this->find_type(upointee(cxtype)))
				return cl;
			if(CLType* cl = this->find_type(class_type(cxtype)))
				return cl;
			return &this->register_type(cxtype);
		}

		CLType* find_alias(CXType cxtype, const string& name)
		{
			auto result = find_if(m_aliases, [&](const unique<CLAlias>& a) { return clang_equalTypes(a->m_cxtarget, cxtype) && (a->m_id == name || a->m_name == name); });
			return result == m_aliases.end() ? nullptr : &**result;
		}

		CLType* get_type(CXType cxtype, const string& name)
		{
			CLType* t = this->find_type(name);
			for(const string& n : { "stl", "mud" })
				if(!t)
					t = this->find_type(n + "::" + name);
			if(!t)
			{
				printf("WARNING: failed to find suitable template type for %s %s\n", spelling(canonical(cxtype)).c_str(), name.c_str());
				t = &this->register_type(cxtype);
			}
			return t;
		}
	};

}