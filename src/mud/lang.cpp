#include <mud/pool.h>
#include <mud/lang.h>
#include <mud/ecs.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.lang;
#else
#include <stl/tinystl/vector.impl.h>
#include <stl/tinystl/unordered_map.impl.h>
#endif

using namespace mud;
namespace tinystl
{
	template class MUD_LANG_EXPORT vector<Pipe*>;
	template class MUD_LANG_EXPORT vector<Valve*>;
	template class MUD_LANG_EXPORT vector<ProcessInput*>;
	template class MUD_LANG_EXPORT vector<ProcessOutput*>;
	template class MUD_LANG_EXPORT vector<Process*>;
	template class MUD_LANG_EXPORT vector<Script*>;
	template class MUD_LANG_EXPORT vector<VisualScript*>;
	template class MUD_LANG_EXPORT vector<TextScript*>;
	template class MUD_LANG_EXPORT vector<StreamBranch>;
	template class MUD_LANG_EXPORT vector<StreamModifier>;
	template class MUD_LANG_EXPORT vector<unique<Valve>>;
	template class MUD_LANG_EXPORT vector<unique<Pipe>>;
	template class MUD_LANG_EXPORT vector<unique<Process>>;
	template class MUD_LANG_EXPORT vector<unique<Call>>;
	template class MUD_LANG_EXPORT unordered_map<int, ScriptError>;
	template class MUD_LANG_EXPORT unordered_map<void*, const TextScript*>;
	template class MUD_LANG_EXPORT unordered_map<string, WrenFunctionDecl>;

	template class MUD_LANG_EXPORT vector<WrenHandle*>;
	template class MUD_LANG_EXPORT unordered_map<void*, WrenHandle*>;
}

#ifndef MUD_CPP_20
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <new>
#endif

#ifdef MUD_MODULES
#include <stdlib.h>
module mud.lang;
#else
#include <stl/vector.h>
#endif

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

//#define MUD_LUA_DEBUG
//#define MUD_LUA_DEBUG_IO

// @todo: there is a weird thing where there are constantly about 10 tables on the stack when entering a script
// so we are missing a pop somewhere in the paths used when declaring reflected types and functions probably

namespace mud
{
	string* g_lua_print_output = nullptr;

	inline void lua_printf(const char* str, ...)
	{
		va_list arglist;

		if(g_lua_print_output)
		{
			char buffer[256];
			va_start(arglist, str);
			vsnprintf(buffer, 256, str, arglist);
			va_end(arglist);
			(*g_lua_print_output) += buffer;
		}
		else
		{
			va_start(arglist, str);
			vprintf(str, arglist);
			va_end(arglist);
		}
	}

	inline int lua_print(lua_State* L)
	{
		int num_args = lua_gettop(L);
		for(int i = 1; i <= num_args; ++i)
			lua_printf("lua -> %s\n", lua_tostring(L, i));
		return 0;
	}

	inline bool check_error(lua_State* state, int result)
	{
		if(result == 0) return false;
		else if(result == LUA_ERRMEM)
			lua_printf("ERROR : lua -> bad_alloc\n");
		else
			lua_printf("ERROR : lua -> %s\n", lua_tostring(state, -1));
		lua_pop(state, 1);
		return true;
	}
	
	void lua_dump_value(lua_State* state, int index)
	{
		int t = lua_type(state, index);
		if(t == LUA_TSTRING)
			printf("'%s'", lua_tostring(state, index));
		else if(t == LUA_TBOOLEAN)
			printf(lua_toboolean(state, index) ? "true" : "false");
		else if(t == LUA_TNUMBER)
			printf("%g", lua_tonumber(state, index));
		else
		{
			cstring type_name = lua_typename(state, t);

			if(strcmp(type_name, "userdata") == 0 && lua_getmetatable(state, index))
			{
				lua_getfield(state, -1, "__name");
				string name = lua_tostring(state, -1);
				lua_pop(state, 2);
				printf("userdata:%s", name.c_str());
			}
			else
				printf("%s", type_name);
		}
	}

	inline void lua_dump_stack(lua_State* state)
	{
		int top = lua_gettop(state);
		for(int i = 1; i <= top; i++)
		{
			lua_dump_value(state, i);
			printf("  ");
		}
		printf("\n");
	}

	void lua_dump_table(lua_State* state)
	{
		if(lua_type(state, -2) == LUA_TSTRING)
			lua_printf("%s", lua_tostring(state, -2));

		lua_pushnil(state);
		while(lua_next(state, -2) != 0)
		{
			lua_pushvalue(state, -2);
			lua_printf("%s = ", lua_tostring(state, -1));
			if(lua_istable(state, -2))
				lua_dump_table(state);
			else
				lua_dump_value(state, -2);
			lua_printf("\n");
			lua_pop(state, 2);
		}
	}

	struct Stack : public NonCopy
	{
		Stack(lua_State* state, int num = 1) : m_state(state), m_num(num) {}
		~Stack() { assert(lua_gettop(m_state) >= m_num); if(m_num >= 1) lua_pop(m_state, m_num); }

		Stack& operator=(Stack&& other) { swap(m_state, other.m_state); swap(m_num, other.m_num); return *this; }
		Stack(Stack&& other) : m_state(other.m_state), m_num(other.m_num) { other.m_num = 0; }

		Stack operator+(Stack&& other) && { Stack obj(m_state, m_num + other.m_num); m_num = 0; other.m_num = 0; return obj; }
		void operator+=(Stack&& other) { assert(m_state == other.m_state); m_num += other.m_num; other.m_num = 0; }

		lua_State* m_state;
		int m_num = 0;

		int release() { const auto n = m_num; m_num = 0; return n; }
	};

	class FromLua : public Dispatch<void, lua_State*, int, Var&>, public LazyGlobal<FromLua>
	{
	public:
		FromLua();
	};

	class ToLua : public Dispatch<Stack, lua_State*>, public LazyGlobal<ToLua>
	{
	public:
		ToLua();
	};

	inline void read_sequence(lua_State* state, int index, Type& sequence_type, Var& result);
	inline Stack push_sequence(lua_State* state, const Var& value);

	inline void read_enum(lua_State* state, int index, Type& type, Var& result);
	inline Stack push_enum(lua_State* state, const Var& value);

	inline Stack push_callable(lua_State* state, const Callable& callable);
	inline Stack push_null(lua_State* state);

	inline Call& lua_cached_call(const Callable& callable)
	{
		static vector<object<Call>> lua_call_table;
		if(callable.m_index >= lua_call_table.size())
			lua_call_table.resize(callable.m_index + 1);

		if(!lua_call_table[callable.m_index])
			lua_call_table[callable.m_index] = oconstruct<Call>(callable);
		return *lua_call_table[callable.m_index];
	}

	inline void get_type_table(lua_State* state, Type& type)
	{
		lua_pushlightuserdata(state, &type);
		lua_gettable(state, LUA_REGISTRYINDEX);
	}

	struct LuaRef : public Ref
	{
		LuaRef(bool alloc, void* pointer, Type& type) : Ref(pointer, type), m_alloc(alloc) {}
		bool m_alloc;
	};

	inline LuaRef userdata(lua_State* state, int index)
	{
		return *static_cast<LuaRef*>(lua_touserdata(state, index));
	}

	inline LuaRef* alloc_userdata(lua_State* state, Type& type, size_t size)
	{
		LuaRef* ref = static_cast<LuaRef*>(lua_newuserdata(state, size));
		get_type_table(state, type);
		lua_setmetatable(state, -2);
		return ref;
	}

	inline Ref alloc_object(lua_State* state, Type& type)
	{
		LuaRef* ref = alloc_userdata(state, type, sizeof(LuaRef) + meta(type).m_size);
		new (ref) LuaRef(true, ref + 1, type); return *ref;
	}

	inline Ref alloc_ref(lua_State* state, Ref source)
	{
		LuaRef* ref = alloc_userdata(state, *source.m_type, sizeof(LuaRef));
		new (ref) LuaRef(false, source.m_value, *source.m_type); return *ref;
	}

	inline Stack push_ref(lua_State* state, Ref object)
	{
		alloc_ref(state, object);
#ifdef MUD_LUA_DEBUG
		printf("Lua -> pushed ref %s at %p\n", type(object).m_name, object.m_value);
#endif
		return{ state, 1 };
	}

	inline Stack push_object(lua_State* state, Ref value)
	{
		Ref ref = alloc_object(state, *value.m_type);
		copy_construct(ref, value);
#ifdef MUD_LUA_DEBUG
		printf("Lua -> pushed object %s at %p\n", type(value).m_name, ref.m_value);
#endif
		return{ state, 1 };
	}

