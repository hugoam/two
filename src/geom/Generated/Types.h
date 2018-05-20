#pragma once

#include <geom/Generated/Forward.h>

#include <obj/Generated/Types.h>
#include <math/Generated/Types.h>

#include <obj/Type.h>
#include <obj/Proto.h>

#include <string>
#include <vector>
#include <stdint.h>


namespace mud
{
    // Exported types
    template <> MUD_GEOM_EXPORT Type& type<mud::DrawMode>();
    template <> MUD_GEOM_EXPORT Type& type<mud::PrimitiveType>();
    template <> MUD_GEOM_EXPORT Type& type<mud::SymbolDetail>();
    template <> MUD_GEOM_EXPORT Type& type<std::vector<mud::Circle>>();
    template <> MUD_GEOM_EXPORT Type& type<std::vector<mud::vec3>>();
    
    template <> MUD_GEOM_EXPORT Type& type<mud::Distribution>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Face3>();
    template <> MUD_GEOM_EXPORT Type& type<mud::MeshPacker>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Plane>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Plane3>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Ray>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Segment>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Shape>();
    template <> MUD_GEOM_EXPORT Type& type<mud::ShapeVar>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Symbol>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Arc>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Box>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Capsule>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Circle>();
    template <> MUD_GEOM_EXPORT Type& type<mud::ConvexHull>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Cube>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Cylinder>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Ellipsis>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Geometry>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Grid2>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Line>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Points>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Polygon>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Quad>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Rect>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Ring>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Sphere>();
    template <> MUD_GEOM_EXPORT Type& type<mud::SphereRing>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Spheroid>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Triangle>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Aabb>();
    template <> MUD_GEOM_EXPORT Type& type<mud::Poisson>();
}
