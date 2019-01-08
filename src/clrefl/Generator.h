#pragma once

#include <clang-c/Index.h>

#include <infra/String.h>
#include <infra/File.h>
#include <refl/Api.h>

#include <json11.hpp>

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <functional>

using std::string;
using std::vector;
using std::map;

using json11::Json;

namespace mud
{
	template <class T_Object, class... T_Args>
	inline T_Object& vector_emplace(std::vector<unique_ptr<T_Object>>& vector, T_Args&&... args)
	{
		vector.push_back(make_unique<T_Object>(std::forward<T_Args>(args)...));
		return static_cast<T_Object&>(*vector.back());
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

	void update_file(const string& path, const string& content)
	{
		string current = read_text_file(path.c_str());
		if(content != current)
			write_file(path.c_str(), content.c_str());
	}

	static CXTranslationUnit g_tu;

	CXCursor cursor(CXTranslationUnit tu) { return clang_getTranslationUnitCursor(tu); }

	string file(CXCursor cursor)
	{
		CXSourceLocation location = clang_getCursorLocation(cursor);
		CXFile file; unsigned line, column, offset;
		clang_getFileLocation(location, &file, &line, &column, &offset);
		return clang_getCString(clang_getFileName(file));
	}

	string spelling(CXToken token) { return clang_getCString(clang_getTokenSpelling(g_tu, token)); }
	string spelling(CXCursor cursor) { return clang_getCString(clang_getCursorSpelling(cursor)); }
	string spelling(CXType type) { return clang_getCString(clang_getTypeSpelling(type)); }

	string displayname(CXCursor cursor) { return clang_getCString(clang_getCursorDisplayName(cursor)); }

	CXType enum_type(CXCursor cursor) { return clang_getEnumDeclIntegerType(cursor); }
	long long enum_value(CXCursor cursor) { return clang_getEnumConstantDeclValue(cursor); }
	bool is_scoped(CXCursor cursor) { return false; } // clang_EnumDecl_isScoped(cursor); }

	CXType type(CXCursor cursor) { return clang_getCursorType(cursor); }
	CXType result_type(CXCursor cursor) { return clang_getCursorResultType(cursor); }

	CXType get_pointee(CXType type) { return clang_getPointeeType(type); }

	bool is_definition(CXCursor cursor) { return clang_isCursorDefinition(cursor); }


	void visit_tokens(CXCursor cursor, std::function<void(CXToken&)> visitor)
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
		visit_tokens(cursor, [&](CXToken& token) {
			if(result == "")
				result = spelling(token);
		});
		return result;
	}

	std::vector<string> get_annotations(CXCursor cursor)
	{
		std::vector<string> annotations;
		visit_children(cursor, [&](CXCursor c) {
			if(c.kind == CXCursor_AnnotateAttr)
				annotations.push_back(displayname(c));
		});
		return annotations;
	}

	string clean_name(const string& name)
	{
		string result = replace(name, "const char*", "cstring");
		return replace(replace(replace(result, " *", "*"), " &", "&"), "> >", ">>");
	}

	string type_name(CXType type, bool is_template = false)
	{
		UNUSED(is_template);
		return clean_name(spelling(type));
	}

	string class_name(CXType type, bool is_template = false)
	{
		if(type.kind == CXType_Pointer)
			return type_name(get_pointee(type));
		if(type.kind == CXType_LValueReference)
			return replace(type_name(get_pointee(type)), "const ", "");
    
		return type_name(type, is_template);
	}

	string unqual_type_name(CXType type, bool is_template = false)
	{
		if(type.kind == CXType_LValueReference)
			return replace(type_name(get_pointee(type)), "const ", "");
        
		return type_name(type, is_template);
	}

	bool is_template_decl(CXCursor cursor)
	{
		bool has_def = false;
		visit_children(cursor, [&](CXCursor cursor) {
			if(clang_getCursorKind(cursor) == CXCursor_CXXBaseSpecifier)
				has_def = true;
		});
		return !has_def;
	}

	string template_name(const string& name)
	{
		return name.substr(0, name.find("<"));
	}

	std::vector<string> template_types(const string&name)
	{
		return split(name.substr(name.find("<") + 1), ",");
	}

	string substitute_template(const string& name, const std::vector<string>& template_types, const std::vector<string>& real_types)
	{
		string result = name;
		for(size_t i = 0; i < template_types.size(); ++i)
			result = replace(name, template_types[i], real_types[i]);
		return result;
	}

	struct CLDefault
	{
		bool m_has_default;
		string m_default;
	};

