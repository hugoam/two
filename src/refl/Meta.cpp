//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.refl;
#else
#include <refl/Meta.h>
#include <refl/MetaDecl.h>
#include <refl/Class.h>
#include <refl/Enum.h>
#include <refl/Convert.h>
#include <type/Types.h>
#include <type/Any.h>
#include <infra/StringConvert.h>
#include <refl/Injector.h>
//#include <ecs/Proto.h>
//#include <ecs/Entity.h>
#include <infra/Vector.h>
//#include <srlz/Serial.h>
#endif

namespace mud
{
	std::vector<Meta*> g_meta = std::vector<Meta*>(c_max_types);
	std::vector<Class*> g_class = std::vector<Class*>(c_max_types);
	std::vector<Enum*> g_enu = std::vector<Enum*>(c_max_types);
	std::vector<Convert*> g_convert = std::vector<Convert*>(c_max_types);

	template <>
	void init_string<void>() {}

	template <>
	void init_string<cstring>() {}

	template <>
	void init_assign<cstring>() {}

	bool is_string(Type& type)
	{
		return type.is<string>() || type.is<cstring>() || type.is<string>();
	}

	string get_string(Member& member, Ref value)
	{
		if(member.m_type->is<cstring>())
			return val<cstring>(member.get(value));
		else if(member.m_type->is<string>())
			return val<string>(member.get(value)).c_str();
		else
			return val<string>(member.get(value));
	}

	Meta::Meta(Type& type, Namespace* location, cstring name, size_t size, TypeClass type_class)
		: m_type(&type)
		, m_namespace(location)
		, m_name(name)
		, m_size(size)
		, m_type_class(type_class)
	{
		type.m_name = m_name;
		g_meta[type.m_id] = this;
	}

	Enum::Enum(Type& type, bool scoped, const std::vector<cstring>& names, const std::vector<uint32_t>& indices, const std::vector<Var>& values)
		: m_type(type)
		, m_scoped(scoped)
		, m_names(names)
		, m_indices(indices)
		, m_values(values)
	{
		g_enu[type.m_id] = this;

		for(size_t i = 0; i < m_names.size(); ++i)
		{
			size_t index = m_indices[i];
			m_map.resize(index + 1);
			m_map[index] = m_names[i];
		}
	}

	uint32_t Enum::value(cstring name)
	{
		for(uint32_t i = 0; i < uint32_t(m_names.size()); ++i)
			if(strcmp(name, m_names[i]) == 0)
				return m_indices[i];
		printf("WARNING: fetching unknown Enum %s value : %s\n", m_type.m_name, name);
		return m_indices[0];
	}

	uint32_t Enum::index(cstring name)
	{
		for(uint32_t i = 0; i < uint32_t(m_names.size()); ++i)
			if(strcmp(name, m_names[i]) == 0)
				return i;
		printf("WARNING: fetching unknown Enum %s index : %s\n", m_type.m_name, name);
		return 0;
	}

	Class::Class(Type& type)
		: m_type(&type)
		, m_meta(&meta(type))
		, m_root(&type)
	{
		g_class[type.m_id] = this;
	}

	Class::Class(Type& type, std::vector<Type*> bases, std::vector<size_t> bases_offsets, std::vector<Constructor> constructors, std::vector<CopyConstructor> copy_constructors,
				 std::vector<Member> members, std::vector<Method> methods, std::vector<Static> static_members)
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

	void Class::inherit(std::vector<Type*> types)
	{
		for(Type* type : types)
			if(g_class[type->m_id])
			{
				vector_prepend(m_members, cls(*type).m_members);
				vector_prepend(m_methods, cls(*type).m_methods);
			}
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
		return vector_has_pred(m_members, [&](const Member& member) { return strcmp(member.m_name, name) == 0; });
	}

	bool Class::has_method(cstring name)
	{
		return vector_has_pred(m_methods, [&](const Method& method) { return strcmp(method.m_name, name) == 0; });
	}

	Member& Class::member(Address address)
	{
		for(Member& look : m_members)
			if(look.m_address == address)
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

	bool Class::has_member(Address address)
	{
		return vector_has_pred(m_members, [&](const Member& look) { return look.m_address == address; });
	}

	bool Class::has_method(Address address)
	{
		return vector_has_pred(m_methods, [&](const Method& look) { return look.m_address == address; });
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
			size_t min_args = constructor.m_arguments.size() - 1 - constructor.m_num_defaults;
			size_t max_args = constructor.m_arguments.size() - 1;
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
		else if(cls(dest).m_copy_constructors.size() > 0)
			cls(dest).m_copy_constructors[0].m_call(dest, source);
	}

	void assign(Ref first, Ref second)
	{
		if(second.m_type->is(*first.m_type))
			meta(first).m_copy_assign(first, second);
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
		this->default_converter<float, ulong2>();
		this->default_converter<double, int>();
		this->default_converter<double, ushort>();
		this->default_converter<double, uint>();
		this->default_converter<double, ulong>();
		this->default_converter<double, ulong2>();
		this->default_converter<int, ushort>();
		this->default_converter<int, uint>();
		this->default_converter<int, ulong>();
		this->default_converter<int, ulong2>();
		this->default_converter<ushort, uint>();
		this->default_converter<ushort, ulong>();
		this->default_converter<ushort, ulong2>();
		this->default_converter<uint, ulong>();
		this->default_converter<uint, ulong2>();
		this->default_converter<ulong, ulong2>();
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
