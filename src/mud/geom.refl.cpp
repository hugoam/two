#include <mud/geom.h>
#include <mud/geom.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.geom;
#else
#endif


namespace mud
{
	void mud_geom_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::DrawMode>();
		static Meta meta = { t, &namspc({ "mud" }), "DrawMode", sizeof(mud::DrawMode), TypeClass::Enum };
		static cstring ids[] = { "OUTLINE", "PLAIN" };
		static uint32_t values[] = { 0, 1 };
		static mud::DrawMode vars[] = { mud::OUTLINE, mud::PLAIN};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::DrawMode>();
	}
	{
		Type& t = type<mud::PrimitiveType>();
		static Meta meta = { t, &namspc({ "mud" }), "PrimitiveType", sizeof(mud::PrimitiveType), TypeClass::Enum };
		static cstring ids[] = { "Points", "Lines", "LineLoop", "LineStrip", "Triangles", "TriangleStrip", "TriangleFan" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6 };
		static mud::PrimitiveType vars[] = { mud::PrimitiveType::Points, mud::PrimitiveType::Lines, mud::PrimitiveType::LineLoop, mud::PrimitiveType::LineStrip, mud::PrimitiveType::Triangles, mud::PrimitiveType::TriangleStrip, mud::PrimitiveType::TriangleFan};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::PrimitiveType>();
	}
	{
		Type& t = type<mud::SymbolDetail>();
		static Meta meta = { t, &namspc({ "mud" }), "SymbolDetail", sizeof(mud::SymbolDetail), TypeClass::Enum };
		static cstring ids[] = { "Lowest", "Low", "Medium", "High", "Highest" };
		static uint32_t values[] = { 0, 1, 2, 3, 4 };
		static mud::SymbolDetail vars[] = { mud::SymbolDetail::Lowest, mud::SymbolDetail::Low, mud::SymbolDetail::Medium, mud::SymbolDetail::High, mud::SymbolDetail::Highest};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::SymbolDetail>();
	}
	
	// Sequences
	{
		Type& t = type<vector<mud::Circle>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Circle>", sizeof(vector<mud::Circle>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::Circle>();
		meta_vector<vector<mud::Circle>, mud::Circle>();
	}
	
	// mud::Distribution
	{
		Type& t = type<mud::Distribution>();
		static Meta meta = { t, &namspc({ "mud" }), "Distribution", sizeof(mud::Distribution), TypeClass::Object };
		static Class cls = { t,
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
		Type& t = type<mud::Face3>();
		static Meta meta = { t, &namspc({ "mud" }), "Face3", sizeof(mud::Face3), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Face3>(ref)) mud::Face3(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Face3>(ref)) mud::Face3(val<mud::Face3>(other)); } }
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
		Type& t = type<mud::MeshPacker>();
		static Meta meta = { t, &namspc({ "mud" }), "MeshPacker", sizeof(mud::MeshPacker), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::MeshPacker>(ref)) mud::MeshPacker(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::MeshPacker>(ref)) mud::MeshPacker(val<mud::MeshPacker>(other)); } }
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
		Type& t = type<mud::Plane>();
		static Meta meta = { t, &namspc({ "mud" }), "Plane", sizeof(mud::Plane), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Plane>(ref)) mud::Plane(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Plane>(ref)) mud::Plane(val<mud::Plane>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Plane::m_normal), type<mud::vec3>(), "normal", var(mud::vec3()), Member::Value, nullptr },
				{ t, member_address(&mud::Plane::m_distance), type<float>(), "distance", var(float()), Member::Value, nullptr }
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
		Type& t = type<mud::Plane3>();
		static Meta meta = { t, &namspc({ "mud" }), "Plane3", sizeof(mud::Plane3), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Plane3>(ref)) mud::Plane3(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Plane3>(ref)) mud::Plane3(val<mud::Plane3>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Plane3::m_origin), type<mud::vec3>(), "origin", var(mud::vec3()), Member::Value, nullptr },
				{ t, member_address(&mud::Plane3::m_a), type<mud::vec3>(), "a", var(mud::vec3()), Member::Value, nullptr },
				{ t, member_address(&mud::Plane3::m_b), type<mud::vec3>(), "b", var(mud::vec3()), Member::Value, nullptr }
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
		Type& t = type<mud::Ray>();
		static Meta meta = { t, &namspc({ "mud" }), "Ray", sizeof(mud::Ray), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Ray>(ref)) mud::Ray(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Ray>(ref)) mud::Ray(val<mud::Ray>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Ray::m_start), type<mud::vec3>(), "start", var(mud::vec3()), Member::Value, nullptr },
				{ t, member_address(&mud::Ray::m_end), type<mud::vec3>(), "end", var(mud::vec3()), Member::Value, nullptr },
				{ t, member_address(&mud::Ray::m_dir), type<mud::vec3>(), "dir", var(mud::vec3()), Member::Value, nullptr },
				{ t, member_address(&mud::Ray::m_inv_dir), type<mud::vec3>(), "inv_dir", var(mud::vec3()), Member::Value, nullptr }
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
		Type& t = type<mud::Segment>();
		static Meta meta = { t, &namspc({ "mud" }), "Segment", sizeof(mud::Segment), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Segment>(ref)) mud::Segment(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Segment>(ref)) mud::Segment(val<mud::Segment>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Segment::m_start), type<mud::vec3>(), "start", var(mud::vec3()), Member::Value, nullptr },
				{ t, member_address(&mud::Segment::m_end), type<mud::vec3>(), "end", var(mud::vec3()), Member::Value, nullptr }
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
		Type& t = type<mud::Shape>();
		static Meta meta = { t, &namspc({ "mud" }), "Shape", sizeof(mud::Shape), TypeClass::Object };
		static Class cls = { t,
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
				{ t, Address(), type<mud::Type>(), "type", Ref(type<mud::Type>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::Shape>(object).m_type); } }
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
		Type& t = type<mud::ShapeVar>();
		static Meta meta = { t, &namspc({ "mud" }), "ShapeVar", sizeof(mud::ShapeVar), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ShapeVar>(ref)) mud::ShapeVar(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ShapeVar>(ref)) mud::ShapeVar( val<mud::Shape>(args[0]) ); }, { { "shape", Ref(type<mud::Shape>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ShapeVar>(ref)) mud::ShapeVar(val<mud::ShapeVar>(other)); } }
			},
			// members
			{
				{ t, member_address<mud::Shape&(mud::ShapeVar::*)()>(&mud::ShapeVar::shape), type<mud::Shape>(), "shape", Ref(type<mud::Shape>()), Member::Flags(Member::NonMutable|Member::Link), [](Ref object) { return Ref(&val<mud::ShapeVar>(object).shape()); } }
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
		Type& t = type<mud::Symbol>();
		static Meta meta = { t, &namspc({ "mud" }), "Symbol", sizeof(mud::Symbol), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Symbol>(ref)) mud::Symbol( val<mud::Colour>(args[0]), val<mud::Colour>(args[1]), val<bool>(args[2]), val<bool>(args[3]), val<mud::SymbolDetail>(args[4]) ); }, { { "fill", var(mud::Colour::White), Param::Default }, { "outline", var(mud::Colour::None), Param::Default }, { "overlay", var(bool(false)), Param::Default }, { "double_sided", var(bool(false)), Param::Default }, { "detail", var(mud::SymbolDetail::Medium), Param::Default } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Symbol>(ref)) mud::Symbol(val<mud::Symbol>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Symbol::m_outline), type<mud::Colour>(), "outline", var(mud::Colour()), Member::Value, nullptr },
				{ t, member_address(&mud::Symbol::m_fill), type<mud::Colour>(), "fill", var(mud::Colour()), Member::Value, nullptr },
				{ t, member_address(&mud::Symbol::m_overlay), type<bool>(), "overlay", var(bool()), Member::Value, nullptr },
				{ t, member_address(&mud::Symbol::m_double_sided), type<bool>(), "double_sided", var(bool()), Member::Value, nullptr },
				{ t, member_address(&mud::Symbol::m_detail), type<mud::SymbolDetail>(), "detail", var(mud::SymbolDetail()), Member::Value, nullptr },
				{ t, member_address(&mud::Symbol::m_image), type<const char*>(), "image", Ref(type<const char*>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Symbol::m_image256), type<mud::Image256>(), "image256", Ref(type<mud::Image256>()), Member::Flags(Member::Pointer|Member::Link), nullptr },
				{ t, member_address(&mud::Symbol::m_program), type<const char*>(), "program", Ref(type<const char*>()), Member::Flags(Member::Pointer|Member::Link), nullptr }
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
		Type& t = type<mud::Arc>();
		static Meta meta = { t, &namspc({ "mud" }), "Arc", sizeof(mud::Arc), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Arc, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Arc>(ref)) mud::Arc(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Arc>(ref)) mud::Arc( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]) ); }, { { "radius", var(float()) }, { "start", var(float()) }, { "end", var(float()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Arc>(ref)) mud::Arc(val<mud::Arc>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Arc::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr },
				{ t, member_address(&mud::Arc::m_start), type<float>(), "start", var(float(0.f)), Member::Value, nullptr },
				{ t, member_address(&mud::Arc::m_end), type<float>(), "end", var(float(1.f)), Member::Value, nullptr }
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
		Type& t = type<mud::ArcLine>();
		static Meta meta = { t, &namspc({ "mud" }), "ArcLine", sizeof(mud::ArcLine), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::ArcLine, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ArcLine>(ref)) mud::ArcLine(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ArcLine>(ref)) mud::ArcLine( val<mud::vec3>(args[0]), val<mud::vec3>(args[1]), val<mud::vec3>(args[2]) ); }, { { "start", var(mud::vec3()) }, { "middle", var(mud::vec3()) }, { "end", var(mud::vec3()) } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ArcLine>(ref)) mud::ArcLine( val<mud::vec3>(args[0]), val<mud::vec3>(args[1]), val<mud::vec3>(args[2]), val<mud::vec3>(args[3]) ); }, { { "center", var(mud::vec3()) }, { "start", var(mud::vec3()) }, { "middle", var(mud::vec3()) }, { "end", var(mud::vec3()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ArcLine>(ref)) mud::ArcLine(val<mud::ArcLine>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ArcLine::m_start), type<mud::vec3>(), "start", var(mud::vec3(Zero3)), Member::Value, nullptr },
				{ t, member_address(&mud::ArcLine::m_middle), type<mud::vec3>(), "middle", var(mud::vec3()), Member::Value, nullptr },
				{ t, member_address(&mud::ArcLine::m_end), type<mud::vec3>(), "end", var(mud::vec3()), Member::Value, nullptr }
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
		Type& t = type<mud::Capsule>();
		static Meta meta = { t, &namspc({ "mud" }), "Capsule", sizeof(mud::Capsule), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Capsule, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Capsule>(ref)) mud::Capsule(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Capsule>(ref)) mud::Capsule( val<float>(args[0]), val<float>(args[1]), val<mud::Axis>(args[2]) ); }, { { "radius", var(float()) }, { "height", var(float()) }, { "axis", var(mud::Axis::X), Param::Default } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Capsule>(ref)) mud::Capsule(val<mud::Capsule>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Capsule::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr },
				{ t, member_address(&mud::Capsule::m_height), type<float>(), "height", var(float(2.f)), Member::Value, nullptr },
				{ t, member_address(&mud::Capsule::m_axis), type<mud::Axis>(), "axis", var(mud::Axis::X), Member::Value, nullptr }
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
		Type& t = type<mud::Cube>();
		static Meta meta = { t, &namspc({ "mud" }), "Cube", sizeof(mud::Cube), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Cube, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Cube>(ref)) mud::Cube(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Cube>(ref)) mud::Cube( val<mud::vec3>(args[0]) ); }, { { "extents", var(mud::vec3()) } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Cube>(ref)) mud::Cube( val<mud::vec3>(args[0]), val<mud::vec3>(args[1]) ); }, { { "center", var(mud::vec3()) }, { "extents", var(mud::vec3()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Cube>(ref)) mud::Cube(val<mud::Cube>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Cube::m_extents), type<mud::vec3>(), "extents", var(mud::vec3{0.5f}), Member::Value, nullptr }
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
		Type& t = type<mud::Aabb>();
		static Meta meta = { t, &namspc({ "mud" }), "Aabb", sizeof(mud::Aabb), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Cube>() },
			{ base_offset<mud::Aabb, mud::Cube>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Aabb>(ref)) mud::Aabb(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Aabb>(ref)) mud::Aabb( val<mud::vec3>(args[0]), val<mud::vec3>(args[1]) ); }, { { "center", var(mud::vec3()) }, { "extents", var(mud::vec3()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Aabb>(ref)) mud::Aabb(val<mud::Aabb>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Aabb::m_empty), type<bool>(), "empty", var(bool()), Member::Value, nullptr }
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
		Type& t = type<mud::Box>();
		static Meta meta = { t, &namspc({ "mud" }), "Box", sizeof(mud::Box), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Box, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Box>(ref)) mud::Box(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Box>(ref)) mud::Box(val<mud::Box>(other)); } }
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
		Type& t = type<mud::Circle>();
		static Meta meta = { t, &namspc({ "mud" }), "Circle", sizeof(mud::Circle), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Circle, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Circle>(ref)) mud::Circle(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Circle>(ref)) mud::Circle( val<float>(args[0]), val<mud::Axis>(args[1]) ); }, { { "radius", var(float()) }, { "axis", var(mud::Axis::Y), Param::Default } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Circle>(ref)) mud::Circle( val<mud::vec3>(args[0]), val<float>(args[1]), val<mud::Axis>(args[2]) ); }, { { "center", var(mud::vec3()) }, { "radius", var(float()) }, { "axis", var(mud::Axis::Y), Param::Default } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Circle>(ref)) mud::Circle(val<mud::Circle>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Circle::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr },
				{ t, member_address(&mud::Circle::m_axis), type<mud::Axis>(), "axis", var(mud::Axis::X), Member::Value, nullptr }
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
		Type& t = type<mud::ConvexHull>();
		static Meta meta = { t, &namspc({ "mud" }), "ConvexHull", sizeof(mud::ConvexHull), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::ConvexHull, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ConvexHull>(ref)) mud::ConvexHull(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ConvexHull>(ref)) mud::ConvexHull( val<vector<mud::vec3>>(args[0]) ); }, { { "vertices", var(vector<mud::vec3>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ConvexHull>(ref)) mud::ConvexHull(val<mud::ConvexHull>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ConvexHull::m_vertices), type<vector<mud::vec3>>(), "vertices", var(vector<mud::vec3>()), Member::Value, nullptr }
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
		Type& t = type<mud::Cylinder>();
		static Meta meta = { t, &namspc({ "mud" }), "Cylinder", sizeof(mud::Cylinder), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Cylinder, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Cylinder>(ref)) mud::Cylinder(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Cylinder>(ref)) mud::Cylinder( val<float>(args[0]), val<float>(args[1]), val<mud::Axis>(args[2]) ); }, { { "radius", var(float()) }, { "height", var(float()) }, { "axis", var(mud::Axis::X), Param::Default } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Cylinder>(ref)) mud::Cylinder(val<mud::Cylinder>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Cylinder::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr },
				{ t, member_address(&mud::Cylinder::m_height), type<float>(), "height", var(float(2.f)), Member::Value, nullptr },
				{ t, member_address(&mud::Cylinder::m_axis), type<mud::Axis>(), "axis", var(mud::Axis::X), Member::Value, nullptr }
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
		Type& t = type<mud::Ellipsis>();
		static Meta meta = { t, &namspc({ "mud" }), "Ellipsis", sizeof(mud::Ellipsis), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Ellipsis, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Ellipsis>(ref)) mud::Ellipsis(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Ellipsis>(ref)) mud::Ellipsis( val<mud::vec2>(args[0]), val<mud::Axis>(args[1]) ); }, { { "radius", var(mud::vec2()) }, { "axis", var(mud::Axis::Y), Param::Default } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Ellipsis>(ref)) mud::Ellipsis(val<mud::Ellipsis>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Ellipsis::m_radius), type<mud::vec2>(), "radius", var(mud::vec2(Unit2)), Member::Value, nullptr },
				{ t, member_address(&mud::Ellipsis::m_axis), type<mud::Axis>(), "axis", var(mud::Axis::Y), Member::Value, nullptr }
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
		Type& t = type<mud::Geometry>();
		static Meta meta = { t, &namspc({ "mud" }), "Geometry", sizeof(mud::Geometry), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Geometry, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Geometry>(ref)) mud::Geometry(  ); }, {} }
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
		Type& t = type<mud::Grid2>();
		static Meta meta = { t, &namspc({ "mud" }), "Grid2", sizeof(mud::Grid2), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Grid2, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Grid2>(ref)) mud::Grid2(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Grid2>(ref)) mud::Grid2( val<mud::vec2>(args[0]), val<mud::vec2>(args[1]) ); }, { { "size", var(mud::vec2()) }, { "space", var(mud::vec2(Unit2)), Param::Default } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Grid2>(ref)) mud::Grid2(val<mud::Grid2>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Grid2::m_size), type<mud::vec2>(), "size", var(mud::vec2{1.f}), Member::Value, nullptr },
				{ t, member_address(&mud::Grid2::m_space), type<mud::vec2>(), "space", var(mud::vec2{0.1f}), Member::Value, nullptr }
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
		Type& t = type<mud::Grid3>();
		static Meta meta = { t, &namspc({ "mud" }), "Grid3", sizeof(mud::Grid3), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Grid3, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Grid3>(ref)) mud::Grid3(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Grid3>(ref)) mud::Grid3( val<mud::uvec2>(args[0]), val<vector<mud::vec3>>(args[1]) ); }, { { "size", var(mud::uvec2()) }, { "points", var(vector<mud::vec3>{}), Param::Default } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Grid3>(ref)) mud::Grid3(val<mud::Grid3>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Grid3::m_size), type<mud::uvec2>(), "size", var(mud::uvec2()), Member::Value, nullptr },
				{ t, member_address(&mud::Grid3::m_points), type<vector<mud::vec3>>(), "points", var(vector<mud::vec3>()), Member::Value, nullptr }
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
		Type& t = type<mud::Line>();
		static Meta meta = { t, &namspc({ "mud" }), "Line", sizeof(mud::Line), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Line, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Line>(ref)) mud::Line(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Line>(ref)) mud::Line( val<mud::vec3>(args[0]), val<mud::vec3>(args[1]) ); }, { { "start", var(mud::vec3()) }, { "end", var(mud::vec3()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Line>(ref)) mud::Line(val<mud::Line>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Line::m_start), type<mud::vec3>(), "start", var(mud::vec3(Zero3)), Member::Value, nullptr },
				{ t, member_address(&mud::Line::m_end), type<mud::vec3>(), "end", var(mud::vec3(Unit3)), Member::Value, nullptr }
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
		Type& t = type<mud::Points>();
		static Meta meta = { t, &namspc({ "mud" }), "Points", sizeof(mud::Points), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Points, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Points>(ref)) mud::Points(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Points>(ref)) mud::Points( val<vector<mud::vec3>>(args[0]) ); }, { { "points", var(vector<mud::vec3>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Points>(ref)) mud::Points(val<mud::Points>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Points::m_points), type<vector<mud::vec3>>(), "points", var(vector<mud::vec3>()), Member::Value, nullptr }
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
		Type& t = type<mud::Poisson>();
		static Meta meta = { t, &namspc({ "mud" }), "Poisson", sizeof(mud::Poisson), TypeClass::Object };
		static Class cls = { t,
			// bases
			{ &type<mud::Distribution>() },
			{ base_offset<mud::Poisson, mud::Distribution>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Poisson>(ref)) mud::Poisson( val<mud::vec2>(args[0]), val<float>(args[1]) ); }, { { "size", var(mud::vec2()) }, { "maxRadius", var(float()) } } }
			},
			// copy constructor
			{
			},
			// members
			{
			},
			// methods
			{
				{ t, "distribute", member_address<vector<mud::vec3>(mud::Poisson::*)(float)>(&mud::Poisson::distribute), [](Ref object, array<Var> args, Var& result) { val<vector<mud::vec3>>(result) = val<mud::Poisson>(object).distribute(val<float>(args[0])); }, { { "radius", var(float()) } }, var(vector<mud::vec3>()) },
				{ t, "distribute_circles", member_address<vector<mud::Circle>(mud::Poisson::*)(float)>(&mud::Poisson::distribute_circles), [](Ref object, array<Var> args, Var& result) { val<vector<mud::Circle>>(result) = val<mud::Poisson>(object).distribute_circles(val<float>(args[0])); }, { { "radius", var(float()) } }, var(vector<mud::Circle>()) },
				{ t, "addPoint", member_address<bool(mud::Poisson::*)(float, mud::vec3&)>(&mud::Poisson::addPoint), [](Ref object, array<Var> args, Var& result) { val<bool>(result) = val<mud::Poisson>(object).addPoint(val<float>(args[0]), val<mud::vec3>(args[1])); }, { { "radius", var(float()) }, { "point", var(mud::vec3()) } }, var(bool()) }
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
		Type& t = type<mud::Polygon>();
		static Meta meta = { t, &namspc({ "mud" }), "Polygon", sizeof(mud::Polygon), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Polygon, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Polygon>(ref)) mud::Polygon(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Polygon>(ref)) mud::Polygon( val<vector<mud::vec3>>(args[0]) ); }, { { "vertices", var(vector<mud::vec3>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Polygon>(ref)) mud::Polygon(val<mud::Polygon>(other)); } }
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
		Type& t = type<mud::Quad>();
		static Meta meta = { t, &namspc({ "mud" }), "Quad", sizeof(mud::Quad), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Quad, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Quad>(ref)) mud::Quad(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Quad>(ref)) mud::Quad( val<mud::vec3>(args[0]), val<mud::vec3>(args[1]), val<mud::vec3>(args[2]), val<mud::vec3>(args[3]) ); }, { { "a", var(mud::vec3()) }, { "b", var(mud::vec3()) }, { "c", var(mud::vec3()) }, { "d", var(mud::vec3()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Quad>(ref)) mud::Quad(val<mud::Quad>(other)); } }
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
		Type& t = type<mud::Rect>();
		static Meta meta = { t, &namspc({ "mud" }), "Rect", sizeof(mud::Rect), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Rect, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Rect>(ref)) mud::Rect(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Rect>(ref)) mud::Rect( val<mud::vec2>(args[0]), val<mud::vec2>(args[1]) ); }, { { "position", var(mud::vec2()) }, { "size", var(mud::vec2()) } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Rect>(ref)) mud::Rect( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]), val<float>(args[3]) ); }, { { "x", var(float()) }, { "y", var(float()) }, { "w", var(float()) }, { "h", var(float()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Rect>(ref)) mud::Rect(val<mud::Rect>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Rect::m_position), type<mud::vec2>(), "position", var(mud::vec2(Zero2)), Member::Value, nullptr },
				{ t, member_address(&mud::Rect::m_size), type<mud::vec2>(), "size", var(mud::vec2(Unit2)), Member::Value, nullptr }
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
		Type& t = type<mud::Ring>();
		static Meta meta = { t, &namspc({ "mud" }), "Ring", sizeof(mud::Ring), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Ring, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Ring>(ref)) mud::Ring(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Ring>(ref)) mud::Ring( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]) ); }, { { "radius", var(float()) }, { "min", var(float()) }, { "max", var(float()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Ring>(ref)) mud::Ring(val<mud::Ring>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Ring::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr },
				{ t, member_address(&mud::Ring::m_min), type<float>(), "min", var(float(0.f)), Member::Value, nullptr },
				{ t, member_address(&mud::Ring::m_max), type<float>(), "max", var(float(1.f)), Member::Value, nullptr }
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
		Type& t = type<mud::Sphere>();
		static Meta meta = { t, &namspc({ "mud" }), "Sphere", sizeof(mud::Sphere), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Sphere, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Sphere>(ref)) mud::Sphere(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Sphere>(ref)) mud::Sphere( val<float>(args[0]) ); }, { { "radius", var(float()) } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Sphere>(ref)) mud::Sphere( val<mud::vec3>(args[0]), val<float>(args[1]) ); }, { { "center", var(mud::vec3()) }, { "radius", var(float()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Sphere>(ref)) mud::Sphere(val<mud::Sphere>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Sphere::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr }
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
		Type& t = type<mud::SphereRing>();
		static Meta meta = { t, &namspc({ "mud" }), "SphereRing", sizeof(mud::SphereRing), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::SphereRing, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::SphereRing>(ref)) mud::SphereRing(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::SphereRing>(ref)) mud::SphereRing( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]) ); }, { { "radius", var(float()) }, { "min", var(float()) }, { "max", var(float()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::SphereRing>(ref)) mud::SphereRing(val<mud::SphereRing>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::SphereRing::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr },
				{ t, member_address(&mud::SphereRing::m_min), type<float>(), "min", var(float()), Member::Value, nullptr },
				{ t, member_address(&mud::SphereRing::m_max), type<float>(), "max", var(float(1.f)), Member::Value, nullptr }
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
		Type& t = type<mud::Spheroid>();
		static Meta meta = { t, &namspc({ "mud" }), "Spheroid", sizeof(mud::Spheroid), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Spheroid, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Spheroid>(ref)) mud::Spheroid(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Spheroid>(ref)) mud::Spheroid( val<float>(args[0]) ); }, { { "radius", var(float()) } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Spheroid>(ref)) mud::Spheroid( val<mud::vec3>(args[0]), val<float>(args[1]) ); }, { { "center", var(mud::vec3()) }, { "radius", var(float()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Spheroid>(ref)) mud::Spheroid(val<mud::Spheroid>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Spheroid::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr }
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
		Type& t = type<mud::Torus>();
		static Meta meta = { t, &namspc({ "mud" }), "Torus", sizeof(mud::Torus), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Torus, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Torus>(ref)) mud::Torus(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Torus>(ref)) mud::Torus( val<float>(args[0]), val<float>(args[1]), val<mud::Axis>(args[2]) ); }, { { "radius", var(float()) }, { "solid_radius", var(float()) }, { "axis", var(mud::Axis::Y), Param::Default } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Torus>(ref)) mud::Torus( val<mud::vec3>(args[0]), val<float>(args[1]), val<float>(args[2]), val<mud::Axis>(args[3]) ); }, { { "center", var(mud::vec3()) }, { "radius", var(float()) }, { "solid_radius", var(float()) }, { "axis", var(mud::Axis::Y), Param::Default } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Torus>(ref)) mud::Torus(val<mud::Torus>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Torus::m_radius), type<float>(), "radius", var(float(1.f)), Member::Value, nullptr },
				{ t, member_address(&mud::Torus::m_solid_radius), type<float>(), "solid_radius", var(float(1.f)), Member::Value, nullptr },
				{ t, member_address(&mud::Torus::m_axis), type<mud::Axis>(), "axis", var(mud::Axis::X), Member::Value, nullptr }
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
		Type& t = type<mud::Triangle>();
		static Meta meta = { t, &namspc({ "mud" }), "Triangle", sizeof(mud::Triangle), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{ &type<mud::Shape>() },
			{ base_offset<mud::Triangle, mud::Shape>() },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Triangle>(ref)) mud::Triangle(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Triangle>(ref)) mud::Triangle( val<mud::vec2>(args[0]) ); }, { { "size", var(mud::vec2()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Triangle>(ref)) mud::Triangle(val<mud::Triangle>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Triangle::m_size), type<mud::vec2>(), "size", var(mud::vec2(Unit2)), Member::Value, nullptr }
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

namespace mud
{
	mud_geom::mud_geom()
		: Module("mud::geom", { &mud_type::m(), &mud_math::m() })
	{
		// setup reflection meta data
		mud_geom_meta(*this);
	}
}

#ifdef MUD_GEOM_MODULE
extern "C"
Module& getModule()
{
		return mud_geom::m();
}
#endif
