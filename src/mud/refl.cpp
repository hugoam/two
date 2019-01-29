#include <mud/pool.h>
#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>


#ifdef MUD_MODULES
module mud.refl;
#else
//#include <refl/Class.h>
//#include <refl/VirtualMethod.h>
#endif

namespace mud
{
	Call::Call()
	{}

	Call::Call(const Callable& callable, vector<Var> arguments)
		: m_callable(&callable)
		, m_arguments(arguments)
		, m_result(meta(*callable.m_return_type.m_type).m_empty_var)
	{}

	Call::Call(const Callable& callable)
		: Call(callable, vector<Var>{})//, callable.m_arguments)
	{}

	Call::Call(const Callable& callable, Ref object)
		: Call(callable)
	{
		m_arguments[0] =  object;
	}

	//bool Call::validate() { return m_callable && m_callable->validate(to_array(m_arguments)); }

	//const Var& Call::operator()() { (*m_callable)(to_array(m_arguments), m_result); return m_result; }
	//const Var& Call::operator()(Ref object) { m_arguments[0] = object; (*m_callable)(to_array(m_arguments), m_result); return m_result; }
}

#ifdef MUD_MODULES
module mud.refl;
#else
#include <stl/tinystl/vector.impl.h>
#endif

using namespace mud;
namespace tinystl
{
	template class MUD_TYPE_EXPORT vector<Namespace>;
	template class MUD_TYPE_EXPORT vector<Param>;
	template class MUD_TYPE_EXPORT vector<Function>;
	template class MUD_TYPE_EXPORT vector<Operator>;
	template class MUD_TYPE_EXPORT vector<Constructor>;
	template class MUD_TYPE_EXPORT vector<CopyConstructor>;
	template class MUD_TYPE_EXPORT vector<Destructor>;
	template class MUD_TYPE_EXPORT vector<Method>;
	template class MUD_TYPE_EXPORT vector<Member>;
	template class MUD_TYPE_EXPORT vector<Static>;
	template class MUD_TYPE_EXPORT vector<Function*>;
	template class MUD_TYPE_EXPORT vector<Method*>;
	template class MUD_TYPE_EXPORT vector<Member*>;
	template class MUD_TYPE_EXPORT vector<Meta*>;
	template class MUD_TYPE_EXPORT vector<Enum*>;
	template class MUD_TYPE_EXPORT vector<Convert*>;
	template class MUD_TYPE_EXPORT vector<Iterable*>;
	template class MUD_TYPE_EXPORT vector<Sequence*>;
	template class MUD_TYPE_EXPORT vector<Class*>;
	template class MUD_TYPE_EXPORT vector<Module*>;
	template class MUD_TYPE_EXPORT vector<Prototype*>;
}


#ifdef MUD_MODULES
module mud.refl;
#else
//#include <ecs/Proto.h>
#endif

namespace mud
{
	Injector::Injector(const Constructor& constructor)
		: Call(constructor)
		, m_object_type(*constructor.m_object_type)
		, m_constructor(constructor)
#ifdef MUD_ECS_PROTO
		, m_proto(is<Prototype>(type) ? &as<Prototype>(type) : nullptr)
#endif
	{
#ifdef MUD_ECS_PROTO
		if(m_proto && &constructor == &cls(type).m_constructors[int(ConstructorIndex::ProtoParts)])
		{
			// we are a combined constructor
			size_t offset = cls(*m_proto->m_stem).m_constructors[int(ConstructorIndex::Default)].m_params.size();
			for(Type* part : m_proto->m_parts)
			{
				m_partIndex.push_back(offset);
				offset += cls(*part).m_constructors[int(ConstructorIndex::Default)].m_params.size();
			}
		}
#endif
	}

	Injector::Injector(Type& type, ConstructorIndex index)
		: Injector(cls(type).m_constructors[int(index)])
	{}

	Injector::Injector(Type& type, size_t arguments)
		: Injector(*cls(type).constructor(arguments))
	{}

	void Injector::inject(Var& value)
	{
		//m_constructor(value, to_array(m_arguments, 1));
	}

	Ref Injector::inject(Pool& pool)
	{
		Ref ref = pool.alloc();
		//m_constructor.m_call(ref, to_array(m_arguments, 1));
		return ref;
	}

	Var Injector::injectvar()
	{
		Var value = meta(m_object_type).m_empty_var;
		this->inject(value);
		return value;
	}

