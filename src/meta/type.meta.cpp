#ifdef TWO_MODULES
module;
#include <infra/Cpp20.h>
module two.type.meta;
#else
#include <cstddef>
#include <stl/new.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/type.conv.h>
#include <type/Api.h>
#endif

using namespace two;

size_t stl_vector_stl_string__size(void* vec) { return (*static_cast<stl::vector<stl::string>*>(vec)).size(); }
void* stl_vector_stl_string__at(void* vec, size_t i) { return &(*static_cast<stl::vector<stl::string>*>(vec))[i]; }
void stl_vector_stl_string__push(void* vec) { (*static_cast<stl::vector<stl::string>*>(vec)).emplace_back(); }
void stl_vector_stl_string__add(void* vec, void* value) { (*static_cast<stl::vector<stl::string>*>(vec)).push_back(*static_cast<stl::string*>(value)); }
void stl_vector_stl_string__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<stl::string>*>(vec)), *static_cast<stl::string*>(value)); }
size_t stl_vector_two_Ref__size(void* vec) { return (*static_cast<stl::vector<two::Ref>*>(vec)).size(); }
void* stl_vector_two_Ref__at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Ref>*>(vec))[i]; }
void stl_vector_two_Ref__push(void* vec) { (*static_cast<stl::vector<two::Ref>*>(vec)).emplace_back(); }
void stl_vector_two_Ref__add(void* vec, void* value) { (*static_cast<stl::vector<two::Ref>*>(vec)).push_back(*static_cast<two::Ref*>(value)); }
void stl_vector_two_Ref__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Ref>*>(vec)), *static_cast<two::Ref*>(value)); }
void two_Ref__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Ref(  ); }
void two_Ref__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Ref( static_cast<void**>(args[0]), *static_cast<two::Type*>(args[1]) ); }
void two_Ref__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Ref((*static_cast<two::Ref*>(other))); }
void two_Index_indexer(void* object, span<void*> args, void*& result) { result = &(*static_cast<two::Index*>(object)).indexer(*static_cast<two::Type*>(args[0])); }
void two_indexed_0(span<void*> args, void*& result) { (*static_cast<two::Ref*>(result)) = two::indexed(*static_cast<two::Type*>(args[0]), *static_cast<uint32_t*>(args[1])); }

