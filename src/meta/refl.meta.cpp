#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.refl;
#else
#include <cstddef>
#include <stl/new.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/pool.meta.h>
#include <meta/refl.meta.h>
#include <meta/refl.conv.h>
#endif

#include <refl/Api.h>

using namespace mud;

void mud_TypeClass__to_string(void* val, string& str) { str = g_enu[type<mud::TypeClass>().m_id]->name(uint32_t((*static_cast<mud::TypeClass*>(val)))); }
void mud_TypeClass__to_value(const string& str, void* val) { (*static_cast<mud::TypeClass*>(val)) = mud::TypeClass(g_enu[type<mud::TypeClass>().m_id]->value(str.c_str())); }
size_t stl_span_mud_Type___size(void* vec) { return (*static_cast<stl::span<mud::Type*>*>(vec)).size(); }
void* stl_span_mud_Type___at(void* vec, size_t i) { return &(*static_cast<stl::span<mud::Type*>*>(vec))[i]; }
size_t stl_vector_mud_Alias___size(void* vec) { return (*static_cast<stl::vector<mud::Alias*>*>(vec)).size(); }
void* stl_vector_mud_Alias___at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::Alias*>*>(vec))[i]; }
void stl_vector_mud_Alias___push(void* vec) { (*static_cast<stl::vector<mud::Alias*>*>(vec)).emplace_back(); }
void stl_vector_mud_Alias___add(void* vec, void* value) { (*static_cast<stl::vector<mud::Alias*>*>(vec)).push_back(static_cast<mud::Alias*>(value)); }
void stl_vector_mud_Alias___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::Alias*>*>(vec)), static_cast<mud::Alias*>(value)); }
size_t stl_vector_mud_Function___size(void* vec) { return (*static_cast<stl::vector<mud::Function*>*>(vec)).size(); }
void* stl_vector_mud_Function___at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::Function*>*>(vec))[i]; }
void stl_vector_mud_Function___push(void* vec) { (*static_cast<stl::vector<mud::Function*>*>(vec)).emplace_back(); }
void stl_vector_mud_Function___add(void* vec, void* value) { (*static_cast<stl::vector<mud::Function*>*>(vec)).push_back(static_cast<mud::Function*>(value)); }
void stl_vector_mud_Function___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::Function*>*>(vec)), static_cast<mud::Function*>(value)); }
size_t stl_vector_mud_Module___size(void* vec) { return (*static_cast<stl::vector<mud::Module*>*>(vec)).size(); }
void* stl_vector_mud_Module___at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::Module*>*>(vec))[i]; }
void stl_vector_mud_Module___push(void* vec) { (*static_cast<stl::vector<mud::Module*>*>(vec)).emplace_back(); }
void stl_vector_mud_Module___add(void* vec, void* value) { (*static_cast<stl::vector<mud::Module*>*>(vec)).push_back(static_cast<mud::Module*>(value)); }
void stl_vector_mud_Module___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::Module*>*>(vec)), static_cast<mud::Module*>(value)); }
size_t stl_vector_mud_Type___size(void* vec) { return (*static_cast<stl::vector<mud::Type*>*>(vec)).size(); }
void* stl_vector_mud_Type___at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::Type*>*>(vec))[i]; }
void stl_vector_mud_Type___push(void* vec) { (*static_cast<stl::vector<mud::Type*>*>(vec)).emplace_back(); }
void stl_vector_mud_Type___add(void* vec, void* value) { (*static_cast<stl::vector<mud::Type*>*>(vec)).push_back(static_cast<mud::Type*>(value)); }
void stl_vector_mud_Type___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::Type*>*>(vec)), static_cast<mud::Type*>(value)); }
size_t stl_vector_mud_Var__size(void* vec) { return (*static_cast<stl::vector<mud::Var>*>(vec)).size(); }
void* stl_vector_mud_Var__at(void* vec, size_t i) { return &(*static_cast<stl::vector<mud::Var>*>(vec))[i]; }
void stl_vector_mud_Var__push(void* vec) { (*static_cast<stl::vector<mud::Var>*>(vec)).emplace_back(); }
void stl_vector_mud_Var__add(void* vec, void* value) { (*static_cast<stl::vector<mud::Var>*>(vec)).push_back(*static_cast<mud::Var*>(value)); }
void stl_vector_mud_Var__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<mud::Var>*>(vec)), *static_cast<mud::Var*>(value)); }
size_t stl_vector_void___size(void* vec) { return (*static_cast<stl::vector<void*>*>(vec)).size(); }
void* stl_vector_void___at(void* vec, size_t i) { return &(*static_cast<stl::vector<void*>*>(vec))[i]; }
void stl_vector_void___push(void* vec) { (*static_cast<stl::vector<void*>*>(vec)).emplace_back(); }
void stl_vector_void___add(void* vec, void* value) { (*static_cast<stl::vector<void*>*>(vec)).push_back(static_cast<void*>(value)); }
void stl_vector_void___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<void*>*>(vec)), static_cast<void*>(value)); }
void mud_Alias__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Alias(  ); }
void mud_Alias__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Alias((*static_cast<mud::Alias*>(other))); }
void mud_Call__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Call(  ); }
void mud_Call__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::Call( *static_cast<mud::Callable*>(args[0]), *static_cast<stl::vector<mud::Var>*>(args[1]) ); }
void mud_Call__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Call((*static_cast<mud::Call*>(other))); }
void* mud_Creator__get_type(void* object) { return &(*static_cast<mud::Creator*>(object)).m_type; }
void* mud_Creator__get_injector(void* object) { return &(*static_cast<mud::Creator*>(object)).injector(); }
void mud_Operator__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::Operator(  ); }
void mud_Operator__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::Operator((*static_cast<mud::Operator*>(other))); }
void mud_QualType__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) mud::QualType(  ); }
void mud_QualType__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) mud::QualType((*static_cast<mud::QualType*>(other))); }
void mud_system_0(span<void*> args, void*& result) { UNUSED(args); result = &mud::system(); }

