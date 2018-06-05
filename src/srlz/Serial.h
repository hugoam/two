//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef MUD_MODULES
#include <obj/Any.h>
#include <obj/Util/Dispatch.h>
#endif
#include <srlz/Generated/Forward.h>

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <map>
#endif

namespace json11
{
	class Json;
}

export_ using json = json11::Json;

namespace mud
{
	using string = std::string;

	export_ class MUD_SRLZ_EXPORT FromJson : public Dispatch<void, Ref&, const json&>
	{
	public:
		FromJson();
	};

	export_ class MUD_SRLZ_EXPORT ToJson : public Dispatch<void, json&>
	{
	public:
		ToJson();
	};

	using JsonVisitor = std::function<void(json&)>;

	MUD_SRLZ_EXPORT void parse_json_file(const string& path, json& data);
	MUD_SRLZ_EXPORT void dump_json_file(const string& path, const json& data);
	MUD_SRLZ_EXPORT void visit_json(json& value, const JsonVisitor& visitor);

	MUD_SRLZ_EXPORT Var unpack(Type& type, const json& data);
	MUD_SRLZ_EXPORT Var unpack(FromJson& unpacker, Type& type, const json& data, bool typed = false);
	MUD_SRLZ_EXPORT void unpack(Var& value, const json& data);
	MUD_SRLZ_EXPORT void unpack(Ref value, const json& data);
	MUD_SRLZ_EXPORT void unpack(FromJson& unpacker, Var& value, const json& data, bool typed = false);

	MUD_SRLZ_EXPORT Var unpack_typed(const json& data);
	MUD_SRLZ_EXPORT Var unpack_typed(FromJson& unpacker, const json& data);

	MUD_SRLZ_EXPORT void pack(const Var& value, json& data);
	MUD_SRLZ_EXPORT void pack(ToJson& packer, const Var& value, json& data, bool typed = false);

	MUD_SRLZ_EXPORT void pack_typed(const Var& value, json& data);
	MUD_SRLZ_EXPORT void pack_typed(ToJson& packer, const Var& value, json& data);

	template <class T>
	T unpackt(const json& data)
	{
		Var value = unpack(type<T>(), data);
		return val<T>(value);
	}

	MUD_SRLZ_EXPORT string pack_json(const Var& value);
	MUD_SRLZ_EXPORT void unpack_json_file(Ref value, const string& path);
}