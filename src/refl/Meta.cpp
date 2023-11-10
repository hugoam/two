//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.refl;
#else
#include <stl/algorithm.h>
#include <infra/ToString.h>
#include <infra/Log.h>
#include <type/Types.h>
#include <type/Any.h>
#include <refl/Meta.h>
#include <refl/MetaDecl.h>
#include <refl/Class.h>
#include <refl/Enum.h>
#include <refl/Convert.h>
#include <refl/Injector.h>
#endif

#include <cstring>
#include <cstdio>

namespace two
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
		return type.is<string>() || type.is<cstring>();
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

	Enum::Enum(Type& type, bool scoped, span<cstring> names, span<uint32_t> values, span<void*> vars)
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
				warn("enum value %s::%s above 2^16, something is fishy\n", type.m_name, m_names[i]);
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
		warn("fetching unknown Enum %s value : %s", m_type.m_name, name);
		return m_values[0];
	}

	uint32_t Enum::value(Ref value)
	{
		const size_t size = m_type.m_size;
		for(uint32_t i = 0; i < uint32_t(m_vars.size()); ++i)
			if(memcmp(value.m_value, m_vars[i], size) == 0)
				return m_values[i];
		warn("fetching unknown Enum %s index : %s", m_type.m_name, to_string(value).c_str());
		return 0;
	}

	uint32_t Enum::index(cstring name)
	{
		for(uint32_t i = 0; i < uint32_t(m_names.size()); ++i)
			if(strcmp(name, m_names[i]) == 0)
				return i;
		warn("fetching unknown Enum %s index : %s", m_type.m_name, name);
		return 0;
	}

	uint32_t Enum::index(Ref value)
	{
		const size_t size = m_type.m_size;
		for(uint32_t i = 0; i < uint32_t(m_vars.size()); ++i)
			if(memcmp(value.m_value, m_vars[i], size) == 0)
				return i;
		warn("fetching unknown Enum %s index : %s", m_type.m_name, to_string(value).c_str());
		return 0;
	}

	Class::Class(Type& type)
		: m_type(&type)
		, m_meta(&meta(type))
		, m_root(&type)
	{
		g_class[type.m_id] = this;
	}

	Class::Class(Type& type, span<Type*> bases, span<size_t> bases_offsets, span<Constructor> constructors, span<CopyConstructor> copy_constructors,
				 span<Member> members, span<Method> methods, span<Static> static_members)
		: m_type(&type)
		, m_meta(&meta(type))
		, m_bases(bases)
		, m_bases_offsets(bases_offsets)
		, m_constructors(constructors)
		, m_copy_constructors(copy_constructors)
		, m_members(members)
		, m_methods(methods)
		, m_static_members(static_members)
		, m_root(&type)
	{
		g_class[type.m_id] = this;
	}

	Class::~Class()
	{}

	void Class::inherit(span<Type*> types)
	{
		//for(Type* type : types)
		//	if(g_class[type->m_id])
		//	{
		//		prepend(m_members, cls(*type).m_members);
		//		prepend(m_methods, cls(*type).m_methods);
		//	}
	}

	void Class::setup_class()
	{
		this->inherit(m_bases);

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

	Ref Class::upcast(Ref object, const Type& base)
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

	Ref Class::downcast(Ref object, const Type& base)
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
		error("retrieving member");
		return m_members[0];
	}

	Method& Class::method(Address address)
	{
		for(Method& look : m_methods)
			if(look.m_address == address)
				return look;
		error("retrieving method");
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

	bool Class::is(const Type& component)
	{
		return find(m_components, [&](Member* member) { return member->m_type->is(component); }) != nullptr;
	}

	Ref Class::as(Ref object, const Type& component)
	{
		Member* member = *find(m_components, [&](Member* member) { return member->m_type->is(component); });
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
			memcpy(dest.m_value, source.m_value, type(dest).m_size);
		else // if(cls(dest).m_copy_constructors.size() > 0)
			;//meta(dest).copy_construct(dest, source);
	}

	void assign(Ref dest, Ref source)
	{
		if(!source.m_type->is(*dest.m_type))
		{
			warn("can't assign values of unrelated types\n");
			return;
		}

		if(is_basic(*dest.m_type))
			memcpy(dest.m_value, source.m_value, meta(dest).m_size);
		else
			meta(dest).copy_assign(dest, source);
	}

	void assign_pointer(Ref first, Ref second)
	{
		UNUSED(first); UNUSED(second);
	}

	string to_name(const Type& type, Ref value)
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

	bool TypeConverter::check(const Type& input, const Type& output)
	{
		return DoubleDispatch::check(input, output);
	}

	bool TypeConverter::check(Ref input, const Type& output)
	{
		return DoubleDispatch::check(*input.m_type, output);
	}

	Var TypeConverter::convert(Ref input, const Type& output)
	{
		Var result = meta(output).m_empty_var;
		DoubleDispatch::dispatch(input, result);
		return result;
	}

	void TypeConverter::convert(Ref input, const Type& output, Var& result)
	{
		if(result.none() || !type(result).is(output))
			result = meta(output).m_empty_var;
		DoubleDispatch::dispatch(input, result);
	}

	bool is_related(const Type& input, const Type& output)
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

	bool convert(Var& source, const Type& output, Var& dest, bool ref)
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

	bool convert(Ref input, const Type& output, Var& result)
	{
		Var inputvar = input;
		return convert(inputvar, output, result);
	}

	Var convert(Ref input, const Type& output)
	{
		Var result;
		convert(input, output, result);
		return result;
	}

	bool can_convert(const Type& input, const Type& output)
	{
		return input.is(output) || is_related(input, output) || TypeConverter::me().check(input, output);
	}

	bool can_convert(Ref input, const Type& output)
	{
		return type(input).is(output) || is_related(type(input), output) || TypeConverter::me().check(input, output);
	}
}
