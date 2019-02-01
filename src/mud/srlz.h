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

export_ using json = json11::Json;

namespace mud
{
	export_ class MUD_SRLZ_EXPORT FromJson : public Dispatch<void, const json&>
	{
	public:
		FromJson();
	};

	export_ class MUD_SRLZ_EXPORT ToJson : public Dispatch<void, json&>
	{
	public:
		ToJson();
	};

	export_ MUD_SRLZ_EXPORT void parse_json_file(const string& path, json& data);
	export_ MUD_SRLZ_EXPORT void dump_json_file(const string& path, const json& data);

#if 0
	export_ using JsonVisitor = std::function<void(json&)>;
	export_ MUD_SRLZ_EXPORT void visit_json(json& value, const JsonVisitor& visitor);
#endif

	export_ MUD_SRLZ_EXPORT const Var& unpack(Type& type, const json& data);
	export_ MUD_SRLZ_EXPORT const Var& unpack(FromJson& unpacker, Type& type, const json& data, bool typed = false);
	export_ MUD_SRLZ_EXPORT void unpack(Var& value, const json& data);
	export_ MUD_SRLZ_EXPORT void unpack(Ref value, const json& data);
	export_ MUD_SRLZ_EXPORT void unpack(FromJson& unpacker, Var& value, const json& data, bool typed = false);

	export_ MUD_SRLZ_EXPORT const Var& unpack_typed(const json& data);
	export_ MUD_SRLZ_EXPORT const Var& unpack_typed(FromJson& unpacker, const json& data);

	export_ MUD_SRLZ_EXPORT void pack(const Var& value, json& data);
	export_ MUD_SRLZ_EXPORT void pack(ToJson& packer, const Var& value, json& data, bool typed = false);

	export_ MUD_SRLZ_EXPORT void pack_typed(const Var& value, json& data);
	export_ MUD_SRLZ_EXPORT void pack_typed(ToJson& packer, const Var& value, json& data);

	export_ template <class T>
	T unpackt(const json& data);

	export_ MUD_SRLZ_EXPORT string pack_json(const Var& value);

	export_ MUD_SRLZ_EXPORT void pack_json_file(const Var& value, const string& path);
	export_ MUD_SRLZ_EXPORT void pack_json_file(ToJson& packer, const Var& value, const string& path);
	export_ MUD_SRLZ_EXPORT void unpack_json_file(Ref value, const string& path);
}


#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#endif

#ifndef MUD_MODULES
#endif

#ifndef MUD_CPP_20
#include <stl/string.h>
#include <stl/vector.h>
#include <stdint.h>
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
	T unpackt(const json& data)
	{
		Var value = unpack(type<T>(), data);
		return val<T>(value);
	}
}
