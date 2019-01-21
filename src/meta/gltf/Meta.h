#pragma once

#ifndef MUD_MODULES
#include <meta/gltf/Module.h>

#include <type/Any.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#endif

namespace mud
{
    void mud_gltf_meta(Module& m)
    {
    UNUSED(m);
    
    // Base Types
    
    // Enums
    {
        static Meta meta = { type<glTFAlphaMode>(), &namspc({}), "glTFAlphaMode", sizeof(glTFAlphaMode), TypeClass::Enum };
        static Enum enu = { type<glTFAlphaMode>(),
            true,
            { "OPAQUE", "MASK", "BLEND" },
            { 0, 1, 2 },
            { var(glTFAlphaMode::OPAQUE), var(glTFAlphaMode::MASK), var(glTFAlphaMode::BLEND) }
        };
        meta_enum<glTFAlphaMode>();
    }
    {
        static Meta meta = { type<glTFComponentType>(), &namspc({}), "glTFComponentType", sizeof(glTFComponentType), TypeClass::Enum };
        static Enum enu = { type<glTFComponentType>(),
            true,
            { "BYTE", "UNSIGNED_BYTE", "SHORT", "UNSIGNED_SHORT", "INT", "FLOAT" },
            { 5120, 5121, 5122, 5123, 5125, 5126 },
            { var(glTFComponentType::BYTE), var(glTFComponentType::UNSIGNED_BYTE), var(glTFComponentType::SHORT), var(glTFComponentType::UNSIGNED_SHORT), var(glTFComponentType::INT), var(glTFComponentType::FLOAT) }
        };
        meta_enum<glTFComponentType>();
    }
    {
        static Meta meta = { type<glTFInterpolation>(), &namspc({}), "glTFInterpolation", sizeof(glTFInterpolation), TypeClass::Enum };
        static Enum enu = { type<glTFInterpolation>(),
            true,
            { "LINEAR", "STEP", "CATMULLROMSPLINE", "CUBIC_SPLINE" },
            { 0, 1, 2, 3 },
            { var(glTFInterpolation::LINEAR), var(glTFInterpolation::STEP), var(glTFInterpolation::CATMULLROMSPLINE), var(glTFInterpolation::CUBIC_SPLINE) }
        };
        meta_enum<glTFInterpolation>();
    }
    {
        static Meta meta = { type<glTFPrimitiveType>(), &namspc({}), "glTFPrimitiveType", sizeof(glTFPrimitiveType), TypeClass::Enum };
        static Enum enu = { type<glTFPrimitiveType>(),
            true,
            { "POINTS", "LINES", "LINE_LOOP", "LINE_STRIP", "TRIANGLES", "TRIANGLE_STRIP", "TRIANGLE_FAN" },
            { 0, 1, 2, 3, 4, 5, 6 },
            { var(glTFPrimitiveType::POINTS), var(glTFPrimitiveType::LINES), var(glTFPrimitiveType::LINE_LOOP), var(glTFPrimitiveType::LINE_STRIP), var(glTFPrimitiveType::TRIANGLES), var(glTFPrimitiveType::TRIANGLE_STRIP), var(glTFPrimitiveType::TRIANGLE_FAN) }
        };
        meta_enum<glTFPrimitiveType>();
    }
    {
        static Meta meta = { type<glTFType>(), &namspc({}), "glTFType", sizeof(glTFType), TypeClass::Enum };
        static Enum enu = { type<glTFType>(),
            true,
            { "SCALAR", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4", "INVALID" },
            { 0, 1, 2, 3, 4, 5, 6, 7 },
            { var(glTFType::SCALAR), var(glTFType::VEC2), var(glTFType::VEC3), var(glTFType::VEC4), var(glTFType::MAT2), var(glTFType::MAT3), var(glTFType::MAT4), var(glTFType::INVALID) }
        };
        meta_enum<glTFType>();
    }
    
    // Sequences
    {
        static Meta meta = { type<vector<glTFAccessor>>(), &namspc({}), "vector<glTFAccessor>", sizeof(vector<glTFAccessor>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFAccessor>>() };
        cls.m_content = &type<glTFAccessor>();
        meta_vector<vector<glTFAccessor>, glTFAccessor>();
    }
    {
        static Meta meta = { type<vector<glTFAnimation>>(), &namspc({}), "vector<glTFAnimation>", sizeof(vector<glTFAnimation>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFAnimation>>() };
        cls.m_content = &type<glTFAnimation>();
        meta_vector<vector<glTFAnimation>, glTFAnimation>();
    }
    {
        static Meta meta = { type<vector<glTFAnimationChannel>>(), &namspc({}), "vector<glTFAnimationChannel>", sizeof(vector<glTFAnimationChannel>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFAnimationChannel>>() };
        cls.m_content = &type<glTFAnimationChannel>();
        meta_vector<vector<glTFAnimationChannel>, glTFAnimationChannel>();
    }
    {
        static Meta meta = { type<vector<glTFAnimationSampler>>(), &namspc({}), "vector<glTFAnimationSampler>", sizeof(vector<glTFAnimationSampler>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFAnimationSampler>>() };
        cls.m_content = &type<glTFAnimationSampler>();
        meta_vector<vector<glTFAnimationSampler>, glTFAnimationSampler>();
    }
    {
        static Meta meta = { type<vector<glTFBuffer>>(), &namspc({}), "vector<glTFBuffer>", sizeof(vector<glTFBuffer>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFBuffer>>() };
        cls.m_content = &type<glTFBuffer>();
        meta_vector<vector<glTFBuffer>, glTFBuffer>();
    }
    {
        static Meta meta = { type<vector<glTFBufferView>>(), &namspc({}), "vector<glTFBufferView>", sizeof(vector<glTFBufferView>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFBufferView>>() };
        cls.m_content = &type<glTFBufferView>();
        meta_vector<vector<glTFBufferView>, glTFBufferView>();
    }
    {
        static Meta meta = { type<vector<glTFCamera>>(), &namspc({}), "vector<glTFCamera>", sizeof(vector<glTFCamera>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFCamera>>() };
        cls.m_content = &type<glTFCamera>();
        meta_vector<vector<glTFCamera>, glTFCamera>();
    }
    {
        static Meta meta = { type<vector<glTFImage>>(), &namspc({}), "vector<glTFImage>", sizeof(vector<glTFImage>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFImage>>() };
        cls.m_content = &type<glTFImage>();
        meta_vector<vector<glTFImage>, glTFImage>();
    }
    {
        static Meta meta = { type<vector<glTFMaterial>>(), &namspc({}), "vector<glTFMaterial>", sizeof(vector<glTFMaterial>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFMaterial>>() };
        cls.m_content = &type<glTFMaterial>();
        meta_vector<vector<glTFMaterial>, glTFMaterial>();
    }
    {
        static Meta meta = { type<vector<glTFMesh>>(), &namspc({}), "vector<glTFMesh>", sizeof(vector<glTFMesh>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFMesh>>() };
        cls.m_content = &type<glTFMesh>();
        meta_vector<vector<glTFMesh>, glTFMesh>();
    }
    {
        static Meta meta = { type<vector<glTFMorphTarget>>(), &namspc({}), "vector<glTFMorphTarget>", sizeof(vector<glTFMorphTarget>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFMorphTarget>>() };
        cls.m_content = &type<glTFMorphTarget>();
        meta_vector<vector<glTFMorphTarget>, glTFMorphTarget>();
    }
    {
        static Meta meta = { type<vector<glTFNode>>(), &namspc({}), "vector<glTFNode>", sizeof(vector<glTFNode>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFNode>>() };
        cls.m_content = &type<glTFNode>();
        meta_vector<vector<glTFNode>, glTFNode>();
    }
    {
        static Meta meta = { type<vector<glTFPrimitive>>(), &namspc({}), "vector<glTFPrimitive>", sizeof(vector<glTFPrimitive>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFPrimitive>>() };
        cls.m_content = &type<glTFPrimitive>();
        meta_vector<vector<glTFPrimitive>, glTFPrimitive>();
    }
    {
        static Meta meta = { type<vector<glTFSampler>>(), &namspc({}), "vector<glTFSampler>", sizeof(vector<glTFSampler>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFSampler>>() };
        cls.m_content = &type<glTFSampler>();
        meta_vector<vector<glTFSampler>, glTFSampler>();
    }
    {
        static Meta meta = { type<vector<glTFScene>>(), &namspc({}), "vector<glTFScene>", sizeof(vector<glTFScene>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFScene>>() };
        cls.m_content = &type<glTFScene>();
        meta_vector<vector<glTFScene>, glTFScene>();
    }
    {
        static Meta meta = { type<vector<glTFSkin>>(), &namspc({}), "vector<glTFSkin>", sizeof(vector<glTFSkin>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFSkin>>() };
        cls.m_content = &type<glTFSkin>();
        meta_vector<vector<glTFSkin>, glTFSkin>();
    }
    {
        static Meta meta = { type<vector<glTFTexture>>(), &namspc({}), "vector<glTFTexture>", sizeof(vector<glTFTexture>), TypeClass::Sequence };
        static Class cls = { type<vector<glTFTexture>>() };
        cls.m_content = &type<glTFTexture>();
        meta_vector<vector<glTFTexture>, glTFTexture>();
    }
    {
        static Meta meta = { type<vector<int>>(), &namspc({}), "vector<int>", sizeof(vector<int>), TypeClass::Sequence };
        static Class cls = { type<vector<int>>() };
        cls.m_content = &type<int>();
        meta_vector<vector<int>, int>();
    }
    
    // glTF
    {
        static Meta meta = { type<glTF>(), &namspc({}), "glTF", sizeof(glTF), TypeClass::Struct };
        static Class cls = { type<glTF>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTF>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTF>(ref)) glTF(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTF>(), [](Ref ref, Ref other) { new(&val<glTF>(ref)) glTF(val<glTF>(other)); } }
            },
            // members
            {
                { type<glTF>(), member_address(&glTF::m_buffers), type<vector<glTFBuffer>>(), "buffers", var(vector<glTFBuffer>()), Member::Value, nullptr },
                { type<glTF>(), member_address(&glTF::m_buffer_views), type<vector<glTFBufferView>>(), "buffer_views", var(vector<glTFBufferView>()), Member::Value, nullptr },
                { type<glTF>(), member_address(&glTF::m_accessors), type<vector<glTFAccessor>>(), "accessors", var(vector<glTFAccessor>()), Member::Value, nullptr },
                { type<glTF>(), member_address(&glTF::m_images), type<vector<glTFImage>>(), "images", var(vector<glTFImage>()), Member::Value, nullptr },
                { type<glTF>(), member_address(&glTF::m_textures), type<vector<glTFTexture>>(), "textures", var(vector<glTFTexture>()), Member::Value, nullptr },
                { type<glTF>(), member_address(&glTF::m_materials), type<vector<glTFMaterial>>(), "materials", var(vector<glTFMaterial>()), Member::Value, nullptr },
                { type<glTF>(), member_address(&glTF::m_meshes), type<vector<glTFMesh>>(), "meshes", var(vector<glTFMesh>()), Member::Value, nullptr },
                { type<glTF>(), member_address(&glTF::m_nodes), type<vector<glTFNode>>(), "nodes", var(vector<glTFNode>()), Member::Value, nullptr },
                { type<glTF>(), member_address(&glTF::m_skins), type<vector<glTFSkin>>(), "skins", var(vector<glTFSkin>()), Member::Value, nullptr },
                { type<glTF>(), member_address(&glTF::m_animations), type<vector<glTFAnimation>>(), "animations", var(vector<glTFAnimation>()), Member::Value, nullptr },
                { type<glTF>(), member_address(&glTF::m_cameras), type<vector<glTFCamera>>(), "cameras", var(vector<glTFCamera>()), Member::Value, nullptr },
                { type<glTF>(), member_address(&glTF::m_samplers), type<vector<glTFSampler>>(), "samplers", var(vector<glTFSampler>()), Member::Value, nullptr },
                { type<glTF>(), member_address(&glTF::m_scenes), type<vector<glTFScene>>(), "scenes", var(vector<glTFScene>()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTF>();
    }
    // glTFAccessor
    {
        static Meta meta = { type<glTFAccessor>(), &namspc({}), "glTFAccessor", sizeof(glTFAccessor), TypeClass::Struct };
        static Class cls = { type<glTFAccessor>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFAccessor>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFAccessor>(ref)) glTFAccessor(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFAccessor>(), [](Ref ref, Ref other) { new(&val<glTFAccessor>(ref)) glTFAccessor(val<glTFAccessor>(other)); } }
            },
            // members
            {
                { type<glTFAccessor>(), member_address(&glTFAccessor::name), type<string>(), "name", var(string()), Member::Value, nullptr },
                { type<glTFAccessor>(), member_address(&glTFAccessor::buffer_view), type<int>(), "buffer_view", var(int()), Member::Value, nullptr },
                { type<glTFAccessor>(), member_address(&glTFAccessor::byte_offset), type<int>(), "byte_offset", var(int(0)), Member::Value, nullptr },
                { type<glTFAccessor>(), member_address(&glTFAccessor::component_type), type<glTFComponentType>(), "component_type", var(glTFComponentType()), Member::Value, nullptr },
                { type<glTFAccessor>(), member_address(&glTFAccessor::normalized), type<bool>(), "normalized", var(bool(false)), Member::Value, nullptr },
                { type<glTFAccessor>(), member_address(&glTFAccessor::count), type<int>(), "count", var(int()), Member::Value, nullptr },
                { type<glTFAccessor>(), member_address(&glTFAccessor::type), type<glTFType>(), "type", var(glTFType::INVALID), Member::Value, nullptr },
                { type<glTFAccessor>(), member_address(&glTFAccessor::sparse), type<glTFSparse>(), "sparse", var(glTFSparse()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFAccessor>();
    }
    // glTFAnimation
    {
        static Meta meta = { type<glTFAnimation>(), &namspc({}), "glTFAnimation", sizeof(glTFAnimation), TypeClass::Struct };
        static Class cls = { type<glTFAnimation>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFAnimation>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFAnimation>(ref)) glTFAnimation(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFAnimation>(), [](Ref ref, Ref other) { new(&val<glTFAnimation>(ref)) glTFAnimation(val<glTFAnimation>(other)); } }
            },
            // members
            {
                { type<glTFAnimation>(), member_address(&glTFAnimation::name), type<string>(), "name", var(string()), Member::Value, nullptr },
                { type<glTFAnimation>(), member_address(&glTFAnimation::samplers), type<vector<glTFAnimationSampler>>(), "samplers", var(vector<glTFAnimationSampler>()), Member::Value, nullptr },
                { type<glTFAnimation>(), member_address(&glTFAnimation::channels), type<vector<glTFAnimationChannel>>(), "channels", var(vector<glTFAnimationChannel>()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFAnimation>();
    }
    // glTFAnimationChannel
    {
        static Meta meta = { type<glTFAnimationChannel>(), &namspc({}), "glTFAnimationChannel", sizeof(glTFAnimationChannel), TypeClass::Struct };
        static Class cls = { type<glTFAnimationChannel>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFAnimationChannel>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFAnimationChannel>(ref)) glTFAnimationChannel(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFAnimationChannel>(), [](Ref ref, Ref other) { new(&val<glTFAnimationChannel>(ref)) glTFAnimationChannel(val<glTFAnimationChannel>(other)); } }
            },
            // members
            {
                { type<glTFAnimationChannel>(), member_address(&glTFAnimationChannel::sampler), type<int>(), "sampler", var(int()), Member::Value, nullptr },
                { type<glTFAnimationChannel>(), member_address(&glTFAnimationChannel::target), type<glTFAnimationTarget>(), "target", var(glTFAnimationTarget()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFAnimationChannel>();
    }
    // glTFAnimationSampler
    {
        static Meta meta = { type<glTFAnimationSampler>(), &namspc({}), "glTFAnimationSampler", sizeof(glTFAnimationSampler), TypeClass::Struct };
        static Class cls = { type<glTFAnimationSampler>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFAnimationSampler>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFAnimationSampler>(ref)) glTFAnimationSampler(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFAnimationSampler>(), [](Ref ref, Ref other) { new(&val<glTFAnimationSampler>(ref)) glTFAnimationSampler(val<glTFAnimationSampler>(other)); } }
            },
            // members
            {
                { type<glTFAnimationSampler>(), member_address(&glTFAnimationSampler::interpolation), type<glTFInterpolation>(), "interpolation", var(glTFInterpolation()), Member::Value, nullptr },
                { type<glTFAnimationSampler>(), member_address(&glTFAnimationSampler::input), type<int>(), "input", var(int()), Member::Value, nullptr },
                { type<glTFAnimationSampler>(), member_address(&glTFAnimationSampler::output), type<int>(), "output", var(int()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFAnimationSampler>();
    }
    // glTFAnimationTarget
    {
        static Meta meta = { type<glTFAnimationTarget>(), &namspc({}), "glTFAnimationTarget", sizeof(glTFAnimationTarget), TypeClass::Struct };
        static Class cls = { type<glTFAnimationTarget>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFAnimationTarget>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFAnimationTarget>(ref)) glTFAnimationTarget(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFAnimationTarget>(), [](Ref ref, Ref other) { new(&val<glTFAnimationTarget>(ref)) glTFAnimationTarget(val<glTFAnimationTarget>(other)); } }
            },
            // members
            {
                { type<glTFAnimationTarget>(), member_address(&glTFAnimationTarget::node), type<int>(), "node", var(int()), Member::Value, nullptr },
                { type<glTFAnimationTarget>(), member_address(&glTFAnimationTarget::path), type<string>(), "path", var(string()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFAnimationTarget>();
    }
    // glTFAttributes
    {
        static Meta meta = { type<glTFAttributes>(), &namspc({}), "glTFAttributes", sizeof(glTFAttributes), TypeClass::Struct };
        static Class cls = { type<glTFAttributes>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFAttributes>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFAttributes>(ref)) glTFAttributes(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFAttributes>(), [](Ref ref, Ref other) { new(&val<glTFAttributes>(ref)) glTFAttributes(val<glTFAttributes>(other)); } }
            },
            // members
            {
                { type<glTFAttributes>(), member_address(&glTFAttributes::POSITION), type<int>(), "POSITION", var(int()), Member::Value, nullptr },
                { type<glTFAttributes>(), member_address(&glTFAttributes::NORMAL), type<int>(), "NORMAL", var(int()), Member::Value, nullptr },
                { type<glTFAttributes>(), member_address(&glTFAttributes::TANGENT), type<int>(), "TANGENT", var(int()), Member::Value, nullptr },
                { type<glTFAttributes>(), member_address(&glTFAttributes::TEXCOORD_0), type<int>(), "TEXCOORD_0", var(int()), Member::Value, nullptr },
                { type<glTFAttributes>(), member_address(&glTFAttributes::TEXCOORD_1), type<int>(), "TEXCOORD_1", var(int()), Member::Value, nullptr },
                { type<glTFAttributes>(), member_address(&glTFAttributes::COLOR_0), type<int>(), "COLOR_0", var(int()), Member::Value, nullptr },
                { type<glTFAttributes>(), member_address(&glTFAttributes::JOINTS_0), type<int>(), "JOINTS_0", var(int()), Member::Value, nullptr },
                { type<glTFAttributes>(), member_address(&glTFAttributes::WEIGHTS_0), type<int>(), "WEIGHTS_0", var(int()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFAttributes>();
    }
    // glTFBuffer
    {
        static Meta meta = { type<glTFBuffer>(), &namspc({}), "glTFBuffer", sizeof(glTFBuffer), TypeClass::Struct };
        static Class cls = { type<glTFBuffer>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFBuffer>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFBuffer>(ref)) glTFBuffer(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFBuffer>(), [](Ref ref, Ref other) { new(&val<glTFBuffer>(ref)) glTFBuffer(val<glTFBuffer>(other)); } }
            },
            // members
            {
                { type<glTFBuffer>(), member_address(&glTFBuffer::name), type<string>(), "name", var(string()), Member::Value, nullptr },
                { type<glTFBuffer>(), member_address(&glTFBuffer::mime_type), type<string>(), "mime_type", var(string()), Member::Value, nullptr },
                { type<glTFBuffer>(), member_address(&glTFBuffer::uri), type<string>(), "uri", var(string()), Member::Value, nullptr },
                { type<glTFBuffer>(), member_address(&glTFBuffer::byte_length), type<int>(), "byte_length", var(int()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFBuffer>();
    }
    // glTFBufferView
    {
        static Meta meta = { type<glTFBufferView>(), &namspc({}), "glTFBufferView", sizeof(glTFBufferView), TypeClass::Struct };
        static Class cls = { type<glTFBufferView>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFBufferView>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFBufferView>(ref)) glTFBufferView(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFBufferView>(), [](Ref ref, Ref other) { new(&val<glTFBufferView>(ref)) glTFBufferView(val<glTFBufferView>(other)); } }
            },
            // members
            {
                { type<glTFBufferView>(), member_address(&glTFBufferView::name), type<string>(), "name", var(string()), Member::Value, nullptr },
                { type<glTFBufferView>(), member_address(&glTFBufferView::buffer), type<int>(), "buffer", var(int(0)), Member::Value, nullptr },
                { type<glTFBufferView>(), member_address(&glTFBufferView::byte_offset), type<size_t>(), "byte_offset", var(size_t(0)), Member::Value, nullptr },
                { type<glTFBufferView>(), member_address(&glTFBufferView::byte_length), type<size_t>(), "byte_length", var(size_t(0)), Member::Value, nullptr },
                { type<glTFBufferView>(), member_address(&glTFBufferView::byte_stride), type<size_t>(), "byte_stride", var(size_t(0)), Member::Value, nullptr },
                { type<glTFBufferView>(), member_address(&glTFBufferView::target), type<int>(), "target", var(int(0)), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFBufferView>();
    }
    // glTFCamera
    {
        static Meta meta = { type<glTFCamera>(), &namspc({}), "glTFCamera", sizeof(glTFCamera), TypeClass::Struct };
        static Class cls = { type<glTFCamera>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFCamera>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFCamera>(ref)) glTFCamera(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFCamera>(), [](Ref ref, Ref other) { new(&val<glTFCamera>(ref)) glTFCamera(val<glTFCamera>(other)); } }
            },
            // members
            {
                { type<glTFCamera>(), member_address(&glTFCamera::name), type<string>(), "name", var(string()), Member::Value, nullptr },
                { type<glTFCamera>(), member_address(&glTFCamera::type), type<string>(), "type", var(string()), Member::Value, nullptr },
                { type<glTFCamera>(), member_address(&glTFCamera::orthographic), type<glTFOrthographic>(), "orthographic", var(glTFOrthographic()), Member::Value, nullptr },
                { type<glTFCamera>(), member_address(&glTFCamera::perspective), type<glTFPerspective>(), "perspective", var(glTFPerspective()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFCamera>();
    }
    // glTFImage
    {
        static Meta meta = { type<glTFImage>(), &namspc({}), "glTFImage", sizeof(glTFImage), TypeClass::Struct };
        static Class cls = { type<glTFImage>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFImage>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFImage>(ref)) glTFImage(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFImage>(), [](Ref ref, Ref other) { new(&val<glTFImage>(ref)) glTFImage(val<glTFImage>(other)); } }
            },
            // members
            {
                { type<glTFImage>(), member_address(&glTFImage::name), type<string>(), "name", var(string()), Member::Value, nullptr },
                { type<glTFImage>(), member_address(&glTFImage::mime_type), type<string>(), "mime_type", var(string()), Member::Value, nullptr },
                { type<glTFImage>(), member_address(&glTFImage::uri), type<string>(), "uri", var(string()), Member::Value, nullptr },
                { type<glTFImage>(), member_address(&glTFImage::buffer_view), type<int>(), "buffer_view", var(int()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFImage>();
    }
    // glTFMaterial
    {
        static Meta meta = { type<glTFMaterial>(), &namspc({}), "glTFMaterial", sizeof(glTFMaterial), TypeClass::Struct };
        static Class cls = { type<glTFMaterial>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFMaterial>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFMaterial>(ref)) glTFMaterial(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFMaterial>(), [](Ref ref, Ref other) { new(&val<glTFMaterial>(ref)) glTFMaterial(val<glTFMaterial>(other)); } }
            },
            // members
            {
                { type<glTFMaterial>(), member_address(&glTFMaterial::name), type<string>(), "name", var(string()), Member::Value, nullptr },
                { type<glTFMaterial>(), member_address(&glTFMaterial::normal_texture), type<glTFTextureInfo>(), "normal_texture", var(glTFTextureInfo()), Member::Value, nullptr },
                { type<glTFMaterial>(), member_address(&glTFMaterial::occlusion_texture), type<glTFTextureInfo>(), "occlusion_texture", var(glTFTextureInfo()), Member::Value, nullptr },
                { type<glTFMaterial>(), member_address(&glTFMaterial::emissive_factor), type<mud::vec3>(), "emissive_factor", var(mud::vec3(to_vec3(mud::Colour::Black))), Member::Value, nullptr },
                { type<glTFMaterial>(), member_address(&glTFMaterial::emissive_texture), type<glTFTextureInfo>(), "emissive_texture", var(glTFTextureInfo()), Member::Value, nullptr },
                { type<glTFMaterial>(), member_address(&glTFMaterial::double_sided), type<bool>(), "double_sided", var(bool(false)), Member::Value, nullptr },
                { type<glTFMaterial>(), member_address(&glTFMaterial::alpha_mode), type<glTFAlphaMode>(), "alpha_mode", var(glTFAlphaMode::OPAQUE), Member::Value, nullptr },
                { type<glTFMaterial>(), member_address(&glTFMaterial::pbr_metallic_roughness), type<glTFMaterialPBR>(), "pbr_metallic_roughness", var(glTFMaterialPBR()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFMaterial>();
    }
    // glTFMaterialPBR
    {
        static Meta meta = { type<glTFMaterialPBR>(), &namspc({}), "glTFMaterialPBR", sizeof(glTFMaterialPBR), TypeClass::Struct };
        static Class cls = { type<glTFMaterialPBR>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFMaterialPBR>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFMaterialPBR>(ref)) glTFMaterialPBR(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFMaterialPBR>(), [](Ref ref, Ref other) { new(&val<glTFMaterialPBR>(ref)) glTFMaterialPBR(val<glTFMaterialPBR>(other)); } }
            },
            // members
            {
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::base_color_factor), type<mud::vec4>(), "base_color_factor", var(mud::vec4(1.f)), Member::Value, nullptr },
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::base_color_texture), type<glTFTextureInfo>(), "base_color_texture", var(glTFTextureInfo()), Member::Value, nullptr },
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::metallic_factor), type<float>(), "metallic_factor", var(float(1.f)), Member::Value, nullptr },
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::roughness_factor), type<float>(), "roughness_factor", var(float(1.f)), Member::Value, nullptr },
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::metallic_roughness_texture), type<glTFTextureInfo>(), "metallic_roughness_texture", var(glTFTextureInfo()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFMaterialPBR>();
    }
    // glTFMesh
    {
        static Meta meta = { type<glTFMesh>(), &namspc({}), "glTFMesh", sizeof(glTFMesh), TypeClass::Struct };
        static Class cls = { type<glTFMesh>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFMesh>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFMesh>(ref)) glTFMesh(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFMesh>(), [](Ref ref, Ref other) { new(&val<glTFMesh>(ref)) glTFMesh(val<glTFMesh>(other)); } }
            },
            // members
            {
                { type<glTFMesh>(), member_address(&glTFMesh::name), type<string>(), "name", var(string()), Member::Value, nullptr },
                { type<glTFMesh>(), member_address(&glTFMesh::primitives), type<vector<glTFPrimitive>>(), "primitives", var(vector<glTFPrimitive>()), Member::Value, nullptr },
                { type<glTFMesh>(), member_address(&glTFMesh::weights), type<vector<float>>(), "weights", var(vector<float>()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFMesh>();
    }
    // glTFMorphTarget
    {
        static Meta meta = { type<glTFMorphTarget>(), &namspc({}), "glTFMorphTarget", sizeof(glTFMorphTarget), TypeClass::Struct };
        static Class cls = { type<glTFMorphTarget>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFMorphTarget>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFMorphTarget>(ref)) glTFMorphTarget(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFMorphTarget>(), [](Ref ref, Ref other) { new(&val<glTFMorphTarget>(ref)) glTFMorphTarget(val<glTFMorphTarget>(other)); } }
            },
            // members
            {
                { type<glTFMorphTarget>(), member_address(&glTFMorphTarget::POSITION), type<int>(), "POSITION", var(int()), Member::Value, nullptr },
                { type<glTFMorphTarget>(), member_address(&glTFMorphTarget::NORMAL), type<int>(), "NORMAL", var(int()), Member::Value, nullptr },
                { type<glTFMorphTarget>(), member_address(&glTFMorphTarget::TANGENT), type<int>(), "TANGENT", var(int()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFMorphTarget>();
    }
    // glTFNode
    {
        static Meta meta = { type<glTFNode>(), &namspc({}), "glTFNode", sizeof(glTFNode), TypeClass::Struct };
        static Class cls = { type<glTFNode>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFNode>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFNode>(ref)) glTFNode(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFNode>(), [](Ref ref, Ref other) { new(&val<glTFNode>(ref)) glTFNode(val<glTFNode>(other)); } }
            },
            // members
            {
                { type<glTFNode>(), member_address(&glTFNode::name), type<string>(), "name", var(string()), Member::Value, nullptr },
                { type<glTFNode>(), member_address(&glTFNode::mesh), type<int>(), "mesh", var(int()), Member::Value, nullptr },
                { type<glTFNode>(), member_address(&glTFNode::camera), type<int>(), "camera", var(int()), Member::Value, nullptr },
                { type<glTFNode>(), member_address(&glTFNode::skin), type<int>(), "skin", var(int()), Member::Value, nullptr },
                { type<glTFNode>(), member_address(&glTFNode::matrix), type<mud::mat4>(), "matrix", var(mud::mat4()), Member::Value, nullptr },
                { type<glTFNode>(), member_address(&glTFNode::translation), type<mud::vec3>(), "translation", var(mud::vec3(mud::Zero3)), Member::Value, nullptr },
                { type<glTFNode>(), member_address(&glTFNode::rotation), type<mud::quat>(), "rotation", var(mud::quat(mud::ZeroQuat)), Member::Value, nullptr },
                { type<glTFNode>(), member_address(&glTFNode::scale), type<mud::vec3>(), "scale", var(mud::vec3(mud::Unit3)), Member::Value, nullptr },
                { type<glTFNode>(), member_address(&glTFNode::children), type<vector<int>>(), "children", var(vector<int>()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFNode>();
    }
    // glTFNodeExtras
    {
        static Meta meta = { type<glTFNodeExtras>(), &namspc({}), "glTFNodeExtras", sizeof(glTFNodeExtras), TypeClass::Struct };
        static Class cls = { type<glTFNodeExtras>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFNodeExtras>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFNodeExtras>(ref)) glTFNodeExtras(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFNodeExtras>(), [](Ref ref, Ref other) { new(&val<glTFNodeExtras>(ref)) glTFNodeExtras(val<glTFNodeExtras>(other)); } }
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
        meta_class<glTFNodeExtras>();
    }
    // glTFOrthographic
    {
        static Meta meta = { type<glTFOrthographic>(), &namspc({}), "glTFOrthographic", sizeof(glTFOrthographic), TypeClass::Struct };
        static Class cls = { type<glTFOrthographic>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFOrthographic>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFOrthographic>(ref)) glTFOrthographic(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFOrthographic>(), [](Ref ref, Ref other) { new(&val<glTFOrthographic>(ref)) glTFOrthographic(val<glTFOrthographic>(other)); } }
            },
            // members
            {
                { type<glTFOrthographic>(), member_address(&glTFOrthographic::xmag), type<float>(), "xmag", var(float()), Member::Value, nullptr },
                { type<glTFOrthographic>(), member_address(&glTFOrthographic::ymag), type<float>(), "ymag", var(float()), Member::Value, nullptr },
                { type<glTFOrthographic>(), member_address(&glTFOrthographic::zfar), type<float>(), "zfar", var(float()), Member::Value, nullptr },
                { type<glTFOrthographic>(), member_address(&glTFOrthographic::znear), type<float>(), "znear", var(float()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFOrthographic>();
    }
    // glTFPerspective
    {
        static Meta meta = { type<glTFPerspective>(), &namspc({}), "glTFPerspective", sizeof(glTFPerspective), TypeClass::Struct };
        static Class cls = { type<glTFPerspective>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFPerspective>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFPerspective>(ref)) glTFPerspective(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFPerspective>(), [](Ref ref, Ref other) { new(&val<glTFPerspective>(ref)) glTFPerspective(val<glTFPerspective>(other)); } }
            },
            // members
            {
                { type<glTFPerspective>(), member_address(&glTFPerspective::yfov), type<float>(), "yfov", var(float()), Member::Value, nullptr },
                { type<glTFPerspective>(), member_address(&glTFPerspective::zfar), type<float>(), "zfar", var(float()), Member::Value, nullptr },
                { type<glTFPerspective>(), member_address(&glTFPerspective::znear), type<float>(), "znear", var(float()), Member::Value, nullptr },
                { type<glTFPerspective>(), member_address(&glTFPerspective::aspect_ration), type<float>(), "aspect_ration", var(float()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFPerspective>();
    }
    // glTFPrimitive
    {
        static Meta meta = { type<glTFPrimitive>(), &namspc({}), "glTFPrimitive", sizeof(glTFPrimitive), TypeClass::Struct };
        static Class cls = { type<glTFPrimitive>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFPrimitive>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFPrimitive>(ref)) glTFPrimitive(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFPrimitive>(), [](Ref ref, Ref other) { new(&val<glTFPrimitive>(ref)) glTFPrimitive(val<glTFPrimitive>(other)); } }
            },
            // members
            {
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::attributes), type<glTFAttributes>(), "attributes", var(glTFAttributes()), Member::Value, nullptr },
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::indices), type<int>(), "indices", var(int()), Member::Value, nullptr },
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::material), type<int>(), "material", var(int()), Member::Value, nullptr },
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::mode), type<glTFPrimitiveType>(), "mode", var(glTFPrimitiveType::TRIANGLES), Member::Value, nullptr },
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::targets), type<vector<glTFMorphTarget>>(), "targets", var(vector<glTFMorphTarget>()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFPrimitive>();
    }
    // glTFSampler
    {
        static Meta meta = { type<glTFSampler>(), &namspc({}), "glTFSampler", sizeof(glTFSampler), TypeClass::Struct };
        static Class cls = { type<glTFSampler>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFSampler>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFSampler>(ref)) glTFSampler(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFSampler>(), [](Ref ref, Ref other) { new(&val<glTFSampler>(ref)) glTFSampler(val<glTFSampler>(other)); } }
            },
            // members
            {
                { type<glTFSampler>(), member_address(&glTFSampler::mag_filter), type<int>(), "mag_filter", var(int()), Member::Value, nullptr },
                { type<glTFSampler>(), member_address(&glTFSampler::min_filter), type<int>(), "min_filter", var(int()), Member::Value, nullptr },
                { type<glTFSampler>(), member_address(&glTFSampler::wrap_s), type<int>(), "wrap_s", var(int(10497)), Member::Value, nullptr },
                { type<glTFSampler>(), member_address(&glTFSampler::wrap_t), type<int>(), "wrap_t", var(int(10497)), Member::Value, nullptr },
                { type<glTFSampler>(), member_address(&glTFSampler::name), type<string>(), "name", var(string()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFSampler>();
    }
    // glTFScene
    {
        static Meta meta = { type<glTFScene>(), &namspc({}), "glTFScene", sizeof(glTFScene), TypeClass::Struct };
        static Class cls = { type<glTFScene>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFScene>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFScene>(ref)) glTFScene(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFScene>(), [](Ref ref, Ref other) { new(&val<glTFScene>(ref)) glTFScene(val<glTFScene>(other)); } }
            },
            // members
            {
                { type<glTFScene>(), member_address(&glTFScene::name), type<string>(), "name", var(string()), Member::Value, nullptr },
                { type<glTFScene>(), member_address(&glTFScene::nodes), type<vector<int>>(), "nodes", var(vector<int>()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFScene>();
    }
    // glTFSkin
    {
        static Meta meta = { type<glTFSkin>(), &namspc({}), "glTFSkin", sizeof(glTFSkin), TypeClass::Struct };
        static Class cls = { type<glTFSkin>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFSkin>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFSkin>(ref)) glTFSkin(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFSkin>(), [](Ref ref, Ref other) { new(&val<glTFSkin>(ref)) glTFSkin(val<glTFSkin>(other)); } }
            },
            // members
            {
                { type<glTFSkin>(), member_address(&glTFSkin::name), type<string>(), "name", var(string()), Member::Value, nullptr },
                { type<glTFSkin>(), member_address(&glTFSkin::skeleton), type<int>(), "skeleton", var(int()), Member::Value, nullptr },
                { type<glTFSkin>(), member_address(&glTFSkin::joints), type<vector<int>>(), "joints", var(vector<int>()), Member::Value, nullptr },
                { type<glTFSkin>(), member_address(&glTFSkin::inverse_bind_matrices), type<int>(), "inverse_bind_matrices", var(int()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFSkin>();
    }
    // glTFSparse
    {
        static Meta meta = { type<glTFSparse>(), &namspc({}), "glTFSparse", sizeof(glTFSparse), TypeClass::Struct };
        static Class cls = { type<glTFSparse>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFSparse>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFSparse>(ref)) glTFSparse(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFSparse>(), [](Ref ref, Ref other) { new(&val<glTFSparse>(ref)) glTFSparse(val<glTFSparse>(other)); } }
            },
            // members
            {
                { type<glTFSparse>(), member_address(&glTFSparse::count), type<int>(), "count", var(int(0)), Member::Value, nullptr },
                { type<glTFSparse>(), member_address(&glTFSparse::indices), type<glTFSparseIndices>(), "indices", var(glTFSparseIndices()), Member::Value, nullptr },
                { type<glTFSparse>(), member_address(&glTFSparse::values), type<glTFSparseValues>(), "values", var(glTFSparseValues()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFSparse>();
    }
    // glTFSparseIndices
    {
        static Meta meta = { type<glTFSparseIndices>(), &namspc({}), "glTFSparseIndices", sizeof(glTFSparseIndices), TypeClass::Struct };
        static Class cls = { type<glTFSparseIndices>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFSparseIndices>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFSparseIndices>(ref)) glTFSparseIndices(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFSparseIndices>(), [](Ref ref, Ref other) { new(&val<glTFSparseIndices>(ref)) glTFSparseIndices(val<glTFSparseIndices>(other)); } }
            },
            // members
            {
                { type<glTFSparseIndices>(), member_address(&glTFSparseIndices::buffer_view), type<int>(), "buffer_view", var(int()), Member::Value, nullptr },
                { type<glTFSparseIndices>(), member_address(&glTFSparseIndices::byte_offset), type<int>(), "byte_offset", var(int(0)), Member::Value, nullptr },
                { type<glTFSparseIndices>(), member_address(&glTFSparseIndices::component_type), type<glTFComponentType>(), "component_type", var(glTFComponentType()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFSparseIndices>();
    }
    // glTFSparseValues
    {
        static Meta meta = { type<glTFSparseValues>(), &namspc({}), "glTFSparseValues", sizeof(glTFSparseValues), TypeClass::Struct };
        static Class cls = { type<glTFSparseValues>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFSparseValues>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFSparseValues>(ref)) glTFSparseValues(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFSparseValues>(), [](Ref ref, Ref other) { new(&val<glTFSparseValues>(ref)) glTFSparseValues(val<glTFSparseValues>(other)); } }
            },
            // members
            {
                { type<glTFSparseValues>(), member_address(&glTFSparseValues::buffer_view), type<int>(), "buffer_view", var(int()), Member::Value, nullptr },
                { type<glTFSparseValues>(), member_address(&glTFSparseValues::byte_offset), type<int>(), "byte_offset", var(int(0)), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFSparseValues>();
    }
    // glTFTexture
    {
        static Meta meta = { type<glTFTexture>(), &namspc({}), "glTFTexture", sizeof(glTFTexture), TypeClass::Struct };
        static Class cls = { type<glTFTexture>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFTexture>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFTexture>(ref)) glTFTexture(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFTexture>(), [](Ref ref, Ref other) { new(&val<glTFTexture>(ref)) glTFTexture(val<glTFTexture>(other)); } }
            },
            // members
            {
                { type<glTFTexture>(), member_address(&glTFTexture::name), type<string>(), "name", var(string()), Member::Value, nullptr },
                { type<glTFTexture>(), member_address(&glTFTexture::sampler), type<int>(), "sampler", var(int()), Member::Value, nullptr },
                { type<glTFTexture>(), member_address(&glTFTexture::source), type<int>(), "source", var(int()), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFTexture>();
    }
    // glTFTextureInfo
    {
        static Meta meta = { type<glTFTextureInfo>(), &namspc({}), "glTFTextureInfo", sizeof(glTFTextureInfo), TypeClass::Struct };
        static Class cls = { type<glTFTextureInfo>(),
            // bases
            {  },
            {  },
            // constructors
            {
                { type<glTFTextureInfo>(), [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFTextureInfo>(ref)) glTFTextureInfo(  ); }, {} }
            },
            // copy constructor
            {
                { type<glTFTextureInfo>(), [](Ref ref, Ref other) { new(&val<glTFTextureInfo>(ref)) glTFTextureInfo(val<glTFTextureInfo>(other)); } }
            },
            // members
            {
                { type<glTFTextureInfo>(), member_address(&glTFTextureInfo::index), type<int>(), "index", var(int()), Member::Value, nullptr },
                { type<glTFTextureInfo>(), member_address(&glTFTextureInfo::scale), type<float>(), "scale", var(float(1.f)), Member::Value, nullptr }
            },
            // methods
            {
            },
            // static members
            {
            }
        };
        meta_class<glTFTextureInfo>();
    }
        m.m_types.push_back(&type<glTF>());
        m.m_types.push_back(&type<glTFAccessor>());
        m.m_types.push_back(&type<glTFAlphaMode>());
        m.m_types.push_back(&type<glTFAnimation>());
        m.m_types.push_back(&type<glTFAnimationChannel>());
        m.m_types.push_back(&type<glTFAnimationSampler>());
        m.m_types.push_back(&type<glTFAnimationTarget>());
        m.m_types.push_back(&type<glTFAttributes>());
        m.m_types.push_back(&type<glTFBuffer>());
        m.m_types.push_back(&type<glTFBufferView>());
        m.m_types.push_back(&type<glTFCamera>());
        m.m_types.push_back(&type<glTFComponentType>());
        m.m_types.push_back(&type<glTFImage>());
        m.m_types.push_back(&type<glTFInterpolation>());
        m.m_types.push_back(&type<glTFMaterial>());
        m.m_types.push_back(&type<glTFMaterialPBR>());
        m.m_types.push_back(&type<glTFMesh>());
        m.m_types.push_back(&type<glTFMorphTarget>());
        m.m_types.push_back(&type<glTFNode>());
        m.m_types.push_back(&type<glTFNodeExtras>());
        m.m_types.push_back(&type<glTFOrthographic>());
        m.m_types.push_back(&type<glTFPerspective>());
        m.m_types.push_back(&type<glTFPrimitive>());
        m.m_types.push_back(&type<glTFPrimitiveType>());
        m.m_types.push_back(&type<glTFSampler>());
        m.m_types.push_back(&type<glTFScene>());
        m.m_types.push_back(&type<glTFSkin>());
        m.m_types.push_back(&type<glTFSparse>());
        m.m_types.push_back(&type<glTFSparseIndices>());
        m.m_types.push_back(&type<glTFSparseValues>());
        m.m_types.push_back(&type<glTFTexture>());
        m.m_types.push_back(&type<glTFTextureInfo>());
        m.m_types.push_back(&type<glTFType>());
        m.m_types.push_back(&type<vector<glTFAccessor>>());
        m.m_types.push_back(&type<vector<glTFAnimation>>());
        m.m_types.push_back(&type<vector<glTFAnimationChannel>>());
        m.m_types.push_back(&type<vector<glTFAnimationSampler>>());
        m.m_types.push_back(&type<vector<glTFBuffer>>());
        m.m_types.push_back(&type<vector<glTFBufferView>>());
        m.m_types.push_back(&type<vector<glTFCamera>>());
        m.m_types.push_back(&type<vector<glTFImage>>());
        m.m_types.push_back(&type<vector<glTFMaterial>>());
        m.m_types.push_back(&type<vector<glTFMesh>>());
        m.m_types.push_back(&type<vector<glTFMorphTarget>>());
        m.m_types.push_back(&type<vector<glTFNode>>());
        m.m_types.push_back(&type<vector<glTFPrimitive>>());
        m.m_types.push_back(&type<vector<glTFSampler>>());
        m.m_types.push_back(&type<vector<glTFScene>>());
        m.m_types.push_back(&type<vector<glTFSkin>>());
        m.m_types.push_back(&type<vector<glTFTexture>>());
        m.m_types.push_back(&type<vector<int>>());
    }
}
