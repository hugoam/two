//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
#include <lang/WrenLib.h>
module two.lang;

//#define TWO_WREN_DEBUG_DECLS
//#define TWO_WREN_DEBUG
#define TWO_WREN_CACHE_HANDLES
//#define TWO_WREN_OPTIMIZE_SET_MEMBER

namespace two
{
	inline WrenInterpreter* wren(WrenVM* vm) { return (WrenInterpreter*) wrenGetUserData(vm); }
	inline const TextScript* wren_script(WrenVM* vm) { return wren(vm)->m_script; }

	void wren_error(WrenVM* vm, WrenErrorType type, const char* module, int line, const char* message)
	{
		const TextScript* script = wren_script(vm);
		if(script && type == WREN_ERROR_COMPILE)
			script->m_compile_errors[line] = { size_t(line), size_t(0), string("^ ") + message };
		else if(script && type == WREN_ERROR_RUNTIME)
			script->m_runtime_errors[-1] = { size_t(line), size_t(0), string("^ ") + message };
		else if(script && type == WREN_ERROR_STACK_TRACE)
		{
			if(script->m_runtime_errors.find(-1) != script->m_runtime_errors.end())
			{
				script->m_runtime_errors[line] = script->m_runtime_errors[-1];
				script->m_runtime_errors[line].m_line = size_t(line);
				script->m_runtime_errors.erase(-1);
			}
		}
		else
			error("wren -> %s:%i %s\n", module, line, message);
	}

	void wren_print(WrenVM* vm, const char* text)
	{
		UNUSED(vm);
		printf("%s\n", text);
	}

	class FromWren : public Dispatch<void, WrenVM*, int, Ref&>, public LazyGlobal<FromWren>
	{
	public:
		FromWren();
	};

	class ToWren : public Dispatch<void, WrenVM*, int>, public LazyGlobal<ToWren>
	{
	public:
		ToWren();
	};

	inline void read_sequence(WrenVM* vm, int slot, const Type& sequence_type, Ref result);
	inline void push_sequence(WrenVM* vm, int slot, Ref value);

	inline void read_enum(WrenVM* vm, int slot, Ref result);
	inline void push_enum(WrenVM* vm, int slot, Ref value);

	inline void push_null(WrenVM* vm, int slot);

	inline Call& cached_call(const Callable& callable)
	{
		static vector<unique<Call>> call_table;
		if(callable.m_index >= call_table.size())
			call_table.resize(callable.m_index + 1);

		if(!call_table[callable.m_index])
			call_table[callable.m_index] = construct<Call>(callable);
		return *call_table[callable.m_index];
	}

	vector<WrenHandle*> g_wren_types = vector<WrenHandle*>(c_max_types);
	vector<WrenHandle*> g_wren_classes = vector<WrenHandle*>(c_max_types);
	vector<WrenHandle*> g_wren_methods = vector<WrenHandle*>(c_max_types * 8);
	vector<WrenHandle*> g_construct_handles;

	//map<void*, WrenHandle*> g_wren_objects;
	unordered_map<void*, WrenHandle*> g_wren_objects;

	string signature(cstring name, size_t num_args)
	{
		string sig = string(name) + "(";
		for(size_t i = 0; i < num_args; ++i)
			sig += "_" + (i == num_args - 1 ? string("") : string(","));
		sig += ")";
		return sig;
	}

	struct WrenRef : public Ref
	{
		WrenRef(bool alloc, void* pointer, const Type& type) : Ref(pointer, type), m_alloc(alloc) {}
		bool m_alloc;
	};

	inline WrenRef wren_ref(WrenVM* vm, int slot)
	{
		return *static_cast<WrenRef*>(wrenGetSlotForeign(vm, slot));
	}

	inline Ref read_ref(WrenVM* vm, int slot)
	{
		WrenType slot_type = wrenGetSlotType(vm, slot);
		if(slot_type == WREN_TYPE_NULL) return Ref();
		else if(slot_type != WREN_TYPE_FOREIGN) return Ref();
		else return wren_ref(vm, slot);
	}

	inline void read_object(WrenVM* vm, int slot, const Type& type, Ref& result)
	{
		WrenType slot_type = wrenGetSlotType(vm, slot);
		if(slot_type == WREN_TYPE_NULL) result = Ref(type);
		else if(slot_type == WREN_TYPE_FOREIGN)
		{
			Ref ref = wren_ref(vm, slot);
			Ref object = cls(ref).upcast(ref, type);
			if(object.m_type->is(type))
				result = object;
		}
	}

	inline const Type& read_type(WrenVM* vm, int slot)
	{
		Ref ref = read_ref(vm, slot);
		return val<Type>(ref);
	}

	inline void read_value(WrenVM* vm, int index, const Type& type, Ref& result)
	{
		FromWren::me().dispatch(Ref(type), vm, index, result);
		//if(result.none())
		//	printf("ERROR : wren -> reading wrong type %s expected %s\n", "", type.m_name);//lua_typename(vm, lua_type(vm, index)), type.m_name);
	}

	inline Ref alloc_object(WrenVM* vm, int slot, int class_slot, const Type& type)
	{
		//printf("[debug] Wren -> alloc object %s\n", type.m_name);
		WrenRef* ref = static_cast<WrenRef*>(wrenSetSlotNewForeign(vm, slot, class_slot, sizeof(WrenRef) + meta(type).m_size));
		new (stl::placeholder(), ref) WrenRef(true, ref + 1, type);
		return *ref;
	}

	inline Ref alloc_ref(WrenVM* vm, int slot, int class_slot, Ref source)
	{
		//printf("[debug] Wren -> alloc ref %s\n", type(source).m_name);
		WrenRef* ref = static_cast<WrenRef*>(wrenSetSlotNewForeign(vm, slot, class_slot, sizeof(WrenRef)));
		new (stl::placeholder(), ref) WrenRef(false, source.m_value, *source.m_type);
		return *ref;
	}

