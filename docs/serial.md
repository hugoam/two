# serial
everything starts with your code : the domain specific problem you want to solve, the application business logic.  
in mud we start here, and not in intricate hierarchies of classes and components to inherit. as such mud is more alike to a programming language/idiom than a framework.

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