	inline Stack push_value(lua_State* state, Ref value)
	{
		if(!ToLua::me().check(value))
		{
			lua_printf("ERROR : lua -> no dispatch to push type %s\n", value.m_type->m_name);
			return push_null(state);
		}
		return ToLua::me().dispatch(value, state);
	}

	inline void read_ref(lua_State* state, int index, Var& result)
	{
		if(lua_isnil(state, index)) result = Ref();
		else if(!lua_isuserdata(state, index)) result = Ref();
		else result = userdata(state, index);
#ifdef MUD_LUA_DEBUG
		printf("Lua -> read ref %s at %p\n", result.m_ref.m_type ? result.m_ref.m_type->m_name : "none", result.m_ref.m_value);
#endif
	}

	inline void read_object(lua_State* state, int index, Type& type_to_read, Var& result)
	{
		if(lua_isnil(state, index)) result = Ref(type_to_read);
		else if(lua_isuserdata(state, index))
		{
			Ref object = userdata(state, index);
			if(object.m_type->is(type_to_read))
				result = object;
		}
#ifdef MUD_LUA_DEBUG
		printf("Lua -> read object %s at %p\n", type(result).m_name, result.m_ref.m_value);
#endif
	}

	inline void read_type(lua_State* state, int index, Var& value)
	{
		if(!lua_istable(state, index)) return;
		lua_getfield(state, index, "cpp_type");
		Type* type = static_cast<Type*>(lua_touserdata(state, -1));
		lua_pop(state, 1);
		value = Ref(type);
	}

	inline void read_value(lua_State* state, int index, Type& type, Var& result)
	{
		FromLua::me().dispatch(Ref(type), state, index, result);
		if(result.none())
			lua_printf("ERROR : lua -> reading wrong type %s expected %s\n", lua_typename(state, lua_type(state, index)), type.m_name);
	}

	inline Stack push(lua_State* state, const Var& var)
	{
		// @todo: what about automatic conversion as with visual scripts ? it might not belong here, maybe in read() ?
		// @todo: might want a case for is_complex() before is_object() ?
		if(var.none() || var.null())
			return push_null(state);
		// kludge
		else if(var.m_mode == REF && type(var).is<Member>())
			return push_ref(state, var.m_ref);
		else if(var.m_mode == REF && type(var).is<Callable>())
			return push_callable(state, val<Callable>(var.m_ref));
		else if(is_sequence(type(var)))
			return push_sequence(state, var);
		else if(is_object(type(var)))
			return push_ref(state, var.m_ref);
		else if(is_struct(type(var)))
			return push_object(state, var.m_ref);
		else if(is_enum(type(var)))
			return push_enum(state, var);
		else
			return push_value(state, var.m_ref);
	}

	inline void read(lua_State* state, int index, Var& value)
	{
		if(value.m_mode == REF && value.m_ref == Ref())
			read_ref(state, index, value);
		else if(type(value).is<Type>())
			read_type(state, index, value);
		else if(is_sequence(type(value)))
			read_sequence(state, index, type(value), value);
		else if(is_object(type(value)) || is_struct(type(value)))
			read_object(state, index, type(value), value);
		else if(is_enum(type(value)))
			read_enum(state, index, type(value), value);
		else
			read_value(state, index, type(value), value);
	}

	inline Stack global_table(lua_State* state)
	{
		lua_pushglobaltable(state); return{ state, 1 };
	}

	inline void set_table(lua_State* state, Var index, Var value)
	{
		push(state, index).release();
		push(state, value).release();
		lua_settable(state, -3);
	}
	
	inline void set_table(lua_State* state, cstring index, Var value)
	{
		push(state, value).release();
		lua_setfield(state, -2, index);
	}

	inline void set_global(lua_State* state, Var index, Var data)
	{
		Stack stack = global_table(state);
		set_table(state, index, data);
	}
	
	inline void set_global(lua_State* state, cstring index, Var data)
	{
		push(state, data).release();
		lua_setglobal(state, index);
	}

	inline void lookup_table_var(lua_State* state, Stack& stack, array<Var> indices)
	{
		for(size_t i = 0; i < indices.size(); ++i)
		{
			stack += push(state, indices[i]);
			lua_gettable(state, -2);
		}
	}

	inline Stack get_table(lua_State* state, cstring name)
	{
		lua_getfield(state, -1, name);
		return { state, 1 };
	}

	inline void lookup_table(lua_State* state, Stack& stack, array<cstring> indices)
	{
		for(size_t i = 0; i < indices.size(); ++i)
		{
			stack += { state, 1 };
			lua_getfield(state, -1, indices[i]);
		}
	}

	inline Stack lookup_table_var(lua_State* state, array<Var> indices)
	{
		Stack stack = global_table(state);
		lookup_table_var(state, stack, indices);
		return stack;
	}

	inline Stack lookup_table(lua_State* state, array<cstring> indices)
	{
		Stack stack = global_table(state);
		lookup_table(state, stack, indices);
		return stack;
	}

	inline Var get_global(lua_State* state, cstring name, Type& type)
	{
		Var result = meta(type).m_empty_var;
		lua_getglobal(state, name);
		Stack stack = { state, 1 };
		read(state, -1, result);
		return result;
	}
	
	inline Var get_global(lua_State* state, array<cstring> indices, Type& type)
	{
		Var result = meta(type).m_empty_var;
		Stack stack = global_table(state);
		lookup_table(state, stack, indices);
		read(state, -1, result);
		return result;
	}

	inline Stack load_code(lua_State* state, cstring code)
	{
		bool error = check_error(state, luaL_loadstring(state, code));
		return Stack{ state, error ? 0 : 1 };
	}

	inline Stack call_lua_stack(lua_State* state, Stack arguments, int num_results = 0, Stack function = { nullptr, 0 })
	{
		bool error = check_error(state, lua_pcall(state, arguments.m_num, num_results, 0));
		arguments.release(); function.release();
		return Stack{ state, error ? 0 : num_results };
	}
	
	inline void call_lua(lua_State* state, Stack function, array<Var> parameters, Var* result = nullptr)
	{
		Stack arguments = { state, 0 };
		for(Var& param : parameters)
			arguments += push(state, param);
		Stack results = call_lua_stack(state, move(arguments), result ? 1 : 0, move(function));
		if(result)
			read(state, results.m_num, *result);
	}

	inline void exec_lua(lua_State* state, cstring code, Var* result = nullptr)
	{
		Stack stack = load_code(state, code);
		if(stack.m_num)
			call_lua(state, move(stack), {}, result);
	}

	inline bool read_params(lua_State* state, const Callable& callable, array<Var> vars)
	{
		bool success = true;
		for(size_t i = 0; i < vars.m_count; ++i)
		{
			read(state, -int(vars.m_count) + int(i), vars[i]);
			success &= !vars[i].none();
			success &= callable.m_params[i].nullable() || !vars[i].null();
#if 1
			if(!success)
				printf("ERROR: lua -> wrong argument %s, expect type %s, got %s\n", callable.m_params[i].m_name, callable.m_params[i].m_type->m_name, type(vars[i]).m_name);
#endif
		}
		return success;
	}

	inline Stack call_cpp(lua_State* state, Call& call, size_t num_arguments)
	{
		bool enough_arguments = num_arguments >= call.m_callable->m_num_required;
		if(enough_arguments && read_params(state, *call.m_callable, to_array(call.m_arguments, 0, num_arguments)))
		{
			call();
			Stack result = call.m_result.none() ? Stack{ state, 0 } : push(state, call.m_result);
#ifdef MUD_LUA_DEBUG
			printf("Lua -> called %s\n", call.m_callable->m_name);
			lua_dump_stack(state);
#endif
			return result;
		}
		lua_printf("ERROR: lua -> %s wrong arguments\n", call.m_callable->m_name); // lua_printf
		return Stack{ state, 0 };
	}

	inline Stack call_cpp(lua_State* state, Callable& callable, size_t num_arguments)
	{
		Call& call = lua_cached_call(callable);
		return call_cpp(state, call, num_arguments);
	}

	inline int call_cpp_callable(lua_State* state)
	{
		Callable& callable = *static_cast<Callable*>(lua_touserdata(state, lua_upvalueindex(1)));
		return call_cpp(state, callable, lua_gettop(state)).release();
	}

	inline int get_member(lua_State* state, int object_index)
	{
		const Member& member = val<Member>(userdata(state, -1));
		Ref object = userdata(state, object_index);
		Ref value = member.cast_get(object);
		return push(state, value).release();
	}

