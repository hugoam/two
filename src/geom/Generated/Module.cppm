#include <assert.h>
#include <stdint.h>
#include <float.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <obj/Config.h>

export module mud.geom;
import std.core;
import std.io;
import std.threading;

export import mud.obj;
export import mud.srlz;
export import mud.math;

#ifdef MUD_OBJ_LIB
#include <obj/Cls.h>
#include <obj/Strung.h>
#endif

#include <geom/Generated/Module.h>

//#include <geom/Aabb.h>
//#include <geom/Geom.h>
//#include <geom/Intersect.h>
//#include <geom/Mesh.h>
//#include <geom/Poisson.h>
//#include <geom/Primitive.h>
//#include <geom/Shape.h>
//#include <geom/ShapeDistrib.h>
//#include <geom/Shapes.h>
//#include <geom/ShapesComplex.h>
//#include <geom/Symbol.h>
//#include <geom/Anim/Anim.h>
//#include <geom/Shape/Circle.h>
//#include <geom/Shape/CompoundShape.h>
//#include <geom/Shape/Cube.h>
//#include <geom/Shape/Cylinder.h>
//#include <geom/Shape/DrawShape.h>
//#include <geom/Shape/Geom.h>
//#include <geom/Shape/Icosphere.h>
//#include <geom/Shape/Line.h>
//#include <geom/Shape/ProcShape.h>
//#include <geom/Shape/Quad.h>
//#include <geom/Shape/Sphere.h>
//#include <geom/Shape/Spheroid.h>
//#include <geom/Shape/Triangle.h>