	inline Ref alloc_object(WrenVM* vm, int slot, const Type& type)
	{
		int class_slot = wrenGetSlotCount(vm);
		wrenEnsureSlots(vm, class_slot + 1);
		wrenSetSlotHandle(vm, class_slot, g_wren_classes[type.m_id]);
		Ref object = alloc_object(vm, slot, class_slot, type);
#ifdef TWO_WREN_CACHE_HANDLES
		assert(g_wren_objects[object.m_value] == nullptr);
		g_wren_objects[object.m_value] = wrenGetSlotHandle(vm, slot);
#endif
		return object;
	}

	inline Ref alloc_ref(WrenVM* vm, int slot, Ref ref)
	{
		int class_slot = wrenGetSlotCount(vm);
		wrenEnsureSlots(vm, class_slot + 1);
		wrenSetSlotHandle(vm, class_slot, g_wren_classes[type(ref).m_id]);
		Ref object = alloc_ref(vm, slot, class_slot, ref);
#ifdef TWO_WREN_CACHE_HANDLES
		assert(g_wren_objects[object.m_value] == nullptr);
		g_wren_objects[object.m_value] = wrenGetSlotHandle(vm, slot);
#endif
		return object;
	}

	inline void push_ref(WrenVM* vm, int slot, Ref object)
	{
		if(!object) push_null(vm, slot);
#ifdef TWO_WREN_CACHE_HANDLES
		WrenHandle*& handle = g_wren_objects[object.m_value];
		if(!handle)
			alloc_ref(vm, slot, object);
		wrenSetSlotHandle(vm, slot, handle);
#else
		alloc_ref(vm, slot, object);
#endif
	}

	inline void push_object(WrenVM* vm, int slot, Ref value)
	{
		if(!value) push_null(vm, slot);
		Ref ref = alloc_object(vm, slot, *value.m_type);
		copy_construct(ref, value);
	}

	inline void push_val(WrenVM* vm, int slot, Ref value)
	{
		if(!ToWren::me().check(value))
		{
			printf("ERROR : wren -> no dispatch to push_value type %s\n", value.m_type->m_name);
			push_null(vm, slot);
		}
		ToWren::me().dispatch(value, vm, slot);
	}

	inline void read_value(WrenVM* vm, int index, Ref& value)
	{
		if(value == Ref())
			value = read_ref(vm, index);
		else if(type(value).is<Type>())
			value = read_ref(vm, index);
		else if(is_sequence(type(value)))
			read_sequence(vm, index, type(value), value);
		else if(is_object(type(value)) || is_struct(type(value)))
			read_object(vm, index, type(value), value);
		else if(is_enum(type(value)))
			read_enum(vm, index, value);
		else
			read_value(vm, index, type(value), value);
	}

	inline void push_value(WrenVM* vm, int slot, Ref value, bool force_ref = true)
	{
		// @todo: what about automatic conversion as with visual scripts ? it might not belong here, maybe in read_value() ?
		// @todo: might want a case for is_complex() before is_object() ?
		const Type& ty = type(value);
		if(!value)
			push_null(vm, slot);
		else if(is_sequence(ty))
			push_sequence(vm, slot, value);
		else if(is_object(ty) || (is_struct(ty) && force_ref))
			push_ref(vm, slot, value);
		else if(is_struct(ty))
			push_object(vm, slot, value);
		else if(is_enum(ty))
			push_enum(vm, slot, value);
		else
			push_val(vm, slot, value);
	}

	inline bool read_params(WrenVM* vm, const Callable& callable, span<Var> vars, size_t offset, size_t first_slot)
	{
		size_t num_args = wrenGetSlotCount(vm) - first_slot;
		for(size_t i = offset; i < offset + num_args; ++i)
		{
			read_value(vm, int(first_slot - offset + i), vars[i].m_ref);
			bool success = !vars[i].none();
			success &= callable.m_params[i].nullable() || !vars[i].null();
			if(!success)
			{
#ifdef TWO_WREN_DEBUG
				error("wren -> wrong argument %s, expect type %s, got %s\n", callable.m_params[i].m_name, type(callable.m_params[i].m_value).m_name, type(vars[i]).m_name);
#endif
				return false;
			}
		}
		for(size_t i = offset + max(num_args, callable.m_num_required - offset); i < vars.size(); ++i)
			vars[i] = callable.m_params[i].default_val();
		return true;
	}

	inline void call_cpp(WrenVM* vm, Call& call, size_t first, size_t num_arguments)
	{
		bool enough_arguments = num_arguments >= call.m_callable->m_num_required;
		if(enough_arguments && read_params(vm, *call.m_callable, call.m_args, 0, first))
		{
			call();
			if(!call.m_result.none())
				push_value(vm, 0, call.m_result);
		}
		else
			error("wren -> %s wrong arguments\n", call.m_callable->m_name);
	}

	inline void call_function(WrenVM* vm, size_t num_args)
	{
		const Callable& callable = val<Callable>(wren_ref(vm, 0));
#ifdef TWO_WREN_DEBUG
		info("wren -> call function %s\n", callable.m_name);
#endif
		Call& call = cached_call(callable);
		call_cpp(vm, call, 1, num_args);
	}

	template <size_t num_args>
	void call_function_args(WrenVM* vm)
	{
		call_function(vm, num_args);
	}

	inline void call_method(WrenVM* vm, size_t num_args)
	{
		const Callable& callable = val<Callable>(read_ref(vm, 0));
#ifdef TWO_WREN_DEBUG
		info("wren -> call method %s\n", callable.m_name);
#endif
		Call& call = cached_call(callable);
		call_cpp(vm, call, 1, num_args + 1);
	}

	template <size_t num_args>
	void call_method_args(WrenVM* vm)
	{
		call_method(vm, num_args);
	}

