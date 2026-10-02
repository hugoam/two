#pragma once

#include <geom/Forward.h>

#if defined TWO_TYPE_LIB
#include <type/Type.h>
#endif


namespace two
{
    // Exported types
    template <> TWO_GEOM_EXPORT Type& type<two::CatmullType>();
    template <> TWO_GEOM_EXPORT Type& type<two::DrawMode>();
    template <> TWO_GEOM_EXPORT Type& type<two::PrimitiveType>();
    template <> TWO_GEOM_EXPORT Type& type<two::SymbolDetail>();
    
    template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::vec2>>();
    template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::vec4>>();
    template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::ivec4>>();
    template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::Circle>>();
    
    template <> TWO_GEOM_EXPORT Type& type<two::Aabb>();
    template <> TWO_GEOM_EXPORT Type& type<two::Curve2>();
    template <> TWO_GEOM_EXPORT Type& type<two::Curve3>();
    template <> TWO_GEOM_EXPORT Type& type<two::CurveSpline>();
    template <> TWO_GEOM_EXPORT Type& type<two::CurveSpline3>();
    template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierCubic>();
    template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierCubic3>();
    template <> TWO_GEOM_EXPORT Type& type<two::CurveLine>();
    template <> TWO_GEOM_EXPORT Type& type<two::CurveLine3>();
    template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierQuadratic>();
    template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierQuadratic3>();
    template <> TWO_GEOM_EXPORT Type& type<two::CurveCatmullRom3>();
    template <> TWO_GEOM_EXPORT Type& type<two::Plane>();
    template <> TWO_GEOM_EXPORT Type& type<two::Plane3>();
    template <> TWO_GEOM_EXPORT Type& type<two::Face3>();
    template <> TWO_GEOM_EXPORT Type& type<two::Segment>();
    template <> TWO_GEOM_EXPORT Type& type<two::Ray>();
    template <> TWO_GEOM_EXPORT Type& type<two::MeshAdapter>();
    template <> TWO_GEOM_EXPORT Type& type<two::Shape>();
    template <> TWO_GEOM_EXPORT Type& type<two::ShapeVar>();
    template <> TWO_GEOM_EXPORT Type& type<two::Geometry>();
    template <> TWO_GEOM_EXPORT Type& type<two::MeshPacker>();
    template <> TWO_GEOM_EXPORT Type& type<two::Line>();
    template <> TWO_GEOM_EXPORT Type& type<two::Rect>();
    template <> TWO_GEOM_EXPORT Type& type<two::Quad>();
    template <> TWO_GEOM_EXPORT Type& type<two::Grid2>();
    template <> TWO_GEOM_EXPORT Type& type<two::Triangle>();
    template <> TWO_GEOM_EXPORT Type& type<two::Circle>();
    template <> TWO_GEOM_EXPORT Type& type<two::Torus>();
    template <> TWO_GEOM_EXPORT Type& type<two::TorusKnot>();
    template <> TWO_GEOM_EXPORT Type& type<two::Ring>();
    template <> TWO_GEOM_EXPORT Type& type<two::Ellipsis>();
    template <> TWO_GEOM_EXPORT Type& type<two::Arc>();
    template <> TWO_GEOM_EXPORT Type& type<two::ArcLine>();
    template <> TWO_GEOM_EXPORT Type& type<two::Cylinder>();
    template <> TWO_GEOM_EXPORT Type& type<two::Capsule>();
    template <> TWO_GEOM_EXPORT Type& type<two::Cube>();
    template <> TWO_GEOM_EXPORT Type& type<two::Tetraedr>();
    template <> TWO_GEOM_EXPORT Type& type<two::Sphere>();
    template <> TWO_GEOM_EXPORT Type& type<two::SphereRing>();
    template <> TWO_GEOM_EXPORT Type& type<two::Spheroid>();
    template <> TWO_GEOM_EXPORT Type& type<two::Icosaedr>();
    template <> TWO_GEOM_EXPORT Type& type<two::Distribution>();
    template <> TWO_GEOM_EXPORT Type& type<two::Poisson>();
    template <> TWO_GEOM_EXPORT Type& type<two::Polygon>();
    template <> TWO_GEOM_EXPORT Type& type<two::Box>();
    template <> TWO_GEOM_EXPORT Type& type<two::Points>();
    template <> TWO_GEOM_EXPORT Type& type<two::Grid3>();
    template <> TWO_GEOM_EXPORT Type& type<two::ConvexHull>();
    template <> TWO_GEOM_EXPORT Type& type<two::Symbol>();
    template <> TWO_GEOM_EXPORT Type& type<two::MarchingCubes>();
}
