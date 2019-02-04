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
		quicksort<typename T::value_type>(vec, pred);
	}

	class CLModule;
	class CLCallable;
	class CLFunction;
	class CLPrimitive;
	class CLType;
	class CLMember;
	class CLMethod;
	class CLClass;
	class CLEnum;

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

	string spelling(CXCursor cursor, CXToken token) { CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor); return clang_string(clang_getTokenSpelling(tu, token)); }
	string spelling(CXCursor cursor) { return clang_string(clang_getCursorSpelling(cursor)); }
	string spelling(CXType type) { return clang_string(clang_getTypeSpelling(type)); }

	string displayname(CXCursor cursor) { return clang_string(clang_getCursorDisplayName(cursor)); }

	CXType enum_type(CXCursor cursor) { return clang_getEnumDeclIntegerType(cursor); }
	long long enum_value(CXCursor cursor) { return clang_getEnumConstantDeclValue(cursor); }
	bool is_scoped(CXCursor cursor) { return clang_EnumDecl_isScoped(cursor); }

	CXType type(CXCursor cursor) { return clang_getCursorType(cursor); }
	CXType result_type(CXCursor cursor) { return clang_getCursorResultType(cursor); }

	CXType get_pointee(CXType type) { return clang_getPointeeType(type); }

	bool is_definition(CXCursor cursor) { return clang_isCursorDefinition(cursor); }

	bool is_const_method(CXCursor cursor) { return clang_CXXMethod_isConst(cursor); }

	void dump_ast(CXCursor cursor, int level)
	{
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

	string clean_name(const string& name)
	{
		return replace(replace(replace(name, " *", "*"), " &", "&"), "> >", ">>");
	}

	string type_name(CXType type)
	{
		string name = clean_name(spelling(type));

		if(name.find("<") != string::npos)
		{
			// only way to get fully qualified template arguments is through clang_Type_getNamedType
			CXType named_type = clang_Type_getNamedType(type);
			if(named_type.kind == CXType_Invalid)
				return name;
			vector<string> types = template_types(clean_name(spelling(named_type)));
			return template_name(name) + "<" + join(types, ",") + ">";
		}

		return name;
	}

	string class_name(CXType type)
	{
		if(spelling(type) == "void *")
			return "void*";
		if(type.kind == CXType_Pointer)
			return replace(type_name(get_pointee(type)), "const ", "");
		if(type.kind == CXType_LValueReference)
			return replace(type_name(get_pointee(type)), "const ", "");
    
		return replace(type_name(type), "const ", "");
	}

	string unqual_type_name(CXType type)
	{
		if(type.kind == CXType_LValueReference)
			return replace(type_name(get_pointee(type)), "const ", "");
        
		return replace(type_name(type), "const ", "");
	}

	string substitute_template(const string& name, const vector<string>& template_types, const vector<string>& real_types)
	{
		string result = name;
		for(size_t i = 0; i < template_types.size(); ++i)
			result = replace(name, template_types[i], real_types[i]);
		return result;
	}

	enum class CLPrimitiveKind
	{
		Namespace,
		Type,
		Class,
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

		CLPrimitiveKind m_kind;
		string m_name;
		string m_id;
		CLPrimitive* m_parent = nullptr;
		CLModule* m_module = nullptr;
		string m_prefix;

		bool m_reflect = false;
		bool m_reflect_content = false;

		bool m_is_basetype = false;
		bool m_is_template = false;
		bool m_is_templated = false;

		vector<string> m_annotations;

		virtual string fix_template(const string& name) { return name; };
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
		Array
	};

	class CLType : public CLPrimitive
	{
	public:
		CLType(CLModule& module, CLPrimitive& parent, const string& name)
			: CLPrimitive(CLPrimitiveKind::Type, name, &parent)
		{
			m_module = &module;
			//m_nested = parent.m_kind == CLPrimitiveKind::Class;

			if(name.back() == '*')
				m_pointer = true;

			if(has({ "void" }, name))
				m_type_kind = CLTypeKind::Void;
			if(has({ "void*" }, name))
				m_type_kind = CLTypeKind::VoidPtr;
			else if(has({ "bool" }, name))
				m_type_kind = CLTypeKind::Boolean;
			else if(has({ "char", "signed char", "unsigned char" }, name))
				m_type_kind = CLTypeKind::Char;
			else if(has({ "short", "int", "long", "long long", "unsigned short", "unsigned int", "unsigned long", "unsigned long long" }, name))
				m_type_kind = CLTypeKind::Integer;
			else if(has({ "float", "double" }, name))
				m_type_kind = CLTypeKind::Float;
			else if(has({ "char*", "const char*" }, name))
				m_type_kind = CLTypeKind::CString;
			else if(has({ "string", "std::string", "mud::string" }, name))
				m_type_kind = CLTypeKind::String;
		}

		CLTypeKind m_type_kind;
		bool m_nested = false;
		bool m_struct = true;
		bool m_move_only = false;
		bool m_pointer = false;

		vector<CLType*> m_bases;
		vector<CLType*> m_deep_bases;
		vector<string> m_aliases;
	};

	struct CLQualType
	{
		CLType* m_type = nullptr;
		string m_spelling;
		string m_type_name;
		string m_unqual_type_name;

		bool operator==(const CLQualType& o) const { return m_type == o.m_type && m_spelling == o.m_spelling; }
		bool operator!=(const CLQualType& o) const { return !(*this == o); }

		bool pointer() const { return m_spelling.back() == '*'; }
		bool reference() const { return m_spelling.back() == '&'; }
		bool isconst() const { return m_spelling.substr(0, 5) == "const"; }
		bool value() const { return !this->pointer() && !this->reference(); }
		bool memvalue() const { return m_type->m_struct && !this->pointer(); }
		bool nullable() const { return this->pointer() || m_type_name == "mud::Ref"; }
		bool copyable() const { return this->isbasetype() || this->isenum() || m_type->m_struct; }

		bool isarray() const { return false; }
		bool isvoid() const { return m_type->m_type_kind == CLTypeKind::Void; }
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

	class CLBaseType : public CLType
	{
	public:
		CLBaseType(CLModule& module, CLPrimitive& parent, const string& name)
			: CLType(module, parent, name)
		{
			m_reflect = true;
			m_is_basetype = true;
		}
	};

	class CLEnum : public CLType
	{
	public:
		CLEnum(CLModule& module, CLPrimitive& parent, const string& name)
			: CLType(module, parent, name)
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

	class CLSequence : public CLType
	{
	public:
		CLSequence(CLModule& module, const string& store, CLType& content_type, bool pointer, CLPrimitive& parent)
			: CLType(module, parent, store + "<" + content_type.m_id + (pointer ? "*" : "") + ">")
		{
			m_type_kind = CLTypeKind::Class;
			m_store = store;
			m_contentcls = &content_type;
			m_content = content_type.m_id + (pointer ? "*" : "");
			m_reflect = true;
		}

		string m_store;
		CLType* m_contentcls;
		string m_content;
	};
	
	class CLParam
	{
	public:
		CLParam(CLCallable& func, size_t index)
			: m_func(&func)
			, m_index(index)
		{}

		CLCallable* m_func;
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

		uint32_t m_index;
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
		CLClass(CLModule& module, CLPrimitive& parent, const string& name)
			: CLType(module, parent, name)
		{
			m_type_kind = CLTypeKind::Class;
		}

		CXCursor m_cursor;

		vector<CLConstructor> m_constructors;
		vector<CLMember> m_members;
		vector<CLMethod> m_methods;
		vector<CLStatic> m_statics;

		vector<string> m_annotations;

		bool m_array = false;
		size_t m_array_size = 0;
		CLType* m_array_type = nullptr;
		bool m_extern = false;

		string m_template_name;
		bool m_template_used = false;
		CLClass* m_template = nullptr;
		vector<string> m_template_types;

		string fix_template_element(const string& name)
		{
			if(m_template && has(m_template->m_template_types, name))
				return m_template_types[index_of(m_template->m_template_types, name)];
			else
				return name;
		}

		virtual string fix_template(const string& name) override
		{
			// first fix nested template types
			vector<string> real_types;
			for(const string& t : template_types(name))
				real_types.push_back(this->fix_template_element(t));
			string result = substitute_template(name, template_types(name), real_types);
			// then fix type itself in case it is a template parameter
			return this->fix_template_element(result);
			// printf("substituted template base name: %s\n", name.c_str);
		}
	};

	class CLContext
	{
	public:
		CLContext()
			: m_root_namespace("")
		{
			m_base_aliases = { "uint8_t", "uint16_t", "uint32_t", "uint64_t", "size_t" };
		}

		CLNamespace m_root_namespace;

		map<string, CLType*> m_types;
		map<string, CLClass*> m_class_templates;
		map<string, CLFunction*> m_func_templates;

		map<string, unique<CLNamespace>> m_namespaces;

		vector<string> m_base_aliases;

		set<string> m_parsed_files;

		CLNamespace& get_namespace(const string& name, CLPrimitive& parent)
		{
			string full_name = parent.m_prefix + name;
			if(m_namespaces.find(full_name) == m_namespaces.end())
				m_namespaces[full_name] = make_unique<CLNamespace>(name, &parent);
			return *m_namespaces[full_name];
		}
	};

	class CLModule
	{
	public:
		CLModule(CLContext& context) : m_context(context) {}
		CLModule(CLContext& context, const string& nemespace, const string& name, const string& dotname, const string& id, 
				 const string& rootdir, const string& subdir, const string& path, vector<string> includedirs, vector<CLModule*> dependencies)
			: m_context(context), m_namespace(nemespace), m_name(name), m_dotname(dotname), m_id(id), m_rootdir(rootdir), m_subdir(subdir), m_path(path)
			, m_includedirs(includedirs), m_dependencies(dependencies)
		{
			m_modules = dependencies;
			m_modules.push_back(this);

			m_preproc_name = to_upper(id);
			m_export = m_preproc_name + "_EXPORT";
			m_refl_export = m_preproc_name + "_REFL_EXPORT";

			m_refl_path = m_rootdir + "\\" + "meta" + "\\" + m_subdir;
			m_bind_path = m_rootdir + "\\" + "bind" + "\\" + m_subdir;

			m_has_structs = file_exists((m_path + "\\" + "Structs.h").c_str());
		}

		CLContext& m_context;
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

		vector<CLModule*> m_modules;

		string m_refl_path;
		string m_bind_path;

		bool m_has_structs;

		vector<unique<CLClass>> m_classes = {};
		vector<unique<CLClass>> m_class_templates = {};
		vector<unique<CLEnum>> m_enums = {};
		vector<unique<CLSequence>> m_sequences = {};
		vector<unique<CLBaseType>> m_basetypes = {};
		vector<unique<CLType>> m_extern_types = {};

		vector<CLType*> m_types = {};

		vector<unique<CLFunction>> m_functions = {};
		vector<unique<CLFunction>> m_func_templates = {};

		CLNamespace& get_namespace(const string& name, CLPrimitive& parent)
		{
			return m_context.get_namespace(name, parent);
		}

		CLClass& get_class_template(const string& name)
		{
			return *m_context.m_class_templates[name];
		}

		CLClass& get_class(const string& name)
		{
			return (CLClass&)*m_context.m_types[name];
		}

		CLType& get_type(const string& name)
		{
			return *m_context.m_types[name];
		}

		void register_type(CLType& type)
		{
			if(!type.m_is_template)
			{
				m_context.m_types[type.m_id] = &type;
				m_types.push_back(&type);
				printf("Type %s\n", type.m_id.c_str());
			}
		}

		CLType& base_type(const string& name, CLPrimitive& parent)
		{
			CLType& type = vector_emplace<CLBaseType>(m_basetypes, *this, parent, name);
			register_type(type);
			return type;
		}

		CLType& proxy_type(const string& name, CLPrimitive& parent)
		{
			CLType& type = vector_emplace<CLType>(m_extern_types, *this, parent, name);
			register_type(type);
			return type;
		}

		CLEnum& enum_type(CLPrimitive& parent, const string& name)
		{
			CLEnum& type = vector_emplace<CLEnum>(m_enums, *this, parent, name);
			register_type(type);
			return type;
		}

		CLSequence& sequence_type(const string& name, const string& content_name, CLType& content_type)
		{
			bool pointer = content_name.find("*") != string::npos;
			CLSequence& cls = vector_emplace<CLSequence>(m_sequences, *this, name, content_type, pointer, m_context.m_root_namespace);
			register_type(cls);
			return cls;
		}

		CLType& register_type(CLPrimitive& parent, const string& clsname)
		{
			for(const string& name : { "vector", "list", "array" })
				if(clsname.find(name) != string::npos)
				{
					string content_name = template_types(clsname)[0];
					CLType* content_type = this->find_type(parent, replace(content_name, "*", ""));
					if(content_type)
						return sequence_type(name, content_name, *content_type);
				}
			for(const string& name : { "unique", "object" })
				if(clsname.find(name) != string::npos)
				{
					CLType& type = this->proxy_type(clsname, m_context.m_root_namespace);
					type.m_move_only = true;
					return type;
				}
			printf("WARNING: declaring empty type %s\n", clsname.c_str());
			return this->proxy_type(clsname, m_context.m_root_namespace);
		}

		CLType* find_type_in(CLPrimitive& parent, const string& name, bool warn = true)
		{
			// stupid fix because clang FUCKING doesn"t always put the prefix in types ..............
			if(has(m_context.m_types, name))
				return m_context.m_types[name];
			else if(has(m_context.m_types, parent.m_prefix + name))
				return m_context.m_types[parent.m_prefix + name];
			else if(parent.m_parent)
				return this->find_type_in(*parent.m_parent, name, warn);
			else
				return nullptr;
		}

		CLType* find_type(CLPrimitive& parent, const string& name, bool warn = true)
		{
			CLType* cls = this->find_type_in(parent, name, warn);
			if(!cls)
			{
				if(has(m_context.m_base_aliases, name))
					return &this->proxy_type(name, m_context.m_root_namespace);
				for(auto& name_namespace : m_context.m_namespaces)
				{
					cls = this->find_type_in(*name_namespace.second, name, warn);
					if(cls)
						break;
				}
			}
			return cls;
		}

		CLType* get_type(CLPrimitive& parent, const string& name, bool warn = true)
		{
			CLType* cls = this->find_type(parent, name, warn);
			if(!cls)
				cls = &this->register_type(parent, name);
			if(!cls && warn)
				printf("ERROR: Type %s not found\n", parent.m_name.c_str());
			return cls;
		 }
	};

}