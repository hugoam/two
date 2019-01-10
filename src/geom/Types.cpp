#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#include <geom/Types.h>
#include <geom/Api.h>
#include <type/Vector.h>
#endif

namespace mud
{
    // Exported types
    template <> MUD_GEOM_EXPORT Type& type<mud::DrawMode>() { static Type ty("mud::DrawMode", sizeof(mud::DrawMode)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::PrimitiveType>() { static Type ty("mud::PrimitiveType", sizeof(mud::PrimitiveType)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::SymbolDetail>() { static Type ty("mud::SymbolDetail", sizeof(mud::SymbolDetail)); return ty; }
    
    template <> MUD_GEOM_EXPORT Type& type<mud::Distribution>() { static Type ty("Distribution", sizeof(mud::Distribution)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Face3>() { static Type ty("Face3", sizeof(mud::Face3)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::MeshPacker>() { static Type ty("MeshPacker", sizeof(mud::MeshPacker)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Plane>() { static Type ty("Plane", sizeof(mud::Plane)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Plane3>() { static Type ty("Plane3", sizeof(mud::Plane3)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Ray>() { static Type ty("Ray", sizeof(mud::Ray)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Segment>() { static Type ty("Segment", sizeof(mud::Segment)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Shape>() { static Type ty("Shape", sizeof(mud::Shape)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::ShapeVar>() { static Type ty("ShapeVar", sizeof(mud::ShapeVar)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Symbol>() { static Type ty("Symbol", sizeof(mud::Symbol)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Arc>() { static Type ty("Arc", type<mud::Shape>(), sizeof(mud::Arc)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::ArcLine>() { static Type ty("ArcLine", type<mud::Shape>(), sizeof(mud::ArcLine)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Capsule>() { static Type ty("Capsule", type<mud::Shape>(), sizeof(mud::Capsule)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Cube>() { static Type ty("Cube", type<mud::Shape>(), sizeof(mud::Cube)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Aabb>() { static Type ty("Aabb", type<mud::Cube>(), sizeof(mud::Aabb)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Box>() { static Type ty("Box", type<mud::Shape>(), sizeof(mud::Box)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Circle>() { static Type ty("Circle", type<mud::Shape>(), sizeof(mud::Circle)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::ConvexHull>() { static Type ty("ConvexHull", type<mud::Shape>(), sizeof(mud::ConvexHull)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Cylinder>() { static Type ty("Cylinder", type<mud::Shape>(), sizeof(mud::Cylinder)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Ellipsis>() { static Type ty("Ellipsis", type<mud::Shape>(), sizeof(mud::Ellipsis)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Geometry>() { static Type ty("Geometry", type<mud::Shape>(), sizeof(mud::Geometry)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Grid2>() { static Type ty("Grid2", type<mud::Shape>(), sizeof(mud::Grid2)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Grid3>() { static Type ty("Grid3", type<mud::Shape>(), sizeof(mud::Grid3)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Line>() { static Type ty("Line", type<mud::Shape>(), sizeof(mud::Line)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Points>() { static Type ty("Points", type<mud::Shape>(), sizeof(mud::Points)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Poisson>() { static Type ty("Poisson", type<mud::Distribution>(), sizeof(mud::Poisson)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Polygon>() { static Type ty("Polygon", type<mud::Shape>(), sizeof(mud::Polygon)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Quad>() { static Type ty("Quad", type<mud::Shape>(), sizeof(mud::Quad)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Rect>() { static Type ty("Rect", type<mud::Shape>(), sizeof(mud::Rect)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Ring>() { static Type ty("Ring", type<mud::Shape>(), sizeof(mud::Ring)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Sphere>() { static Type ty("Sphere", type<mud::Shape>(), sizeof(mud::Sphere)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::SphereRing>() { static Type ty("SphereRing", type<mud::Shape>(), sizeof(mud::SphereRing)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Spheroid>() { static Type ty("Spheroid", type<mud::Shape>(), sizeof(mud::Spheroid)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Torus>() { static Type ty("Torus", type<mud::Shape>(), sizeof(mud::Torus)); return ty; }
    template <> MUD_GEOM_EXPORT Type& type<mud::Triangle>() { static Type ty("Triangle", type<mud::Shape>(), sizeof(mud::Triangle)); return ty; }
}
