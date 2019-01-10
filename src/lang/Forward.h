

#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>
#include <pool/Forward.h>
#include <refl/Forward.h>

#ifndef MUD_LANG_EXPORT
#define MUD_LANG_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum class Language : unsigned int;
    enum StreamModifier : unsigned int;
    enum ValveKind : unsigned int;
    
    class Script;
    class TextScript;
	struct ScriptError;
    class Interpreter;
    class ScriptClass;
    class LuaInterpreter;
    struct StreamLocation;
    class StreamBranch;
    class Stream;
    class Valve;
    class Pipe;
    class Process;
    class VisualScript;
    class ProcessInput;
    class ProcessOutput;
    class ProcessValue;
    class ProcessCreate;
    class ProcessCallable;
    class ProcessScript;
    class ProcessFunction;
    class ProcessMethod;
    class ProcessGetMember;
    class ProcessSetMember;
    class ProcessDisplay;
    class WrenInterpreter;
}

namespace mud {
namespace detail {

    
    
}
}

namespace mud {
namespace gfx {

    
    
}
}

namespace bimg {

    
    
}

namespace bx {

    
    
}