	inline void call_wren(WrenVM* vm, WrenHandle* method, WrenHandle* object, span<Var> parameters, Var* result = nullptr)
	{
		wrenBegin(vm);
		wrenEnsureSlots(vm, int(parameters.m_count + 1));
		wrenSetSlotHandle(vm, 0, object);
		for(int i = 0; i < int(parameters.size()); ++i)
			push_value(vm, i + 1, parameters[i]);
		wrenCall(vm, method);
		if(result) read_value(vm, 0, *result);
	}

	inline void call_wren_virtual(WrenVM* vm, Method& method, Ref object, span<Var> parameters)
	{
#ifdef TWO_WREN_DEBUG
		info("wren -> call wren %s\n", method.m_name);
#endif
		WrenHandle* hmethod = g_wren_methods[method.m_index];
		WrenHandle* hobject = g_wren_objects[object.m_value];
		call_wren(vm, hmethod, hobject, parameters);
	}

	inline void get_member(WrenVM* vm)
	{
		const Member& member = val<Member>(read_ref(vm, 0));
#ifdef TWO_WREN_DEBUG
		info("wren -> get member %s\n", member.m_name);
#endif
		Ref object = read_ref(vm, 1);
		Ref value = member.cast_get(object);
		push_value(vm, 0, value);
	}

	inline void set_member(WrenVM* vm)
	{
		const Member& member = val<Member>(read_ref(vm, 0));
#ifdef TWO_WREN_DEBUG
		info("wren -> set member %s\n", member.m_name);
#endif
		Ref object = read_ref(vm, 1);
#ifdef TWO_WREN_OPTIMIZE_SET_MEMBER
		Ref value = member.cast_get(object);
		read_value(vm, 2, value);
		if(member.is_pointer())
			member.cast_set(object, value);
#else
		Var value = member.m_default_value;
		read_value(vm, 2, value);
		member.cast_set(object, value);
#endif
	}

	inline void get_static(WrenVM* vm)
	{
		const Static& member = val<Static>(read_ref(vm, 0));
		push_value(vm, 0, member.m_value);
	}

	inline void set_static(WrenVM* vm)
	{
		Ref ref = read_ref(vm, 0);
		Static& member = val<Static>(ref);
		Var result = member.m_value;
		read_value(vm, 1, result);
		assign(member.m_value, result);
	}

	inline void construct(WrenVM* vm)
	{
		const Constructor* constructor = &val<Constructor>(read_ref(vm, 0));
		if(!constructor) return;
#ifdef TWO_WREN_DEBUG
		info("wren -> construct %s\n", constructor->m_name);
#endif
		Call& construct = cached_call(*constructor);
		if(read_params(vm, *construct.m_callable, construct.m_args, 1, 2))
		{
			Ref object = alloc_object(vm, 0, 1, *constructor->m_object_type);
			construct(object);
		}
	}

	inline void copy_construct(WrenVM* vm)
	{
		const CopyConstructor* constructor = &val<CopyConstructor>(read_ref(vm, 0));
		if(!constructor) return;
#ifdef TWO_WREN_DEBUG
		info("wren -> copy construct %s\n", constructor->m_name);
#endif
		
		Ref object = alloc_object(vm, 0, 1, *constructor->m_object_type);
		Ref other = read_ref(vm, 2);
		//constructor(object, other);
	}

	inline void construct_interface(WrenVM* vm)
	{
		WrenInterpreter* wren = two::wren(vm);
		const Constructor* constructor = &val<Constructor>(read_ref(vm, 0));
		if(!constructor) return;
#ifdef TWO_WREN_DEBUG
		info("wren -> construct %s\n", constructor->m_name);
#endif
		Call& construct = cached_call(*constructor);
		VirtualMethod virtual_method = [=](Method& method, Ref object, span<Var> args) { wren->virtual_call(method, object, args); };
		construct.m_args.back() = var(virtual_method);
		if(read_params(vm, *construct.m_callable, construct.m_args, 1, 2))
		{
			Ref object = alloc_object(vm, 0, 1, *constructor->m_object_type);
			construct(object);
			assert(g_wren_objects[object.m_value] == nullptr);
			g_wren_objects[object.m_value] = wrenGetSlotHandle(vm, 0);
			wren->create_virtual(object);
		}
	}

	inline void destroy(void* memory)
	{
		WrenRef ref = *(WrenRef*)memory;
		//if(ref.m_alloc && cls(ref).m_destructor.size() > 0)
		//	cls(ref).m_destructor[0].m_call(ref);
	}

	inline void register_enum(WrenVM* vm, string module, string name, const Type& type)
	{
		Enum& enu = two::enu(type);

		string t = "    ";

		string members;
		for(size_t i = 0; i < enu.m_names.size(); ++i)
		{
			members += t + "static " + string(enu.m_names[i]) + " { " + to_string(enu.m_values[i]) + " }\n";
		}

		string decl;
		decl += "class " + name + " {\n";
		decl += members;
		decl += "}\n";

#ifdef TWO_WREN_DEBUG_DECLS
		printf("%s\n", decl.c_str());
#endif

		wrenInterpret(vm, module.c_str(), decl.c_str());
	}

	inline string callable_params(Callable& callable, size_t offset, size_t count)
	{
		if(count == offset)
			return string(""); 
		string params;
		for(const Param& param : span<Param>{ callable.m_params, offset, count - offset })
		{
			params += param.m_name;
			params += ",";
		}
		params.pop_back();
		return params;
	}

