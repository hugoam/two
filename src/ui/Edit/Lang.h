//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <stl/unordered_map.h>
#include <stl/map.h>
#include <ui/Forward.h>
#include <ui/Edit/TypeIn.h>

#ifndef MUD_CPP_20
#ifndef MUD_UNORDERED_MAP_TINYSTL
#include <unordered_set>
#endif
#include <regex>
#endif

namespace mud
{
	struct Identifier
	{
		uvec2 m_location;
		string m_declaration;
	};

	struct LanguageDefinition
	{
		string m_name;
		vector<string> m_punctuation;
		vector<string> m_operators;
#ifdef MUD_NO_STL
		unordered_map<string, void*> m_keywords;
#else
		std::unordered_set<string> m_keywords;
#endif
		unordered_map<string, Identifier> m_identifiers;
		unordered_map<string, Identifier> m_functions;
		unordered_map<string, Identifier> m_preproc_identifiers;
		string m_comment_start;
		string m_comment_end;

		vector<std::pair<string, PaletteIndex>> m_regex_string_tokens;
		vector<std::pair<std::regex, PaletteIndex>> m_regex_tokens;

		bool m_case_sensitive;
	};

	LanguageDefinition& LanguageCpp();
	LanguageDefinition& LanguageHLSL();
	LanguageDefinition& LanguageGLSL();
	LanguageDefinition& LanguageC();
	LanguageDefinition& LanguageLua();
	LanguageDefinition& LanguageWren();
}