	CLDefault find_default_value(CXCursor cursor)//decl, cls, cursor)
	{
		CLDefault result;
		visit_children(cursor, [&](CXCursor c) {
			if(c.kind == CXCursor_CXXBoolLiteralExpr || c.kind == CXCursor_FloatingLiteral || c.kind == CXCursor_IntegerLiteral || c.kind == CXCursor_StringLiteral)
				result = { true, first_token(c) };
			else if(c.kind == CXCursor_CallExpr || c.kind == CXCursor_DeclRefExpr || c.kind == CXCursor_UnexposedExpr)
				result = { true, "" };
		});
		return result;
	}

	class CLFile
	{
	public:
		CLFile(const string& path) : m_path(path) {}

		string m_path;
		size_t m_depth = 0;
        
		//void __cmp__(other):
		//    return m_depth < other.depth
	};

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

		bool m_reflect = true;

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

	class CLType : public CLPrimitive
	{
	public:
		CLType(CLModule& module, const string& name, CLPrimitive& parent, bool is_template = false)
			: CLPrimitive(name, &parent)
			, m_is_template(is_template)
			//, m_nested(type(parent) == Class)
		{
			m_module = &module;
		}

		bool m_nested = false;
		bool m_struct = true;
		bool m_is_template = false;
		std::vector<CLType*> m_bases;
		std::vector<CLType*> m_deep_bases;
		std::vector<string> m_aliases;

		//bool m_isProto = false;
	};

	class CLTypeProxy
	{
	public:
		CLTypeProxy(const string& name) : m_name(name), m_id(name) {}

		string m_name;
		string m_id;
		bool m_struct = true;
	};

	class CLBaseType : public CLType
	{
	public:
		CLBaseType(CLModule& module, const string& name, CLPrimitive& parent)
			: CLType(module, name, parent)
		{}
	};

	class CLEnum : public CLType
	{
	public:
		CLEnum(CLModule& module, CXCursor cursor, CLPrimitive& parent)
			: CLType(module, displayname(cursor), parent)
		{
			m_scoped = is_scoped(cursor);
			m_enum_type = spelling(enum_type(cursor));
			m_prefix = parent.m_prefix + (m_scoped ? m_id + "::" : "");
			//m_reflect = "reflect" in get_annotations(cursor)

			visit_children(cursor, [&](CXCursor c)
			{
				if(c.kind == CXCursor_EnumConstantDecl)
				{
					m_ids.push_back(displayname(c));
					m_values.push_back(to_string(enum_value(c)));
					m_scoped_ids.push_back(m_prefix + displayname(c));
				}
			});
		}

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
			: CLType(module, store + "<" + content_type.m_id + (pointer ? "*" : "") + ">", parent)
		{
			m_store = store;
			m_contentcls = &content_type;
			m_content = content_type.m_id + (pointer ? "*" : "");
		};

		string m_store;
		CLType* m_contentcls;
		string m_content;
	};
	
            
	class CLParam
	{
	public:
		CLParam(CLFunction& func, CXCursor cursor, size_t index, CLPrimitive& parent);

		CLFunction* m_func;
		size_t m_index;
		string m_name;
		CLType* m_cls;
		string m_type;
		string m_clsname;

		bool m_pointer;
		bool m_reference;
		bool m_const_pointer;
		bool m_const_reference;

		bool m_nullable;
		bool m_output;
		bool m_input;

		bool m_has_default;
		string m_default;

		//CLParam copy(size_t index)
		//{
			//param = copy.copy(self)
			//param.index = index
			//return param
		//}
        
		bool equals(const CLParam& param) const
		{
			return param.m_name == m_name && param.m_type == m_type;
		}
	};

	class CLFunction
	{
	public:
		CLFunction(CLModule& module, CXCursor cursor, CLPrimitive& parent);

		CLModule& m_module;
		CLPrimitive& m_parent;
		string m_name;
		string m_id;
		string m_idstr;

		std::vector<CLParam> m_params;
		string m_returnType;
		bool m_returnPointer;
		string m_returnClsName;
		string m_unqualReturnType;
		bool m_is_function;
		bool m_is_template;

		string m_signature;
		CLType* m_returnCls;
	};

	class CLMethod : public CLFunction
	{
	public:
		CLMethod(CLType& parent, CXCursor cursor);

		std::vector<CLParam> m_expected_params;
	};

	class CLConstructor : public CLMethod
	{
	public:
		CLConstructor(CLType& parent, CXCursor cursor)
			: CLMethod(parent, cursor)
		{}

