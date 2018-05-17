I am releasing [mud](https://github.com/hugoam/mud): an all-purpose c++ app prototyping library, focused towards live graphical apps and games, packed with features, still in experimental phase.

### TL;DR: c++ reflection, serialization, scripting, ui inspection on top of any c++ code, declarative UI and declarative graphics, and even a physically based rendering add-on

Try some live examples in the browser:
- [pbr materials](https://hugoam.github.io/mud-io/examples/03_materials_low.html)
- [lights](https://hugoam.github.io/mud-io/examples/04_lights.html)
- [sponza (.obj import)](https://hugoam.github.io/mud-io/examples/04_sponza.html)
- [character (animations)](https://hugoam.github.io/mud-io/examples/05_character.html)
- [particles](https://hugoam.github.io/mud-io/examples/06_particles.html)
- [gltf](https://hugoam.github.io/mud-io/examples/07_gltf.html)
- [sky (perez model)](https://hugoam.github.io/mud-io/examples/08_sky.html)
- [live shader](https://hugoam.github.io/mud-io/examples/09_live_shader.html)
- [live graphics](https://hugoam.github.io/mud-io/examples/14_live_gfx.html)
- [live graphics (visual script)](https://hugoam.github.io/mud-io/examples/4_live_gfx_visual.html)

Links: [github](https://github.com/hugoam/mud) - [official page](https://hugoam.github.io/mud-io) - [twitter](https://twitter.com/hugoamnov) - [patreon]()

## A screenshot:
![live graphics](https://github.com/hugoam/mud-io/blob/master/media/14_live_gfx.png)

## Another screenshot:
![gltf](https://github.com/hugoam/mud-io/blob/master/media/07_gltf.png)

## Summary
[mud](https://github.com/hugoam/mud) is a set of 6 small, self-contained libraries rather than a single one: they are 6 building blocks that turn out essential to prototyping any c++ app.  
Three of them are low-level generic c++ blocks: they rely on applying generic operations on arbitrary types:
- reflection of any c++ code to a set of generic primitives
- generic serialization of any c++ objects to any format (currently json)
- generic script bindings for any c++ objects, methods, functions, seamlessly, **and** a visual scripting language

Two of them make the interactive/graphical foundation of an app:
- immediate/declarative UI
- immediate/declarative graphics

The last one ties the ui and the generic c++ blocks together:
- generic ui to edit and inspect c++ objects, modules, call methods, edit text and visual scripts

**mud** stems from a strong programming philosophy: it wagers that the future of application and game coding lies in small, self-contained, reusable and shared libraries, and **not** in gigantic tightly coupled *engines* of hundreds thousands of lines of code.

For our shared knowledge and our programs to progress, the building blocks have to be **small** and **understandable by most** (which is essentially the same thing). There are many such blocks already in many domains (network, pathfinding, database, graphics).

I started writing mud because I discovered some of the blocks I needed were missing. The common thread between these blocks, is an unrelenting thirst for simplicity. With the building blocks mud provides, one can create live graphical apps in few lines of code, but also, **anyone** can potentially create a *game engine*.

**mud** is open-source, and published under the zlib license: as such it is looking for sponsors, funding, and your support through [patreon](https://www.patreon.com/libmud).

In theory, mud compiles to any desktop, mobile or web platform, mud graphics relying on the [bgfx](https://github.com/bkaradzic/bgfx) library which supports them. In practice, there is some work ahead to make that happen and refine the build system for each of them.

## Domains
To be able to quickly together c++ apps, but also for educational purposes, the following blocks needed to exist in the open-source ecosystem:
- [a small generic c++ layer](https://github.com/hugoam/mud/blob/master/docs/reflection.md) (< 5 kLoC): c++ primitives that allow manipulating generic objects at runtime, and precompilation of any c++ code to an initializer for these primitives.
- [a small generic serialization layer](https://github.com/hugoam/mud/blob/master/docs/serialization.md) (< 1 kLoC): serialize generic c++ objects from and to different formats. mud does only json (and previously sqlite), but some binary formats like flat buffers should be studied (although they usually have their own code generation).
- [a small generic scripting library](https://github.com/hugoam/mud/blob/master/docs/scripting.md) (< 3 kLoC): manipulate generic c++ objects through scripts. all reflected primitives: functions, methods, members can be used seamlessly. mud does only lua, and a powerful graph based visual scripting language.
- [a small UI library](https://github.com/hugoam/mud/blob/master/docs/ui.md) (< 10 kLoC) that does: immediate-mode widget declarations, logic/layout/styling separation, fully automatic layout, css-like skinning, image-based skinning, style sheets, input widgets, docking windows and tabs, allows to define complex widgets easily.
- [a small graphics library](https://github.com/hugoam/mud/blob/master/docs/graphics.md) (< 6 kLoC): immediate-mode rendering graph declaration, with the following basic primitives: meshes, models, shaders, programs, materials, skeletons, animations, render targets, filters, render passes, render pipelines. It is minimalistic in design, and is **NOT a game engine** nor does it try to be.
- [a small ui inspection library](https://github.com/hugoam/mud/blob/master/docs/inspector.md) (< 3 kLoC): generic ui components: inspector panel, edit an object fields, call a method on an object, inspect an object graph/structure, all these are generic ui components operating on the reflected primitives.
- [a small pbr rendering model]() (< 4 kLoC): a sample implementation of a physically based rendering model for the above graphics library, demonstrating it can be simple (it's the research behind that is complex).

In each of these domains, simplicity and DRY is always favored over other concerns: performance, for example, is only ever considered under the prism of global simplicity and conciseness. If a performance improvement involves obscuring the mechanics of the system significantly, it is not even considered.

To get a more in-depth look at how using these features looks, in code, you might want to have a look at the [main page](https://github.com/hugoam/mud) of the github repo.

## What's the plan ?
The building blocks are just starting to fall in place such that writing mud c++ apps feels thrilling and liberating in its simplicty. That means, I believe, the moment has come to start communicating about this project in order to, if anything, get collective help into pushing it to maturity: there are still many aspects to improve and flaws to iron out. With proper support, I believe a first stable release could happen before the end of the year.

Creating mud has been a huge time investment over the course of a few years: the only way I can pursue that effort and make it thrive into the programming ecosystem of our dreams, is through funding and sponsorship: you are welcome to have a look at our [patreon](https://www.patreon.com/libmud).

Feature-wise, most of the core features are in place, the remaining work being to improve robustness, error-handling, fix bugs, add more platforms. This leaves an open roadmap to investigate more advanced graphics topics: real-time global illumination, clustered rendering, distance field shadows. But these are all just slightly outside the scope of mud, so they might come as extensions.

And then, of course, there's a game engine. More on that in a few weeks :)

## So what now ?
If you are interested in following the development, it's mostly on my [twitter](https://twitter.com/hugoamnov).  
If you want to try it, you can just clone the [sample github repo](https://github.com/hugoam/mud-sample), or check out the [main repo](https://github.com/hugoam/mud).  
If you want to learn about how it works, check out the [documentation](https://github.com/hugoam/mud/blob/master/docs/mud.md) and the [quickstart](https://github.com/hugoam/mud/blob/master/docs/tutorial.md) guide.  
And once again, if you want to support it, mud has a [patreon](https://www.patreon.com/libmud).

Aside from polishing the existing examples and documentation (as people start using the library and opening issues), I will spend the next few weeks adding new samples to demonstrate how simple applications can be built with mud, and posting articles to go more in-depth concerning the different topics that mud covers.

So stay tuned !

