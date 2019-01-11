#include <geom/Api.h>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(mud_geom)
{
    
    // Enums
    enum_<mud::DrawMode>("mud::DrawMode")
        .value("OUTLINE", mud::OUTLINE)
        .value("PLAIN", mud::PLAIN)
        ;
    enum_<mud::PrimitiveType>("mud::PrimitiveType")
        .value("Points", mud::PrimitiveType::Points)
        .value("Lines", mud::PrimitiveType::Lines)
        .value("LineLoop", mud::PrimitiveType::LineLoop)
        .value("LineStrip", mud::PrimitiveType::LineStrip)
        .value("Triangles", mud::PrimitiveType::Triangles)
        .value("TriangleStrip", mud::PrimitiveType::TriangleStrip)
        .value("TriangleFan", mud::PrimitiveType::TriangleFan)
        ;
    enum_<mud::SymbolDetail>("mud::SymbolDetail")
        .value("Lowest", mud::SymbolDetail::Lowest)
        .value("Low", mud::SymbolDetail::Low)
        .value("Medium", mud::SymbolDetail::Medium)
        .value("High", mud::SymbolDetail::High)
        .value("Highest", mud::SymbolDetail::Highest)
        ;
    
    // Sequences
    
    // Arrays
    
    // Structs
    value_object<mud::Face3>("Face3")
        ;
    value_object<mud::MeshPacker>("MeshPacker")
        ;
    value_object<mud::Plane>("Plane")
        .field("normal", &mud::Plane::m_normal)
        .field("distance", &mud::Plane::m_distance)
        ;
    value_object<mud::Plane3>("Plane3")
        .field("origin", &mud::Plane3::m_origin)
        .field("a", &mud::Plane3::m_a)
        .field("b", &mud::Plane3::m_b)
        ;
    value_object<mud::Ray>("Ray")
        .field("start", &mud::Ray::m_start)
        .field("end", &mud::Ray::m_end)
        .field("dir", &mud::Ray::m_dir)
        .field("inv_dir", &mud::Ray::m_inv_dir)
        ;
    value_object<mud::Segment>("Segment")
        .field("start", &mud::Segment::m_start)
        .field("end", &mud::Segment::m_end)
        ;
    value_object<mud::ShapeVar>("ShapeVar")
        .field("shape", &mud::ShapeVar::shape)
        ;
    value_object<mud::Symbol>("Symbol")
        .field("outline", &mud::Symbol::m_outline)
        .field("fill", &mud::Symbol::m_fill)
        .field("overlay", &mud::Symbol::m_overlay)
        .field("double_sided", &mud::Symbol::m_double_sided)
        .field("detail", &mud::Symbol::m_detail)
        .field("image", &mud::Symbol::m_image)
        .field("image256", &mud::Symbol::m_image256)
        .field("program", &mud::Symbol::m_program)
        ;
    value_object<mud::Arc>("Arc")
        .field("radius", &mud::Arc::m_radius)
        .field("start", &mud::Arc::m_start)
        .field("end", &mud::Arc::m_end)
        ;
    value_object<mud::ArcLine>("ArcLine")
        .field("start", &mud::ArcLine::m_start)
        .field("middle", &mud::ArcLine::m_middle)
        .field("end", &mud::ArcLine::m_end)
        ;
    value_object<mud::Capsule>("Capsule")
        .field("radius", &mud::Capsule::m_radius)
        .field("height", &mud::Capsule::m_height)
        .field("axis", &mud::Capsule::m_axis)
        ;
    value_object<mud::Cube>("Cube")
        .field("extents", &mud::Cube::m_extents)
        ;
    value_object<mud::Aabb>("Aabb")
        .field("empty", &mud::Aabb::m_empty)
        ;
    value_object<mud::Box>("Box")
        ;
    value_object<mud::Circle>("Circle")
        .field("radius", &mud::Circle::m_radius)
        .field("axis", &mud::Circle::m_axis)
        ;
    value_object<mud::ConvexHull>("ConvexHull")
        .field("vertices", &mud::ConvexHull::m_vertices)
        ;
    value_object<mud::Cylinder>("Cylinder")
        .field("radius", &mud::Cylinder::m_radius)
        .field("height", &mud::Cylinder::m_height)
        .field("axis", &mud::Cylinder::m_axis)
        ;
    value_object<mud::Ellipsis>("Ellipsis")
        .field("radius", &mud::Ellipsis::m_radius)
        .field("axis", &mud::Ellipsis::m_axis)
        ;
    value_object<mud::Grid2>("Grid2")
        .field("size", &mud::Grid2::m_size)
        .field("space", &mud::Grid2::m_space)
        ;
    value_object<mud::Grid3>("Grid3")
        .field("size", &mud::Grid3::m_size)
        .field("points", &mud::Grid3::m_points)
        ;
    value_object<mud::Line>("Line")
        .field("start", &mud::Line::m_start)
        .field("end", &mud::Line::m_end)
        ;
    value_object<mud::Points>("Points")
        .field("points", &mud::Points::m_points)
        ;
    value_object<mud::Polygon>("Polygon")
        ;
    value_object<mud::Quad>("Quad")
        ;
    value_object<mud::Rect>("Rect")
        .field("position", &mud::Rect::m_position)
        .field("size", &mud::Rect::m_size)
        ;
    value_object<mud::Ring>("Ring")
        .field("radius", &mud::Ring::m_radius)
        .field("min", &mud::Ring::m_min)
        .field("max", &mud::Ring::m_max)
        ;
    value_object<mud::Sphere>("Sphere")
        .field("radius", &mud::Sphere::m_radius)
        ;
    value_object<mud::SphereRing>("SphereRing")
        .field("radius", &mud::SphereRing::m_radius)
        .field("min", &mud::SphereRing::m_min)
        .field("max", &mud::SphereRing::m_max)
        ;
    value_object<mud::Spheroid>("Spheroid")
        .field("radius", &mud::Spheroid::m_radius)
        ;
    value_object<mud::Torus>("Torus")
        .field("radius", &mud::Torus::m_radius)
        .field("solid_radius", &mud::Torus::m_solid_radius)
        .field("axis", &mud::Torus::m_axis)
        ;
    value_object<mud::Triangle>("Triangle")
        .field("size", &mud::Triangle::m_size)
        ;
    
    // Classes
    class_<mud::Distribution>("Distribution")
        ;
    class_<mud::Shape>("Shape")
        .property("type", &mud::Shape::m_type)
        ;
    class_<mud::Geometry>("Geometry")
        .constructor<>()
        ;
    class_<mud::Poisson>("Poisson")
        .constructor<mud::vec2, float>()
        .function("distribute", &mud::Poisson::distribute)
        .function("distribute_circles", &mud::Poisson::distribute_circles)
        .function("addPoint", &mud::Poisson::addPoint)
        ;
    
    // Functions
    function("to_ray", &mud::to_ray);
    function("to_segment", &mud::to_segment);
    function("distribute_poisson", &mud::distribute_poisson);
    
}
