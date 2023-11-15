#pragma once

#include <infra/Config.h>

#ifndef TWO_MODULES
#include <ui/Forward.h>
#include <gfx/Forward.h>
#include <gfx-ui/Forward.h>
#endif

#ifndef TWO_FRAME_EXPORT
#define TWO_FRAME_EXPORT TWO_IMPORT
#endif

namespace two
{
	export_ struct ShellContext;
	export_ class ShellWindow;
    export_ class Shell;
}