	inline int set_member(lua_State* state, int object_index, int value_index)
	{
		const Member& member = val<Member>(userdata(state, -1));
		Ref object = userdata(state, object_index);
		Var value = member.m_default_value;
		read(state, value_index, value);
		member.cast_set(object, value);
		return 0;
	}

	inline int construct_function(lua_State* state)
	{
		Type* type = static_cast<Type*>(lua_touserdata(state, lua_upvalueindex(1)));
		size_t num_args = lua_gettop(state) - 1;
		const Constructor* constructor = cls(*type).constructor(num_args);
		if(constructor)
		{
			Call& construct = lua_cached_call(*constructor);
			if(read_params(state, *construct.m_callable, to_array(construct.m_arguments, 1, num_args)))
				construct(alloc_object(state, *type));
			else
				lua_pushnil(state);
		}
		else
			lua_pushnil(state);
		return 1;
	}

	inline void get_metafield(lua_State* state, int object, int key)
	{
		lua_getmetatable(state, object);
		lua_pushvalue(state, key);
		lua_gettable(state, -2);
	}

	inline int index_function(lua_State* state)
	{
		get_metafield(state, 1, 2);
		if(lua_isuserdata(state, -1))
			return get_member(state, 1);
		// if function or nil, just return it
		return 1;
	};

	inline int newindex_function(lua_State* state)
	{
		get_metafield(state, 1, 2);
		if(lua_isuserdata(state, -1))
			return set_member(state, 1, 3);
		return 0;
	};

	inline int tostring_function(lua_State* state)
	{
		Ref object = userdata(state, 1);
		lua_pushstring(state, to_string(object).c_str());
		return 1;
	};
	
	inline int eq_function(lua_State* state)
	{
		Ref first = userdata(state, 1);
		Ref second = userdata(state, 2);
		lua_pushboolean(state, compare(first, second));
		return 1;
	};

	inline int gc_function(lua_State* state)
	{
		Type* type = static_cast<Type*>(lua_touserdata(state, lua_upvalueindex(1)));
		LuaRef object = userdata(state, 1);
		//if(object.m_alloc && cls(object).m_destructor.size() > 0)
		//	cls(*type).m_destructor[0](object);
		return 0;
	}

	inline void set_cfunction(lua_State* state, cstring name, lua_CFunction func)
	{
		lua_pushstring(state, name);
		lua_pushcfunction(state, func);
		lua_settable(state, -3);
	}

	inline void set_type_closure(lua_State* state, cstring name, lua_CFunction func, Type& type)
	{
		lua_pushstring(state, name);
		lua_pushlightuserdata(state, &type);
		lua_pushcclosure(state, func, 1);
		lua_settable(state, -3);
	}

	inline void create_type_metatable(lua_State* state, Type& type)
	{
		lua_pushlightuserdata(state, &type);
		luaL_newmetatable(state, type.m_name);

		lua_newtable(state);
		set_type_closure(state, "__call", construct_function, type);
		lua_setmetatable(state, -2);

		set_type_closure(state, "__index", index_function, type);
		set_type_closure(state, "__newindex", newindex_function, type);
		set_type_closure(state, "__tostring", tostring_function, type);
		set_type_closure(state, "__eq", eq_function, type);
		if(g_class[type.m_id] && !cls(type).m_destructor.empty())
			set_type_closure(state, "__gc", gc_function, type);

		lua_pushstring(state, "cpp_type");
		lua_pushlightuserdata(state, &type);
		lua_settable(state, -3);

		//lua_pushvalue(state, -1);
		//lua_setglobal(state, type.m_name);

		lua_settable(state, LUA_REGISTRYINDEX);
	}

	void register_field(lua_State* state, Type& type, cstring key, Ref field)
	{
		get_type_table(state, type);
		set_table(state, key, field);
		lua_pop(state, 1);
	}
	
	template <class T>
	inline void read_integer(lua_State* state, int index, Var& result)
	{
		int success; lua_Integer value = lua_tointegerx(state, index, &success);
		if(success)
			val<T>(result) = static_cast<T>(value);
	}

	template <class T>
	inline void read_number(lua_State* state, int index, Var& result)
	{
		int success; lua_Number value = lua_tonumberx(state, index, &success);
		if(success)
			val<T>(result) = static_cast<T>(value);
	}

	inline void read_cstring(lua_State* state, int index, Var& result)
	{
		size_t len; const char* value = lua_tolstring(state, index, &len);
		if(value)
			val<const char*>(result) = value;
	}

	inline void read_string(lua_State* state, int index, Var& result)
	{
		size_t len; const char* value = lua_tolstring(state, index, &len);
		if(value)
			val<string>(result) = value;
	}

	inline void read_null(lua_State* state, int index, Var& result)
	{
		if(lua_isnil(state, index))
			result = Ref();
	}

	inline void read_enum(lua_State* state, int index, Type& type, Var& result)
	{
		if(!lua_isnumber(state, index) || fmod(lua_tonumber(state, index), 1.) != 0)
			return;
		result = enu(type).varn(uint32_t(lua_tointeger(state, index)));
	}

	inline void read_sequence(lua_State* state, int index, Type& sequence_type, Var& result)
	{
		if(!lua_istable(state, index))
			return;

		lua_pushnil(state);
		while(lua_next(state, (index > 0) ? index : (index - 1)) != 0)
		{
			Var element = meta(*iter(sequence_type).m_element_type).m_empty_var;
			read(state, -1, element);
			sequence(result).add(result, element);
			lua_pop(state, 1); // pop the value but keep the key for the next iteration
		}
	}

	FromLua::FromLua()
	{
		function<int>     ([](void*, Ref, lua_State* state, int index, Var& result) { read_integer<int>(state, index, result); });
		function<ushort>  ([](void*, Ref, lua_State* state, int index, Var& result) { read_integer<ushort>(state, index, result); });
		function<uint>    ([](void*, Ref, lua_State* state, int index, Var& result) { read_integer<uint>(state, index, result); });
		function<ulong>   ([](void*, Ref, lua_State* state, int index, Var& result) { read_integer<ulong>(state, index, result); });
		function<ullong>  ([](void*, Ref, lua_State* state, int index, Var& result) { read_integer<ullong>(state, index, result); });
		function<float>   ([](void*, Ref, lua_State* state, int index, Var& result) { read_number<float>(state, index, result); });
		function<double>  ([](void*, Ref, lua_State* state, int index, Var& result) { read_number<double>(state, index, result); });
		function<cstring> ([](void*, Ref, lua_State* state, int index, Var& result) { read_cstring(state, index, result); });
		function<string>  ([](void*, Ref, lua_State* state, int index, Var& result) { read_string(state, index, result); });
		function<bool>    ([](void*, Ref, lua_State* state, int index, Var& result) { val<bool>(result) = lua_toboolean(state, index) != 0; });

		function<Type>    ([](void*, Ref, lua_State* state, int index, Var& result) { return read_type(state, index, result); });
		//function<Prototype> ([](Ref, lua_State* state, int index) { return read_type(state, index); });
	}

	inline Stack push_null(lua_State* state)
	{
		lua_pushnil(state); return{ state, 1 };
	}

	inline Stack push_bool(lua_State* state, bool value)
	{
		lua_pushboolean(state, value); return{ state, 1 };
	}

	inline Stack push_string(lua_State* state, const string& value)
	{
		lua_pushlstring(state, value.c_str(), value.size()); return{ state, 1 };
	}

	inline Stack push_cstring(lua_State* state, const char* value)
	{
		lua_pushstring(state, value); return{ state, 1 };
	}

	template<typename T>
	Stack push_integer(lua_State* state, T value)
	{
		lua_pushinteger(state, value); return{ state, 1 };
	}

	inline Stack push_array(lua_State* state)
	{
		lua_newtable(state); return{ state, 1 };
	}

	template<typename T>
	inline Stack push_scalar(lua_State* state, T value)
	{
		lua_pushnumber(state, value); return{ state, 1 };
	}

	inline Stack push_dict(lua_State* state, const Var& value)
	{
		Stack obj = push_array(state); UNUSED(value);
		//iterdict(value).iterate(value, [=](Var key, Var element) {
		//	set_table(state, key, element); });
		return obj;
	}

	inline Stack push_sequence(lua_State* state, const Var& value)
	{
		Stack obj = push_array(state);
		size_t index = 1;
		iter(value).iterate(value, [&](/*size_t index, */Ref element) {
			set_table(state, var(index++ /*+ 1*/), element); });
		return obj;
	}

	inline Stack push_enum(lua_State* state, const Var& value)
	{
		return push_integer(state, enu(value).index(value));
	};

