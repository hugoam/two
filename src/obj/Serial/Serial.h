//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <obj/Any.h>
#include <obj/Util/Dispatch.h>

#ifndef MUD_META_GENERATOR
#include <json.hpp>
using nlohmann::json;
#else
struct json;
#endif

#include <string>

namespace mud
{
	using string = std::string;

	class MUD_OBJ_EXPORT FromJson : public Dispatch<void, Ref&, const json&>
	{
	public:
		FromJson();
	};

	class MUD_OBJ_EXPORT ToJson : public Dispatch<void, json&>
	{
	public:
		ToJson();
	};

	using JsonVisitor = std::function<void(json&)>;

	MUD_OBJ_EXPORT std::vector<uint8_t> read_binary_file(const string& path);
	MUD_OBJ_EXPORT string read_text_file(const string& path);

	MUD_OBJ_EXPORT json parse_json_file(const string& path);
	MUD_OBJ_EXPORT void dump_json_file(const string& path, const json& data);
	MUD_OBJ_EXPORT void visit_json(json& value, const JsonVisitor& visitor);

	MUD_OBJ_EXPORT Var unpack(Type& type, const json& data);
	MUD_OBJ_EXPORT Var unpack(FromJson& unpacker, Type& type, const json& data, bool typed = false);
	MUD_OBJ_EXPORT void unpack(FromJson& unpacker, Var& value, const json& data, bool typed = false);

	MUD_OBJ_EXPORT Var unpack_typed(const json& data);
	MUD_OBJ_EXPORT Var unpack_typed(FromJson& unpacker, const json& data);

	MUD_OBJ_EXPORT json pack(const Var& value);
	MUD_OBJ_EXPORT void pack(const Var& value, json& data);
	MUD_OBJ_EXPORT void pack(ToJson& packer, const Var& value, json& data, bool typed = false);

	MUD_OBJ_EXPORT void pack_typed(const Var& value, json& data);
	MUD_OBJ_EXPORT void pack_typed(ToJson& packer, const Var& value, json& data);

	template <class T>
	T unpackt(const json& data)
	{
		Var value = unpack(type<T>(), data);
		return val<T>(value);
	}

	MUD_OBJ_EXPORT string pack_json(const Var& value);
}
