#pragma once

#include <infra/Config.h>

#include <type/Forward.h>
#include <math/Forward.h>

#ifndef MUD_GEOM_EXPORT
#define MUD_GEOM_EXPORT MUD_IMPORT
#endif

namespace mud
{
    enum DrawMode : unsigned int;
    enum class PrimitiveType : unsigned int;
    enum class SymbolDetail : unsigned short;
    
    
    class Shape;
    class ShapeVar;
    struct Line;
    struct Rect;
    struct Quad;
    struct Grid2;
    struct Triangle;
    struct Circle;
    struct Torus;
	struct TorusKnot;
    struct Ring;
    struct Ellipsis;
    struct Arc;
    struct ArcLine;
    struct Cylinder;
    struct Capsule;
    struct Cube;
    struct Sphere;
    struct SphereRing;
    struct Spheroid;
	struct Icosahedron;
    struct Aabb;
    struct Plane;
    struct Plane3;
    struct Face3;
    struct Segment;
    struct Ray;
    struct Plane6;
    struct Point8;
    struct VertexAttribute;
    struct Vertex;
    struct Tri;
    struct ShapeVertex;
    struct ShapeTriangle;
    struct MeshAdapter;
    class Geometry;
    struct MeshPacker;
    class Distribution;
    class Poisson;
    class RandomShapePoint;
    struct Polygon;
    struct Box;
    struct Points;
    struct Grid3;
    struct ConvexHull;
    struct Symbol;
    struct ShapeSize;
    struct ProcShape;
    struct CompoundShape;
    struct DispatchDrawProcShape;
    class IcoSphere;
}

#ifdef MUD_META_GENERATOR
#include <stl/vector.h>
namespace stl
{
	export_ extern template class refl_ seque_ vector<mud::vec2>;
	export_ extern template class refl_ seque_ vector<mud::vec4>;
	export_ extern template class refl_ seque_ vector<mud::ivec4>;

	export_ extern template class refl_ seque_ vector<mud::Circle>;
}
#endif