	inline Stack push_callable(lua_State* state, const Callable& callable)
	{
		lua_pushlightuserdata(state, (void*) &callable);
		lua_pushcclosure(state, call_cpp_callable, 1);
		return{ state, 1 };
	}

	ToLua::ToLua()
	{
		function<void>([](void*, Ref, lua_State* state) { return push_null(state); });

		dispatch_branch<int>     (*this, +[](int&      value, lua_State* state) { return push_integer(state, value); });
		dispatch_branch<ushort>  (*this, +[](ushort&   value, lua_State* state) { return push_integer(state, value); });
		dispatch_branch<uint>    (*this, +[](uint&     value, lua_State* state) { return push_integer(state, value); });
		dispatch_branch<ulong>   (*this, +[](ulong&    value, lua_State* state) { return push_integer(state, value); });
		dispatch_branch<ullong>  (*this, +[](ullong&   value, lua_State* state) { return push_integer(state, value); });
		dispatch_branch<float>   (*this, +[](float&    value, lua_State* state) { return push_scalar(state, value); });
		dispatch_branch<double>  (*this, +[](double&   value, lua_State* state) { return push_scalar(state, value); });
		dispatch_branch<cstring> (*this, +[](cstring   value, lua_State* state) { return push_cstring(state, value); });
		dispatch_branch<string>  (*this, +[](string&   value, lua_State* state) { return push_string(state, value); });
		dispatch_branch<bool>    (*this, +[](bool&     value, lua_State* state) { return push_bool(state, value); });
	}

	class LuaContext : public NonCopy
	{
	public:
		explicit LuaContext(vector<string> import_namespaces = {})
			: m_import_namespaces(import_namespaces)
		{
			m_state = luaL_newstate();

			lua_atpanic(m_state, [](lua_State* state) -> int
			{
				const string str = lua_tostring(state, -1);
				lua_pop(state, 1);
				assert(false && "lua_atpanic triggered");
				exit(0);
			});

			luaL_openlibs(m_state);

			lua_pushcfunction(m_state, lua_print);
			lua_setglobal(m_state, "print");
		}

		~LuaContext()
		{
			assert(m_state);
			lua_close(m_state);
		}

		bool import_namespace(const string& path)
		{
			for(const string& name : m_import_namespaces)
				if(path == name)
					return true;
			return false;
		}

		array<cstring> namespace_path(Namespace& location, size_t shave_off = 0)
		{
			if(location.is_root())
				return array<cstring>{};
			if(import_namespace(location.m_path[0]))
				return location.m_path.size() == 1 ? array<cstring>{} : array<cstring>{ location.m_path.data() + 1, location.m_path.size() - 1 - shave_off };
			else
				return array<cstring>{ location.m_path.data(), location.m_path.size() - shave_off };
		}

		void register_namespace(Namespace& location)
		{
			if(location.is_root())
				return;
			Stack stack = lookup_table(m_state, namespace_path(location, 1));
			lua_newtable(m_state);
			lua_setfield(m_state, -2, location.m_path.back());
		}

		void register_enum(Type& type)
		{
			Enum& e = enu(type);

			Stack stack = lookup_table(m_state, namespace_path(*meta(type).m_namespace));
				
			if(e.m_scoped)
				stack += get_table(m_state, type.m_name);

			for(size_t i = 0; i < e.m_names.size(); ++i)
			{
				set_table(m_state, e.m_names[i], e.varn(i));
			}
		}

		void register_type(Type& type)
		{
			if(!g_meta[type.m_id])
			{
				printf("WARNING: lua - type %s doesn't have reflection meta type\n", type.m_name);
				return;
			}

			create_type_metatable(m_state, type);

			Stack stack = lookup_table(m_state, namespace_path(*meta(type).m_namespace));
			get_type_table(m_state, type);
			lua_setfield(m_state, -2, type.m_name);

			if(is_enum(type))
				register_enum(type);
		}

		void register_function(Function& function)
		{
			Stack stack = lookup_table(m_state, namespace_path(*function.m_namespace));
			set_table(m_state, function.m_name, Ref(&function));
		}

		void register_static(Type& type, Static& member)
		{
			//Stack stack = lookup_table(m_state, { string(type.m_name) });
			get_type_table(m_state, type);
			set_table(m_state, member.m_name, member.m_value);
		}

		void register_method(Type& type, Method& method)
		{
			register_field(m_state, type, method.m_name, Ref(&method));
		}

		void register_member(Type& type, Member& member)
		{
			register_field(m_state, type, member.m_name, Ref(&member));
		}
		
		vector<string> m_import_namespaces;

		lua_State* m_state;
	};
}


namespace mud
{
	LuaInterpreter::LuaInterpreter(bool import_symbols)
		: m_context(construct<LuaContext>(vector<string>{ "mud", "toy" }))
	{
		g_lua_print_output = &m_output;
		if(import_symbols)
			this->declare_types();
	}

	LuaInterpreter::~LuaInterpreter()
	{}

	void LuaInterpreter::declare_types()
	{
		System& system = System::instance();

		//printf("INFO: Declaring lua Meta info\n");
		//system.dumpMetaInfo();

		for(Namespace& location : system.m_namespaces)
			m_context->register_namespace(location);

		for(Function* function : system.m_functions)
			m_context->register_function(*function);

		for(Type* type : system.m_types)
			m_context->register_type(*type);

		for(Type* type : system.m_types)
			if(g_class[type->m_id])
			{
				for(Member& member : cls(*type).m_members)
					m_context->register_member(*type, member);
				for(Method& method : cls(*type).m_methods)
					m_context->register_method(*type, method);
				for(Static& static_member : cls(*type).m_static_members)
					m_context->register_static(*type, static_member);
			}
	}

	Var LuaInterpreter::get(const string& name, Type& type)
	{
		return get_global(m_context->m_state, name.c_str(), type);
	}

	void LuaInterpreter::set(const string& name, Var value)
	{
		set_global(m_context->m_state, name.c_str(), value);
	}

	Var LuaInterpreter::getx(array<cstring> path, Type& type)
	{
		return get_global(m_context->m_state, path, type);
	}

	void LuaInterpreter::setx(array<cstring> path, Var value)
	{
		Stack stack = lookup_table(m_context->m_state, { path, path.size() - 1 });
		set_table(m_context->m_state, *path.end(), value);
	}

	void LuaInterpreter::call(const string& code, Var* result)
	{
#ifdef MUD_LUA_DEBUG_IO
		printf("lua -> %s\n", code);
#endif
		exec_lua(m_context->m_state, code.c_str(), result);
#ifdef MUD_LUA_DEBUG_IO
		printf("lua -> %s\n", m_output.c_str());
		m_output = "";
#endif
	}

}


#ifdef MUD_MODULES
module mud.lang;
#else
#endif

namespace mud
{
	Script::Script(Type& type, const string& name, const Signature& signature)
		: Callable(name.c_str(), signature.m_params, signature.m_return_type)
		, m_index(index(mud::type<Script>(), Ref(this, type)))
		, m_type(type)
		, m_name(name)
		, m_signature(signature)
	{
		Callable::m_name = m_name.c_str();
		m_signature.m_params = m_params;
	}

	Script::~Script()
	{
		unindex(type<Script>(), m_index);
	}

	Interpreter::Interpreter()
	{}

	void Interpreter::call(const TextScript& script, array<Var> args, Var* result)
	{
		m_script = &script;
		script.m_runtime_errors.clear();
		script.m_compile_errors.clear();

		for(const Param& param : script.m_signature.m_params)
		{
			this->set(param.m_name, args[param.m_index]);
		}

		this->call(script.m_script, result);
	}

	string Interpreter::flush()
	{
		string output = m_output;
		m_output = "";
		return output;
	}

	TextScript::TextScript(const string& name, Language language, const Signature& signature)
		: Script(type<TextScript>(), name, signature)
		, m_language(language)
	{}

	void TextScript::operator()(array<Var> args, Var& result) const
	{
		m_interpreter->call(*this, args, result.none() ? nullptr : &result);
	}

	ScriptClass::ScriptClass(const string& name, const vector<Type*>& parts)
		: m_name(name)
		, m_class_type(m_name.c_str())
		, m_class(m_class_type)
		, m_prototype(m_class_type, parts)
	{}
}


#ifdef MUD_MODULES
module mud.lang;
#else
#endif

namespace mud
{
	StreamBranch::StreamBranch(Stream* stream, Var value, StreamIndex index)
		: m_stream(stream)
		, m_index(index)
		, m_depth(index.size() - 1)
		, m_value(value)
	{}

	StreamBranch& StreamBranch::add_branch()
	{
		StreamIndex branch_index = m_index;
		branch_index.push_back(m_branches.size());
		m_branches.push_back({ m_stream, m_stream->m_default, branch_index });
		return m_branches.back();
	}