		//void createAggregate(constructors, components) :
		//	constructor = copy.copy(self)
		//	constructor.expected_params = [param.copy(i) for i, param in enumerate([param for constr in components for param in constr.params])]
		//	constructor.params = [param for param in constructor.expected_params if(next((p for p in m_params if(p.equals(param)), None)]
		//		constructor.combined = true
		//		if(len(constructor.params) == len(constructor.expected_params) :
		//			constructors.push_back(constructor)
	};
	
	class CLStatic
	{
	public:
		CLStatic(CLClass& parent, CXCursor cursor)
			: m_parent(parent)
		{
			m_member = spelling(cursor);
			m_name = replace(spelling(cursor), "m_", "");
		}

		CLClass& m_parent;
		string m_member;
		string m_name;
	};

	class CLMember // : public CLPrimitive
	{
	public:
		CLMember(CLClass& parent, CXCursor cursor);

		CLClass& m_parent;

		CLType* m_cls = nullptr;
		unique_ptr<CLMethod> m_function = nullptr;

		string m_clsname;
		string m_type;

		string m_member;
		string m_name;
		string m_capname;

		std::vector<string> m_annotations;

		bool m_pointer;
		bool m_reference;

		bool m_nonmutable = false;
		bool m_structure = false;
		bool m_link = false;
		//bool m_component = false;

		bool m_output = false;
		bool m_input = false;

		bool m_setter;

		bool m_has_default = false;
		string m_default = "";
	};

	class CLClass : public CLType
	{
	public:
		CLClass(CLModule& module, CXCursor cursor, CLPrimitive& parent);

		string m_idstr;

		CXCursor m_cursor;

		std::vector<CLConstructor> m_constructors;
		std::vector<CLMember> m_members;
		std::vector<CLMethod> m_methods;
		std::vector<CLStatic> m_statics;

		std::vector<string> m_annotations;

		bool m_struct = false;
		bool m_array = false;
		size_t m_array_size = 0;
		CLType* m_array_type = nullptr;
		bool m_extern = false;

		string m_template_name;
		bool m_template_used = false;
		CLClass* m_template;
		std::vector<string> m_template_types;

		//CLClass* m_stem = nullptr;
		//m_parts = []
		//m_isModular = false
		//m_isProto = false

		void parse_contents(CXCursor cursor);
		void parse_child(CXCursor cursor);

	#if 0
		void fix_template_element(name):
			if(m_template && name in m_template.template_types:
				return m_template_types[m_template.template_types.index(name)]
			else:
				return name
    
		void fix_template(name):
			# first fix nested template types
			real_types = [m_fix_template_element(t) for t in template_types(name)]
			name = substitute_template(name, template_types(name), real_types)
			# then fix type itself in case it is a template parameter
			return m_fix_template_element(name)
			#print "substituted template base name: ", name
    
	#endif
	};

	class CLContext
	{
	public:
		CLContext()
			: m_root_namespace("")
		{
			m_namespaces[""] = m_root_namespace;

			m_base_types = { "void", "bool", "int", "float", "double", "char", "unsigned char", "short", "unsigned short", "int", "unsigned int", "long", "unsigned long", "long long", "unsigned long long", "std::string", "cstring" };
			m_base_aliases = { "uint8_t", "uint16_t", "uint32_t", "uint64_t", "size_t", "mud::Id" };
		}

		CLNamespace m_root_namespace;

		std::map<string, CLType*> m_types;
		std::map<string, CLClass*> m_class_templates;
		std::map<string, CLFunction*> m_func_templates;

		std::map<string, CLNamespace> m_namespaces;

		std::vector<string> m_base_types;
		std::vector<string> m_base_aliases;

