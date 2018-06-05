
#pragma once

#ifndef MUD_MODULES
#include <obj/System/System.h>

#include <obj/Generated/Module.h>
#include <math/Generated/Module.h>
#endif
        
#include <geom/Generated/Forward.h>
#include <geom/Generated/Types.h>

#include <geom/Aabb.h>
#include <geom/Geom.h>
#include <geom/Intersect.h>
#include <geom/Mesh.h>
#include <geom/Poisson.h>
#include <geom/Primitive.h>
#include <geom/Shape.h>
#include <geom/ShapeDistrib.h>
#include <geom/Shapes.h>
#include <geom/ShapesComplex.h>
#include <geom/Symbol.h>
#include <geom/Anim/Anim.h>
#include <geom/Shape/Circle.h>
#include <geom/Shape/CompoundShape.h>
#include <geom/Shape/Cube.h>
#include <geom/Shape/Cylinder.h>
#include <geom/Shape/DrawShape.h>
#include <geom/Shape/Geom.h>
#include <geom/Shape/Icosphere.h>
#include <geom/Shape/Line.h>
#include <geom/Shape/ProcShape.h>
#include <geom/Shape/Quad.h>
#include <geom/Shape/Sphere.h>
#include <geom/Shape/Spheroid.h>
#include <geom/Shape/Triangle.h>

namespace mud
{
	export_ class MUD_GEOM_EXPORT mudgeom : public Module
	{
	private:
		mudgeom();

	public:
		static mudgeom& m() { static mudgeom instance; return instance; }
	};
}

#ifdef MUD_GEOM_MODULE
extern "C"
MUD_GEOM_EXPORT Module& getModule();
#endif
