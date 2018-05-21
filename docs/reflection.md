# C++ reflection in [mud](https://github.com/hugoam/mud)
The lowest and most fundamental layer of [mud](mud.md) is the reflection layer.  
Its *core principle* arises from a pure programming problem : how to *reconcile* **types** with **generic algorithms**, while prioritizing *simple and elegant* code *always*.  
The issue it aims to solve is the following : *many algorithms* are *best expressed* as operating on **completely generic, type-erased objects**, rather than **typed objects** : however, in its most efficient and mature form, c++ deals with strongly typed objects to generate tightly optimized machine code (leading some developers to stick to these *good* parts, see *orthodox c++*).

A typical programming problem varies between three degrees of genericity: we can separate algorithms whether they:
- operate on **one** *specific* data type
- operate on a **subset** of all possible types (= a *concept* or an *interface* type)
- operate on **any** *arbitrary* type

c++ *excels* at solving the **first kind of problem**. For the other two, however, the tools offered by idiomatic c++ are *less than ideal*: c++ templates come with *sizable disadvantages*: *bloated binaries, slow compilation, high verbosity and complexity*, resulting in a *high cognitive cost*. The generic idioms outlined here make for an interesting alternative.   

For this purpose, mud provides **generics**, **type-erased** objects, and **reflection**.  
Suppose we have a way to manipulate type-less objects, inspect their features, fields and methods, and modify their state in a generic way.

Once we have such constructs, a typical program will contain two flavours of code :
- parts in the strongly typed end of the spectrum, operating on their static compile-time knowledge of a type :
```c++
MyClass object;
object->foo(34, "cocorico!"); // we want to call the foo method of the MyClass object
```
- parts in the generic, type-erased end of the spectrum, operating on their properties examined at run-time :
```c++
Var object;
serialize(object); // we want to serialize all fields of object, whatever these fields are
```
As a consequence of having two such idioms, objects constantly go *back and forth* these two representations : **typed** and **generic**, seamlessly.

