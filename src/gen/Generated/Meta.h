

#pragma once

#ifndef MUD_MODULES
#include <gen/Generated/Module.h>

#include <obj/Any.h>
#include <obj/Reflect/MetaDecl.h>
#include <obj/System/System.h>
#endif

namespace mud
{
    template <> MUD_GEN_EXPORT Type& type<mud::Noise::CellularDistanceFunction>();
    template <> MUD_GEN_EXPORT Type& type<mud::Noise::CellularReturnType>();
    template <> MUD_GEN_EXPORT Type& type<mud::Noise::FractalType>();
    template <> MUD_GEN_EXPORT Type& type<mud::Noise::Interp>();
    template <> MUD_GEN_EXPORT Type& type<mud::Noise::NoiseType>();
    
#ifdef MUD_GEN_REFLECTION_IMPL
    void gen_meta(Module& m)
    {   
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<mud::Noise::CellularDistanceFunction>(), &namspc({ "mud", "Noise" }), "CellularDistanceFunction", sizeof(mud::Noise::CellularDistanceFunction), TypeClass::Enum };
        static Enum enu = { type<mud::Noise::CellularDistanceFunction>(),
            false,
            { "Euclidean", "Manhattan", "Natural" },
            { 0, 1, 2 },
            { var(Noise::Euclidean), var(Noise::Manhattan), var(Noise::Natural) }
        };
        meta_enum<mud::Noise::CellularDistanceFunction>();
    }
    
    {
        static Meta meta = { type<mud::Noise::CellularReturnType>(), &namspc({ "mud", "Noise" }), "CellularReturnType", sizeof(mud::Noise::CellularReturnType), TypeClass::Enum };
        static Enum enu = { type<mud::Noise::CellularReturnType>(),
            false,
            { "CellValue", "NoiseLookup", "Distance", "Distance2", "Distance2Add", "Distance2Sub", "Distance2Mul", "Distance2Div" },
            { 0, 1, 2, 3, 4, 5, 6, 7 },
            { var(Noise::CellValue), var(Noise::NoiseLookup), var(Noise::Distance), var(Noise::Distance2), var(Noise::Distance2Add), var(Noise::Distance2Sub), var(Noise::Distance2Mul), var(Noise::Distance2Div) }
        };
        meta_enum<mud::Noise::CellularReturnType>();
    }
    
    {
        static Meta meta = { type<mud::Noise::FractalType>(), &namspc({ "mud", "Noise" }), "FractalType", sizeof(mud::Noise::FractalType), TypeClass::Enum };
        static Enum enu = { type<mud::Noise::FractalType>(),
            false,
            { "FBM", "Billow", "RigidMulti" },
            { 0, 1, 2 },
            { var(Noise::FBM), var(Noise::Billow), var(Noise::RigidMulti) }
        };
        meta_enum<mud::Noise::FractalType>();
    }
    
    {
        static Meta meta = { type<mud::Noise::Interp>(), &namspc({ "mud", "Noise" }), "Interp", sizeof(mud::Noise::Interp), TypeClass::Enum };
        static Enum enu = { type<mud::Noise::Interp>(),
            false,
            { "Linear", "Hermite", "Quintic" },
            { 0, 1, 2 },
            { var(Noise::Linear), var(Noise::Hermite), var(Noise::Quintic) }
        };
        meta_enum<mud::Noise::Interp>();
    }
    
    {
        static Meta meta = { type<mud::Noise::NoiseType>(), &namspc({ "mud", "Noise" }), "NoiseType", sizeof(mud::Noise::NoiseType), TypeClass::Enum };
        static Enum enu = { type<mud::Noise::NoiseType>(),
            false,
            { "Value", "ValueFractal", "Perlin", "PerlinFractal", "Simplex", "SimplexFractal", "Cellular", "WhiteNoise", "Cubic", "CubicFractal" },
            { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
            { var(Noise::Value), var(Noise::ValueFractal), var(Noise::Perlin), var(Noise::PerlinFractal), var(Noise::Simplex), var(Noise::SimplexFractal), var(Noise::Cellular), var(Noise::WhiteNoise), var(Noise::Cubic), var(Noise::CubicFractal) }
        };
        meta_enum<mud::Noise::NoiseType>();
    }
    
    {
        static Meta meta = { type<mud::PatternSampling>(), &namspc({ "mud" }), "PatternSampling", sizeof(mud::PatternSampling), TypeClass::Enum };
        static Enum enu = { type<mud::PatternSampling>(),
            false,
            { "PATTERN_X", "PATTERN_XY", "PATTERN_DEPTH" },
            { 0, 1, 2 },
            { var(mud::PATTERN_X), var(mud::PATTERN_XY), var(mud::PATTERN_DEPTH) }
        };
        meta_enum<mud::PatternSampling>();
    }
    
    {
        static Meta meta = { type<mud::Result>(), &namspc({ "mud" }), "Result", sizeof(mud::Result), TypeClass::Enum };
        static Enum enu = { type<mud::Result>(),
            false,
            { "kSuccess", "kFail", "kUnfinished" },
            { 0, 1, 2 },
            { var(mud::kSuccess), var(mud::kFail), var(mud::kUnfinished) }
        };
        meta_enum<mud::Result>();
    }
    
    
    // Sequences
    {
        static Meta meta = { type<std::vector<mud::Image256>>(), &namspc({}), "std::vector<mud::Image256>", sizeof(std::vector<mud::Image256>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::Image256>>() };
        cls.m_content = &type<mud::Image256>();
        meta_sequence<std::vector<mud::Image256>, mud::Image256>();
    }
    
    
    
    
        
    // mud::Circlifier
    {
        static Meta meta = { type<mud::Circlifier>(), &namspc({ "mud" }), "Circlifier", sizeof(mud::Circlifier), TypeClass::Object };
        static Class cls = { type<mud::Circlifier>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Circlifier>(), [](Ref ref, array<Var> args) { new(&val<mud::Circlifier>(ref)) mud::Circlifier( val<mud::Image256>(args[0]) ); }, { { "image", var(mud::Image256()) } } }
            },
            // copy constructor
            {
            },
            // members
            {
            },
            // methods
            {
                { type<mud::Circlifier>(), "compute", member_address(&mud::Circlifier::compute), [](Ref object, array<Var> args, Var& result) { val<std::vector<mud::Circle>>(result) = val<mud::Circlifier>(object).compute(val<mud::Colour>(args[0]), val<float>(args[1])); }, { { "colour", var(mud::Colour()) }, { "scale", var(float(1.f)), Param::Default } }, var(std::vector<mud::Circle>()) }
            },
            // static members
            {
            }
        };
        
        
        init_pool<mud::Circlifier>(); 
        
        meta_class<mud::Circlifier>();
    }
    
    
    
        
    // mud::Fract
    {
        static Meta meta = { type<mud::Fract>(), &namspc({ "mud" }), "Fract", sizeof(mud::Fract), TypeClass::Object };
        static Class cls = { type<mud::Fract>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Fract>(), [](Ref ref, array<Var> args) { new(&val<mud::Fract>(ref)) mud::Fract( val<size_t>(args[0]) ); }, { { "numTabs", var(size_t()), Param::Default } } }
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Fract>(), member_address(&mud::Fract::m_numTabs), type<size_t>(), "numTabs", var(size_t()), Member::Value }
            },
            // methods
            {
                { type<mud::Fract>(), "generate", member_address(&mud::Fract::generate), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Fract>(object).generate(val<size_t>(args[0])); }, { { "numTabs", var(size_t()), Param::Default } }, Var() },
                { type<mud::Fract>(), "regen", member_address(&mud::Fract::regen), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args);val<mud::Fract>(object).regen(); }, {}, Var() },
                { type<mud::Fract>(), "render", member_address(&mud::Fract::render), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Fract>(object).render(val<mud::Rect>(args[0]), val<mud::Pattern>(args[1]), val<uint16_t>(args[2]), val<uint16_t>(args[3]), val<mud::Image256>(args[4])); }, { { "rect", var(mud::Rect()) }, { "pattern", var(mud::Pattern()) }, { "resX", var(uint16_t()) }, { "resY", var(uint16_t()) }, { "outputImage", var(mud::Image256()), Param::Output } }, Var() },
                { type<mud::Fract>(), "renderWhole", member_address(&mud::Fract::renderWhole), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Fract>(object).renderWhole(val<mud::Pattern>(args[0]), val<uint16_t>(args[1]), val<uint16_t>(args[2]), val<mud::Image256>(args[3])); }, { { "pattern", var(mud::Pattern()) }, { "resX", var(uint16_t()) }, { "resY", var(uint16_t()) }, { "outputImage", var(mud::Image256()), Param::Output } }, Var() },
                { type<mud::Fract>(), "renderGrid", member_address(&mud::Fract::renderGrid), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Fract>(object).renderGrid(val<size_t>(args[0]), val<mud::Pattern>(args[1]), val<uint16_t>(args[2]), val<uint16_t>(args[3]), val<std::vector<mud::Image256>>(args[4])); }, { { "size", var(size_t()) }, { "pattern", var(mud::Pattern()) }, { "resX", var(uint16_t()) }, { "resY", var(uint16_t()) }, { "outputImages", var(std::vector<mud::Image256>()), Param::Output } }, Var() }
            },
            // static members
            {
            }
        };
        
        
        init_pool<mud::Fract>(); 
        
        meta_class<mud::Fract>();
    }
    
    
        
    // mud::FractSample
    {
        static Meta meta = { type<mud::FractSample>(), &namspc({ "mud" }), "FractSample", sizeof(mud::FractSample), TypeClass::Object };
        static Class cls = { type<mud::FractSample>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::FractSample>(), [](Ref ref, array<Var> args) { new(&val<mud::FractSample>(ref)) mud::FractSample( val<mud::Fract>(args[0]), val<mud::Rect>(args[1]), val<uint16_t>(args[2]), val<uint16_t>(args[3]) ); }, { { "fract", Ref(type<mud::Fract>()) }, { "rect", var(mud::Rect()) }, { "resolutionX", var(uint16_t()) }, { "resolutionY", var(uint16_t()) } } }
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::FractSample>(), Address(), type<mud::Fract>(), "fract", Ref(type<mud::Fract>()), Member::None },
                { type<mud::FractSample>(), member_address(&mud::FractSample::m_rect), type<mud::Rect>(), "rect", var(mud::Rect()), Member::Value },
                { type<mud::FractSample>(), member_address(&mud::FractSample::m_resolutionX), type<uint16_t>(), "resolutionX", var(uint16_t()), Member::Value },
                { type<mud::FractSample>(), member_address(&mud::FractSample::m_resolutionY), type<uint16_t>(), "resolutionY", var(uint16_t()), Member::Value }
            },
            // methods
            {
                { type<mud::FractSample>(), "render", member_address(&mud::FractSample::render), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::FractSample>(object).render(val<mud::Pattern>(args[0]), val<mud::Image256>(args[1])); }, { { "pattern", var(mud::Pattern()) }, { "outputImage", var(mud::Image256()), Param::Output } }, Var() }
            },
            // static members
            {
            }
        };
        
        
        init_pool<mud::FractSample>(); 
        
        meta_class<mud::FractSample>();
    }
    
    
        
    // mud::FractTab
    {
        static Meta meta = { type<mud::FractTab>(), &namspc({ "mud" }), "FractTab", sizeof(mud::FractTab), TypeClass::Struct };
        static Class cls = { type<mud::FractTab>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::FractTab>(), [](Ref ref, Ref other) { new(&val<mud::FractTab>(ref)) mud::FractTab(val<mud::FractTab>(other)); } }
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
        
        
        
        
        meta_class<mud::FractTab>();
    }
    
    
        
    // mud::Noise
    {
        static Meta meta = { type<mud::Noise>(), &namspc({ "mud" }), "Noise", sizeof(mud::Noise), TypeClass::Object };
        static Class cls = { type<mud::Noise>(),
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
        
        
        
        
        meta_class<mud::Noise>();
    }
    
    
    
        
    // mud::Pattern
    {
        static Meta meta = { type<mud::Pattern>(), &namspc({ "mud" }), "Pattern", sizeof(mud::Pattern), TypeClass::Struct };
        static Class cls = { type<mud::Pattern>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Pattern>(), [](Ref ref, array<Var> args) { new(&val<mud::Pattern>(ref)) mud::Pattern( val<mud::Palette>(args[0]), val<mud::PatternSampling>(args[1]), val<float>(args[2]), val<size_t>(args[3]) ); }, { { "palette", var(mud::Palette()) }, { "sampling", var(mud::PatternSampling()) }, { "precision", var(float(1.f)), Param::Default }, { "step", var(size_t()), Param::Default } } },
                { type<mud::Pattern>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::Pattern>(ref)) mud::Pattern(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Pattern>(), [](Ref ref, Ref other) { new(&val<mud::Pattern>(ref)) mud::Pattern(val<mud::Pattern>(other)); } }
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
        
        
        
        
        meta_class<mud::Pattern>();
    }
    
    
    
    
    
        
    // mud::Tile
    {
        static Meta meta = { type<mud::Tile>(), &namspc({ "mud" }), "Tile", sizeof(mud::Tile), TypeClass::Struct };
        static Class cls = { type<mud::Tile>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Tile>(), [](Ref ref, Ref other) { new(&val<mud::Tile>(ref)) mud::Tile(val<mud::Tile>(other)); } }
            },
            // members
            {
                { type<mud::Tile>(), member_address(&mud::Tile::m_index), type<size_t>(), "index", var(size_t()), Member::Value },
                { type<mud::Tile>(), member_address(&mud::Tile::m_name), type<std::string>(), "name", var(std::string()), Member::Value },
                { type<mud::Tile>(), member_address(&mud::Tile::m_symmetry), type<char>(), "symmetry", var(char()), Member::Value },
                { type<mud::Tile>(), member_address(&mud::Tile::m_cardinality), type<int>(), "cardinality", var(int()), Member::Value },
                { type<mud::Tile>(), member_address(&mud::Tile::m_profile), type<int>(), "profile", var(int()), Member::Value }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Tile>();
    }
    
    
        
    // mud::TileModel
    {
        static Meta meta = { type<mud::TileModel>(), &namspc({ "mud" }), "TileModel", sizeof(mud::TileModel), TypeClass::Struct };
        static Class cls = { type<mud::TileModel>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::TileModel>(), [](Ref ref, Ref other) { new(&val<mud::TileModel>(ref)) mud::TileModel(val<mud::TileModel>(other)); } }
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
        
        
        
        
        meta_class<mud::TileModel>();
    }
    
    
        
    // mud::Tileblock
    {
        static Meta meta = { type<mud::Tileblock>(), &namspc({ "mud" }), "Tileblock", sizeof(mud::Tileblock), TypeClass::Object };
        static Class cls = { type<mud::Tileblock>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Tileblock>(), [](Ref ref, array<Var> args) { new(&val<mud::Tileblock>(ref)) mud::Tileblock( val<mud::GfxSystem>(args[0]), val<mud::uvec3>(args[1]), val<mud::vec3>(args[2]), val<mud::WaveTileset>(args[3]) ); }, { { "gfx_system", Ref(type<mud::GfxSystem>()) }, { "size", var(mud::uvec3()) }, { "period", var(mud::vec3()) }, { "tileset", var(mud::WaveTileset()) } } }
            },
            // copy constructor
            {
            },
            // members
            {
                { type<mud::Tileblock>(), member_address(&mud::Tileblock::m_size), type<mud::uvec3>(), "size", var(mud::uvec3()), Member::Value },
                { type<mud::Tileblock>(), member_address(&mud::Tileblock::m_period), type<mud::vec3>(), "period", var(mud::vec3()), Member::Value },
                { type<mud::Tileblock>(), member_address(&mud::Tileblock::m_aabb), type<mud::Aabb>(), "aabb", var(mud::Aabb()), Member::Value }
            },
            // methods
            {
                { type<mud::Tileblock>(), "reset", member_address(&mud::Tileblock::reset), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args);val<mud::Tileblock>(object).reset(); }, {}, Var() },
                { type<mud::Tileblock>(), "observe", member_address(&mud::Tileblock::observe), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args);val<mud::Tileblock>(object).observe(); }, {}, Var() },
                { type<mud::Tileblock>(), "propagate", member_address(&mud::Tileblock::propagate), [](Ref object, array<Var> args, Var& result) { UNUSED(result); UNUSED(args);val<mud::Tileblock>(object).propagate(); }, {}, Var() },
                { type<mud::Tileblock>(), "solve", member_address(&mud::Tileblock::solve), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Tileblock>(object).solve(val<size_t>(args[0])); }, { { "limit", var(size_t()), Param::Default } }, Var() },
                { type<mud::Tileblock>(), "update", member_address(&mud::Tileblock::update), [](Ref object, array<Var> args, Var& result) { UNUSED(result); val<mud::Tileblock>(object).update(val<mud::Wave>(args[0])); }, { { "wave", var(mud::Wave()) } }, Var() }
            },
            // static members
            {
            }
        };
        
        
        init_pool<mud::Tileblock>(); 
        
        meta_class<mud::Tileblock>();
    }
    
    
        
    // mud::Tileset
    {
        static Meta meta = { type<mud::Tileset>(), &namspc({ "mud" }), "Tileset", sizeof(mud::Tileset), TypeClass::Struct };
        static Class cls = { type<mud::Tileset>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<mud::Tileset>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::Tileset>(ref)) mud::Tileset(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::Tileset>(), [](Ref ref, Ref other) { new(&val<mud::Tileset>(ref)) mud::Tileset(val<mud::Tileset>(other)); } }
            },
            // members
            {
                { type<mud::Tileset>(), member_address(&mud::Tileset::m_name), type<std::string>(), "name", var(std::string()), Member::Value },
                { type<mud::Tileset>(), member_address(&mud::Tileset::m_tile_size), type<mud::vec3>(), "tile_size", var(mud::vec3()), Member::Value },
                { type<mud::Tileset>(), member_address(&mud::Tileset::m_tile_scale), type<mud::vec3>(), "tile_scale", var(mud::vec3()), Member::Value },
                { type<mud::Tileset>(), member_address(&mud::Tileset::m_num_tiles), type<uint16_t>(), "nutiles", var(uint16_t()), Member::Value }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Tileset>();
    }
    
    
    
        
    // mud::Wave
    {
        static Meta meta = { type<mud::Wave>(), &namspc({ "mud" }), "Wave", sizeof(mud::Wave), TypeClass::Struct };
        static Class cls = { type<mud::Wave>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::Wave>(), [](Ref ref, Ref other) { new(&val<mud::Wave>(ref)) mud::Wave(val<mud::Wave>(other)); } }
            },
            // members
            {
            },
            // methods
            {
                { type<mud::Wave>(), "solve", member_address(&mud::Wave::solve), [](Ref object, array<Var> args, Var& result) { val<mud::Result>(result) = val<mud::Wave>(object).solve(val<size_t>(args[0])); }, { { "limit", var(size_t()) } }, var(mud::Result()) }
            },
            // static members
            {
            }
        };
        
        
        
        
        meta_class<mud::Wave>();
    }
    
    
        
    // mud::WaveTileset
    {
        static Meta meta = { type<mud::WaveTileset>(), &namspc({ "mud" }), "WaveTileset", sizeof(mud::WaveTileset), TypeClass::Struct };
        static Class cls = { type<mud::WaveTileset>(),
            // bases
            { &type<mud::Tileset>() },
            { base_offset<mud::WaveTileset, mud::Tileset>() },
            // constructors
            {
                { type<mud::WaveTileset>(), [](Ref ref, array<Var> args) { UNUSED(args);new(&val<mud::WaveTileset>(ref)) mud::WaveTileset(  ); }, {} }
            },
            // copy constructor
            {
                { type<mud::WaveTileset>(), [](Ref ref, Ref other) { new(&val<mud::WaveTileset>(ref)) mud::WaveTileset(val<mud::WaveTileset>(other)); } }
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
        
        
        
        
        meta_class<mud::WaveTileset>();
    }
    
    
        
    // mud::TileWave
    {
        static Meta meta = { type<mud::TileWave>(), &namspc({ "mud" }), "TileWave", sizeof(mud::TileWave), TypeClass::Struct };
        static Class cls = { type<mud::TileWave>(),
            // bases
            { &type<mud::Wave>() },
            { base_offset<mud::TileWave, mud::Wave>() },
            // constructors
            {
                { type<mud::TileWave>(), [](Ref ref, array<Var> args) { new(&val<mud::TileWave>(ref)) mud::TileWave( val<mud::WaveTileset>(args[0]), val<uint16_t>(args[1]), val<uint16_t>(args[2]), val<uint16_t>(args[3]), val<bool>(args[4]) ); }, { { "tileset", var(mud::WaveTileset()) }, { "width", var(uint16_t()) }, { "height", var(uint16_t()) }, { "depth", var(uint16_t()) }, { "periodic", var(bool()) } } }
            },
            // copy constructor
            {
                { type<mud::TileWave>(), [](Ref ref, Ref other) { new(&val<mud::TileWave>(ref)) mud::TileWave(val<mud::TileWave>(other)); } }
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
        
        
        
        
        meta_class<mud::TileWave>();
    }
    
    
        
    // mud::array_3d<float>
    {
        static Meta meta = { type<mud::array_3d<float>>(), &namspc({ "mud" }), "array_3d<float>", sizeof(mud::array_3d<float>), TypeClass::Struct };
        static Class cls = { type<mud::array_3d<float>>(),
            // bases
            { &type<std::vector<float>>() },
            { base_offset<mud::array_3d<float>, std::vector<float>>() },
            // constructors
            {
            },
            // copy constructor
            {
                { type<mud::array_3d<float>>(), [](Ref ref, Ref other) { new(&val<mud::array_3d<float>>(ref)) mud::array_3d<float>(val<mud::array_3d<float>>(other)); } }
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
        
        
        
        
        meta_class<mud::array_3d<float>>();
    }
    

    
        m.m_types.push_back(&type<mud::Noise::CellularDistanceFunction>());
        m.m_types.push_back(&type<mud::Noise::CellularReturnType>());
        m.m_types.push_back(&type<mud::Circlifier>());
        m.m_types.push_back(&type<mud::Fract>());
        m.m_types.push_back(&type<mud::FractSample>());
        m.m_types.push_back(&type<mud::FractTab>());
        m.m_types.push_back(&type<mud::Noise::FractalType>());
        m.m_types.push_back(&type<mud::Noise::Interp>());
        m.m_types.push_back(&type<mud::Noise>());
        m.m_types.push_back(&type<mud::Noise::NoiseType>());
        m.m_types.push_back(&type<mud::Pattern>());
        m.m_types.push_back(&type<mud::PatternSampling>());
        m.m_types.push_back(&type<mud::Result>());
        m.m_types.push_back(&type<mud::Tile>());
        m.m_types.push_back(&type<mud::TileModel>());
        m.m_types.push_back(&type<mud::Tileblock>());
        m.m_types.push_back(&type<mud::Tileset>());
        m.m_types.push_back(&type<mud::Wave>());
        m.m_types.push_back(&type<std::vector<mud::Image256>>());
        m.m_types.push_back(&type<mud::WaveTileset>());
        m.m_types.push_back(&type<mud::TileWave>());
        m.m_types.push_back(&type<mud::array_3d<float>>());
    
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::generate_fract(val<uint16_t>(args[0]), val<uint16_t>(args[1]), val<mud::Pattern>(args[2]), val<mud::Image256>(args[3])); };
            std::vector<Param> params = { { "pixelWidth", var(uint16_t()) }, { "pixelHeight", var(uint16_t()) }, { "pattern", var(mud::Pattern()) }, { "outputImage", var(mud::Image256()), Param::Output } };
            static Function f = { &namspc({ "mud" }), "generate_fract", function_id<void(*)(uint16_t, uint16_t, const mud::Pattern&, mud::Image256&)>(&mud::generate_fract), func, params, Var() };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::noise_2d(val<float>(args[0]), val<float>(args[1]), val<mud::Noise::NoiseType>(args[2]), val<float>(args[3]), val<mud::Noise::Interp>(args[4])); };
            std::vector<Param> params = { { "x", var(float()) }, { "y", var(float()) }, { "noise_type", var(mud::Noise::NoiseType()) }, { "frequency", var(float(0.01f)), Param::Default }, { "interp", var(mud::Noise::Interp()), Param::Default } };
            static Function f = { &namspc({ "mud" }), "noise_2d", function_id<float(*)(float, float, mud::Noise::NoiseType, float, mud::Noise::Interp)>(&mud::noise_2d), func, params, var(float()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::noise_3d(val<float>(args[0]), val<float>(args[1]), val<float>(args[2]), val<mud::Noise::NoiseType>(args[3]), val<float>(args[4]), val<mud::Noise::Interp>(args[5])); };
            std::vector<Param> params = { { "x", var(float()) }, { "y", var(float()) }, { "z", var(float()) }, { "noise_type", var(mud::Noise::NoiseType()) }, { "frequency", var(float(0.01f)), Param::Default }, { "interp", var(mud::Noise::Interp()), Param::Default } };
            static Function f = { &namspc({ "mud" }), "noise_3d", function_id<float(*)(float, float, float, mud::Noise::NoiseType, float, mud::Noise::Interp)>(&mud::noise_3d), func, params, var(float()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::noise_fract_2d(val<float>(args[0]), val<float>(args[1]), val<mud::Noise::NoiseType>(args[2]), val<float>(args[3]), val<mud::Noise::Interp>(args[4]), val<mud::Noise::FractalType>(args[5]), val<int>(args[6]), val<float>(args[7]), val<float>(args[8])); };
            std::vector<Param> params = { { "x", var(float()) }, { "y", var(float()) }, { "noise_type", var(mud::Noise::NoiseType()) }, { "frequency", var(float()) }, { "interp", var(mud::Noise::Interp()), Param::Default }, { "fractal_type", var(mud::Noise::FractalType()), Param::Default }, { "octaves", var(int(3)), Param::Default }, { "lacunarity", var(float(2.f)), Param::Default }, { "gain", var(float(0.5f)), Param::Default } };
            static Function f = { &namspc({ "mud" }), "noise_fract_2d", function_id<float(*)(float, float, mud::Noise::NoiseType, float, mud::Noise::Interp, mud::Noise::FractalType, int, float, float)>(&mud::noise_fract_2d), func, params, var(float()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) {  val<float>(result) = mud::noise_fract_3d(val<float>(args[0]), val<float>(args[1]), val<float>(args[2]), val<mud::Noise::NoiseType>(args[3]), val<float>(args[4]), val<mud::Noise::Interp>(args[5]), val<mud::Noise::FractalType>(args[6]), val<int>(args[7]), val<float>(args[8]), val<float>(args[9])); };
            std::vector<Param> params = { { "x", var(float()) }, { "y", var(float()) }, { "z", var(float()) }, { "noise_type", var(mud::Noise::NoiseType()) }, { "frequency", var(float()) }, { "interp", var(mud::Noise::Interp()), Param::Default }, { "fractal_type", var(mud::Noise::FractalType()), Param::Default }, { "octaves", var(int(3)), Param::Default }, { "lacunarity", var(float(2.f)), Param::Default }, { "gain", var(float(0.5f)), Param::Default } };
            static Function f = { &namspc({ "mud" }), "noise_fract_3d", function_id<float(*)(float, float, float, mud::Noise::NoiseType, float, mud::Noise::Interp, mud::Noise::FractalType, int, float, float)>(&mud::noise_fract_3d), func, params, var(float()) };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::noise_field_2d(val<mud::array_3d<float>>(args[0]), val<mud::Noise::NoiseType>(args[1]), val<float>(args[2]), val<mud::Noise::Interp>(args[3])); };
            std::vector<Param> params = { { "output_values", var(mud::array_3d<float>()), Param::Output }, { "noise_type", var(mud::Noise::NoiseType()) }, { "frequency", var(float(0.01f)), Param::Default }, { "interp", var(mud::Noise::Interp()), Param::Default } };
            static Function f = { &namspc({ "mud" }), "noise_field_2d", function_id<void(*)(mud::array_3d<float>&, mud::Noise::NoiseType, float, mud::Noise::Interp)>(&mud::noise_field_2d), func, params, Var() };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::noise_field_3d(val<mud::array_3d<float>>(args[0]), val<mud::Noise::NoiseType>(args[1]), val<float>(args[2]), val<mud::Noise::Interp>(args[3])); };
            std::vector<Param> params = { { "output_values", var(mud::array_3d<float>()), Param::Output }, { "noise_type", var(mud::Noise::NoiseType()) }, { "frequency", var(float(0.01f)), Param::Default }, { "interp", var(mud::Noise::Interp()), Param::Default } };
            static Function f = { &namspc({ "mud" }), "noise_field_3d", function_id<void(*)(mud::array_3d<float>&, mud::Noise::NoiseType, float, mud::Noise::Interp)>(&mud::noise_field_3d), func, params, Var() };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::parse_json_tileset(val<std::string>(args[0]), val<std::string>(args[1]), val<mud::Tileset>(args[2])); };
            std::vector<Param> params = { { "path", var(std::string()) }, { "subset", var(std::string()) }, { "outputTileset", var(mud::Tileset()), Param::Output } };
            static Function f = { &namspc({ "mud" }), "parse_json_tileset", function_id<void(*)(const std::string&, const std::string&, mud::Tileset&)>(&mud::parse_json_tileset), func, params, Var() };
            m.m_functions.push_back(&f);
        }
        {
            auto func = [](array<Var> args, Var& result) { UNUSED(result);  mud::parse_json_wave_tileset(val<std::string>(args[0]), val<std::string>(args[1]), val<mud::WaveTileset>(args[2])); };
            std::vector<Param> params = { { "path", var(std::string()) }, { "subset", var(std::string()) }, { "outputTileset", var(mud::WaveTileset()), Param::Output } };
            static Function f = { &namspc({ "mud" }), "parse_json_wave_tileset", function_id<void(*)(const std::string&, const std::string&, mud::WaveTileset&)>(&mud::parse_json_wave_tileset), func, params, Var() };
            m.m_functions.push_back(&f);
        }
    }
#endif

}
