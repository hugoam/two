<p align="center"><img src="https://github.com/hugoam/two/blob/master/media/libtwo0.png" /></p>

# [two](https://github.com/hugoam/two)

| CI            | Community     | Support   |
| ------------- | ------------- | --------- |
[![Build Status](https://travis-ci.org/hugoam/two.svg?branch=master)](https://travis-ci.org/hugoam/two) [![Build status](https://ci.appveyor.com/api/projects/status/4a77n3scl71ybcgj?svg=true)](https://ci.appveyor.com/project/hugoam/two) | [![Community](https://img.shields.io/discourse/https/discourse.toyengine.io/posts.svg)](https://discourse.toyengine.io) [![Gitter](https://badges.gitter.im/hugoam/two.svg)](https://gitter.im/hugoam/two) | [![Patreon](https://img.shields.io/badge/donate-patreon-orange.svg)](https://www.patreon.com/bePatron?u=11301355)

two is an all-purpose c++ app prototyping library, focused towards live graphical apps and games.  
two contains all the essential building blocks to develop lean c++ apps from scratch, providing [reflection](#reflection) and low level [generic](#generic-features) algorithms, an [immediate ui](#ui) paradigm, and an immediate minimalistic and flexible [graphics renderer](#graphics).

two aims to provide the *quickest idioms* to build functional and lightweight c++ graphical applications. It tackles the problem of the code you *don't* want to write, and *should not have* to write when prototyping an app. One core principle in two is : *don't repeat yourself*: we take this aim very seriously and we believe it's a principle that is way too often disregarded.

two consists of a set of 6 small, self-contained libraries rather than a single one: 6 building blocks essential to prototyping any c++ app.  

The first set of blocks, consists of low level c++ programming tools, which purpose is to avoid duplicating code over and over, by providing [generic algorithms](https://github.com/hugoam/two#generic-features) instead, operating on generic objects. Their aim is that ideally, each line of code you have to write is *only* concerned with the *problem domain* you are trying to solve, and not lower-level auxiliary operations.

These are the three low-level generic c++ blocks: they rely on applying generic operations on arbitrary types:
- [reflection](#reflection) of any c++ code to a set of generic primitives
- [generic serialization](docs/serial.md) of any c++ objects to any format (currently json)
- [generic script](docs/scripting.md) bindings for any c++ objects, methods, functions, seamlessly, **and** a visual scripting language

The second set of blocks consists of the the interactive/graphical foundation of an app:
- immediate/declarative UI to draw skinnable, auto-layout ui panels in few lines of code
- immediate/declarative graphics to render 3d objects in a minimal amount of code

The last one ties the ui and the generic c++ blocks together:
- generic ui to edit and inspect c++ objects, modules, call methods, edit text and visual scripts

**two** stems from a strong programming philosophy: it wagers that the future of application and game coding lies in small, self-contained, reusable and shared libraries, and **not** in gigantic tightly coupled *engines* of hundreds thousands of lines of code.

For our shared knowledge and our programs to progress, the building blocks have to be **small** and **understandable by most** (which is essentially the same thing). There are many such blocks already in many domains (network, pathfinding, database, graphics).

I started writing two because I discovered some of the blocks I needed were missing. The common thread between these blocks, is an unrelenting thirst for simplicity. With the building blocks two provides, one can create live graphical apps in few lines of code, but also, **anyone** can potentially create a *game engine*.

**two** is open-source, and published under the zlib license: as such it is looking for sponsors, funding, and your support through [patreon](https://www.patreon.com/libmud).

# domains
Here is a slightly more in-depth description of each of two core components :
- [a small generic c++ layer](https://github.com/hugoam/two/blob/master/docs/reflection.md) (< 5 kLoC): c++ primitives that allow manipulating generic objects at runtime, and precompilation of any c++ code to an initializer for these primitives.
- [a small generic serialization layer](https://github.com/hugoam/two/blob/master/docs/serial.md) (< 1 kLoC): serialize generic c++ objects from and to different formats. two does only json (and previously sqlite), but some binary formats like flat buffers should be studied (although they usually have their own code generation).
- [a small generic scripting library](https://github.com/hugoam/two/blob/master/docs/scripting.md) (< 3 kLoC): manipulate generic c++ objects through scripts. all reflected primitives: functions, methods, members can be used seamlessly. two does only lua, and a powerful graph based visual scripting language.
- [a small UI library](https://github.com/hugoam/two/blob/master/docs/ui.md) (< 10 kLoC) that does: immediate-mode widget declarations, logic/layout/styling separation, fully automatic layout, css-like skinning, image-based skinning, style sheets, input widgets, docking windows and tabs, allows to define complex widgets easily.
- [a small graphics library](https://github.com/hugoam/two/blob/master/docs/graphics.md) (< 6 kLoC): immediate-mode rendering graph declaration, with the following basic primitives: meshes, models, shaders, programs, materials, skeletons, animations, render targets, filters, render passes, render pipelines. It is minimalistic in design, and is **NOT a game engine** nor does it try to be.
- [a small ui inspection library](https://github.com/hugoam/two/blob/master/docs/inspector.md) (< 3 kLoC): generic ui components: inspector panel, edit an object fields, call a method on an object, inspect an object graph/structure, all these are generic ui components operating on the reflected primitives.
- [a small pbr rendering model]() (< 4 kLoC): a sample implementation of a physically based rendering model for the above graphics library, demonstrating it can be simple (it's the research behind that is complex).

# building
two is built with [GENie](https://github.com/bkaradzic/GENie) build system, which is based on premake and consists of a bunch of lua scripts. The GENie binaries needed by two for windows and linux are included for convenience in the `bin` folder.  
To get a headstart and build two you should clone this repository, and run GENie which will generate projects for two libraries and for the examples.

The build instructions for linux and gcc look like:
- `git clone --recursive https://github.com/hugoam/two`
- `cd two`
- for linux (make):
  - `bin/linux/genie --gcc=linux-gcc gmake`
  - `cd build/projects/gmake-linux`
  - `make config=debug64 -j8`
- for osx (make): `bin/darwin/genie --gcc=osx gmake`
- for osx (xcode): `bin/darwin/genie --xcode=osx xcode9`
- for windows (visual studio): `bin/windows/genie vs2017`

# quickstart
This is the minimal sample code you need to run a two application
```c++
#include <two/two.h>

using namespace two;

bool pump(Shell& app)
{
    // ui code goes here
    return app.pump();
}

int main(int argc, char *argv[])
{
    Shell app(RESOURCE_PATH);
    app.run(pump);
}
```

# [reflection](docs/reflection.md)
Everything starts with your code : the domain specific problem you want to solve, the application business logic.  
In two we start here, and not in intricate hierarchies of classes and components to inherit. As such two is more alike to a programming language/idiom than a framework.

```c++
namespace app
{
    class refl_ MyObject
    {
    public:
        constr_ MyObject(int var, std::string field);
        
        meth_ int method();

        attr_ int m_var; 
        attr_ std::string m_field;
        attr_ std::vector<float> m_floats;
    };
    
    func_ void foo(int arg);
    func_ void bar(MyObject& object);
}
```

That code is gonna reside in a module, which you need to precompile to a reflection file, using two reflection generator.  
From this point, you are allowed to manipulate the reflected classes, objects and functions in a completely generic and type-erased way:

```c++
// call a generic function
Var result = function(foo)({ var(5) });

MyObject object = { 12, 'cocorico' };
// create generic values and references
Var a = &object;        // a holds generic reference to object
Var b = var(object);    // b holds a copy of object

// construct an object generically
Var c = construct(type<MyObject>(), { var(12), var(string("cocorico")) });

// call a generic object method
Var result = method(&MyObject::method)(object, {});

// get and set a generic object member
Var member = member(&MyObject::m_var).get(object);
member(&MyObject::m_field).set(object, var("cocorico!"));

// iterate a generic collection
Var collection = member(&MyObject::m_floats).get(object);
iterate(var, [](const Var& element) { printf("%f\n", element.val<float>(); });

// create a generic collection
std::vector<Var> objects = { var(5), var(34.13f), var(string("cocorico")), var(MyObject(15, "two rocks")) };
iterate(var, [](const Var& element) { printf("%s, ", to_string(element); }); // prints 5, 34.13f, cocorico, 
```

# [generic features]()
two builds on top of these low level generic operations to provide, for any of the reflected types and primitives:
- [ui components](docs/inspector.md) for creating, editing, saving, inspecting an object structure
- [serialization](docs/serial.md) facilities
- [scripting](docs/scripting.md) languages seamless integration with languages (lua, visual scripting)

Here are a few examples of how using these features looks:
```cpp
AppObject object(12, 'cocorico');
// draw an inspector ui panel to edit this object
ui::inspector(parent, &object);

// serialize and deserialize any object to and from its json representation
std::string json = slz::pack(object);
Var object = slz::unpack(type<MyObject>(), json);
```

In a lua script you can use any of the reflected functions, types, methods, fields
```lua
local object = MyObject(5, 'hello world!')
print(object:method())
bar(object) -- you can even pass c++ objects to a function
```

Add nodes to the visual script from c++
```c++
Valve& arg = script.value(5);
Valve& field = script.value(string("cocorico"));
script.create<MyObject>({ &arg, &field }); // adds a node that creates an object
```

Now to use these features you need an actual running application.  
The first step to bootstrap an application is to actually create a window with a user interface.

# [ui](docs/ui.md)
two ui uses a novel paradigm that sits halfway between **immediate** (like dear imgui) and **retained** ui (like Qt) : its API looks and feels exactly like an immediate ui library, except not much is *actually* done immediately. As such, we prefer to refer to it as a **declarative** ui.  
The final tree of widgets will look exactly like the tree of the declarations that is traversed on any given frame. however, events are processed, and rendering is done in a separate step.

Once you have setup a window and called the `begin()` function on the root widget on each iteration, you can freely declare/draw all your widgets:
```c++
Widget& window = ui::window(uroot, "My Window");
ui::label(window, "Welcome to two ui");
if(ui::button(window, "Click me !"))
    printf("Button clicked !\n");
ui::color_edit(window, Colour(1.f, 0.34f, 0.73f));
```

The styles of all widgets are entirely customizable, through style sheets declared in the json format  
styles govern literally all aspects of :
- the layout of the widgets
- the appearance of the widgets

By switching between [style sheets]() on the fly, you can instantly change the **whole** appearance of the ui

You can also specify styles on a per-widget basis, by passing in a style parameter
```c++
Style style = {};
ui::button(parent, style, "Click me!");
```

# [graphics](graphics.md)
two gfx library uses the same immediate paradigm as the ui. instead of nesting ui nodes (widgets) calls, you nest graphics nodes calls. as such it is perfect for quickly setting up some debug graphics rendering.

```c++
// create a viewer to render into
SceneViewer& viewer = ui::scene_viewer(uroot);
Gnode& groot = viewer.m_scene.m_graph.begin();

// draw a node, which transform applies to children of this node
Gnode& gnode gfx::node(root, {}, vec3(0.f, 15.f, 7.5f));

// draw a cube shape item as a child of node
gfx::shape(gnode, Symbol(Colour::White), Cube());

// draw a 3d model item as a child of node
Item& item = gfx::model(gnode, "my_3d_model.obj");

// animate a model
Animated& animated = gfx::animated(gnode, item);
animated.play("walk");
```

# examples

## [pbr materials](https://hugoam.github.io/two-io/examples/03_materials_low.html)
![pbr materials](https://github.com/hugoam/two-io/blob/master/media/03_materials.png)

## [lights](https://hugoam.github.io/two-io/examples/04_lights.html)
![lights](https://github.com/hugoam/two-io/blob/master/media/04_lights.png)

## [sponza (.obj import)](https://hugoam.github.io/two-io/examples/04_sponza.html)
![sponza (.obj import)](https://github.com/hugoam/two-io/blob/master/media/04_sponza.png)

## [character (animations)](https://hugoam.github.io/two-io/examples/05_character.html)
![character (animations)](https://github.com/hugoam/two-io/blob/master/media/05_character.png)

## [particles](https://hugoam.github.io/two-io/examples/06_particles.html)
![particles](https://github.com/hugoam/two-io/blob/master/media/06_particles.png)

## [gltf](https://hugoam.github.io/two-io/examples/07_gltf.html)
![gltf](https://github.com/hugoam/two-io/blob/master/media/07_gltf.png)

## [sky (perez model)](https://hugoam.github.io/two-io/examples/08_sky.html)
![sky (perez model)](https://github.com/hugoam/two-io/blob/master/media/08_sky.png)

## [live shader](https://hugoam.github.io/two-io/examples/09_live_shader.html)
![live shader](https://github.com/hugoam/two-io/blob/master/media/09_live_shader.png)

## [live graphics](https://hugoam.github.io/two-io/examples/14_live_gfx.html)
![live graphics](https://github.com/hugoam/two-io/blob/master/media/14_live_gfx.png)

## [live graphics (visual script)](https://hugoam.github.io/two-io/examples/4_live_gfx_visual.html)
![live graphics (visual script)](https://github.com/hugoam/two-io/blob/master/media/14_live_gfx_visual.png)

# credits
two couldn't exist without:
- [GENie](https://github.com/bkaradzic/GENie) build system
- [bgfx](https://github.com/bkaradzic/bgfx) rendering library
- [vg-renderer](https://github.com/jdryg/vg-renderer) and [NanoVG](https://github.com/memononen/nanovg) vector drawing libraries
- [lua](https://github.com/lua/lua) scripting language
- [stb](https://github.com/nothings/stb) headers
- [glm](https://github.com/g-truc/glm) math library
- [json](https://github.com/nlohmann/json) header

# support
Creating two has been a huge time investment over the course of a few years: the only way I can pursue that effort and make it thrive into the programming ecosystem of our dreams, is through funding and sponsorship: you are welcome to have a look at our [patreon](https://www.patreon.com/toyengine).

Iron supports:
- Mike King

Stone supports:
- Etienne Balit, Le Bach, Manos Agelidis, Nebo Milic, Omar Cornut, Stefan Hagen, Sunder Iyer

# license
two is licensed under the [zlib license](LICENSE.txt).
