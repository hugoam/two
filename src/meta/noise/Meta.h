

#pragma once

#ifndef MUD_MODULES
#include <meta/noise/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_noise_meta(Module& m)
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
    
    
    
    // Sequences
    {
        static Meta meta = { type<std::vector<mud::Image256>>(), &namspc({}), "std::vector<mud::Image256>", sizeof(std::vector<mud::Image256>), TypeClass::Sequence };
        static Class cls = { type<std::vector<mud::Image256>>() };
        cls.m_content = &type<mud::Image256>();
        meta_sequence<std::vector<mud::Image256>, mud::Image256>();
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
    
    

    
        m.m_types.push_back(&type<mud::Noise::CellularDistanceFunction>());
        m.m_types.push_back(&type<mud::Noise::CellularReturnType>());
        m.m_types.push_back(&type<mud::Noise::FractalType>());
        m.m_types.push_back(&type<mud::Noise::Interp>());
        m.m_types.push_back(&type<mud::Noise>());
        m.m_types.push_back(&type<mud::Noise::NoiseType>());
    
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
    }
}