	Ref Injector::injectpool()
	{
		Pool& pool = *g_pools[m_object_type.m_id];
		return this->inject(pool);
	}

	void Injector::destroy(Ref object)
	{
		Pool& pool = *g_pools[m_object_type.m_id];
		pool.destroy(object);
	}

#ifdef MUD_ECS_PROTO
	array<Var> Injector::args(Type& type)
	{
		size_t index = m_partIndex[m_proto->part_index(type)];
		return to_array(m_args, index);
	}
#endif

	Creator::Creator(Type& type)
		: m_type(type)
#ifdef MUD_ECS_PROTO
		, m_construct(cls(type).m_prototypes.size() > 0)
		, m_prototype(m_construct ? cls(type).m_prototypes[0] : nullptr)
#else
		, m_construct(false)
		, m_prototype(nullptr)
#endif
		, m_injector(oconstruct<Injector>(m_prototype ? *m_prototype : type))
	{}

	void Creator::set_prototype(Type& prototype)
	{
		m_prototype = &prototype;
		m_injector = oconstruct<Injector>(*m_prototype);
	}
}


#ifdef MUD_MODULES
module mud.refl;
#else
#endif

namespace mud
{
	Static::Static(Type& parent_type, cstring name, Ref value)
		: m_parent_type(&parent_type)
		, m_name(name)
		, m_value(value)
	{}

	Member::Member(Type& object_type, size_t offset, Type& type, cstring name, const void* default_value, Flags flags, MemberGet get)
		: m_index(0)
		, m_object_type(&object_type)
		, m_offset(offset)
		, m_type(&type)
		, m_name(name)
		, m_default_value((void*)default_value, type)
		, m_flags(flags)
		, m_get(get)
	{}

	Member::~Member()
	{}
}


#ifdef MUD_MODULES
module mud.refl;
#else
//#include <ecs/Proto.h>
//#include <ecs/Entity.h>
//#include <srlz/Serial.h>
#endif

namespace mud
{
	vector<Meta*> g_meta = vector<Meta*>(c_max_types);
	vector<Class*> g_class = vector<Class*>(c_max_types);
	vector<Enum*> g_enu = vector<Enum*>(c_max_types);
	vector<Convert*> g_convert = vector<Convert*>(c_max_types);
	vector<Iterable*> g_iterable = vector<Iterable*>(c_max_types);
	vector<Sequence*> g_sequence = vector<Sequence*>(c_max_types);

#if 0
	template <>
	void init_string<void>() {}

	template <>
	void init_string<void*>() {}

	template <>
	void init_string<cstring>() {}

	template <>
	void init_assign<void*>() {}

	template <>
	void init_assign<cstring>() {}
#endif

	bool is_string(Type& type)
	{
		return type.is<string>() || type.is<cstring>() || type.is<string>();
	}

	string get_string(Member& member, Ref value)
	{
		if(member.m_type->is<cstring>())
			return val<cstring>(member.get(value));
		else if(member.m_type->is<string>())
			return val<string>(member.get(value));
		else
			return to_string(member.get(value));
	}

	Meta::Meta(Type& type, Namespace* location, cstring name, size_t size, TypeClass type_class, bool is_array)
		: m_type(&type)
		, m_namespace(location)
		, m_name(name)
		, m_size(size)
		, m_type_class(type_class)
		, m_is_array(is_array)
	{
		type.m_name = m_name;
		g_meta[type.m_id] = this;
	}

	Enum::Enum(Type& type, bool scoped, array<cstring> names, array<uint32_t> values, array<void*> vars)
		: m_type(type)
		, m_scoped(scoped)
		, m_names(names)
		, m_values(values)
		, m_vars(vars)
	{
		g_enu[type.m_id] = this;

		for(size_t i = 0; i < m_names.size(); ++i)
		{
			size_t value = m_values[i];
			if(value > size_t(1 << 16))
			{
				printf("WARNING: enum value %s::%s above 2^16, something is fishy\n", type.m_name, m_names[i]);
				continue;
			}
			m_reverse.resize(value + 1);
			m_reverse[value] = m_names[i];
		}
	}

	uint32_t Enum::value(cstring name)
	{
		for(uint32_t i = 0; i < uint32_t(m_names.size()); ++i)
			if(strcmp(name, m_names[i]) == 0)
				return m_values[i];
		printf("WARNING: fetching unknown Enum %s value : %s\n", m_type.m_name, name);
		return m_values[0];
	}

