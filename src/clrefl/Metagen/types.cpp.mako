<%!
def type_get(c):
    return 'type<' + c.id + '>()'

def type_get_pt(c):
    return '&type<' + c.id + '>()'
%>

#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module ${ module.namespace }.${ module.name };
#else
#include <${ module.subdir }/Types.h>
#include <${ module.subdir }/Api.h>
#include <type/Vector.h>
//#include <ecs/Proto.h>
#endif

namespace mud
{
    // Exported types
    % for b in module.basetypes :
    template <> ${ module.export } Type& type<${ b.name }>() { static Type ty("${ b.name }"); return ty; }
    % endfor
    % for e in module.enums :
    template <> ${ module.export } Type& type<${ e.id }>() { static Type ty("${ e.id }"); return ty; }
    % endfor
    
    % for c in module.classes :
        % if c.reflect and not c.nested and c.id != 'mud::Type':
    template <> ${ module.export } Type& type<${ c.id }>() { static Type ty("${ c.name }"${ ", " + type_get(c.bases[0]) if c.bases else '' }); return ty; }
        % endif
    % endfor
}
