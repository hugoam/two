#pragma once

#include <mud/refl.h>
#include <mud/infra.h>
#include <mud/type.h>






#ifndef MUD_SRLZ_EXPORT
#define MUD_SRLZ_EXPORT MUD_IMPORT
#endif


    
    

namespace mud {

    
    
    class FromJson;
    class ToJson;
}

namespace json11 {

    
    
}



#ifndef MUD_MODULES
#include <stl/string.h>
#endif

#ifndef MUD_MODULES
namespace json11
{
	class Json;
}
#endif

namespace mud
{
	export_ using Json = json11::Json;

	export_ class MUD_SRLZ_EXPORT FromJson : public Dispatch<void, const Json&>
	{
	public:
		FromJson();
	};

	export_ class MUD_SRLZ_EXPORT ToJson : public Dispatch<void, Json&>
	{
	public:
		ToJson();
	};

	export_ MUD_SRLZ_EXPORT void parse_json_file(const string& path, Json& data);
	export_ MUD_SRLZ_EXPORT void dump_json_file(const string& path, const Json& data);

#if 0
	export_ using JsonVisitor = std::function<void(Json&)>;
	export_ MUD_SRLZ_EXPORT void visit_json(Json& value, const JsonVisitor& visitor);
#endif

	export_ MUD_SRLZ_EXPORT Var unpack(Type& type, const Json& data);
	export_ MUD_SRLZ_EXPORT Var unpack(FromJson& unpacker, Type& type, const Json& data);
	export_ MUD_SRLZ_EXPORT void unpack(Var& value, const Json& data);
	export_ MUD_SRLZ_EXPORT void unpack(Ref value, const Json& data);
	export_ MUD_SRLZ_EXPORT void unpack(FromJson& unpacker, Var& value, const Json& data);
	export_ MUD_SRLZ_EXPORT void unpack(FromJson& unpacker, Ref value, const Json& data);

	export_ MUD_SRLZ_EXPORT Var unpack_typed(const Json& data);
	export_ MUD_SRLZ_EXPORT Var unpack_typed(FromJson& unpacker, const Json& data);

	export_ MUD_SRLZ_EXPORT void pack(const Var& value, Json& data);
	export_ MUD_SRLZ_EXPORT void pack(ToJson& packer, const Var& value, Json& data, bool typed = false);

	export_ MUD_SRLZ_EXPORT void pack_typed(const Var& value, Json& data);
	export_ MUD_SRLZ_EXPORT void pack_typed(ToJson& packer, const Var& value, Json& data);

	export_ template <class T>
	T unpackt(const Json& data);

	export_ MUD_SRLZ_EXPORT string pack_json(const Var& value);

	export_ MUD_SRLZ_EXPORT void pack_json_file(const Var& value, const string& path);
	export_ MUD_SRLZ_EXPORT void pack_json_file(ToJson& packer, const Var& value, const string& path);
	export_ MUD_SRLZ_EXPORT void unpack_json_file(Ref value, const string& path);
}

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif


namespace mud
{
    // Exported types
    
    
}



#ifndef MUD_MODULES
#endif

namespace mud
{
	export_ template <class T>
	T unpackt(const Json& data)
	{
		Var value = unpack(type<T>(), data);
		return val<T>(value);
	}
}
