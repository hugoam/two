I've spent the last 4 months developing an UI toolkit focused towards games, with a lot of power yet small and lean. It is free, open-source, and I want to share it with game developpers.

TL;DR - Made a new free and open-source UI library that gamedevs should know about
=====
Show me the demo already ! Try it in the browser : [here](http://hugoam.github.io/kiui/livedemo/kiui.html)
![switching between styles at runtime](media/themes.gif?raw=true)
Have a look at a few GIFs : [Themes](http://hugoam.github.io/kiui/media/styles.gif) [Dock Windows](http://hugoam.github.io/kiui/media/dockspace.gif)
[Text Edit](http://hugoam.github.io/kiui/media/texteditx.gif) [Tweakin Style](http://hugoam.github.io/kiui/media/styling.gif) [Tweakin Some More] (http://hugoam.github.io/kiui/media/stylingbis.gif)
Open-source ! [Github](https://github.com/hugoam/kiui)

Why ?
=====
Like I suppose, many gamedevs before me, coding UI has always been a source of discomfort.
I wanted to code my interfaces as I coded the rest. With a sense of freedom to organise everything however I felt the most natural.
In most domains, when I have needed a library to do a specific task, I've been able to find a small and efficient library that would do just that.
That is true of database, pathfinding, message queuing, network, even rendering.
Yet... the UI domain was rebellious. All the solutions I tried forced me to write ugly code.

You can feel the lack of diversity in UI when you google the answers to question : what is a good UI library for games ?
I even went to web-based UI at some point, and it taught me about some great features an UI solution should have. But I needed native UI.
So, four months ago, I finally rolled up my sleeves, deciding that if there was one domain where I could bring something to the world, it was about UI.

Today, after four month, the library is good enough to start communicating about it on public channels like the gamedev community.
I hope to find here some enthusiasts first users, and get the word out, so that the library can grow toward stability over the following months.

What makes it stick out ?
=========================
Here are all the requirements and features that I strived to pack into this library :
- Logic code is separated from appearance code, for clean UI code writing
- Layout is automatic, no manual positioning or sizing is ever needed (no messing with VSizers and HBoxes)
- Appearance is completely tweakable both through Style Sheets and directly from code
- Vector based skinning (borders, rounded corners, gradients, shadows)
- Game friendly image based skinning (9 sprites)
- Basic widgets : dropdown, slider, checkbox, text input, multiline text, filtered dropdown
- Toolkit widgets : dockspace, dockable windows, tabs, docking bar, tables, trees
- Fit for both an editor UI and a game UI
- Core library is completely standalone and self contained
- Has a nifty standalone renderer using the really good NanoVG vector drawing library

Technical specs :
- Modern C++ (in the limit of my young knowledge)
- Emscripten and
- Cross-Platform (tested under gcc, clang and msvc as of now)
- Free as in beer and as in speech : MIT license
- Lightweight : small codebase of around 15kLoC, 600kB footprint for the .dll on windows

What's the catch ?
==================
Well kiUi is still in its infancy. It is a work in progress, with an API that is not stable yet.
There is virtually no documentation as of now, although I believe the code to be quite clean and self-explanatory.
And now that it's close to being feature-complete I'll have time to write docs and tutorials.

So what now ?
=============
Well if you have a project like mine, a game with quite a lot of UI design and possibly a toolset or an editor, consider using it !
Here is the github repository where the real stuff happens : https://github.com/hugoam/kiui
Happy to share it, and happy to hear any kind of feedback, bug reports in the future. (I'm exposing myself to a shitstorm of issue reports, I know ;) )

There will also be a kind of discussion on the next features and widgets to implement.
High on the list is to make the UI blend into different native OSes like a real toolkit.

And probably, see you soon, as the game and toolset powered by this lib, I shall soon share with you also !
