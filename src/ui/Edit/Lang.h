//  Copyright (c) 2019 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <ui/Forward.h>
#include <ui/Edit/TypeIn.h>

namespace two
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
		unordered_set<string> m_keywords;
		unordered_map<string, Identifier> m_identifiers;
		unordered_map<string, Identifier> m_functions;
		unordered_map<string, Identifier> m_preproc_identifiers;
		string m_comment_start;
		string m_comment_end;

		struct StringToken { string token; PaletteIndex color; };
		struct RegexToken { std::regex token; PaletteIndex color; };
		vector<StringToken> m_regex_string_tokens;
		vector<RegexToken> m_regex_tokens;

		bool m_case_sensitive;
	};

	export_ LanguageDefinition& LanguageCpp();
	export_ LanguageDefinition& LanguageHLSL();
	export_ LanguageDefinition& LanguageGLSL();
	export_ LanguageDefinition& LanguageC();
	export_ LanguageDefinition& LanguageLua();
	export_ LanguageDefinition& LanguageWren();
}
