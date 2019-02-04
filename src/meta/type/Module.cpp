#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.type;
#else
#include <stddef.h>
#include <infra/ToString.h>
#include <type/Vector.h>
#include <type/Any.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/type/Convert.h>
#endif

#include <type/Api.h>

using namespace mud;

size_t vector_mud_Ref___size(void* vec) { return (*static_cast<vector<mud::Ref>*>(vec)).size(); }
void* vector_mud_Ref___at(void* vec, size_t i) { return &(*static_cast<vector<mud::Ref>*>(vec))[i]; }
void vector_mud_Ref___add(void* vec, void* value) { (*static_cast<vector<mud::Ref>*>(vec)).push_back(*static_cast<mud::Ref*>(value)); }
void vector_mud_Ref___remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<mud::Ref>*>(vec)), *static_cast<mud::Ref*>(value)); }
void mud_Index_indexer(void* object, array<void*> args, void*& result) { result = &(*static_cast<mud::Index*>(object)).indexer(*static_cast<mud::Type*>(args[0])); }
void* mud_Indexer__get_type(void* object) { return &(*static_cast<mud::Indexer*>(object)).m_type; }
void mud_Ref__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Ref*>(ref))) mud::Ref(  ); }
void mud_Ref__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Ref*>(ref))) mud::Ref( static_cast<void**>(args[0]), *static_cast<mud::Type*>(args[1]) ); }
void mud_Ref__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Ref*>(ref))) mud::Ref((*static_cast<mud::Ref*>(other))); }
void mud_indexed_0(array<void*> args, void*& result) { (*static_cast<mud::Ref*>(result)) = mud::indexed(*static_cast<mud::Type*>(args[0]), *static_cast<uint32_t*>(args[1])); }

