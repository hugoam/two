#pragma once

#ifndef MUD_MODULES
#include <meta/geom/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_geom_meta(Module& m)
    {
    UNUSED(m);
    
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<mud::DrawMode>(), &namspc({ "mud" }), "DrawMode", sizeof(mud::DrawMode), TypeClass::Enum };
        static Enum enu = { type<mud::DrawMode>(),
            false,
            { "OUTLINE", "PLAIN" },
            { 0, 1 },
            { var(mud::OUTLINE), var(mud::PLAIN) }
        };
        meta_enum<mud::DrawMode>();
    }
    {
        static Meta meta = { type<mud::PrimitiveType>(), &namspc({ "mud" }), "PrimitiveType", sizeof(mud::PrimitiveType), TypeClass::Enum };
        static Enum enu = { type<mud::PrimitiveType>(),
            true,
            { "Points", "Lines", "LineLoop", "LineStrip", "Triangles", "TriangleStrip", "TriangleFan" },
            { 0, 1, 2, 3, 4, 5, 6 },
            { var(mud::PrimitiveType::Points), var(mud::PrimitiveType::Lines), var(mud::PrimitiveType::LineLoop), var(mud::PrimitiveType::LineStrip), var(mud::PrimitiveType::Triangles), var(mud::PrimitiveType::TriangleStrip), var(mud::PrimitiveType::TriangleFan) }
        };
        meta_enum<mud::PrimitiveType>();
    }
    {
        static Meta meta = { type<mud::SymbolDetail>(), &namspc({ "mud" }), "SymbolDetail", sizeof(mud::SymbolDetail), TypeClass::Enum };
        static Enum enu = { type<mud::SymbolDetail>(),
            true,
            { "Lowest", "Low", "Medium", "High", "Highest" },
            { 0, 1, 2, 3, 4 },
            { var(mud::SymbolDetail::Lowest), var(mud::SymbolDetail::Low), var(mud::SymbolDetail::Medium), var(mud::SymbolDetail::High), var(mud::SymbolDetail::Highest) }
        };
        meta_enum<mud::SymbolDetail>();
    }
    
    // Sequences
    {
        static Meta meta = { type<vector<mud::Circle>>(), &namspc({}), "vector<mud::Circle>", sizeof(vector<mud::Circle>), TypeClass::Sequence };
        static Class cls = { type<vector<mud::Circle>>() };
        cls.m_content = &type<mud::Circle>();
        meta_vector<vector<mud::Circle>, mud::Circle>();
    }
    
    // mud::Distribution
    {
        static Meta meta = { type<mud::Distribution>(), &namspc({ "mud" }), "Distribution", sizeof(mud::Distribution), TypeClass::Object };
        static Class cls = { type<mud::Distribution>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Distribution>();
    }
    // mud::Face3
    {
        static Meta meta = { type<mud::Face3>(), &namspc({ "mud" }), "Face3", sizeof(mud::Face3), TypeClass::Struct };
        static Class cls = { type<mud::Face3>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Face3>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Face3>(ref)) mud::Face3(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Face3>(), [](Ref ref, Ref other) { new(&val<mud::Face3>(ref)) mud::Face3(val<mud::Face3>(other)); } }
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Face3>();
    }
    // mud::MeshPacker
    {
        static Meta meta = { type<mud::MeshPacker>(), &namspc({ "mud" }), "MeshPacker", sizeof(mud::MeshPacker), TypeClass::Struct };
        static Class cls = { type<mud::MeshPacker>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::MeshPacker>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::MeshPacker>(ref)) mud::MeshPacker(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::MeshPacker>(), [](Ref ref, Ref other) { new(&val<mud::MeshPacker>(ref)) mud::MeshPacker(val<mud::MeshPacker>(other)); } }
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::MeshPacker>();
    }
    // mud::Plane
    {
        static Meta meta = { type<mud::Plane>(), &namspc({ "mud" }), "Plane", sizeof(mud::Plane), TypeClass::Struct };
        static Class cls = { type<mud::Plane>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Plane>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Plane>(ref)) mud::Plane(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Plane>(), [](Ref ref, Ref other) { new(&val<mud::Plane>(ref)) mud::Plane(val<mud::Plane>(other)); } }
            },
            // members
            {
                { type<mud::Plane>(), member_address(&mud::Plane::m_normal), type<mud::vec3>(), "normal", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::Plane>(), member_address(&mud::Plane::m_distance), type<float>(), "distance", var(float()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Plane>();
    }
    // mud::Plane3
    {
        static Meta meta = { type<mud::Plane3>(), &namspc({ "mud" }), "Plane3", sizeof(mud::Plane3), TypeClass::Struct };
        static Class cls = { type<mud::Plane3>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Plane3>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Plane3>(ref)) mud::Plane3(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Plane3>(), [](Ref ref, Ref other) { new(&val<mud::Plane3>(ref)) mud::Plane3(val<mud::Plane3>(other)); } }
            },
            // members
            {
                { type<mud::Plane3>(), member_address(&mud::Plane3::m_origin), type<mud::vec3>(), "origin", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::Plane3>(), member_address(&mud::Plane3::m_a), type<mud::vec3>(), "a", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::Plane3>(), member_address(&mud::Plane3::m_b), type<mud::vec3>(), "b", var(mud::vec3()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Plane3>();
    }
    // mud::Ray
    {
        static Meta meta = { type<mud::Ray>(), &namspc({ "mud" }), "Ray", sizeof(mud::Ray), TypeClass::Struct };
        static Class cls = { type<mud::Ray>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Ray>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Ray>(ref)) mud::Ray(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Ray>(), [](Ref ref, Ref other) { new(&val<mud::Ray>(ref)) mud::Ray(val<mud::Ray>(other)); } }
            },
            // members
            {
                { type<mud::Ray>(), member_address(&mud::Ray::m_start), type<mud::vec3>(), "start", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::Ray>(), member_address(&mud::Ray::m_end), type<mud::vec3>(), "end", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::Ray>(), member_address(&mud::Ray::m_dir), type<mud::vec3>(), "dir", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::Ray>(), member_address(&mud::Ray::m_inv_dir), type<mud::vec3>(), "inv_dir", var(mud::vec3()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Ray>();
    }
    // mud::Segment
    {
        static Meta meta = { type<mud::Segment>(), &namspc({ "mud" }), "Segment", sizeof(mud::Segment), TypeClass::Struct };
        static Class cls = { type<mud::Segment>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Segment>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Segment>(ref)) mud::Segment(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Segment>(), [](Ref ref, Ref other) { new(&val<mud::Segment>(ref)) mud::Segment(val<mud::Segment>(other)); } }
            },
            // members
            {
                { type<mud::Segment>(), member_address(&mud::Segment::m_start), type<mud::vec3>(), "start", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::Segment>(), member_address(&mud::Segment::m_end), type<mud::vec3>(), "end", var(mud::vec3()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Segment>();
    }
    // mud::Shape
    {
        static Meta meta = { type<mud::Shape>(), &namspc({ "mud" }), "Shape", sizeof(mud::Shape), TypeClass::Object };
        static Class cls = { type<mud::Shape>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Shape>(), Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Shape>(object).m_type); } }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Shape>();
    }
    // mud::ShapeVar
    {
        static Meta meta = { type<mud::ShapeVar>(), &namspc({ "mud" }), "ShapeVar", sizeof(mud::ShapeVar), TypeClass::Struct };
        static Class cls = { type<mud::ShapeVar>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ShapeVar>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ShapeVar>(ref)) mud::ShapeVar(  ); }, {} },
                { type<mud::ShapeVar>(), [](Ref ref, array<Var> args) { new(&val<mud::ShapeVar>(ref)) mud::ShapeVar( val<mud::Shape>(args[0]) ); }, { { "shape", Ref(type<mud::Shape>()) } } }
            },
            // copy constructor
            {
                { type<mud::ShapeVar>(), [](Ref ref, Ref other) { new(&val<mud::ShapeVar>(ref)) mud::ShapeVar(val<mud::ShapeVar>(other)); } }
            },
            // members
            {
                { type<mud::ShapeVar>(), member_address<mud::Shape&(mud::ShapeVar::*)()>(&mud::ShapeVar::shape), type<mud::Shape>(), "shape", Ref(type<mud::Shape>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::ShapeVar>(object).shape()); } }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::ShapeVar>();
    }
    // mud::Symbol
    {
        static Meta meta = { type<mud::Symbol>(), &namspc({ "mud" }), "Symbol", sizeof(mud::Symbol), TypeClass::Struct };
        static Class cls = { type<mud::Symbol>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Symbol>(), [](Ref ref, array<Var> args) { new(&val<mud::Symbol>(ref)) mud::Symbol( val<mud::Colour>(args[0]), val<mud::Colour>(args[1]), val<bool>(args[2]), val<bool>(args[3]), val<mud::SymbolDetail>(args[4]) ); }, { { "fill", var(mud::Colour::White), Param::Default }, { "outline", var(mud::Colour::None), Param::Default }, { "overlay", var(bool(false)), Param::Default }, { "double_sided", var(bool(false)), Param::Default }, { "detail", var(mud::SymbolDetail::Medium), Param::Default } } }
            },
            // copy constructor
            {
                { type<mud::Symbol>(), [](Ref ref, Ref other) { new(&val<mud::Symbol>(ref)) mud::Symbol(val<mud::Symbol>(other)); } }
            },
            // members
            {
                { type<mud::Symbol>(), member_address(&mud::Symbol::m_outline), type<mud::Colour>(), "outline", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::Symbol>(), member_address(&mud::Symbol::m_fill), type<mud::Colour>(), "fill", var(mud::Colour()), Member::Value, nullptr },
                { type<mud::Symbol>(), member_address(&mud::Symbol::m_overlay), type<bool>(), "overlay", var(bool()), Member::Value, nullptr },
                { type<mud::Symbol>(), member_address(&mud::Symbol::m_double_sided), type<bool>(), "double_sided", var(bool()), Member::Value, nullptr },
                { type<mud::Symbol>(), member_address(&mud::Symbol::m_detail), type<mud::SymbolDetail>(), "detail", var(mud::SymbolDetail()), Member::Value, nullptr },
                { type<mud::Symbol>(), member_address(&mud::Symbol::m_image), type<const char*>(), "image", Ref(type<const char*>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::Symbol>(), member_address(&mud::Symbol::m_image256), type<mud::Image256>(), "image256", Ref(type<mud::Image256>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
                { type<mud::Symbol>(), member_address(&mud::Symbol::m_program), type<const char*>(), "program", Ref(type<const char*>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Symbol>();
    }
    // mud::Arc
    {
        static Meta meta = { type<mud::Arc>(), &namspc({ "mud" }), "Arc", sizeof(mud::Arc), TypeClass::Struct };
        static Class cls = { type<mud::Arc>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Arc, mud::Shape>() },
            // constructors
            {
                { type<mud::Arc>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Arc>(ref)) mud::Arc(  ); }, {} },
                { type<mud::Arc>(), [](Ref ref, array<Var> args) { new(&val<mud::Arc>(ref)) mud::Arc( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]) ); }, { { "radius", var(float()) }, { "start", var(float()) }, { "end", var(float()) } } }
            },
            // copy constructor
            {
                { type<mud::Arc>(), [](Ref ref, Ref other) { new(&val<mud::Arc>(ref)) mud::Arc(val<mud::Arc>(other)); } }
            },
            // members
            {
                { type<mud::Arc>(), member_address(&mud::Arc::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr },
                { type<mud::Arc>(), member_address(&mud::Arc::m_start), type<float>(), "start", var(float(0.f)), Member::Value, nullptr },
                { type<mud::Arc>(), member_address(&mud::Arc::m_end), type<float>(), "end", var(float(1.f)), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Arc>();
    }
    // mud::ArcLine
    {
        static Meta meta = { type<mud::ArcLine>(), &namspc({ "mud" }), "ArcLine", sizeof(mud::ArcLine), TypeClass::Struct };
        static Class cls = { type<mud::ArcLine>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::ArcLine, mud::Shape>() },
            // constructors
            {
                { type<mud::ArcLine>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ArcLine>(ref)) mud::ArcLine(  ); }, {} },
                { type<mud::ArcLine>(), [](Ref ref, array<Var> args) { new(&val<mud::ArcLine>(ref)) mud::ArcLine( val<mud::vec3>(args[0]), val<mud::vec3>(args[1]), val<mud::vec3>(args[2]) ); }, { { "start", var(mud::vec3()) }, { "middle", var(mud::vec3()) }, { "end", var(mud::vec3()) } } },
                { type<mud::ArcLine>(), [](Ref ref, array<Var> args) { new(&val<mud::ArcLine>(ref)) mud::ArcLine( val<mud::vec3>(args[0]), val<mud::vec3>(args[1]), val<mud::vec3>(args[2]), val<mud::vec3>(args[3]) ); }, { { "center", var(mud::vec3()) }, { "start", var(mud::vec3()) }, { "middle", var(mud::vec3()) }, { "end", var(mud::vec3()) } } }
            },
            // copy constructor
            {
                { type<mud::ArcLine>(), [](Ref ref, Ref other) { new(&val<mud::ArcLine>(ref)) mud::ArcLine(val<mud::ArcLine>(other)); } }
            },
            // members
            {
                { type<mud::ArcLine>(), member_address(&mud::ArcLine::m_start), type<mud::vec3>(), "start", var(mud::vec3(Zero3)), Member::Value, nullptr },
                { type<mud::ArcLine>(), member_address(&mud::ArcLine::m_middle), type<mud::vec3>(), "middle", var(mud::vec3()), Member::Value, nullptr },
                { type<mud::ArcLine>(), member_address(&mud::ArcLine::m_end), type<mud::vec3>(), "end", var(mud::vec3()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::ArcLine>();
    }
    // mud::Capsule
    {
        static Meta meta = { type<mud::Capsule>(), &namspc({ "mud" }), "Capsule", sizeof(mud::Capsule), TypeClass::Struct };
        static Class cls = { type<mud::Capsule>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Capsule, mud::Shape>() },
            // constructors
            {
                { type<mud::Capsule>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Capsule>(ref)) mud::Capsule(  ); }, {} },
                { type<mud::Capsule>(), [](Ref ref, array<Var> args) { new(&val<mud::Capsule>(ref)) mud::Capsule( val<float>(args[0]), val<float>(args[1]), val<mud::Axis>(args[2]) ); }, { { "radius", var(float()) }, { "height", var(float()) }, { "axis", var(mud::Axis::X), Param::Default } } }
            },
            // copy constructor
            {
                { type<mud::Capsule>(), [](Ref ref, Ref other) { new(&val<mud::Capsule>(ref)) mud::Capsule(val<mud::Capsule>(other)); } }
            },
            // members
            {
                { type<mud::Capsule>(), member_address(&mud::Capsule::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr },
                { type<mud::Capsule>(), member_address(&mud::Capsule::m_height), type<float>(), "height", var(float(2.f)), Member::Value, nullptr },
                { type<mud::Capsule>(), member_address(&mud::Capsule::m_axis), type<mud::Axis>(), "axis", var(mud::Axis::X), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Capsule>();
    }
    // mud::Cube
    {
        static Meta meta = { type<mud::Cube>(), &namspc({ "mud" }), "Cube", sizeof(mud::Cube), TypeClass::Struct };
        static Class cls = { type<mud::Cube>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Cube, mud::Shape>() },
            // constructors
            {
                { type<mud::Cube>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Cube>(ref)) mud::Cube(  ); }, {} },
                { type<mud::Cube>(), [](Ref ref, array<Var> args) { new(&val<mud::Cube>(ref)) mud::Cube( val<mud::vec3>(args[0]) ); }, { { "extents", var(mud::vec3()) } } },
                { type<mud::Cube>(), [](Ref ref, array<Var> args) { new(&val<mud::Cube>(ref)) mud::Cube( val<mud::vec3>(args[0]), val<mud::vec3>(args[1]) ); }, { { "center", var(mud::vec3()) }, { "extents", var(mud::vec3()) } } }
            },
            // copy constructor
            {
                { type<mud::Cube>(), [](Ref ref, Ref other) { new(&val<mud::Cube>(ref)) mud::Cube(val<mud::Cube>(other)); } }
            },
            // members
            {
                { type<mud::Cube>(), member_address(&mud::Cube::m_extents), type<mud::vec3>(), "extents", var(mud::vec3{0.5f}), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Cube>();
    }
    // mud::Aabb
    {
        static Meta meta = { type<mud::Aabb>(), &namspc({ "mud" }), "Aabb", sizeof(mud::Aabb), TypeClass::Struct };
        static Class cls = { type<mud::Aabb>(),
            // bases
            { &type<mud::Cube>() },
            { base_offset<mud::Aabb, mud::Cube>() },
            // constructors
            {
                { type<mud::Aabb>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Aabb>(ref)) mud::Aabb(  ); }, {} },
                { type<mud::Aabb>(), [](Ref ref, array<Var> args) { new(&val<mud::Aabb>(ref)) mud::Aabb( val<mud::vec3>(args[0]), val<mud::vec3>(args[1]) ); }, { { "center", var(mud::vec3()) }, { "extents", var(mud::vec3()) } } }
            },
            // copy constructor
            {
                { type<mud::Aabb>(), [](Ref ref, Ref other) { new(&val<mud::Aabb>(ref)) mud::Aabb(val<mud::Aabb>(other)); } }
            },
            // members
            {
                { type<mud::Aabb>(), member_address(&mud::Aabb::m_empty), type<bool>(), "empty", var(bool()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Aabb>();
    }
    // mud::Box
    {
        static Meta meta = { type<mud::Box>(), &namspc({ "mud" }), "Box", sizeof(mud::Box), TypeClass::Struct };
        static Class cls = { type<mud::Box>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Box, mud::Shape>() },
            // constructors
            {
                { type<mud::Box>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Box>(ref)) mud::Box(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Box>(), [](Ref ref, Ref other) { new(&val<mud::Box>(ref)) mud::Box(val<mud::Box>(other)); } }
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Box>();
    }
    // mud::Circle
    {
        static Meta meta = { type<mud::Circle>(), &namspc({ "mud" }), "Circle", sizeof(mud::Circle), TypeClass::Struct };
        static Class cls = { type<mud::Circle>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Circle, mud::Shape>() },
            // constructors
            {
                { type<mud::Circle>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Circle>(ref)) mud::Circle(  ); }, {} },
                { type<mud::Circle>(), [](Ref ref, array<Var> args) { new(&val<mud::Circle>(ref)) mud::Circle( val<float>(args[0]), val<mud::Axis>(args[1]) ); }, { { "radius", var(float()) }, { "axis", var(mud::Axis::Y), Param::Default } } },
                { type<mud::Circle>(), [](Ref ref, array<Var> args) { new(&val<mud::Circle>(ref)) mud::Circle( val<mud::vec3>(args[0]), val<float>(args[1]), val<mud::Axis>(args[2]) ); }, { { "center", var(mud::vec3()) }, { "radius", var(float()) }, { "axis", var(mud::Axis::Y), Param::Default } } }
            },
            // copy constructor
            {
                { type<mud::Circle>(), [](Ref ref, Ref other) { new(&val<mud::Circle>(ref)) mud::Circle(val<mud::Circle>(other)); } }
            },
            // members
            {
                { type<mud::Circle>(), member_address(&mud::Circle::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr },
                { type<mud::Circle>(), member_address(&mud::Circle::m_axis), type<mud::Axis>(), "axis", var(mud::Axis::X), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Circle>();
    }
    // mud::ConvexHull
    {
        static Meta meta = { type<mud::ConvexHull>(), &namspc({ "mud" }), "ConvexHull", sizeof(mud::ConvexHull), TypeClass::Struct };
        static Class cls = { type<mud::ConvexHull>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::ConvexHull, mud::Shape>() },
            // constructors
            {
                { type<mud::ConvexHull>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ConvexHull>(ref)) mud::ConvexHull(  ); }, {} },
                { type<mud::ConvexHull>(), [](Ref ref, array<Var> args) { new(&val<mud::ConvexHull>(ref)) mud::ConvexHull( val<vector<mud::vec3>>(args[0]) ); }, { { "vertices", var(vector<mud::vec3>()) } } }
            },
            // copy constructor
            {
                { type<mud::ConvexHull>(), [](Ref ref, Ref other) { new(&val<mud::ConvexHull>(ref)) mud::ConvexHull(val<mud::ConvexHull>(other)); } }
            },
            // members
            {
                { type<mud::ConvexHull>(), member_address(&mud::ConvexHull::m_vertices), type<vector<mud::vec3>>(), "vertices", var(vector<mud::vec3>()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::ConvexHull>();
    }
    // mud::Cylinder
    {
        static Meta meta = { type<mud::Cylinder>(), &namspc({ "mud" }), "Cylinder", sizeof(mud::Cylinder), TypeClass::Struct };
        static Class cls = { type<mud::Cylinder>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Cylinder, mud::Shape>() },
            // constructors
            {
                { type<mud::Cylinder>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Cylinder>(ref)) mud::Cylinder(  ); }, {} },
                { type<mud::Cylinder>(), [](Ref ref, array<Var> args) { new(&val<mud::Cylinder>(ref)) mud::Cylinder( val<float>(args[0]), val<float>(args[1]), val<mud::Axis>(args[2]) ); }, { { "radius", var(float()) }, { "height", var(float()) }, { "axis", var(mud::Axis::X), Param::Default } } }
            },
            // copy constructor
            {
                { type<mud::Cylinder>(), [](Ref ref, Ref other) { new(&val<mud::Cylinder>(ref)) mud::Cylinder(val<mud::Cylinder>(other)); } }
            },
            // members
            {
                { type<mud::Cylinder>(), member_address(&mud::Cylinder::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr },
                { type<mud::Cylinder>(), member_address(&mud::Cylinder::m_height), type<float>(), "height", var(float(2.f)), Member::Value, nullptr },
                { type<mud::Cylinder>(), member_address(&mud::Cylinder::m_axis), type<mud::Axis>(), "axis", var(mud::Axis::X), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Cylinder>();
    }
    // mud::Ellipsis
    {
        static Meta meta = { type<mud::Ellipsis>(), &namspc({ "mud" }), "Ellipsis", sizeof(mud::Ellipsis), TypeClass::Struct };
        static Class cls = { type<mud::Ellipsis>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Ellipsis, mud::Shape>() },
            // constructors
            {
                { type<mud::Ellipsis>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Ellipsis>(ref)) mud::Ellipsis(  ); }, {} },
                { type<mud::Ellipsis>(), [](Ref ref, array<Var> args) { new(&val<mud::Ellipsis>(ref)) mud::Ellipsis( val<mud::vec2>(args[0]), val<mud::Axis>(args[1]) ); }, { { "radius", var(mud::vec2()) }, { "axis", var(mud::Axis::Y), Param::Default } } }
            },
            // copy constructor
            {
                { type<mud::Ellipsis>(), [](Ref ref, Ref other) { new(&val<mud::Ellipsis>(ref)) mud::Ellipsis(val<mud::Ellipsis>(other)); } }
            },
            // members
            {
                { type<mud::Ellipsis>(), member_address(&mud::Ellipsis::m_radius), type<mud::vec2>(), "radius", var(mud::vec2(Unit2)), Member::Value, nullptr },
                { type<mud::Ellipsis>(), member_address(&mud::Ellipsis::m_axis), type<mud::Axis>(), "axis", var(mud::Axis::Y), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Ellipsis>();
    }
    // mud::Geometry
    {
        static Meta meta = { type<mud::Geometry>(), &namspc({ "mud" }), "Geometry", sizeof(mud::Geometry), TypeClass::Object };
        static Class cls = { type<mud::Geometry>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Geometry, mud::Shape>() },
            // constructors
            {
                { type<mud::Geometry>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Geometry>(ref)) mud::Geometry(  ); }, {} }
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        init_pool<mud::Geometry>();
        meta_class<mud::Geometry>();
    }
    // mud::Grid2
    {
        static Meta meta = { type<mud::Grid2>(), &namspc({ "mud" }), "Grid2", sizeof(mud::Grid2), TypeClass::Struct };
        static Class cls = { type<mud::Grid2>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Grid2, mud::Shape>() },
            // constructors
            {
                { type<mud::Grid2>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Grid2>(ref)) mud::Grid2(  ); }, {} },
                { type<mud::Grid2>(), [](Ref ref, array<Var> args) { new(&val<mud::Grid2>(ref)) mud::Grid2( val<mud::vec2>(args[0]), val<mud::vec2>(args[1]) ); }, { { "size", var(mud::vec2()) }, { "space", var(mud::vec2(Unit2)), Param::Default } } }
            },
            // copy constructor
            {
                { type<mud::Grid2>(), [](Ref ref, Ref other) { new(&val<mud::Grid2>(ref)) mud::Grid2(val<mud::Grid2>(other)); } }
            },
            // members
            {
                { type<mud::Grid2>(), member_address(&mud::Grid2::m_size), type<mud::vec2>(), "size", var(mud::vec2{1.f}), Member::Value, nullptr },
                { type<mud::Grid2>(), member_address(&mud::Grid2::m_space), type<mud::vec2>(), "space", var(mud::vec2{0.1f}), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Grid2>();
    }
    // mud::Grid3
    {
        static Meta meta = { type<mud::Grid3>(), &namspc({ "mud" }), "Grid3", sizeof(mud::Grid3), TypeClass::Struct };
        static Class cls = { type<mud::Grid3>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Grid3, mud::Shape>() },
            // constructors
            {
                { type<mud::Grid3>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Grid3>(ref)) mud::Grid3(  ); }, {} },
                { type<mud::Grid3>(), [](Ref ref, array<Var> args) { new(&val<mud::Grid3>(ref)) mud::Grid3( val<mud::uvec2>(args[0]), val<vector<mud::vec3>>(args[1]) ); }, { { "size", var(mud::uvec2()) }, { "points", var(vector<mud::vec3>{}), Param::Default } } }
            },
            // copy constructor
            {
                { type<mud::Grid3>(), [](Ref ref, Ref other) { new(&val<mud::Grid3>(ref)) mud::Grid3(val<mud::Grid3>(other)); } }
            },
            // members
            {
                { type<mud::Grid3>(), member_address(&mud::Grid3::m_size), type<mud::uvec2>(), "size", var(mud::uvec2()), Member::Value, nullptr },
                { type<mud::Grid3>(), member_address(&mud::Grid3::m_points), type<vector<mud::vec3>>(), "points", var(vector<mud::vec3>()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Grid3>();
    }
    // mud::Line
    {
        static Meta meta = { type<mud::Line>(), &namspc({ "mud" }), "Line", sizeof(mud::Line), TypeClass::Struct };
        static Class cls = { type<mud::Line>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Line, mud::Shape>() },
            // constructors
            {
                { type<mud::Line>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Line>(ref)) mud::Line(  ); }, {} },
                { type<mud::Line>(), [](Ref ref, array<Var> args) { new(&val<mud::Line>(ref)) mud::Line( val<mud::vec3>(args[0]), val<mud::vec3>(args[1]) ); }, { { "start", var(mud::vec3()) }, { "end", var(mud::vec3()) } } }
            },
            // copy constructor
            {
                { type<mud::Line>(), [](Ref ref, Ref other) { new(&val<mud::Line>(ref)) mud::Line(val<mud::Line>(other)); } }
            },
            // members
            {
                { type<mud::Line>(), member_address(&mud::Line::m_start), type<mud::vec3>(), "start", var(mud::vec3(Zero3)), Member::Value, nullptr },
                { type<mud::Line>(), member_address(&mud::Line::m_end), type<mud::vec3>(), "end", var(mud::vec3(Unit3)), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Line>();
    }
    // mud::Points
    {
        static Meta meta = { type<mud::Points>(), &namspc({ "mud" }), "Points", sizeof(mud::Points), TypeClass::Struct };
        static Class cls = { type<mud::Points>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Points, mud::Shape>() },
            // constructors
            {
                { type<mud::Points>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Points>(ref)) mud::Points(  ); }, {} },
                { type<mud::Points>(), [](Ref ref, array<Var> args) { new(&val<mud::Points>(ref)) mud::Points( val<vector<mud::vec3>>(args[0]) ); }, { { "points", var(vector<mud::vec3>()) } } }
            },
            // copy constructor
            {
                { type<mud::Points>(), [](Ref ref, Ref other) { new(&val<mud::Points>(ref)) mud::Points(val<mud::Points>(other)); } }
            },
            // members
            {
                { type<mud::Points>(), member_address(&mud::Points::m_points), type<vector<mud::vec3>>(), "points", var(vector<mud::vec3>()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Points>();
    }
    // mud::Poisson
    {
        static Meta meta = { type<mud::Poisson>(), &namspc({ "mud" }), "Poisson", sizeof(mud::Poisson), TypeClass::Object };
        static Class cls = { type<mud::Poisson>(),
            // bases
            { &type<mud::Distribution>() },
            { base_offset<mud::Poisson, mud::Distribution>() },
            // constructors
            {
                { type<mud::Poisson>(), [](Ref ref, array<Var> args) { new(&val<mud::Poisson>(ref)) mud::Poisson( val<mud::vec2>(args[0]), val<float>(args[1]) ); }, { { "size", var(mud::vec2()) }, { "maxRadius", var(float()) } } }
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
                { type<mud::Poisson>(), "distribute", member_address<vector<mud::vec3>(mud::Poisson::*)(float)>(&mud::Poisson::distribute), [](Ref object, array<Var> args, Var& result) { val<vector<mud::vec3>>(result) = val<mud::Poisson>(object).distribute(val<float>(args[0])); }, { { "radius", var(float()) } }, var(vector<mud::vec3>()) },
                { type<mud::Poisson>(), "distribute_circles", member_address<vector<mud::Circle>(mud::Poisson::*)(float)>(&mud::Poisson::distribute_circles), [](Ref object, array<Var> args, Var& result) { val<vector<mud::Circle>>(result) = val<mud::Poisson>(object).distribute_circles(val<float>(args[0])); }, { { "radius", var(float()) } }, var(vector<mud::Circle>()) },
                { type<mud::Poisson>(), "addPoint", member_address<bool(mud::Poisson::*)(float, mud::vec3&)>(&mud::Poisson::addPoint), [](Ref object, array<Var> args, Var& result) { val<bool>(result) = val<mud::Poisson>(object).addPoint(val<float>(args[0]), val<mud::vec3>(args[1])); }, { { "radius", var(float()) }, { "point", var(mud::vec3()) } }, var(bool()) }
            },
            // static members
            {
            }
        };
        init_pool<mud::Poisson>();
        meta_class<mud::Poisson>();
    }
    // mud::Polygon
    {
        static Meta meta = { type<mud::Polygon>(), &namspc({ "mud" }), "Polygon", sizeof(mud::Polygon), TypeClass::Struct };
        static Class cls = { type<mud::Polygon>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Polygon, mud::Shape>() },
            // constructors
            {
                { type<mud::Polygon>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Polygon>(ref)) mud::Polygon(  ); }, {} },
                { type<mud::Polygon>(), [](Ref ref, array<Var> args) { new(&val<mud::Polygon>(ref)) mud::Polygon( val<vector<mud::vec3>>(args[0]) ); }, { { "vertices", var(vector<mud::vec3>()) } } }
            },
            // copy constructor
            {
                { type<mud::Polygon>(), [](Ref ref, Ref other) { new(&val<mud::Polygon>(ref)) mud::Polygon(val<mud::Polygon>(other)); } }
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Polygon>();
    }
    // mud::Quad
    {
        static Meta meta = { type<mud::Quad>(), &namspc({ "mud" }), "Quad", sizeof(mud::Quad), TypeClass::Struct };
        static Class cls = { type<mud::Quad>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Quad, mud::Shape>() },
            // constructors
            {
                { type<mud::Quad>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Quad>(ref)) mud::Quad(  ); }, {} },
                { type<mud::Quad>(), [](Ref ref, array<Var> args) { new(&val<mud::Quad>(ref)) mud::Quad( val<mud::vec3>(args[0]), val<mud::vec3>(args[1]), val<mud::vec3>(args[2]), val<mud::vec3>(args[3]) ); }, { { "a", var(mud::vec3()) }, { "b", var(mud::vec3()) }, { "c", var(mud::vec3()) }, { "d", var(mud::vec3()) } } }
            },
            // copy constructor
            {
                { type<mud::Quad>(), [](Ref ref, Ref other) { new(&val<mud::Quad>(ref)) mud::Quad(val<mud::Quad>(other)); } }
            },
            // members
            {
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Quad>();
    }
    // mud::Rect
    {
        static Meta meta = { type<mud::Rect>(), &namspc({ "mud" }), "Rect", sizeof(mud::Rect), TypeClass::Struct };
        static Class cls = { type<mud::Rect>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Rect, mud::Shape>() },
            // constructors
            {
                { type<mud::Rect>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Rect>(ref)) mud::Rect(  ); }, {} },
                { type<mud::Rect>(), [](Ref ref, array<Var> args) { new(&val<mud::Rect>(ref)) mud::Rect( val<mud::vec2>(args[0]), val<mud::vec2>(args[1]) ); }, { { "position", var(mud::vec2()) }, { "size", var(mud::vec2()) } } },
                { type<mud::Rect>(), [](Ref ref, array<Var> args) { new(&val<mud::Rect>(ref)) mud::Rect( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]), val<float>(args[3]) ); }, { { "x", var(float()) }, { "y", var(float()) }, { "w", var(float()) }, { "h", var(float()) } } }
            },
            // copy constructor
            {
                { type<mud::Rect>(), [](Ref ref, Ref other) { new(&val<mud::Rect>(ref)) mud::Rect(val<mud::Rect>(other)); } }
            },
            // members
            {
                { type<mud::Rect>(), member_address(&mud::Rect::m_position), type<mud::vec2>(), "position", var(mud::vec2(Zero2)), Member::Value, nullptr },
                { type<mud::Rect>(), member_address(&mud::Rect::m_size), type<mud::vec2>(), "size", var(mud::vec2(Unit2)), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Rect>();
    }
    // mud::Ring
    {
        static Meta meta = { type<mud::Ring>(), &namspc({ "mud" }), "Ring", sizeof(mud::Ring), TypeClass::Struct };
        static Class cls = { type<mud::Ring>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Ring, mud::Shape>() },
            // constructors
            {
                { type<mud::Ring>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Ring>(ref)) mud::Ring(  ); }, {} },
                { type<mud::Ring>(), [](Ref ref, array<Var> args) { new(&val<mud::Ring>(ref)) mud::Ring( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]) ); }, { { "radius", var(float()) }, { "min", var(float()) }, { "max", var(float()) } } }
            },
            // copy constructor
            {
                { type<mud::Ring>(), [](Ref ref, Ref other) { new(&val<mud::Ring>(ref)) mud::Ring(val<mud::Ring>(other)); } }
            },
            // members
            {
                { type<mud::Ring>(), member_address(&mud::Ring::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr },
                { type<mud::Ring>(), member_address(&mud::Ring::m_min), type<float>(), "min", var(float(0.f)), Member::Value, nullptr },
                { type<mud::Ring>(), member_address(&mud::Ring::m_max), type<float>(), "max", var(float(1.f)), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Ring>();
    }
    // mud::Sphere
    {
        static Meta meta = { type<mud::Sphere>(), &namspc({ "mud" }), "Sphere", sizeof(mud::Sphere), TypeClass::Struct };
        static Class cls = { type<mud::Sphere>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Sphere, mud::Shape>() },
            // constructors
            {
                { type<mud::Sphere>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Sphere>(ref)) mud::Sphere(  ); }, {} },
                { type<mud::Sphere>(), [](Ref ref, array<Var> args) { new(&val<mud::Sphere>(ref)) mud::Sphere( val<float>(args[0]) ); }, { { "radius", var(float()) } } },
                { type<mud::Sphere>(), [](Ref ref, array<Var> args) { new(&val<mud::Sphere>(ref)) mud::Sphere( val<mud::vec3>(args[0]), val<float>(args[1]) ); }, { { "center", var(mud::vec3()) }, { "radius", var(float()) } } }
            },
            // copy constructor
            {
                { type<mud::Sphere>(), [](Ref ref, Ref other) { new(&val<mud::Sphere>(ref)) mud::Sphere(val<mud::Sphere>(other)); } }
            },
            // members
            {
                { type<mud::Sphere>(), member_address(&mud::Sphere::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Sphere>();
    }
    // mud::SphereRing
    {
        static Meta meta = { type<mud::SphereRing>(), &namspc({ "mud" }), "SphereRing", sizeof(mud::SphereRing), TypeClass::Struct };
        static Class cls = { type<mud::SphereRing>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::SphereRing, mud::Shape>() },
            // constructors
            {
                { type<mud::SphereRing>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::SphereRing>(ref)) mud::SphereRing(  ); }, {} },
                { type<mud::SphereRing>(), [](Ref ref, array<Var> args) { new(&val<mud::SphereRing>(ref)) mud::SphereRing( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]) ); }, { { "radius", var(float()) }, { "min", var(float()) }, { "max", var(float()) } } }
            },
            // copy constructor
            {
                { type<mud::SphereRing>(), [](Ref ref, Ref other) { new(&val<mud::SphereRing>(ref)) mud::SphereRing(val<mud::SphereRing>(other)); } }
            },
            // members
            {
                { type<mud::SphereRing>(), member_address(&mud::SphereRing::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr },
                { type<mud::SphereRing>(), member_address(&mud::SphereRing::m_min), type<float>(), "min", var(float()), Member::Value, nullptr },
                { type<mud::SphereRing>(), member_address(&mud::SphereRing::m_max), type<float>(), "max", var(float(1.f)), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::SphereRing>();
    }
    // mud::Spheroid
    {
        static Meta meta = { type<mud::Spheroid>(), &namspc({ "mud" }), "Spheroid", sizeof(mud::Spheroid), TypeClass::Struct };
        static Class cls = { type<mud::Spheroid>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Spheroid, mud::Shape>() },
            // constructors
            {
                { type<mud::Spheroid>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Spheroid>(ref)) mud::Spheroid(  ); }, {} },
                { type<mud::Spheroid>(), [](Ref ref, array<Var> args) { new(&val<mud::Spheroid>(ref)) mud::Spheroid( val<float>(args[0]) ); }, { { "radius", var(float()) } } },
                { type<mud::Spheroid>(), [](Ref ref, array<Var> args) { new(&val<mud::Spheroid>(ref)) mud::Spheroid( val<mud::vec3>(args[0]), val<float>(args[1]) ); }, { { "center", var(mud::vec3()) }, { "radius", var(float()) } } }
            },
            // copy constructor
            {
                { type<mud::Spheroid>(), [](Ref ref, Ref other) { new(&val<mud::Spheroid>(ref)) mud::Spheroid(val<mud::Spheroid>(other)); } }
            },
            // members
            {
                { type<mud::Spheroid>(), member_address(&mud::Spheroid::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Spheroid>();
    }
    // mud::Torus
    {
        static Meta meta = { type<mud::Torus>(), &namspc({ "mud" }), "Torus", sizeof(mud::Torus), TypeClass::Struct };
        static Class cls = { type<mud::Torus>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Torus, mud::Shape>() },
            // constructors
            {
                { type<mud::Torus>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Torus>(ref)) mud::Torus(  ); }, {} },
                { type<mud::Torus>(), [](Ref ref, array<Var> args) { new(&val<mud::Torus>(ref)) mud::Torus( val<float>(args[0]), val<float>(args[1]), val<mud::Axis>(args[2]) ); }, { { "radius", var(float()) }, { "solid_radius", var(float()) }, { "axis", var(mud::Axis::Y), Param::Default } } },
                { type<mud::Torus>(), [](Ref ref, array<Var> args) { new(&val<mud::Torus>(ref)) mud::Torus( val<mud::vec3>(args[0]), val<float>(args[1]), val<float>(args[2]), val<mud::Axis>(args[3]) ); }, { { "center", var(mud::vec3()) }, { "radius", var(float()) }, { "solid_radius", var(float()) }, { "axis", var(mud::Axis::Y), Param::Default } } }
            },
            // copy constructor
            {
                { type<mud::Torus>(), [](Ref ref, Ref other) { new(&val<mud::Torus>(ref)) mud::Torus(val<mud::Torus>(other)); } }
            },
            // members
            {
                { type<mud::Torus>(), member_address(&mud::Torus::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr },
                { type<mud::Torus>(), member_address(&mud::Torus::m_solid_radius), type<float>(), "solid_radius", var(float(1.f)), Member::Value, nullptr },
                { type<mud::Torus>(), member_address(&mud::Torus::m_axis), type<mud::Axis>(), "axis", var(mud::Axis::X), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Torus>();
    }
    // mud::Triangle
    {
        static Meta meta = { type<mud::Triangle>(), &namspc({ "mud" }), "Triangle", sizeof(mud::Triangle), TypeClass::Struct };
        static Class cls = { type<mud::Triangle>(),
            // bases
            { &type<mud::Shape>() },
            { base_offset<mud::Triangle, mud::Shape>() },
            // constructors
            {
                { type<mud::Triangle>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Triangle>(ref)) mud::Triangle(  ); }, {} },
                { type<mud::Triangle>(), [](Ref ref, array<Var> args) { new(&val<mud::Triangle>(ref)) mud::Triangle( val<mud::vec2>(args[0]) ); }, { { "size", var(mud::vec2()) } } }
            },
            // copy constructor
            {
                { type<mud::Triangle>(), [](Ref ref, Ref other) { new(&val<mud::Triangle>(ref)) mud::Triangle(val<mud::Triangle>(other)); } }
            },
            // members
            {
                { type<mud::Triangle>(), member_address(&mud::Triangle::m_size), type<mud::vec2>(), "size", var(mud::vec2(Unit2)), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<mud::Triangle>();
    }
        m.m_types.push_back(&type<mud::Distribution>());
        m.m_types.push_back(&type<mud::DrawMode>());
        m.m_types.push_back(&type<mud::Face3>());
        m.m_types.push_back(&type<mud::MeshPacker>());
        m.m_types.push_back(&type<mud::Plane>());
        m.m_types.push_back(&type<mud::Plane3>());
        m.m_types.push_back(&type<mud::PrimitiveType>());
        m.m_types.push_back(&type<mud::Ray>());
        m.m_types.push_back(&type<mud::Segment>());
        m.m_types.push_back(&type<mud::Shape>());
        m.m_types.push_back(&type<mud::ShapeVar>());
        m.m_types.push_back(&type<mud::Symbol>());
        m.m_types.push_back(&type<mud::SymbolDetail>());
        m.m_types.push_back(&type<vector<mud::Circle>>());
        m.m_types.push_back(&type<mud::Aabb>());
        m.m_types.push_back(&type<mud::Arc>());
        m.m_types.push_back(&type<mud::ArcLine>());
        m.m_types.push_back(&type<mud::Box>());
        m.m_types.push_back(&type<mud::Capsule>());
        m.m_types.push_back(&type<mud::Circle>());
        m.m_types.push_back(&type<mud::ConvexHull>());
        m.m_types.push_back(&type<mud::Cube>());
        m.m_types.push_back(&type<mud::Cylinder>());
        m.m_types.push_back(&type<mud::Ellipsis>());
        m.m_types.push_back(&type<mud::Geometry>());
        m.m_types.push_back(&type<mud::Grid2>());
        m.m_types.push_back(&type<mud::Grid3>());
        m.m_types.push_back(&type<mud::Line>());
        m.m_types.push_back(&type<mud::Points>());
        m.m_types.push_back(&type<mud::Poisson>());
        m.m_types.push_back(&type<mud::Polygon>());
        m.m_types.push_back(&type<mud::Quad>());
        m.m_types.push_back(&type<mud::Rect>());
        m.m_types.push_back(&type<mud::Ring>());
        m.m_types.push_back(&type<mud::Sphere>());
        m.m_types.push_back(&type<mud::SphereRing>());
        m.m_types.push_back(&type<mud::Spheroid>());
        m.m_types.push_back(&type<mud::Torus>());
        m.m_types.push_back(&type<mud::Triangle>());
        {
            auto func = [](array<Var> args, Var& result) {  val<mud::Ray>(result) = mud::to_ray(val<mud::vec3>(args[0]), val<mud::vec3>(args[1]), val<float>(args[2])); };
            vector<Param> params = { { "pos", var(mud::vec3()) }, { "dir", var(mud::vec3()) }, { "distance", var(float(1000.f)), Param::Default } };
            static Function f = { &namspc({ "mud" }), "to_ray", funcptr<mud::Ray(*)(const mud::vec3&, const mud::vec3&, float)>(&mud::to_ray), func, params, var(mud::Ray()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<mud::Segment>(result) = mud::to_segment(val<mud::Ray>(args[0])); };
            vector<Param> params = { { "ray", var(mud::Ray()) } };
            static Function f = { &namspc({ "mud" }), "to_segment", funcptr<mud::Segment(*)(const mud::Ray&)>(&mud::to_segment), func, params, var(mud::Segment()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<vector<mud::vec3>>(result) = mud::distribute_poisson(val<mud::vec2>(args[0]), val<float>(args[1])); };
            vector<Param> params = { { "size", var(mud::vec2()) }, { "radius", var(float()) } };
            static Function f = { &namspc({ "mud" }), "distribute_poisson", funcptr<vector<mud::vec3>(*)(mud::vec2, float)>(&mud::distribute_poisson), func, params, var(vector<mud::vec3>()) };
            m.m_functions.push_back(&f);
        }
    }
}