	void StreamBranch::resize(size_t size)
	{
		for(size_t i = m_branches.size(); i < size; ++i)
			this->add_branch();
	}

	void StreamBranch::clear()
	{
		m_branches.clear();
	}

	void StreamBranch::copy(const StreamBranch& source)
	{
		if(m_branches.size() == source.m_branches.size())
		{
			for(size_t i = 0; i < m_branches.size(); ++i)
				m_branches[i].copy(source.m_branches[i]);
		}
		else
		{
			*this = source;
		}
	}

	StreamBranch& StreamBranch::branch(const StreamIndex& index)
	{
		if(index.size() > m_depth + 1)
		{
			size_t at = index[m_depth + 1];
			while(at >= m_branches.size())
				this->add_branch();
			return m_branches[at].branch(index);
		}
		else
		{
			return *this;
		}
	}

	StreamBranch* StreamBranch::find_branch(const StreamIndex& index, size_t depth)
	{
		if(m_branches.empty())
			return this;
		else if(m_branches.size() <= index[depth])
			return nullptr;
		else
			return m_branches[index[depth]].find_branch(index, depth + 1);
	}

	void StreamBranch::write(const Var& value, bool multiplex)
	{
		if(multiplex && !(value == Ref()) && is_sequence(type(value)))
		{
			Iterable& it = iter(value);
			this->resize(it.size(value));

			it.iteratei(value, [&](size_t i, Ref element) {
				m_branches[i].m_value = element;
			});
		}
		else
		{
			m_value = value;
		}
	}

	bool StreamBranch::read(Var& value, Type* expected_type, bool ref)
	{
		if(!expected_type)
		{
			value = m_value.m_ref;
			return true;
		}
		bool result = convert(m_value, *expected_type, value, ref);
#if 0
		if(!result)
			printf("WARNING: No conversion possible from %s to %s : dest set to None\n", type(source).m_name, output.m_name);
#endif
		return result;
	}

	Stream::Stream()
		: StreamBranch(this, Var(), { 0 })
	{}

	Stream::Stream(Var value, bool nullable, bool reference)
		: StreamBranch(this, value, { 0 })
		, m_default(value)
		, m_type(value == Ref() ? &type<Ref>() : &type(value))
		, m_nullable(nullable)
		, m_reference(reference)
	{}

	Stream::Stream(const Stream& stream)
		: Stream(stream.m_default, stream.m_nullable, stream.m_reference)
	{
		*this = stream;
	}

	Stream& Stream::operator=(const Stream& stream)
	{
		this->copy(stream);
		this->compute();
		return *this;
	}

	bool compare_tip(const Topology& topology, const Topology& other)
	{
		size_t depth = other.size();
		return equal(topology.end() - depth, topology.end(), other.begin(), other.end());
	}

	StreamBranch* Stream::match_branch(const StreamLocation& source)
	{
		if(source.m_topology.size() > 0 && m_topology.size() > 0)
			if(compare_tip(source.m_topology, m_topology))
			{
				size_t offset = source.m_topology.size() - m_topology.size();
				return this->find_branch(source.m_index, offset + 1);
			}

		return this->find_branch(source.m_index, m_depth + 1);
	}

	void Stream::compute()
	{
		m_size = 0;
		m_topology.clear();

		if(m_branches.size() == 0)
			return;

		m_topology.resize(100, SIZE_MAX);

		this->visit(false, [&](StreamBranch& branch) {
			if(branch.m_branches.size() == 0)
				++m_size;
			
			if(m_topology[branch.m_depth] == SIZE_MAX)
				m_topology[branch.m_depth] = branch.m_branches.size();
			else if(m_topology[branch.m_depth] != branch.m_branches.size())
				m_topology[branch.m_depth] = 0;
		});

		vector_remove_if(m_topology, [](size_t& val) { return val == 0 || val == SIZE_MAX; });
	}

	void Stream::flatten(Stream& source)
	{
		if(source.m_branches.empty())
			return;

		m_branches.clear();

		m_value = meta(*m_type).m_empty_var;
		Sequence& seq = sequence(m_value);
		Var element = meta(*iter(*m_type).m_element_type).m_empty_var;

		source.visit(true, [&](StreamBranch& branch)
		{
			branch.read(element, iter(*m_type).m_element_type, m_reference);
			seq.add(m_value, element);
		});
	}

	void Stream::graft(Stream& source)
	{
		Iterable& iterable = iter(source.m_value);
		this->resize(iterable.size(source.m_value));

		size_t index = 0;
		iterable.iterate(source.m_value, [&](Ref element)
		{
			m_branches[index++].m_value = element;
		});
	}

	void Stream::read(Stream& source)
	{
		*this = source; // why is this needed :/
		
		m_num_invalid = 0;
		source.visit(true, [&](StreamBranch& source_branch)
		{
			StreamBranch& branch = this->branch(source_branch.m_index);
			bool success = source_branch.read(branch.m_value, m_type, m_reference);
			branch.m_valid = success && (m_nullable || !branch.m_value.null());
			if(!branch.m_valid)
				m_num_invalid++;
		});
	}

	void Stream::validate()
	{
		m_num_invalid = 0;
		this->visit(true, [&](StreamBranch& branch)
		{
			branch.m_valid = m_nullable || !branch.m_value.null();
			if(!branch.m_valid)
				m_num_invalid++;
		});
	}
}

