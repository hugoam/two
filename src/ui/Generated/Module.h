
#pragma once

#include <obj/System/System.h>

#include <obj/Generated/Module.h>
#include <math/Generated/Module.h>
#include <ctx/Generated/Module.h>
        
#include <ui/Generated/Forward.h>
#include <ui/Generated/Types.h>

#include <ui/Button.h>
#include <ui/Container.h>
#include <ui/Cursor.h>
#include <ui/Dock.h>
#include <ui/Image.h>
#include <ui/ImageAtlas.h>
#include <ui/Input.h>
#include <ui/Node.h>
#include <ui/Scrollbar.h>
#include <ui/ScrollSheet.h>
#include <ui/Sheet.h>
#include <ui/Slider.h>
#include <ui/Ui.h>
#include <ui/UiWindow.h>
#include <ui/User.h>
#include <ui/Widget.h>
#include <ui/Window.h>
#include <ui/Controller/Controller.h>
#include <ui/Edit/Console.h>
#include <ui/Edit/Directory.h>
#include <ui/Edit/Lang.h>
#include <ui/Edit/TypeIn.h>
#include <ui/Frame/Caption.h>
#include <ui/Frame/Dim.h>
#include <ui/Frame/Frame.h>
#include <ui/Frame/Layer.h>
#include <ui/Frame/Solver.h>
#include <ui/Frame/UiRect.h>
#include <ui/Render/Renderer.h>
#include <ui/Structs/Container.h>
#include <ui/Structs/Dock.h>
#include <ui/Structs/Node.h>
#include <ui/Structs/RootSheet.h>
#include <ui/Structs/Widget.h>
#include <ui/Structs/Window.h>
#include <ui/Style/9Sprite.h>
#include <ui/Style/Layout.h>
#include <ui/Style/Paint.h>
#include <ui/Style/Skin.h>
#include <ui/Style/Style.h>
#include <ui/Style/StyleParser.h>
#include <ui/Style/Styler.h>
#include <ui/Style/Styles.h>

namespace mud
{
	class MUD_UI_EXPORT mudui : public Module
	{
	private:
		mudui();

	public:
		static mudui& module() { static mudui instance; return instance; }
	};
}

#ifdef MUD_UI_MODULE
extern "C"
MUD_UI_EXPORT Module& getModule();
#endif
