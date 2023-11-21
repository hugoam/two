#pragma once

#include <infra/Config.h>

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