	uint32_t Enum::value(Ref value)
	{
		const size_t size = m_type.m_size;
		for(uint32_t i = 0; i < uint32_t(m_vars.size()); ++i)
			if(memcmp(value.m_value, m_vars[i], size) == 0)
				return m_values[i];
		printf("WARNING: fetching unknown Enum %s index : %s\n", m_type.m_name, to_string(value).c_str());
		return 0;
	}

	uint32_t Enum::index(cstring name)
	{
		for(uint32_t i = 0; i < uint32_t(m_names.size()); ++i)
			if(strcmp(name, m_names[i]) == 0)
				return i;
		printf("WARNING: fetching unknown Enum %s index : %s\n", m_type.m_name, name);
		return 0;
	}

	uint32_t Enum::index(Ref value)
	{
		const size_t size = m_type.m_size;
		for(uint32_t i = 0; i < uint32_t(m_vars.size()); ++i)
			if(memcmp(value.m_value, m_vars[i], size) == 0)
				return i;
		printf("WARNING: fetching unknown Enum %s index : %s\n", m_type.m_name, to_string(value).c_str());
		return 0;
	}

	Class::Class(Type& type)
		: m_type(&type)
		, m_meta(&meta(type))
		, m_root(&type)
	{
		g_class[type.m_id] = this;
	}

	Class::Class(Type& type, array<Type*> bases, array<size_t> bases_offsets, array<Constructor> constructors, array<CopyConstructor> copy_constructors,
				 array<Member> members, array<Method> methods, array<Static> static_members)
		: m_type(&type)
		, m_meta(&meta(type))
		, m_root(&type)
		, m_bases(bases)
		, m_bases_offsets(bases_offsets)
		, m_constructors(constructors)
		, m_copy_constructors(copy_constructors)
		, m_members(members)
		, m_methods(methods)
		, m_static_members(static_members)
	{
		g_class[type.m_id] = this;
	}

	Class::~Class()
	{}

	void Class::inherit(vector<Type*> types)
	{
		//for(Type* type : types)
		//	if(g_class[type->m_id])
		//	{
		//		vector_prepend(m_members, cls(*type).m_members);
		//		vector_prepend(m_methods, cls(*type).m_methods);
		//	}
	}

	void Class::setup_class()
	{
		//this->inherit(m_bases);

		for(size_t i = 0; i < m_members.size(); ++i)
			m_members[i].m_index = int(i);

		for(size_t i = 0; i < m_constructors.size(); ++i)
			m_constructors[i].m_index = i;

		for(Member& member : m_members)
		{
			if(member.is_structure() && strcmp(member.m_name, "contents") == 0) // @kludge name check is a kludge until we separate structure and nested member
				m_nested = true;
			if(strcmp(member.m_name, "id") == 0 || strcmp(member.m_name, "index") == 0)
				m_id_member = &member;
			if(strcmp(member.m_name, "name") == 0 && is_string(*member.m_type))
				m_name_member = &member;
			if(strcmp(member.m_name, "type") == 0 && member.m_type->is<Type>())
				m_type_member = &member;

			if(member.is_component())
				m_components.push_back(&member);

			m_field_names.push_back(member.m_name);
			m_field_values.push_back(member.m_default_value);
		}

		for(Member* component : m_components)
			if(g_class[component->m_type->m_id])
			{
				Class& c = cls(*component->m_type);
				for(Member& member : c.m_members)
					m_deep_members.push_back(&member);
				for(Method& method : c.m_methods)
					m_deep_methods.push_back(&method);
			}
	}

	Ref Class::upcast(Ref object, Type& base)
	{
		if(!object) return object;
		for(size_t i = 0; i < m_bases.size(); ++i)
			if(m_bases[i]->is(base))
			{
				Ref upcasted = { static_cast<char*>(object.m_value) + m_bases_offsets[i], base };
				return &type(upcasted) == &base ? upcasted : cls(upcasted).upcast(upcasted, base);
			}
		return object;
	}

	Ref Class::downcast(Ref object, Type& base)
	{
		if(!object) return object;
		for(size_t i = 0; i < m_bases.size(); ++i)
			if(m_bases[i] == &base)
			{
				return { static_cast<char*>(object.m_value) - m_bases_offsets[i], *m_type };
			}
		return object;
	}