namespace mud
{
	void mud_refl_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::TypeClass>();
		static Meta meta = { t, &namspc({ "mud" }), "TypeClass", sizeof(mud::TypeClass), TypeClass::Enum };
		static cstring ids[] = { "None", "Object", "Struct", "Sequence", "BaseType", "Enum" };
		static uint32_t values[] = { 0, 1, 2, 4, 5, 6 };
		static mud::TypeClass vars[] = { mud::TypeClass::None, mud::TypeClass::Object, mud::TypeClass::Struct, mud::TypeClass::Sequence, mud::TypeClass::BaseType, mud::TypeClass::Enum};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_TypeClass__to_string,
		                           mud_TypeClass__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	{
		Type& t = type<stl::span<mud::Type*>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<mud::Type*>", sizeof(stl::span<mud::Type*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Type>(),
		                             stl_span_mud_Type___size,
		                             stl_span_mud_Type___at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::vector<mud::Alias*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::Alias*>", sizeof(stl::vector<mud::Alias*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Alias>(),
		                             stl_vector_mud_Alias___size,
		                             stl_vector_mud_Alias___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_Alias___push,
		                             stl_vector_mud_Alias___add,
		                             stl_vector_mud_Alias___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::Function*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::Function*>", sizeof(stl::vector<mud::Function*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Function>(),
		                             stl_vector_mud_Function___size,
		                             stl_vector_mud_Function___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_Function___push,
		                             stl_vector_mud_Function___add,
		                             stl_vector_mud_Function___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::Module*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::Module*>", sizeof(stl::vector<mud::Module*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Module>(),
		                             stl_vector_mud_Module___size,
		                             stl_vector_mud_Module___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_Module___push,
		                             stl_vector_mud_Module___add,
		                             stl_vector_mud_Module___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::Type*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::Type*>", sizeof(stl::vector<mud::Type*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Type>(),
		                             stl_vector_mud_Type___size,
		                             stl_vector_mud_Type___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_Type___push,
		                             stl_vector_mud_Type___add,
		                             stl_vector_mud_Type___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<mud::Var>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<mud::Var>", sizeof(stl::vector<mud::Var>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Var>(),
		                             stl_vector_mud_Var__size,
		                             stl_vector_mud_Var__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_mud_Var__push,
		                             stl_vector_mud_Var__add,
		                             stl_vector_mud_Var__remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<void*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<void*>", sizeof(stl::vector<void*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<void*>(),
		                             stl_vector_void___size,
		                             stl_vector_void___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_void___push,
		                             stl_vector_void___add,
		                             stl_vector_void___remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// mud::Alias
	{
		Type& t = type<mud::Alias>();
		static Meta meta = { t, &namspc({ "mud" }), "Alias", sizeof(mud::Alias), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Alias__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Alias__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Call
	{
		Type& t = type<mud::Call>();
		static Meta meta = { t, &namspc({ "mud" }), "Call", sizeof(mud::Call), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Call__construct_0, {} },
			{ t, mud_Call__construct_1, { { "callable", type<mud::Callable>(),  }, { "args", type<stl::vector<mud::Var>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Call__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Call, m_args), type<stl::vector<mud::Var>>(), "args", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Call, m_vargs), type<stl::vector<void*>>(), "vargs", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Call, m_result), type<mud::Var>(), "result", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Callable
	{
		Type& t = type<mud::Callable>();
		static Meta meta = { t, &namspc({ "mud" }), "Callable", sizeof(mud::Callable), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Class
	{
		Type& t = type<mud::Class>();
		static Meta meta = { t, &namspc({ "mud" }), "Class", sizeof(mud::Class), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Convert
	{
		Type& t = type<mud::Convert>();
		static Meta meta = { t, &namspc({ "mud" }), "Convert", sizeof(mud::Convert), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Creator
	{
		Type& t = type<mud::Creator>();
		static Meta meta = { t, &namspc({ "mud" }), "Creator", sizeof(mud::Creator), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<mud::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_Creator__get_type },
			{ t, offsetof(mud::Creator, m_construct), type<bool>(), "construct", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Creator, m_prototype), type<mud::Type>(), "prototype", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, SIZE_MAX, type<mud::Injector>(), "injector", nullptr, Member::Flags(Member::NonMutable|Member::Link), mud_Creator__get_injector }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::Enum
	{
		Type& t = type<mud::Enum>();
		static Meta meta = { t, &namspc({ "mud" }), "Enum", sizeof(mud::Enum), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Member
	{
		Type& t = type<mud::Member>();
		static Meta meta = { t, &namspc({ "mud" }), "Member", sizeof(mud::Member), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Meta
	{
		Type& t = type<mud::Meta>();
		static Meta meta = { t, &namspc({ "mud" }), "Meta", sizeof(mud::Meta), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Module
	{
		Type& t = type<mud::Module>();
		static Meta meta = { t, &namspc({ "mud" }), "Module", sizeof(mud::Module), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Module, m_name), type<const char*>(), "name", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Module, m_deps), type<stl::vector<mud::Module*>>(), "deps", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Module, m_types), type<stl::vector<mud::Type*>>(), "types", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Module, m_aliases), type<stl::vector<mud::Alias*>>(), "aliases", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Module, m_functions), type<stl::vector<mud::Function*>>(), "functions", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Module, m_path), type<const char*>(), "path", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::Namespace
	{
		Type& t = type<mud::Namespace>();
		static Meta meta = { t, &namspc({ "mud" }), "Namespace", sizeof(mud::Namespace), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Operator
	{
		Type& t = type<mud::Operator>();
		static Meta meta = { t, &namspc({ "mud" }), "Operator", sizeof(mud::Operator), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_Operator__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Operator__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Operator, m_function), type<mud::Function>(), "function", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Operator, m_type), type<mud::Type>(), "type", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Operator, m_name), type<const char*>(), "name", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Operator, m_sign), type<const char*>(), "sign", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// mud::Param
	{
		Type& t = type<mud::Param>();
		static Meta meta = { t, &namspc({ "mud" }), "Param", sizeof(mud::Param), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::QualType
	{
		Type& t = type<mud::QualType>();
		static Meta meta = { t, &namspc({ "mud" }), "QualType", sizeof(mud::QualType), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_QualType__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_QualType__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// mud::Signature
	{
		Type& t = type<mud::Signature>();
		static Meta meta = { t, &namspc({ "mud" }), "Signature", sizeof(mud::Signature), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::Static
	{
		Type& t = type<mud::Static>();
		static Meta meta = { t, &namspc({ "mud" }), "Static", sizeof(mud::Static), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::System
	{
		Type& t = type<mud::System>();
		static Meta meta = { t, &namspc({ "mud" }), "System", sizeof(mud::System), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::System, m_modules), type<stl::vector<mud::Module*>>(), "modules", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::System, m_types), type<stl::vector<mud::Type*>>(), "types", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::System, m_aliases), type<stl::vector<mud::Alias*>>(), "aliases", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::System, m_functions), type<stl::vector<mud::Function*>>(), "functions", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// mud::Constructor
	{
		Type& t = type<mud::Constructor>();
		static Meta meta = { t, &namspc({ "mud" }), "Constructor", sizeof(mud::Constructor), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Callable>() };
		static size_t bases_offsets[] = { base_offset<mud::Constructor, mud::Callable>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::CopyConstructor
	{
		Type& t = type<mud::CopyConstructor>();
		static Meta meta = { t, &namspc({ "mud" }), "CopyConstructor", sizeof(mud::CopyConstructor), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Callable>() };
		static size_t bases_offsets[] = { base_offset<mud::CopyConstructor, mud::Callable>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Destructor
	{
		Type& t = type<mud::Destructor>();
		static Meta meta = { t, &namspc({ "mud" }), "Destructor", sizeof(mud::Destructor), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Callable>() };
		static size_t bases_offsets[] = { base_offset<mud::Destructor, mud::Callable>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Function
	{
		Type& t = type<mud::Function>();
		static Meta meta = { t, &namspc({ "mud" }), "Function", sizeof(mud::Function), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Callable>() };
		static size_t bases_offsets[] = { base_offset<mud::Function, mud::Callable>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Injector
	{
		Type& t = type<mud::Injector>();
		static Meta meta = { t, &namspc({ "mud" }), "Injector", sizeof(mud::Injector), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Call>() };
		static size_t bases_offsets[] = { base_offset<mud::Injector, mud::Call>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Method
	{
		Type& t = type<mud::Method>();
		static Meta meta = { t, &namspc({ "mud" }), "Method", sizeof(mud::Method), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Callable>() };
		static size_t bases_offsets[] = { base_offset<mud::Method, mud::Callable>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<mud::Alias>());
		m.m_types.push_back(&type<mud::Call>());
		m.m_types.push_back(&type<mud::Callable>());
		m.m_types.push_back(&type<mud::Class>());
		m.m_types.push_back(&type<mud::Convert>());
		m.m_types.push_back(&type<mud::Creator>());
		m.m_types.push_back(&type<mud::Enum>());
		m.m_types.push_back(&type<mud::Member>());
		m.m_types.push_back(&type<mud::Meta>());
		m.m_types.push_back(&type<mud::Module>());
		m.m_types.push_back(&type<mud::Namespace>());
		m.m_types.push_back(&type<mud::Operator>());
		m.m_types.push_back(&type<mud::Param>());
		m.m_types.push_back(&type<mud::QualType>());
		m.m_types.push_back(&type<mud::Signature>());
		m.m_types.push_back(&type<mud::Static>());
		m.m_types.push_back(&type<mud::System>());
		m.m_types.push_back(&type<mud::TypeClass>());
		m.m_types.push_back(&type<stl::span<mud::Type*>>());
		m.m_types.push_back(&type<stl::vector<mud::Alias*>>());
		m.m_types.push_back(&type<stl::vector<mud::Function*>>());
		m.m_types.push_back(&type<stl::vector<mud::Module*>>());
		m.m_types.push_back(&type<stl::vector<mud::Type*>>());
		m.m_types.push_back(&type<stl::vector<mud::Var>>());
		m.m_types.push_back(&type<stl::vector<void*>>());
		m.m_types.push_back(&type<mud::Constructor>());
		m.m_types.push_back(&type<mud::CopyConstructor>());
		m.m_types.push_back(&type<mud::Destructor>());
		m.m_types.push_back(&type<mud::Function>());
		m.m_types.push_back(&type<mud::Injector>());
		m.m_types.push_back(&type<mud::Method>());
		{
			static Function f = { &namspc({ "mud" }), "system", funcptr<mud::System&(*)()>(mud::system), mud_system_0, {}, { &type<mud::System>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_refl::mud_refl()
		: Module("mud::refl", { &mud_infra::m(), &mud_type::m(), &mud_pool::m() })
	{
		// setup reflection meta data
		mud_refl_meta(*this);
	}
}

#ifdef MUD_REFL_MODULE
extern "C"
Module& getModule()
{
	return mud_refl::m();
}
#endif