namespace two
{
	void two_type_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	{
		Type& t = type<void*>();
		static Meta meta = { t, &namspc({}), "void*", sizeof(void*), TypeClass::BaseType };
	}
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
		Type& t = type<schar>();
		static Meta meta = { t, &namspc({}), "schar", sizeof(schar), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(schar());
		static Convert convert = { [](void* val, string& str) { to_string<schar>((*static_cast<schar*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<schar>(str, (*static_cast<schar*>(val))); } };
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
		Type& t = type<uchar>();
		static Meta meta = { t, &namspc({}), "uchar", sizeof(uchar), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(uchar());
		static Convert convert = { [](void* val, string& str) { to_string<uchar>((*static_cast<uchar*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<uchar>(str, (*static_cast<uchar*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<ushort>();
		static Meta meta = { t, &namspc({}), "ushort", sizeof(ushort), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(ushort());
		static Convert convert = { [](void* val, string& str) { to_string<ushort>((*static_cast<ushort*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<ushort>(str, (*static_cast<ushort*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<uint>();
		static Meta meta = { t, &namspc({}), "uint", sizeof(uint), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(uint());
		static Convert convert = { [](void* val, string& str) { to_string<uint>((*static_cast<uint*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<uint>(str, (*static_cast<uint*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<ulong>();
		static Meta meta = { t, &namspc({}), "ulong", sizeof(ulong), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(ulong());
		static Convert convert = { [](void* val, string& str) { to_string<ulong>((*static_cast<ulong*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<ulong>(str, (*static_cast<ulong*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<ullong>();
		static Meta meta = { t, &namspc({}), "ullong", sizeof(ullong), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(ullong());
		static Convert convert = { [](void* val, string& str) { to_string<ullong>((*static_cast<ullong*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<ullong>(str, (*static_cast<ullong*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<llong>();
		static Meta meta = { t, &namspc({}), "llong", sizeof(llong), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(llong());
		static Convert convert = { [](void* val, string& str) { to_string<llong>((*static_cast<llong*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<llong>(str, (*static_cast<llong*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<ldouble>();
		static Meta meta = { t, &namspc({}), "ldouble", sizeof(ldouble), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(ldouble());
		static Convert convert = { [](void* val, string& str) { to_string<ldouble>((*static_cast<ldouble*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<ldouble>(str, (*static_cast<ldouble*>(val))); } };
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
		Type& t = type<double>();
		static Meta meta = { t, &namspc({}), "double", sizeof(double), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(double());
		static Convert convert = { [](void* val, string& str) { to_string<double>((*static_cast<double*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<double>(str, (*static_cast<double*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<const char*>();
		static Meta meta = { t, &namspc({}), "const char*", sizeof(const char*), TypeClass::BaseType };
	}
	{
		Type& t = type<stl::string>();
		static Meta meta = { t, &namspc({}), "stl::string", sizeof(stl::string), TypeClass::BaseType };
		g_meta[t.m_id]->m_empty_var = var(stl::string());
		static Convert convert = { [](void* val, string& str) { to_string<stl::string>((*static_cast<stl::string*>(val)), str); }, 
		                           [](const string& str, void* val) { to_value<stl::string>(str, (*static_cast<stl::string*>(val))); } };
		g_convert[t.m_id] = &convert;
	}
	{
		Type& t = type<void>();
		static Meta meta = { t, &namspc({}), "void", 0, TypeClass::BaseType };
	}
	
	// Enums
	
	// Sequences
	{
		Type& t = type<stl::vector<stl::string>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<stl::string>", sizeof(stl::vector<stl::string>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<stl::string>(),
		                             stl_vector_stl_string__size,
		                             stl_vector_stl_string__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_stl_string__push,
		                             stl_vector_stl_string__add,
		                             stl_vector_stl_string__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::Ref>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Ref>", sizeof(stl::vector<two::Ref>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Ref>(),
		                             stl_vector_two_Ref__size,
		                             stl_vector_two_Ref__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Ref__push,
		                             stl_vector_two_Ref__add,
		                             stl_vector_two_Ref__remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// two::Type
	{
		Type& t = type<two::Type>();
		static Meta meta = { t, &namspc({ "two" }), "Type", sizeof(two::Type), TypeClass::Object };
		// bases
		// defaults
		static two::Type* base_default = nullptr;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Type, m_id), type<uint32_t>(), "id", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Type, m_name), type<const char*>(), "name", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Type, m_size), type<size_t>(), "size", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Type, m_base), type<two::Type>(), "base", base_default, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::Ref
	{
		Type& t = type<two::Ref>();
		static Meta meta = { t, &namspc({ "two" }), "Ref", sizeof(two::Ref), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Ref__construct_0, {} },
			{ t, two_Ref__construct_1, { { "value", type<void*>(), Param::Nullable }, { "type", type<two::Type>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Ref__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Ref, m_type), type<two::Type>(), "type", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Ref, m_value), type<void*>(), "value", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Var
	{
		Type& t = type<two::Var>();
		static Meta meta = { t, &namspc({ "two" }), "Var", sizeof(two::Var), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Indexer
	{
		Type& t = type<two::Indexer>();
		static Meta meta = { t, &namspc({ "two" }), "Indexer", sizeof(two::Indexer), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Indexer, m_type), type<two::Type>(), "type", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Indexer, m_objects), type<stl::vector<two::Ref>>(), "objects", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::Index
	{
		Type& t = type<two::Index>();
		static Meta meta = { t, &namspc({ "two" }), "Index", sizeof(two::Index), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "indexer", Address(), two_Index_indexer, { { "type", type<two::Type>(),  } }, { &type<two::Indexer>(), QualType::None } }
		};
		// static members
		static Static statics[] = {
			{ t, "me", Ref(&two::Index::me) }
		};
		static Class cls = { t, {}, {}, {}, {}, {}, methods, statics, };
	}
	// two::Prototype
	{
		Type& t = type<two::Prototype>();
		static Meta meta = { t, &namspc({ "two" }), "Prototype", sizeof(two::Prototype), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<void*>());
		m.m_types.push_back(&type<bool>());
		m.m_types.push_back(&type<char>());
		m.m_types.push_back(&type<schar>());
		m.m_types.push_back(&type<short>());
		m.m_types.push_back(&type<int>());
		m.m_types.push_back(&type<long>());
		m.m_types.push_back(&type<uchar>());
		m.m_types.push_back(&type<ushort>());
		m.m_types.push_back(&type<uint>());
		m.m_types.push_back(&type<ulong>());
		m.m_types.push_back(&type<ullong>());
		m.m_types.push_back(&type<llong>());
		m.m_types.push_back(&type<ldouble>());
		m.m_types.push_back(&type<float>());
		m.m_types.push_back(&type<double>());
		m.m_types.push_back(&type<const char*>());
		m.m_types.push_back(&type<stl::string>());
		m.m_types.push_back(&type<stl::vector<stl::string>>());
		m.m_types.push_back(&type<stl::vector<two::Ref>>());
		m.m_types.push_back(&type<two::Type>());
		m.m_types.push_back(&type<two::Ref>());
		m.m_types.push_back(&type<two::Var>());
		m.m_types.push_back(&type<two::Indexer>());
		m.m_types.push_back(&type<two::Index>());
		m.m_types.push_back(&type<two::Prototype>());
		m.m_types.push_back(&type<void>());
		{
			static Function f = { &namspc({ "two" }), "indexed", funcptr<two::Ref(*)(const two::Type&, uint32_t)>(two::indexed), two_indexed_0, { { "type", type<two::Type>(),  }, { "id", type<uint32_t>(),  } }, { &type<two::Ref>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
	}
}

namespace two
{
	two_type::two_type()
		: Module("two::type", { &two_infra::m() })
	{
		// setup reflection meta data
		two_type_meta(*this);
	}
}

#ifdef TWO_TYPE_MODULE
extern "C"
Module& getModule()
{
	return two_type::m();
}
#endif
