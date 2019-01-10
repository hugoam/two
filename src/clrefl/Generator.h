#pragma once

#include <clang-c/Index.h>

#include <infra/String.h>
#include <infra/File.h>
#include <refl/Api.h>

#include <json11.hpp>

#include <string>
#include <vector>
#include <map>
#include <set>
#include <fstream>
#include <functional>

namespace mud
{
	// todo:
	// - add error/warning for member of non reflected type
	// - handle aliases of known types (either by parsing using/typedef, or by checking canonical type always)
	// - allow precompilation of separate modules

	using std::string;
	using std::vector;
	using std::map;

	using json11::Json;

	template <class T, class... T_Args>
	inline T& vector_emplace(std::vector<unique_ptr<T>>& vector, T_Args&&... args)
	{
		vector.push_back(make_unique<T>(std::forward<T_Args>(args)...));
		return static_cast<T&>(*vector.back());
	}

	template <class T_Value>
	bool has(const std::vector<T_Value>& vector, const T_Value& key)
	{
		return vector_has(vector, key);
	}

	template <class T_Map, class T_Key>
	bool has(const T_Map& map, const T_Key& key)
	{
		return map.find(key) != map.end();
	}

	template <class T_Vector, class T_Pred>
	void sort(T_Vector& vector, T_Pred pred)
	{
		std::sort(vector.begin(), vector.end(), pred);
	}

	class CLModule;
	class CLFunction;
	class CLPrimitive;
	class CLType;
	class CLMember;
	class CLMethod;
	class CLClass;
	class CLEnum;

	void visit_tokens(CXCursor cursor, const std::function<void(CXToken)>& visitor);
	void visit_children(CXCursor cursor, const std::function<void(CXCursor)>& visitor);
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

	void visit_tokens(CXCursor cursor, const std::function<void(CXToken)>& visitor)
	{
		CXTranslationUnit tu = clang_Cursor_getTranslationUnit(cursor);
		CXSourceRange extent = clang_getCursorExtent(cursor);
		
		CXToken* tokens = nullptr;
		unsigned int num_tokens = 0;
		clang_tokenize(tu, extent, &tokens, &num_tokens);

		for(size_t i = 0; i < num_tokens; ++i)
			visitor(tokens[i]);
	}