#ifdef MUD_MODULES
module mud.lang;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_LANG_EXPORT Type& type<mud::Language>() { static Type ty("mud::Language", sizeof(mud::Language)); return ty; }
    
    template <> MUD_LANG_EXPORT Type& type<mud::Interpreter>() { static Type ty("Interpreter", sizeof(mud::Interpreter)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Pipe>() { static Type ty("Pipe", sizeof(mud::Pipe)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Process>() { static Type ty("Process", sizeof(mud::Process)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ScriptClass>() { static Type ty("ScriptClass", sizeof(mud::ScriptClass)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ScriptError>() { static Type ty("ScriptError", sizeof(mud::ScriptError)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::StreamBranch>() { static Type ty("StreamBranch", sizeof(mud::StreamBranch)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Valve>() { static Type ty("Valve", sizeof(mud::Valve)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::LuaInterpreter>() { static Type ty("LuaInterpreter", type<mud::Interpreter>(), sizeof(mud::LuaInterpreter)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessCallable>() { static Type ty("ProcessCallable", type<mud::Process>(), sizeof(mud::ProcessCallable)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessCreate>() { static Type ty("ProcessCreate", type<mud::Process>(), sizeof(mud::ProcessCreate)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessDisplay>() { static Type ty("ProcessDisplay", type<mud::Process>(), sizeof(mud::ProcessDisplay)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessFunction>() { static Type ty("ProcessFunction", type<mud::ProcessCallable>(), sizeof(mud::ProcessFunction)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessGetMember>() { static Type ty("ProcessGetMember", type<mud::Process>(), sizeof(mud::ProcessGetMember)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessInput>() { static Type ty("ProcessInput", type<mud::Process>(), sizeof(mud::ProcessInput)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessMethod>() { static Type ty("ProcessMethod", type<mud::ProcessCallable>(), sizeof(mud::ProcessMethod)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessOutput>() { static Type ty("ProcessOutput", type<mud::Process>(), sizeof(mud::ProcessOutput)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessScript>() { static Type ty("ProcessScript", type<mud::ProcessCallable>(), sizeof(mud::ProcessScript)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessSetMember>() { static Type ty("ProcessSetMember", type<mud::Process>(), sizeof(mud::ProcessSetMember)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::ProcessValue>() { static Type ty("ProcessValue", type<mud::Process>(), sizeof(mud::ProcessValue)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Script>() { static Type ty("Script", type<mud::Callable>(), sizeof(mud::Script)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::Stream>() { static Type ty("Stream", type<mud::StreamBranch>(), sizeof(mud::Stream)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::TextScript>() { static Type ty("TextScript", type<mud::Script>(), sizeof(mud::TextScript)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::VisualScript>() { static Type ty("VisualScript", type<mud::Script>(), sizeof(mud::VisualScript)); return ty; }
    template <> MUD_LANG_EXPORT Type& type<mud::WrenInterpreter>() { static Type ty("WrenInterpreter", type<mud::Interpreter>(), sizeof(mud::WrenInterpreter)); return ty; }
}


#ifdef MUD_MODULES
module mud.lang;
#else
#endif

namespace mud
{
	ProcessValue::ProcessValue(VisualScript& script, const Var& value)
		: Process(script, value == Ref() ? "Ref" : type(value).m_name, type<ProcessValue>())
		, m_output(*this, "output", OUTPUT_VALVE, value, false, false)
	{
		m_output.m_edit = true;
		m_output.m_stream.write(value);
		m_state = COMPUTED;
	}

	ProcessValue::ProcessValue(VisualScript& script, Type& type)
		: ProcessValue(script, meta(type).m_empty_var)
	{}

	ProcessCreate::ProcessCreate(VisualScript& script, Type& type, const Constructor& constructor)
		: Process(script, meta(type).m_name, mud::type<ProcessCreate>())
		, m_object_type(type)
		, m_injector(constructor)
		, m_output(*this, "output", OUTPUT_VALVE, is_struct(type) ? meta(type).m_empty_var : Var(meta(type).m_empty_ref), false, is_struct(type) ? false : true)
		, m_pool(is_struct(type) ? nullptr : g_pools[m_object_type.m_id].get())
	{
		for(const Param& param : m_injector.m_constructor.m_params)
			//if(param.m_mode == INPUT_PARAM)
			if(param.m_index > 0) // skip first, it's the object reference
				m_input_params.push_back(oconstruct<Valve>(*this, param));
	}

	ProcessCreate::ProcessCreate(VisualScript& script, Type& type, ConstructorIndex constructor)
		: ProcessCreate(script, type, *cls(type).constructor(constructor))
	{}

	ProcessCreate::ProcessCreate(VisualScript& script, Type& type, size_t num_args)
		: ProcessCreate(script, type, *cls(type).constructor(num_args))
	{}

	void ProcessCreate::clear()
	{
		for(Ref& object : m_persistent_objects)
			m_pool->destroy(object);
		m_persistent_objects.clear();
	}

	void ProcessCreate::process(const StreamLocation& branch)
	{
		for(size_t i = 1; i < m_injector.m_arguments.size(); ++i)
			m_injector.m_arguments[i] = m_inputs[i - 1]->read(branch);

		if(is_struct(m_object_type))
		{
			Var& value = m_output.m_stream.branch(branch.m_index).m_value;
			m_injector.inject(value);
		}
		else
		{
			Ref object = m_injector.inject(*m_pool);
			m_output.m_stream.write(branch, object);
			m_persistent_objects.push_back(object);
		}
	}

	ProcessCallable::ProcessCallable(VisualScript& script, Callable& callable)
		: Process(script, callable.m_name, type<ProcessCallable>())
		, m_parameters(callable.m_params.size() + (callable.m_return_type == g_qvoid ? 0 : 1))
		, m_callable(callable)
	{
		for(const Param& param : callable.m_params)
			m_params.push_back(oconstruct<Valve>(*this, param));

		if(callable.m_return_type != g_qvoid)
			m_result = oconstruct<Valve>(*this, "result", OUTPUT_VALVE, meta(*callable.m_return_type.m_type).m_empty_var, false, false);
	}

	void ProcessCallable::process(const StreamLocation& branch)
	{
		for(Valve* valve : m_inputs)
			m_parameters[valve->m_index] = valve->read(branch);
		for(Valve* valve : m_outputs)
			m_parameters[m_inputs.size() + valve->m_index] = valve->m_stream.m_default;

		if(m_result)
		{
			Var& value = m_result->m_stream.branch(branch.m_index).m_value;
			//m_callable(to_array(m_parameters), value);
			m_result->m_stream.branch(branch.m_index).write(value);
		}
		else
		{
			static Var unused;
			//m_callable(to_array(m_parameters), unused);
		}

		for(const Param& param : m_callable.m_params)
			if(param.output())
			{
				m_params[param.m_index]->m_stream.write(branch, m_parameters[param.m_index]);
			}
	}

	ProcessScript::ProcessScript(VisualScript& script, VisualScript& target)
		: ProcessCallable(script, target)
		, m_target(target)
	{}

	ProcessFunction::ProcessFunction(VisualScript& script, Function& function)
		: ProcessCallable(script, function)
		, m_function(function)
	{}

	ProcessMethod::ProcessMethod(VisualScript& script, Method& method)
		: ProcessCallable(script, method)
		, m_method(method)
		, m_object(*this, "object", OUTPUT_VALVE, meta(*method.m_object_type).m_empty_ref, false, true)
	{
		m_parameters.resize(m_parameters.size() + 1);
	}

	void ProcessMethod::process(const StreamLocation& branch)
	{
		ProcessCallable::process(branch);
		m_object.m_stream.write(branch, m_parameters[0]);
	}

	ProcessGetMember::ProcessGetMember(VisualScript& script, Member& member)
		: Process(script, member.m_name, type<ProcessGetMember>())
		, m_member(member)
		, m_input_object(*this, "object", INPUT_VALVE, meta(*member.m_object_type).m_empty_ref, false, true)
		, m_output(*this, member.m_name, OUTPUT_VALVE, member.m_default_value, false, !(member.is_value()))
	{}

	void ProcessGetMember::process(const StreamLocation& branch)
	{
		const Var& object = m_input_object.read(branch);
		Var& value = m_output.m_stream.branch(branch.m_index).m_value;
		//m_member.get(object.m_ref, value);
		value = m_member.get(object.m_ref);
	}

	ProcessSetMember::ProcessSetMember(VisualScript& script, Member& member)
		: Process(script, member.m_name, type<ProcessSetMember>())
		, m_member(member)
		, m_input_object(*this, "object", INPUT_VALVE, meta(*member.m_object_type).m_empty_ref, false, true)
		, m_input_value(*this, member.m_name, INPUT_VALVE, member.m_default_value, false, false)
		, m_output_object(*this, "object", OUTPUT_VALVE, meta(*member.m_object_type).m_empty_ref, false, true)
	{}

	void ProcessSetMember::process(const StreamLocation& branch)
	{
		const Var& object = m_input_object.read(branch);
		const Var& value = m_input_value.read(branch);
		m_member.set(object.m_ref, value.m_ref);

		m_output_object.m_stream.write(branch, object);
	}

	ProcessDisplay::ProcessDisplay(VisualScript& script)
		: Process(script, "Display", type<ProcessDisplay>())
		, m_input_value(*this, "input", INPUT_VALVE)
	{}

	void ProcessDisplay::process(const StreamLocation& branch)
	{
		UNUSED(branch);
		if(m_update_display)
			m_update_display(*this);
	}
}


#ifdef MUD_MODULES
module mud.lang;
#else
#endif

#include <algorithm>

#define MUD_DEBUG_SCRIPT

namespace mud
{
	template <class T, class V>
	inline auto remove_pt(vector<T>& vec, V& value)
	{
		auto pos = find_if(vec.begin(), vec.end(), [&](auto& pt) { return pt.get() == &value; });
		vec.erase(pos);
	}

	template <class T> inline T min(T a, T b) { return a < b ? a : b; }

	template <> void to_value<StreamIndex>(const string& str, StreamIndex& val) { UNUSED(str); UNUSED(val); }
	template <> void to_string<StreamIndex>(const StreamIndex& val, string& str) { str += "{"; for(size_t i : val) str += to_string(i) + ","; str.pop_back(); str += "}"; }

	Valve::Valve(Process& process, cstring name, ValveKind kind, Var value, bool nullable, bool reference)
		: m_process(process)
		, m_index(kind == INPUT_VALVE ? process.m_inputs.size() : process.m_outputs.size())
		, m_name(name)
		, m_kind(kind)
		, m_stream(value, nullable, reference)
		, m_edit(false)
	{
		if(kind == INPUT_VALVE)
			process.m_inputs.push_back(this);
		if(kind == OUTPUT_VALVE)
			process.m_outputs.push_back(this);

		if(kind == INPUT_VALVE)
		{
			m_stream.write(value, false);
			m_stream.validate();
			// @todo merge these two operations ? should we validate every time we write ?
		}
	}

	Valve::Valve(Process& process, const Param& param)
		: Valve(process, param.m_name, param.output() ? OUTPUT_VALVE : INPUT_VALVE, param.default_val(), param.nullable(), param.reference())
	{}

	Valve::~Valve()
	{
		for(Pipe* pipe : m_pipes)
			m_process.m_script.disconnect(*pipe);
	}

	string Valve::error_info()
	{
		string errors;
		m_stream.visit(true, [&](StreamBranch& branch)
		{
			if(!branch.m_valid)
			{
				//errors += "";
				//errors += "\n";
			}
		});
		if(m_stream.m_num_invalid > 0)
			return to_string(m_stream.m_num_invalid) + " errors\n" + errors;
		else
			return "";
	}

	string Valve::param_info()
	{
		string info;

		info += to_string(m_stream.m_size);
		info += " elements\n";

		m_stream.visit(true, [&](StreamBranch& branch)
		{
			info += to_string(branch.m_index);
			if(branch.m_value == Ref())
				info += "null";
			else
			{
				info += "(" + string(meta(branch.m_value).m_name) + ") ";
				if(g_convert[type(branch.m_value).m_id])
					info += to_string(branch.m_value);
				info += "\n";
			}
		});
		if(info.size() > 1000)
			info.resize(1000);
		return info;
	}

	bool Valve::check(const StreamLocation& location)
	{
		//if(!m_stream.m_type || m_stream.m_type->is(type<Ref>())) return true;
		StreamBranch* stream_branch = m_stream.match_branch(location);
		return stream_branch ? stream_branch->m_valid : false;
	}

	const Var& Valve::read(const StreamLocation& location)
	{
		StreamBranch* stream_branch = m_stream.match_branch(location);
		assert(stream_branch);
		return stream_branch->m_value;
	}

	object<Pipe> Valve::try_connect(Valve& output, StreamModifier modifier)
	{
		if(!m_pipes.empty())
			m_process.m_script.disconnect(*m_pipes[0]);

		return oconstruct<Pipe>(output, *this, modifier);
	}

	void Valve::propagate()
	{
		for(Pipe* pipe : m_pipes)
			pipe->propagate();
	}

	Pipe::Pipe(Valve& output, Valve& input, StreamModifier modifier)
		: m_output(output)
		, m_input(input)
		, m_modifier(modifier)
	{
		// the output plug is actually the input of the pipe itself
		// conversely the input plug receives what gets out of the pipe

		m_output.m_pipes.push_back(this);
		m_input.m_pipes.push_back(this);

		m_output.m_process.connected(input.m_process);

		if(!input.m_process.m_script.m_locked)
			this->propagate();
	}

	Pipe::~Pipe()
	{
		vector_remove(m_output.m_pipes, this);
		vector_remove(m_input.m_pipes, this);
	}
	
	void dump_stream(Stream& stream, const string& name)
	{
		printf("INFO: Dump tree %s\n", name.c_str());
		stream.visit(true, [&](StreamBranch& branch)
		{
			for(size_t d = 0; d < branch.m_depth; ++d)
				printf("    ");
			printf("Branch %s value %s\n", to_string(branch.m_index).c_str(), convert(type(branch.m_value)).m_to_string ? to_string(branch.m_value).c_str()
																														: to_name(type(branch.m_value), branch.m_value.m_ref).c_str());
		});
	}

	void Pipe::propagate()
	{
		if(m_modifier == SM_FLATTEN)
			m_input.m_stream.flatten(m_output.m_stream);
		else if(m_modifier == SM_GRAFT)
			m_input.m_stream.graft(m_output.m_stream);
		else
			m_input.m_stream.read(m_output.m_stream);

		m_input.m_process.invalidate();

		//dump_stream(m_input.m_stream, m_input.m_process.m_title + " " + m_input.m_name);
	}

	Process::Process(VisualScript& script, cstring title, Type& type)
		: m_type(type)
		, m_script(script)
		, m_index(script.m_processes.size())
		, m_title(title)
		, m_position{ 0, 0 }
	{}

	Process::~Process()
	{}

	Valve& Process::out_flow()
	{
		if(!m_out_flow)
			m_out_flow = oconstruct<Valve>(*this, "out", FLOW_VALVE_OUT);
		return *m_out_flow;
	}

	Valve& Process::in_flow()
	{
		if(!m_in_flow)
			m_in_flow = oconstruct<Valve>(*this, "in", FLOW_VALVE_IN);
		return *m_in_flow;
	}

	void Process::recompute()
	{
		//printf("DEBUG: Process %s executing\n", m_title.c_str());
		this->execute();
		m_state = COMPUTED;

		if(m_callback)
			m_callback(*this);

		for(Valve* output : m_outputs)
			output->propagate();

		if(m_out_flow)
			m_out_flow->propagate();
	}

	void Process::execute()
	{
		//printf("execute process %s\n", m_title.c_str());
		this->clear();

		this->execution_flow();

		m_execution_flow.visit(true, [this](StreamBranch& branch) {
			this->process_branch({ branch.m_index, m_execution_flow.m_topology });
		});

		for(Valve* output : m_outputs)
		{
			output->m_stream.compute();
		}

		if(m_out_flow)
			m_out_flow->m_stream = m_execution_flow;
	}

	Valve& Process::find_master_input()
	{
		Valve* masterInput = m_inputs[0];

		// Process stream flow is the flow of the input with most branches
		for(Valve* input : m_inputs)
			if(input->m_stream.m_size > masterInput->m_stream.m_size)
				masterInput = input;

		if(m_in_flow && m_in_flow->m_stream.m_size > masterInput->m_stream.m_size)
			masterInput = m_in_flow.get();

		return *masterInput;
	}

	void Process::execution_flow()
	{
		if(m_inputs.empty())
			return;

		Valve& masterInput = m_master_input ? *m_master_input : this->find_master_input();
		
		m_execution_flow.copy(masterInput.m_stream);

		if(m_secondary_input != nullptr)
			m_execution_flow.visit(true, [&](StreamBranch& branch) {
				branch.copy(m_secondary_input->m_stream);
			});

		m_execution_flow.compute();
	}

	bool Process::validate_inputs(const StreamLocation& branch)
	{
		bool valid = true;
		for(Valve* input : m_inputs)
		{
			bool check = input->check(branch);
			valid = valid && check;
#ifdef MUD_DEBUG_SCRIPT
			if(!check)
				printf("WARNING: Wrong parameter for process %s, input %s, branch %s\n", m_title.c_str(), input->m_name.c_str(), to_string(branch.m_index).c_str());
#endif
		}
		return valid;
	}

	void Process::process_branch(const StreamLocation& branch)
	{
		if(!this->validate_inputs(branch))
		{
#ifdef MUD_DEBUG_SCRIPT
			//if(!branch.empty()) // @todo this doesn't work (branches are never empty :/
				printf("WARNING: Process %s failed for branch %s\n", m_title.c_str(), to_string(branch.m_index).c_str());
#endif
			for(Valve* valve : m_outputs)
				valve->m_stream.write(branch, Var());
			return;
		}

		this->process(branch);
	}

	Process& Process::flow(Valve& valve)
	{
		m_script.connect(valve, this->in_flow());
		return *this;
	}

	Valve* Process::pipe(vector<Valve*> outputParams, Process* flow, vector<StreamModifier> modifiers)
	{
		this->plug(outputParams, flow, modifiers);
		return m_outputs.size() > 0 ? &this->output() : nullptr;
	}

	Process& Process::plug(vector<Valve*> outputParams, Process* flow, vector<StreamModifier> modifiers)
	{
		if(flow)
			this->flow(flow->out_flow());
		size_t num_inputs = min(m_inputs.size(), outputParams.size());
		for(size_t i = 0; i < num_inputs; ++i)
			m_script.connect(*outputParams[i], *m_inputs[i], modifiers.size() > i ? modifiers[i] : SM_NONE);
		return *this;
	}

	Process& Process::combine_flow(size_t masterInput, size_t secondaryInput)
	{
		m_master_input = m_inputs[masterInput];
		m_secondary_input = m_inputs[secondaryInput];
		return *this;
	}

	void Process::connected(Process& output)
	{
		output.m_edge = false;
		output.m_state = UNCOMPUTED;
	}

	int Process::visit_order()
	{
		if(!m_dirty)
			return m_order;

		m_order = 0;
		m_dirty = false;

		if(m_out_flow)
			for(Pipe* pipe : m_out_flow->m_pipes)
			{
				Process& process = pipe->m_input.m_process;
				m_order = min(m_order, process.visit_order() - 1);
			}

		for(Valve* valve : m_outputs)
			for(Pipe* pipe : valve->m_pipes)
			{
				Process& process = pipe->m_input.m_process;
				m_order = min(m_order, process.visit_order() - 1);
			}

		return m_order;
	}

	VisualScript::VisualScript(cstring name, const Signature& signature)
		: Script(type<VisualScript>(), name, signature)
	{
		if(!signature.m_return_type.isvoid())
			this->node<ProcessOutput>(Param("return", *signature.m_return_type.m_type));

		for(const Param& param : signature.m_params)
			if(!param.output())
				this->node<ProcessInput>(param);
			else if(param.output())
				this->node<ProcessOutput>(param);
	}

	void VisualScript::remove(Process& process)
	{
		remove_pt(m_processes, process);

		size_t index = 0;
		for(auto& element : m_processes)
			element->m_index = index++;
	}

	void VisualScript::lock()
	{
		m_locked = true;
	}

	void VisualScript::unlock(bool execute)
	{
		m_locked = false;
		if(execute)
		{
			this->reorder();
			this->execute();
		}
	}

	void VisualScript::reorder()
	{
		for(auto& process : m_processes)
			process->m_dirty = true;

		for(auto& process : m_processes)
			if(process->m_edge)
				process->visit_order();

		m_execution.clear();
		for(auto& process : m_processes)
			m_execution.push_back(process.get());

		std::sort(m_execution.begin(), m_execution.end(),
			[](Process* lhs, Process* rhs) { return lhs->m_order < rhs->m_order; });
	}

	void VisualScript::connect(Valve& output, Valve& input, StreamModifier modifier)
	{
		object<Pipe> pipe = input.try_connect(output, modifier);
		if(pipe)
			m_pipes.push_back(move(pipe));
		if(!m_locked)
			this->execute();
	}

	void VisualScript::disconnect(Pipe& pipe)
	{
		remove_pt(m_pipes, pipe);
	}

	Valve& VisualScript::input(const string& name)
	{
		for(ProcessInput* input : m_inputs)
			if(input->m_name == name)
				return input->m_output;
		return m_inputs[0]->m_output;
	}

	void VisualScript::execute(bool uncomputed)
	{
		for(Process* process : m_execution)
			if(!uncomputed || (!process->computed() && !process->locked()))
			{
				process->recompute();
			}
	}

	void VisualScript::operator()(array<Var> args, Var& result) const
	{
		// @kludge: ugly cast until we decide something on this callable constness mess
		VisualScript& self = const_cast<VisualScript&>(*this);
		self.lock();
		for(size_t i = 0; i < m_inputs.size(); ++i)
			m_inputs[i]->m_output.m_stream.write(args[i]);
		self.unlock(false);

		self.reorder();
		self.execute(false);
		UNUSED(result);
	}

	ProcessInput::ProcessInput(VisualScript& script, const Param& param)
		: Process(script, param.m_name, type<ProcessInput>())
		, Param(param)
		, m_output(*this, param.m_name, OUTPUT_VALVE, param.default_val(), param.nullable(), param.reference())
	{
		script.m_inputs.push_back(this);
	}

	ProcessOutput::ProcessOutput(VisualScript& script, const Param& param)
		: Process(script, param.m_name, type<ProcessOutput>())
		, Param(param)
		, m_input(*this, param.m_name, INPUT_VALVE, param.default_val(), param.nullable(), param.reference())
	{
		script.m_outputs.push_back(this);
	}
}

#ifndef MUD_CPP_20
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>
#include <cctype>
#endif

#ifdef MUD_MODULES
#include <stdlib.h>
module mud.lang;
#else
#include <stl/vector.h>
#include <stl/map.h>
#include <stl/unordered_map.h>
#include <stl/set.h>
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
	template <class T>
	inline T max(T a, T b) { return a < b ? b : a; }

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

	inline void read_enum(WrenVM* vm, int slot, Ref result);
	inline void push_enum(WrenVM* vm, int slot, Ref value);

	inline void push_null(WrenVM* vm, int slot);

	inline Call& cached_call(const Callable& callable)
	{
		static vector<object<Call>> call_table;
		if(callable.m_index >= call_table.size())
			call_table.resize(callable.m_index + 1);

		if(!call_table[callable.m_index])
			call_table[callable.m_index] = oconstruct<Call>(callable);
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
			read_enum(vm, index, value);
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

	inline bool read_params(WrenVM* vm, const Callable& callable, array<Var> vars, size_t offset, size_t first_slot)
	{
		size_t num_args = wrenGetSlotCount(vm) - first_slot;
		for(size_t i = offset; i < offset + num_args; ++i)
		{
			read(vm, int(first_slot - offset + i), vars[i].m_ref);
			bool success = !vars[i].none();
			success &= callable.m_params[i].nullable() || !vars[i].null();
			if (!success)
			{
#ifdef MUD_WREN_DEBUG
				printf("ERROR: wren -> wrong argument %s, expect type %s, got %s\n", callable.m_params[i].m_name, type(callable.m_params[i].m_value).m_name, type(vars[i]).m_name);
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
		if(enough_arguments && read_params(vm, *call.m_callable, call.m_arguments, 0, first))
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
		wrenEnsureSlots(vm, int(parameters.m_count + 1));
		wrenSetSlotHandle(vm, 0, object);
		for(int i = 0; i < int(parameters.size()); ++i)
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
		if(read_params(vm, *construct.m_callable, construct.m_arguments, 1, 2))
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
		//constructor(object, other);
	}

	inline void construct_interface(WrenVM* vm)
	{
		WrenInterpreter* wren = mud::wren(vm);
		const Constructor* constructor = &val<Constructor>(read_ref(vm, 0));
		if (!constructor) return;
#ifdef MUD_WREN_DEBUG
		printf("INFO: wren -> construct %s\n", constructor->m_name);
#endif
		Call& construct = cached_call(*constructor);
		VirtualMethod virtual_method = [=](Method& method, Ref object, array<Var> args) { wren->virtual_call(method, object, args); };
		construct.m_arguments.back() = var(virtual_method);
		if(read_params(vm, *construct.m_callable, construct.m_arguments, 1, 2))
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

	inline void register_enum(WrenVM* vm, string module, string name, Type& type)
	{
		Enum& enu = mud::enu(type);

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

#ifdef MUD_WREN_DEBUG_DECLS
		printf("%s\n", decl.c_str());
#endif

		wrenInterpret(vm, module.c_str(), decl.c_str());
	}

	inline string callable_params(Callable& callable, size_t offset, size_t count)
	{
		if(count == offset)
			return string(""); 
		string params;
		for(const Param& param : to_array(callable.m_params, offset, count - offset))
		{
			params += param.m_name;
			params += ",";
		}
		params.pop_back();
		return params;
	}

	inline void register_class(WrenVM* vm, string module, string name, Type& type)
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

	inline void read_enum(WrenVM* vm, int slot, Ref result)
	{
		if(wrenGetSlotType(vm, slot) == WREN_TYPE_NUM)
			enu(result).varn(uint32_t(wrenGetSlotDouble(vm, slot)), result);
	}

	inline void read_sequence(WrenVM* vm, int slot, Type& sequence_type, Ref result)
	{
		if(wrenGetSlotType(vm, slot) != WREN_TYPE_LIST)
			return;

		wrenEnsureSlots(vm, slot + 2);
		int count = wrenGetListCount(vm, slot);

		for(int i = 0; i < count; ++i)
		{
			Var element = meta(*iter(sequence_type).m_element_type).m_empty_ref;
			wrenGetListElement(vm, slot, i, slot + 1);
			read(vm, slot + 1, element);
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
			push(vm, slots, element);
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

	class WrenContext : public NonCopy
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
			string result = replace(replace(replace(name, "<", "_"), ">", ""), "*", "");
			for(auto& nemespace : m_namespaces)
				result = replace(result, nemespace.first + "::", "");
			result[0] = char(toupper(result[0]));
			return result;
		}

		void register_type(Type& type)
		{
			if(!g_meta[type.m_id])
			{
				printf("WARNING: wren - type %s doesn't have reflection meta type\n", type.m_name);
				return;
			}

			auto module = [&](Type& type) -> string
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

			array<cstring> path = namespace_path(*function.m_namespace);

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

#ifdef MUD_WREN_DEBUG_DECLS
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

namespace mud
{
	static map<string, string> namespaces()
	{
		map<string, string> n;
		n["mud"] = "toy";
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

	Var WrenInterpreter::get(const string& name, Type& type)
	{
		wrenBegin(m_context->m_vm);
		wrenEnsureSlots(m_context->m_vm, 1);
		wrenGetVariable(m_context->m_vm, "main", name.c_str(), 0);
		Var result = Ref(&type);
		read(m_context->m_vm, 0, result);
		return result;
	}

	void WrenInterpreter::set(const string& name, Var value)
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
		wrenAssignVariable(m_context->m_vm, "main", name.c_str(), 0);
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

	void WrenInterpreter::call(const string& code, Var* result)
	{
		UNUSED(result);
		wrenInterpret(m_context->m_vm, "main", code.c_str());
	}

	void WrenInterpreter::virtual_call(Method& method, Ref object, array<Var> args)
	{
		m_script = m_virtual_scripts[object.m_value];
		call_wren_virtual(m_context->m_vm, method, object, args);
	}

	void WrenInterpreter::create_virtual(Ref object)
	{
		m_virtual_scripts[object.m_value] = m_script;
	}
}