namespace mud
{
	void mud_type_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	{
		Type& t = type<bool>();
		static Meta meta = { t, &namspc({}), "bool", sizeof(bool), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(bool());
		static Convert convert = { [](void* val, string& str) { to_string<bool>((*static_cast<bool*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<bool>(str, (*static_cast<bool*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<char>();
		static Meta meta = { t, &namspc({}), "char", sizeof(char), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(char());
		static Convert convert = { [](void* val, string& str) { to_string<char>((*static_cast<char*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<char>(str, (*static_cast<char*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<const char*>();
		static Meta meta = { t, &namspc({}), "const char*", sizeof(const char*), TypeClass::BaseType };
	}
	{
		Type& t = type<double>();
		static Meta meta = { t, &namspc({}), "double", sizeof(double), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(double());
		static Convert convert = { [](void* val, string& str) { to_string<double>((*static_cast<double*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<double>(str, (*static_cast<double*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<float>();
		static Meta meta = { t, &namspc({}), "float", sizeof(float), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(float());
		static Convert convert = { [](void* val, string& str) { to_string<float>((*static_cast<float*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<float>(str, (*static_cast<float*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<int>();
		static Meta meta = { t, &namspc({}), "int", sizeof(int), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(int());
		static Convert convert = { [](void* val, string& str) { to_string<int>((*static_cast<int*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<int>(str, (*static_cast<int*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<long>();
		static Meta meta = { t, &namspc({}), "long", sizeof(long), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(long());
		static Convert convert = { [](void* val, string& str) { to_string<long>((*static_cast<long*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<long>(str, (*static_cast<long*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<long long>();
		static Meta meta = { t, &namspc({}), "long long", sizeof(long long), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(llong());
		static Convert convert = { [](void* val, string& str) { to_string<long long>((*static_cast<long long*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<long long>(str, (*static_cast<long long*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<short>();
		static Meta meta = { t, &namspc({}), "short", sizeof(short), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(short());
		static Convert convert = { [](void* val, string& str) { to_string<short>((*static_cast<short*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<short>(str, (*static_cast<short*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<string>();
		static Meta meta = { t, &namspc({}), "string", sizeof(string), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(string());
		static Convert convert = { [](void* val, string& str) { to_string<string>((*static_cast<string*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<string>(str, (*static_cast<string*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<unsigned char>();
		static Meta meta = { t, &namspc({}), "unsigned char", sizeof(unsigned char), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(uchar());
		static Convert convert = { [](void* val, string& str) { to_string<unsigned char>((*static_cast<unsigned char*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<unsigned char>(str, (*static_cast<unsigned char*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<unsigned int>();
		static Meta meta = { t, &namspc({}), "unsigned int", sizeof(unsigned int), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(uint());
		static Convert convert = { [](void* val, string& str) { to_string<unsigned int>((*static_cast<unsigned int*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<unsigned int>(str, (*static_cast<unsigned int*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<unsigned long>();
		static Meta meta = { t, &namspc({}), "unsigned long", sizeof(unsigned long), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(ulong());
		static Convert convert = { [](void* val, string& str) { to_string<unsigned long>((*static_cast<unsigned long*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<unsigned long>(str, (*static_cast<unsigned long*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<unsigned long long>();
		static Meta meta = { t, &namspc({}), "unsigned long long", sizeof(unsigned long long), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(ullong());
		static Convert convert = { [](void* val, string& str) { to_string<unsigned long long>((*static_cast<unsigned long long*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<unsigned long long>(str, (*static_cast<unsigned long long*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<unsigned short>();
		static Meta meta = { t, &namspc({}), "unsigned short", sizeof(unsigned short), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(ushort());
		static Convert convert = { [](void* val, string& str) { to_string<unsigned short>((*static_cast<unsigned short*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<unsigned short>(str, (*static_cast<unsigned short*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<void>();
		static Meta meta = { t, &namspc({}), "void", 0, TypeClass::BaseType };
	}
	{
		Type& t = type<void*>();
		static Meta meta = { t, &namspc({}), "void*", sizeof(void*), TypeClass::BaseType };
	}
	
	// Enums
	
	// Sequences
	{
		Type& t = type<vector<mud::Ref>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Ref>", sizeof(vector<mud::Ref>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Ref>(),
		                             vector_mud_Ref___size,
		                             vector_mud_Ref___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_mud_Ref___add,
		                             vector_mud_Ref___remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// mud::Index
	{
		Type& t = type<mud::Index>();
		static Meta meta = { t, &namspc({ "mud" }), "Index", sizeof(mud::Index), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "indexer", Address(), mud_Index_indexer, { { "type", type<mud::Type>(),  } }, { &type<mud::Indexer>(), QualType::None } }
		};
		// static members
		static Static statics[] = {
			{ t, "me", Ref(&mud::Index::me) }
		};
		static Class cls = { t, {}, {}, {}, {}, {}, methods, statics, };
	}
	// mud::Indexer
	{
		Type& t = type<mud::Indexer>();
		static Meta meta = { t, &namspc({ "mud" }), "Indexer", sizeof(mud::Indexer), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<mud::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_Indexer__get_type },
			{ t, offsetof(mud::Indexer, m_objects), type<vector<mud::Ref>>(), "objects", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::Ref
	{
		Type& t = type<mud::Ref>();
		static Meta meta = { t, &namspc({ "mud" }), "Ref", sizeof(mud::Ref), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Ref__construct_0, {} },
			{ t, mud_Ref__construct_1, { { "value", type<void*>(), Param::Nullable }, { "type", type<mud::Type>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Ref__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Ref, m_type), type<mud::Type>(), "type", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Ref, m_value), type<void*>(), "value", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Type
	{
		Type& t = type<mud::Type>();
		static Meta meta = { t, &namspc({ "mud" }), "Type", sizeof(mud::Type), TypeClass::Object };
		// bases
		// defaults
		static mud::Type* base_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Type, m_id), type<uint32_t>(), "id", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Type, m_size), type<size_t>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Type, m_base), type<mud::Type>(), "base", base_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::Var
	{
		Type& t = type<mud::Var>();
		static Meta meta = { t, &namspc({ "mud" }), "Var", sizeof(mud::Var), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
		m.m_types.push_back(&type<mud::Index>());
		m.m_types.push_back(&type<mud::Indexer>());
		m.m_types.push_back(&type<mud::Ref>());
		m.m_types.push_back(&type<mud::Type>());
		m.m_types.push_back(&type<mud::Var>());
		m.m_types.push_back(&type<bool>());
		m.m_types.push_back(&type<char>());
		m.m_types.push_back(&type<const char*>());
		m.m_types.push_back(&type<double>());
		m.m_types.push_back(&type<float>());
		m.m_types.push_back(&type<int>());
		m.m_types.push_back(&type<long>());
		m.m_types.push_back(&type<long long>());
		m.m_types.push_back(&type<short>());
		m.m_types.push_back(&type<string>());
		m.m_types.push_back(&type<unsigned char>());
		m.m_types.push_back(&type<unsigned int>());
		m.m_types.push_back(&type<unsigned long>());
		m.m_types.push_back(&type<unsigned long long>());
		m.m_types.push_back(&type<unsigned short>());
		m.m_types.push_back(&type<vector<mud::Ref>>());
		m.m_types.push_back(&type<void>());
		m.m_types.push_back(&type<void*>());
		{
			static Function f = { &namspc({ "mud" }), "indexed", nullptr, mud_indexed_0, { { "type", type<mud::Type>(),  }, { "id", type<uint32_t>(),  } }, { &type<mud::Ref>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_type::mud_type()
		: Module("mud::type", { &mud_infra::m() })
	{
		// setup reflection meta data
		mud_type_meta(*this);
	}
}

#ifdef MUD_TYPE_MODULE
extern "C"
Module& getModule()
{
		return mud_type::m();
}
#endif
