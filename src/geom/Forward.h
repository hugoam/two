#pragma once

#include <infra/Config.h>

#ifndef TWO_GEOM_EXPORT
#define TWO_GEOM_EXPORT TWO_IMPORT
#endif

namespace two
{
    export_ enum DrawMode : unsigned int;
    export_ enum class PrimitiveType : unsigned int;
    export_ enum class SymbolDetail : unsigned short;
	export_ enum class CatmullType : unsigned int;
    
    export_ class Shape;
    export_ class ShapeVar;
    export_ struct Line;
    export_ struct Rect;
    export_ struct Quad;
    export_ struct Grid2;
    export_ struct Triangle;
    export_ struct Circle;
    export_ struct Torus;
	export_ struct TorusKnot;
    export_ struct Ring;
    export_ struct Ellipsis;
    export_ struct Arc;
    export_ struct ArcLine;
    export_ struct Cylinder;
    export_ struct Capsule;
    export_ struct Cube;
	export_ struct Tetraedr;
    export_ struct Sphere;
    export_ struct SphereRing;
    export_ struct Spheroid;
	export_ struct Icosaedr;
    export_ struct Aabb;
	export_ class Curve2;
	export_ class Curve3;
	export_ struct CurveBezierCubic;
	export_ struct CurveBezierCubic3;
	export_ struct CurveBezierQuadratic;
	export_ struct CurveBezierQuadratic3;
	export_ struct CurveCatmullRom3;
	export_ struct CurveLine;
	export_ struct CurveLine3;
	export_ struct CurveSpline;
	export_ struct CurveSpline3;
    export_ struct Plane;
    export_ struct Plane3;
    export_ struct Face3;
    export_ struct Segment;
    export_ struct Ray;
    export_ struct Plane6;
    export_ struct Point8;
    export_ struct VertexAttribute;
    export_ struct Vertex;
    export_ struct Tri;
    export_ struct ShapeVertex;
    export_ struct ShapeTriangle;
    export_ struct MeshAdapter;
    export_ class Geometry;
    export_ struct MeshPacker;
	export_ class MarchingCubes;
    export_ class Distribution;
    export_ class Poisson;
    export_ class RandomShapePoint;
    export_ struct Polygon;
    export_ struct Box;
    export_ struct Points;
    export_ struct Grid3;
    export_ struct ConvexHull;
    export_ struct Symbol;
    export_ struct ShapeSize;
    export_ struct ProcShape;
    export_ struct CompoundShape;
    export_ struct DispatchDrawProcShape;
    export_ class IcoSphere;
}

#ifdef TWO_META_GENERATOR
#include <stl/vector.h>
#include <stl/span.h>
namespace stl
{
	extern template struct refl_ span_ span<two::vec3>;

	extern template class refl_ seque_ vector<two::vec2>;
	extern template class refl_ seque_ vector<two::vec4>;
	extern template class refl_ seque_ vector<two::ivec4>;

	extern template class refl_ seque_ vector<two::Circle>;
}
#endif
