#include <two/infra.h>

module;
module two.refl.meta;

using namespace two;

void two_TypeClass__to_string(void* val, string& str) { str = g_enu[type<two::TypeClass>().m_id]->name(uint32_t((*static_cast<two::TypeClass*>(val)))); }
void two_TypeClass__to_value(const string& str, void* val) { (*static_cast<two::TypeClass*>(val)) = two::TypeClass(g_enu[type<two::TypeClass>().m_id]->value(str.c_str())); }
size_t stl_span_two_Type___size(void* vec) { return (*static_cast<stl::span<two::Type*>*>(vec)).size(); }
void* stl_span_two_Type___at(void* vec, size_t i) { return &(*static_cast<stl::span<two::Type*>*>(vec))[i]; }
size_t stl_vector_two_Var__size(void* vec) { return (*static_cast<stl::vector<two::Var>*>(vec)).size(); }
void* stl_vector_two_Var__at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Var>*>(vec))[i]; }
void stl_vector_two_Var__push(void* vec) { (*static_cast<stl::vector<two::Var>*>(vec)).emplace_back(); }
void stl_vector_two_Var__add(void* vec, void* value) { (*static_cast<stl::vector<two::Var>*>(vec)).push_back(*static_cast<two::Var*>(value)); }
void stl_vector_two_Var__remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Var>*>(vec)), *static_cast<two::Var*>(value)); }
size_t stl_vector_void___size(void* vec) { return (*static_cast<stl::vector<void*>*>(vec)).size(); }
void* stl_vector_void___at(void* vec, size_t i) { return &(*static_cast<stl::vector<void*>*>(vec))[i]; }
void stl_vector_void___push(void* vec) { (*static_cast<stl::vector<void*>*>(vec)).emplace_back(); }
void stl_vector_void___add(void* vec, void* value) { (*static_cast<stl::vector<void*>*>(vec)).push_back(static_cast<void*>(value)); }
void stl_vector_void___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<void*>*>(vec)), static_cast<void*>(value)); }
size_t stl_vector_two_Module___size(void* vec) { return (*static_cast<stl::vector<two::Module*>*>(vec)).size(); }
void* stl_vector_two_Module___at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Module*>*>(vec))[i]; }
void stl_vector_two_Module___push(void* vec) { (*static_cast<stl::vector<two::Module*>*>(vec)).emplace_back(); }
void stl_vector_two_Module___add(void* vec, void* value) { (*static_cast<stl::vector<two::Module*>*>(vec)).push_back(static_cast<two::Module*>(value)); }
void stl_vector_two_Module___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Module*>*>(vec)), static_cast<two::Module*>(value)); }
size_t stl_vector_two_Type___size(void* vec) { return (*static_cast<stl::vector<two::Type*>*>(vec)).size(); }
void* stl_vector_two_Type___at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Type*>*>(vec))[i]; }
void stl_vector_two_Type___push(void* vec) { (*static_cast<stl::vector<two::Type*>*>(vec)).emplace_back(); }
void stl_vector_two_Type___add(void* vec, void* value) { (*static_cast<stl::vector<two::Type*>*>(vec)).push_back(static_cast<two::Type*>(value)); }
void stl_vector_two_Type___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Type*>*>(vec)), static_cast<two::Type*>(value)); }
size_t stl_vector_two_Alias___size(void* vec) { return (*static_cast<stl::vector<two::Alias*>*>(vec)).size(); }
void* stl_vector_two_Alias___at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Alias*>*>(vec))[i]; }
void stl_vector_two_Alias___push(void* vec) { (*static_cast<stl::vector<two::Alias*>*>(vec)).emplace_back(); }
void stl_vector_two_Alias___add(void* vec, void* value) { (*static_cast<stl::vector<two::Alias*>*>(vec)).push_back(static_cast<two::Alias*>(value)); }
void stl_vector_two_Alias___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Alias*>*>(vec)), static_cast<two::Alias*>(value)); }
size_t stl_vector_two_Function___size(void* vec) { return (*static_cast<stl::vector<two::Function*>*>(vec)).size(); }
void* stl_vector_two_Function___at(void* vec, size_t i) { return &(*static_cast<stl::vector<two::Function*>*>(vec))[i]; }
void stl_vector_two_Function___push(void* vec) { (*static_cast<stl::vector<two::Function*>*>(vec)).emplace_back(); }
void stl_vector_two_Function___add(void* vec, void* value) { (*static_cast<stl::vector<two::Function*>*>(vec)).push_back(static_cast<two::Function*>(value)); }
void stl_vector_two_Function___remove(void* vec, void* value) { vector_remove_any((*static_cast<stl::vector<two::Function*>*>(vec)), static_cast<two::Function*>(value)); }
void two_QualType__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::QualType(  ); }
void two_QualType__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::QualType((*static_cast<two::QualType*>(other))); }
void two_Operator__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Operator(  ); }
void two_Operator__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Operator((*static_cast<two::Operator*>(other))); }
void two_Call__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Call(  ); }
void two_Call__construct_1(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::Call( *static_cast<two::Callable*>(args[0]), *static_cast<stl::vector<two::Var>*>(args[1]) ); }
void two_Call__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Call((*static_cast<two::Call*>(other))); }
void* two_Creator__get_type(void* object) { return &(*static_cast<two::Creator*>(object)).m_type; }
void* two_Creator__get_injector(void* object) { return &(*static_cast<two::Creator*>(object)).injector(); }
void two_Alias__construct_0(void* ref, span<void*> args) { UNUSED(args); new(stl::placeholder(), ref) two::Alias(  ); }
void two_Alias__copy_construct(void* ref, void* other) { new(stl::placeholder(), ref) two::Alias((*static_cast<two::Alias*>(other))); }
void two_system_0(span<void*> args, void*& result) { UNUSED(args); result = &two::system(); }

