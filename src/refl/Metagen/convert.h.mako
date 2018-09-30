
#pragma once

#include <${ module.subdir }/Types.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <refl/Meta.h>
#include <refl/Enum.h>
#include <infra/StringConvert.h>
#endif

namespace mud
{
    % for e in module.enums :
        % if e.reflect :
    export_ template <> inline void from_string(const string& str, ${ e.id }& val) { val = static_cast<${ e.id }>(enu<${ e.id }>().value(str.c_str())); };
    export_ template <> inline void to_string(const ${ e.id }& val, string& str) { str = enu<${ e.id }>().m_map[size_t(val)]; };
    
        % endif
    % endfor
    
    % for c in module.classes :
        % if c.array :
    export_ template <> inline void from_string(const string& str, ${ c.id }& val) { string_to_fixed_vector<${ c.id }, ${ c.array_content.id }>(str, val); };
    export_ template <> inline void to_string(const ${ c.id }& val, string& str) { fixed_vector_to_string<${ c.id }, ${ c.array_size }>(val, str); };
    
        % endif
    % endfor
}
