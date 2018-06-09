

#pragma once

#ifndef MUD_MODULES
#include <math/Refl/Module.h>

#include <obj/Any.h>
#include <obj/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mudmath_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<mud::Axes>(), &namspc({ "mud" }), "Axes", sizeof(mud::Axes), TypeClass::Enum };
        static Enum enu = { type<mud::Axes>(),
            true,
            { "None", "X", "Y", "Z" },
            { 0, 1, 2, 4 },
            { var(Axes::None), var(Axes::X), var(Axes::Y), var(Axes::Z) }
        };
        meta_enum<mud::Axes>();
    }
    
    {
        static Meta meta = { type<mud::Axis>(), &namspc({ "mud" }), "Axis", sizeof(mud::Axis), TypeClass::Enum };
        static Enum enu = { type<mud::Axis>(),
            true,
            { "X", "Y", "Z" },
            { 0, 1, 2 },
            { var(Axis::X), var(Axis::Y), var(Axis::Z) }
        };
        meta_enum<mud::Axis>();
    }
    
    {
        static Meta meta = { type<mud::Clockwise>(), &namspc({ "mud" }), "Clockwise", sizeof(mud::Clockwise), TypeClass::Enum };
        static Enum enu = { type<mud::Clockwise>(),
            false,
            { "CLOCKWISE", "ANTI_CLOCKWISE" },
            { 0, 1 },
            { var(mud::CLOCKWISE), var(mud::ANTI_CLOCKWISE) }
        };
        meta_enum<mud::Clockwise>();
    }
    
    {
        static Meta meta = { type<mud::Side>(), &namspc({ "mud" }), "Side", sizeof(mud::Side), TypeClass::Enum };
        static Enum enu = { type<mud::Side>(),
            true,
            { "Right", "Left", "Up", "Down", "Back", "Front" },
            { 0, 1, 2, 3, 4, 5 },
            { var(Side::Right), var(Side::Left), var(Side::Up), var(Side::Down), var(Side::Back), var(Side::Front) }
        };
        meta_enum<mud::Side>();
    }
    
    {
        static Meta meta = { type<mud::SignedAxis>(), &namspc({ "mud" }), "SignedAxis", sizeof(mud::SignedAxis), TypeClass::Enum };
        static Enum enu = { type<mud::SignedAxis>(),
            true,
            { "PlusX", "MinusX", "PlusY", "MinusY", "PlusZ", "MinusZ" },
            { 0, 1, 2, 3, 4, 5 },
            { var(SignedAxis::PlusX), var(SignedAxis::MinusX), var(SignedAxis::PlusY), var(SignedAxis::MinusY), var(SignedAxis::PlusZ), var(SignedAxis::MinusZ) }
        };
        meta_enum<mud::SignedAxis>();
    }
    
    {
        static Meta meta = { type<mud::SpectrumPalette>(), &namspc({ "mud" }), "SpectrumPalette", sizeof(mud::SpectrumPalette), TypeClass::Enum };
        static Enum enu = { type<mud::SpectrumPalette>(),
            false,
            { "SPECTRUM_GRAYSCALE", "SPECTRUM_HUE" },
            { 0, 1 },
            { var(mud::SPECTRUM_GRAYSCALE), var(mud::SPECTRUM_HUE) }
        };
        meta_enum<mud::SpectrumPalette>();
    }
    
    {
        static Meta meta = { type<mud::TrackMode>(), &namspc({ "mud" }), "TrackMode", sizeof(mud::TrackMode), TypeClass::Enum };
        static Enum enu = { type<mud::TrackMode>(),
            true,
            { "Constant", "ConstantRandom", "Curve", "CurveRandom" },
            { 0, 1, 2, 3 },
            { var(TrackMode::Constant), var(TrackMode::ConstantRandom), var(TrackMode::Curve), var(TrackMode::CurveRandom) }
        };
        meta_enum<mud::TrackMode>();
    }
    
    
    // Sequences
    {
        static Meta meta = { type<std::vector<float>>(), &namspc({}), "std::vector<float>", sizeof(std::vector<float>), TypeClass::Sequence };
        static Class cls = { type<std::vector<float>>() };
        cls.m_content = &type<float>();
        meta_sequence<std::vector<float>, float>();
    }
    
    {
        static Meta meta = { type<std::vector<mud::Colour>>(), &namspc({}), "std::vector<mud::Colour>", sizeof(std::vector<mud::Colour>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::Colour>>() };
        cls.m_content = &type<mud::Colour>();
        meta_sequence<std::vector<mud::Colour>, mud::Colour>();
    }
    
    {
        static Meta meta = { type<std::vector<mud::Colour>>(), &namspc({}), "std::vector<mud::Colour>", sizeof(std::vector<mud::Colour>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::Colour>>() };
        cls.m_content = &type<mud::Colour>();
        meta_sequence<std::vector<mud::Colour>, mud::Colour>();
    }
    
    {
        static Meta meta = { type<std::vector<mud::quat>>(), &namspc({}), "std::vector<mud::quat>", sizeof(std::vector<mud::quat>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::quat>>() };
        cls.m_content = &type<mud::quat>();
        meta_sequence<std::vector<mud::quat>, mud::quat>();
    }
    
    {
        static Meta meta = { type<std::vector<mud::uvec3>>(), &namspc({}), "std::vector<mud::uvec3>", sizeof(std::vector<mud::uvec3>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::uvec3>>() };
        cls.m_content = &type<mud::uvec3>();
        meta_sequence<std::vector<mud::uvec3>, mud::uvec3>();
    }
    
    {
        static Meta meta = { type<std::vector<mud::vec3>>(), &namspc({}), "std::vector<mud::vec3>", sizeof(std::vector<mud::vec3>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::vec3>>() };
        cls.m_content = &type<mud::vec3>();
        meta_sequence<std::vector<mud::vec3>, mud::vec3>();
    }
    
    {
        static Meta meta = { type<std::vector<uint32_t>>(), &namspc({}), "std::vector<uint32_t>", sizeof(std::vector<uint32_t>), TypeClass::Sequence };
        static Class cls = { type<std::vector<uint32_t>>() };
        cls.m_content = &type<uint32_t>();
        meta_sequence<std::vector<uint32_t>, uint32_t>();
    }
    
    
    
    
    
    
        
    // mud::AutoStat<float>
    {
        static Meta meta = { type<mud::AutoStat<float>>(), &namspc({ "mud" }), "AutoStat<float>", sizeof(mud::AutoStat<float>), TypeClass::Object };
        static Class cls = { type<mud::AutoStat<float>>(),
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
        static Meta meta = { type<mud::AutoStat<int>>(), &namspc({ "mud" }), "AutoStat<int>", sizeof(mud::AutoStat<int>), TypeClass::Object };
        static Class cls = { type<mud::AutoStat<int>>(),
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
        static Meta meta = { type<mud::Colour>(), &namspc({ "mud" }), "Colour", sizeof(mud::Colour), TypeClass::Struct };
        static Class cls = { type<mud::Colour>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Colour>(), [](Ref ref, array<Var> args) { new(&val<mud::Colour>(ref)) mud::Colour( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]), val<float>(args[3]) ); }, { { "r", var(float(0.f)), Param::Default }, { "g", var(float(0.f)), Param::Default }, { "b", var(float(0.f)), Param::Default }, { "a", var(float(1.f)), Param::Default } } }
            },
            // copy constructor
            {
                { type<mud::Colour>(), [](Ref ref, Ref other) { new(&val<mud::Colour>(ref)) mud::Colour(val<mud::Colour>(other)); } }
            },
            // members
            {
                { type<mud::Colour>(), member_address(&mud::Colour::m_r), type<float>(), "r", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Colour>(), member_address(&mud::Colour::m_g), type<float>(), "g", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Colour>(), member_address(&mud::Colour::m_b), type<float>(), "b", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Colour>(), member_address(&mud::Colour::m_a), type<float>(), "a", var(float()), Member::Flags(Member::Value|Member::Mutable) }
            },
            // methods
            {
            },
            // static members
            {
                { type<mud::Colour>(), "Black", Ref(&mud::Colour::Black) },
                { type<mud::Colour>(), "AlphaBlack", Ref(&mud::Colour::AlphaBlack) },
                { type<mud::Colour>(), "Red", Ref(&mud::Colour::Red) },
                { type<mud::Colour>(), "Green", Ref(&mud::Colour::Green) },
                { type<mud::Colour>(), "NeonGreen", Ref(&mud::Colour::NeonGreen) },
                { type<mud::Colour>(), "Blue", Ref(&mud::Colour::Blue) },
                { type<mud::Colour>(), "Pink", Ref(&mud::Colour::Pink) },
                { type<mud::Colour>(), "Cyan", Ref(&mud::Colour::Cyan) },
                { type<mud::Colour>(), "Yellow", Ref(&mud::Colour::Yellow) },
                { type<mud::Colour>(), "White", Ref(&mud::Colour::White) },
                { type<mud::Colour>(), "AlphaWhite", Ref(&mud::Colour::AlphaWhite) },
                { type<mud::Colour>(), "LightGrey", Ref(&mud::Colour::LightGrey) },
                { type<mud::Colour>(), "MidGrey", Ref(&mud::Colour::MidGrey) },
                { type<mud::Colour>(), "DarkGrey", Ref(&mud::Colour::DarkGrey) },
                { type<mud::Colour>(), "AlphaGrey", Ref(&mud::Colour::AlphaGrey) },
                { type<mud::Colour>(), "Transparent", Ref(&mud::Colour::Transparent) },
                { type<mud::Colour>(), "Invisible", Ref(&mud::Colour::Invisible) },
                { type<mud::Colour>(), "None", Ref(&mud::Colour::None) }
            }
        };
        
        
        
        init_string<mud::Colour>(); 
        meta_class<mud::Colour>();
    }
    
    
    
        
    // mud::Gauge
    {
        static Meta meta = { type<mud::Gauge>(), &namspc({ "mud" }), "Gauge", sizeof(mud::Gauge), TypeClass::Struct };
        static Class cls = { type<mud::Gauge>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Gauge>(), [](Ref ref, array<Var> args) { new(&val<mud::Gauge>(ref)) mud::Gauge( val<float>(args[0]) ); }, { { "value", var(float(0.f)), Param::Default } } }
            },
            // copy constructor
            {
                { type<mud::Gauge>(), [](Ref ref, Ref other) { new(&val<mud::Gauge>(ref)) mud::Gauge(val<mud::Gauge>(other)); } }
            },
            // members
            {
                { type<mud::Gauge>(), member_address(&mud::Gauge::value), type<float>(), "value", var(float()), Member::Flags(Member::Value|Member::Mutable) }
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
    
    
    
        
    // mud::Image256
    {
        static Meta meta = { type<mud::Image256>(), &namspc({ "mud" }), "Image256", sizeof(mud::Image256), TypeClass::Struct };
        static Class cls = { type<mud::Image256>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Image256>(), [](Ref ref, array<Var> args) { new(&val<mud::Image256>(ref)) mud::Image256( val<uint16_t>(args[0]), val<uint16_t>(args[1]), val<mud::Palette>(args[2]) ); }, { { "width", var(uint16_t()), Param::Default }, { "height", var(uint16_t()), Param::Default }, { "palette", var(mud::Palette()), Param::Default } } }
            },
            // copy constructor
            {
                { type<mud::Image256>(), [](Ref ref, Ref other) { new(&val<mud::Image256>(ref)) mud::Image256(val<mud::Image256>(other)); } }
            },
            // members
            {
                { type<mud::Image256>(), member_address(&mud::Image256::m_pixels), type<std::vector<uint32_t>>(), "pixels", var(std::vector<uint32_t>()), Member::Value },
                { type<mud::Image256>(), member_address(&mud::Image256::m_width), type<uint16_t>(), "width", var(uint16_t()), Member::Value },
                { type<mud::Image256>(), member_address(&mud::Image256::m_height), type<uint16_t>(), "height", var(uint16_t()), Member::Value },
                { type<mud::Image256>(), member_address(&mud::Image256::m_palette), type<mud::Palette>(), "palette", var(mud::Palette()), Member::Value }
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
    
    
    
        
    // mud::Palette
    {
        static Meta meta = { type<mud::Palette>(), &namspc({ "mud" }), "Palette", sizeof(mud::Palette), TypeClass::Struct };
        static Class cls = { type<mud::Palette>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Palette>(), [](Ref ref, array<Var> args) { new(&val<mud::Palette>(ref)) mud::Palette( val<mud::SpectrumPalette>(args[0]), val<size_t>(args[1]) ); }, { { "spectrum", var(mud::SpectrumPalette()) }, { "steps", var(size_t()) } } },
                { type<mud::Palette>(), [](Ref ref, array<Var> args) { new(&val<mud::Palette>(ref)) mud::Palette( val<std::vector<mud::Colour>>(args[0]) ); }, { { "colours", var(std::vector<mud::Colour>()) } } },
                { type<mud::Palette>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::Palette>(ref)) mud::Palette(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Palette>(), [](Ref ref, Ref other) { new(&val<mud::Palette>(ref)) mud::Palette(val<mud::Palette>(other)); } }
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
        static Meta meta = { type<mud::Range<float>>(), &namspc({ "mud" }), "Range<float>", sizeof(mud::Range<float>), TypeClass::Struct };
        static Class cls = { type<mud::Range<float>>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Range<float>>(), [](Ref ref, Ref other) { new(&val<mud::Range<float>>(ref)) mud::Range<float>(val<mud::Range<float>>(other)); } }
            },
            // members
            {
                { type<mud::Range<float>>(), member_address(&mud::Range<float>::m_min), type<float>(), "min", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Range<float>>(), member_address(&mud::Range<float>::m_max), type<float>(), "max", var(float()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::Range<mud::Colour>>(), &namspc({ "mud" }), "Range<mud::Colour>", sizeof(mud::Range<mud::Colour>), TypeClass::Struct };
        static Class cls = { type<mud::Range<mud::Colour>>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Range<mud::Colour>>(), [](Ref ref, Ref other) { new(&val<mud::Range<mud::Colour>>(ref)) mud::Range<mud::Colour>(val<mud::Range<mud::Colour>>(other)); } }
            },
            // members
            {
                { type<mud::Range<mud::Colour>>(), member_address(&mud::Range<mud::Colour>::m_min), type<mud::Colour>(), "min", var(mud::Colour()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Range<mud::Colour>>(), member_address(&mud::Range<mud::Colour>::m_max), type<mud::Colour>(), "max", var(mud::Colour()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::Range<mud::quat>>(), &namspc({ "mud" }), "Range<mud::quat>", sizeof(mud::Range<mud::quat>), TypeClass::Struct };
        static Class cls = { type<mud::Range<mud::quat>>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Range<mud::quat>>(), [](Ref ref, Ref other) { new(&val<mud::Range<mud::quat>>(ref)) mud::Range<mud::quat>(val<mud::Range<mud::quat>>(other)); } }
            },
            // members
            {
                { type<mud::Range<mud::quat>>(), member_address(&mud::Range<mud::quat>::m_min), type<mud::quat>(), "min", var(mud::quat()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Range<mud::quat>>(), member_address(&mud::Range<mud::quat>::m_max), type<mud::quat>(), "max", var(mud::quat()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::Range<mud::vec3>>(), &namspc({ "mud" }), "Range<mud::vec3>", sizeof(mud::Range<mud::vec3>), TypeClass::Struct };
        static Class cls = { type<mud::Range<mud::vec3>>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Range<mud::vec3>>(), [](Ref ref, Ref other) { new(&val<mud::Range<mud::vec3>>(ref)) mud::Range<mud::vec3>(val<mud::Range<mud::vec3>>(other)); } }
            },
            // members
            {
                { type<mud::Range<mud::vec3>>(), member_address(&mud::Range<mud::vec3>::m_min), type<mud::vec3>(), "min", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Range<mud::vec3>>(), member_address(&mud::Range<mud::vec3>::m_max), type<mud::vec3>(), "max", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::Range<uint32_t>>(), &namspc({ "mud" }), "Range<uint32_t>", sizeof(mud::Range<uint32_t>), TypeClass::Struct };
        static Class cls = { type<mud::Range<uint32_t>>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Range<uint32_t>>(), [](Ref ref, Ref other) { new(&val<mud::Range<uint32_t>>(ref)) mud::Range<uint32_t>(val<mud::Range<uint32_t>>(other)); } }
            },
            // members
            {
                { type<mud::Range<uint32_t>>(), member_address(&mud::Range<uint32_t>::m_min), type<uint32_t>(), "min", var(uint32_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::Range<uint32_t>>(), member_address(&mud::Range<uint32_t>::m_max), type<uint32_t>(), "max", var(uint32_t()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::Ratio>(), &namspc({ "mud" }), "Ratio", sizeof(mud::Ratio), TypeClass::Struct };
        static Class cls = { type<mud::Ratio>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Ratio>(), [](Ref ref, array<Var> args) { new(&val<mud::Ratio>(ref)) mud::Ratio( val<float>(args[0]) ); }, { { "value", var(float(0.f)), Param::Default } } }
            },
            // copy constructor
            {
                { type<mud::Ratio>(), [](Ref ref, Ref other) { new(&val<mud::Ratio>(ref)) mud::Ratio(val<mud::Ratio>(other)); } }
            },
            // members
            {
                { type<mud::Ratio>(), member_address(&mud::Ratio::value), type<float>(), "value", var(float()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::Time>(), &namspc({ "mud" }), "Time", sizeof(mud::Time), TypeClass::Struct };
        static Class cls = { type<mud::Time>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Time>(), [](Ref ref, array<Var> args) { new(&val<mud::Time>(ref)) mud::Time( val<double>(args[0]) ); }, { { "value", var(double()) } } }
            },
            // copy constructor
            {
                { type<mud::Time>(), [](Ref ref, Ref other) { new(&val<mud::Time>(ref)) mud::Time(val<mud::Time>(other)); } }
            },
            // members
            {
                { type<mud::Time>(), member_address(&mud::Time::m_value), type<double>(), "value", var(double()), Member::Value }
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
        static Meta meta = { type<mud::TimeSpan>(), &namspc({ "mud" }), "TimeSpan", sizeof(mud::TimeSpan), TypeClass::Struct };
        static Class cls = { type<mud::TimeSpan>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::TimeSpan>(), [](Ref ref, array<Var> args) { new(&val<mud::TimeSpan>(ref)) mud::TimeSpan( val<mud::Time>(args[0]), val<mud::Time>(args[1]) ); }, { { "s", var(mud::Time()) }, { "e", var(mud::Time()) } } }
            },
            // copy constructor
            {
                { type<mud::TimeSpan>(), [](Ref ref, Ref other) { new(&val<mud::TimeSpan>(ref)) mud::TimeSpan(val<mud::TimeSpan>(other)); } }
            },
            // members
            {
                { type<mud::TimeSpan>(), member_address(&mud::TimeSpan::start), type<mud::Time>(), "start", var(mud::Time()), Member::Value },
                { type<mud::TimeSpan>(), member_address(&mud::TimeSpan::end), type<mud::Time>(), "end", var(mud::Time()), Member::Value }
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
    
    
        
    // mud::ValueCurve<float>
    {
        static Meta meta = { type<mud::ValueCurve<float>>(), &namspc({ "mud" }), "ValueCurve<float>", sizeof(mud::ValueCurve<float>), TypeClass::Struct };
        static Class cls = { type<mud::ValueCurve<float>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueCurve<float>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueCurve<float>>(ref)) mud::ValueCurve<float>(  ); }, {} },
                { type<mud::ValueCurve<float>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<float>>(ref)) mud::ValueCurve<float>( val<std::vector<float>>(args[0]) ); }, { { "keys", var(std::vector<float>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueCurve<float>>(), [](Ref ref, Ref other) { new(&val<mud::ValueCurve<float>>(ref)) mud::ValueCurve<float>(val<mud::ValueCurve<float>>(other)); } }
            },
            // members
            {
                { type<mud::ValueCurve<float>>(), member_address(&mud::ValueCurve<float>::m_keys), type<std::vector<float>>(), "keys", var(std::vector<float>()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::ValueCurve<mud::Colour>>(), &namspc({ "mud" }), "ValueCurve<mud::Colour>", sizeof(mud::ValueCurve<mud::Colour>), TypeClass::Struct };
        static Class cls = { type<mud::ValueCurve<mud::Colour>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueCurve<mud::Colour>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueCurve<mud::Colour>>(ref)) mud::ValueCurve<mud::Colour>(  ); }, {} },
                { type<mud::ValueCurve<mud::Colour>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<mud::Colour>>(ref)) mud::ValueCurve<mud::Colour>( val<std::vector<mud::Colour>>(args[0]) ); }, { { "keys", var(std::vector<mud::Colour>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueCurve<mud::Colour>>(), [](Ref ref, Ref other) { new(&val<mud::ValueCurve<mud::Colour>>(ref)) mud::ValueCurve<mud::Colour>(val<mud::ValueCurve<mud::Colour>>(other)); } }
            },
            // members
            {
                { type<mud::ValueCurve<mud::Colour>>(), member_address(&mud::ValueCurve<mud::Colour>::m_keys), type<std::vector<mud::Colour>>(), "keys", var(std::vector<mud::Colour>()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::ValueCurve<mud::quat>>(), &namspc({ "mud" }), "ValueCurve<mud::quat>", sizeof(mud::ValueCurve<mud::quat>), TypeClass::Struct };
        static Class cls = { type<mud::ValueCurve<mud::quat>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueCurve<mud::quat>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueCurve<mud::quat>>(ref)) mud::ValueCurve<mud::quat>(  ); }, {} },
                { type<mud::ValueCurve<mud::quat>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<mud::quat>>(ref)) mud::ValueCurve<mud::quat>( val<std::vector<mud::quat>>(args[0]) ); }, { { "keys", var(std::vector<mud::quat>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueCurve<mud::quat>>(), [](Ref ref, Ref other) { new(&val<mud::ValueCurve<mud::quat>>(ref)) mud::ValueCurve<mud::quat>(val<mud::ValueCurve<mud::quat>>(other)); } }
            },
            // members
            {
                { type<mud::ValueCurve<mud::quat>>(), member_address(&mud::ValueCurve<mud::quat>::m_keys), type<std::vector<mud::quat>>(), "keys", var(std::vector<mud::quat>()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::ValueCurve<mud::vec3>>(), &namspc({ "mud" }), "ValueCurve<mud::vec3>", sizeof(mud::ValueCurve<mud::vec3>), TypeClass::Struct };
        static Class cls = { type<mud::ValueCurve<mud::vec3>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueCurve<mud::vec3>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueCurve<mud::vec3>>(ref)) mud::ValueCurve<mud::vec3>(  ); }, {} },
                { type<mud::ValueCurve<mud::vec3>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<mud::vec3>>(ref)) mud::ValueCurve<mud::vec3>( val<std::vector<mud::vec3>>(args[0]) ); }, { { "keys", var(std::vector<mud::vec3>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueCurve<mud::vec3>>(), [](Ref ref, Ref other) { new(&val<mud::ValueCurve<mud::vec3>>(ref)) mud::ValueCurve<mud::vec3>(val<mud::ValueCurve<mud::vec3>>(other)); } }
            },
            // members
            {
                { type<mud::ValueCurve<mud::vec3>>(), member_address(&mud::ValueCurve<mud::vec3>::m_keys), type<std::vector<mud::vec3>>(), "keys", var(std::vector<mud::vec3>()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::ValueCurve<uint32_t>>(), &namspc({ "mud" }), "ValueCurve<uint32_t>", sizeof(mud::ValueCurve<uint32_t>), TypeClass::Struct };
        static Class cls = { type<mud::ValueCurve<uint32_t>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueCurve<uint32_t>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueCurve<uint32_t>>(ref)) mud::ValueCurve<uint32_t>(  ); }, {} },
                { type<mud::ValueCurve<uint32_t>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueCurve<uint32_t>>(ref)) mud::ValueCurve<uint32_t>( val<std::vector<uint32_t>>(args[0]) ); }, { { "keys", var(std::vector<uint32_t>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueCurve<uint32_t>>(), [](Ref ref, Ref other) { new(&val<mud::ValueCurve<uint32_t>>(ref)) mud::ValueCurve<uint32_t>(val<mud::ValueCurve<uint32_t>>(other)); } }
            },
            // members
            {
                { type<mud::ValueCurve<uint32_t>>(), member_address(&mud::ValueCurve<uint32_t>::m_keys), type<std::vector<uint32_t>>(), "keys", var(std::vector<uint32_t>()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::ValueTrack<float>>(), &namspc({ "mud" }), "ValueTrack<float>", sizeof(mud::ValueTrack<float>), TypeClass::Struct };
        static Class cls = { type<mud::ValueTrack<float>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueTrack<float>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueTrack<float>>(ref)) mud::ValueTrack<float>(  ); }, {} },
                { type<mud::ValueTrack<float>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<float>>(ref)) mud::ValueTrack<float>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<float>>(args[1]), val<mud::ValueCurve<float>>(args[2]), val<mud::ValueCurve<float>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<float>()) }, { "min_curve", var(mud::ValueCurve<float>()) }, { "max_curve", var(mud::ValueCurve<float>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueTrack<float>>(), [](Ref ref, Ref other) { new(&val<mud::ValueTrack<float>>(ref)) mud::ValueTrack<float>(val<mud::ValueTrack<float>>(other)); } }
            },
            // members
            {
                { type<mud::ValueTrack<float>>(), member_address(&mud::ValueTrack<float>::m_mode), type<mud::TrackMode>(), "mode", var(mud::TrackMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<float>>(), member_address(&mud::ValueTrack<float>::m_curve), type<mud::ValueCurve<float>>(), "curve", var(mud::ValueCurve<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<float>>(), member_address(&mud::ValueTrack<float>::m_min_curve), type<mud::ValueCurve<float>>(), "min_curve", var(mud::ValueCurve<float>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<float>>(), member_address(&mud::ValueTrack<float>::m_max_curve), type<mud::ValueCurve<float>>(), "max_curve", var(mud::ValueCurve<float>()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::ValueTrack<mud::Colour>>(), &namspc({ "mud" }), "ValueTrack<mud::Colour>", sizeof(mud::ValueTrack<mud::Colour>), TypeClass::Struct };
        static Class cls = { type<mud::ValueTrack<mud::Colour>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueTrack<mud::Colour>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueTrack<mud::Colour>>(ref)) mud::ValueTrack<mud::Colour>(  ); }, {} },
                { type<mud::ValueTrack<mud::Colour>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<mud::Colour>>(ref)) mud::ValueTrack<mud::Colour>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<mud::Colour>>(args[1]), val<mud::ValueCurve<mud::Colour>>(args[2]), val<mud::ValueCurve<mud::Colour>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<mud::Colour>()) }, { "min_curve", var(mud::ValueCurve<mud::Colour>()) }, { "max_curve", var(mud::ValueCurve<mud::Colour>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueTrack<mud::Colour>>(), [](Ref ref, Ref other) { new(&val<mud::ValueTrack<mud::Colour>>(ref)) mud::ValueTrack<mud::Colour>(val<mud::ValueTrack<mud::Colour>>(other)); } }
            },
            // members
            {
                { type<mud::ValueTrack<mud::Colour>>(), member_address(&mud::ValueTrack<mud::Colour>::m_mode), type<mud::TrackMode>(), "mode", var(mud::TrackMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::Colour>>(), member_address(&mud::ValueTrack<mud::Colour>::m_curve), type<mud::ValueCurve<mud::Colour>>(), "curve", var(mud::ValueCurve<mud::Colour>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::Colour>>(), member_address(&mud::ValueTrack<mud::Colour>::m_min_curve), type<mud::ValueCurve<mud::Colour>>(), "min_curve", var(mud::ValueCurve<mud::Colour>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::Colour>>(), member_address(&mud::ValueTrack<mud::Colour>::m_max_curve), type<mud::ValueCurve<mud::Colour>>(), "max_curve", var(mud::ValueCurve<mud::Colour>()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::ValueTrack<mud::quat>>(), &namspc({ "mud" }), "ValueTrack<mud::quat>", sizeof(mud::ValueTrack<mud::quat>), TypeClass::Struct };
        static Class cls = { type<mud::ValueTrack<mud::quat>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueTrack<mud::quat>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueTrack<mud::quat>>(ref)) mud::ValueTrack<mud::quat>(  ); }, {} },
                { type<mud::ValueTrack<mud::quat>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<mud::quat>>(ref)) mud::ValueTrack<mud::quat>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<mud::quat>>(args[1]), val<mud::ValueCurve<mud::quat>>(args[2]), val<mud::ValueCurve<mud::quat>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<mud::quat>()) }, { "min_curve", var(mud::ValueCurve<mud::quat>()) }, { "max_curve", var(mud::ValueCurve<mud::quat>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueTrack<mud::quat>>(), [](Ref ref, Ref other) { new(&val<mud::ValueTrack<mud::quat>>(ref)) mud::ValueTrack<mud::quat>(val<mud::ValueTrack<mud::quat>>(other)); } }
            },
            // members
            {
                { type<mud::ValueTrack<mud::quat>>(), member_address(&mud::ValueTrack<mud::quat>::m_mode), type<mud::TrackMode>(), "mode", var(mud::TrackMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::quat>>(), member_address(&mud::ValueTrack<mud::quat>::m_curve), type<mud::ValueCurve<mud::quat>>(), "curve", var(mud::ValueCurve<mud::quat>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::quat>>(), member_address(&mud::ValueTrack<mud::quat>::m_min_curve), type<mud::ValueCurve<mud::quat>>(), "min_curve", var(mud::ValueCurve<mud::quat>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::quat>>(), member_address(&mud::ValueTrack<mud::quat>::m_max_curve), type<mud::ValueCurve<mud::quat>>(), "max_curve", var(mud::ValueCurve<mud::quat>()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::ValueTrack<mud::vec3>>(), &namspc({ "mud" }), "ValueTrack<mud::vec3>", sizeof(mud::ValueTrack<mud::vec3>), TypeClass::Struct };
        static Class cls = { type<mud::ValueTrack<mud::vec3>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueTrack<mud::vec3>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueTrack<mud::vec3>>(ref)) mud::ValueTrack<mud::vec3>(  ); }, {} },
                { type<mud::ValueTrack<mud::vec3>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<mud::vec3>>(ref)) mud::ValueTrack<mud::vec3>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<mud::vec3>>(args[1]), val<mud::ValueCurve<mud::vec3>>(args[2]), val<mud::ValueCurve<mud::vec3>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<mud::vec3>()) }, { "min_curve", var(mud::ValueCurve<mud::vec3>()) }, { "max_curve", var(mud::ValueCurve<mud::vec3>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueTrack<mud::vec3>>(), [](Ref ref, Ref other) { new(&val<mud::ValueTrack<mud::vec3>>(ref)) mud::ValueTrack<mud::vec3>(val<mud::ValueTrack<mud::vec3>>(other)); } }
            },
            // members
            {
                { type<mud::ValueTrack<mud::vec3>>(), member_address(&mud::ValueTrack<mud::vec3>::m_mode), type<mud::TrackMode>(), "mode", var(mud::TrackMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::vec3>>(), member_address(&mud::ValueTrack<mud::vec3>::m_curve), type<mud::ValueCurve<mud::vec3>>(), "curve", var(mud::ValueCurve<mud::vec3>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::vec3>>(), member_address(&mud::ValueTrack<mud::vec3>::m_min_curve), type<mud::ValueCurve<mud::vec3>>(), "min_curve", var(mud::ValueCurve<mud::vec3>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<mud::vec3>>(), member_address(&mud::ValueTrack<mud::vec3>::m_max_curve), type<mud::ValueCurve<mud::vec3>>(), "max_curve", var(mud::ValueCurve<mud::vec3>()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::ValueTrack<uint32_t>>(), &namspc({ "mud" }), "ValueTrack<uint32_t>", sizeof(mud::ValueTrack<uint32_t>), TypeClass::Struct };
        static Class cls = { type<mud::ValueTrack<uint32_t>>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ValueTrack<uint32_t>>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ValueTrack<uint32_t>>(ref)) mud::ValueTrack<uint32_t>(  ); }, {} },
                { type<mud::ValueTrack<uint32_t>>(), [](Ref ref, array<Var> args) { new(&val<mud::ValueTrack<uint32_t>>(ref)) mud::ValueTrack<uint32_t>( val<mud::TrackMode>(args[0]), val<mud::ValueCurve<uint32_t>>(args[1]), val<mud::ValueCurve<uint32_t>>(args[2]), val<mud::ValueCurve<uint32_t>>(args[3]) ); }, { { "mode", var(mud::TrackMode()) }, { "curve", var(mud::ValueCurve<uint32_t>()) }, { "min_curve", var(mud::ValueCurve<uint32_t>()) }, { "max_curve", var(mud::ValueCurve<uint32_t>()) } } }
            },
            // copy constructor
            {
                { type<mud::ValueTrack<uint32_t>>(), [](Ref ref, Ref other) { new(&val<mud::ValueTrack<uint32_t>>(ref)) mud::ValueTrack<uint32_t>(val<mud::ValueTrack<uint32_t>>(other)); } }
            },
            // members
            {
                { type<mud::ValueTrack<uint32_t>>(), member_address(&mud::ValueTrack<uint32_t>::m_mode), type<mud::TrackMode>(), "mode", var(mud::TrackMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<uint32_t>>(), member_address(&mud::ValueTrack<uint32_t>::m_curve), type<mud::ValueCurve<uint32_t>>(), "curve", var(mud::ValueCurve<uint32_t>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<uint32_t>>(), member_address(&mud::ValueTrack<uint32_t>::m_min_curve), type<mud::ValueCurve<uint32_t>>(), "min_curve", var(mud::ValueCurve<uint32_t>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ValueTrack<uint32_t>>(), member_address(&mud::ValueTrack<uint32_t>::m_max_curve), type<mud::ValueCurve<uint32_t>>(), "max_curve", var(mud::ValueCurve<uint32_t>()), Member::Flags(Member::Value|Member::Mutable) }
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
    
    
    
    
    
        
    // mud::ivec3
    {
        static Meta meta = { type<mud::ivec3>(), &namspc({ "mud" }), "ivec3", sizeof(mud::ivec3), TypeClass::Struct };
        static Class cls = { type<mud::ivec3>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::ivec3>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::ivec3>(ref)) mud::ivec3(  ); }, {} },
                { type<mud::ivec3>(), [](Ref ref, array<Var> args) { new(&val<mud::ivec3>(ref)) mud::ivec3( val<int>(args[0]) ); }, { { "a", var(int()) } } },
                { type<mud::ivec3>(), [](Ref ref, array<Var> args) { new(&val<mud::ivec3>(ref)) mud::ivec3( val<int>(args[0]), val<int>(args[1]), val<int>(args[2]) ); }, { { "x", var(int()) }, { "y", var(int()) }, { "z", var(int()) } } }
            },
            // copy constructor
            {
                { type<mud::ivec3>(), [](Ref ref, Ref other) { new(&val<mud::ivec3>(ref)) mud::ivec3(val<mud::ivec3>(other)); } }
            },
            // members
            {
                { type<mud::ivec3>(), member_address(&mud::ivec3::x), type<int>(), "x", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ivec3>(), member_address(&mud::ivec3::y), type<int>(), "y", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::ivec3>(), member_address(&mud::ivec3::z), type<int>(), "z", var(int()), Member::Flags(Member::Value|Member::Mutable) }
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
    
    
    
        
    // mud::mat4
    {
        static Meta meta = { type<mud::mat4>(), &namspc({ "mud" }), "mat4", sizeof(mud::mat4), TypeClass::Struct };
        static Class cls = { type<mud::mat4>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::mat4>(), [](Ref ref, Ref other) { new(&val<mud::mat4>(ref)) mud::mat4(val<mud::mat4>(other)); } }
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
        static Meta meta = { type<mud::quat>(), &namspc({ "mud" }), "quat", sizeof(mud::quat), TypeClass::Struct };
        static Class cls = { type<mud::quat>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::quat>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::quat>(ref)) mud::quat(  ); }, {} },
                { type<mud::quat>(), [](Ref ref, array<Var> args) { new(&val<mud::quat>(ref)) mud::quat( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]), val<float>(args[3]) ); }, { { "w", var(float()) }, { "x", var(float()) }, { "y", var(float()) }, { "z", var(float()) } } },
                { type<mud::quat>(), [](Ref ref, array<Var> args) { new(&val<mud::quat>(ref)) mud::quat( val<mud::vec3>(args[0]) ); }, { { "euler_angles", var(mud::vec3()) } } }
            },
            // copy constructor
            {
                { type<mud::quat>(), [](Ref ref, Ref other) { new(&val<mud::quat>(ref)) mud::quat(val<mud::quat>(other)); } }
            },
            // members
            {
                { type<mud::quat>(), member_address(&mud::quat::x), type<float>(), "x", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::quat>(), member_address(&mud::quat::y), type<float>(), "y", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::quat>(), member_address(&mud::quat::z), type<float>(), "z", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::quat>(), member_address(&mud::quat::w), type<float>(), "w", var(float()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::uvec2>(), &namspc({ "mud" }), "uvec2", sizeof(mud::uvec2), TypeClass::Struct };
        static Class cls = { type<mud::uvec2>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::uvec2>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::uvec2>(ref)) mud::uvec2(  ); }, {} },
                { type<mud::uvec2>(), [](Ref ref, array<Var> args) { new(&val<mud::uvec2>(ref)) mud::uvec2( val<uint32_t>(args[0]) ); }, { { "a", var(uint32_t()) } } },
                { type<mud::uvec2>(), [](Ref ref, array<Var> args) { new(&val<mud::uvec2>(ref)) mud::uvec2( val<uint32_t>(args[0]), val<uint32_t>(args[1]) ); }, { { "x", var(uint32_t()) }, { "y", var(uint32_t()) } } }
            },
            // copy constructor
            {
                { type<mud::uvec2>(), [](Ref ref, Ref other) { new(&val<mud::uvec2>(ref)) mud::uvec2(val<mud::uvec2>(other)); } }
            },
            // members
            {
                { type<mud::uvec2>(), member_address(&mud::uvec2::x), type<uint32_t>(), "x", var(uint32_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::uvec2>(), member_address(&mud::uvec2::y), type<uint32_t>(), "y", var(uint32_t()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::uvec3>(), &namspc({ "mud" }), "uvec3", sizeof(mud::uvec3), TypeClass::Struct };
        static Class cls = { type<mud::uvec3>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::uvec3>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::uvec3>(ref)) mud::uvec3(  ); }, {} },
                { type<mud::uvec3>(), [](Ref ref, array<Var> args) { new(&val<mud::uvec3>(ref)) mud::uvec3( val<uint32_t>(args[0]) ); }, { { "a", var(uint32_t()) } } },
                { type<mud::uvec3>(), [](Ref ref, array<Var> args) { new(&val<mud::uvec3>(ref)) mud::uvec3( val<uint32_t>(args[0]), val<uint32_t>(args[1]), val<uint32_t>(args[2]) ); }, { { "x", var(uint32_t()) }, { "y", var(uint32_t()) }, { "z", var(uint32_t()) } } }
            },
            // copy constructor
            {
                { type<mud::uvec3>(), [](Ref ref, Ref other) { new(&val<mud::uvec3>(ref)) mud::uvec3(val<mud::uvec3>(other)); } }
            },
            // members
            {
                { type<mud::uvec3>(), member_address(&mud::uvec3::x), type<uint32_t>(), "x", var(uint32_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::uvec3>(), member_address(&mud::uvec3::y), type<uint32_t>(), "y", var(uint32_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::uvec3>(), member_address(&mud::uvec3::z), type<uint32_t>(), "z", var(uint32_t()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::uvec4>(), &namspc({ "mud" }), "uvec4", sizeof(mud::uvec4), TypeClass::Struct };
        static Class cls = { type<mud::uvec4>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::uvec4>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::uvec4>(ref)) mud::uvec4(  ); }, {} },
                { type<mud::uvec4>(), [](Ref ref, array<Var> args) { new(&val<mud::uvec4>(ref)) mud::uvec4( val<uint32_t>(args[0]) ); }, { { "a", var(uint32_t()) } } },
                { type<mud::uvec4>(), [](Ref ref, array<Var> args) { new(&val<mud::uvec4>(ref)) mud::uvec4( val<uint32_t>(args[0]), val<uint32_t>(args[1]), val<uint32_t>(args[2]), val<uint32_t>(args[3]) ); }, { { "w", var(uint32_t()) }, { "x", var(uint32_t()) }, { "y", var(uint32_t()) }, { "z", var(uint32_t()) } } }
            },
            // copy constructor
            {
                { type<mud::uvec4>(), [](Ref ref, Ref other) { new(&val<mud::uvec4>(ref)) mud::uvec4(val<mud::uvec4>(other)); } }
            },
            // members
            {
                { type<mud::uvec4>(), member_address(&mud::uvec4::x), type<uint32_t>(), "x", var(uint32_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::uvec4>(), member_address(&mud::uvec4::y), type<uint32_t>(), "y", var(uint32_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::uvec4>(), member_address(&mud::uvec4::z), type<uint32_t>(), "z", var(uint32_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::uvec4>(), member_address(&mud::uvec4::w), type<uint32_t>(), "w", var(uint32_t()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::vec2>(), &namspc({ "mud" }), "vec2", sizeof(mud::vec2), TypeClass::Struct };
        static Class cls = { type<mud::vec2>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::vec2>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::vec2>(ref)) mud::vec2(  ); }, {} },
                { type<mud::vec2>(), [](Ref ref, array<Var> args) { new(&val<mud::vec2>(ref)) mud::vec2( val<float>(args[0]) ); }, { { "a", var(float()) } } },
                { type<mud::vec2>(), [](Ref ref, array<Var> args) { new(&val<mud::vec2>(ref)) mud::vec2( val<float>(args[0]), val<float>(args[1]) ); }, { { "x", var(float()) }, { "y", var(float()) } } }
            },
            // copy constructor
            {
                { type<mud::vec2>(), [](Ref ref, Ref other) { new(&val<mud::vec2>(ref)) mud::vec2(val<mud::vec2>(other)); } }
            },
            // members
            {
                { type<mud::vec2>(), member_address(&mud::vec2::x), type<float>(), "x", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::vec2>(), member_address(&mud::vec2::y), type<float>(), "y", var(float()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::vec3>(), &namspc({ "mud" }), "vec3", sizeof(mud::vec3), TypeClass::Struct };
        static Class cls = { type<mud::vec3>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::vec3>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::vec3>(ref)) mud::vec3(  ); }, {} },
                { type<mud::vec3>(), [](Ref ref, array<Var> args) { new(&val<mud::vec3>(ref)) mud::vec3( val<float>(args[0]) ); }, { { "a", var(float()) } } },
                { type<mud::vec3>(), [](Ref ref, array<Var> args) { new(&val<mud::vec3>(ref)) mud::vec3( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]) ); }, { { "x", var(float()) }, { "y", var(float()) }, { "z", var(float()) } } }
            },
            // copy constructor
            {
                { type<mud::vec3>(), [](Ref ref, Ref other) { new(&val<mud::vec3>(ref)) mud::vec3(val<mud::vec3>(other)); } }
            },
            // members
            {
                { type<mud::vec3>(), member_address(&mud::vec3::x), type<float>(), "x", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::vec3>(), member_address(&mud::vec3::y), type<float>(), "y", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::vec3>(), member_address(&mud::vec3::z), type<float>(), "z", var(float()), Member::Flags(Member::Value|Member::Mutable) }
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
        static Meta meta = { type<mud::vec4>(), &namspc({ "mud" }), "vec4", sizeof(mud::vec4), TypeClass::Struct };
        static Class cls = { type<mud::vec4>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::vec4>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::vec4>(ref)) mud::vec4(  ); }, {} },
                { type<mud::vec4>(), [](Ref ref, array<Var> args) { new(&val<mud::vec4>(ref)) mud::vec4( val<float>(args[0]) ); }, { { "a", var(float()) } } },
                { type<mud::vec4>(), [](Ref ref, array<Var> args) { new(&val<mud::vec4>(ref)) mud::vec4( val<float>(args[0]), val<float>(args[1]), val<float>(args[2]), val<float>(args[3]) ); }, { { "w", var(float()) }, { "x", var(float()) }, { "y", var(float()) }, { "z", var(float()) } } }
            },
            // copy constructor
            {
                { type<mud::vec4>(), [](Ref ref, Ref other) { new(&val<mud::vec4>(ref)) mud::vec4(val<mud::vec4>(other)); } }
            },
            // members
            {
                { type<mud::vec4>(), member_address(&mud::vec4::x), type<float>(), "x", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::vec4>(), member_address(&mud::vec4::y), type<float>(), "y", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::vec4>(), member_address(&mud::vec4::z), type<float>(), "z", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<mud::vec4>(), member_address(&mud::vec4::w), type<float>(), "w", var(float()), Member::Flags(Member::Value|Member::Mutable) }
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
    

    
        m.m_types.push_back(&type<mud::AutoStat<float>>());
        m.m_types.push_back(&type<mud::AutoStat<int>>());
        m.m_types.push_back(&type<mud::Axes>());
        m.m_types.push_back(&type<mud::Axis>());
        m.m_types.push_back(&type<mud::Clockwise>());
        m.m_types.push_back(&type<mud::Colour>());
        m.m_types.push_back(&type<mud::Gauge>());
        m.m_types.push_back(&type<mud::Image256>());
        m.m_types.push_back(&type<mud::Palette>());
        m.m_types.push_back(&type<mud::Range<float>>());
        m.m_types.push_back(&type<mud::Range<mud::Colour>>());
        m.m_types.push_back(&type<mud::Range<mud::quat>>());
        m.m_types.push_back(&type<mud::Range<mud::vec3>>());
        m.m_types.push_back(&type<mud::Range<uint32_t>>());
        m.m_types.push_back(&type<mud::Ratio>());
        m.m_types.push_back(&type<mud::Side>());
        m.m_types.push_back(&type<mud::SignedAxis>());
        m.m_types.push_back(&type<mud::SpectrumPalette>());
        m.m_types.push_back(&type<mud::Time>());
        m.m_types.push_back(&type<mud::TimeSpan>());
        m.m_types.push_back(&type<mud::TrackMode>());
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
        m.m_types.push_back(&type<mud::ivec3>());
        m.m_types.push_back(&type<mud::mat4>());
        m.m_types.push_back(&type<mud::quat>());
        m.m_types.push_back(&type<std::vector<float>>());
        m.m_types.push_back(&type<std::vector<mud::Colour>>());
        m.m_types.push_back(&type<std::vector<mud::Colour>>());
        m.m_types.push_back(&type<std::vector<mud::quat>>());
        m.m_types.push_back(&type<std::vector<mud::uvec3>>());
        m.m_types.push_back(&type<std::vector<mud::vec3>>());
        m.m_types.push_back(&type<std::vector<uint32_t>>());
        m.m_types.push_back(&type<mud::uvec2>());
        m.m_types.push_back(&type<mud::uvec3>());
        m.m_types.push_back(&type<mud::uvec4>());
        m.m_types.push_back(&type<mud::vec2>());
        m.m_types.push_back(&type<mud::vec3>());
        m.m_types.push_back(&type<mud::vec4>());
    
        {
            auto func = [](array<Var> args, Var& result) {  val<float>(result) = ::sinf(val<float>(args[0])); };
            std::vector<Param> params = { { "a", var(float()) } };
            static Function f = { &namspc({}), "sinf", function_id<float(*)(float)>(&::sinf), func, params, var(float()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<float>(result) = ::cosf(val<float>(args[0])); };
            std::vector<Param> params = { { "a", var(float()) } };
            static Function f = { &namspc({}), "cosf", function_id<float(*)(float)>(&::cosf), func, params, var(float()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<double>(result) = ::sin(val<double>(args[0])); };
            std::vector<Param> params = { { "a", var(double()) } };
            static Function f = { &namspc({}), "sin", function_id<double(*)(double)>(&::sin), func, params, var(double()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<double>(result) = ::cos(val<double>(args[0])); };
            std::vector<Param> params = { { "a", var(double()) } };
            static Function f = { &namspc({}), "cos", function_id<double(*)(double)>(&::cos), func, params, var(double()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::add(val<float>(args[0]), val<float>(args[1])); };
            std::vector<Param> params = { { "a", var(float()) }, { "b", var(float()) } };
            static Function f = { &namspc({ "mud" }), "add", function_id<float(*)(float, float)>(&mud::add), func, params, var(float()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::subtract(val<float>(args[0]), val<float>(args[1])); };
            std::vector<Param> params = { { "a", var(float()) }, { "b", var(float()) } };
            static Function f = { &namspc({ "mud" }), "subtract", function_id<float(*)(float, float)>(&mud::subtract), func, params, var(float()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::multiply(val<float>(args[0]), val<float>(args[1])); };
            std::vector<Param> params = { { "a", var(float()) }, { "b", var(float()) } };
            static Function f = { &namspc({ "mud" }), "multiply", function_id<float(*)(float, float)>(&mud::multiply), func, params, var(float()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::divide(val<float>(args[0]), val<float>(args[1])); };
            std::vector<Param> params = { { "a", var(float()) }, { "b", var(float()) } };
            static Function f = { &namspc({ "mud" }), "divide", function_id<float(*)(float, float)>(&mud::divide), func, params, var(float()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::nsinf(val<float>(args[0])); };
            std::vector<Param> params = { { "a", var(float()) } };
            static Function f = { &namspc({ "mud" }), "nsinf", function_id<float(*)(float)>(&mud::nsinf), func, params, var(float()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::ncosf(val<float>(args[0])); };
            std::vector<Param> params = { { "a", var(float()) } };
            static Function f = { &namspc({ "mud" }), "ncosf", function_id<float(*)(float)>(&mud::ncosf), func, params, var(float()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<double>(result) = mud::nsin(val<double>(args[0])); };
            std::vector<Param> params = { { "a", var(double()) } };
            static Function f = { &namspc({ "mud" }), "nsin", function_id<double(*)(double)>(&mud::nsin), func, params, var(double()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<double>(result) = mud::ncos(val<double>(args[0])); };
            std::vector<Param> params = { { "a", var(double()) } };
            static Function f = { &namspc({ "mud" }), "ncos", function_id<double(*)(double)>(&mud::ncos), func, params, var(double()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<uint32_t>(result) = mud::to_rgba(val<mud::Colour>(args[0])); };
            std::vector<Param> params = { { "colour", var(mud::Colour()) } };
            static Function f = { &namspc({ "mud" }), "to_rgba", function_id<uint32_t(*)(const mud::Colour&)>(&mud::to_rgba), func, params, var(uint32_t()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<uint32_t>(result) = mud::to_abgr(val<mud::Colour>(args[0])); };
            std::vector<Param> params = { { "colour", var(mud::Colour()) } };
            static Function f = { &namspc({ "mud" }), "to_abgr", function_id<uint32_t(*)(const mud::Colour&)>(&mud::to_abgr), func, params, var(uint32_t()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::from_rgba(val<uint32_t>(args[0])); };
            std::vector<Param> params = { { "colour", var(uint32_t()) } };
            static Function f = { &namspc({ "mud" }), "from_rgba", function_id<mud::Colour(*)(uint32_t)>(&mud::from_rgba), func, params, var(mud::Colour()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::from_abgr(val<uint32_t>(args[0])); };
            std::vector<Param> params = { { "colour", var(uint32_t()) } };
            static Function f = { &namspc({ "mud" }), "from_abgr", function_id<mud::Colour(*)(uint32_t)>(&mud::from_abgr), func, params, var(mud::Colour()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::to_linear(val<mud::Colour>(args[0])); };
            std::vector<Param> params = { { "colour", var(mud::Colour()) } };
            static Function f = { &namspc({ "mud" }), "to_linear", function_id<mud::Colour(*)(const mud::Colour&)>(&mud::to_linear), func, params, var(mud::Colour()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::hsl_to_rgb(val<float>(args[0]), val<float>(args[1]), val<float>(args[2])); };
            std::vector<Param> params = { { "h", var(float()) }, { "s", var(float()) }, { "l", var(float()) } };
            static Function f = { &namspc({ "mud" }), "hsl_to_rgb", function_id<mud::Colour(*)(float, float, float)>(&mud::hsl_to_rgb), func, params, var(mud::Colour()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::rgb_to_hsl(val<float>(args[0]), val<float>(args[1]), val<float>(args[2])); };
            std::vector<Param> params = { { "r", var(float()) }, { "g", var(float()) }, { "b", var(float()) } };
            static Function f = { &namspc({ "mud" }), "rgb_to_hsl", function_id<mud::Colour(*)(float, float, float)>(&mud::rgb_to_hsl), func, params, var(mud::Colour()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::rgba_to_hsla(val<mud::Colour>(args[0])); };
            std::vector<Param> params = { { "colour", var(mud::Colour()) } };
            static Function f = { &namspc({ "mud" }), "rgba_to_hsla", function_id<mud::Colour(*)(const mud::Colour&)>(&mud::rgba_to_hsla), func, params, var(mud::Colour()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<mud::Colour>(result) = mud::hsla_to_rgba(val<mud::Colour>(args[0])); };
            std::vector<Param> params = { { "colour", var(mud::Colour()) } };
            static Function f = { &namspc({ "mud" }), "hsla_to_rgba", function_id<mud::Colour(*)(const mud::Colour&)>(&mud::hsla_to_rgba), func, params, var(mud::Colour()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<mud::vec3>(result) = mud::add(val<mud::vec3>(args[0]), val<mud::vec3>(args[1])); };
            std::vector<Param> params = { { "a", var(mud::vec3()) }, { "b", var(mud::vec3()) } };
            static Function f = { &namspc({ "mud" }), "add", function_id<mud::vec3(*)(mud::vec3, mud::vec3)>(&mud::add), func, params, var(mud::vec3()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<mud::vec3>(result) = mud::subtract(val<mud::vec3>(args[0]), val<mud::vec3>(args[1])); };
            std::vector<Param> params = { { "a", var(mud::vec3()) }, { "b", var(mud::vec3()) } };
            static Function f = { &namspc({ "mud" }), "subtract", function_id<mud::vec3(*)(mud::vec3, mud::vec3)>(&mud::subtract), func, params, var(mud::vec3()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<mud::vec3>(result) = mud::multiply(val<mud::vec3>(args[0]), val<mud::vec3>(args[1])); };
            std::vector<Param> params = { { "a", var(mud::vec3()) }, { "b", var(mud::vec3()) } };
            static Function f = { &namspc({ "mud" }), "multiply", function_id<mud::vec3(*)(mud::vec3, mud::vec3)>(&mud::multiply), func, params, var(mud::vec3()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<mud::vec3>(result) = mud::divide(val<mud::vec3>(args[0]), val<mud::vec3>(args[1])); };
            std::vector<Param> params = { { "a", var(mud::vec3()) }, { "b", var(mud::vec3()) } };
            static Function f = { &namspc({ "mud" }), "divide", function_id<mud::vec3(*)(mud::vec3, mud::vec3)>(&mud::divide), func, params, var(mud::vec3()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::grid(val<mud::uvec3>(args[0]), val<std::vector<mud::uvec3>>(args[1])); };
            std::vector<Param> params = { { "size", var(mud::uvec3()) }, { "output_coords", var(std::vector<mud::uvec3>()), Param::Output } };
            static Function f = { &namspc({ "mud" }), "grid", function_id<void(*)(mud::uvec3, std::vector<mud::uvec3>&)>(&mud::grid), func, params, Var() };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::grid_center(val<mud::uvec3>(args[0]), val<float>(args[1]), val<mud::vec3>(args[2])); };
            std::vector<Param> params = { { "coord", var(mud::uvec3()) }, { "cell_size", var(float()) }, { "output_center", var(mud::vec3()), Param::Output } };
            static Function f = { &namspc({ "mud" }), "grid_center", function_id<void(*)(mud::uvec3, float, mud::vec3&)>(&mud::grid_center), func, params, Var() };
            m.m_functions.push_back(&f);
        }
    }
}
