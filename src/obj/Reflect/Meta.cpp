//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <obj/Cpp20.h>

#ifdef MUD_MODULES
module mud.obj;
#else
#include <obj/Config.h>
#include <obj/Reflect/Meta.h>
#include <obj/Reflect/MetaDecl.h>
#include <obj/Reflect/Class.h>
#include <obj/Reflect/Enum.h>
#include <obj/Reflect/Convert.h>
#include <obj/Types.h>
#include <obj/Any.h>
#include <obj/String/StringConvert.h>
#include <obj/Reflect/Injector.h>
#include <obj/Proto.h>
#include <obj/Complex.h>
#include <obj/Vector.h>
#include <obj/Serial/Serial.h>
#endif

namespace mud
{
	template <>
	void init_string<void>() {}

	template <>
	void init_string<cstring>() {}

	template <>
	void init_assign<cstring>() {}

	bool is_string(Type& type)
	{
		return type.is<string>() || type.is<cstring>() || type.is<strung>();
	}

	string get_string(Member& member, Ref value)
	{
		if(member.m_type->is<cstring>())
			return val<cstring>(member.get(value));
		else if(member.m_type->is<strung>())
			return val<strung>(member.get(value)).c_str();
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
		m_type->m_name = m_name;
		m_type->m_meta = this;
	}

	Enum::Enum(Type& type, bool scoped, const std::vector<cstring>& names, const std::vector<size_t>& indices, const std::vector<Var>& values)
		: m_type(type)
		, m_scoped(scoped)
		, m_names(names)
		, m_indices(indices)
		, m_values(values)
	{
		m_type.m_enum = this;

		for(size_t i = 0; i < m_names.size(); ++i)
		{
			size_t index = m_indices[i];
			m_map.resize(index + 1);
			m_map[index] = m_names[i];
		}
	}

	uint32_t Enum::value(cstring name)
	{
		for(size_t i = 0; i < m_names.size(); ++i)
			if(strcmp(name, m_names[i]) == 0)
				return m_indices[i];
		printf("WARNING: fetching unknown Enum %s value : %s\n", m_type.m_name, name);
		return m_indices[0];
	}

	size_t Enum::index(cstring name)
	{
		for(size_t i = 0; i < m_names.size(); ++i)
			if(strcmp(name, m_names[i]) == 0)
				return i;
		printf("WARNING: fetching unknown Enum %s index : %s\n", m_type.m_name, name);
		return 0;
	}

	Class::Class(Type& type)
		: m_type(&type)
		, m_meta(type.m_meta)
		, m_root(&type)
	{
		m_type->m_class = this;
	}

	Class::Class(Type& type, std::vector<Type*> bases, std::vector<size_t> bases_offsets, std::vector<Constructor> constructors, std::vector<CopyConstructor> copy_constructors,
				 std::vector<Member> members, std::vector<Method> methods, std::vector<Static> static_members)
		: m_type(&type)
		, m_meta(type.m_meta)
		, m_root(&type)
		, m_bases(bases)
		, m_bases_offsets(bases_offsets)
		, m_constructors(constructors)
		, m_copy_constructors(copy_constructors)
		, m_members(members)
		, m_methods(methods)
		, m_static_members(static_members)
	{
		m_type->m_class = this;
	}

	Class::~Class()
	{
		if(m_prototype)
			vector_remove(m_root->m_class->m_prototypes, m_prototype);
	}

	void Class::inherit(std::vector<Type*> types)
	{
		for(Type* type : types)
			if(type->m_meta)
			{
				vector_prepend(m_members, type->m_class->m_members);
				vector_prepend(m_methods, type->m_class->m_methods);
			}
	}

