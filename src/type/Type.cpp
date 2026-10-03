//  Copyright (c) 2023 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

module;
#include <infra/Cpp20.h>
module two.type;

namespace two
{
	bool Address::operator==(const Address& other) const
	{
		return memcmp(value, other.value, sizeof(value)) == 0;
	}

	Index Index::me;

	static uint32_t s_type_index = 2;

	Type::Type(int)
		: m_id(1)
		, m_name("Type")
	{}

	Type::Type()
		: m_id(0)
		, m_name("")
	{}

	Type::Type(const char* name, size_t size)
		: m_id(s_type_index++)
		, m_name(name)
		, m_size(size)
	{
		//printf("[debug] Type %s %i\n", name, int(m_id));

		if(strcmp(name, "INVALID") == 0)
			warn("Invalid type created, this means an lref was created for a type which isn't exported\n");
	}
	
	Type::Type(const char* name, Type& base, size_t size)
		: Type(name, size)
	{
		m_base = &base;
	}

	Type::~Type()
	{}

	bool Type::is(const Type& type) const
	{
		if(&type == this)
			return true;
		else if(m_base)
			return m_base->is(type);
		else
			return false;
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

	void TypeConverter::convert(Ref input, Var& result)
	{
		DoubleDispatch::dispatch(input, result);
	}
}