	inline void register_class(WrenVM* vm, string module, string name, const Type& type)
	{
		if(type.is<Function>() || type.is<Type>() || type.is<Constructor>() || type.is<CopyConstructor>() || type.is<Method>() || type.is<Member>() || type.is<Static>()) return;
		if(type.is<Class>() || type.is<Creator>() || type.is<System>()) return;

		string constructors;
		string members;
		string methods;
		string statics;
		string bind;

		string t = "    ";
		string c = type.m_name;

		bind += t + t + "__ty = Type.ref(\"" + c + "\")\n";

		for(Constructor& constructor : cls(type).m_constructors)
		{
			string n = "constructor" + to_string(constructor.m_index);

			bind += t + t + "__" + n + " = Constructor.ref(\"" + c + "\", " + to_string(constructor.m_index) + ")\n";

			for(size_t count = constructor.m_num_required; count <= constructor.m_params.size(); ++count)
			{
				string params = callable_params(constructor, 1, count);
				string paramsnext = params.empty() ? "" : ", " + params;

				if(constructor.m_name == string(constructor.m_object_type->m_name))
					constructors += t + "static new(" + params + ") { __" + n + ".call(this" + paramsnext + ") }\n";
				else
					constructors += t + "static " + constructor.m_name + "(" + params + ") { __" + n + ".call(this" + paramsnext + ") }\n";
			}
		}

		for(CopyConstructor& constructor : cls(type).m_copy_constructors)
		{
			UNUSED(constructor);

			bind += t + t + "__copy_constructor = CopyConstructor.ref(\"" + c + "\")\n";

			constructors += t + "static copy(other) { __copy_constructor.call(this, other) }\n";
		}

		for(Member& member : cls(type).m_members)
		{
			string n = string(member.m_name);

			bind += t + t + "__" + n + " = Member.ref(\"" + c + "\", \"" + n + "\")\n";

			members += t + n + " { __" + n + ".get(this) }\n";
			if(member.is_mutable())
				members += t + n + "=(value) { __" + n + ".set(this, value) }\n";
		}

		for(Method& method : cls(type).m_methods)
		{
			string n = string(method.m_name);
			bind += t + t + "__" + n + " = Method.ref(\"" + c + "\", \"" + n + "\")\n";

			for(size_t count = method.m_num_required; count <= method.m_params.size(); ++count)
			{
				string params = callable_params(method, 1, count);
				string paramsnext = params.empty() ? "" : ", " + params;

				methods += t + n + "(" + params + ") { __" + n + ".call(this" + paramsnext + ") }\n";
			}
		}

		for(Operator& op : cls(type).m_operators)
		{
			bind += t + t + "__" + op.m_name + " = Operator.ref(\"" + op.m_name + "\", \"" + op.m_type->m_name + "\")\n";

			methods += t + op.m_sign + "(other) { __" + op.m_name + ".call(this, other) }\n";
		}

		for(Static& static_member : cls(type).m_static_members)
		{
			string n = string(static_member.m_name);

			bind += t + t + "__" + n + " = Static.ref(\"" + c + "\", \"" + n + "\")\n";

			statics += t + "static " + n + " { __" + n + ".get() }\n";
			statics += t + "static " + n + "=(value) { __" + n + ".set(value) }\n";
		}

		string decl;
		decl += "foreign class " + name + " {\n";
		decl += "\n";
		decl += constructors;
		decl += "\n";
		decl += members;
		decl += "\n";
		decl += methods;
		decl += "\n";
		decl += statics;
		decl += "\n";
		decl += t + "static type { __ty }\n";
		decl += t + "static bind() {\n";
		decl += bind;
		decl += t + "}\n";
		decl += "\n";
		decl += "}\n";
		decl += "\n";
		decl += name + ".bind()\n";

#ifdef TWO_WREN_DEBUG_DECLS
		printf("%s\n", decl.c_str());
#endif

		WrenInterpretResult result = wrenInterpret(vm, module.c_str(), decl.c_str());

		if(result != WREN_RESULT_SUCCESS)
		{
			error("could not declare wren class %s", name.c_str());
			return;
		}

		wrenBegin(vm);
		wrenEnsureSlots(vm, 1);
		wrenGetVariable(vm, module.c_str(), name.c_str(), 0);
		assert(g_wren_classes[type.m_id] == nullptr);
		g_wren_classes[type.m_id] = wrenGetSlotHandle(vm, 0);
	}

	Function* find_function(cstring nemespace, cstring name, size_t num_args)
	{
		for(Function* function : system().m_functions)
			if(function->m_namespace->m_name == string(nemespace) && function->m_name == string(name) && function->m_params.size() == num_args)
				return function;
		return nullptr;
	}