	Member& Class::member(cstring name)
	{
		for(Member& member : m_members)
			if(strcmp(member.m_name, name) == 0)
				return member;
		return m_members[0];
	}

	Method& Class::method(cstring name)
	{
		for(Method& method : m_methods)
			if(strcmp(method.m_name, name) == 0)
				return method;
		return m_methods[0];
	}

	Static& Class::static_member(cstring name)
	{
		for(Static& member : m_static_members)
			if(strcmp(member.m_name, name) == 0)
				return member;
		return m_static_members[0];
	}

	Operator& Class::op(cstring name)
	{
		for(Operator& op : m_operators)
			if(strcmp(op.m_function->m_name, name) == 0)
				return op;
		return m_operators[0];
	}

	bool Class::has_member(cstring name)
	{
		return has_pred(m_members, [&](const Member& member) { return strcmp(member.m_name, name) == 0; });
	}

	bool Class::has_method(cstring name)
	{
		return has_pred(m_methods, [&](const Method& method) { return strcmp(method.m_name, name) == 0; });
	}

	Member& Class::member(size_t offset)
	{
		for(Member& look : m_members)
			if(look.m_offset == offset)
				return look;
		printf("ERROR: retrieving member\n");
		return m_members[0];
	}

	Method& Class::method(Address address)
	{
		for(Method& look : m_methods)
			if(look.m_address == address)
				return look;
		printf("ERROR: retrieving method\n");
		return m_methods[0];
	}

	bool Class::has_member(size_t offset)
	{
		return has_pred(m_members, [&](const Member& look) { return look.m_offset == offset; });
	}

	bool Class::has_method(Address address)
	{
		return has_pred(m_methods, [&](const Method& look) { return look.m_address == address; });
	}

	const Constructor* Class::constructor(ConstructorIndex index) const
	{
		const Constructor* constructor = nullptr;
		if(index == ConstructorIndex::Default)
			constructor = this->constructor(m_members.size());
		if(!constructor && !m_constructors.empty())
			return &m_constructors[0];
		return constructor;
	}

	const Constructor* Class::constructor(size_t arguments) const
	{
		for(const Constructor& constructor : m_constructors)
		{
			size_t min_args = constructor.m_params.size() - 1 - constructor.m_num_defaults;
			size_t max_args = constructor.m_params.size() - 1;
			if(arguments >= min_args && arguments <= max_args)
				return &constructor;
		}
		return nullptr;
	}

	bool Class::is(Type& component)
	{
		return vector_find(m_components, [&](Member* member) { return member->m_type->is(component); }) != nullptr;
	}

	Ref Class::as(Ref object, Type& component)
	{
		Member* member = *vector_find(m_components, [&](Member* member) { return member->m_type->is(component); });
		return cls(*member->m_type).upcast(member->get(object), component);
	}

	bool compare(Ref first, Ref second)
	{
		UNUSED(first); UNUSED(second);
		return false;
	}

	void copy_construct(Ref dest, Ref source)
	{
		if(is_basic(*dest.m_type))
			memcpy(dest.m_value, source.m_value, meta(dest).m_size);
		//else if(cls(dest).m_copy_constructors.size() > 0)
		//	cls(dest).m_copy_constructors[0](dest, source);
	}

	void assign(Ref first, Ref second)
	{
		if(second.m_type->is(*first.m_type))
			meta(first).copy_assign(first, second);
		else
			printf("WARNING: can't assign values of unrelated types\n");
	}

	void assign_pointer(Ref first, Ref second)
	{
		UNUSED(first); UNUSED(second);
	}

	string to_name(Type& type, Ref value)
	{
		string name;
		if(is_basic(type))
			name = to_string(value);
		else if(!value)
			name = "null";
		else if(cls(type).m_name_member)
			name = get_string(*cls(type).m_name_member, value);
		else if(cls(type).m_id_member)
			name = string(type.m_name) + " : " + to_string(cls(type).m_id_member->get(value));
		else
			name = string(type.m_name); // + " : " + to_string(value.m_value); // @todo void* to string fails with vs2017 + modules
		return name;
	}

