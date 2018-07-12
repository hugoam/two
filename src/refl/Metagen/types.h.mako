#pragma once

#include <${ module.subdir }/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
#include <obj/Vector.h>
#endif

#ifndef MUD_MODULES
% for m in module.dependencies :
#include <${ m.subdir }/Types.h>
% endfor
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif

% if module.has_structs :
#include <${ module.subdir }/Structs.h>
% endif

namespace mud
{
    // Exported types
    % for b in module.basetypes :
    export_ template <> ${ module.export } Type& type<${ b.name }>();
    % endfor
    % for e in module.enums :
        % if not e.nested or e.reflect :
    export_ template <> ${ module.export } Type& type<${ e.id }>();
        % endif
    % endfor
    
    % for c in module.classes :
        % if c.reflect and not c.nested and c.id != 'mud::Type':
    export_ template <> ${ module.export } Type& type<${ c.id }>();
        % endif
    % endfor
    
    % for c in module.classes :
        % if c.reflect and not c.nested and c.id != 'mud::Type':
	export_ template struct ${ module.export } Typed<std::vector<${ c.id }*>>;
        % endif
    % endfor
}
