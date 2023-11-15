#pragma once

#include <infra/Config.h>

#ifndef TWO_MODULES
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
#endif

#ifndef TWO_UIO_EXPORT
#define TWO_UIO_EXPORT TWO_IMPORT
#endif

namespace two
{
    export_ enum class EditNestMode : unsigned int;
    export_ enum class EditorHint : unsigned int;

    export_ class DispatchItem;
    export_ class DispatchSelector;
    export_ struct EditSpec;
    export_ class ScriptEditor;
    export_ class DispatchInput;
}

#ifdef TWO_META_GENERATOR
namespace stl
{
	extern template class refl_ seque_ vector<two::Var>;
}
#endif
