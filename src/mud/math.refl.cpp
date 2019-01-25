#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/math.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.math;
#else
#endif


namespace mud
{
	void mud_math_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::Axes>();
		static Meta meta = { t, &namspc({ "mud" }), "Axes", sizeof(mud::Axes), TypeClass::Enum };
		static cstring ids[] = { "None", "X", "Y", "Z" };
		static uint32_t values[] = { 0, 1, 2, 4 };
		static mud::Axes vars[] = { mud::Axes::None, mud::Axes::X, mud::Axes::Y, mud::Axes::Z};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::Axes>();
	}
	{
		Type& t = type<mud::Axis>();
		static Meta meta = { t, &namspc({ "mud" }), "Axis", sizeof(mud::Axis), TypeClass::Enum };
		static cstring ids[] = { "X", "Y", "Z" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::Axis vars[] = { mud::Axis::X, mud::Axis::Y, mud::Axis::Z};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::Axis>();
	}
	{
		Type& t = type<mud::Clockwise>();
		static Meta meta = { t, &namspc({ "mud" }), "Clockwise", sizeof(mud::Clockwise), TypeClass::Enum };
		static cstring ids[] = { "CLOCKWISE", "ANTI_CLOCKWISE" };
		static uint32_t values[] = { 0, 1 };
		static mud::Clockwise vars[] = { mud::CLOCKWISE, mud::ANTI_CLOCKWISE};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, false, ids, values, refs };
		meta_enum<mud::Clockwise>();
	}
	{
		Type& t = type<mud::Side>();
		static Meta meta = { t, &namspc({ "mud" }), "Side", sizeof(mud::Side), TypeClass::Enum };
		static cstring ids[] = { "Right", "Left", "Up", "Down", "Back", "Front" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5 };
		static mud::Side vars[] = { mud::Side::Right, mud::Side::Left, mud::Side::Up, mud::Side::Down, mud::Side::Back, mud::Side::Front};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::Side>();
	}
	{
		Type& t = type<mud::SignedAxis>();
		static Meta meta = { t, &namspc({ "mud" }), "SignedAxis", sizeof(mud::SignedAxis), TypeClass::Enum };
		static cstring ids[] = { "PlusX", "MinusX", "PlusY", "MinusY", "PlusZ", "MinusZ" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5 };
		static mud::SignedAxis vars[] = { mud::SignedAxis::PlusX, mud::SignedAxis::MinusX, mud::SignedAxis::PlusY, mud::SignedAxis::MinusY, mud::SignedAxis::PlusZ, mud::SignedAxis::MinusZ};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::SignedAxis>();
	}
	{
		Type& t = type<mud::Spectrum>();
		static Meta meta = { t, &namspc({ "mud" }), "Spectrum", sizeof(mud::Spectrum), TypeClass::Enum };
		static cstring ids[] = { "Value", "Hue" };
		static uint32_t values[] = { 0, 1 };
		static mud::Spectrum vars[] = { mud::Spectrum::Value, mud::Spectrum::Hue};
		static void* refs[] = { &vars[0], &vars[1]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::Spectrum>();
	}
	{
		Type& t = type<mud::TrackMode>();
		static Meta meta = { t, &namspc({ "mud" }), "TrackMode", sizeof(mud::TrackMode), TypeClass::Enum };
		static cstring ids[] = { "Constant", "ConstantRandom", "Curve", "CurveRandom" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static mud::TrackMode vars[] = { mud::TrackMode::Constant, mud::TrackMode::ConstantRandom, mud::TrackMode::Curve, mud::TrackMode::CurveRandom};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<mud::TrackMode>();
	}
	
	// Sequences
	{
		Type& t = type<vector<float>>();
		static Meta meta = { t, &namspc({}), "vector<float>", sizeof(vector<float>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<float>();
		meta_vector<vector<float>, float>();
	}
	{
		Type& t = type<vector<mud::Colour>>();
		static Meta meta = { t, &namspc({}), "vector<mud::Colour>", sizeof(vector<mud::Colour>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::Colour>();
		meta_vector<vector<mud::Colour>, mud::Colour>();
	}
	{
		Type& t = type<vector<mud::quat>>();
		static Meta meta = { t, &namspc({}), "vector<mud::quat>", sizeof(vector<mud::quat>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::quat>();
		meta_vector<vector<mud::quat>, mud::quat>();
	}
	{
		Type& t = type<vector<mud::uvec3>>();
		static Meta meta = { t, &namspc({}), "vector<mud::uvec3>", sizeof(vector<mud::uvec3>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::uvec3>();
		meta_vector<vector<mud::uvec3>, mud::uvec3>();
	}
	{
		Type& t = type<vector<mud::vec3>>();
		static Meta meta = { t, &namspc({}), "vector<mud::vec3>", sizeof(vector<mud::vec3>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<mud::vec3>();
		meta_vector<vector<mud::vec3>, mud::vec3>();
	}
	{
		Type& t = type<vector<uint32_t>>();
		static Meta meta = { t, &namspc({}), "vector<uint32_t>", sizeof(vector<uint32_t>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<uint32_t>();
		meta_vector<vector<uint32_t>, uint32_t>();
	}
	
	// mud::AutoStat<float>
	{
		Type& t = type<mud::AutoStat<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "AutoStat<float>", sizeof(mud::AutoStat<float>), TypeClass::Object };
		// defaults
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
		meta_class<mud::AutoStat<float>>();
	}
	// mud::AutoStat<int>
	{
		Type& t = type<mud::AutoStat<int>>();
		static Meta meta = { t, &namspc({ "mud" }), "AutoStat<int>", sizeof(mud::AutoStat<int>), TypeClass::Object };
		// defaults
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
		meta_class<mud::AutoStat<int>>();
	}
	// mud::Colour
	{
		Type& t = type<mud::Colour>();
		static Meta meta = { t, &namspc({ "mud" }), "Colour", sizeof(mud::Colour), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Colour>(ref)) mud::Colour(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Colour>(ref)) mud::Colour( val<float>(args[0]), val<float>(args[1]) ); }, { { "v", var(float()) }, { "a", var(float(1.f)), Param::Default } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Colour>(ref)) mud::Colour( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]), val<float>(args[3]) ); }, { { "r", var(float()) }, { "g", var(float()) }, { "b", var(float()) }, { "a", var(float(1.f)), Param::Default } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Colour>(ref)) mud::Colour(val<mud::Colour>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Colour::m_r), type<float>(), "r", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Colour::m_g), type<float>(), "g", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Colour::m_b), type<float>(), "b", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Colour::m_a), type<float>(), "a", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
				{ t, "Black", Ref(&mud::Colour::Black) },
				{ t, "AlphaBlack", Ref(&mud::Colour::AlphaBlack) },
				{ t, "Red", Ref(&mud::Colour::Red) },
				{ t, "Green", Ref(&mud::Colour::Green) },
				{ t, "NeonGreen", Ref(&mud::Colour::NeonGreen) },
				{ t, "Blue", Ref(&mud::Colour::Blue) },
				{ t, "Pink", Ref(&mud::Colour::Pink) },
				{ t, "Cyan", Ref(&mud::Colour::Cyan) },
				{ t, "Yellow", Ref(&mud::Colour::Yellow) },
				{ t, "White", Ref(&mud::Colour::White) },
				{ t, "AlphaWhite", Ref(&mud::Colour::AlphaWhite) },
				{ t, "LightGrey", Ref(&mud::Colour::LightGrey) },
				{ t, "MidGrey", Ref(&mud::Colour::MidGrey) },
				{ t, "DarkGrey", Ref(&mud::Colour::DarkGrey) },
				{ t, "AlphaGrey", Ref(&mud::Colour::AlphaGrey) },
				{ t, "Transparent", Ref(&mud::Colour::Transparent) },
				{ t, "Invisible", Ref(&mud::Colour::Invisible) },
				{ t, "None", Ref(&mud::Colour::None) }
			}
		};
		init_string<mud::Colour>();
		meta_class<mud::Colour>();
	}
	// mud::Gauge
	{
		Type& t = type<mud::Gauge>();
		static Meta meta = { t, &namspc({ "mud" }), "Gauge", sizeof(mud::Gauge), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Gauge>(ref)) mud::Gauge( val<float>(args[0]) ); }, { { "value", var(float(0.f)), Param::Default } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Gauge>(ref)) mud::Gauge(val<mud::Gauge>(other)); } }
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
		meta_class<mud::Gauge>();
	}
	// mud::Image
	{
		Type& t = type<mud::Image>();
		static Meta meta = { t, &namspc({ "mud" }), "Image", sizeof(mud::Image), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Image>(ref)) mud::Image(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Image>(ref)) mud::Image(val<mud::Image>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Image::d_name), type<string>(), "d_name", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Image::d_path), type<string>(), "d_path", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Image>();
	}
	// mud::Image256
	{
		Type& t = type<mud::Image256>();
		static Meta meta = { t, &namspc({ "mud" }), "Image256", sizeof(mud::Image256), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Image256>(ref)) mud::Image256( val<uint16_t>(args[0]), val<uint16_t>(args[1]), val<mud::Palette>(args[2]) ); }, { { "width", var(uint16_t(0)), Param::Default }, { "height", var(uint16_t(0)), Param::Default }, { "palette", var(mud::Palette()), Param::Default } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Image256>(ref)) mud::Image256(val<mud::Image256>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Image256::m_pixels), type<vector<uint32_t>>(), "pixels", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Image256::m_width), type<uint16_t>(), "width", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Image256::m_height), type<uint16_t>(), "height", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Image256::m_palette), type<mud::Palette>(), "palette", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Image256>();
	}
	// mud::ImageAtlas
	{
		Type& t = type<mud::ImageAtlas>();
		static Meta meta = { t, &namspc({ "mud" }), "ImageAtlas", sizeof(mud::ImageAtlas), TypeClass::Object };
		// defaults
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
		meta_class<mud::ImageAtlas>();
	}
	// mud::Palette
	{
		Type& t = type<mud::Palette>();
		static Meta meta = { t, &namspc({ "mud" }), "Palette", sizeof(mud::Palette), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Palette>(ref)) mud::Palette( val<mud::Spectrum>(args[0]), val<size_t>(args[1]) ); }, { { "spectrum", var(mud::Spectrum()) }, { "steps", var(size_t()) } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Palette>(ref)) mud::Palette( val<vector<mud::Colour>>(args[0]) ); }, { { "colours", var(vector<mud::Colour>()) } } },
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Palette>(ref)) mud::Palette(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Palette>(ref)) mud::Palette(val<mud::Palette>(other)); } }
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
		meta_class<mud::Palette>();
	}
	// mud::Range<float>
	{
		Type& t = type<mud::Range<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "Range<float>", sizeof(mud::Range<float>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Range<float>>(ref)) mud::Range<float>(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Range<float>>(ref)) mud::Range<float>(val<mud::Range<float>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Range<float>::m_min), type<float>(), "min", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Range<float>::m_max), type<float>(), "max", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Range<float>>();
	}
	// mud::Range<mud::Colour>
	{
		Type& t = type<mud::Range<mud::Colour>>();
		static Meta meta = { t, &namspc({ "mud" }), "Range<mud::Colour>", sizeof(mud::Range<mud::Colour>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Range<mud::Colour>>(ref)) mud::Range<mud::Colour>(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Range<mud::Colour>>(ref)) mud::Range<mud::Colour>(val<mud::Range<mud::Colour>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Range<mud::Colour>::m_min), type<mud::Colour>(), "min", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Range<mud::Colour>::m_max), type<mud::Colour>(), "max", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Range<mud::Colour>>();
	}
	// mud::Range<mud::quat>
	{
		Type& t = type<mud::Range<mud::quat>>();
		static Meta meta = { t, &namspc({ "mud" }), "Range<mud::quat>", sizeof(mud::Range<mud::quat>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Range<mud::quat>>(ref)) mud::Range<mud::quat>(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Range<mud::quat>>(ref)) mud::Range<mud::quat>(val<mud::Range<mud::quat>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Range<mud::quat>::m_min), type<mud::quat>(), "min", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Range<mud::quat>::m_max), type<mud::quat>(), "max", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Range<mud::quat>>();
	}
	// mud::Range<mud::vec3>
	{
		Type& t = type<mud::Range<mud::vec3>>();
		static Meta meta = { t, &namspc({ "mud" }), "Range<mud::vec3>", sizeof(mud::Range<mud::vec3>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Range<mud::vec3>>(ref)) mud::Range<mud::vec3>(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Range<mud::vec3>>(ref)) mud::Range<mud::vec3>(val<mud::Range<mud::vec3>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Range<mud::vec3>::m_min), type<mud::vec3>(), "min", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Range<mud::vec3>::m_max), type<mud::vec3>(), "max", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Range<mud::vec3>>();
	}
	// mud::Range<uint32_t>
	{
		Type& t = type<mud::Range<uint32_t>>();
		static Meta meta = { t, &namspc({ "mud" }), "Range<uint32_t>", sizeof(mud::Range<uint32_t>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Range<uint32_t>>(ref)) mud::Range<uint32_t>(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Range<uint32_t>>(ref)) mud::Range<uint32_t>(val<mud::Range<uint32_t>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Range<uint32_t>::m_min), type<uint32_t>(), "min", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::Range<uint32_t>::m_max), type<uint32_t>(), "max", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Range<uint32_t>>();
	}
	// mud::Ratio
	{
		Type& t = type<mud::Ratio>();
		static Meta meta = { t, &namspc({ "mud" }), "Ratio", sizeof(mud::Ratio), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Ratio>(ref)) mud::Ratio( val<float>(args[0]) ); }, { { "value", var(float(0.f)), Param::Default } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Ratio>(ref)) mud::Ratio(val<mud::Ratio>(other)); } }
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
		meta_class<mud::Ratio>();
	}
	// mud::Time
	{
		Type& t = type<mud::Time>();
		static Meta meta = { t, &namspc({ "mud" }), "Time", sizeof(mud::Time), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Time>(ref)) mud::Time( val<double>(args[0]) ); }, { { "value", var(double()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Time>(ref)) mud::Time(val<mud::Time>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Time::m_value), type<double>(), "value", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Time>();
	}
	// mud::TimeSpan
	{
		Type& t = type<mud::TimeSpan>();
		static Meta meta = { t, &namspc({ "mud" }), "TimeSpan", sizeof(mud::TimeSpan), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::TimeSpan>(ref)) mud::TimeSpan( val<mud::Time>(args[0]), val<mud::Time>(args[1]) ); }, { { "s", var(mud::Time()) }, { "e", var(mud::Time()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::TimeSpan>(ref)) mud::TimeSpan(val<mud::TimeSpan>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::TimeSpan::start), type<mud::Time>(), "start", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::TimeSpan::end), type<mud::Time>(), "end", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::TimeSpan>();
	}
	// mud::Transform
	{
		Type& t = type<mud::Transform>();
		static Meta meta = { t, &namspc({ "mud" }), "Transform", sizeof(mud::Transform), TypeClass::Struct };
		// defaults
		static mud::vec3 position_default = Zero3;
		static mud::quat rotation_default = ZeroQuat;
		static mud::vec3 scale_default = Unit3;
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::Transform>(ref)) mud::Transform(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::Transform>(ref)) mud::Transform( val<mud::vec3>(args[0]), val<mud::quat>(args[1]), val<mud::vec3>(args[2]) ); }, { { "position", var(mud::vec3()) }, { "rotation", var(mud::quat()) }, { "scale", var(mud::vec3()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::Transform>(ref)) mud::Transform(val<mud::Transform>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::Transform::m_position), type<mud::vec3>(), "position", Ref(&position_default), Member::Value, nullptr },
				{ t, member_address(&mud::Transform::m_rotation), type<mud::quat>(), "rotation", Ref(&rotation_default), Member::Value, nullptr },
				{ t, member_address(&mud::Transform::m_scale), type<mud::vec3>(), "scale", Ref(&scale_default), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::Transform>();
	}
	// mud::ValueCurve<float>
	{
		Type& t = type<mud::ValueCurve<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueCurve<float>", sizeof(mud::ValueCurve<float>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ValueCurve<float>>(ref)) mud::ValueCurve<float>(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<float>>(ref)) mud::ValueCurve<float>( val<vector<float>>(args[0]) ); }, { { "keys", var(vector<float>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ValueCurve<float>>(ref)) mud::ValueCurve<float>(val<mud::ValueCurve<float>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ValueCurve<float>::m_keys), type<vector<float>>(), "keys", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ValueCurve<float>>();
	}
	// mud::ValueCurve<mud::Colour>
	{
		Type& t = type<mud::ValueCurve<mud::Colour>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueCurve<mud::Colour>", sizeof(mud::ValueCurve<mud::Colour>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ValueCurve<mud::Colour>>(ref)) mud::ValueCurve<mud::Colour>(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<mud::Colour>>(ref)) mud::ValueCurve<mud::Colour>( val<vector<mud::Colour>>(args[0]) ); }, { { "keys", var(vector<mud::Colour>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ValueCurve<mud::Colour>>(ref)) mud::ValueCurve<mud::Colour>(val<mud::ValueCurve<mud::Colour>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ValueCurve<mud::Colour>::m_keys), type<vector<mud::Colour>>(), "keys", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ValueCurve<mud::Colour>>();
	}
	// mud::ValueCurve<mud::quat>
	{
		Type& t = type<mud::ValueCurve<mud::quat>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueCurve<mud::quat>", sizeof(mud::ValueCurve<mud::quat>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ValueCurve<mud::quat>>(ref)) mud::ValueCurve<mud::quat>(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<mud::quat>>(ref)) mud::ValueCurve<mud::quat>( val<vector<mud::quat>>(args[0]) ); }, { { "keys", var(vector<mud::quat>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ValueCurve<mud::quat>>(ref)) mud::ValueCurve<mud::quat>(val<mud::ValueCurve<mud::quat>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ValueCurve<mud::quat>::m_keys), type<vector<mud::quat>>(), "keys", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ValueCurve<mud::quat>>();
	}
	// mud::ValueCurve<mud::vec3>
	{
		Type& t = type<mud::ValueCurve<mud::vec3>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueCurve<mud::vec3>", sizeof(mud::ValueCurve<mud::vec3>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ValueCurve<mud::vec3>>(ref)) mud::ValueCurve<mud::vec3>(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<mud::vec3>>(ref)) mud::ValueCurve<mud::vec3>( val<vector<mud::vec3>>(args[0]) ); }, { { "keys", var(vector<mud::vec3>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ValueCurve<mud::vec3>>(ref)) mud::ValueCurve<mud::vec3>(val<mud::ValueCurve<mud::vec3>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ValueCurve<mud::vec3>::m_keys), type<vector<mud::vec3>>(), "keys", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ValueCurve<mud::vec3>>();
	}
	// mud::ValueCurve<uint32_t>
	{
		Type& t = type<mud::ValueCurve<uint32_t>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueCurve<uint32_t>", sizeof(mud::ValueCurve<uint32_t>), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ValueCurve<uint32_t>>(ref)) mud::ValueCurve<uint32_t>(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<uint32_t>>(ref)) mud::ValueCurve<uint32_t>( val<vector<uint32_t>>(args[0]) ); }, { { "keys", var(vector<uint32_t>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ValueCurve<uint32_t>>(ref)) mud::ValueCurve<uint32_t>(val<mud::ValueCurve<uint32_t>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ValueCurve<uint32_t>::m_keys), type<vector<uint32_t>>(), "keys", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ValueCurve<uint32_t>>();
	}
	// mud::ValueTrack<float>
	{
		Type& t = type<mud::ValueTrack<float>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueTrack<float>", sizeof(mud::ValueTrack<float>), TypeClass::Struct };
		// defaults
		static float value_default = One<float>::value();
		static float min_default = One<float>::value();
		static float max_default = One<float>::value();
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ValueTrack<float>>(ref)) mud::ValueTrack<float>(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<float>>(ref)) mud::ValueTrack<float>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<float>>(args[1]), val<mud::ValueCurve<float>>(args[2]), val<mud::ValueCurve<float>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<float>()) }, { "min_curve", var(mud::ValueCurve<float>()) }, { "max_curve", var(mud::ValueCurve<float>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ValueTrack<float>>(ref)) mud::ValueTrack<float>(val<mud::ValueTrack<float>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ValueTrack<float>::m_mode), type<mud::TrackMode>(), "mode", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<float>::m_value), type<float>(), "value", Ref(&value_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<float>::m_min), type<float>(), "min", Ref(&min_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<float>::m_max), type<float>(), "max", Ref(&max_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<float>::m_curve), type<mud::ValueCurve<float>>(), "curve", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<float>::m_min_curve), type<mud::ValueCurve<float>>(), "min_curve", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<float>::m_max_curve), type<mud::ValueCurve<float>>(), "max_curve", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ValueTrack<float>>();
	}
	// mud::ValueTrack<mud::Colour>
	{
		Type& t = type<mud::ValueTrack<mud::Colour>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueTrack<mud::Colour>", sizeof(mud::ValueTrack<mud::Colour>), TypeClass::Struct };
		// defaults
		static mud::Colour value_default = One<mud::Colour>::value();
		static mud::Colour min_default = One<mud::Colour>::value();
		static mud::Colour max_default = One<mud::Colour>::value();
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ValueTrack<mud::Colour>>(ref)) mud::ValueTrack<mud::Colour>(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<mud::Colour>>(ref)) mud::ValueTrack<mud::Colour>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<mud::Colour>>(args[1]), val<mud::ValueCurve<mud::Colour>>(args[2]), val<mud::ValueCurve<mud::Colour>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<mud::Colour>()) }, { "min_curve", var(mud::ValueCurve<mud::Colour>()) }, { "max_curve", var(mud::ValueCurve<mud::Colour>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ValueTrack<mud::Colour>>(ref)) mud::ValueTrack<mud::Colour>(val<mud::ValueTrack<mud::Colour>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ValueTrack<mud::Colour>::m_mode), type<mud::TrackMode>(), "mode", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::Colour>::m_value), type<mud::Colour>(), "value", Ref(&value_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::Colour>::m_min), type<mud::Colour>(), "min", Ref(&min_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::Colour>::m_max), type<mud::Colour>(), "max", Ref(&max_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::Colour>::m_curve), type<mud::ValueCurve<mud::Colour>>(), "curve", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::Colour>::m_min_curve), type<mud::ValueCurve<mud::Colour>>(), "min_curve", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::Colour>::m_max_curve), type<mud::ValueCurve<mud::Colour>>(), "max_curve", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ValueTrack<mud::Colour>>();
	}
	// mud::ValueTrack<mud::quat>
	{
		Type& t = type<mud::ValueTrack<mud::quat>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueTrack<mud::quat>", sizeof(mud::ValueTrack<mud::quat>), TypeClass::Struct };
		// defaults
		static mud::quat value_default = One<mud::quat>::value();
		static mud::quat min_default = One<mud::quat>::value();
		static mud::quat max_default = One<mud::quat>::value();
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ValueTrack<mud::quat>>(ref)) mud::ValueTrack<mud::quat>(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<mud::quat>>(ref)) mud::ValueTrack<mud::quat>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<mud::quat>>(args[1]), val<mud::ValueCurve<mud::quat>>(args[2]), val<mud::ValueCurve<mud::quat>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<mud::quat>()) }, { "min_curve", var(mud::ValueCurve<mud::quat>()) }, { "max_curve", var(mud::ValueCurve<mud::quat>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ValueTrack<mud::quat>>(ref)) mud::ValueTrack<mud::quat>(val<mud::ValueTrack<mud::quat>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ValueTrack<mud::quat>::m_mode), type<mud::TrackMode>(), "mode", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::quat>::m_value), type<mud::quat>(), "value", Ref(&value_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::quat>::m_min), type<mud::quat>(), "min", Ref(&min_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::quat>::m_max), type<mud::quat>(), "max", Ref(&max_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::quat>::m_curve), type<mud::ValueCurve<mud::quat>>(), "curve", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::quat>::m_min_curve), type<mud::ValueCurve<mud::quat>>(), "min_curve", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::quat>::m_max_curve), type<mud::ValueCurve<mud::quat>>(), "max_curve", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ValueTrack<mud::quat>>();
	}
	// mud::ValueTrack<mud::vec3>
	{
		Type& t = type<mud::ValueTrack<mud::vec3>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueTrack<mud::vec3>", sizeof(mud::ValueTrack<mud::vec3>), TypeClass::Struct };
		// defaults
		static mud::vec3 value_default = One<mud::vec3>::value();
		static mud::vec3 min_default = One<mud::vec3>::value();
		static mud::vec3 max_default = One<mud::vec3>::value();
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ValueTrack<mud::vec3>>(ref)) mud::ValueTrack<mud::vec3>(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<mud::vec3>>(ref)) mud::ValueTrack<mud::vec3>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<mud::vec3>>(args[1]), val<mud::ValueCurve<mud::vec3>>(args[2]), val<mud::ValueCurve<mud::vec3>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<mud::vec3>()) }, { "min_curve", var(mud::ValueCurve<mud::vec3>()) }, { "max_curve", var(mud::ValueCurve<mud::vec3>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ValueTrack<mud::vec3>>(ref)) mud::ValueTrack<mud::vec3>(val<mud::ValueTrack<mud::vec3>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ValueTrack<mud::vec3>::m_mode), type<mud::TrackMode>(), "mode", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::vec3>::m_value), type<mud::vec3>(), "value", Ref(&value_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::vec3>::m_min), type<mud::vec3>(), "min", Ref(&min_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::vec3>::m_max), type<mud::vec3>(), "max", Ref(&max_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::vec3>::m_curve), type<mud::ValueCurve<mud::vec3>>(), "curve", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::vec3>::m_min_curve), type<mud::ValueCurve<mud::vec3>>(), "min_curve", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<mud::vec3>::m_max_curve), type<mud::ValueCurve<mud::vec3>>(), "max_curve", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ValueTrack<mud::vec3>>();
	}
	// mud::ValueTrack<uint32_t>
	{
		Type& t = type<mud::ValueTrack<uint32_t>>();
		static Meta meta = { t, &namspc({ "mud" }), "ValueTrack<uint32_t>", sizeof(mud::ValueTrack<uint32_t>), TypeClass::Struct };
		// defaults
		static uint32_t value_default = One<uint32_t>::value();
		static uint32_t min_default = One<uint32_t>::value();
		static uint32_t max_default = One<uint32_t>::value();
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ValueTrack<uint32_t>>(ref)) mud::ValueTrack<uint32_t>(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<uint32_t>>(ref)) mud::ValueTrack<uint32_t>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<uint32_t>>(args[1]), val<mud::ValueCurve<uint32_t>>(args[2]), val<mud::ValueCurve<uint32_t>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<uint32_t>()) }, { "min_curve", var(mud::ValueCurve<uint32_t>()) }, { "max_curve", var(mud::ValueCurve<uint32_t>()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ValueTrack<uint32_t>>(ref)) mud::ValueTrack<uint32_t>(val<mud::ValueTrack<uint32_t>>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ValueTrack<uint32_t>::m_mode), type<mud::TrackMode>(), "mode", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<uint32_t>::m_value), type<uint32_t>(), "value", Ref(&value_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<uint32_t>::m_min), type<uint32_t>(), "min", Ref(&min_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<uint32_t>::m_max), type<uint32_t>(), "max", Ref(&max_default), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<uint32_t>::m_curve), type<mud::ValueCurve<uint32_t>>(), "curve", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<uint32_t>::m_min_curve), type<mud::ValueCurve<uint32_t>>(), "min_curve", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ValueTrack<uint32_t>::m_max_curve), type<mud::ValueCurve<uint32_t>>(), "max_curve", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		meta_class<mud::ValueTrack<uint32_t>>();
	}
	// mud::bvec3
	{
		Type& t = type<mud::bvec3>();
		static Meta meta = { t, &namspc({ "mud" }), "bvec3", sizeof(mud::bvec3), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::bvec3>(ref)) mud::bvec3(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::bvec3>(ref)) mud::bvec3(val<mud::bvec3>(other)); } }
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
		meta_class<mud::bvec3>();
	}
	// mud::bvec4
	{
		Type& t = type<mud::bvec4>();
		static Meta meta = { t, &namspc({ "mud" }), "bvec4", sizeof(mud::bvec4), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::bvec4>(ref)) mud::bvec4(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::bvec4>(ref)) mud::bvec4(val<mud::bvec4>(other)); } }
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
		meta_class<mud::bvec4>();
	}
	// mud::half2
	{
		Type& t = type<mud::half2>();
		static Meta meta = { t, &namspc({ "mud" }), "half2", sizeof(mud::half2), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::half2>(ref)) mud::half2(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::half2>(ref)) mud::half2(val<mud::half2>(other)); } }
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
		meta_class<mud::half2>();
	}
	// mud::half3
	{
		Type& t = type<mud::half3>();
		static Meta meta = { t, &namspc({ "mud" }), "half3", sizeof(mud::half3), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::half3>(ref)) mud::half3(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::half3>(ref)) mud::half3(val<mud::half3>(other)); } }
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
		meta_class<mud::half3>();
	}
	// mud::ivec2
	{
		Type& t = type<mud::ivec2>();
		static Meta meta = { t, &namspc({ "mud" }), "ivec2", sizeof(mud::ivec2), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ivec2>(ref)) mud::ivec2(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ivec2>(ref)) mud::ivec2(val<mud::ivec2>(other)); } }
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
		meta_class<mud::ivec2>();
	}
	// mud::ivec3
	{
		Type& t = type<mud::ivec3>();
		static Meta meta = { t, &namspc({ "mud" }), "ivec3", sizeof(mud::ivec3), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ivec3>(ref)) mud::ivec3(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ivec3>(ref)) mud::ivec3( val<int>(args[0]) ); }, { { "a", var(int()) } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::ivec3>(ref)) mud::ivec3( val<int>(args[0]), val<int>(args[1]), val<int>(args[2]) ); }, { { "x", var(int()) }, { "y", var(int()) }, { "z", var(int()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ivec3>(ref)) mud::ivec3(val<mud::ivec3>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::ivec3::x), type<int>(), "x", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ivec3::y), type<int>(), "y", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::ivec3::z), type<int>(), "z", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_string<mud::ivec3>();
		meta_class<mud::ivec3>();
	}
	// mud::ivec4
	{
		Type& t = type<mud::ivec4>();
		static Meta meta = { t, &namspc({ "mud" }), "ivec4", sizeof(mud::ivec4), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::ivec4>(ref)) mud::ivec4(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::ivec4>(ref)) mud::ivec4(val<mud::ivec4>(other)); } }
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
		meta_class<mud::ivec4>();
	}
	// mud::mat4
	{
		Type& t = type<mud::mat4>();
		static Meta meta = { t, &namspc({ "mud" }), "mat4", sizeof(mud::mat4), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::mat4>(ref)) mud::mat4(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::mat4>(ref)) mud::mat4(val<mud::mat4>(other)); } }
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
		meta_class<mud::mat4>();
	}
	// mud::quat
	{
		Type& t = type<mud::quat>();
		static Meta meta = { t, &namspc({ "mud" }), "quat", sizeof(mud::quat), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::quat>(ref)) mud::quat(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::quat>(ref)) mud::quat( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]), val<float>(args[3]) ); }, { { "w", var(float()) }, { "x", var(float()) }, { "y", var(float()) }, { "z", var(float()) } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::quat>(ref)) mud::quat( val<mud::vec3>(args[0]) ); }, { { "euler_angles", var(mud::vec3()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::quat>(ref)) mud::quat(val<mud::quat>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::quat::x), type<float>(), "x", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::quat::y), type<float>(), "y", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::quat::z), type<float>(), "z", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::quat::w), type<float>(), "w", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_string<mud::quat>();
		meta_class<mud::quat>();
	}
	// mud::uvec2
	{
		Type& t = type<mud::uvec2>();
		static Meta meta = { t, &namspc({ "mud" }), "uvec2", sizeof(mud::uvec2), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::uvec2>(ref)) mud::uvec2(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::uvec2>(ref)) mud::uvec2( val<uint32_t>(args[0]) ); }, { { "a", var(uint32_t()) } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::uvec2>(ref)) mud::uvec2( val<uint32_t>(args[0]), val<uint32_t>(args[1]) ); }, { { "x", var(uint32_t()) }, { "y", var(uint32_t()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::uvec2>(ref)) mud::uvec2(val<mud::uvec2>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::uvec2::x), type<uint32_t>(), "x", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::uvec2::y), type<uint32_t>(), "y", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_string<mud::uvec2>();
		meta_class<mud::uvec2>();
	}
	// mud::uvec3
	{
		Type& t = type<mud::uvec3>();
		static Meta meta = { t, &namspc({ "mud" }), "uvec3", sizeof(mud::uvec3), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::uvec3>(ref)) mud::uvec3(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::uvec3>(ref)) mud::uvec3( val<uint32_t>(args[0]) ); }, { { "a", var(uint32_t()) } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::uvec3>(ref)) mud::uvec3( val<uint32_t>(args[0]), val<uint32_t>(args[1]), val<uint32_t>(args[2]) ); }, { { "x", var(uint32_t()) }, { "y", var(uint32_t()) }, { "z", var(uint32_t()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::uvec3>(ref)) mud::uvec3(val<mud::uvec3>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::uvec3::x), type<uint32_t>(), "x", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::uvec3::y), type<uint32_t>(), "y", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::uvec3::z), type<uint32_t>(), "z", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_string<mud::uvec3>();
		meta_class<mud::uvec3>();
	}
	// mud::uvec4
	{
		Type& t = type<mud::uvec4>();
		static Meta meta = { t, &namspc({ "mud" }), "uvec4", sizeof(mud::uvec4), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::uvec4>(ref)) mud::uvec4(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::uvec4>(ref)) mud::uvec4( val<uint32_t>(args[0]) ); }, { { "a", var(uint32_t()) } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::uvec4>(ref)) mud::uvec4( val<uint32_t>(args[0]), val<uint32_t>(args[1]), val<uint32_t>(args[2]), val<uint32_t>(args[3]) ); }, { { "w", var(uint32_t()) }, { "x", var(uint32_t()) }, { "y", var(uint32_t()) }, { "z", var(uint32_t()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::uvec4>(ref)) mud::uvec4(val<mud::uvec4>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::uvec4::x), type<uint32_t>(), "x", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::uvec4::y), type<uint32_t>(), "y", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::uvec4::z), type<uint32_t>(), "z", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::uvec4::w), type<uint32_t>(), "w", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_string<mud::uvec4>();
		meta_class<mud::uvec4>();
	}
	// mud::vec2
	{
		Type& t = type<mud::vec2>();
		static Meta meta = { t, &namspc({ "mud" }), "vec2", sizeof(mud::vec2), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::vec2>(ref)) mud::vec2(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::vec2>(ref)) mud::vec2( val<float>(args[0]) ); }, { { "a", var(float()) } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::vec2>(ref)) mud::vec2( val<float>(args[0]), val<float>(args[1]) ); }, { { "x", var(float()) }, { "y", var(float()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::vec2>(ref)) mud::vec2(val<mud::vec2>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::vec2::x), type<float>(), "x", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::vec2::y), type<float>(), "y", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_string<mud::vec2>();
		meta_class<mud::vec2>();
	}
	// mud::vec3
	{
		Type& t = type<mud::vec3>();
		static Meta meta = { t, &namspc({ "mud" }), "vec3", sizeof(mud::vec3), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::vec3>(ref)) mud::vec3(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::vec3>(ref)) mud::vec3( val<float>(args[0]) ); }, { { "a", var(float()) } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::vec3>(ref)) mud::vec3( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]) ); }, { { "x", var(float()) }, { "y", var(float()) }, { "z", var(float()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::vec3>(ref)) mud::vec3(val<mud::vec3>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::vec3::x), type<float>(), "x", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::vec3::y), type<float>(), "y", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::vec3::z), type<float>(), "z", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_string<mud::vec3>();
		meta_class<mud::vec3>();
	}
	// mud::vec4
	{
		Type& t = type<mud::vec4>();
		static Meta meta = { t, &namspc({ "mud" }), "vec4", sizeof(mud::vec4), TypeClass::Struct };
		// defaults
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<mud::vec4>(ref)) mud::vec4(  ); }, {} },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::vec4>(ref)) mud::vec4( val<float>(args[0]) ); }, { { "a", var(float()) } } },
				{ t, [](Ref ref, array<Var> args) { new(&val<mud::vec4>(ref)) mud::vec4( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]), val<float>(args[3]) ); }, { { "w", var(float()) }, { "x", var(float()) }, { "y", var(float()) }, { "z", var(float()) } } }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<mud::vec4>(ref)) mud::vec4(val<mud::vec4>(other)); } }
			},
			// members
			{
				{ t, member_address(&mud::vec4::x), type<float>(), "x", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::vec4::y), type<float>(), "y", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::vec4::z), type<float>(), "z", Ref(), Member::Value, nullptr },
				{ t, member_address(&mud::vec4::w), type<float>(), "w", Ref(), Member::Value, nullptr }
			},
			// methods
			{
			},
			// static members
			{
			}
		};
		init_string<mud::vec4>();
		meta_class<mud::vec4>();
	}
	// mud::Sprite
	{
		Type& t = type<mud::Sprite>();
		static Meta meta = { t, &namspc({ "mud" }), "Sprite", sizeof(mud::Sprite), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::Image>() },
			{ base_offset<mud::Sprite, mud::Image>() },
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
		meta_class<mud::Sprite>();
	}
	// mud::SpriteAtlas
	{
		Type& t = type<mud::SpriteAtlas>();
		static Meta meta = { t, &namspc({ "mud" }), "SpriteAtlas", sizeof(mud::SpriteAtlas), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::ImageAtlas>() },
			{ base_offset<mud::SpriteAtlas, mud::ImageAtlas>() },
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
		meta_class<mud::SpriteAtlas>();
	}
	// mud::TextureAtlas
	{
		Type& t = type<mud::TextureAtlas>();
		static Meta meta = { t, &namspc({ "mud" }), "TextureAtlas", sizeof(mud::TextureAtlas), TypeClass::Object };
		// defaults
		static Class cls = { t,
			// bases
			{ &type<mud::ImageAtlas>() },
			{ base_offset<mud::TextureAtlas, mud::ImageAtlas>() },
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
		meta_class<mud::TextureAtlas>();
	}
		m.m_types.push_back(&type<mud::AutoStat<float>>());
		m.m_types.push_back(&type<mud::AutoStat<int>>());
		m.m_types.push_back(&type<mud::Axes>());
		m.m_types.push_back(&type<mud::Axis>());
		m.m_types.push_back(&type<mud::Clockwise>());
		m.m_types.push_back(&type<mud::Colour>());
		m.m_types.push_back(&type<mud::Gauge>());
		m.m_types.push_back(&type<mud::Image>());
		m.m_types.push_back(&type<mud::Image256>());
		m.m_types.push_back(&type<mud::ImageAtlas>());
		m.m_types.push_back(&type<mud::Palette>());
		m.m_types.push_back(&type<mud::Range<float>>());
		m.m_types.push_back(&type<mud::Range<mud::Colour>>());
		m.m_types.push_back(&type<mud::Range<mud::quat>>());
		m.m_types.push_back(&type<mud::Range<mud::vec3>>());
		m.m_types.push_back(&type<mud::Range<uint32_t>>());
		m.m_types.push_back(&type<mud::Ratio>());
		m.m_types.push_back(&type<mud::Side>());
		m.m_types.push_back(&type<mud::SignedAxis>());
		m.m_types.push_back(&type<mud::Spectrum>());
		m.m_types.push_back(&type<mud::Time>());
		m.m_types.push_back(&type<mud::TimeSpan>());
		m.m_types.push_back(&type<mud::TrackMode>());
		m.m_types.push_back(&type<mud::Transform>());
		m.m_types.push_back(&type<mud::ValueCurve<float>>());
		m.m_types.push_back(&type<mud::ValueCurve<mud::Colour>>());
		m.m_types.push_back(&type<mud::ValueCurve<mud::quat>>());
		m.m_types.push_back(&type<mud::ValueCurve<mud::vec3>>());
		m.m_types.push_back(&type<mud::ValueCurve<uint32_t>>());
		m.m_types.push_back(&type<mud::ValueTrack<float>>());
		m.m_types.push_back(&type<mud::ValueTrack<mud::Colour>>());
		m.m_types.push_back(&type<mud::ValueTrack<mud::quat>>());
		m.m_types.push_back(&type<mud::ValueTrack<mud::vec3>>());
		m.m_types.push_back(&type<mud::ValueTrack<uint32_t>>());
		m.m_types.push_back(&type<mud::bvec3>());
		m.m_types.push_back(&type<mud::bvec4>());
		m.m_types.push_back(&type<mud::half2>());
		m.m_types.push_back(&type<mud::half3>());
		m.m_types.push_back(&type<mud::ivec2>());
		m.m_types.push_back(&type<mud::ivec3>());
		m.m_types.push_back(&type<mud::ivec4>());
		m.m_types.push_back(&type<mud::mat4>());
		m.m_types.push_back(&type<mud::quat>());
		m.m_types.push_back(&type<mud::uvec2>());
		m.m_types.push_back(&type<mud::uvec3>());
		m.m_types.push_back(&type<mud::uvec4>());
		m.m_types.push_back(&type<mud::vec2>());
		m.m_types.push_back(&type<mud::vec3>());
		m.m_types.push_back(&type<mud::vec4>());
		m.m_types.push_back(&type<vector<float>>());
		m.m_types.push_back(&type<vector<mud::Colour>>());
		m.m_types.push_back(&type<vector<mud::quat>>());
		m.m_types.push_back(&type<vector<mud::uvec3>>());
		m.m_types.push_back(&type<vector<mud::vec3>>());
		m.m_types.push_back(&type<vector<uint32_t>>());
		m.m_types.push_back(&type<mud::Sprite>());
		m.m_types.push_back(&type<mud::SpriteAtlas>());
		m.m_types.push_back(&type<mud::TextureAtlas>());
		{
			auto func = [](array<Var> args, Var& result) {  val<float>(result) = sinf(val<float>(args[0])); };
			vector<Param> params = { { "a", var(float()) } };
			static Function f = { &namspc({}), "sinf", funcptr<float(*)(float)>(&sinf), func, params, var(float()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<float>(result) = cosf(val<float>(args[0])); };
			vector<Param> params = { { "a", var(float()) } };
			static Function f = { &namspc({}), "cosf", funcptr<float(*)(float)>(&cosf), func, params, var(float()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<double>(result) = sin(val<double>(args[0])); };
			vector<Param> params = { { "a", var(double()) } };
			static Function f = { &namspc({}), "sin", funcptr<double(*)(double)>(&sin), func, params, var(double()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<double>(result) = cos(val<double>(args[0])); };
			vector<Param> params = { { "a", var(double()) } };
			static Function f = { &namspc({}), "cos", funcptr<double(*)(double)>(&cos), func, params, var(double()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::add<float>(val<float>(args[0]), val<float>(args[1])); };
			vector<Param> params = { { "a", var(float()) }, { "b", var(float()) } };
			static Function f = { &namspc({ "mud" }), "add<float>", funcptr<float(*)(float, float)>(&mud::add<float>), func, params, var(float()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::subtract<float>(val<float>(args[0]), val<float>(args[1])); };
			vector<Param> params = { { "a", var(float()) }, { "b", var(float()) } };
			static Function f = { &namspc({ "mud" }), "subtract<float>", funcptr<float(*)(float, float)>(&mud::subtract<float>), func, params, var(float()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::multiply<float>(val<float>(args[0]), val<float>(args[1])); };
			vector<Param> params = { { "a", var(float()) }, { "b", var(float()) } };
			static Function f = { &namspc({ "mud" }), "multiply<float>", funcptr<float(*)(float, float)>(&mud::multiply<float>), func, params, var(float()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::divide<float>(val<float>(args[0]), val<float>(args[1])); };
			vector<Param> params = { { "a", var(float()) }, { "b", var(float()) } };
			static Function f = { &namspc({ "mud" }), "divide<float>", funcptr<float(*)(float, float)>(&mud::divide<float>), func, params, var(float()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::nsinf(val<float>(args[0])); };
			vector<Param> params = { { "a", var(float()) } };
			static Function f = { &namspc({ "mud" }), "nsinf", funcptr<float(*)(float)>(&mud::nsinf), func, params, var(float()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::ncosf(val<float>(args[0])); };
			vector<Param> params = { { "a", var(float()) } };
			static Function f = { &namspc({ "mud" }), "ncosf", funcptr<float(*)(float)>(&mud::ncosf), func, params, var(float()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<double>(result) = mud::nsin(val<double>(args[0])); };
			vector<Param> params = { { "a", var(double()) } };
			static Function f = { &namspc({ "mud" }), "nsin", funcptr<double(*)(double)>(&mud::nsin), func, params, var(double()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<double>(result) = mud::ncos(val<double>(args[0])); };
			vector<Param> params = { { "a", var(double()) } };
			static Function f = { &namspc({ "mud" }), "ncos", funcptr<double(*)(double)>(&mud::ncos), func, params, var(double()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<uint32_t>(result) = mud::to_rgba(val<mud::Colour>(args[0])); };
			vector<Param> params = { { "colour", var(mud::Colour()) } };
			static Function f = { &namspc({ "mud" }), "to_rgba", funcptr<uint32_t(*)(const mud::Colour&)>(&mud::to_rgba), func, params, var(uint32_t()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<uint32_t>(result) = mud::to_abgr(val<mud::Colour>(args[0])); };
			vector<Param> params = { { "colour", var(mud::Colour()) } };
			static Function f = { &namspc({ "mud" }), "to_abgr", funcptr<uint32_t(*)(const mud::Colour&)>(&mud::to_abgr), func, params, var(uint32_t()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::from_rgba(val<uint32_t>(args[0])); };
			vector<Param> params = { { "colour", var(uint32_t()) } };
			static Function f = { &namspc({ "mud" }), "from_rgba", funcptr<mud::Colour(*)(uint32_t)>(&mud::from_rgba), func, params, var(mud::Colour()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::from_abgr(val<uint32_t>(args[0])); };
			vector<Param> params = { { "colour", var(uint32_t()) } };
			static Function f = { &namspc({ "mud" }), "from_abgr", funcptr<mud::Colour(*)(uint32_t)>(&mud::from_abgr), func, params, var(mud::Colour()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::to_linear(val<mud::Colour>(args[0])); };
			vector<Param> params = { { "colour", var(mud::Colour()) } };
			static Function f = { &namspc({ "mud" }), "to_linear", funcptr<mud::Colour(*)(const mud::Colour&)>(&mud::to_linear), func, params, var(mud::Colour()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::to_gamma(val<mud::Colour>(args[0])); };
			vector<Param> params = { { "colour", var(mud::Colour()) } };
			static Function f = { &namspc({ "mud" }), "to_gamma", funcptr<mud::Colour(*)(const mud::Colour&)>(&mud::to_gamma), func, params, var(mud::Colour()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::to_srgb(val<mud::Colour>(args[0])); };
			vector<Param> params = { { "colour", var(mud::Colour()) } };
			static Function f = { &namspc({ "mud" }), "to_srgb", funcptr<mud::Colour(*)(const mud::Colour&)>(&mud::to_srgb), func, params, var(mud::Colour()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::hsl_to_rgb(val<float>(args[0]), val<float>(args[1]), val<float>(args[2])); };
			vector<Param> params = { { "h", var(float()) }, { "s", var(float()) }, { "l", var(float()) } };
			static Function f = { &namspc({ "mud" }), "hsl_to_rgb", funcptr<mud::Colour(*)(float, float, float)>(&mud::hsl_to_rgb), func, params, var(mud::Colour()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::rgb_to_hsl(val<float>(args[0]), val<float>(args[1]), val<float>(args[2])); };
			vector<Param> params = { { "r", var(float()) }, { "g", var(float()) }, { "b", var(float()) } };
			static Function f = { &namspc({ "mud" }), "rgb_to_hsl", funcptr<mud::Colour(*)(float, float, float)>(&mud::rgb_to_hsl), func, params, var(mud::Colour()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::rgba_to_hsla(val<mud::Colour>(args[0])); };
			vector<Param> params = { { "colour", var(mud::Colour()) } };
			static Function f = { &namspc({ "mud" }), "rgba_to_hsla", funcptr<mud::Colour(*)(const mud::Colour&)>(&mud::rgba_to_hsla), func, params, var(mud::Colour()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::hsla_to_rgba(val<mud::Colour>(args[0])); };
			vector<Param> params = { { "colour", var(mud::Colour()) } };
			static Function f = { &namspc({ "mud" }), "hsla_to_rgba", funcptr<mud::Colour(*)(const mud::Colour&)>(&mud::hsla_to_rgba), func, params, var(mud::Colour()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::quat>(result) = mud::look_dir(val<mud::vec3>(args[0]), val<mud::vec3>(args[1])); };
			vector<Param> params = { { "direction", var(mud::vec3()) }, { "forward", var(mud::vec3()), Param::Default } };
			static Function f = { &namspc({ "mud" }), "look_dir", funcptr<mud::quat(*)(const mud::vec3&, const mud::vec3&)>(&mud::look_dir), func, params, var(mud::quat()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::quat>(result) = mud::look_at(val<mud::vec3>(args[0]), val<mud::vec3>(args[1]), val<mud::vec3>(args[2])); };
			vector<Param> params = { { "eye", var(mud::vec3()) }, { "target", var(mud::vec3()) }, { "forward", var(mud::vec3()), Param::Default } };
			static Function f = { &namspc({ "mud" }), "look_at", funcptr<mud::quat(*)(const mud::vec3&, const mud::vec3&, const mud::vec3&)>(&mud::look_at), func, params, var(mud::quat()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::vec3>(result) = mud::add<mud::vec3>(val<mud::vec3>(args[0]), val<mud::vec3>(args[1])); };
			vector<Param> params = { { "a", var(mud::vec3()) }, { "b", var(mud::vec3()) } };
			static Function f = { &namspc({ "mud" }), "add<mud::vec3>", funcptr<mud::vec3(*)(mud::vec3, mud::vec3)>(&mud::add<mud::vec3>), func, params, var(mud::vec3()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::vec3>(result) = mud::subtract<mud::vec3>(val<mud::vec3>(args[0]), val<mud::vec3>(args[1])); };
			vector<Param> params = { { "a", var(mud::vec3()) }, { "b", var(mud::vec3()) } };
			static Function f = { &namspc({ "mud" }), "subtract<mud::vec3>", funcptr<mud::vec3(*)(mud::vec3, mud::vec3)>(&mud::subtract<mud::vec3>), func, params, var(mud::vec3()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::vec3>(result) = mud::multiply<mud::vec3>(val<mud::vec3>(args[0]), val<mud::vec3>(args[1])); };
			vector<Param> params = { { "a", var(mud::vec3()) }, { "b", var(mud::vec3()) } };
			static Function f = { &namspc({ "mud" }), "multiply<mud::vec3>", funcptr<mud::vec3(*)(mud::vec3, mud::vec3)>(&mud::multiply<mud::vec3>), func, params, var(mud::vec3()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::vec3>(result) = mud::divide<mud::vec3>(val<mud::vec3>(args[0]), val<mud::vec3>(args[1])); };
			vector<Param> params = { { "a", var(mud::vec3()) }, { "b", var(mud::vec3()) } };
			static Function f = { &namspc({ "mud" }), "divide<mud::vec3>", funcptr<mud::vec3(*)(mud::vec3, mud::vec3)>(&mud::divide<mud::vec3>), func, params, var(mud::vec3()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::grid(val<mud::uvec3>(args[0]), val<vector<mud::uvec3>>(args[1])); };
			vector<Param> params = { { "size", var(mud::uvec3()) }, { "output_coords", var(vector<mud::uvec3>()), Param::Output } };
			static Function f = { &namspc({ "mud" }), "grid", funcptr<void(*)(const mud::uvec3&, vector<mud::uvec3>&)>(&mud::grid), func, params, Var() };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) {  val<mud::vec3>(result) = mud::grid_center(val<mud::uvec3>(args[0]), val<mud::vec3>(args[1])); };
			vector<Param> params = { { "coord", var(mud::uvec3()) }, { "cell_size", var(mud::vec3()) } };
			static Function f = { &namspc({ "mud" }), "grid_center", funcptr<mud::vec3(*)(const mud::uvec3&, const mud::vec3&)>(&mud::grid_center), func, params, var(mud::vec3()) };
			m.m_functions.push_back(&f);
		}
		{
			auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::index_list(val<uint32_t>(args[0]), val<vector<uint32_t>>(args[1])); };
			vector<Param> params = { { "size", var(uint32_t()) }, { "output_indices", var(vector<uint32_t>()), Param::Output } };
			static Function f = { &namspc({ "mud" }), "index_list", funcptr<void(*)(uint32_t, vector<uint32_t>&)>(&mud::index_list), func, params, Var() };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_math::mud_math()
		: Module("mud::math", { &mud_infra::m(), &mud_type::m() })
	{
		// setup reflection meta data
		mud_math_meta(*this);
	}
}

#ifdef MUD_MATH_MODULE
extern "C"
Module& getModule()
{
		return mud_math::m();
}
#endif
