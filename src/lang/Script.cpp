//  Copyright (c) 2018 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.lang;
#else
#include <obj/Indexer.h>
#include <proto/Proto.h>
#include <lang/Types.h>
#include <lang/Script.h>
#include <lang/Lua.h>
#endif

namespace mud
{
	Script::Script(Type& type, cstring name, const Signature& signature)
		: Callable(name, signature.m_params, signature.m_returnval)
		, m_index(index(mud::type<Script>(), Ref(this, type)))
		, m_type(type)
		, m_name(name)
		, m_signature(signature)
	{
		m_signature.m_params = m_params;
	}

	Script::~Script()
	{
		unindex(type<Script>(), m_index);
	}

	TextScript::TextScript(cstring name, Language language, const Signature& signature)
		: Script(type<TextScript>(), name, signature)
		, m_language(language)
	{}

	void TextScript::operator()(array<Var> args, Var& result) const
	{
		for(const Param& param : m_signature.m_params)
		{
			m_interpreter->set(param.m_name, args[param.m_index]);
		}

		m_interpreter->call(m_script.c_str(), result.none() ? nullptr : &result);
	}

	ScriptClass::ScriptClass(const string& name, const std::vector<Type*>& parts)
		: m_name(name)
		, m_type(m_name.c_str())
		, m_class(m_type)
	{
		g_prototypes[m_type.m_id] = make_unique<Prototype>(m_class);
		for(Type* type : parts)
			g_prototypes[m_type.m_id]->add_part(*type);
	}
}