	WrenForeignClassMethods bindForeignClass(WrenVM* vm, const char* module, const char* className)
	{
		UNUSED(vm); UNUSED(module);

		WrenForeignClassMethods methods = {};

		if(strcmp(className, "Function") == 0)
		{
			methods.allocate = [](WrenVM* vm)
			{
				const char* n = wrenGetSlotString(vm, 1);
				const char* f = wrenGetSlotString(vm, 2);
				size_t num_args = size_t(wrenGetSlotDouble(vm, 3));
				Function* function = find_function(n, f, num_args);
				alloc_ref(vm, 0, 0, Ref(function));
			};
		}
		else if(strcmp(className, "Type") == 0)
		{
			methods.allocate = [](WrenVM* vm)
			{
				const char* name = wrenGetSlotString(vm, 1);
				Type* type = system().find_type(name);
				if(g_wren_types[type->m_id] != nullptr)
					warn("type %s already fetched", name);
				else
				{
					alloc_ref(vm, 0, 0, Ref(type));
					g_wren_types[type->m_id] = wrenGetSlotHandle(vm, 0);
				}
			};
		}
		else if(strcmp(className, "Constructor") == 0)
		{
			methods.allocate = [](WrenVM* vm)
			{
				const char* c = wrenGetSlotString(vm, 1);
				size_t index = size_t(wrenGetSlotDouble(vm, 2));
				Type* type = system().find_type(c);
				const Constructor* constructor = &cls(*type).m_constructors[index];
				alloc_ref(vm, 0, 0, Ref(constructor));
			};
		}
		else if(strcmp(className, "CopyConstructor") == 0)
		{
			methods.allocate = [](WrenVM* vm)
			{
				const char* c = wrenGetSlotString(vm, 1);
				Type* type = system().find_type(c);
				const CopyConstructor* constructor = &cls(*type).m_copy_constructors[0];
				alloc_ref(vm, 0, 0, Ref(constructor));
			};
		}
		else if(strcmp(className, "Member") == 0)
		{
			methods.allocate = [](WrenVM* vm)
			{
				const char* c = wrenGetSlotString(vm, 1);
				const char* m = wrenGetSlotString(vm, 2);
				Type* type = system().find_type(c);
				Member* member = &cls(*type).member(m);
				alloc_ref(vm, 0, 0, Ref(member));
			};
		}
		else if(strcmp(className, "Static") == 0)
		{
			methods.allocate = [](WrenVM* vm)
			{
				const char* c = wrenGetSlotString(vm, 1);
				const char* m = wrenGetSlotString(vm, 2);
				Type* type = system().find_type(c);
				Static* member = &cls(*type).static_member(m);
				alloc_ref(vm, 0, 0, Ref(member));
			};
		}
		else if(strcmp(className, "Method") == 0)
		{
			methods.allocate = [](WrenVM* vm)
			{
				const char* c = wrenGetSlotString(vm, 1);
				const char* m = wrenGetSlotString(vm, 2);
				Type* type = system().find_type(c);
				Method* method = &cls(*type).method(m);
				alloc_ref(vm, 0, 0, Ref(method));
			};
		}
		else if(strcmp(className, "Operator") == 0)
		{
			methods.allocate = [](WrenVM* vm)
			{
				const char* f = wrenGetSlotString(vm, 1);
				const char* t = wrenGetSlotString(vm, 2);
				Type* type = system().find_type(t);
				Function* function = cls(*type).op(f).m_function;
				alloc_ref(vm, 0, 0, Ref(function));
			};
		}
		else if(strcmp(className, "VirtualConstructor") == 0)
		{
			methods.allocate = [](WrenVM* vm)
			{
				const char* c = wrenGetSlotString(vm, 1);
				Type* type = system().find_type(c);
				const Constructor* constructor = &cls(*type).m_constructors[0];
				alloc_ref(vm, 0, 0, Ref(constructor));
				
				for(Method& method : cls(*type).m_methods)
				{
					string sig = signature(method.m_name, method.m_params.size() - 1);
					g_wren_methods[method.m_index] = wrenMakeCallHandle(vm, sig.c_str());
				}
			};
		}
		
		if(strcmp(className , "Random") != 0)
			methods.finalize = destroy;

		return methods;
	}

	WrenForeignMethodFn bindForeignMethod(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature)
	{
		UNUSED(vm); UNUSED(module); UNUSED(isStatic);

		if(strcmp(className, "Function") == 0)
		{
			if(strcmp(signature, "call()") == 0)
				return call_function_args<0>;
			if(strcmp(signature, "call(_)") == 0)
				return call_function_args<1>;
			if(strcmp(signature, "call(_,_)") == 0)
				return call_function_args<2>;
			if(strcmp(signature, "call(_,_,_)") == 0)
				return call_function_args<3>;
			if(strcmp(signature, "call(_,_,_,_)") == 0)
				return call_function_args<4>;
			if(strcmp(signature, "call(_,_,_,_,_)") == 0)
				return call_function_args<5>;
			if(strcmp(signature, "call(_,_,_,_,_,_)") == 0)
				return call_function_args<6>;
			if(strcmp(signature, "call(_,_,_,_,_,_,_)") == 0)
				return call_function_args<7>;
			if(strcmp(signature, "call(_,_,_,_,_,_,_,_)") == 0)
				return call_function_args<8>;
			if(strcmp(signature, "call(_,_,_,_,_,_,_,_,_)") == 0)
				return call_function_args<9>;
		}

		if(strcmp(className, "Type") == 0)
		{
			if(strcmp(signature, "new(_)") == 0)
			return [](WrenVM* vm)
			{
				const char* name = wrenGetSlotString(vm, 1);
				Ref t = alloc_object(vm, 0, 0, type<Type>());
				Type* type = new (stl::placeholder(), t.m_value) Type(name);
				assert(g_wren_types[type->m_id] == nullptr);
				g_wren_types[type->m_id] = wrenGetSlotHandle(vm, 0);
			};
		}

		if(strcmp(className, "Operator") == 0)
		{
			if(strcmp(signature, "call(_,_)") == 0)
				return call_function_args<2>;
		}

		if(strcmp(className, "Constructor") == 0)
		{
			return construct;
		}

		if(strcmp(className, "CopyConstructor") == 0)
		{
			return copy_construct;
		}

		if(strcmp(className, "Member") == 0)
		{
			if(strcmp(signature, "get(_)") == 0)
				return get_member;
			if(strcmp(signature, "set(_,_)") == 0)
				return set_member;
		}

		if(strcmp(className, "Static") == 0)
		{
			if(strcmp(signature, "get()") == 0)
				return get_static;
			if(strcmp(signature, "set(_)") == 0)
				return set_static;
		}

		if(strcmp(className, "Method") == 0)
		{
			if(strcmp(signature, "call(_)") == 0)
				return call_method_args<0>;
			if(strcmp(signature, "call(_,_)") == 0)
				return call_method_args<1>;
			if(strcmp(signature, "call(_,_,_)") == 0)
				return call_method_args<2>;
			if(strcmp(signature, "call(_,_,_,_)") == 0)
				return call_method_args<3>;
			if(strcmp(signature, "call(_,_,_,_,_)") == 0)
				return call_method_args<4>;
			if(strcmp(signature, "call(_,_,_,_,_,_)") == 0)
				return call_method_args<5>;
		}

		if(strcmp(className, "VirtualConstructor") == 0)
		{
			return construct_interface;
		}

		// Unknown method.
		return NULL;
	}

