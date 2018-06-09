#pragma once

#include <geom/Forward.h>

#if !defined MUD_MODULES || defined MUD_OBJ_LIB
#include <obj/Type.h>
//#include <proto/Proto.h>
#endif

#ifndef MUD_MODULES
#include <obj/Types.h>
#include <math/Types.h>
#endif

#ifndef MUD_CPP_20
#include <string>
#include <vector>
#include <cstdint>
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
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Aabb>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Poisson>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Arc>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Box>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Capsule>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Circle>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::ConvexHull>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Cube>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Cylinder>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Ellipsis>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Geometry>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Grid2>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Line>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Points>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Polygon>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Quad>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Rect>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Ring>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Sphere>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::SphereRing>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Spheroid>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Torus>();
    export_ template <> MUD_GEOM_EXPORT Type& type<mud::Triangle>();
}