	TypeConverter::TypeConverter()
		: DoubleDispatch()
	{
		this->default_converter<float, double>();
		this->default_converter<float, int>();
		this->default_converter<float, ushort>();
		this->default_converter<float, uint>();
		this->default_converter<float, ulong>();
		this->default_converter<float, ullong>();
		this->default_converter<double, int>();
		this->default_converter<double, ushort>();
		this->default_converter<double, uint>();
		this->default_converter<double, ulong>();
		this->default_converter<double, ullong>();
		this->default_converter<int, ushort>();
		this->default_converter<int, uint>();
		this->default_converter<int, ulong>();
		this->default_converter<int, ullong>();
		this->default_converter<ushort, uint>();
		this->default_converter<ushort, ulong>();
		this->default_converter<ushort, ullong>();
		this->default_converter<uint, ulong>();
		this->default_converter<uint, ullong>();
		this->default_converter<ulong, ullong>();
	}

	bool TypeConverter::check(Type& input, Type& output)
	{
		return DoubleDispatch::check(input, output);
	}

	bool TypeConverter::check(Ref input, Type& output)
	{
		return DoubleDispatch::check(*input.m_type, output);
	}

	Var TypeConverter::convert(Ref input, Type& output)
	{
		Var result = meta(output).m_empty_var;
		DoubleDispatch::dispatch(input, result);
		return result;
	}

	void TypeConverter::convert(Ref input, Type& output, Var& result)
	{
		if(result.none() || !type(result).is(output))
			result = meta(output).m_empty_var;
		DoubleDispatch::dispatch(input, result);
	}

	bool is_related(Type& input, Type& output)
	{
		UNUSED(input); UNUSED(output);
		return false;
	}
	
	inline void assign(Var& source, Var& dest, bool ref)
	{
		if(ref)
			dest = source;
		else
			dest = source.m_ref;
	}

	bool convert(Var& source, Type& output, Var& dest, bool ref)
	{
		Ref value = source;
		if(output.is(type<Ref>()))
			dest = source;
		else if(type(value).is(output))
			assign(source, dest, ref);
		else if(g_class[type(source).m_id] && cls(source).is(output))
			dest = cls(source).as(source.m_ref, output);
		else if(TypeConverter::me().check(value, output))
			TypeConverter::me().convert(value, output, dest);
		else
		{
			dest.clear();
			return false;
		}

		return true;
	}

	bool convert(Ref input, Type& output, Var& result)
	{
		Var inputvar = input;
		return convert(inputvar, output, result);
	}

	Var convert(Ref input, Type& output)
	{
		Var result;
		convert(input, output, result);
		return result;
	}

	bool can_convert(Type& input, Type& output)
	{
		return input.is(output) || is_related(input, output) || TypeConverter::me().check(input, output);
	}

	bool can_convert(Ref input, Type& output)
	{
		return type(input).is(output) || is_related(type(input), output) || TypeConverter::me().check(input, output);
	}
}


#ifdef MUD_MODULES
module mud.refl;
#else
#endif

namespace mud
{
	template <> Type& type<VirtualMethod>() { static Type ty("VirtualMethod"); return ty; }

	Param::Param(cstring name, Type& type, Flags flags, void* default_val)
		: m_name(name)
		, m_type(&type)
		, m_flags(flags)
		, m_default(default_val)
	{
		//if(value == Ref())
		//	m_flags = static_cast<Flags>(m_flags | Nullable);
	}

	Signature::Signature(const vector<Param>& params, QualType return_type)
		: m_params(params)
		, m_return_type(return_type)
	{}

	static uint32_t s_callable_index = 0;

	Callable::Callable(cstring name, const vector<Param>& params, QualType return_type)
		: m_index(++s_callable_index)
		, m_name(name)
		, m_return_type(return_type)
		, m_params(params)
		, m_num_defaults(0)
	{
		this->setup();
	}

	void Callable::setup()
	{
		//for(size_t i = 0; i < m_params.size(); ++i)
		//{
		//	m_params[i].m_index = i;
		//	m_arguments.push_back({ m_params[i].m_value });
		//
		//	if(m_num_defaults == 0 && m_params[i].defaulted())
		//		m_num_defaults = m_params.size() - i;
		//}
		//
		//m_num_required = m_params.size() - m_num_defaults;
	}

