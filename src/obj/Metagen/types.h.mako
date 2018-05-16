#pragma once

#include <${ module.subdir }/Generated/Forward.h>

% for m in module.dependencies :
#include <${ m.subdir }/Generated/Types.h>
% endfor

#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>

% if module.has_structs :
#include <${ module.subdir }/Structs.h>
% endif

namespace mud
{
    // Exported types
    % for b in module.basetypes :
    template <> ${ module.export } Type& type<${ b.name }>();
    % endfor
    % for e in module.enums :
        % if not e.nested :
    template <> ${ module.export } Type& type<${ e.id }>();
        % endif
    % endfor
    % for s in module.sequences :
    template <> ${ module.export } Type& type<${ s.id }>();
    % endfor
    
    % for c in module.classes :
        % if c.isProto:
    template <> ${ module.export } Prototype& proto<${ c.id }>();
        % endif
        % if c.reflect and not c.nested and c.id != 'mud::Type' and c.id != 'mud::Prototype':
    template <> ${ module.export } Type& type<${ c.id }>();
        % endif
    % endfor
}
