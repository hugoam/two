module;
#include <infra/Cpp20.h>
module two.geom;

namespace two
{
    // Exported types
    template <> TWO_GEOM_EXPORT Type& type<two::CatmullType>() { static Type ty("CatmullType", sizeof(two::CatmullType)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::DrawMode>() { static Type ty("DrawMode", sizeof(two::DrawMode)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::PrimitiveType>() { static Type ty("PrimitiveType", sizeof(two::PrimitiveType)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::SymbolDetail>() { static Type ty("SymbolDetail", sizeof(two::SymbolDetail)); return ty; }
    
    template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::vec2>>() { static Type ty("vector<two::vec2>", sizeof(stl::vector<two::vec2>)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::vec4>>() { static Type ty("vector<two::vec4>", sizeof(stl::vector<two::vec4>)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::ivec4>>() { static Type ty("vector<two::ivec4>", sizeof(stl::vector<two::ivec4>)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::Circle>>() { static Type ty("vector<two::Circle>", sizeof(stl::vector<two::Circle>)); return ty; }
    
    template <> TWO_GEOM_EXPORT Type& type<two::Aabb>() { static Type ty("Aabb", sizeof(two::Aabb)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Curve2>() { static Type ty("Curve2", sizeof(two::Curve2)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Curve3>() { static Type ty("Curve3", sizeof(two::Curve3)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::CurveSpline>() { static Type ty("CurveSpline", type<two::Curve2>(), sizeof(two::CurveSpline)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::CurveSpline3>() { static Type ty("CurveSpline3", type<two::Curve3>(), sizeof(two::CurveSpline3)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierCubic>() { static Type ty("CurveBezierCubic", type<two::Curve2>(), sizeof(two::CurveBezierCubic)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierCubic3>() { static Type ty("CurveBezierCubic3", type<two::Curve3>(), sizeof(two::CurveBezierCubic3)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::CurveLine>() { static Type ty("CurveLine", type<two::Curve2>(), sizeof(two::CurveLine)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::CurveLine3>() { static Type ty("CurveLine3", type<two::Curve3>(), sizeof(two::CurveLine3)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierQuadratic>() { static Type ty("CurveBezierQuadratic", type<two::Curve2>(), sizeof(two::CurveBezierQuadratic)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierQuadratic3>() { static Type ty("CurveBezierQuadratic3", type<two::Curve3>(), sizeof(two::CurveBezierQuadratic3)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::CurveCatmullRom3>() { static Type ty("CurveCatmullRom3", type<two::Curve3>(), sizeof(two::CurveCatmullRom3)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Plane>() { static Type ty("Plane", sizeof(two::Plane)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Plane3>() { static Type ty("Plane3", sizeof(two::Plane3)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Face3>() { static Type ty("Face3", sizeof(two::Face3)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Segment>() { static Type ty("Segment", sizeof(two::Segment)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Ray>() { static Type ty("Ray", sizeof(two::Ray)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::MeshAdapter>() { static Type ty("MeshAdapter", sizeof(two::MeshAdapter)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Shape>() { static Type ty("Shape", sizeof(two::Shape)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::ShapeVar>() { static Type ty("ShapeVar", sizeof(two::ShapeVar)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Geometry>() { static Type ty("Geometry", type<two::Shape>(), sizeof(two::Geometry)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::MeshPacker>() { static Type ty("MeshPacker", sizeof(two::MeshPacker)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Line>() { static Type ty("Line", type<two::Shape>(), sizeof(two::Line)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Rect>() { static Type ty("Rect", type<two::Shape>(), sizeof(two::Rect)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Quad>() { static Type ty("Quad", type<two::Shape>(), sizeof(two::Quad)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Grid2>() { static Type ty("Grid2", type<two::Shape>(), sizeof(two::Grid2)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Triangle>() { static Type ty("Triangle", type<two::Shape>(), sizeof(two::Triangle)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Circle>() { static Type ty("Circle", type<two::Shape>(), sizeof(two::Circle)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Torus>() { static Type ty("Torus", type<two::Shape>(), sizeof(two::Torus)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::TorusKnot>() { static Type ty("TorusKnot", type<two::Shape>(), sizeof(two::TorusKnot)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Ring>() { static Type ty("Ring", type<two::Shape>(), sizeof(two::Ring)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Ellipsis>() { static Type ty("Ellipsis", type<two::Shape>(), sizeof(two::Ellipsis)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Arc>() { static Type ty("Arc", type<two::Shape>(), sizeof(two::Arc)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::ArcLine>() { static Type ty("ArcLine", type<two::Shape>(), sizeof(two::ArcLine)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Cylinder>() { static Type ty("Cylinder", type<two::Shape>(), sizeof(two::Cylinder)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Capsule>() { static Type ty("Capsule", type<two::Shape>(), sizeof(two::Capsule)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Cube>() { static Type ty("Cube", type<two::Shape>(), sizeof(two::Cube)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Tetraedr>() { static Type ty("Tetraedr", type<two::Shape>(), sizeof(two::Tetraedr)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Sphere>() { static Type ty("Sphere", type<two::Shape>(), sizeof(two::Sphere)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::SphereRing>() { static Type ty("SphereRing", type<two::Shape>(), sizeof(two::SphereRing)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Spheroid>() { static Type ty("Spheroid", type<two::Shape>(), sizeof(two::Spheroid)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Icosaedr>() { static Type ty("Icosaedr", type<two::Shape>(), sizeof(two::Icosaedr)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Distribution>() { static Type ty("Distribution", sizeof(two::Distribution)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Poisson>() { static Type ty("Poisson", type<two::Distribution>(), sizeof(two::Poisson)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Polygon>() { static Type ty("Polygon", type<two::Shape>(), sizeof(two::Polygon)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Box>() { static Type ty("Box", type<two::Shape>(), sizeof(two::Box)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Points>() { static Type ty("Points", type<two::Shape>(), sizeof(two::Points)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Grid3>() { static Type ty("Grid3", type<two::Shape>(), sizeof(two::Grid3)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::ConvexHull>() { static Type ty("ConvexHull", type<two::Shape>(), sizeof(two::ConvexHull)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::Symbol>() { static Type ty("Symbol", sizeof(two::Symbol)); return ty; }
    template <> TWO_GEOM_EXPORT Type& type<two::MarchingCubes>() { static Type ty("MarchingCubes", sizeof(two::MarchingCubes)); return ty; }
}
