#include <assert.h>
#include <stdint.h>
#include <limits.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include <obj/Config.h>

export module mud.edit;
import std.core;
import std.io;
import std.threading;
import std.regex;

export import mud.obj;
export import mud.srlz;
export import mud.math;
export import mud.geom;
export import mud.lang;
export import mud.ui;
export import mud.uio;
export import mud.gfx;
export import mud.gfxpbr;

#ifdef MUD_OBJ_LIB
#include <obj/Cls.h>
#include <obj/Strung.h>
#endif

#include <edit/Generated/Module.h>

//#include <edit/Action.h>
//#include <edit/ActionStack.h>
//#include <edit/Brush.h>
//#include <edit/EditContext.h>
//#include <edit/Tool.h>
//#include <edit/Viewport.h>
//#include <edit/Tools/CopyTool.h>
//#include <edit/Tools/RotateTool.h>
//#include <edit/Tools/ScaleTool.h>
//#include <edit/Tools/TranslateTool.h>
//#include <edit/Tools/ViewTool.h>
//#include <edit/Tools/WorkPlaneTool.h>
//#include <edit/Ui/GfxEdit.h>
//#include <edit/Ui/ParticleEdit.h>
//#include <edit/Ui/PrefabEdit.h>
//#include <edit/Viewer/SpaceSheet.h>
//#include <edit/Viewer/SpaceViewer.h>
//#include <edit/Viewer/Viewer.h>
