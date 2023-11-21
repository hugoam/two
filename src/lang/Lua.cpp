//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
#include <lang/LuaLib.h>
module two.lang;

#include <infra/Swap.h>

#define TWO_LUA_DEBUG 0
#define TWO_LUA_DEBUG_IO 0

// @todo: there is a weird thing where there are constantly about 10 tables on the stack when entering a script
// so we are missing a pop somewhere in the paths used when declaring reflected types and functions probably

namespace two
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

	struct Stack
	{
		Stack(lua_State* state, int num = 1) : m_state(state), m_num(num) {}
		~Stack() { assert(lua_gettop(m_state) >= m_num); if(m_num >= 1) lua_pop(m_state, m_num); }

		Stack& operator=(Stack&& other) { using two::swap; swap(m_state, other.m_state); swap(m_num, other.m_num); return *this; }
		Stack(Stack&& other) : m_state(other.m_state), m_num(other.m_num) { other.m_num = 0; }

		Stack operator+(Stack&& other) && { Stack obj(m_state, m_num + other.m_num); m_num = 0; other.m_num = 0; return obj; }
		void operator+=(Stack&& other) { assert(m_state == other.m_state); m_num += other.m_num; other.m_num = 0; }

		lua_State* m_state;
		int m_num = 0;

		int release() { const auto n = m_num; m_num = 0; return n; }
	};

	class FromLua : public Dispatch<void, lua_State*, int>, public LazyGlobal<FromLua>
	{
	public:
		FromLua();
	};

	class ToLua : public Dispatch<Stack, lua_State*>, public LazyGlobal<ToLua>
	{
	public:
		ToLua();
	};

	inline void read_sequence(lua_State* state, int index, const Type& sequence_type, Ref result);
	inline Stack push_sequence(lua_State* state, const Var& value);

	inline void read_enum(lua_State* state, int index, const Type& type, Ref result);
	inline Stack push_enum(lua_State* state, const Var& value);

	inline Stack push_callable(lua_State* state, const Callable& callable);
	inline Stack push_null(lua_State* state);

	inline Call& lua_cached_call(const Callable& callable)
	{
		static vector<unique<Call>> lua_call_table;
		if(callable.m_index >= lua_call_table.size())
			lua_call_table.resize(callable.m_index + 1);

		if(!lua_call_table[callable.m_index])
			lua_call_table[callable.m_index] = construct<Call>(callable);
		return *lua_call_table[callable.m_index];
	}

	inline void get_type_table(lua_State* state, const Type& type)
	{
		lua_pushlightuserdata(state, (void*)&type);
		lua_gettable(state, LUA_REGISTRYINDEX);
	}

	struct LuaRef : public Ref
	{
		LuaRef(bool alloc, void* pointer, const Type& type) : Ref(pointer, type), m_alloc(alloc) {}
		bool m_alloc;
	};

	inline LuaRef userdata(lua_State* state, int index)
	{
		return *static_cast<LuaRef*>(lua_touserdata(state, index));
	}

	inline LuaRef* alloc_userdata(lua_State* state, const Type& type, size_t size)
	{
		LuaRef* ref = static_cast<LuaRef*>(lua_newuserdata(state, size));
		get_type_table(state, type);
		lua_setmetatable(state, -2);
		return ref;
	}

	inline Ref alloc_object(lua_State* state, const Type& type)
	{
		LuaRef* ref = alloc_userdata(state, type, sizeof(LuaRef) + type.m_size);
		new (stl::placeholder(), ref) LuaRef(true, ref + 1, type); return *ref;
	}

	inline Ref alloc_ref(lua_State* state, Ref source)
	{
		LuaRef* ref = alloc_userdata(state, *source.m_type, sizeof(LuaRef));
		new (stl::placeholder(), ref) LuaRef(false, source.m_value, *source.m_type); return *ref;
	}

	inline Stack push_ref(lua_State* state, Ref object)
	{
		alloc_ref(state, object);
#if TWO_LUA_DEBUG
		printf("Lua -> pushed ref %s at %p\n", type(object).m_name, object.m_value);
#endif
		return{ state, 1 };
	}

	inline Stack push_object(lua_State* state, Ref value)
	{
		Ref ref = alloc_object(state, *value.m_type);
		copy_construct(ref, value);
#if TWO_LUA_DEBUG
		printf("Lua -> pushed object %s at %p\n", type(value).m_name, ref.m_value);
#endif
		return{ state, 1 };
	}

	inline Stack push_value(lua_State* state, Ref value)
	{
		if(!ToLua::me().check(value))
		{
			lua_printf("ERROR : lua -> no dispatch to push_value type %s\n", value.m_type->m_name);
			return push_null(state);
		}
		return ToLua::me().dispatch(value, state);
	}

	inline Ref read_ref(lua_State* state, int index)
	{
		if(lua_isnil(state, index)) return Ref();
		else if(!lua_isuserdata(state, index)) return Ref();
		else return userdata(state, index);
#if TWO_LUA_DEBUG
		//printf("Lua -> read_value ref %s at %p\n", result.m_type ? result.m_type->m_name : "none", result.m_value);
#endif
	}

	inline Ref read_object(lua_State* state, int index, const Type& type_to_read)
	{
		if(lua_isnil(state, index)) return Ref(type_to_read);
		else if(lua_isuserdata(state, index))
		{
			Ref object = userdata(state, index);
			if(object.m_type->is(type_to_read))
				return object;
		}
#if TWO_LUA_DEBUG
		//printf("Lua -> read_value object %s at %p\n", type(result).m_name, result.m_value);
#endif
	}

	inline Ref read_type(lua_State* state, int index)
	{
		if(!lua_istable(state, index)) return Ref();
		lua_getfield(state, index, "cpp_type");
		Type* type = static_cast<Type*>(lua_touserdata(state, -1));
		lua_pop(state, 1);
		return Ref(type);
	}

	inline void read_value(lua_State* state, int index, const Type& type, Ref result)
	{
		UNUSED(type);
		FromLua::me().dispatch(result, state, index);
		//if(result.none())
		//	lua_printf("ERROR : lua -> reading wrong type %s expected %s\n", lua_typename(state, lua_type(state, index)), type.m_name);
	}

	inline Stack push_value(lua_State* state, const Var& var)
	{
		// @todo: what about automatic conversion as with visual scripts ? it might not belong here, maybe in read_value() ?
		// @todo: might want a case for is_complex() before is_object() ?
		if(var.none() || var.null())
			return push_null(state);
		// kludge
		else if(var.m_mode == VarMode::Ref && type(var).is<Member>())
			return push_ref(state, var.m_ref);
		else if(var.m_mode == VarMode::Ref && type(var).is<Callable>())
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

	inline void read_value(lua_State* state, int index, Var& value)
	{
		if(value.m_mode == VarMode::Ref && value.m_ref == Ref())
			value = read_ref(state, index);
		else if(type(value).is<Type>())
			value = read_type(state, index);
		else if(is_sequence(type(value)))
			read_sequence(state, index, type(value), value);
		else if(is_object(type(value)) || is_struct(type(value)))
			value = read_object(state, index, type(value));
		else if(is_enum(type(value)))
			read_enum(state, index, type(value), value);
		else
			read_value(state, index, type(value), value);
	}

	inline Stack global_table(lua_State* state)
	{
		lua_pushglobaltable(state); return{ state, 1 };
	}

	inline void set_table(lua_State* state, Var index, const Var& value)
	{
		push_value(state, index).release();
		push_value(state, value).release();
		lua_settable(state, -3);
	}
	
	inline void set_table(lua_State* state, cstring index, const Var& value)
	{
		push_value(state, value).release();
		lua_setfield(state, -2, index);
	}

	inline void set_global(lua_State* state, Var index, Var data)
	{
		Stack stack = global_table(state);
		set_table(state, index, data);
	}
	
	inline void set_global(lua_State* state, cstring index, Var data)
	{
		push_value(state, data).release();
		lua_setglobal(state, index);
	}

	inline void lookup_table_var(lua_State* state, Stack& stack, span<Var> indices)
	{
		for(size_t i = 0; i < indices.size(); ++i)
		{
			stack += push_value(state, indices[i]);
			lua_gettable(state, -2);
		}
	}

	inline Stack get_table(lua_State* state, cstring name)
	{
		lua_getfield(state, -1, name);
		return { state, 1 };
	}

	inline void lookup_table(lua_State* state, Stack& stack, span<cstring> indices)
	{
		for(size_t i = 0; i < indices.size(); ++i)
		{
			stack += { state, 1 };
			lua_getfield(state, -1, indices[i]);
		}
	}

	inline Stack lookup_table_var(lua_State* state, span<Var> indices)
	{
		Stack stack = global_table(state);
		lookup_table_var(state, stack, indices);
		return stack;
	}

	inline Stack lookup_table(lua_State* state, span<cstring> indices)
	{
		Stack stack = global_table(state);
		lookup_table(state, stack, indices);
		return stack;
	}

	inline Var get_global(lua_State* state, cstring name, const Type& type)
	{
		Var result = meta(type).m_empty_var;
		lua_getglobal(state, name);
		Stack stack = { state, 1 };
		read_value(state, -1, result);
		return result;
	}
	
	inline Var get_global(lua_State* state, span<cstring> indices, const Type& type)
	{
		Var result = meta(type).m_empty_var;
		Stack stack = global_table(state);
		lookup_table(state, stack, indices);
		read_value(state, -1, result);
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
	
	inline void call_lua(lua_State* state, Stack function, span<Var> parameters, Var* result = nullptr)
	{
		Stack arguments = { state, 0 };
		for(Var& param : parameters)
			arguments += push_value(state, param);
		Stack results = call_lua_stack(state, move(arguments), result ? 1 : 0, move(function));
		if(result)
			read_value(state, results.m_num, *result);
	}

	inline void exec_lua(lua_State* state, cstring code, Var* result = nullptr)
	{
		Stack stack = load_code(state, code);
		if(stack.m_num)
			call_lua(state, move(stack), {}, result);
	}

	inline bool read_params(lua_State* state, const Callable& callable, span<Var> vars, size_t skip = 0)
	{
		bool success = true;
		auto read_param = [&](const Param& param , Var& arg, size_t i)
		{
			read_value(state, -int(vars.m_count) + int(i), arg);
			success &= !arg.none();
			success &= param.nullable() || !arg.null();
			if(!success)
				error("lua -> %s wrong argument %s, expect %s%s, got %s%s\n",
					   callable.m_name, param.m_name, param.m_type->m_name, param.nullable() ? "" : " (non null)", type(arg).m_name, arg.null() ? " (null)" : "");
		};
		for(size_t i = 0; i < vars.m_count; ++i)
			read_param(callable.m_params[i+skip], vars[i], i);
		return success;
	}

	inline Stack call_cpp(lua_State* state, Call& call, size_t num_arguments)
	{
		bool enough_arguments = num_arguments >= call.m_callable->m_num_required;
		if(enough_arguments && read_params(state, *call.m_callable, { call.m_args, 0, num_arguments }))
		{
			call.prepare();
			call();
#if TWO_LUA_DEBUG
			printf("Lua -> called %s\n", call.m_callable->m_name);
#endif
			Stack result = Stack{ state, 0 };
			if(!call.m_result.none())
				result = push_value(state, call.m_result);
#if TWO_LUA_DEBUG
			//lua_dump_stack(state);
#endif
			return result;
		}
		lua_printf("[ERROR] lua -> %s wrong arguments\n", call.m_callable->m_name); // lua_printf
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
		return push_value(state, value).release();
	}

	inline int set_member(lua_State* state, int object_index, int value_index)
	{
		const Member& member = val<Member>(userdata(state, -1));
		Ref object = userdata(state, object_index);
		Var value = member.m_default_value;
		read_value(state, value_index, value);
		member.cast_set(object, value);
		return 0;
	}

	inline int construct_function(lua_State* state)
	{
		const Type& type = *static_cast<Type*>(lua_touserdata(state, lua_upvalueindex(1)));
		const Class& c = cls(type);
		size_t num_args = lua_gettop(state) - 1;
		const Constructor* constructor = c.constructor(num_args);
		if(constructor)
		{
			Call& construct = lua_cached_call(*constructor);
			if(read_params(state, *construct.m_callable, { construct.m_args, 1, num_args }, 1))
			{
				construct.prepare();
				construct(alloc_object(state, type));
			}
			else
				lua_pushnil(state);
		}
		else
		{
			lua_printf("[ERROR] lua -> %s no constructor taking %d arguments\n", type.m_name, int(num_args)); // lua_printf
			lua_pushnil(state);
		}
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

	inline void set_type_closure(lua_State* state, cstring name, lua_CFunction func, const Type& type)
	{
		lua_pushstring(state, name);
		lua_pushlightuserdata(state, (void*)&type);
		lua_pushcclosure(state, func, 1);
		lua_settable(state, -3);
	}

	inline void create_type_metatable(lua_State* state, const Type& type)
	{
		lua_pushlightuserdata(state, (void*)&type);
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
		lua_pushlightuserdata(state, (void*)&type);
		lua_settable(state, -3);

		lua_settable(state, LUA_REGISTRYINDEX);
	}

	void register_field(lua_State* state, const Type& type, cstring key, Ref field)
	{
		get_type_table(state, type);
		set_table(state, key, field);
		lua_pop(state, 1);
	}
	
	template <class T>
	inline void read_integer(lua_State* state, int index, Ref result)
	{
		int success; lua_Integer value = lua_tointegerx(state, index, &success);
		if(success)
			val<T>(result) = static_cast<T>(value);
	}

	template <class T>
	inline void read_number(lua_State* state, int index, Ref result)
	{
		int success; lua_Number value = lua_tonumberx(state, index, &success);
		if(success)
			val<T>(result) = static_cast<T>(value);
	}

	inline void read_cstring(lua_State* state, int index, Ref result)
	{
		size_t len; const char* value = lua_tolstring(state, index, &len);
		if(value)
			val<const char*>(result) = value;
	}

	inline void read_string(lua_State* state, int index, Ref result)
	{
		size_t len; const char* value = lua_tolstring(state, index, &len);
		if(value)
			val<string>(result) = value;
	}

	inline void read_null(lua_State* state, int index, Ref result)
	{
		if(lua_isnil(state, index))
			result = Ref();
	}

	inline void read_enum(lua_State* state, int index, const Type& type, Ref result)
	{
		if(!lua_isnumber(state, index) || fmod(lua_tonumber(state, index), 1.) != 0)
			return;
		result = enu(type).varn(uint32_t(lua_tointeger(state, index)));
	}

	inline void read_sequence(lua_State* state, int index, const Type& sequence_type, Ref result)
	{
		if(!lua_istable(state, index))
			return;

		lua_pushnil(state);
		while(lua_next(state, (index > 0) ? index : (index - 1)) != 0)
		{
			Var element = meta(*iter(sequence_type).m_element_type).m_empty_var;
			read_value(state, -1, element);
			sequence(result).add(result, element);
			lua_pop(state, 1); // pop the value but keep the key for the next iteration
		}
	}

	FromLua::FromLua()
	{
		function<int>     ([](void*, Ref result, lua_State* state, int index) { read_integer<int>(state, index, result); });
		function<ushort>  ([](void*, Ref result, lua_State* state, int index) { read_integer<ushort>(state, index, result); });
		function<uint>    ([](void*, Ref result, lua_State* state, int index) { read_integer<uint>(state, index, result); });
		function<ulong>   ([](void*, Ref result, lua_State* state, int index) { read_integer<ulong>(state, index, result); });
		function<ullong>  ([](void*, Ref result, lua_State* state, int index) { read_integer<ullong>(state, index, result); });
		function<float>   ([](void*, Ref result, lua_State* state, int index) { read_number<float>(state, index, result); });
		function<double>  ([](void*, Ref result, lua_State* state, int index) { read_number<double>(state, index, result); });
		function<cstring> ([](void*, Ref result, lua_State* state, int index) { read_cstring(state, index, result); });
		function<string>  ([](void*, Ref result, lua_State* state, int index) { read_string(state, index, result); });
		function<bool>    ([](void*, Ref result, lua_State* state, int index) { val<bool>(result) = lua_toboolean(state, index) != 0; });
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

	template <class T>
	Stack push_integer(lua_State* state, T value)
	{
		lua_pushinteger(state, value); return{ state, 1 };
	}

	inline Stack push_array(lua_State* state)
	{
		lua_newtable(state); return{ state, 1 };
	}

	template <class T>
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

	class LuaContext
	{
	public:
		explicit LuaContext(span<string> import_namespaces = {})
			: m_import_namespaces(import_namespaces.begin(), import_namespaces.end())
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

		span<cstring> namespace_path(Namespace& location, size_t shave_off = 0)
		{
			if(location.is_root())
				return {};
			if(import_namespace(location.m_path[0]))
				return location.m_path.size() == 1 ? span<cstring>{} : span<cstring>{ location.m_path.data() + 1, location.m_path.size() - 1 - shave_off };
			else
				return { location.m_path.data(), location.m_path.size() - shave_off };
		}

		void register_namespace(Namespace& location)
		{
			if(location.is_root())
				return;
			Stack stack = lookup_table(m_state, namespace_path(location, 1));
			lua_newtable(m_state);
			lua_setfield(m_state, -2, location.m_path.back());
		}

		void register_enum(const Type& type)
		{
			Enum& e = enu(type);

			Stack stack = lookup_table(m_state, namespace_path(*meta(type).m_namespace));
				
			if(e.m_scoped)
				stack += get_table(m_state, type.m_name);

			for(size_t i = 0; i < e.m_names.size(); ++i)
			{
				set_table(m_state, e.m_names[i], e.varn(uint32_t(i)));
			}
		}

		void register_type(const Type& type)
		{
			if(!g_meta[type.m_id])
			{
				warn("lua - type %s doesn't have reflection meta type\n", type.m_name);
				return;
			}

			create_type_metatable(m_state, type);

			Stack stack = lookup_table(m_state, namespace_path(*meta(type).m_namespace));
			get_type_table(m_state, type);
			lua_setfield(m_state, -2, type.m_name);

			if(is_enum(type))
				register_enum(type);
		}

		void register_alias(Alias& alias)
		{
			Stack stack = lookup_table(m_state, namespace_path(*alias.m_namespace));
			get_type_table(m_state, *alias.m_type);
			lua_setfield(m_state, -2, alias.m_name);
		}

		void register_function(Function& function)
		{
			Stack stack = lookup_table(m_state, namespace_path(*function.m_namespace));
			set_table(m_state, function.m_name, Ref(&function));
		}

		void register_static(const Type& type, Static& member)
		{
			//Stack stack = lookup_table(m_state, { string(type.m_name) });
			get_type_table(m_state, type);
			set_table(m_state, member.m_name, member.m_value);
		}

		void register_method(const Type& type, Method& method)
		{
			register_field(m_state, type, method.m_name, Ref(&method));
		}

		void register_member(const Type& type, Member& member)
		{
			register_field(m_state, type, member.m_name, Ref(&member));
		}
		
		vector<string> m_import_namespaces;

		lua_State* m_state;
	};
}


namespace two
{
	LuaInterpreter::LuaInterpreter(bool import_symbols)
		: m_context(construct<LuaContext>(vector<string>{ "two", "toy" }))
	{
		//g_lua_print_output = &m_output;
		if(import_symbols)
			this->declare_types();
	}

	LuaInterpreter::~LuaInterpreter()
	{}

	void LuaInterpreter::declare_types()
	{
		System& system = System::instance();

		//info("declaring lua Meta info");
		//system.dumpMetaInfo();

		for(Namespace& location : system.m_namespaces)
			m_context->register_namespace(location);

		for(Function* function : system.m_functions)
			m_context->register_function(*function);

		for(Type* type : system.m_types)
			m_context->register_type(*type);

		for(Alias* alias : system.m_aliases)
			m_context->register_alias(*alias);

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

	Var LuaInterpreter::get(const string& name, const Type& type)
	{
		return get_global(m_context->m_state, name.c_str(), type);
	}

	void LuaInterpreter::set(const string& name, const Var& value)
	{
		set_global(m_context->m_state, name.c_str(), value);
	}

	Var LuaInterpreter::getx(span<cstring> path, const Type& type)
	{
		return get_global(m_context->m_state, path, type);
	}

	void LuaInterpreter::setx(span<cstring> path, const Var& value)
	{
		Stack stack = lookup_table(m_context->m_state, { path, path.size() - 1 });
		set_table(m_context->m_state, *path.end(), value);
	}

	void LuaInterpreter::call(const string& code, Var* result)
	{
#if TWO_LUA_DEBUG_IO
		printf("lua -> %s\n", code);
#endif
		exec_lua(m_context->m_state, code.c_str(), result);
#if TWO_LUA_DEBUG_IO
		printf("lua -> %s\n", m_output.c_str());
		m_output = "";
#endif
	}

}