	void visit_children(CXCursor cursor, const std::function<void(CXCursor)>& visitor)
	{
		CXCursorVisitor cxvisitor = [](CXCursor cursor, CXCursor parent, CXClientData client_data) -> CXChildVisitResult
		{
			UNUSED(parent);
			std::function<void(CXCursor)>& func = *(std::function<void(CXCursor)>*)client_data;
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

	std::vector<string> get_annotations(CXCursor cursor)
	{
		std::vector<string> annotations;
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

	std::vector<string> template_types(const string& name)
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
			std::vector<string> types = template_types(clean_name(spelling(named_type)));
			return template_name(name) + "<" + join(types, ",") + ">";
		}

		return name;
	}

	string class_name(CXType type)
	{
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

	string substitute_template(const string& name, const std::vector<string>& template_types, const std::vector<string>& real_types)
	{
		string result = name;
		for(size_t i = 0; i < template_types.size(); ++i)
			result = replace(name, template_types[i], real_types[i]);
		return result;
	}

	class CLPrimitive
	{
	public:
		CLPrimitive(const string& name, CLPrimitive* parent = nullptr)
			: m_name(name)
			, m_id(parent ? parent->m_prefix + name : name)
			, m_parent(parent)
			, m_module(parent ? parent->m_module : nullptr)
			, m_prefix(m_id == "" ? "" : m_id + "::")
		{}

		string m_name;
		string m_id;
		CLPrimitive* m_parent = nullptr;
		CLModule* m_module = nullptr;
		string m_prefix;

		bool m_reflect = false;

		bool m_is_template = false;
		bool m_is_templated = false;

		std::vector<string> m_annotations;

		virtual string fix_template(const string& name) { return name; };
	};

	class CLNamespace : public CLPrimitive
	{
	public:
		CLNamespace(const string& name = "", CLPrimitive* parent = nullptr)
			: CLPrimitive(name, parent)
		{}
	};

	struct CLQualType
	{
		CLType* m_type = nullptr;
		string m_spelling;
		string m_type_name;
		string m_unqual_type_name;

		bool pointer() const { return m_spelling.back() == '*'; }
		bool reference() const { return m_spelling.back() == '&' && m_spelling.find("const") == string::npos; }
		bool const_pointer() const { return m_spelling.substr(0, 5) == "const" && m_spelling.back() == '*'; }
		bool const_reference() const { return m_spelling.substr(0, 5) == "const" && m_spelling.back() == '&'; }
		bool value() const { return !this->pointer() && !this->reference(); }
		bool nullable() const { return this->pointer() || m_type_name == "mud::Ref"; }

		explicit operator CLType&() { return *m_type; }
		explicit operator const CLType&() const { return *m_type; }
	};

	class CLType : public CLPrimitive
	{
	public:
		CLType(CLModule& module, CLPrimitive& parent, const string& name)
			: CLPrimitive(name, &parent)
			//, m_nested(type(parent) == Class)
		{
			m_module = &module;
		}

		bool m_nested = false;
		bool m_struct = true;
		bool m_move_only = false;
		bool m_pointer = false;

		std::vector<CLType*> m_bases;
		std::vector<CLType*> m_deep_bases;
		std::vector<string> m_aliases;
	};

	class CLBaseType : public CLType
	{
	public:
		CLBaseType(CLModule& module, CLPrimitive& parent, const string& name)
			: CLType(module, parent, name)
		{
			m_reflect = true;
			if(name == "const char*")
				m_pointer = true;
		}
	};

	class CLEnum : public CLType
	{
	public:
		CLEnum(CLModule& module, CLPrimitive& parent, const string& name)
			: CLType(module, parent, name)
		{}

		bool m_scoped = false;
		string m_enum_type;
		std::vector<string> m_ids;
		std::vector<string> m_values;

		std::vector<string> m_scoped_ids;
	};

	class CLSequence : public CLType
	{
	public:
		CLSequence(CLModule& module, const string& store, CLType& content_type, bool pointer, CLPrimitive& parent)
			: CLType(module, parent, store + "<" + content_type.m_id + (pointer ? "*" : "") + ">")
		{
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
		CLParam(CLFunction& func, size_t index)
			: m_func(&func)
			, m_index(index)
		{}

		CLFunction* m_func;
		size_t m_index;
		string m_name;
		CLQualType m_type;

		bool m_output;

		bool m_has_default = false;
		string m_default = "";
	};

	class CLFunction : public CLPrimitive
	{
	public:
		CLFunction(CLPrimitive& parent, const string& name)
			: CLPrimitive(name, &parent)
		{}

		CLQualType m_return_type;
		std::vector<CLParam> m_params;
	};

	class CLMethod : public CLFunction
	{
	public:
		CLMethod(CLType& parent, const string& name)
			: CLFunction(parent, name)
		{}

		bool m_overloaded = false;
		bool m_const = false;
		std::vector<CLParam> m_expected_params;
	};

	class CLConstructor : public CLMethod
	{
	public:
		CLConstructor(CLType& parent, const string& name)
			: CLMethod(parent, name)
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
			: m_parent(parent)
		{}

		CLClass& m_parent;
		CLQualType m_type;

		unique_ptr<CLMethod> m_method = nullptr;
		bool m_setter;

		string m_member;
		string m_name;
		string m_capname;

		std::vector<string> m_annotations;

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
		{}

		CXCursor m_cursor;

		std::vector<CLConstructor> m_constructors;
		std::vector<CLMember> m_members;
		std::vector<CLMethod> m_methods;
		std::vector<CLStatic> m_statics;

		std::vector<string> m_annotations;

		bool m_array = false;
		size_t m_array_size = 0;
		CLType* m_array_type = nullptr;
		bool m_extern = false;

		string m_template_name;
		bool m_template_used = false;
		CLClass* m_template = nullptr;
		std::vector<string> m_template_types;

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
			std::vector<string> real_types;
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
			m_base_aliases = { "uint8_t", "uint16_t", "uint32_t", "uint64_t", "size_t", "mud::Id" };
		}

		CLNamespace m_root_namespace;

		std::map<string, CLType*> m_types;
		std::map<string, CLClass*> m_class_templates;
		std::map<string, CLFunction*> m_func_templates;

		std::map<string, unique_ptr<CLNamespace>> m_namespaces;

		std::vector<string> m_base_aliases;

		std::set<string> m_parsed_files;

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
		CLModule(CLContext& context, const string& nemespace, const string& name, const string& dotname, const string& id, 
				 const string& rootdir, const string& subdir, const string& path, std::vector<string> includedirs, std::vector<CLModule*> dependencies)
			: m_context(context), m_namespace(nemespace), m_name(name), m_dotname(dotname), m_id(id), m_rootdir(rootdir), m_subdir(subdir), m_path(path)
			, m_includedirs(includedirs), m_dependencies(dependencies)
		{
			m_modules = dependencies;
			m_modules.push_back(this);

			m_preproc_name = to_upper(id);
			m_export = m_preproc_name + "_EXPORT";
			m_refl_export = m_preproc_name + "_REFL_EXPORT";

			m_refl_path = m_rootdir + "\\" + "meta" + "\\" + m_subdir;

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

		std::vector<string> m_includedirs;
		std::vector<CLModule*> m_dependencies;

		string m_preproc_name;
		string m_export;
		string m_refl_export;

		std::vector<CLModule*> m_modules;

		string m_refl_path;

		bool m_has_structs;

		std::vector<unique_ptr<CLClass>> m_classes = {};
		std::vector<unique_ptr<CLClass>> m_class_templates = {};
		std::vector<unique_ptr<CLEnum>> m_enums = {};
		std::vector<unique_ptr<CLSequence>> m_sequences = {};
		std::vector<unique_ptr<CLBaseType>> m_basetypes = {};
		std::vector<unique_ptr<CLType>> m_extern_types = {};

		std::vector<CLType*> m_types = {};

		std::vector<unique_ptr<CLFunction>> m_functions = {};
		std::vector<unique_ptr<CLFunction>> m_func_templates = {};

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
			for(const string& name : { "std::vector", "std::list", "mud::array", "array" })
				if(clsname.find(name) == 0)
				{
					string content_name = template_types(clsname)[0];
					CLType* content_type = this->find_type(parent, replace(content_name, "*", ""));
					if(content_type)
						return sequence_type(name, content_name, *content_type);
				}
			for(const string& name : { "unique_ptr", "object_ptr" })
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