The role of mud reflection layer is two-fold, to provide you both : 
- the [primitives](#primitives) to seamlessly and safely interface between typed objects and type-erased objects
- the [operations](#operations) to inspect and mutate any aspect of type-erased objects, allowing you to write generic algorithms

## Generic problems
Here are a few examples of problems that are typically best solved in a generic manner:
- serialize an object and its components recursively, or more generally, inspect its state
- compare two objects for equality member by member
- test if any of an object methods will produce errors
- check if an object type fits a given concept

## Reflecting a class
The prerequisite to using generic [primitives](#primitives) and [operations](#operations) on any given c++ construct, is to produce the necessary reflection data, for this construct.  
This is done by annotating the code in the following manner, which is then fed to a precompiler or reflection [generator](#generator) :
```c++
enum class _refl_ ShapeType
{
    Sphere,
    Cube
};

class _refl_ MyObject
{
public:
    _constr_ MyObject(int number, std::string name);

    _meth_ int method();

    _attr_ int m_number;
    _attr_ std::string m_name;
    
    _attr_ ShapeType m_shape;
    
    _attr_ std::vector<float> m_floats;
};

_func_ void foo(int arg);
_func_ void bar(MyObject& object);
```
Notice how this is a standard c++ definition, with some added [reflection hints](#hints): `_refl_` to reflect a class, `_constr_` to reflect a constructor, `_meth_` for a reflected method, and `_attr_` for a reflected attribute.

Using these annotations, the reflection [generator](#generator) produces a couple of reflection files, which declares and registers [constructs](#constructs) using mud corresponding types: [functions](../src/obj/Reflect/Method.h), [types](../src/obj/Reflect/Meta.h), [classes](../src/obj/Reflect/Class.h), [class members](../src/obj/Reflect/Member.h), [class methods](../src/obj/Reflect/Method.h), [enums](../src/obj/Reflect/Enum.h).  

## Types
Passing objects around in a **generic** fashion means we need to keep track of their type.
As such a core construct of mud is the [Type](../src/obj/Type.h) object, that uniquely identifies a type: to fetch this object for any given c++ class, call the following function:

```c++
template <class T>
Type& type();
```

mud **must** ensure that the type of a given c++ class is always unique : wherever, two calls to `type<T>()` from any two points in any two c++ modules, should always return the same [Type](../src/obj/Type.h) handle.

A special case of types is c++ polymorphic objects: to correctly pass such objects around using **generic** [primitives](#primitives), mud needs to be able to get the actual derived type. For this, mud expects the base class to have a `Type` member named `type`, like so:
```c++
class Shape
{
public:
    Shape(Type& type) : m_type(type) {}
    virtual ~Shape() {}
    
    _attr_ Type& m_type; // can be a pointer too
}
```
This allows to convert a pointer or reference to a `Shape` to an aptly typed generic `Ref` or `Var`. To get the real type of a potentially polymorphic object, the `typeof(object)` function ensures you always get the true type of a given object: it simply retrieves the `type` member if that type of object has one (= is polymorphic), or call `type<T>()` instead.

## Primitives
### Values and references
Now that we have a way to identify an object type, we can start safely passing these objects around as *generic* **values** and **references** :  
mud provides two constructs to represent generic objects :
- a `Var` is a type-erased [value](../src/obj/Var.h), which can contain any object
- a `Ref` is a type-erased [reference](../src/obj/Ref.h) to a value, which can be of any type

It's worth to note that **generic** *value types* are costly to pass around: as `Var` uses heap allocated memory to contain its objects, memory allocations happen each time one is created or copied.  
As a consequence, and a good rule of thumb, when passing objects around, you should use `Ref` everywhere possible.

Creating a `Var` or `Ref` from a c++ objects is done like so :
```c++
MyObject object = { 12, 'cocorico' };
Ref a = &object; // a holds generic reference to object
Var b = var(object); // b holds a copy of object
```

Retrieving typed values from generic `Var` and `Ref` is done with the `val()` function :
```c++
MyObject& aa = val<MyObject>(a);
MyObject& bb = val<MyObject>(b);
```

### c++ constructs
Each reflected c++ construct is represented by their respective type and objects :
- the [function](../src/obj/Reflect/Method.h) class represents any c++ function: use it to [call](#call-a-function) the underlying c++ function with **generic** arguments
- the [meta](../src/obj/Reflect/Meta.h) class represents any c++ type: use it to [create](#create-an-object) an object, [convert](#convert-an-object-to-a-string) an object to a string
- the [class](../src/obj/Reflect/Class.h) class represents any c++ class: use it to [construct](#construct-an-object) an object,  to iterate a class **bases**, **members** or **methods**
- the [member](../src/obj/Reflect/Member.h) class represents a c++ class member (see above): use it to [get](#get-a-member-value) or [set](#set-a-member-value) a **generic** value to this member
- the [method](../src/obj/Reflect/Method.h) class represents a c++ class method (see above): use it to [call](#call-an-object-method) the underlying c++ method with **generic** arguments
- the [enum](../src/obj/Reflect/Enum.h) class represents a c++ enum (scoped or not): use it to convert an index to its label, or a label to its index, or a label to its underlying value, etc...

In general, you can retrieve or browse these construct in different ways:
- you can retrieve it from the c++ construct by calling either of `function()`, `type()`, `meta()`, `cls()`, `member()`, `method()` with the construct as an argument
- you can browse all of a [module](../src/obj/System/System.h) constructs, or retrieve on specifically by name
- you can browse all of the [system](../src/obj/System/System.h) constructs, i.e. the sum of all constructs in all currently loaded modules

## Operations
Here are the different operations enabled by the generic reflection primitives :  

(*Note: In these examples retrieving the generic c++ construct and using it is done successively: in real code, these are most likely done in different locations.*)

### call a function
Call any [function](../src/obj/Reflect/Method.h) object by passing an array of **generic** arguments (a vector of `Var`):
```c++
Function& func = function(foo); // retrieve the function
Var result = func({ var(5) }); // call it with generic parameters
```

### construct an object (for classes)
Call any [constructor](../src/obj/Reflect/Method.h), with an array of generic arguments:
```c++
Constructor& constr = cls<MyObject>().constructor(); // retrieve the main constructor
Var object = constr({ var(12), var(string("cocorico")) }); // call it with generic parameters
```

### create an object (any type)
Create an empty object of any default constructible type:
```c++
Var value = meta<int>().empty_var();
Var value = meta<MyObject>().empty_var();
```

### call an object method
Call any [method](../src/obj/Reflect/Method.h) with an array of generic arguments:
```c++
Method& bar = method(&MyObject::bar); // retrieve the method
Var result = bar(object, { var(12) }); // call it with generic parameters
```

### get a member value
Get the generic value of any [member](../src/obj/Reflect/Member.h):
```c++
Member& colour = member(&MyObject::m_colour); // retrieve the member
Var value = colour.get(object); // fetch its generic value from a generic object
```

### set a member value
Set the generic value of any [member](../src/obj/Reflect/Member.h):
```c++
Member& name = member(&MyObject::m_name); // retrieve the member
name.set(object, var(string("cocorico!"))); // set it on a generic object with a generic value
```

### iterate a collection
Iterate any **sequence** type as a collection of generic values:
```c++
Member& floats = member(&MyObject::m_floats); // retrieve the member
Var var = floats.get(object); // fetch its generic value
iterate(var, [](Ref element) { printf("%f\n", val<float>(element)); });  // iterate its contents as generic values
```

### convert an object to a string
All base, enums and sequence types support conversion to a string from a generic value:
```c++
Var a = var(14);
Var f = var(4.93f);
Var floats = var(std::vector<float>{ 3.03f, 0.45f, 0.1f });
to_string(a); // prints "14"
to_string(f); // prints "4.93"
to_string(floats); // prints "3.03,0.45,0.1"
```

## Generator
### Hints
The following hints are defined for reflecting c++ constructs:
- `_refl_`: reflect a type
- `_attr_`: reflect a class field (static or not)
- `_meth_`: reflect a class method
- `_func_`: reflect a function
- `_array_`: specifies that a reflected type behaves like an array type (implements the [] operator)
- `_struct_`: specifies that a reflected type has value semantic

When compiling, these are defined to nothing : they only have a meaning when run through the reflection generator.

### Precompiling
Precompiling is done by the [reflection generator](../src/obj/Metagen/generator.py) : it's essentially a c++ AST parser, written in python over [libclang](https://github.com/llvm-mirror/clang/tree/master/tools/libclang) : it goes over all the headers in your module, and each time a [reflection hint](#hints) is found in the AST, the meta data is generated for the annotated construct.

The meta data is bundled into the following reflection files, added to a `Generated` folder :
- a `Forward.h` file containing forward declarations for all types in your module
- a `Module.h` file regrouping all headers file from your module, and the module object declaration itself
- a `Types.h` file containing mud type handle declarations
- a `Meta.h` file containing the actual meta information declarations

To precompile your module, `generator.py` is used, passing the paths to all modules as arguments :
```bash
generator.py path_to_module_1 path_to_module_2 [...]
```
There is no need to deal with the generator directly though : using a custom action of the [GENie](https://github.com/bkaradzic/GENie) build system for your project, simply call :
```bash
genie reflect
```
The reflection will be precompiled again. Let's remember to do that every time we modify any of the reflected primitives in our headers.

### Template classes
Reflection of template classes is partially supported under certain conditions:
- fields and methods must be [annotated](#hints) in the unspecialized template definition
- only the actual instantiations of this definition will be reflected, just like any regular class
- each reflected version must be *explicitly instantiated* and annotated with a [reflection hint](#hints) on the place of instantiation

```c++
template <class T>
class _refl_ Foo // annotate the template so that the precompiler will pickup the reflected features
{
    _attr_ T m_attribute;
};

template class _refl_ Foo<int>; // fully reflects the explicit instantiation for type int
```

## Generic features
The primitives and low level generic operations we outlined might seem trivial, yet they open vast arrays of possibilities for generic programming blocks, that immediately scale to the new types and new modules you add to your application code.

mud builds on top of these to provide the following generic building blocks, for any of the reflected types and primitives :
- ui for creating, editing, saving, inspecting any object structure
- serialization in and out of any arbitrary object
- seamless binding of all reflected primitives with scripting languages (lua, visual scripting)

The scripting and visual scripting examples are good demonstrations of the power enabled by the reflection/generic idioms.
- [live graphics](https://hugoam.github.io/mud-io/examples/14_live_gfx.html)
- [live graphics (visual script)](https://hugoam.github.io/mud-io/examples/14_live_gfx_visual.html)

<br>![live graphics](https://github.com/hugoam/mud-io/blob/master/media/14_live_gfx.png)

## Going further
In a later article, we will show an interesting application of this reflection model: we wrote a **typed** c++ representation of the [glTF](https://github.com/KhronosGroup/glTF/tree/master/specification/2.0) format that generically serialize from and to the *glTF json format*. This eliminates more than half of the logic that is usually contained in glTF importers, and makes it the smallest and simplest it can possibly be (fitting in < 1kLoC).

