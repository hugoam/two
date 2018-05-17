# scripting
mud reflection allows to automatically bind all of a module types, methods, fields and functions to a lua counterpart  
it supports the following features :
- call c++ functions from lua
- create c++ objects from lua code
- call c++ object methods from lua
- pass any basic type, c++ object, or collection of objects back to these c++ functions
- call lua functions from c++

given the following reflected c++ class :
```c++
class _refl_ MyObject
{
public:
    _constr_ MyObject(int var, std::string field);
    
    _meth_ int method();
};

_func_ void bar(MyObject& object);
```

mud allows you to write a lua script using any of the reflected functions, types, methods, fields
```lua
local object = MyObject(5, 'hello world!')
print(object:method())
bar(object) -- you can even pass c++ objects to a function
```

in order to do that, you simply create a [lua interpreter](../src/lang/Lua/Lua.h) and set it up to use your module
```c++
LuaInterpreter lua;
lua.reflect(MyModule::module());
```

then create a [script](../src/lang/Script/Script.h) object passing the lua code as a string
```c++
Script script = { lua_code };
```

you can then [call](../src/lang/Script/Script.h#L247) this script like a regular function, as many times as you want
```c++
script();
```

## script parameters
you can define a lua script taking some typed parameters  

to do that, just create a [signature](../src/obj/Reflect/Method.h#L53) specifying the sequence of [parameters](../src/obj/Reflect/Method.h#L27) and pass that when creating the script object
```c++
Signature signature = { { "param", Ref(cls<int>()) } };
Script script = { "example script", lua_code, signature };
```

you can then [call](../src/lang/Script/Script.h#L247) the lua script passing in the correct parameters
```
script({ var(57) });
```

the lua script can then access the parameter as if it was a function call
```lua
print(param) -- prints 57
```

# visual script

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

