#pragma once

#include <stdint.h>
#include <stl/string.h>
#include <stl/vector.h>
#include <geom/Forward.h>

#if !defined TWO_MODULES || defined TWO_TYPE_LIB
#include <type/Type.h>
#endif

#ifndef TWO_MODULES
#include <type/Types.h>
#include <math/Types.h>
#endif


namespace two
{
    // Exported types
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CatmullType>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::DrawMode>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::PrimitiveType>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::SymbolDetail>();
    
    export_ template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::vec2>>();
    export_ template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::vec4>>();
    export_ template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::ivec4>>();
    export_ template <> TWO_GEOM_EXPORT Type& type<stl::vector<two::Circle>>();
    
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Aabb>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Curve2>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Curve3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveSpline>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveSpline3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierCubic>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierCubic3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveLine>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveLine3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierQuadratic>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveBezierQuadratic3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::CurveCatmullRom3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Plane>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Plane3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Face3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Segment>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Ray>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::MeshAdapter>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Shape>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::ShapeVar>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Geometry>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::MeshPacker>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Line>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Rect>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Quad>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Grid2>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Triangle>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Circle>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Torus>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::TorusKnot>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Ring>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Ellipsis>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Arc>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::ArcLine>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Cylinder>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Capsule>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Cube>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Tetraedr>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Sphere>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::SphereRing>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Spheroid>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Icosaedr>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Distribution>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Poisson>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Polygon>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Box>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Points>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Grid3>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::ConvexHull>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::Symbol>();
    export_ template <> TWO_GEOM_EXPORT Type& type<two::MarchingCubes>();
}