	void Class::setup_class()
	{
		if(m_type->m_kind == TypeKind::Prototype)
		{
			m_prototype = &as<Prototype>(*m_type);
			m_root->m_class->m_prototypes.push_back(m_prototype);
			m_components = m_prototype->m_parts;

			for(Type* type : m_prototype->m_parts)
			{
				for(Member& member : type->m_class->m_members)
					m_deep_members.push_back(&member);
				for(Method& method : type->m_class->m_methods)
					m_deep_methods.push_back(&method);
			}
		}

		this->inherit(m_bases);

		for(size_t i = 0; i < m_members.size(); ++i)
			m_members[i].m_index = i;

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

			m_field_names.push_back(member.m_name);
			m_field_values.push_back(member.m_default_value);
		}
	}

	Ref Class::upcast(Ref object, Type& base)
	{
		if(!object) return object;
		for(size_t i = 0; i < m_bases.size(); ++i)
			if(m_bases[i] == &base)
			{
				return Ref{ static_cast<char*>(object.m_value) + m_bases_offsets[i], base };
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

	bool Class::is_related(Ref object, Type& target)
	{
		bool result = (m_prototype && &target == m_root)
					|| ((m_meta->m_type_class == TypeClass::Complex || m_prototype) && this->get_stem(object).has_part(target));
		return result;
	}

	Complex& Class::get_stem(Ref object)
	{
		if(m_prototype)
			return val<Construct>(object).m_stem;
		else
			return val<Complex>(object);
	}

	Ref Class::get_related(Ref object, Type& target)
	{
		if(&target == m_root)
			return &this->get_stem(object);
		else 
			return this->get_stem(object).partref(target);
	}

	bool compare(Ref first, Ref second)
	{
		UNUSED(first); UNUSED(second);
		return false;
	}

	void copy_construct(Ref dest, Ref source)
	{
		if(is_basic(dest.type()))
			memcpy(dest.m_value, source.m_value, meta(dest).m_size);
		else if(cls(dest).m_copy_constructors.size() > 0)
			cls(dest).m_copy_constructors[0].m_call(dest, source);
	}

	void assign(Ref first, Ref second)
	{
		if(second.type().is(first.type()))
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
		if(type.m_meta->m_type_class == TypeClass::Complex)
		{
			Construct& construct = *val<Complex>(value).m_construct;
			return to_name(construct.m_prototype, &construct);
		}	
		
		string name;
		if(is_basic(type))
			name = to_string(value);
		else if(!value)
			name = "null";
		else if(type.m_class->m_name_member)
			name = get_string(*type.m_class->m_name_member, value);
		else if(type.m_class->m_id_member)
			name = string(type.m_name) + " : " + to_string(type.m_class->m_id_member->get(value));
		else
			name = string(type.m_name); // + " : " + to_string(value.m_value); // @todo void* to string fails with vs2017 + modules
		return name;
	}

	TypeConverter::TypeConverter()
		: DoubleDispatch()
	{
		this->default_converter<float, int>();
		this->default_converter<float, uint32_t>();
		this->default_converter<float, size_t>();
		this->default_converter<double, int>();
		this->default_converter<double, uint32_t>();
		this->default_converter<double, size_t>();
		this->default_converter<double, float>();
		this->default_converter<int, uint32_t>();
		this->default_converter<int, size_t>();
		this->default_converter<uint32_t, size_t>();
	}

	bool TypeConverter::check(Ref input, Type& output)
	{
		return DoubleDispatch::check(*input.m_type, output);
	}

	Var TypeConverter::convert(Ref input, Type& output)
	{
		Var result = output.m_meta->m_empty_var();
		DoubleDispatch::dispatch(input, result);
		return result;
	}

	void TypeConverter::convert(Ref input, Type& output, Var& result)
	{
		if(result.none() || !result.type().is(output))
			result = output.m_meta->m_empty_var();
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
		else if(value.type().is(output))
			assign(source, dest, ref);
		else if(is_class(value.type()) && cls(value).is_related(value, output))
			dest = cls(value).get_related(value, output);
		else if(TypeConverter::me().check(value, output))
			TypeConverter::me().convert(value, output, dest);
		else
		{
			dest.clear();
			return false;
		}

		return true;
	}

	Var convert(Ref input, Type& output)
	{
		return TypeConverter::me().convert(input, output);
	}

	void convert(Ref input, Type& output, Var& result)
	{
		return TypeConverter::me().convert(input, output, result);
	}

	bool can_convert(Type& input, Type& output)
	{
		return input.is(output) || is_related(input, output) || TypeConverter::me().check(input, output);
	}

	bool can_convert(Ref input, Type& output)
	{
		return input.type().is(output) || is_related(input.type(), output) || TypeConverter::me().check(input, output);
	}
}
