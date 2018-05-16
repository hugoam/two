

#pragma once

#include <obj/Config.h>

#include <obj/Generated/Forward.h>
#include <lang/Generated/Forward.h>
#include <ui/Generated/Forward.h>

#if defined MUD_UIO_LIB
#define MUD_UIO_EXPORT MUD_EXPORT
#else
#define MUD_UIO_EXPORT MUD_IMPORT
#endif


    
    

namespace std {

    
    
}

namespace mud {
namespace ui {

    
    
}
}

namespace glm {

    
    
}

namespace mud {

    enum class EditorHint : unsigned int;
    
    
    struct SectionAction;
    struct Section;
    class ScriptEditor;
    class DispatchInput;
}

namespace mud {
namespace detail {

    
    
}
}

