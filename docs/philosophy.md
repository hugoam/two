# philosophy

## a different approach to dispatch
the common pattern for polymorphic dispatch is to make interfaces with virtual functions.
in this pattern the standard example is a shape, with a draw function, and a bunch of sub-classes :
```c++
class Shape
{
public:
    virtual ~Shape() {}
    virtual void draw() = 0;
};

class Circle : public Rectangle
{
public:
    Circle(float radius);
    virtual void draw() final;
};

class Rect
{
public:
    Circle(float width, float height);
    virtual void draw() final;
};
```

this pattern is oldest t : you will find it in virtually every c++ book.
however, for such a common pattern the list of its inconvenients is pretty rough :
- types have to know about **all operations** that you can do on them

this means, that, as a user of the library, you can't change the Shape class and the Shape implementations, you **can't add new polymorphic operations**

of course, drawing is not the only thing you can do with a shape : you might want to
- generate a random point inside
- check if a point is inside
- measure their area
- check if they intersect

so you are left with two options : splitting the class, or ending up with a huge

our approach is radically different

this allows us to do not only single dispatch, but also double (or multiple) dispatch
but more importantly, this allows us to keep the operations separated from the types
