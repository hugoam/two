<%!
def type_get(c):
    return 'type<' + c.id + '>()'

def type_get_pt(c):
    return '&type<' + c.id + '>()'
%>

#ifdef MUD_CPP_20
#include <cassert>
#include <cstdint>
#include <climits>
#include <cfloat>
import std.core;
import std.memory;
import std.threading;
import std.regex;
#endif

#include <${ module.subdir }/Generated/Types.h>
#include <${ module.subdir }/Generated/Module.h>
#include <obj/Proto.h>

namespace mud
{
    // Exported types
    % for b in module.basetypes :
    template <> ${ module.export } Type& type<${ b.name }>() { static Type ty("${ b.name }"); return ty; }
    % endfor
    % for e in module.enums :
    template <> ${ module.export } Type& type<${ e.id }>() { static Type ty("${ e.id }"); return ty; }
    % endfor
    % for s in module.sequences :
    template <> ${ module.export } Type& type<${ s.id }>() { static Type ty("${ s.id }"); return ty; }
    % endfor
    
    % for c in module.classes :
        % if c.reflect and c.isProto:
    template <> ${ module.export } Prototype& proto<${ c.id }>() { static Prototype ty("${ c.id }", ${ type_get(c.parts[0]) }, { ${ ', '.join([type_get_pt(part) for part in c.parts[1:]]) } }); return ty; }
    template <> ${ module.export } Type& type<${ c.id }>() { return proto<${ c.id }>(); }
        % elif c.reflect and not c.nested and c.id != 'mud::Type' and c.id != 'mud::Prototype':
    template <> ${ module.export } Type& type<${ c.id }>() { static Type ty("${ c.name }"${ ", " + type_get(c.bases[0]) if c.bases else '' }); return ty; }
        % endif
    % endfor
}
