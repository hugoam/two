//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#ifndef TWO_MODULES
#include <stl/string.h>
#include <type/Dispatch.h>
#include <type/Var.h>
#endif
#include <srlz/Forward.h>

#ifndef TWO_MODULES
namespace json11
{
	class Json;
}
#endif

namespace two
{
	export_ using Json = json11::Json;

	export_ class TWO_SRLZ_EXPORT FromJson : public Dispatch<void, const Json&>
	{
	public:
		FromJson();
	};

	export_ class TWO_SRLZ_EXPORT ToJson : public Dispatch<void, Json&>
	{
	public:
		ToJson();
	};

	export_ TWO_SRLZ_EXPORT void parse_json_file(const string& path, Json& data);
	export_ TWO_SRLZ_EXPORT void dump_json_file(const string& path, const Json& data);

#if 0
	export_ using JsonVisitor = std::function<void(Json&)>;
	export_ TWO_SRLZ_EXPORT void visit_json(Json& value, const JsonVisitor& visitor);
#endif

	export_ TWO_SRLZ_EXPORT Var unpack(Type& type, const Json& data);
	export_ TWO_SRLZ_EXPORT Var unpack(FromJson& unpacker, Type& type, const Json& data);
	export_ TWO_SRLZ_EXPORT void unpack(Var& value, const Json& data);
	export_ TWO_SRLZ_EXPORT void unpack(Ref value, const Json& data);
	export_ TWO_SRLZ_EXPORT void unpack(FromJson& unpacker, Var& value, const Json& data);
	export_ TWO_SRLZ_EXPORT void unpack(FromJson& unpacker, Ref value, const Json& data);

	export_ TWO_SRLZ_EXPORT Var unpack_typed(const Json& data);
	export_ TWO_SRLZ_EXPORT Var unpack_typed(FromJson& unpacker, const Json& data);

	export_ TWO_SRLZ_EXPORT void pack(const Var& value, Json& data);
	export_ TWO_SRLZ_EXPORT void pack(ToJson& packer, const Var& value, Json& data, bool typed = false);

	export_ TWO_SRLZ_EXPORT void pack_typed(const Var& value, Json& data);
	export_ TWO_SRLZ_EXPORT void pack_typed(ToJson& packer, const Var& value, Json& data);

	export_ template <class T>
	T unpackt(const Json& data);

	export_ TWO_SRLZ_EXPORT string pack_json(const Var& value);

	export_ TWO_SRLZ_EXPORT void pack_json_file(const Var& value, const string& path);
	export_ TWO_SRLZ_EXPORT void pack_json_file(ToJson& packer, const Var& value, const string& path);
	export_ TWO_SRLZ_EXPORT void unpack_json_file(Ref value, const string& path);
}
