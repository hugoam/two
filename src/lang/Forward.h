

#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <obj/Forward.h>
#include <pool/Forward.h>
#include <refl/Forward.h>

#ifndef MUD_LANG_EXPORT
#define MUD_LANG_EXPORT MUD_IMPORT
#endif


    
    

namespace std {

    
    
}

namespace glm {

    
    
}

namespace json11 {

    
    
}

namespace mud {

    enum StreamModifier : unsigned int;
    enum ValveKind : unsigned int;
    
    
    class LuaInterpreter;
    class Script;
    class LuaScript;
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
}

namespace mud {
namespace detail {

    
    
}
}