	template <class T>
	inline void read_integer(WrenVM* vm, int slot, Ref result)
	{
		if(wrenGetSlotType(vm, slot) == WREN_TYPE_NUM)
			val<T>(result) = static_cast<T>(wrenGetSlotDouble(vm, slot));
	}

	template <class T>
	inline void read_number(WrenVM* vm, int slot, Ref result)
	{
		if(wrenGetSlotType(vm, slot) == WREN_TYPE_NUM)
			val<T>(result) = static_cast<T>(wrenGetSlotDouble(vm, slot));
	}

	void read_cstring(WrenVM* vm, int slot, Ref& result)
	{
		if(wrenGetSlotType(vm, slot) == WREN_TYPE_STRING)
			(cstring&)(result.m_value) = wrenGetSlotString(vm, slot);
	}

	inline void read_string(WrenVM* vm, int slot, Ref result)
	{
		if(wrenGetSlotType(vm, slot) == WREN_TYPE_STRING)
			val<string>(result) = wrenGetSlotString(vm, slot);
	}

	inline void read_null(WrenVM* vm, int slot, Ref result)
	{
		if(wrenGetSlotType(vm, slot) == WREN_TYPE_NULL)
			result = Ref();
	}

	inline void read_enum(WrenVM* vm, int slot, Ref result)
	{
		if(wrenGetSlotType(vm, slot) == WREN_TYPE_NUM)
			enu(result).varn(uint32_t(wrenGetSlotDouble(vm, slot)), result);
	}

	inline void read_sequence(WrenVM* vm, int slot, const Type& sequence_type, Ref result)
	{
		if(wrenGetSlotType(vm, slot) != WREN_TYPE_LIST)
			return;

		wrenEnsureSlots(vm, slot + 2);
		int count = wrenGetListCount(vm, slot);

		for(int i = 0; i < count; ++i)
		{
			Var element = meta(*iter(sequence_type).m_element_type).m_empty_ref;
			wrenGetListElement(vm, slot, i, slot + 1);
			read_value(vm, slot + 1, element);
			sequence(result).add(result, element);
		}
	}

	FromWren::FromWren()
	{
		function<int>     ([](void*, Ref, WrenVM* vm, int slot, Ref& result) { read_integer<int>(vm, slot, result); });
		function<ushort>  ([](void*, Ref, WrenVM* vm, int slot, Ref& result) { read_integer<ushort>(vm, slot, result); });
		function<uint>    ([](void*, Ref, WrenVM* vm, int slot, Ref& result) { read_integer<uint>(vm, slot, result); });
		function<ulong>   ([](void*, Ref, WrenVM* vm, int slot, Ref& result) { read_integer<ulong>(vm, slot, result); });
		function<ullong>  ([](void*, Ref, WrenVM* vm, int slot, Ref& result) { read_integer<ullong>(vm, slot, result); });
		function<float>   ([](void*, Ref, WrenVM* vm, int slot, Ref& result) { read_number<float>(vm, slot, result); });
		function<double>  ([](void*, Ref, WrenVM* vm, int slot, Ref& result) { read_number<double>(vm, slot, result); });
		function<cstring> ([](void*, Ref, WrenVM* vm, int slot, Ref& result) { read_cstring(vm, slot, result); });
		function<string>  ([](void*, Ref, WrenVM* vm, int slot, Ref& result) { read_string(vm, slot, result); });
		function<bool>    ([](void*, Ref, WrenVM* vm, int slot, Ref& result) { val<bool>(result) = wrenGetSlotBool(vm, slot); });

		function<Type>([](void*, Ref, WrenVM* vm, int slot, Ref& result) { result = read_ref(vm, slot); });
	}

	inline void push_null(WrenVM* vm, int slot)
	{
		wrenSetSlotNull(vm, slot);
	}

	inline void push_bool(WrenVM* vm, int slot, bool value)
	{
		wrenSetSlotBool(vm, slot, value);
	}

	inline void push_string(WrenVM* vm, int slot, const string& value)
	{
		wrenSetSlotString(vm, slot, value.c_str());
	}

	inline void push_cstring(WrenVM* vm, int slot, const char* value)
	{
		wrenSetSlotString(vm, slot, value);
	}

	template <class T>
	inline void push_integer(WrenVM* vm, int slot, T value)
	{
		wrenSetSlotDouble(vm, slot, double(value));
	}

	template <class T>
	inline void push_scalar(WrenVM* vm, int slot, T value)
	{
		wrenSetSlotDouble(vm, slot, double(value));
	}

	inline void push_dict(WrenVM* vm, int slot, Ref value)
	{
		UNUSED(vm); UNUSED(slot); UNUSED(value);
		//iterdict(value).iterate(value, [=](Var key, Var element) {
		//	set_table(vm, key, element); });
		//});
	}

	inline void push_sequence(WrenVM* vm, int slot, Ref value)
	{
		wrenSetSlotNewList(vm, slot);
		int slots = wrenGetSlotCount(vm);
		wrenEnsureSlots(vm, slots + 1);

		int index = 1;
		iter(value).iterate(value, [&](Ref element) {
			push_value(vm, slots, element);
			wrenInsertInList(vm, slot, index, slots);
		});
	}

	inline void push_enum(WrenVM* vm, int slot, Ref value)
	{
		wrenSetSlotDouble(vm, slot, double(enu(value).index(value)));
	}

