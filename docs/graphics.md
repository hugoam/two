# graphics
mud gfx library uses the same immediate paradigm as the ui. instead of nesting ui nodes (widgets) calls, you nest graphics nodes calls. as such it is perfect for quickly setting up some debug graphics rendering.

mud rendering primitives :
- **[shapes](#shapes)**: parametric definitions of standard shapes : circle, sphere, cylinder, cube, rectangle, etc...
- **[symbols](#symbols)**: how a given shape should be rendered : color, fill and outline, level of detail
- **[meshes](#meshes)**: rendering primitives and their index and vertex data
- **[models](#models)**: a sum of meshes and optionally a skeleton
- **[textures](#textures)**: immutable or dynamic 2D-, 3D-, cubemap- and array-textures
- **[shaders](#shaders)**: a shader (vertex, fragment, geometry, compute) is linked to a sequence of blocks
- **[programs](#programs)**: a program is the sum of shaders and blocks that governs the rendering of a primitive
- **[materials](#materials)**: a material associated to a program, contains all the data parameters of this program
- **[blocks](#blocks)**: a render block holds all the state and logic of a given rendering feature
- **[passes](#passes)**: a pass is a unit of renderer work, which can do virtually any render operation
- **[renderers](#renderers)**: a renderer is a sequence of passes, it dictates how is a viewport rendered
- **[pipelines](#pipelines)**: a pipeline is a collection of all render blocks needed by its renderers

the graph is composed of the following primitives :
- **[nodes](#nodes)**: a node is a transform an a user object
- **[items](#items)**: an instance of a model

here are all the functions of the [immediate gfx API](../src/gfx/Graph.h) :

# graph
this function adds a node to the hierarchy :
```c++
namespace gfx
{
    Gnode& node(Gnode& parent, Ref object, const vec3& position, const quat& rotation, const vec3& scale);
}
```

these functions add a shape item to the hierarchy :
```c++
namespace gfx
{
    Item& shape(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags, Material* material, size_t instances);
    void draw(Gnode& parent, const Shape& shape, const Symbol& symbol, uint32_t flags);
}
```

these functions add a model item to the hierarchy :
```c++
namespace gfx
{
    Item& item(Gnode& parent, const Model& model, uint32_t flags, Material* material, size_t instances);
    Item& model(Gnode& parent, const string& name, uint32_t flags, Material* material, size_t instances);
    Animated& animated(Gnode& parent, Item& item);
}
```

this function adds a particles emitter to the hierarchy :
```c++
namespace gfx
{
    Particles& particles(Gnode& parent, const ParticleGenerator& emitter, uint32_t flags, size_t instances);
}
```

these functions add lights to the hierarchy :
```c++
namespace gfx
{
    Light& light(Gnode& parent, LightType type, bool shadows, Colour colour, float range, float attenuation);
    Light& sun_light(Gnode& parent, float azimuth, float elevation);
    GIProbe& gi_probe(Gnode& parent);
    void radiance(Gnode& parent, const string& texture);
}
```

this function sets the background :
```c++
namespace gfx
{
    void custom_sky(Gnode& parent, std::function<void(Render&)> renderer);
}
```

these functions create a material in the hierarchy :
```c++
namespace gfx
{
    Material& material(Gnode& parent, UnshadedMaterialBlock& unshaded_block);
    Material& material(Gnode& parent, PbrMaterialBlock& pbr_block);
}
```

create a viewer to render into
```c++
SceneViewer& viewer = ui::scene_viewer(uroot);
Gnode& groot = viewer.m_scene.m_graph.begin();
```

draw a node, setting the transform for all children of this node
```c++
Gnode& gnode gfx::node(root, {}, vec3(0.f, 15.f, 7.5f));
```

# [shapes](../src/math/Shape.h)
the math module offers standard parametric definitions of [various 3D and 2D shapes](../src/math/Shape.h)  
these shapes can be used in various operations : rendering, random point distribution, physics collisions  

to draw any arbitrary shape, call the `gfx::shape` function, passing a `shape` and a `symbol` object  
the [symbol](../src/math/Shape.h#L335) parameter drives how the shape should be rendered : outline color, fill color, image, lod, double-sided
```c++
gfx::shape(gnode, Symbol(Colour::White), Cube());
```

# [meshes](../src/gfx/Mesh.h#L33)
a mesh is a rendering primitive that maps roughly 1:1 to the API primitives and their buffers  
meshes are usually created by mud when loading a [model](#models) so you don't have to deal with them directly  
   
meshes are composed of indices, vertices, and a [primitive types](../src/math/Geometry.h#L170) :
```c++
enum class _refl_ PrimitiveType : unsigned int
{
    Points = 0,
    Lines = 1,
    LineLoop = 2,
    LineStrip = 3,
    Triangles = 4,
    TriangleStrip = 5,
    TriangleFan = 6
};
```

* this section will be fleshed out as the interface to create meshes gets polished

# [models](../src/gfx/Mesh.h#L90)
a model is a collection of primitives (meshes) to be rendered as a single entity  
anything rendered to the screen by the gfx module, except immediate geometry, is a model

to draw an instance of a model, call the `gfx::item` function, passing either the `name` of the model or directly a `model`object
```c++
gfx::item(gnode, "my_3d_model.obj");
```

# [textures](../src/gfx/Texture.h)
a texture is an image file loaded and ready to be used for rendering  
the main use of textures is for them to be sampled in materials

```c++
Texture& texture = gfx::texture("my_texture.jpg");
UnshadedMaterialBlock unshaded_block = { &texture };
Material& material = gfx::material(gnode, unshaded_block);
gfx::item(gnode, model, material);
```

animate a model item
```c
Item& item = gfx::model(gnode, "my_3d_model.obj");
Animated& animated = gfx::animated(gnode, item);
animated.play("walk");
```
