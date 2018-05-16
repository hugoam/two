# uio
mud provides a range of generic ui components residing in the [uio]() module.
these components are of a critical utility either for live debugging the state of the app or for production-grade editor tools:
- [browse](#browse) a module namespaces, functions, types
- [call](#call) a method
- [edit](#edit) a value
- [inspect](#inspector) an object fields
- inspect an object [structure](#graph) as a graph
- [create](#creator) an object
- inspect a [collection](#library) of objects, add and remove object to it
- toggle a [console](#console) to do virtually any operation on the application state

## browse
the `system_inspector` and `module_inspector` ui components allow to inspect all the system modules, or one module specifically :
```c++
uio::system_inspector();
uio::module_inspector();
```

## call
this `method_call_edit` component allows to set the arguments to a method and call it :
```c++
Method& meth = method(MyObject::foo);
uio::method_call_edit(ui, meth);
```

## edit
the `value_edit` component allows to edit a single value :
```c++
Var value = var(35);
uio::value_edit(ui, value);
```

## inspector
the `inspector` component allows to edit any object, all of its fields, and all of its components :
```c++
AppObject object(12, 'cocorico');
uio::inspector(ui, &object);
```

## creator
the `creator` component allows to edit all fields of an object and create it :
```c++
Var object = var<MyObject>();
uio::creator(ui, object); 
```

## library
the `multi_inspector` component allows to edit each of a collection of objects, and add and remove objects to it :
```c++
std::vector<Var> objects = { var(MyObject(5, "cocorico")) };
uio::multi_inspector(ui, objects);
```

## console