	ToWren::ToWren()
	{
		function<void>([](void*, Ref, WrenVM* vm, int slot) { return push_null(vm, slot); });

		dispatch_branch<int>     (*this, +[](int&      value, WrenVM* vm, int slot) { return push_integer(vm, slot, value); });
		dispatch_branch<ushort>  (*this, +[](ushort&   value, WrenVM* vm, int slot) { return push_integer(vm, slot, value); });
		dispatch_branch<uint>    (*this, +[](uint&     value, WrenVM* vm, int slot) { return push_integer(vm, slot, value); });
		dispatch_branch<ulong>   (*this, +[](ulong&    value, WrenVM* vm, int slot) { return push_integer(vm, slot, value); });
		dispatch_branch<ullong>  (*this, +[](ullong&   value, WrenVM* vm, int slot) { return push_integer(vm, slot, value); });
		dispatch_branch<float>   (*this, +[](float&    value, WrenVM* vm, int slot) { return push_scalar(vm, slot, value); });
		dispatch_branch<double>  (*this, +[](double&   value, WrenVM* vm, int slot) { return push_scalar(vm, slot, value); });
		dispatch_branch<cstring> (*this, +[](cstring   value, WrenVM* vm, int slot) { return push_cstring(vm, slot, value); });
		dispatch_branch<string>  (*this, +[](string&   value, WrenVM* vm, int slot) { return push_string(vm, slot, value); });
		dispatch_branch<bool>    (*this, +[](bool&     value, WrenVM* vm, int slot) { return push_bool(vm, slot, value); });
	}

	class WrenContext
	{
	public:
		explicit WrenContext(WrenInterpreter& interpreter, map<string, string> namespaces = {})
			: m_namespaces(namespaces)
		{
			WrenConfiguration config;
			wrenInitConfiguration(&config);

			config.bindForeignClassFn = bindForeignClass;
			config.bindForeignMethodFn = bindForeignMethod;
			config.errorFn = wren_error;
			config.writeFn = wren_print;
			config.userData = &interpreter;

			m_vm = wrenNewVM(&config);
		}

		~WrenContext()
		{
			auto release = [&](vector<WrenHandle*>& handles)
			{
				for(WrenHandle*& handle : handles)
					if(handle)
					{
						wrenReleaseHandle(m_vm, handle);
						handle = nullptr;
					}
			};

			release(g_wren_types);
			release(g_wren_classes);
			release(g_wren_methods);
			release(g_construct_handles);

			for(auto& object_handle : g_wren_objects)
				wrenReleaseHandle(m_vm, object_handle.second);

			g_construct_handles.clear();
			g_wren_objects.clear();

			assert(m_vm);
			wrenFreeVM(m_vm);
		}

		void register_primitives()
		{
			for(size_t num_args = 0; num_args < 6; ++num_args)
			{
				string signature = "construct" + to_string(num_args) + "(";
				for(size_t i = 0; i < num_args; ++i)
					signature += "_" + (i == num_args - 1 ? string("") : string(","));
				signature += ")";

				g_construct_handles.push_back(wrenMakeCallHandle(m_vm, signature.c_str()));
			}

			string primitives =
				"foreign class Function {\n"
				"    construct ref(namespace, name, num_args) {}\n"
				"    \n"
				"    foreign call()\n"
				"    foreign call(a0)\n"
				"    foreign call(a0, a1)\n"
				"    foreign call(a0, a1, a2)\n"
				"    foreign call(a0, a1, a2, a3)\n"
				"    foreign call(a0, a1, a2, a3, a4)\n"
				"    foreign call(a0, a1, a2, a3, a4, a5)\n"
				"    foreign call(a0, a1, a2, a3, a4, a5, a6)\n"
				"    foreign call(a0, a1, a2, a3, a4, a5, a6, a7)\n"
				"    foreign call(a0, a1, a2, a3, a4, a5, a6, a7, a8)\n"
				"}\n"
				"\n"
				"foreign class Type {\n"
				"    foreign static new(name)\n"
				"    construct ref(name) {}\n"
				"}\n"
				"\n"
				"foreign class Constructor {\n"
				"    construct ref(class_name, index) {}\n"
				"    \n"
				"    foreign call(cls)\n"
				"    foreign call(cls, a0)\n"
				"    foreign call(cls, a0, a1)\n"
				"    foreign call(cls, a0, a1, a2)\n"
				"    foreign call(cls, a0, a1, a2, a3)\n"
				"    foreign call(cls, a0, a1, a2, a3, a4)\n"
				"    foreign call(cls, a0, a1, a2, a3, a4, a5)\n"
				"}\n"
				"\n"
				"foreign class CopyConstructor {\n"
				"    construct ref(class_name) {}\n"
				"    \n"
				"    foreign call(cls, other)\n"
				"}\n"
				"\n"
				"foreign class Member {\n"
				"    construct ref(class_name, member_name) {}\n"
				"    \n"
				"    foreign get(object)\n"
				"    foreign set(object, value)\n"
				"}\n"
				"\n"
				"foreign class Static {\n"
				"    construct ref(class_name, member_name) {}\n"
				"    \n"
				"    foreign get()\n"
				"    foreign set(value)\n"
				"}\n"
				"\n"
				"foreign class Method {\n"
				"    construct ref(class_name, method_name) {}\n"
				"    \n"
				"    foreign call(object)\n"
				"    foreign call(object, a0)\n"
				"    foreign call(object, a0, a1)\n"
				"    foreign call(object, a0, a1, a2)\n"
				"    foreign call(object, a0, a1, a2, a3)\n"
				"    foreign call(object, a0, a1, a2, a3, a4)\n"
				"}\n"
				"\n"
				"foreign class Operator {\n"
				"    construct ref(name, class_name) {}\n"
				"    \n"
				"    foreign call(a0, a1)\n"
				"}\n"
				"\n"
				"foreign class VirtualConstructor {\n"
				"    construct ref(class_name) {}\n"
				"    \n"
				"    foreign call(cls)\n"
				"    foreign call(cls, a0)\n"
				"}\n"
				;

			wrenInterpret(m_vm, "main", primitives.c_str());

			wrenBegin(m_vm);
			wrenEnsureSlots(m_vm, 1);
			wrenGetVariable(m_vm, "main", "Type", 0);
			assert(g_wren_classes[type<Type>().m_id] == nullptr);
			g_wren_classes[type<Type>().m_id] = wrenGetSlotHandle(m_vm, 0);
		}

		span<cstring> namespace_path(Namespace& location)
		{
			if(location.is_root())
				return {};
			else
				return location.m_path;
		}