	bool Callable::validate(array<void*> args, size_t offset) const
	{
		UNUSED(args); UNUSED(offset);
		//if(args.m_count < m_arguments.size() - m_num_defaults)
		//	return false;
		//
		//bool valid = true;
		//for(size_t i = offset; i < m_params.size(); ++i)
		//{
		//	valid &= type(m_params[i].m_value).is(type(args[i]));
		//	valid &= m_params[i].nullable() || !args[i].null();
		//}
		//return valid;
		return true;
	}

	Function::Function(Namespace* location, cstring name, FunctionPointer identity, FunctionFunc trigger, const vector<Param>& params, QualType return_type)
		: Callable(name, params, return_type)
		, m_namespace(location)
		, m_identity(identity)
		, m_call(trigger)
	{
		Operator op = as_operator(*this);
		if(op && is_class(*op.m_type))
		{
			cls(*op.m_type).m_operators.push_back(op);
		}
	}

	Operator as_operator(Function& function)
	{
		if(function.m_name == string("add"))
		{
			return { &function, function.m_params[0].m_type, function.m_name, "+" };
		}
		else if(function.m_name == string("subtract"))
		{
			return { &function, function.m_params[0].m_type, function.m_name, "-" };
		}
		else if(function.m_name == string("multiply"))
		{
			return { &function, function.m_params[0].m_type, function.m_name, "*" };
		}
		else if(function.m_name == string("divide"))
		{
			return { &function, function.m_params[0].m_type, function.m_name,  "/" };
		}
		else return {};
	}

	Method::Method(Type& object_type, cstring name, Address address, MethodFunc trigger, const vector<Param>& params, QualType return_type)
		: Callable(name, vector_union({ 1, { "self", object_type } }, params), return_type)
		, m_object_type(&object_type)
		, m_address(address)
		, m_call(trigger)
	{}

	Constructor::Constructor(Type& object_type, ConstructorFunc constructor, const vector<Param>& params)
		: Callable(object_type.m_name, vector_union({ 1, { "self", object_type } }, params))
		, m_object_type(&object_type)
		, m_call(constructor)
	{}

	Constructor::Constructor(Type& object_type, cstring name, ConstructorFunc constructor, const vector<Param>& params)
		: Callable(name, vector_union({ 1, { "self", object_type } }, params))
		, m_object_type(&object_type)
		, m_call(constructor)
	{}

	CopyConstructor::CopyConstructor(Type& object_type, CopyConstructorFunc constructor)
		: Callable(object_type.m_name, { 1, { "self", object_type } })
		, m_object_type(&object_type)
		, m_call(constructor)
	{}

	Destructor::Destructor(Type& object_type, DestructorFunc destructor)
		: Callable(object_type.m_name, { 1, { "self", object_type } })
		, m_object_type(&object_type)
		, m_call(destructor)
	{}
}


#ifdef MUD_MODULES
module mud.refl;
#else
#endif

namespace mud
{
	Module::Module(cstring name, vector<Module*> deps)
		: m_name(name)
		, m_deps(deps)
	{}
}


#ifdef MUD_MODULES
module mud.refl;
#else
#endif

namespace mud
{
	Namespace::Namespace(cstring name, Namespace* parent)
		: m_name(name)
		, m_parent(parent)
	{
		if(parent)
		{
			m_path = parent->m_path;
			m_path.push_back(name);
		}
	}

	Namespace& namspc(vector<cstring> path)
	{
		return system().get_namespace(path);
	}
}


#ifdef MUD_MODULES
module mud.refl;
#else
#include <stl/string.h>
#endif

#ifdef _WIN32
	#include <windows.h>
	#define BINARY_EXT ".exe"
	#define MODULE_EXT ".dll"
#else
	#include <dlfcn.h>
	#define BINARY_EXT ""
	#define MODULE_EXT ".so"
#endif

#ifdef _DEBUG
	#define BUILD_SUFFIX "_d"
#else
	#define BUILD_SUFFIX ""
#endif

#include <cstdio>

namespace mud
{
	Module* load_module(cstring path)
	{
		string module_path = string(path) + BUILD_SUFFIX + MODULE_EXT;
		string loaded_path = string(path) + BUILD_SUFFIX + "_loaded" + MODULE_EXT;
		
		if(!file_exists(module_path))
		{
			printf("ERROR: Module %s not found\n", module_path.c_str());
			return nullptr;
		}

		copy_file(module_path, loaded_path);

#ifdef _WIN32
		HMODULE module_handle = LoadLibraryA(loaded_path.c_str());
#else
		void* module_handle = dlopen(loaded_path.c_str(), RTLD_NOW);
#endif

#ifdef _WIN32
		GetModule get_module = (GetModule)GetProcAddress(module_handle, "getModule");
#else
		GetModule get_module = (GetModule)dlsym(module_handle, "getModule");
#endif

		Module& m = get_module();

		m.m_handle = module_handle;
		m.m_path = module_path.c_str();

		return &m;
	}

