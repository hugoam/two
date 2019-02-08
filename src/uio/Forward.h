#pragma once

#include <infra/Config.h>

#include <infra/Forward.h>
#include <tree/Forward.h>
#include <type/Forward.h>
#include <ecs/Forward.h>
#include <pool/Forward.h>
#include <refl/Forward.h>
#include <math/Forward.h>
#include <lang/Forward.h>
#include <ctx/Forward.h>
#include <ui/Forward.h>

#ifndef MUD_UIO_EXPORT
#define MUD_UIO_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum class EditNestMode : unsigned int;
    enum class EditorHint : unsigned int;
    
    
    class DispatchItem;
    struct SectionAction;
    struct Section;
    class DispatchSelector;
    struct EditSpec;
    class ScriptEditor;
    class DispatchInput;
}

#ifdef MUD_META_GENERATOR
namespace stl
{
	export_ extern template class refl_ seque_ vector<mud::Var>;
}
#endif
