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
        .field("normal", &mud::Plane::normal)
        .field("distance", &mud::Plane::distance)
        ;
    value_object<mud::Plane3>("Plane3")
        .field("origin", &mud::Plane3::origin)
        .field("a", &mud::Plane3::a)
        .field("b", &mud::Plane3::b)
        ;
    value_object<mud::Ray>("Ray")
        .field("start", &mud::Ray::start)
        .field("end", &mud::Ray::end)
        .field("dir", &mud::Ray::dir)
        .field("inv_dir", &mud::Ray::inv_dir)
        ;
    value_object<mud::Segment>("Segment")
        .field("start", &mud::Segment::start)
        .field("end", &mud::Segment::end)
        ;
    value_object<mud::ShapeVar>("ShapeVar")
        .field("shape", &mud::ShapeVar::shape)
        ;
    value_object<mud::Symbol>("Symbol")
        .field("outline", &mud::Symbol::outline)
        .field("fill", &mud::Symbol::fill)
        .field("overlay", &mud::Symbol::overlay)
        .field("double_sided", &mud::Symbol::double_sided)
        .field("detail", &mud::Symbol::detail)
        .field("image", &mud::Symbol::image)
        .field("image256", &mud::Symbol::image256)
        .field("program", &mud::Symbol::program)
        ;
    value_object<mud::Arc>("Arc")
        .field("radius", &mud::Arc::radius)
        .field("start", &mud::Arc::start)
        .field("end", &mud::Arc::end)
        ;
    value_object<mud::ArcLine>("ArcLine")
        .field("start", &mud::ArcLine::start)
        .field("middle", &mud::ArcLine::middle)
        .field("end", &mud::ArcLine::end)
        ;
    value_object<mud::Capsule>("Capsule")
        .field("radius", &mud::Capsule::radius)
        .field("height", &mud::Capsule::height)
        .field("axis", &mud::Capsule::axis)
        ;
    value_object<mud::Cube>("Cube")
        .field("extents", &mud::Cube::extents)
        ;
    value_object<mud::Aabb>("Aabb")
        .field("empty", &mud::Aabb::empty)
        ;
    value_object<mud::Box>("Box")
        ;
    value_object<mud::Circle>("Circle")
        .field("radius", &mud::Circle::radius)
        .field("axis", &mud::Circle::axis)
        ;
    value_object<mud::ConvexHull>("ConvexHull")
        .field("vertices", &mud::ConvexHull::vertices)
        ;
    value_object<mud::Cylinder>("Cylinder")
        .field("radius", &mud::Cylinder::radius)
        .field("height", &mud::Cylinder::height)
        .field("axis", &mud::Cylinder::axis)
        ;
    value_object<mud::Ellipsis>("Ellipsis")
        .field("radius", &mud::Ellipsis::radius)
        .field("axis", &mud::Ellipsis::axis)
        ;
    value_object<mud::Grid2>("Grid2")
        .field("size", &mud::Grid2::size)
        .field("space", &mud::Grid2::space)
        ;
    value_object<mud::Grid3>("Grid3")
        .field("size", &mud::Grid3::size)
        .field("points", &mud::Grid3::points)
        ;
    value_object<mud::Line>("Line")
        .field("start", &mud::Line::start)
        .field("end", &mud::Line::end)
        ;
    value_object<mud::Points>("Points")
        .field("points", &mud::Points::points)
        ;
    value_object<mud::Polygon>("Polygon")
        ;
    value_object<mud::Quad>("Quad")
        ;
    value_object<mud::Rect>("Rect")
        .field("position", &mud::Rect::position)
        .field("size", &mud::Rect::size)
        ;
    value_object<mud::Ring>("Ring")
        .field("radius", &mud::Ring::radius)
        .field("min", &mud::Ring::min)
        .field("max", &mud::Ring::max)
        ;
    value_object<mud::Sphere>("Sphere")
        .field("radius", &mud::Sphere::radius)
        ;
    value_object<mud::SphereRing>("SphereRing")
        .field("radius", &mud::SphereRing::radius)
        .field("min", &mud::SphereRing::min)
        .field("max", &mud::SphereRing::max)
        ;
    value_object<mud::Spheroid>("Spheroid")
        .field("radius", &mud::Spheroid::radius)
        ;
    value_object<mud::Torus>("Torus")
        .field("radius", &mud::Torus::radius)
        .field("solid_radius", &mud::Torus::solid_radius)
        .field("axis", &mud::Torus::axis)
        ;
    value_object<mud::Triangle>("Triangle")
        .field("size", &mud::Triangle::size)
        ;
    
    // Classes
    class_<mud::Distribution>("Distribution")
        ;
    class_<mud::Shape>("Shape")
        .property("type", &mud::Shape::type)
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
