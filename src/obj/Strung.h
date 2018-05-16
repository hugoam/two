//  Copyright (c) 2016 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#pragma once

#include <obj/Generated/Forward.h>
#include <string.h>

namespace mud
{
	using cstring = const char*;

	struct _refl_ MUD_OBJ_EXPORT strung
	{
		_constr_ strung() : m_buffer("") {}
		_constr_ strung(cstring str) : m_buffer("") { strcpy(m_buffer, str); }
		char m_buffer[256];
		const char* c_str() const { return m_buffer; }
		bool operator==(const strung& other) const;
		bool operator==(const char* other) const;
		operator const char*() const { return m_buffer; }
	};
}