	void unload_module(Module& m)
	{
#ifdef _WIN32
		int result = FreeLibrary((HMODULE) m.m_handle);
#else
		int result = dlclose(m.m_handle);
#endif
		UNUSED(result);
	}

	void reload_module(Module& m)
	{
#ifdef _WIN32
		HANDLE module_file = CreateFile(m.m_path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if(module_file == INVALID_HANDLE_VALUE)
			return;

		uint64_t last_modified;
		GetFileTime(module_file, NULL, NULL, (FILETIME*)&last_modified);

		if(m.m_last_modified < last_modified)
		{
			// do reload
		}

		CloseHandle(module_file);
#else
		UNUSED(m);
#endif
	}

	FunctionPointer module_function(Module& module, cstring name)
	{
#ifdef _WIN32
		return (FunctionPointer)GetProcAddress((HMODULE)module.m_handle, name);
#else
		return (FunctionPointer)dlsym(module.m_handle, name);
#endif
	}

	System::System()
	{
		m_namespaces.reserve(100);
	}

	void System::launch_process(cstring path, cstring args)
	{
		string binary_path = string(path) + BUILD_SUFFIX + BINARY_EXT;

#ifdef _WIN32
		STARTUPINFO startupInfo = { sizeof(startupInfo) };
		PROCESS_INFORMATION processInfo = {};

		string cmd = string(path) + " " + string(args);
		vector<char> mutcmd(cmd.c_str(), cmd.c_str() + cmd.size() + 1);

		CreateProcess(path, mutcmd.data(), NULL, NULL, FALSE, 0, NULL, NULL, &startupInfo, &processInfo);

		WaitForSingleObject(processInfo.hProcess, INFINITE);
		CloseHandle(processInfo.hProcess);
		CloseHandle(processInfo.hThread);
#else
		UNUSED(binary_path); UNUSED(args);
#endif
	}

	void System::load_modules(vector<Module*> modules)
	{
		for(Module* m : modules)
			this->load_module(*m);
	}

	bool System::has_module(Module& m)
	{
		return vector_has(m_modules, &m);
	}

	Module* System::open_module(cstring path)
	{
		return mud::load_module(path);
	}

	void System::load_module(Module& m)
	{
		if(vector_has(m_modules, &m))
			return;

		m_modules.push_back(&m);

		for(Module* dep : m.m_deps)
			load_module(*dep);

		for(Type* type : m.m_types)
			m_types.push_back(type);

		for(Function* function : m.m_functions)
			m_functions.push_back(function);
	}

	void System::unload_module(Module& m)
	{
		vector_remove(m_modules, &m);

		for(Type* type : m.m_types)
			vector_remove(m_types, type);

		for(Function* function : m.m_functions)
			vector_remove(m_functions, function);

		mud::unload_module(m);
	}

	Module& System::reload_module(Module& m)
	{
		cstring path = m.m_path;
		this->unload_module(m);
		Module& reloaded = *this->open_module(path);
		this->load_module(reloaded);
		return reloaded;
	}

	Type* System::find_type(cstring name)
	{
		for(Type* type : m_types)
			if(strcmp(type->m_name, name) == 0)
				return type;
		return nullptr;
	}

	Function* System::find_function(cstring name)
	{
		for(Function* function : m_functions)
			if(strcmp(function->m_name, name) == 0)
				return function;
		return nullptr;
	}

	Function* System::find_function(cstring nemespace, cstring name)
	{
		for(Function* function : m_functions)
			if(function->m_namespace->m_name == string(nemespace) && function->m_name == string(name))
				return function;
		return nullptr;
	}

	Function& System::function(FunctionPointer identity)
	{
		for(Function* func : m_functions)
			if(func->m_identity == identity)
			{
				return *func;
			}
		printf("ERROR: retrieving function\n");
		return *m_functions[0];
	}

	vector<cstring> System::meta_symbols()
	{
		vector<cstring> symbols;

		for(Function* function : System::instance().m_functions)
			symbols.push_back(function->m_name);

		for(Type* type : System::instance().m_types)
			symbols.push_back(type->m_name);

		return symbols;
	}

	void System::dump_meta_info()
	{
		for(Function* function : System::instance().m_functions)
			printf("INFO: Meta function %s\n", function->m_name);

		for(Type* type : System::instance().m_types)
		{
			printf("INFO: Meta type %s\n", type->m_name);

			if(!g_class[type->m_id])
				continue;

			for(Member& member : cls(*type).m_members)
				if(member.m_object_type == type)
					printf("      Meta member %s::%s\n", member.m_object_type->m_name, member.m_name);
			for(Method& method : cls(*type).m_methods)
				if(method.m_object_type == type)
					printf("      Meta method %s::%s\n", method.m_object_type->m_name, method.m_name);
			for(Static& static_member : cls(*type).m_static_members)
				printf("      Meta static member %s::%s\n", static_member.m_value.m_type->m_name, static_member.m_name);
		}
	}

	void System::dump_memory_usage()
	{
		printf("LOG: memory usage\n");
		printf("-----------------\n");
		for(Type* type : m_types)
		{
			if(type->m_debug_count == 0)
				continue;
			printf("Type : %s\n", type->m_name);
			printf(" ----- Objects : %zu\n", type->m_debug_count);
			printf(" ----- Memory : %zu\n", type->m_debug_memory);
		}
	}

	bool compare(const vector<cstring>& first, const vector<cstring>& second)
	{
		if(first.size() != second.size())
			return false;
		for(size_t i = 0; i < first.size(); ++i)
			if(strcmp(first[i], second[i]) != 0)
				return false;
		return true;
	}

	Namespace& System::get_namespace(vector<cstring> path)
	{
		for(Namespace& location : m_namespaces)
			if(compare(location.m_path, path))
			{
				return location;
			}

		Namespace* parent = nullptr;
		cstring name = "";

		if(!path.empty())
		{
			name = pop(path);
			parent = &namspc(path);
		}

		m_namespaces.push_back(Namespace{ name, parent });
		return m_namespaces.back();
	}
}

#ifdef MUD_MODULES
module mud.refl;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_REFL_EXPORT Type& type<mud::TypeClass>() { static Type ty("mud::TypeClass", sizeof(mud::TypeClass)); return ty; }
    
