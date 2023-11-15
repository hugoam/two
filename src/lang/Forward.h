#pragma once

#include <infra/Config.h>

#ifndef TWO_MODULES
#include <infra/Forward.h>
#include <type/Forward.h>
#include <pool/Forward.h>
#include <refl/Forward.h>
#endif

#ifndef TWO_LANG_EXPORT
#define TWO_LANG_EXPORT TWO_IMPORT
#endif

namespace two
{
    export_ enum class Language : unsigned int;
    export_ enum StreamModifier : unsigned int;
    export_ enum ValveKind : unsigned int;
    
    export_ class Script;
    export_ class TextScript;
	export_ struct ScriptError;
    export_ class Interpreter;
    export_ class ScriptClass;
    export_ class LuaInterpreter;
    export_ struct StreamLocation;
    export_ class StreamBranch;
    export_ class Stream;
    export_ class Valve;
    export_ class Pipe;
    export_ class Process;
    export_ class VisualScript;
    export_ class ProcessInput;
    export_ class ProcessOutput;
    export_ class ProcessValue;
    export_ class ProcessCreate;
    export_ class ProcessCallable;
    export_ class ProcessScript;
    export_ class ProcessFunction;
    export_ class ProcessMethod;
    export_ class ProcessGetMember;
    export_ class ProcessSetMember;
    export_ class ProcessDisplay;
    export_ class WrenInterpreter;
}

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
}
#endif
