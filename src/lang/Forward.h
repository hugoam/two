#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <type/Forward.h>
#include <pool/Forward.h>
#include <refl/Forward.h>

#ifndef TWO_LANG_EXPORT
#define TWO_LANG_EXPORT TWO_IMPORT
#endif

namespace two
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

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
}
#endif
