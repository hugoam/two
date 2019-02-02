#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.refl;
#else
#include <stl/new.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/pool/Module.h>
#include <meta/refl/Module.h>
#include <meta/refl/Convert.h>
#endif

#include <refl/Api.h>

using namespace mud;

void mud_TypeClass__to_string(void* val, string& str) { str = g_enu[type<mud::TypeClass>().m_id]->name(uint32_t((*static_cast<mud::TypeClass*>(val)))); }
void mud_TypeClass__to_value(const string& str, void* val) { (*static_cast<mud::TypeClass*>(val)) = mud::TypeClass(g_enu[type<mud::TypeClass>().m_id]->value(str.c_str())); }
size_t vector_mud_Function____size(void* vec) { return (*static_cast<vector<mud::Function*>*>(vec)).size(); }
void* vector_mud_Function____at(void* vec, size_t i) { return &(*static_cast<vector<mud::Function*>*>(vec))[i]; }
void vector_mud_Function____add(void* vec, void* value) { (*static_cast<vector<mud::Function*>*>(vec)).push_back(static_cast<mud::Function*>(value)); }
void vector_mud_Function____remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<mud::Function*>*>(vec)), static_cast<mud::Function*>(value)); }
size_t vector_mud_Module____size(void* vec) { return (*static_cast<vector<mud::Module*>*>(vec)).size(); }
void* vector_mud_Module____at(void* vec, size_t i) { return &(*static_cast<vector<mud::Module*>*>(vec))[i]; }
void vector_mud_Module____add(void* vec, void* value) { (*static_cast<vector<mud::Module*>*>(vec)).push_back(static_cast<mud::Module*>(value)); }
void vector_mud_Module____remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<mud::Module*>*>(vec)), static_cast<mud::Module*>(value)); }
size_t vector_mud_Type____size(void* vec) { return (*static_cast<vector<mud::Type*>*>(vec)).size(); }
void* vector_mud_Type____at(void* vec, size_t i) { return &(*static_cast<vector<mud::Type*>*>(vec))[i]; }
void vector_mud_Type____add(void* vec, void* value) { (*static_cast<vector<mud::Type*>*>(vec)).push_back(static_cast<mud::Type*>(value)); }
void vector_mud_Type____remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<mud::Type*>*>(vec)), static_cast<mud::Type*>(value)); }
size_t vector_mud_Var___size(void* vec) { return (*static_cast<vector<mud::Var>*>(vec)).size(); }
void* vector_mud_Var___at(void* vec, size_t i) { return &(*static_cast<vector<mud::Var>*>(vec))[i]; }
void vector_mud_Var___add(void* vec, void* value) { (*static_cast<vector<mud::Var>*>(vec)).push_back(*static_cast<mud::Var*>(value)); }
void vector_mud_Var___remove(void* vec, void* value) { vector_remove_any((*static_cast<vector<mud::Var>*>(vec)), *static_cast<mud::Var*>(value)); }
void mud_Call__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Call*>(ref))) mud::Call(  ); }
void mud_Call__construct_1(void* ref, array<void*> args) { new(stl::placeholder(), &(*static_cast<mud::Call*>(ref))) mud::Call( *static_cast<mud::Callable*>(args[0]), *static_cast<vector<mud::Var>*>(args[1]) ); }
void mud_Call__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Call*>(ref))) mud::Call((*static_cast<mud::Call*>(other))); }
void* mud_Creator__get_type(void* object) { return &(*static_cast<mud::Creator*>(object)).m_type; }
void* mud_Creator__get_injector(void* object) { return &(*static_cast<mud::Creator*>(object)).injector(); }
void mud_Operator__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::Operator*>(ref))) mud::Operator(  ); }
void mud_Operator__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::Operator*>(ref))) mud::Operator((*static_cast<mud::Operator*>(other))); }
void mud_QualType__construct_0(void* ref, array<void*> args) { UNUSED(args); new(stl::placeholder(), &(*static_cast<mud::QualType*>(ref))) mud::QualType(  ); }
void mud_QualType__copy_construct(void* ref, void* other) { new(stl::placeholder(), &(*static_cast<mud::QualType*>(ref))) mud::QualType((*static_cast<mud::QualType*>(other))); }
void mud_system_0(array<void*> args, void*& result) { UNUSED(args); result = &mud::system(); }

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
		Type& t = type<vector<mud::Function*>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Function*>", sizeof(vector<mud::Function*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Function>(),
		                             vector_mud_Function____size,
		                             vector_mud_Function____at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_mud_Function____add,
		                             vector_mud_Function____remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<mud::Module*>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Module*>", sizeof(vector<mud::Module*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Module>(),
		                             vector_mud_Module____size,
		                             vector_mud_Module____at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_mud_Module____add,
		                             vector_mud_Module____remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<mud::Type*>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Type*>", sizeof(vector<mud::Type*>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Type>(),
		                             vector_mud_Type____size,
		                             vector_mud_Type____at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_mud_Type____add,
		                             vector_mud_Type____remove };
		g_sequence[t.m_id] = &sequence;
	}
	{
		Type& t = type<vector<mud::Var>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Var>", sizeof(vector<mud::Var>), TypeClass::Sequence };
		static Class cls = { t };
		static Iterable iterable = { &type<mud::Var>(),
		                             vector_mud_Var___size,
		                             vector_mud_Var___at};
		g_iterable[t.m_id] = &iterable;
		static Sequence sequence = { vector_mud_Var___add,
		                             vector_mud_Var___remove };
		g_sequence[t.m_id] = &sequence;
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
			{ t, mud_Call__construct_1, { { "callable", type<mud::Callable>(),  }, { "arguments", type<vector<mud::Var>>(),  } } }
		};
		// copy constructor
		static CopyConstructor copy_constructor[] = {
			{ t, mud_Call__copy_construct }
		};
		// members
		static Member members[] = {
			{ t, offsetof(mud::Call, m_args), type<vector<mud::Var>>(), "arguments", nullptr, Member::Value, nullptr },
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
			{ t, offsetof(mud::Module, m_deps), type<vector<mud::Module*>>(), "deps", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Module, m_types), type<vector<mud::Type*>>(), "types", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Module, m_functions), type<vector<mud::Function*>>(), "functions", nullptr, Member::Value, nullptr },
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
			{ t, offsetof(mud::System, m_modules), type<vector<mud::Module*>>(), "modules", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::System, m_types), type<vector<mud::Type*>>(), "types", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::System, m_functions), type<vector<mud::Function*>>(), "functions", nullptr, Member::Value, nullptr }
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
		m.m_types.push_back(&type<vector<mud::Function*>>());
		m.m_types.push_back(&type<vector<mud::Module*>>());
		m.m_types.push_back(&type<vector<mud::Type*>>());
		m.m_types.push_back(&type<vector<mud::Var>>());
		m.m_types.push_back(&type<mud::Constructor>());
		m.m_types.push_back(&type<mud::CopyConstructor>());
		m.m_types.push_back(&type<mud::Destructor>());
		m.m_types.push_back(&type<mud::Function>());
		m.m_types.push_back(&type<mud::Injector>());
		m.m_types.push_back(&type<mud::Method>());
		{
			static Function f = { &namspc({ "mud" }), "system", nullptr, mud_system_0, {}, { &type<mud::System>(), QualType::None } };
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