		CLNamespace& get_namespace(const string& name, CLPrimitive& parent)
		{
			string full_name = parent.m_prefix + name;
			if(m_namespaces.find(full_name) == m_namespaces.end())
				m_namespaces[full_name] = CLNamespace(name, &parent);
			return m_namespaces[full_name];
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

		CLContext m_context;
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

		std::vector<CLFile*> m_headers = {};
		std::vector<CLFile*> m_sources = {};
    
		std::vector<unique_ptr<CLClass>> m_classes = {};
		std::vector<unique_ptr<CLClass>> m_class_templates = {};
		std::vector<unique_ptr<CLEnum>> m_enums = {};
		std::vector<unique_ptr<CLSequence>> m_sequences = {};
		std::vector<unique_ptr<CLBaseType>> m_basetypes = {};
		std::vector<unique_ptr<CLType>> m_extern_types = {};

		std::vector<CLType*> m_types = {};

		std::vector<unique_ptr<CLFunction>> m_functions = {};
		std::vector<unique_ptr<CLFunction>> m_func_templates = {};

		//print m_path
        
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

		CLType* find_type_in(CLPrimitive* parent, const string& name, bool warn = true)
		{
			// stupid fix because clang FUCKING doesn"t always put the prefix in types ..............
			if(has(m_context.m_types, name))
				return m_context.m_types[name];
			else if(parent && has(m_context.m_types, parent->m_prefix + name))
				return m_context.m_types[parent->m_prefix + name];
			else if(parent && parent->m_parent)
				return this->find_type_in(parent->m_parent, name, warn);
			else
				return nullptr;
		}

		void register_type(CLType& type)
		{
			if(!type.m_is_template)
			{
				m_context.m_types[type.m_id] = &type;
				m_types.push_back(&type);
				printf("Type %s\n", type.m_id.c_str());
			}
			else
			{
				//m_templates.push_back(&type);
				printf("Template %s\n", type.m_id.c_str());
			}
		}

		CLFunction& function(CXCursor cursor, CLPrimitive& parent)
		{
			//print "Function ", cursor.displayname
			CLFunction& func = vector_emplace<CLFunction>(m_functions, *this, cursor, parent);
			return func;
		}

		CLFunction& function_template(CXCursor cursor, CLPrimitive& parent)
		{
			//print "Function Template ", cursor.displayname
			CLFunction& func = vector_emplace<CLFunction>(m_functions, *this, cursor, parent);
			m_context.m_func_templates[func.m_name] = &func;
			return func;
		}

		CLType& base_type(const string& name, CLPrimitive& parent)
		{
			CLType& type = vector_emplace<CLBaseType>(m_basetypes, *this, name, parent);
			register_type(type);
			return type;
		}

		CLType& proxy_type(const string& name, CLPrimitive& parent)
		{
			//m_extern_types.push_back(make_unique<CLTypeProxy>(name));
			CLType& type = vector_emplace<CLType>(m_extern_types, *this, name, parent);
			register_type(type);
			return type;
		}

		CLEnum& enum_type(CXCursor cursor, CLPrimitive& parent)
		{
			CLEnum& type = vector_emplace<CLEnum>(m_enums, *this, cursor, parent);
			register_type(type);
			return type;
		}

		CLSequence& sequence_type(const string& name, const string& content_name, CLType& content_type)
		{
			//#print ">>>>>>>>>>>> register_type Sequence", name, content_type.name, content_name
			bool pointer = content_name.find("*") != string::npos;
			CLSequence& cls = vector_emplace<CLSequence>(m_sequences, *this, name, content_type, pointer, m_context.m_root_namespace);
			register_type(cls);
			return cls;
		}

		CLClass& class_type(CXCursor cursor, CLPrimitive& parent)
		{
			CLClass& cls = vector_emplace<CLClass>(m_classes, *this, cursor, parent);
			register_type(cls);
			return cls;
		}

		CLClass& class_template(CXCursor cursor, CLPrimitive& parent)
		{
			CLClass& cls = vector_emplace<CLClass>(m_class_templates, *this, cursor, parent);
			register_type(cls);
			m_context.m_class_templates[cls.m_template_name] = &cls;
			return cls;
		}

		CLType& register_type(CLPrimitive& parent, const string& clsname)
		{
			for(const string& name : { "std::vector", "std::list", "mud::array", "array" })
				if(clsname.find(name) == 0)
				{
					string content_name = clsname.substr(clsname.find("<") + 1);
					CLType* content_type = this->find_type(parent, replace(content_name, "*", ""));
					if(content_type)
						return sequence_type(name, content_name, *content_type);
				}
			for(const string& name : { "unique_ptr", "object_ptr" })
				if(clsname.find(name) != string::npos)
				{
					return this->proxy_type(clsname, parent);
				}
			printf("WARNING: declaring empty type %s\n", clsname.c_str());
			return this->proxy_type(clsname, parent);
		}

		CLType* find_type(CLPrimitive& parent, const string& name, bool warn = true)
		{
			if(has(m_context.m_base_types, name) || has(m_context.m_base_aliases, name))
				return &this->proxy_type(name, parent);
			CLType* cls = this->find_type_in(&parent, name, warn);
			if(!cls)
			{
				for(auto name_namespace : m_context.m_namespaces)
				{
					cls = this->find_type_in(&name_namespace.second, name, warn);
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