		void register_namespace(Namespace& location)
		{
			if(location.is_root())
				return;
			string imports = "import \"main\" for Function, Type, Constructor, CopyConstructor, Member, Method, Static, Operator, VirtualConstructor\n";
			wrenInterpret(m_vm, location.m_name, imports.c_str());
		}

		string clean_name(cstring name)
		{
			if(name == string("Ui")) return "UiRoot";
			string result = replace(replace(replace(name, "<", "_"), ">", ""), "*", "");
			for(auto& nemespace : m_namespaces)
				result = replace(result, nemespace.first + "::", "");
			result[0] = char(toupper(result[0]));
			return result;
		}

		void register_type(const Type& type)
		{
			if(!g_meta[type.m_id])
			{
				warn("wren - type %s doesn't have reflection meta type\n", type.m_name);
				return;
			}

			auto module = [&](const Type& type) -> string
			{
				if(meta(type).m_namespace->m_name != string(""))
					return m_namespaces[string(meta(type).m_namespace->m_name)];
				else
					return "main";
			};

			string name = clean_name(type.m_name);
			if(is_class(type))
				register_class(m_vm, module(type), name, type);
			if(is_enum(type))
				register_enum(m_vm, module(type), name, type);
		}

		void register_function(Function& function)
		{
			if(as_operator(function))
				return;

			span<cstring> path = namespace_path(*function.m_namespace);

			string c = path.size() > 0 ? to_pascalcase(path[path.m_count - 1]) : "Module";
			string n = string(function.m_name);
			string parent = function.m_namespace->m_name;

			WrenFunctionDecl& decls = m_function_decls[c];

			decls.bind += "        __" + n + " = Function.ref(\"" + parent + "\", \"" + n + "\", " + to_string(function.m_params.size()) + ")\n";

			for(size_t count = function.m_num_required; count <= function.m_params.size(); ++count)
			{
				string params = callable_params(function, 0, count);
				string paramsnext = params.empty() ? "" : ", " + params;

				decls.functions += "    static " + n + "(" + params + ") { __" + n + ".call(" + params + ") }\n";
			}
		}

		void declare_namespace(Namespace& location)
		{
			string c = location.m_name != string("") ? to_pascalcase(location.m_name) : "Module";

			if(m_function_decls.find(c) == m_function_decls.end())
				return;

			WrenFunctionDecl& decls = m_function_decls[c];

			string decl;
			decl += "class " + c + " {\n";
			decl += decls.functions;
			decl += "\n";
			decl += "    static bind() {\n";
			decl += decls.bind;
			decl += "    }\n";
			decl += "}\n";
			decl += "\n";
			decl += c + ".bind()\n";

#ifdef TWO_WREN_DEBUG_DECLS
			printf("%s\n", decl.c_str());
#endif

			string parent = location.m_parent ? location.m_parent->m_name : "";
			string module = parent != "" ? m_namespaces[parent] : "main";
			wrenInterpret(m_vm, module.c_str(), decl.c_str());
		}

		map<string, string> m_namespaces;
		map<string, WrenFunctionDecl> m_function_decls;

		set<string> m_variables;

		WrenVM* m_vm;
	};
}

namespace two
{
	static map<string, string> namespaces()
	{
		map<string, string> n;
		n["two"] = "toy";
		n["ui"]  = "toy";
		n["gfx"] = "toy";
		n["toy"] = "toy";
		return n;
	}

	WrenInterpreter::WrenInterpreter(bool import_symbols)
		: m_context(construct<WrenContext>(*this, namespaces()))
	{
		//g_lua_print_output = &m_output;
		if(import_symbols)
			this->declare_types();
	}

	WrenInterpreter::~WrenInterpreter()
	{}

	void WrenInterpreter::declare_types()
	{
		System& system = System::instance();

		m_context->register_primitives();

		for(Namespace& location : system.m_namespaces)
			m_context->register_namespace(location);

		for(Function* function : system.m_functions)
			m_context->register_function(*function);
		
		for(Namespace& location : system.m_namespaces)
			m_context->declare_namespace(location);

		for(Type* type : system.m_types)
			m_context->register_type(*type);

		this->flush();
	}

	Var WrenInterpreter::get(const string& name, const Type& type)
	{
		wrenBegin(m_context->m_vm);
		wrenEnsureSlots(m_context->m_vm, 1);
		wrenGetVariable(m_context->m_vm, "main", name.c_str(), 0);
		Var result = Ref(&type);
		read_value(m_context->m_vm, 0, result);
		return result;
	}

	void WrenInterpreter::set(const string& name, const Var& value)
	{
		if(m_context->m_variables.find(name) == m_context->m_variables.end())
		{
			string create = "var " + string(name) + " = null";
			wrenInterpret(m_context->m_vm, "main", create.c_str());
			m_context->m_variables.insert(name);
		}
		wrenBegin(m_context->m_vm);
		wrenEnsureSlots(m_context->m_vm, 1);
		push_value(m_context->m_vm, 0, value);
		wrenAssignVariable(m_context->m_vm, "main", name.c_str(), 0);
	}

	Var WrenInterpreter::getx(span<cstring> path, const Type& type)
	{
		UNUSED(path); UNUSED(type);
		return Var();
	}

	void WrenInterpreter::setx(span<cstring> path, const Var& value)
	{
		UNUSED(path); UNUSED(value);
	}

	void WrenInterpreter::call(const string& code, Var* result)
	{
		UNUSED(result);
		wrenInterpret(m_context->m_vm, "main", code.c_str());
	}

	void WrenInterpreter::virtual_call(Method& method, Ref object, span<Var> args)
	{
		m_script = m_virtual_scripts[object.m_value];
		call_wren_virtual(m_context->m_vm, method, object, args);
	}

	void WrenInterpreter::create_virtual(Ref object)
	{
		m_virtual_scripts[object.m_value] = m_script;
	}
}
