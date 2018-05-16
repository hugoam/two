# ui
mud ui uses a novel paradigm that sits halfway between **immediate** (like dear imgui) and **retained** ui (like Qt) :  
its API looks and feels exactly like an immediate ui library, except not much is *actually* done immediately.

as such, we refer to it as a **declarative** ui : the final tree of widgets maps exactly to the tree of declarations that is traversed on any given frame. however, events are processed, and rendering is done in a separate step.

to use mud ui you only need three things :
- create a [context](#context)
- each frame, declare your [widgets](#widgets)
- optionally, customize [styles](#styles)

# overview
mud ui library shines in the following aspects :
- **declarative/immediate** is the **simplest** and most powerful paradigm for writing ui
- **logic code** is separated from **layout and appearance code**, for clean ui code
- **layout is automatic**, no *manual* positioning or *sizing* is ever required
- widgets **appearance** and **layout** is completely determined by **styles**
- vector based skinning (borders, rounded corners, gradients, shadows)
- image based skinning (9-sprites)
- **one ui** for everything: games, tools, desktop apps, web apps
- **tiny** codebase (< 8kLoC)
- basic widgets : dropdown, slider, checkbox, text input, multiline text, filtered dropdown
- toolkit widgets : dockspace, dockable windows, tabs, dock sidebar, tables, trees

as soon as you need to create your own widgets, you need a theoretical understanding of the ui inner workings.
there are three main mechanisms at play in mud ui :
- the [layout system](#layout-system), computed by different solvers
- [events](#events) and their propagation
- how elements are [rendered](#rendering) and skinned

# quickstart
drawing the ui is started by calling `begin()` on the root ui widget, and [ui elements](#widgets) are produced as a hierarchy of nested calls : each component is a function call (`ui::sheet`, `ui::button`...) of which the first parameter is always the **parent**.

the first step is creating a [render system](), and a [ui window]() :
```c++
BgfxSystem render_system = {};
UiWindow& ui_window = render_system.create_window("My App", 800, 600, false);
```

on each iteration, you need to call the `begin()` function on the root widget :
```c++
Widget& ui = ui_window.m_ui.begin();
```

after that, declare/draw any widgets :
```c++
Widget& window = ui::window(ui, "My Window");
ui::label(window, "Welcome to mud ui");
if(ui::button(window, "Click me !"))
    printf("Button clicked !\n");
ui::color_edit(window, Colour(1.f, 0.34f, 0.73f));
```

# context
mud supports four context providers :
- [glfw](../src/ctx-glfw): cross-platform OpenGL context
- [windows](../src/ctx-win): native Windows context
- [emscripten](../src/ctx-wasm): native asmjs/WebAssembly context
- [ogre](../src/ctx-ogre): integration in the Ogre3d engine

you mostly don't need to touch these directly : contexts will be provided to you by a render system :
- [bgfx](../src/ctx-bgfx): lower level render system, on top of bgfx library (wraps all of the above)
- [gfx](../src/gfx): higher level gfx library

if you wish to only use mud up to the ui level, you must create a [bgfx render system](../src/ctx-bgfx/BgfxSystem.h) :
```c++
BgfxSystem render_system = {};
UiWindow& ui_window = render_system.create_window("My App", 800, 600, false);
```

if you wish to use mud gfx rendering library, just replace it with the [mud gfx render system](../src/gfx/GfxSystem.h) :
```c++
GfxSystem render_system = {};
UiWindow& ui_window = render_system.create_window("My App", 800, 600, false);
```

once this is done, your app is basically up and running  
you just need to update it each frame :
```c++
while(render_system->next_frame())
{
    // your application logic goes here
}
```

# widgets
to create a widget, call its function, the first parameter of which is always the **parent** it should be nested in.  
widgets taking a string or vector of string parameters representing their contents, display each string either as a label, or as an icon if it is of the form `(icon.png)`

## [basic widgets](../src/ui/Button/Button.h)
```c++
namespace ui
{
    Widget& icon(Widget& parent, const string& icon);
    Widget& label(Widget& parent, const string& label);
    Widget& text(Widget& parent, const string& label);
}
```

## [basic controls](../src/ui/Button/Button.h)
```c++
namespace ui
{
    Widget& button(Widget& parent, const string& content = "");
    Widget& multi_button(Widget& parent, const vector<string>& elements, Style* element_style = nullptr);
    
    Widget& toggle(Widget& parent, bool& on, const string& content = "");
    Widget& multi_toggle(Widget& parent, bool& on, const vector<string>& elements, Style* element_style = nullptr);
    
    Widget& checkbox(Widget& parent, bool& on);
}
```

## [sliders](../src/ui/Button/Slider.h)
```c++
namespace ui
{
    bool slider(Widget& parent, float& value, SliderMetrics metrics, Dim dim = DIM_X);
}
```

## [misc widgets](../src/ui/Button/Button.h)
```c++
namespace ui
{
    Widget& fill_bar(Widget& parent, float percentage, Dim dim = DIM_X);
}
```

## [selector widgets](../src/ui/Button/Button.h)
all selector widgets have a similar interface : they take a vector of string elements representing each choice, and they update an index parameter depending which is the currently selected choice

```c++
namespace ui
{
    bool radio_switch(Widget& parent, const vector<string>& labels, size_t& value);
    bool dropdown_input(Widget& parent, const vector<string>& choices, size_t& value, bool compact = false);
    bool typedown_input(Widget& parent, const vector<string>& choices, size_t& value);
}
```

## [text editor](../src/ui/TypeIn.h)
mud has a pretty full featured [text editor](../src/ui/TypeIn.h#L147) with mouse and keyboard selection, line numbers, undo and redo, syntax hilighting, on-hover tooltips, and auto-complete.

```c++
namespace ui
{
    TextEdit& type_in(Widget& parent, string& text, size_t lines = 1, const string& allowed_chars = "");
    TextEdit& text_edit(Widget& parent, string& text, size_t lines = 1, std::vector<string>* vocabulary = nullptr);
}
```

## [input widgets](../src/ui/Edit/Input.h)
there is a range of built-in input widgets :
`input<T>()` maps to number input for numbers, and to checkbox and textboxes for bool and string types

```c++
namespace ui
{
    template <class T>
    bool number_input(Widget& parent, T& value);
    
    template <class T>
    bool slider_input(Widget& parent, T& value);
    
    template <class T>
    bool input(Widget& parent, T& value);
}
```

## [popups and modals](../src/ui/Widget/Sheet.h)
```c++
namespace ui
{
    Widget& popup(Widget& parent, const vec2& position, bool modal);
    Widget& modal(Widget& parent);
}
```

## [toolbars](../src/ui/Button/Button.h)
```c++
namespace ui
{
    Widget& toolbutton(Widget& parent, const string& icon);
    Widget& tooldock(Widget& parent);
    Widget& toolbar(Widget& parent, bool wrap = false);
}
```
    
## [menus](../src/ui/Button/Button.h)
```c++
namespace ui
{
    Widget& menu_choice(Widget& parent, const vector<string>& elements);
    Widget& menu(Widget& parent, const string& label, bool submenu = false);
    Widget& menubar(Widget& parent);
}
```

## [containers](../src/ui/Container/Container.h)
```c++
namespace ui
{
    Table& table(Widget& parent, std::vector<string> columns, std::vector<float> weights);
}
```

```c++
namespace ui
{
    Expandbox& expandbox(Widget& parent, const vector<string>& elements, bool open = true);
    TreeNode& tree_node(Widget& parent, const vector<string>& elements, bool leaf = false, bool open = true);
}
```

```c++
namespace ui
{
    Widget* tab(Tabber& tabber, const string& name);
    Tabber& tabber(Widget& parent, bool downtabs = false);
}
```

## file browser
```c++
namespace ui
{
    Widget& file_browser(Widget& parent, string& path);
    Widget& file_tree(Widget& parent, const string& path);
}
```

## [windows](../src/ui/Window/Window.h)
```c++
namespace ui
{
    Window& window(Widget& parent, const string& title, WindowState state = WINDOW_DEFAULT);
}
```

## dock containers

## [nodes](../src/ui/Window/Node.h)
```c++
namespace ui
{
    Canvas& canvas(Widget& parent, const string& title, size_t num_nodes = 0);
    
    Node& node(Canvas& parent, const string& title, int order = 0);
    Node& node(Canvas& parent, const string& title, vec2& position, int order = 0);
    
    NodePlug& node_input(Node& node, const string& name, const string& icon, const Colour& colour, bool connected = false);
    NodePlug& node_output(Node& node, const string& name, const string& icon, const Colour& colour, bool connected = false);
}
```

# [layout system](../src/ui/Frame/Solver.h)
the first fundamental block of **mud ui** is the **layout system** : it dictates the positioning and sizing of **all** widgets on the screen.  
each widget in mud has a [frame](../src/ui/Frame/Frame.h) object : mostly a rectangle with a few additional properties.  
every frame that is in the [flow]() is automatically laid out by its parent [solver](), depending on both children and parent layout properties.

the most important properties governing layout are the following :
- [solver](../src/ui/Frame/Dim.h#L58) : which solver should be used to layout the children : 
  - `row solver`: the simple and ubiquitous solver : lays out its children in a sequence, and computes its size as the sum of its children sizes.
  - complex solvers are made of sub-solvers :
  - `grid solver`: lays out children in multiple rows according to a 2d index (x, y)
  - `table solver`: lays out children in rows vertically, and in columns horizontally
- [flow](../src/ui/Frame/Dim.h#L73) : whether or not the widget is part of the automatic layout flow.
  - `flow`: is in the parent flow = positioned and sized by the parent solver
  - `free`: not in the parent flow = positions itself, but sized by the parent (outside of the flow)
- [direction](../src/ui/Frame/Dim.h#L31) : the direction of the flow, in which the children are laid out. it can be either of :
  - relative : `orthogonal` or `parallel` to its parent own direction
  - absolute : `paragraph` or `reading`, meaning vertical or horizontal.
- [sizing](../src/ui/Frame/Dim.h#L81) : how the size of a widget is computed : one of `expand`, `shrink`, `content` or `wrap`
  - `expand` : takes all available space in the parent
  - `shrink` : shrinks to the total measured size of all children widgets in the [flow]()
  - `fixed` : determined by its content (a string or an image)
  - `wrap` : hybrid behavior, expanding as soon as there is available space, but wrapping the contents if space is minimal

aditionally, some more cosmetic layout attributes governs some sizing and positioning offsets :
- [span](../src/ui/Frame/Dim.h) : how much of the parent space an `expand` or `wrap` widget wants to occupy, as a ratio
- [padding](../src/ui/Frame/Dim.h) : an offset added **inside** the widget frame, padding it around its content
- [margin](../src/ui/Frame/Dim.h): an offset added **around** the widget frame when it laid out by its parent
- [spacing](../src/ui/Frame/Dim.h): an offset added **between each widget** positioned in the flow
- [pivot](../src/ui/Frame/Dim.h#L40): in which direction the solver sequences its children : `forward` or `reverse`
- [aligh](../src/ui/Frame/Dim.h#L46): where in the parent sequence should the widget be aligned

we believe the above set of properties and solvers is sufficiently wide, so that roughly any thinkable 2d layout of frames can be produced, while being quite simpler than the CSS layout rules.

all these properties are computed for each frame, by their widget [style](../src/ui/Frame/Style.h#L163), which holds a [layout](../src/ui/Frame/Style.h#L82) object.

# rendering

# [skin](../src/ui/Style/Style.h#L114)
if the layout of the frames is determined by the layout, the graphical appearance of the ui elements itself is determined by the [skin](../src/ui/Style/Style.h#L114).  
[styles](../src/ui/Style/Style.h#L163) hold both : a layout, a skin, and an additional list of skins affected to specific widget states.

the skin properties are *very* similar to CSS graphical properties :
- [background colour](../src/ui/Style/Style.h#L133), [border colour](../src/ui/Style/Style.h#L134), [text colour](../src/ui/Style/Style.h#L135): self-explanatory
- [text font](../src/ui/Style/Style.h#L136): self-explanatory
- [text break](../src/ui/Style/Style.h#L137): should the text be broken in lines when newlines are encountered
- [text wrap](../src/ui/Style/Style.h#L138): should the text wrap around the frame edges
- [border width](../src/ui/Style/Style.h#L139): four values, as in CSS (and in the same order: left, top, right, bottom)
- [corner radius](../src/ui/Style/Style.h#L140): four values, as in CSS (same order)
- [padding](../src/ui/Style/Style.h#L140): an offset added around the frame content (image/string)
- [margin](../src/ui/Style/Style.h#L140): an offset added around the frame content
- [align](../src/ui/Style/Style.h#L140): how the content aligns in the frame
- [image](../src/ui/Style/Style.h#L140): 
- [overlay](../src/ui/Style/Style.h#L140): an image applied as overlay
- [tile](../src/ui/Style/Style.h#L140): an image applied in a tiled repating pattern
- [image skin](../src/ui/Style/ImageSkin.h#L18): an image skin, defined by 9 sprites
- [shadow](../src/ui/Style/Style.h#L140): 
- [shadow colour](../src/ui/Style/Style.h#L140):
- [hover cursor](../src/ui/Style/Style.h#L140):


# [styles](../src/ui/Style/Style.h#L163)
a [style](../src/ui/Style/Style.h#L163) object contains a [layout](../src/ui/Frame/Style.h#L82) and [skin](../src/ui/Style/Style.h#L114) which are both applied to each widget set to this style.  
a **style** also holds some [additional skins](../src/ui/Style/Style.h#L163) that apply only to specific widget states.

all ui widgets have a [default style](../src/ui/Style/Style.h#L193), identified by having the same name as the widget:
in the following code the widget will use the style called `"button"`:
```c++
ui::button(parent, "Click me!");
```

most ui widgets have an overload allowing you to explicitly set a style as the second parameter :
```c++
static Style my_style = { "MyStyle" };
ui::button(parent, my_style, "Click me!");
```

in the lack of c++ designated initializers, we have a special syntax which allows us to use "named" arguments :
```c++
static Style my_style = { "MyStyle", Args{ { &Layout::m_space, BLOCK } } };
```

styles can be modified and created from code. but more interestingly, they can be modified all at once by loading a `json style sheet`.
by switching between style sheets on the fly, you can instantly change the **whole** appearance of the ui.
mud ui provides four default style sheets : `minimal`, `vector`, `blendish` and `blendish dark`.

to load a style sheet, use the following parser [functions](../src/ui/Style/StyleParser.h#L13) :
```c++
ui::set_style_sheet(ui_window.m_styler, ui_window.m_resource_path + "interface/styles/minimal.json");
```

a [json style sheet](../data/interface/styles/minimal.yml) consists mainly of a sequence of selectors, each one setting some attributes of the selected styles (indiscriminately of whether it's a layout or a skin attribute) :  
```json
{   
    "selector" : "Tooltip, Popdown, DropdownList, MenuList, SubMenuList",
    "background_colour" : [1.0, 0.43, 0.7, 1],
    "border_colour" : { "r": 1.0, "g": 0.43, "b": 0.7 },
    "text_colour" : "ClearGreyText"
},
```
notice how attributes can be either set as a list of arguments (of their type constructor), or as a named object.  
colours in particular can also be identified by a name, referencing colours indexed in the [colours](../data/interface/styles/minimal.yml) section at the top of the style sheet.

to set attributes for a specific widget states, the syntax is the following :
```json
{   
    "selector" : "Button", 
    "hovered" : {
        "background_colour" : "Grey312"
    }
}
```

# [events](../src/ctx/InputEvent.h)
in general, events are dispatched in the following way :
- mouse events are dispatched to the top-most `OPAQUE` widget under the mouse cursor.
- key events are dispatched to the widget that has focus / is modal for the given input device.

to check for an event after you declared a widget, use the [following functions](https://github.com/hugoam/mud/blob/master/src/ui/Structs/Widget.h#L69) on the `Widget` object :
```c++
KeyEvent key_event(KeyCode code, EventType event_type, InputModifier modifier = InputModifier::Any);
KeyEvent key_event(KeyCode code, InputModifier modifier = InputModifier::Any);
MouseEvent mouse_event(DeviceType device, EventType event_type, InputModifier modifier = InputModifier::None, bool consume = true);
```

the returned object evaluates to true the widget received an event of this type, so the calling code usually looks like so :
```c++
if(MouseEvent mouse_event = self.mouse_event(DeviceType::MouseLeft, EventType::Pressed))
{
    // handle the event
}
```
