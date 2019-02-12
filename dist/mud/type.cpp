#include <mud/infra.h>
#include <mud/type.h>



#ifdef MUD_MODULES
module mud.obj;
#else
#endif

namespace mud
{
	AnyHandler AnyHandler::none;
}


#ifdef MUD_MODULES
module mud.type;
#else
#endif

namespace mud
{
	vector<Prototype*> g_prototypes = vector<Prototype*>(c_max_types);

	Prototype::Prototype(Type& type, vector<Type*> parts)
		: m_type(type)
		, m_hash_parts(c_max_types)
	{
		g_prototypes[type.m_id] = this;
		for(Type* part : parts)
			this->add_part(*part);
		this->add_part(m_type);
	}

	void Prototype::add_part(Type& type)
	{
		Type* base = &type;
		while(base)
		{
			m_hash_parts[base->m_id] = m_parts.size();
			base = base->m_base;
		}
		m_parts.push_back(&type);
	}
}

#ifndef MUD_CPP_20
#include <cstring>
#include <cstdio>
#endif

#ifdef MUD_MODULES
module mud.obj;
#else
#include <stl/vector.h>
#include <stl/string.h>
//#include <ecs/Proto.h>
#endif

namespace mud
{
	bool Address::operator==(const Address& other) const
	{
		return strncmp(value, other.value, 16) == 0;
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
		//printf("DEBUG: Type %s %i\n", name, int(m_id));

		if(strcmp(name, "INVALID") == 0)
			printf("WARNING: Invalid type created, this means an lref was created for a type which isn't exported\n");
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
}
#ifndef USE_STL
#ifdef MUD_MODULES
module mud.math;
#else
#include <stl/vector.hpp>
#include <stl/unordered_set.hpp>
#include <stl/unordered_map.hpp>
#endif

namespace stl
{
	using namespace mud;
	template class MUD_TYPE_EXPORT vector<string>;
	template class MUD_TYPE_EXPORT vector<Type*>;
	template class MUD_TYPE_EXPORT vector<Prototype*>;
	template class MUD_TYPE_EXPORT buf<Var>;
	template class MUD_TYPE_EXPORT buffer<Var>;
	template class MUD_TYPE_EXPORT vector<Var>;
	template class MUD_TYPE_EXPORT vector<Ref>;
	template class MUD_TYPE_EXPORT vector<void(*)(Ref, Ref)>;
	template class MUD_TYPE_EXPORT vector<vector<void(*)(Ref, Ref)>>;
	template class MUD_TYPE_EXPORT vector<unique<Indexer>>;
	//template class MUD_TYPE_EXPORT unordered_set<string>;
	template class MUD_TYPE_EXPORT unordered_map<string, string>;
}
#endif

#ifdef MUD_MODULES
module mud.type;
#else
#endif

namespace mud
{
    // Exported types
    template <> MUD_TYPE_EXPORT Type& type<bool>() { static Type ty("bool", sizeof(bool)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<char>() { static Type ty("char", sizeof(char)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<const char*>() { static Type ty("const char*", sizeof(const char*)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<double>() { static Type ty("double", sizeof(double)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<float>() { static Type ty("float", sizeof(float)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<int>() { static Type ty("int", sizeof(int)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<ldouble>() { static Type ty("ldouble", sizeof(ldouble)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<llong>() { static Type ty("llong", sizeof(llong)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<long>() { static Type ty("long", sizeof(long)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<schar>() { static Type ty("schar", sizeof(schar)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<short>() { static Type ty("short", sizeof(short)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<stl::string>() { static Type ty("stl::string", sizeof(stl::string)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<uchar>() { static Type ty("uchar", sizeof(uchar)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<uint>() { static Type ty("uint", sizeof(uint)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<ullong>() { static Type ty("ullong", sizeof(ullong)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<ulong>() { static Type ty("ulong", sizeof(ulong)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<ushort>() { static Type ty("ushort", sizeof(ushort)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<void>() { static Type ty("void"); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<void*>() { static Type ty("void*", sizeof(void*)); return ty; }
    
    template <> MUD_TYPE_EXPORT Type& type<stl::vector<mud::Ref>>() { static Type ty("vector<mud::Ref>", sizeof(stl::vector<mud::Ref>)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<stl::vector<stl::string>>() { static Type ty("vector<stl::string>", sizeof(stl::vector<stl::string>)); return ty; }
    
    template <> MUD_TYPE_EXPORT Type& type<mud::Index>() { static Type ty("Index", sizeof(mud::Index)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<mud::Indexer>() { static Type ty("Indexer", sizeof(mud::Indexer)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<mud::Prototype>() { static Type ty("Prototype", sizeof(mud::Prototype)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<mud::Ref>() { static Type ty("Ref", sizeof(mud::Ref)); return ty; }
    template <> MUD_TYPE_EXPORT Type& type<mud::Var>() { static Type ty("Var", sizeof(mud::Var)); return ty; }
}