namespace two
{
	void two_refl_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<two::TypeClass>();
		static Meta meta = { t, &namspc({ "two" }), "TypeClass", sizeof(two::TypeClass), TypeClass::Enum };
		static cstring ids[] = { "None", "Object", "Struct", "Sequence", "BaseType", "Enum" };
		static uint32_t values[] = { 0, 1, 2, 4, 5, 6 };
		static two::TypeClass vars[] = { two::TypeClass::None, two::TypeClass::Object, two::TypeClass::Struct, two::TypeClass::Sequence, two::TypeClass::BaseType, two::TypeClass::Enum};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_TypeClass__to_string,
		                           two_TypeClass__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	{
		Type& t = type<stl::span<two::Type*>>();
		static Meta meta = { t, &namspc({ "stl" }), "span<two::Type*>", sizeof(stl::span<two::Type*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Type>(),
		                             stl_span_two_Type___size,
		                             stl_span_two_Type___at};
		g_iterable[t.m_id] = &iterable;
	}
	{
		Type& t = type<stl::vector<two::Var>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Var>", sizeof(stl::vector<two::Var>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Var>(),
		                             stl_vector_two_Var__size,
		                             stl_vector_two_Var__at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Var__push,
		                             stl_vector_two_Var__add,
		                             stl_vector_two_Var__remove };
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
	{
		Type& t = type<stl::vector<two::Module*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Module*>", sizeof(stl::vector<two::Module*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Module>(),
		                             stl_vector_two_Module___size,
		                             stl_vector_two_Module___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Module___push,
		                             stl_vector_two_Module___add,
		                             stl_vector_two_Module___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::Type*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Type*>", sizeof(stl::vector<two::Type*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Type>(),
		                             stl_vector_two_Type___size,
		                             stl_vector_two_Type___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Type___push,
		                             stl_vector_two_Type___add,
		                             stl_vector_two_Type___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::Alias*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Alias*>", sizeof(stl::vector<two::Alias*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Alias>(),
		                             stl_vector_two_Alias___size,
		                             stl_vector_two_Alias___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Alias___push,
		                             stl_vector_two_Alias___add,
		                             stl_vector_two_Alias___remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<stl::vector<two::Function*>>();
		static Meta meta = { t, &namspc({ "stl" }), "vector<two::Function*>", sizeof(stl::vector<two::Function*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<two::Function>(),
		                             stl_vector_two_Function___size,
		                             stl_vector_two_Function___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { stl_vector_two_Function___push,
		                             stl_vector_two_Function___add,
		                             stl_vector_two_Function___remove };
		g_sequence[t.m_id] = &sequence;
	}
	
	// two::QualType
	{
		Type& t = type<two::QualType>();
		static Meta meta = { t, &namspc({ "two" }), "QualType", sizeof(two::QualType), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_QualType__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_QualType__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Param
	{
		Type& t = type<two::Param>();
		static Meta meta = { t, &namspc({ "two" }), "Param", sizeof(two::Param), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Signature
	{
		Type& t = type<two::Signature>();
		static Meta meta = { t, &namspc({ "two" }), "Signature", sizeof(two::Signature), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Callable
	{
		Type& t = type<two::Callable>();
		static Meta meta = { t, &namspc({ "two" }), "Callable", sizeof(two::Callable), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Function
	{
		Type& t = type<two::Function>();
		static Meta meta = { t, &namspc({ "two" }), "Function", sizeof(two::Function), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Callable>() };
		static size_t bases_offsets[] = { base_offset<two::Function, two::Callable>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Operator
	{
		Type& t = type<two::Operator>();
		static Meta meta = { t, &namspc({ "two" }), "Operator", sizeof(two::Operator), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Operator__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Operator__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Operator, m_function), type<two::Function>(), "function", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Operator, m_type), type<two::Type>(), "type", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Operator, m_name), type<const char*>(), "name", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Operator, m_sign), type<const char*>(), "sign", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Method
	{
		Type& t = type<two::Method>();
		static Meta meta = { t, &namspc({ "two" }), "Method", sizeof(two::Method), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Callable>() };
		static size_t bases_offsets[] = { base_offset<two::Method, two::Callable>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Constructor
	{
		Type& t = type<two::Constructor>();
		static Meta meta = { t, &namspc({ "two" }), "Constructor", sizeof(two::Constructor), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Callable>() };
		static size_t bases_offsets[] = { base_offset<two::Constructor, two::Callable>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::CopyConstructor
	{
		Type& t = type<two::CopyConstructor>();
		static Meta meta = { t, &namspc({ "two" }), "CopyConstructor", sizeof(two::CopyConstructor), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Callable>() };
		static size_t bases_offsets[] = { base_offset<two::CopyConstructor, two::Callable>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Destructor
	{
		Type& t = type<two::Destructor>();
		static Meta meta = { t, &namspc({ "two" }), "Destructor", sizeof(two::Destructor), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Callable>() };
		static size_t bases_offsets[] = { base_offset<two::Destructor, two::Callable>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Call
	{
		Type& t = type<two::Call>();
		static Meta meta = { t, &namspc({ "two" }), "Call", sizeof(two::Call), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Call__construct_0, {} },
			{ t, two_Call__construct_1, { { "callable", type<two::Callable>(),  }, { "args", type<stl::vector<two::Var>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Call__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(two::Call, m_args), type<stl::vector<two::Var>>(), "args", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Call, m_vargs), type<stl::vector<void*>>(), "vargs", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Call, m_result), type<two::Var>(), "result", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, members, {}, {}, };
	}
	// two::Meta
	{
		Type& t = type<two::Meta>();
		static Meta meta = { t, &namspc({ "two" }), "Meta", sizeof(two::Meta), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Convert
	{
		Type& t = type<two::Convert>();
		static Meta meta = { t, &namspc({ "two" }), "Convert", sizeof(two::Convert), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Static
	{
		Type& t = type<two::Static>();
		static Meta meta = { t, &namspc({ "two" }), "Static", sizeof(two::Static), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Member
	{
		Type& t = type<two::Member>();
		static Meta meta = { t, &namspc({ "two" }), "Member", sizeof(two::Member), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Class
	{
		Type& t = type<two::Class>();
		static Meta meta = { t, &namspc({ "two" }), "Class", sizeof(two::Class), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Enum
	{
		Type& t = type<two::Enum>();
		static Meta meta = { t, &namspc({ "two" }), "Enum", sizeof(two::Enum), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Injector
	{
		Type& t = type<two::Injector>();
		static Meta meta = { t, &namspc({ "two" }), "Injector", sizeof(two::Injector), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Call>() };
		static size_t bases_offsets[] = { base_offset<two::Injector, two::Call>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::Creator
	{
		Type& t = type<two::Creator>();
		static Meta meta = { t, &namspc({ "two" }), "Creator", sizeof(two::Creator), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, SIZE_MAX, type<two::Type>(), "type", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_Creator__get_type },
			{ t, offsetof(two::Creator, m_construct), type<bool>(), "construct", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Creator, m_prototype), type<two::Type>(), "prototype", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, SIZE_MAX, type<two::Injector>(), "injector", nullptr, Member::Flags(Member::NonMutable|Member::Link), two_Creator__get_injector }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::Namespace
	{
		Type& t = type<two::Namespace>();
		static Meta meta = { t, &namspc({ "two" }), "Namespace", sizeof(two::Namespace), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Alias
	{
		Type& t = type<two::Alias>();
		static Meta meta = { t, &namspc({ "two" }), "Alias", sizeof(two::Alias), TypeClass::Struct };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_Alias__construct_0, {} }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, two_Alias__copy_construct }
		};
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, constructors, copy_constructor, {}, {}, {}, };
	}
	// two::Module
	{
		Type& t = type<two::Module>();
		static Meta meta = { t, &namspc({ "two" }), "Module", sizeof(two::Module), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Module, m_name), type<const char*>(), "name", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Module, m_deps), type<stl::vector<two::Module*>>(), "deps", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Module, m_types), type<stl::vector<two::Type*>>(), "types", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Module, m_aliases), type<stl::vector<two::Alias*>>(), "aliases", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Module, m_functions), type<stl::vector<two::Function*>>(), "functions", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Module, m_path), type<const char*>(), "path", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	// two::System
	{
		Type& t = type<two::System>();
		static Meta meta = { t, &namspc({ "two" }), "System", sizeof(two::System), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::System, m_modules), type<stl::vector<two::Module*>>(), "modules", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::System, m_types), type<stl::vector<two::Type*>>(), "types", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::System, m_aliases), type<stl::vector<two::Alias*>>(), "aliases", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::System, m_functions), type<stl::vector<two::Function*>>(), "functions", nullptr, Member::NonMutable, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, members, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<stl::span<two::Type*>>());
		m.m_types.push_back(&type<stl::vector<two::Var>>());
		m.m_types.push_back(&type<stl::vector<void*>>());
		m.m_types.push_back(&type<stl::vector<two::Module*>>());
		m.m_types.push_back(&type<stl::vector<two::Type*>>());
		m.m_types.push_back(&type<stl::vector<two::Alias*>>());
		m.m_types.push_back(&type<stl::vector<two::Function*>>());
		m.m_types.push_back(&type<two::QualType>());
		m.m_types.push_back(&type<two::Param>());
		m.m_types.push_back(&type<two::Signature>());
		m.m_types.push_back(&type<two::Callable>());
		m.m_types.push_back(&type<two::Function>());
		m.m_types.push_back(&type<two::Operator>());
		m.m_types.push_back(&type<two::Method>());
		m.m_types.push_back(&type<two::Constructor>());
		m.m_types.push_back(&type<two::CopyConstructor>());
		m.m_types.push_back(&type<two::Destructor>());
		m.m_types.push_back(&type<two::Call>());
		m.m_types.push_back(&type<two::TypeClass>());
		m.m_types.push_back(&type<two::Meta>());
		m.m_types.push_back(&type<two::Convert>());
		m.m_types.push_back(&type<two::Static>());
		m.m_types.push_back(&type<two::Member>());
		m.m_types.push_back(&type<two::Class>());
		m.m_types.push_back(&type<two::Enum>());
		m.m_types.push_back(&type<two::Injector>());
		m.m_types.push_back(&type<two::Creator>());
		m.m_types.push_back(&type<two::Namespace>());
		m.m_types.push_back(&type<two::Alias>());
		m.m_types.push_back(&type<two::Module>());
		m.m_types.push_back(&type<two::System>());
		{
			static Function f = { &namspc({ "two" }), "system", funcptr<two::System&(*)()>(two::system), two_system_0, {}, { &type<two::System>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
	}
}

namespace two
{
	two_refl::two_refl()
		: Module("two::refl", { &two_infra::m(), &two_type::m(), &two_pool::m() })
	{
		// setup reflection meta data
		two_refl_meta(*this);
	}
}

#ifdef TWO_REFL_MODULE
extern "C"
Module& getModule()
{
	return two_refl::m();
}
#endif