    template <> MUD_REFL_EXPORT Type& type<mud::Call>() { static Type ty("Call", sizeof(mud::Call)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Callable>() { static Type ty("Callable", sizeof(mud::Callable)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Class>() { static Type ty("Class", sizeof(mud::Class)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Convert>() { static Type ty("Convert", sizeof(mud::Convert)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Creator>() { static Type ty("Creator", sizeof(mud::Creator)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Enum>() { static Type ty("Enum", sizeof(mud::Enum)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Member>() { static Type ty("Member", sizeof(mud::Member)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Meta>() { static Type ty("Meta", sizeof(mud::Meta)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Module>() { static Type ty("Module", sizeof(mud::Module)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Namespace>() { static Type ty("Namespace", sizeof(mud::Namespace)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Operator>() { static Type ty("Operator", sizeof(mud::Operator)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Param>() { static Type ty("Param", sizeof(mud::Param)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::QualType>() { static Type ty("QualType", sizeof(mud::QualType)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Signature>() { static Type ty("Signature", sizeof(mud::Signature)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Static>() { static Type ty("Static", sizeof(mud::Static)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::System>() { static Type ty("System", sizeof(mud::System)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Constructor>() { static Type ty("Constructor", type<mud::Callable>(), sizeof(mud::Constructor)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::CopyConstructor>() { static Type ty("CopyConstructor", type<mud::Callable>(), sizeof(mud::CopyConstructor)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Destructor>() { static Type ty("Destructor", type<mud::Callable>(), sizeof(mud::Destructor)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Function>() { static Type ty("Function", type<mud::Callable>(), sizeof(mud::Function)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Injector>() { static Type ty("Injector", type<mud::Call>(), sizeof(mud::Injector)); return ty; }
    template <> MUD_REFL_EXPORT Type& type<mud::Method>() { static Type ty("Method", type<mud::Callable>(), sizeof(mud::Method)); return ty; }
}
