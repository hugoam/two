//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>
#ifndef MUD_CPP_20
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <type_traits>
#endif

#ifdef MUD_MODULES
#include <stdlib.h>
module mud.lang;
#else
#include <proto/Proto.h>
#include <infra/NonCopy.h>
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <refl/Sequence.h>
#include <obj/Any.h>
#include <infra/Vector.h>
#include <refl/System.h>
#include <obj/Dispatch.h>
#include <obj/DispatchDecl.h>
#include <infra/Global.h>
#include <lang/Types.h>
#include <lang/Wren.h>
#endif

extern "C"
{
#include <wren.h>

void wrenBegin(WrenVM* vm);

void wrenAssignVariable(WrenVM* vm, const char* module, const char* name,
						int value_slot);
}

//#define MUD_WREN_DEBUG_DECLS
//#define MUD_WREN_DEBUG
#define MUD_WREN_CACHE_HANDLES
//#define MUD_WREN_OPTIMIZE_SET_MEMBER

namespace mud
{
	void wren_error(WrenVM* vm, WrenErrorType type, const char* module, int line, const char* message)
	{
		UNUSED(vm);
		printf("ERROR: wren -> %s:%i %s\n", module, line, message);
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

	inline void read_sequence(WrenVM* vm, int slot, Type& sequence_type, Ref result);
	inline void push_sequence(WrenVM* vm, int slot, Ref value);

	inline void read_enum(WrenVM* vm, int slot, Type& type, Ref result);
	inline void push_enum(WrenVM* vm, int slot, Ref value);

	inline void push_null(WrenVM* vm, int slot);

	inline Call& cached_call(const Callable& callable)
	{
		static std::vector<object_ptr<Call>> call_table;
		if(callable.m_index >= call_table.size())
			call_table.resize(callable.m_index + 1);

		if(!call_table[callable.m_index])
			call_table[callable.m_index] = make_object<Call>(callable);
		return *call_table[callable.m_index];
	}

	std::vector<WrenHandle*> g_wren_types = std::vector<WrenHandle*>(c_max_types);
	std::vector<WrenHandle*> g_wren_classes = std::vector<WrenHandle*>(c_max_types);
	std::vector<WrenHandle*> g_wren_methods = std::vector<WrenHandle*>(c_max_types * 8);
	std::vector<WrenHandle*> g_construct_handles;

	//std::map<void*, WrenHandle*> g_wren_objects;
	std::unordered_map<void*, WrenHandle*> g_wren_objects;

	string signature(cstring name, size_t num_args)
	{
		string sig = string(name) + "(";
		for (size_t i = 0; i < num_args; ++i)
			sig += "_" + (i == num_args - 1 ? string("") : string(","));
		sig += ")";
		return sig;
	}

	struct WrenRef : public Ref
	{
		WrenRef(bool alloc, void* pointer, Type& type) : Ref(pointer, type), m_alloc(alloc) {}
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

	inline void read_object(WrenVM* vm, int slot, Type& type, Ref& result)
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

	inline Type& read_type(WrenVM* vm, int slot)
	{
		Ref ref = read_ref(vm, slot);
		return val<Type>(ref);
	}

	inline void read_value(WrenVM* vm, int index, Type& type, Ref& result)
	{
		FromWren::me().dispatch(Ref(type), vm, index, result);
		//if(result.none())
		//	printf("ERROR : wren -> reading wrong type %s expected %s\n", "", type.m_name);//lua_typename(vm, lua_type(vm, index)), type.m_name);
	}

	inline Ref alloc_object(WrenVM* vm, int slot, int class_slot, Type& type)
	{
		//printf("DEBUG: Wren -> alloc object %s\n", type.m_name);
		WrenRef* ref = static_cast<WrenRef*>(wrenSetSlotNewForeign(vm, slot, class_slot, sizeof(WrenRef) + meta(type).m_size));
		new (ref) WrenRef(true, ref + 1, type);
		return *ref;
	}

	inline Ref alloc_ref(WrenVM* vm, int slot, int class_slot, Ref source)
	{
		//printf("DEBUG: Wren -> alloc ref %s\n", type(source).m_name);
		WrenRef* ref = static_cast<WrenRef*>(wrenSetSlotNewForeign(vm, slot, class_slot, sizeof(WrenRef)));
		new (ref) WrenRef(false, source.m_value, *source.m_type);
		return *ref;
	}

	inline Ref alloc_object(WrenVM* vm, int slot, Type& type)
	{
		int class_slot = wrenGetSlotCount(vm);
		wrenEnsureSlots(vm, class_slot + 1);
		wrenSetSlotHandle(vm, class_slot, g_wren_classes[type.m_id]);
		Ref object = alloc_object(vm, slot, class_slot, type);
#ifdef MUD_WREN_CACHE_HANDLES
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
#ifdef MUD_WREN_CACHE_HANDLES
		assert(g_wren_objects[object.m_value] == nullptr);
		g_wren_objects[object.m_value] = wrenGetSlotHandle(vm, slot);
#endif
		return object;
	}

	inline void push_ref(WrenVM* vm, int slot, Ref object)
	{
		if(!object) push_null(vm, slot);
#ifdef MUD_WREN_CACHE_HANDLES
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

	inline void push_value(WrenVM* vm, int slot, Ref value)
	{
		if(!ToWren::me().check(value))
		{
			printf("ERROR : wren -> no dispatch to push type %s\n", value.m_type->m_name);
			push_null(vm, slot);
		}
		ToWren::me().dispatch(value, vm, slot);
	}

	inline void read(WrenVM* vm, int index, Ref& value)
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
			read_enum(vm, index, type(value), value);
		else
			read_value(vm, index, type(value), value);
	}

	inline void push(WrenVM* vm, int slot, Ref value, bool force_ref = true)
	{
		// @todo: what about automatic conversion as with visual scripts ? it might not belong here, maybe in read() ?
		// @todo: might want a case for is_complex() before is_object() ?
		Type& ty = type(value);
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
			push_value(vm, slot, value);
	}

	inline bool read_params(WrenVM* vm, const Param* params, array<Var> vars, size_t first)
	{
		wrenEnsureSlots(vm, first + vars.m_count);
		for(size_t i = 0; i < vars.m_count; ++i)
		{
			read(vm, int(first) + int(i), vars[i].m_ref);
			bool success = !vars[i].none();
			success &= params[i].nullable() || !vars[i].null();
#ifdef MUD_WREN_DEBUG
			if(!success)
			{
				printf("ERROR: wren -> wrong argument %s, expect type %s, got %s\n", params[i].m_name, type(params[i].m_value).m_name, type(vars[i]).m_name);
				return false;
			}
#endif
		}
		return true;
	}

	inline void call_cpp(WrenVM* vm, Call& call, size_t first, size_t num_arguments)
	{
		bool enough_arguments = num_arguments >= call.m_arguments.size() - call.m_callable->m_num_defaults;
		if(enough_arguments && read_params(vm, &call.m_callable->m_params[0], to_array(call.m_arguments, 0, num_arguments), first))
		{
			call();
			if(!call.m_result.none())
				push(vm, 0, call.m_result);
		}
		else
			printf("ERROR: wren -> %s wrong arguments\n", call.m_callable->m_name);
	}

	inline void call_function(WrenVM* vm, size_t num_args)
	{
		const Callable& callable = val<Callable>(wren_ref(vm, 0));
#ifdef MUD_WREN_DEBUG
		printf("INFO: wren -> call function %s\n", callable.m_name);
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
#ifdef MUD_WREN_DEBUG
		printf("INFO: wren -> call method %s\n", callable.m_name);
#endif
		Call& call = cached_call(callable);
		call_cpp(vm, call, 1, num_args + 1);
	}

	template <size_t num_args>
	void call_method_args(WrenVM* vm)
	{
		call_method(vm, num_args);
	}

	inline void call_wren(WrenVM* vm, WrenHandle* method, WrenHandle* object, array<Var> parameters, Var* result = nullptr)
	{
		wrenBegin(vm);
		wrenEnsureSlots(vm, parameters.m_count + 1);
		wrenSetSlotHandle(vm, 0, object);
		for(size_t i = 0; i < parameters.size(); ++i)
			push(vm, i + 1, parameters[i]);
		wrenCall(vm, method);
		if(result) read(vm, 0, *result);
	}

	inline void call_wren_virtual(WrenVM* vm, Method& method, Ref object, array<Var> parameters)
	{
#ifdef MUD_WREN_DEBUG
		printf("INFO: wren -> call wren %s\n", method.m_name);
#endif
		WrenHandle* hmethod = g_wren_methods[method.m_index];
		WrenHandle* hobject = g_wren_objects[object.m_value];
		call_wren(vm, hmethod, hobject, parameters);
	}

	inline void get_member(WrenVM* vm)
	{
		const Member& member = val<Member>(read_ref(vm, 0));
#ifdef MUD_WREN_DEBUG
		printf("INFO: wren -> get member %s\n", member.m_name);
#endif
		Ref object = read_ref(vm, 1);
		Ref value = member.cast_get(object);
		push(vm, 0, value);
	}

	inline void set_member(WrenVM* vm)
	{
		const Member& member = val<Member>(read_ref(vm, 0));
#ifdef MUD_WREN_DEBUG
		printf("INFO: wren -> set member %s\n", member.m_name);
#endif
		Ref object = read_ref(vm, 1);
#ifdef MUD_WREN_OPTIMIZE_SET_MEMBER
		//if (member.m_name == string("value"))
		//	int i = 0;
		Ref value = member.cast_get(object);
		read(vm, 2, value);
		if(member.is_pointer())
			member.cast_set(object, value);
#else
		Var value = member.m_default_value;
		read(vm, 2, value);
		member.cast_set(object, value);
#endif
	}

	inline void get_static(WrenVM* vm)
	{
		const Static& member = val<Static>(read_ref(vm, 0));
		push(vm, 0, member.m_value);
	}

	inline void set_static(WrenVM* vm)
	{
		Ref ref = read_ref(vm, 0);
		Static& member = val<Static>(ref);
		Var result = member.m_value;
		read(vm, 1, result);
		assign(member.m_value, result);
	}

	inline void construct(WrenVM* vm)
	{
		const Constructor* constructor = &val<Constructor>(read_ref(vm, 0));
		if(!constructor) return;
#ifdef MUD_WREN_DEBUG
		printf("INFO: wren -> construct %s\n", constructor->m_name);
#endif
		Call& construct = cached_call(*constructor);
		if(read_params(vm, &construct.m_callable->m_params[1], to_array(construct.m_arguments, 1), 2))
		{
			Ref object = alloc_object(vm, 0, 1, *constructor->m_object_type);
			construct(object);
		}
	}

	inline void copy_construct(WrenVM* vm)
	{
		const CopyConstructor* constructor = &val<CopyConstructor>(read_ref(vm, 0));
		if (!constructor) return;
#ifdef MUD_WREN_DEBUG
		printf("INFO: wren -> copy construct %s\n", constructor->m_name);
#endif
		
		Ref object = alloc_object(vm, 0, 1, *constructor->m_object_type);
		Ref other = read_ref(vm, 2);
		constructor->m_call(object, other);
	}

	inline void construct_interface(WrenVM* vm)
	{
		const Constructor* constructor = &val<Constructor>(read_ref(vm, 0));
		if (!constructor) return;
#ifdef MUD_WREN_DEBUG
		printf("INFO: wren -> construct %s\n", constructor->m_name);
#endif
		Call& construct = cached_call(*constructor);
		VirtualMethod virtual_method = [=](Method& method, Ref object, array<Var> args) { call_wren_virtual(vm, method, object, args); };
		construct.m_arguments.back() = var(virtual_method);
		if (read_params(vm, &construct.m_callable->m_params[1], to_array(construct.m_arguments, 1), 2))
		{
			Ref object = alloc_object(vm, 0, 1, *constructor->m_object_type);
			construct(object);
			assert(g_wren_objects[object.m_value] == nullptr);
			g_wren_objects[object.m_value] = wrenGetSlotHandle(vm, 0);
		}
	}

	inline void destroy(void* memory)
	{
		WrenRef ref = *(WrenRef*)memory;
		if(ref.m_alloc && cls(ref).m_destructor.size() > 0)
			cls(ref).m_destructor[0].m_call(ref);
	}

	inline void register_enum(WrenVM* vm, string name, Type& type)
	{
		Enum& enu = mud::enu(type);

		string t = "    ";

		string members;
		for(size_t i = 0; i < enu.m_names.size(); ++i)
		{
			members += t + "static " + string(enu.m_names[i]) + " { " + to_string(enu.m_indices[i]) + " }\n";
		}

		string decl;
		decl += "class " + name + " {\n";
		decl += members;
		decl += "}\n";

		string module = meta(type).m_namespace->m_name != string("") ? meta(type).m_namespace->m_name : "main";

#ifdef MUD_WREN_DEBUG_DECLS
		printf("%s\n", decl.c_str());
#endif

		wrenInterpret(vm, module.c_str(), decl.c_str());
	}

	inline void register_class(WrenVM* vm, string name, Type& type)
	{
		if(type.is<Function>() || type.is<Type>() || type.is<Constructor>() || type.is<Method>() || type.is<Member>() || type.is<Static>()) return;
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
			string params = [&]() { if(constructor.m_params.size() == 1) return string("");  string params; for(Param& param : to_array(constructor.m_params, 1)) { params += param.m_name; params += ","; } params.pop_back(); return params; }();
			string paramsnext = params.empty() ? "" : ", " + params;

			bind += t + t + "__" + n + " = Constructor.ref(\"" + c + "\", " + to_string(constructor.m_index) + ")\n";

			constructors += t + "static new(" + params + ") { __" + n + ".call(this" + paramsnext + ") }\n";
		}

		for(CopyConstructor& constructor : cls(type).m_copy_constructors)
		{
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
			string params = [&]() { if(method.m_params.size() == 1) return string("");  string params; for(Param& param : to_array(method.m_params, 1)) { params += param.m_name; params += ","; } params.pop_back(); return params; }();
			string paramsnext = params.empty() ? "" : ", " + params;

			bind += t + t + "__" + n + " = Method.ref(\"" + c + "\", \"" + n + "\")\n";

			methods += t + n + "(" + params + ") { __" + n + ".call(this" + paramsnext + ") }\n";
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

		string module = meta(type).m_namespace->m_name != string("") ? meta(type).m_namespace->m_name : "main";

#ifdef MUD_WREN_DEBUG_DECLS
		printf("%s\n", decl.c_str());
#endif

		WrenInterpretResult result = wrenInterpret(vm, module.c_str(), decl.c_str());

		if(result != WREN_RESULT_SUCCESS)
		{
			printf("ERROR: could not declare wren class %s\n", name.c_str());
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
		for (Function* function : system().m_functions)
			if (function->m_namespace->m_name == string(nemespace) && function->m_name == string(name) && function->m_params.size() == num_args)
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
				if (g_wren_types[type->m_id] != nullptr)
					printf("WARNING: type %s already fetched\n", name);
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
		
		if(className != string("Random"))
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
				Type* type = new (t.m_value) Type(name);
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
	inline void read_integer(WrenVM* vm, int slot, Ref result) // std::is_integral<T>::value
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

	inline void read_enum(WrenVM* vm, int slot, Type& type, Ref result)
	{
		if(wrenGetSlotType(vm, slot) == WREN_TYPE_NUM)
			enum_set_index(result, size_t(wrenGetSlotDouble(vm, slot)));
	}

	inline void read_sequence(WrenVM* vm, int slot, Type& sequence_type, Ref result)
	{
		if(wrenGetSlotType(vm, slot) != WREN_TYPE_LIST)
			return;

		wrenEnsureSlots(vm, slot + 2);
		int count = wrenGetListCount(vm, slot);

		for(int i = 0; i < count; ++i)
		{
			Var element = meta(*cls(sequence_type).m_content).m_empty_ref;
			wrenGetListElement(vm, slot, i, slot + 1);
			read(vm, slot + 1, element);
			add_sequence(result, element);
		}
	}

	FromWren::FromWren()
	{
		function<int>([](Ref, WrenVM* vm, int slot, Ref& result) { read_integer<int>(vm, slot, result); });
		function<uint32_t>([](Ref, WrenVM* vm, int slot, Ref& result) { read_integer<uint32_t>(vm, slot, result); });
		function<float>([](Ref, WrenVM* vm, int slot, Ref& result) { read_number<float>(vm, slot, result); });
		function<cstring>([](Ref, WrenVM* vm, int slot, Ref& result) { read_cstring(vm, slot, result); });
		function<string>([](Ref, WrenVM* vm, int slot, Ref& result) { read_string(vm, slot, result); });
		function<Id>([](Ref, WrenVM* vm, int slot, Ref& result) { read_integer<Id>(vm, slot, result); });
		function<bool>([](Ref, WrenVM* vm, int slot, Ref& result) { val<bool>(result) = wrenGetSlotBool(vm, slot); });

		function<Type>([](Ref, WrenVM* vm, int slot, Ref& result) { result = read_ref(vm, slot); });
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

	template<typename T>
	inline void push_integer(WrenVM* vm, int slot, T value)
	{
		wrenSetSlotDouble(vm, slot, double(value));
	}

	template<typename T>
	inline void push_scalar(WrenVM* vm, int slot, T value)
	{
		wrenSetSlotDouble(vm, slot, double(value));
	}

	inline void push_dict(WrenVM* vm, int slot, Ref value)
	{
		iterate_dict(value, [=](Var key, Var element) {
		//	set_table(vm, key, element); });
		});
	}

	inline void push_sequence(WrenVM* vm, int slot, Ref value)
	{
		wrenSetSlotNewList(vm, slot);
		size_t slots = wrenGetSlotCount(vm);
		wrenEnsureSlots(vm, slots + 1);

		size_t index = 1;
		iterate_sequence(value, [&](Ref element) {
			push(vm, slots, element);
			wrenInsertInList(vm, slot, index, slots);
		});
	}

	inline void push_enum(WrenVM* vm, int slot, Ref value)
	{
		wrenSetSlotDouble(vm, slot, double(enum_index(value)));
	};

	ToWren::ToWren()
	{
		function<void>([](Ref, WrenVM* vm, int slot) { return push_null(vm, slot); });

		dispatch_branch<int>     (*this, [](int&      value, WrenVM* vm, int slot) { return push_integer(vm, slot, value); });
		dispatch_branch<uint16_t>(*this, [](uint16_t& value, WrenVM* vm, int slot) { return push_integer(vm, slot, value); });
		dispatch_branch<uint32_t>(*this, [](uint32_t& value, WrenVM* vm, int slot) { return push_integer(vm, slot, value); });
		dispatch_branch<uint64_t>(*this, [](uint64_t& value, WrenVM* vm, int slot) { return push_integer(vm, slot, value); });
		dispatch_branch<float>   (*this, [](float&    value, WrenVM* vm, int slot) { return push_scalar(vm, slot, value); });
		dispatch_branch<double>  (*this, [](double&   value, WrenVM* vm, int slot) { return push_scalar(vm, slot, value); });
		dispatch_branch<cstring> (*this, [](cstring   value, WrenVM* vm, int slot) { return push_cstring(vm, slot, value); });
		dispatch_branch<string>  (*this, [](string&   value, WrenVM* vm, int slot) { return push_string(vm, slot, value); });
		dispatch_branch<bool>    (*this, [](bool&     value, WrenVM* vm, int slot) { return push_bool(vm, slot, value); });
	}

	class WrenContext : public NonCopy
	{
	public:
		explicit WrenContext(std::vector<string> import_namespaces = {})
			: m_import_namespaces(import_namespaces)
		{
			WrenConfiguration config;
			wrenInitConfiguration(&config);

			config.bindForeignClassFn = bindForeignClass;
			config.bindForeignMethodFn = bindForeignMethod;
			config.errorFn = wren_error;
			config.writeFn = wren_print;

			m_vm = wrenNewVM(&config);
		}

		~WrenContext()
		{
			auto release = [&](std::vector<WrenHandle*>& handles)
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
			for (size_t num_args = 0; num_args < 6; ++num_args)
			{
				string signature = "construct" + to_string(num_args) + "(";
				for (size_t i = 0; i < num_args; ++i)
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

		array<cstring> namespace_path(Namespace& location)
		{
			if(location.is_root())
				return array<cstring>{};
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
			string result = replace_all(replace_all(replace_all(name, "<", "_"), ">", ""), "*", "");
			for(string n : m_import_namespaces)
				result = replace_all(result, n + "::", "");
			result[0] = char(toupper(result[0]));
			return result;
		}

		void register_type(Type& type)
		{
			string name = clean_name(type.m_name);
			if(is_class(type))
				register_class(m_vm, name, type);
			if(is_enum(type))
				register_enum(m_vm, name, type);
		}

		void register_function(Function& function)
		{
			if(as_operator(function))
				return;

			array<cstring> path = namespace_path(*function.m_namespace);

			string c = path.size() > 0 ? to_pascalcase(path[path.m_count-1]) : "Module";
			string n = string(function.m_name);
			string parent = function.m_namespace->m_name;
			string params = [&]() { if(function.m_params.size() == 0) return string(""); string params; for(Param& param : function.m_params) { params += param.m_name; params += ","; } params.pop_back(); return params; }();
			string paramsnext = params.empty() ? "" : ", " + params;

			Functions& decls = m_function_decls[c];

			decls.functions += "    static " + n + "(" + params + ") { __" + n + ".call(" + params + ") }\n";

			decls.bind += "        __" + n + " = Function.ref(\"" + parent + "\", \"" + n + "\", " + to_string(function.m_params.size()) + ")\n";
		}

		void declare_namespace(Namespace& location)
		{
			string c = location.m_name != string("") ? to_pascalcase(location.m_name) : "Module";

			if(m_function_decls.find(c) == m_function_decls.end())
				return;

			Functions& decls = m_function_decls[c];

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

#ifdef MUD_WREN_DEBUG_DECLS
			printf("%s\n", decl.c_str());
#endif

			string parent = location.m_parent ? location.m_parent->m_name : "";
			string module = parent != "" ? parent : "main";
			wrenInterpret(m_vm, module.c_str(), decl.c_str());
		}

		std::vector<string> m_import_namespaces;

		struct Functions
		{
			string functions;
			string bind;
		};

		std::map<string, Functions> m_function_decls;

		std::set<string> m_variables;

		WrenVM* m_vm;
	};
}


namespace mud
{
	WrenInterpreter::WrenInterpreter(bool import_symbols)
		: m_context(make_unique<WrenContext>(std::vector<string>{ "mud", "toy" }))
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
	}

	Var WrenInterpreter::get(cstring name, Type& type)
	{
		wrenBegin(m_context->m_vm);
		wrenEnsureSlots(m_context->m_vm, 1);
		wrenGetVariable(m_context->m_vm, "main", name, 0);
		Var result = Ref(&type);
		read(m_context->m_vm, 0, result);
		return result;
	}

	void WrenInterpreter::set(cstring name, Var value)
	{
		if(m_context->m_variables.find(name) == m_context->m_variables.end())
		{
			string create = "var " + string(name) + " = null";
			wrenInterpret(m_context->m_vm, "main", create.c_str());
			m_context->m_variables.insert(name);
		}
		wrenBegin(m_context->m_vm);
		wrenEnsureSlots(m_context->m_vm, 1);
		push(m_context->m_vm, 0, value);
		wrenAssignVariable(m_context->m_vm, "main", name, 0);
	}

	Var WrenInterpreter::getx(array<cstring> path, Type& type)
	{
		UNUSED(path); UNUSED(type);
		return Var();
	}

	void WrenInterpreter::setx(array<cstring> path, Var value)
	{
		UNUSED(path); UNUSED(value);
	}

	void WrenInterpreter::call(cstring code, Var* result)
	{
		wrenInterpret(m_context->m_vm, "main", code);
	}

	void WrenInterpreter::virtual_call(Method& method, Ref object, array<Var> args)
	{
		call_wren_virtual(m_context->m_vm, method, object, args);
	}
}
