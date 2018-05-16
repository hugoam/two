# mud [![Build Status](https://travis-ci.org/hugoam/mud.svg?branch=master)](https://travis-ci.org/hugoam/mud)

mud aims to be smallest and fastest c++ application prototyping library.  
it provides facilities which, in retrospect, you will never want to build an application **without**.  
mud is about all the code you **don't** want to write, and **should not have** to write, whenever prototyping an app.  
if there should be one central principle at the core of mud, that would be DRY : **don't repeat yourself**. like, **ever**. and we are dead serious about this.

it tries to improve on the somewhat depressing fact that, in many domains, state of the art modern programming is just riddled with redundant, superfluous code.  
mud tries to set different practices as a standard way to code. using these, we attain the quickest iteration speed.

here is a list of all the code you **never wanted to** write, and **won't need to** when using mud :
- ui library code
- debug and introspection ui code
- object serialization code
- scripting language binding code (e.g in-app console)

on top of that, because these are fundamental to any game prototype, we throw in :
- a visual scripting language
- low-level graphics pipeline implementation code

of course, in later stages, you could always want to write code that fits in either of these categories.  
the point of mud is, until you want to think about this, you don't want to have to think about this.  
using these features until you outgrow them doesn't cost anything, and once you do they don't either.

the purpose of mud is to maximize the potential of each line of code written, so that ideally, each of them is **only** concerned with the **problem domain** you are trying to solve, and not any of the auxiliary operations above.

mud is divided in 5 sub libraries, all small (between 5k and 10kloc each) :
- a object library, which sets the common primitives for manipulating dynamic objects
- a math library provides the glm math types and their reflection along with some common math operations
- a ui library allows to draw immediate-mode, skinnable, auto-layout ui panels in few lines of code
- a scripting library allows to call your c++ code from 
- a meta ui library provides ui elements to manipulate objects 

# quickstart
this is the minimal sample code you need to run a mud application
```c++
#include <mud/mud.h>

using namespace mud;

bool pump(Shell& app)
{
    // ui code goes here
    return app.pump();
}

int main(int argc, char *argv[])
{
    Shell app(EXEC_PATH, RESOURCE_PATH);

    bool pursue = true;
    while(pursue)
        pursue = pump(app);
}
```

# reflection
everything starts with your code : the domain specific problem you want to solve, the application business logic.  
in mud we start here, and not in intricate hierarchies of classes and components to inherit. as such mud is more alike to a programming language/idiom than a framework.

```c++
namespace app
{
    class _refl_ MyObject
    {
    public:
        _constr_ MyObject(int var, std::string field);
        
        _meth_ int method();

        _attr_ int m_var; 
        _attr_ std::string m_field;
        _attr_ std::vector<float> m_floats;
    };
    
    _func_ void foo(int arg);
    _func_ void bar(MyObject& object);
}
```

that code is gonna reside in a module, which you need to precompile to a reflection file, using mud reflection generator.  
from this point, you are allowed to manipulate the reflected classes, objects and functions in a completely generic and type-erased way.

the only step you need to do beforehand, is to initialize your module. mud won't do it for you, because of c++ static initialization order hell : modules could be initialized before the modules they depend on.
```c++
module::instance();
```

## operations
these are the different operations you can do on the generic reflection primitives :

call a function
```c++
Function& func = function(foo);
Var result = func({ var(5) });
```

store an object in a generic variable
```c++
MyObject object = { 12, 'cocorico' };
Var a = &object; // a holds generic reference to object
Var b = var(object); // b holds a copy of object
```

or create it generically
```c++
Type& type = cls<MyObject>();
Var object = create(type, { var(12), var(string("cocorico")) });
```

call a method
```c++
Method& meth = method(&MyObject::method);
Var result = meth(object, {});
```

get a member value
```c++
Member& mem = member(&MyObject::m_var);
Var var = mem.get(object);
```

set a member value
```c++
Member& mem = member(&MyObject::m_field);
mem.set(object, var("cocorico!"));
```

iterate a collection
```c++
Member& mem = member(&MyObject::m_floats);
Var var = mem.get(object);
iterate(var, [](const Var& element) { printf("%f\n", element.val<float>(); }); 
```

