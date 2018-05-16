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

