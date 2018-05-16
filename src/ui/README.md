Warning: kiUi is currently in a hiatus pending the publication of a wider set of libraries which it will be part of
Until then it is discouraged to try to use it

kiUi [![Build Status](https://travis-ci.org/hugoam/kiui.svg?branch=master)](https://travis-ci.org/hugoam/kiui)
====

kiUi is a lightweight auto-layout Ui library, abstracted out from any rendering or input code.

kiui supports Emscripten : try the live demo [here](http://hugoam.github.io/kiui/livedemo/kiui.html).

It is designed according to the following design goals :
- Separation of Ui appearance and logic
- Automatic layout as the norm, not the exception (as in HTML)
- Easy styling, separated from logic (as in CSS)
- Brevity and simplicity above everything else, especially in C++ code
- Good for both an editor Ui and a game Ui

![screenshot of the example window with a raw skin](media/kiui.png?raw=true)

Auto-Layout
===========

Every single element in kiUi auto-layouts ! You have nothing to do. No position to set, no size to determine.
- Code the logic : Just add your widgets and define the logic as you please.
- Code the appearance : Just set your fonts, font-size, images, and kiUi will do the rest.

The style can be defined and tweaked separately by an artist. Style are defined in C++ as of now, but Style Sheets are planned to come soon.

Skins
=====

kiUi was conceived so that each element can be styled in a way very similar to CSS, through Style Sheets
You can switch between Styles Sheets on the fly

![switching between styles at runtime](media/themes.gif?raw=true)

Usage
====
```C++
RootSheet& root = uiwindow.rootSheet();
Window& window = root.emplace<Window>("Example window");

Expandbox& expandbox = window.emplace<Expandbox>("Collapsable box");

Label& label = expandbox.emplace<Label>("kiUi says hello.");
Button& button = expand.emplace<Button>("Push me");
```

For a more in-depth usage example look at the full demo implementation : [Example](src/Ui/mkUiExample.cpp)

Nano
====

kiUi comes with a light renderer / input system based on NanoVG and GLFW to quickly bootstrap a prototype application in a few lines of code.

```C++
GlWindow glwindow(1200, 800, "mk UiEditApp");
glwindow.initContext();

UiWindow& uiwindow = glwindow.uiWindow();
bool pursue = true;
while(pursue)
    pursue = glwindow.renderFrame();
```

Widgets
=======

- Dockspace
- Tabber
- Table
- Window (resize, drag, dock)
- Radiobutton
- Dropdown


Editor
======

kiUi will come with a simple editor which also uses kiUi for its interface


## License
The library is licensed under [zlib license](LICENSE.txt)

## Links
Uses [nanovg](https://github.com/memononen/nanovg) for vector rendering
Uses [glfw](https://github.com/glfw/glfw) for OpenGL context management