store multiple objects in a type-erased vector
```c++
std::vector<Var> objects = { var(5), var(34.13f), var(string("cocorico")), var(MyObject(15, "mud rocks")) };
iterate(var, [](const Var& element) { printf("%s, ", to_string(element); }); // prints 5, 34.13f, cocorico, 
```

## meta features
these were the low level generic operations that are defined to access the reflected types.  
mud builds on top of these, to provide you, for any of the reflected types and primitives :
- ui for creating, editing, saving, inspecting an object structure
- serialization facilities
- seamless integration with scripting languages (lua, visual scripting)

draw an inspector ui panel to edit properties of this object
```c++
AppObject object(12, 'cocorico');
inspector(parent, &object);
```

serialize any object to its json representation
```c++
std::string json = pack(object);
```

the resulting json will look like this
```json
{
    "var" : 5, 
    "field" : "cocorico",
    "floats" : [5.0, 32.3, 7.12]
}
```

deserialize any object from json
```c++
Type& type = cls<MyObject>();
Var object = unpack(type, json);
```

in a lua script you can use any of the reflected functions, types, methods, fields
```lua
local object = MyObject(5, 'hello world!')
print(object:method())
bar(object) -- you can even pass c++ objects to a function
```

run a lua script stored in a string
```c++
Script script = { lua_code };
script();
```

create a visual script in which all the reflected primitives can be used
```c++
VisualScript script = {};
```

add nodes to the visual script from c++
```c++
Valve& arg = script.value(5);
Valve& field = script.value(string("cocorico"));
script.create<MyObject>({ &arg, &field }); // adds a node that creates an object
```

this was a rough overview of all the meta features mud provides on top of your application code : more details on that later.  
now to use these features you need an actual running application.  
the first step to bootstrap an application is to actually create a window with a user interface.

# ui
mud ui uses a novel paradigm that sits halfway between **immediate** (like dear imgui) and **retained** ui (like Qt) : its API looks and feels exactly like an immediate ui library, except not much is *actually* done immediately. as such, we prefer to refer to it as a **declarative** ui.  
the final tree of widgets will look exactly like the tree of the declarations that is traversed on any given frame. however, events are processed, and rendering is done in a separate step.

the first step is creating a window
```c++
UiWindow ui_window = { "My App", 1600, 900 };
```

then on each iteration, you need to call the `begin()` function on the root widget
```c++
Widget& uroot = ui_window.m_root_widget.begin();
```

after that you can freely declare/draw all your widgets
```c++
Widget& window = ui::window(uroot, "My Window");
ui::label(window, "Welcome to mud ui");
if(ui::button(window, "Click me !"))
    printf("Button clicked !\n");
ui::color_edit(window, Colour(1.f, 0.34f, 0.73f));
```

the styles of all widgets are entirely customizable, through style sheets declared in the json format  
styles govern literally all aspects of :
- the layout of the widgets
- the appearance of the widgets

by switching between style sheets on the fly, you can instantly change the **whole** appearance of the ui

here is what a style sheet looks like
```json
```

you can also specify styles on a per-widget basis, by passing in a style parameter
```c++
Style style = {};
ui::button(parent, style, "Click me!");
```

# graphics
mud gfx library uses the same immediate paradigm as the ui. instead of nesting ui nodes (widgets) calls, you nest graphics nodes calls. as such it is perfect for quickly setting up some debug graphics rendering.

create a viewer to render into
```c++
SceneViewer& viewer = ui::scene_viewer(uroot);
Gnode& groot = viewer.m_scene.m_graph.begin();
```

draw a node, setting the transform for all children of this node
```c++
Gnode& gnode gfx::node(root, {}, vec3(0.f, 15.f, 7.5f));
```

draw a cube shape item
```c++
gfx::shape(gnode, Symbol(Colour::White), Cube());
```

draw a 3d model item
```c++
gfx::model(gnode, "my_3d_model.obj");
```

animate a model item
```c
Item& item = gfx::model(gnode, "my_3d_model.obj");
Animated& animated = gfx::animated(gnode, item);
animated.play("walk");
```

meta ui
=======

serialization
=============

scripting
=========
