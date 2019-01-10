#pragma once

#include <geom/Forward.h>

#if !defined MUD_MODULES || defined MUD_TYPE_LIB
#include <type/Type.h>
#include <type/Vector.h>
#endif

#ifndef MUD_MODULES
#include <type/Types.h>
#include <math/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <cstdint>
#include <vector>
#endif


namespace mud
{
    // Exported types
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::DrawMode>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::PrimitiveType>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::SymbolDetail>();
    
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Distribution>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Face3>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::MeshPacker>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Plane>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Plane3>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Ray>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Segment>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Shape>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::ShapeVar>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Symbol>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Arc>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::ArcLine>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Capsule>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Cube>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Aabb>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Box>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Circle>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::ConvexHull>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Cylinder>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Ellipsis>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Geometry>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Grid2>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Grid3>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Line>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Points>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Poisson>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Polygon>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Quad>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Rect>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Ring>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Sphere>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::SphereRing>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Spheroid>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Torus>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Triangle>();
    
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Distribution*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Face3*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::MeshPacker*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Plane*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Plane3*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Ray*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Segment*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Shape*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::ShapeVar*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Symbol*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Arc*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::ArcLine*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Capsule*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Cube*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Aabb*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Box*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Circle*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::ConvexHull*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Cylinder*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Ellipsis*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Geometry*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Grid2*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Grid3*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Line*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Points*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Poisson*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Polygon*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Quad*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Rect*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Ring*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Sphere*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::SphereRing*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Spheroid*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Torus*>>;
    export_ template struct MUD_GEOM_EXPORT Typed<std::vector<mud::Triangle*>>;
}
