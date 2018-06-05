
#pragma once

#ifndef MUD_MODULES
#include <obj/System/System.h>

#include <obj/Generated/Module.h>
#include <srlz/Generated/Module.h>
#include <math/Generated/Module.h>
#include <geom/Generated/Module.h>
#include <lang/Generated/Module.h>
#include <ui/Generated/Module.h>
#include <uio/Generated/Module.h>
#include <gfx/Generated/Module.h>
#include <gfx-pbr/Generated/Module.h>
#endif
        
#include <edit/Generated/Forward.h>
#include <edit/Generated/Types.h>

#include <edit/Action.h>
#include <edit/ActionStack.h>
#include <edit/Brush.h>
#include <edit/EditContext.h>
#include <edit/Tool.h>
#include <edit/Viewport.h>
#include <edit/Tools/CopyTool.h>
#include <edit/Tools/RotateTool.h>
#include <edit/Tools/ScaleTool.h>
#include <edit/Tools/TranslateTool.h>
#include <edit/Tools/ViewTool.h>
#include <edit/Tools/WorkPlaneTool.h>
#include <edit/Ui/GfxEdit.h>
#include <edit/Ui/ParticleEdit.h>
#include <edit/Ui/PrefabEdit.h>
#include <edit/Viewer/SpaceSheet.h>
#include <edit/Viewer/SpaceViewer.h>
#include <edit/Viewer/Viewer.h>

namespace mud
{
	export_ class MUD_EDIT_EXPORT mudedit : public Module
	{
	private:
		mudedit();

	public:
		static mudedit& m() { static mudedit instance; return instance; }
	};
}

#ifdef MUD_EDIT_MODULE
extern "C"
MUD_EDIT_EXPORT Module& getModule();
#endif
