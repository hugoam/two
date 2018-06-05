

#pragma once

#ifndef MUD_MODULES
#include <gfx-gltf/Generated/Module.h>

#include <obj/Any.h>
#include <obj/Reflect/MetaDecl.h>
#include <obj/System/System.h>
#endif

namespace mud
{
    
#ifdef MUD_GFX_GLTF_REFLECTION_IMPL
    void gfxgltf_meta(Module& m)
    {   
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
            { "SCALAR", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4" },
            { 0, 1, 2, 3, 4, 5, 6 },
            { var(glTFType::SCALAR), var(glTFType::VEC2), var(glTFType::VEC3), var(glTFType::VEC4), var(glTFType::MAT2), var(glTFType::MAT3), var(glTFType::MAT4) }
        };
        meta_enum<glTFType>();
    }
    
    
    // Sequences
    {
        static Meta meta = { type<std::vector<glTFAccessor>>(), &namspc({}), "std::vector<glTFAccessor>", sizeof(std::vector<glTFAccessor>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFAccessor>>() };
        cls.m_content = &type<glTFAccessor>();
        meta_sequence<std::vector<glTFAccessor>, glTFAccessor>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFAnimation>>(), &namspc({}), "std::vector<glTFAnimation>", sizeof(std::vector<glTFAnimation>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFAnimation>>() };
        cls.m_content = &type<glTFAnimation>();
        meta_sequence<std::vector<glTFAnimation>, glTFAnimation>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFAnimationChannel>>(), &namspc({}), "std::vector<glTFAnimationChannel>", sizeof(std::vector<glTFAnimationChannel>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFAnimationChannel>>() };
        cls.m_content = &type<glTFAnimationChannel>();
        meta_sequence<std::vector<glTFAnimationChannel>, glTFAnimationChannel>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFAnimationSampler>>(), &namspc({}), "std::vector<glTFAnimationSampler>", sizeof(std::vector<glTFAnimationSampler>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFAnimationSampler>>() };
        cls.m_content = &type<glTFAnimationSampler>();
        meta_sequence<std::vector<glTFAnimationSampler>, glTFAnimationSampler>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFBuffer>>(), &namspc({}), "std::vector<glTFBuffer>", sizeof(std::vector<glTFBuffer>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFBuffer>>() };
        cls.m_content = &type<glTFBuffer>();
        meta_sequence<std::vector<glTFBuffer>, glTFBuffer>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFBufferView>>(), &namspc({}), "std::vector<glTFBufferView>", sizeof(std::vector<glTFBufferView>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFBufferView>>() };
        cls.m_content = &type<glTFBufferView>();
        meta_sequence<std::vector<glTFBufferView>, glTFBufferView>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFCamera>>(), &namspc({}), "std::vector<glTFCamera>", sizeof(std::vector<glTFCamera>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFCamera>>() };
        cls.m_content = &type<glTFCamera>();
        meta_sequence<std::vector<glTFCamera>, glTFCamera>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFImage>>(), &namspc({}), "std::vector<glTFImage>", sizeof(std::vector<glTFImage>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFImage>>() };
        cls.m_content = &type<glTFImage>();
        meta_sequence<std::vector<glTFImage>, glTFImage>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFMaterial>>(), &namspc({}), "std::vector<glTFMaterial>", sizeof(std::vector<glTFMaterial>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFMaterial>>() };
        cls.m_content = &type<glTFMaterial>();
        meta_sequence<std::vector<glTFMaterial>, glTFMaterial>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFMesh>>(), &namspc({}), "std::vector<glTFMesh>", sizeof(std::vector<glTFMesh>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFMesh>>() };
        cls.m_content = &type<glTFMesh>();
        meta_sequence<std::vector<glTFMesh>, glTFMesh>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFMorphTarget>>(), &namspc({}), "std::vector<glTFMorphTarget>", sizeof(std::vector<glTFMorphTarget>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFMorphTarget>>() };
        cls.m_content = &type<glTFMorphTarget>();
        meta_sequence<std::vector<glTFMorphTarget>, glTFMorphTarget>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFNode>>(), &namspc({}), "std::vector<glTFNode>", sizeof(std::vector<glTFNode>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFNode>>() };
        cls.m_content = &type<glTFNode>();
        meta_sequence<std::vector<glTFNode>, glTFNode>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFPrimitive>>(), &namspc({}), "std::vector<glTFPrimitive>", sizeof(std::vector<glTFPrimitive>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFPrimitive>>() };
        cls.m_content = &type<glTFPrimitive>();
        meta_sequence<std::vector<glTFPrimitive>, glTFPrimitive>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFScene>>(), &namspc({}), "std::vector<glTFScene>", sizeof(std::vector<glTFScene>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFScene>>() };
        cls.m_content = &type<glTFScene>();
        meta_sequence<std::vector<glTFScene>, glTFScene>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFSkin>>(), &namspc({}), "std::vector<glTFSkin>", sizeof(std::vector<glTFSkin>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFSkin>>() };
        cls.m_content = &type<glTFSkin>();
        meta_sequence<std::vector<glTFSkin>, glTFSkin>();
    }
    
    {
        static Meta meta = { type<std::vector<glTFTexture>>(), &namspc({}), "std::vector<glTFTexture>", sizeof(std::vector<glTFTexture>), TypeClass::Sequence };
        static Class cls = { type<std::vector<glTFTexture>>() };
        cls.m_content = &type<glTFTexture>();
        meta_sequence<std::vector<glTFTexture>, glTFTexture>();
    }
    
    {
        static Meta meta = { type<std::vector<int>>(), &namspc({}), "std::vector<int>", sizeof(std::vector<int>), TypeClass::Sequence };
        static Class cls = { type<std::vector<int>>() };
        cls.m_content = &type<int>();
        meta_sequence<std::vector<int>, int>();
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
            },
            // copy constructor
            {
                { type<glTF>(), [](Ref ref, Ref other) { new(&val<glTF>(ref)) glTF(val<glTF>(other)); } }
            },
            // members
            {
                { type<glTF>(), member_address(&glTF::m_buffers), type<std::vector<glTFBuffer>>(), "buffers", var(std::vector<glTFBuffer>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_buffer_views), type<std::vector<glTFBufferView>>(), "buffer_views", var(std::vector<glTFBufferView>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_accessors), type<std::vector<glTFAccessor>>(), "accessors", var(std::vector<glTFAccessor>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_images), type<std::vector<glTFImage>>(), "images", var(std::vector<glTFImage>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_textures), type<std::vector<glTFTexture>>(), "textures", var(std::vector<glTFTexture>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_materials), type<std::vector<glTFMaterial>>(), "materials", var(std::vector<glTFMaterial>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_meshes), type<std::vector<glTFMesh>>(), "meshes", var(std::vector<glTFMesh>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_nodes), type<std::vector<glTFNode>>(), "nodes", var(std::vector<glTFNode>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_skins), type<std::vector<glTFSkin>>(), "skins", var(std::vector<glTFSkin>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_animations), type<std::vector<glTFAnimation>>(), "animations", var(std::vector<glTFAnimation>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_cameras), type<std::vector<glTFCamera>>(), "cameras", var(std::vector<glTFCamera>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTF>(), member_address(&glTF::m_scenes), type<std::vector<glTFScene>>(), "scenes", var(std::vector<glTFScene>()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFAccessor>(), [](Ref ref, Ref other) { new(&val<glTFAccessor>(ref)) glTFAccessor(val<glTFAccessor>(other)); } }
            },
            // members
            {
                { type<glTFAccessor>(), member_address(&glTFAccessor::buffer_view), type<int>(), "buffer_view", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAccessor>(), member_address(&glTFAccessor::byte_offset), type<int>(), "byte_offset", var(int(0)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAccessor>(), member_address(&glTFAccessor::component_type), type<glTFComponentType>(), "component_type", var(glTFComponentType()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAccessor>(), member_address(&glTFAccessor::normalized), type<bool>(), "normalized", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAccessor>(), member_address(&glTFAccessor::count), type<int>(), "count", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAccessor>(), member_address(&glTFAccessor::type), type<glTFType>(), "type", var(glTFType()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAccessor>(), member_address(&glTFAccessor::sparse), type<glTFSparse>(), "sparse", var(glTFSparse()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFAnimation>(), [](Ref ref, Ref other) { new(&val<glTFAnimation>(ref)) glTFAnimation(val<glTFAnimation>(other)); } }
            },
            // members
            {
                { type<glTFAnimation>(), member_address(&glTFAnimation::name), type<std::string>(), "name", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAnimation>(), member_address(&glTFAnimation::samplers), type<std::vector<glTFAnimationSampler>>(), "samplers", var(std::vector<glTFAnimationSampler>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAnimation>(), member_address(&glTFAnimation::channels), type<std::vector<glTFAnimationChannel>>(), "channels", var(std::vector<glTFAnimationChannel>()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFAnimationChannel>(), [](Ref ref, Ref other) { new(&val<glTFAnimationChannel>(ref)) glTFAnimationChannel(val<glTFAnimationChannel>(other)); } }
            },
            // members
            {
                { type<glTFAnimationChannel>(), member_address(&glTFAnimationChannel::sampler), type<int>(), "sampler", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAnimationChannel>(), member_address(&glTFAnimationChannel::target), type<glTFAnimationTarget>(), "target", var(glTFAnimationTarget()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFAnimationSampler>(), [](Ref ref, Ref other) { new(&val<glTFAnimationSampler>(ref)) glTFAnimationSampler(val<glTFAnimationSampler>(other)); } }
            },
            // members
            {
                { type<glTFAnimationSampler>(), member_address(&glTFAnimationSampler::interpolation), type<glTFInterpolation>(), "interpolation", var(glTFInterpolation()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAnimationSampler>(), member_address(&glTFAnimationSampler::input), type<int>(), "input", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAnimationSampler>(), member_address(&glTFAnimationSampler::output), type<int>(), "output", var(int()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFAnimationTarget>(), [](Ref ref, Ref other) { new(&val<glTFAnimationTarget>(ref)) glTFAnimationTarget(val<glTFAnimationTarget>(other)); } }
            },
            // members
            {
                { type<glTFAnimationTarget>(), member_address(&glTFAnimationTarget::node), type<int>(), "node", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAnimationTarget>(), member_address(&glTFAnimationTarget::path), type<std::string>(), "path", var(std::string()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFAttributes>(), [](Ref ref, Ref other) { new(&val<glTFAttributes>(ref)) glTFAttributes(val<glTFAttributes>(other)); } }
            },
            // members
            {
                { type<glTFAttributes>(), member_address(&glTFAttributes::POSITION), type<int>(), "POSITION", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAttributes>(), member_address(&glTFAttributes::NORMAL), type<int>(), "NORMAL", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAttributes>(), member_address(&glTFAttributes::TANGENT), type<int>(), "TANGENT", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAttributes>(), member_address(&glTFAttributes::TEXCOORD_0), type<int>(), "TEXCOORD_0", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAttributes>(), member_address(&glTFAttributes::TEXCOORD_1), type<int>(), "TEXCOORD_1", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAttributes>(), member_address(&glTFAttributes::COLOR_0), type<int>(), "COLOR_0", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAttributes>(), member_address(&glTFAttributes::JOINTS_0), type<int>(), "JOINTS_0", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFAttributes>(), member_address(&glTFAttributes::WEIGHTS_0), type<int>(), "WEIGHTS_0", var(int()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFBuffer>(), [](Ref ref, Ref other) { new(&val<glTFBuffer>(ref)) glTFBuffer(val<glTFBuffer>(other)); } }
            },
            // members
            {
                { type<glTFBuffer>(), member_address(&glTFBuffer::mime_type), type<std::string>(), "mime_type", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFBuffer>(), member_address(&glTFBuffer::uri), type<std::string>(), "uri", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFBuffer>(), member_address(&glTFBuffer::byte_length), type<int>(), "byte_length", var(int()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFBufferView>(), [](Ref ref, Ref other) { new(&val<glTFBufferView>(ref)) glTFBufferView(val<glTFBufferView>(other)); } }
            },
            // members
            {
                { type<glTFBufferView>(), member_address(&glTFBufferView::buffer), type<int>(), "buffer", var(int(0)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFBufferView>(), member_address(&glTFBufferView::byte_offset), type<size_t>(), "byte_offset", var(size_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFBufferView>(), member_address(&glTFBufferView::byte_length), type<size_t>(), "byte_length", var(size_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFBufferView>(), member_address(&glTFBufferView::byte_stride), type<size_t>(), "byte_stride", var(size_t()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFBufferView>(), member_address(&glTFBufferView::target), type<int>(), "target", var(int(0)), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFCamera>(), [](Ref ref, Ref other) { new(&val<glTFCamera>(ref)) glTFCamera(val<glTFCamera>(other)); } }
            },
            // members
            {
                { type<glTFCamera>(), member_address(&glTFCamera::type), type<std::string>(), "type", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFCamera>(), member_address(&glTFCamera::orthographic), type<glTFOrthographic>(), "orthographic", var(glTFOrthographic()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFCamera>(), member_address(&glTFCamera::perspective), type<glTFPerspective>(), "perspective", var(glTFPerspective()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFImage>(), [](Ref ref, Ref other) { new(&val<glTFImage>(ref)) glTFImage(val<glTFImage>(other)); } }
            },
            // members
            {
                { type<glTFImage>(), member_address(&glTFImage::mime_type), type<std::string>(), "mime_type", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFImage>(), member_address(&glTFImage::uri), type<std::string>(), "uri", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFImage>(), member_address(&glTFImage::buffer_view), type<int>(), "buffer_view", var(int()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFMaterial>(), [](Ref ref, Ref other) { new(&val<glTFMaterial>(ref)) glTFMaterial(val<glTFMaterial>(other)); } }
            },
            // members
            {
                { type<glTFMaterial>(), member_address(&glTFMaterial::name), type<std::string>(), "name", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterial>(), member_address(&glTFMaterial::normal_texture), type<glTFTextureInfo>(), "normal_texture", var(glTFTextureInfo()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterial>(), member_address(&glTFMaterial::occlusion_texture), type<glTFTextureInfo>(), "occlusion_texture", var(glTFTextureInfo()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterial>(), member_address(&glTFMaterial::emissive_factor), type<mud::vec3>(), "emissive_factor", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterial>(), member_address(&glTFMaterial::emissive_texture), type<glTFTextureInfo>(), "emissive_texture", var(glTFTextureInfo()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterial>(), member_address(&glTFMaterial::double_sided), type<bool>(), "double_sided", var(bool(false)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterial>(), member_address(&glTFMaterial::alpha_mode), type<glTFAlphaMode>(), "alpha_mode", var(glTFAlphaMode()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterial>(), member_address(&glTFMaterial::pbr_metallic_roughness), type<glTFMaterialPBR>(), "pbr_metallic_roughness", var(glTFMaterialPBR()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFMaterialPBR>(), [](Ref ref, Ref other) { new(&val<glTFMaterialPBR>(ref)) glTFMaterialPBR(val<glTFMaterialPBR>(other)); } }
            },
            // members
            {
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::base_color_factor), type<mud::vec4>(), "base_color_factor", var(mud::vec4()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::base_color_texture), type<glTFTextureInfo>(), "base_color_texture", var(glTFTextureInfo()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::metallic_factor), type<float>(), "metallic_factor", var(float(1.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::roughness_factor), type<float>(), "roughness_factor", var(float(1.f)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMaterialPBR>(), member_address(&glTFMaterialPBR::metallic_roughness_texture), type<glTFTextureInfo>(), "metallic_roughness_texture", var(glTFTextureInfo()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFMesh>(), [](Ref ref, Ref other) { new(&val<glTFMesh>(ref)) glTFMesh(val<glTFMesh>(other)); } }
            },
            // members
            {
                { type<glTFMesh>(), member_address(&glTFMesh::primitives), type<std::vector<glTFPrimitive>>(), "primitives", var(std::vector<glTFPrimitive>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMesh>(), member_address(&glTFMesh::weights), type<std::vector<float>>(), "weights", var(std::vector<float>()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFMorphTarget>(), [](Ref ref, Ref other) { new(&val<glTFMorphTarget>(ref)) glTFMorphTarget(val<glTFMorphTarget>(other)); } }
            },
            // members
            {
                { type<glTFMorphTarget>(), member_address(&glTFMorphTarget::POSITION), type<int>(), "POSITION", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMorphTarget>(), member_address(&glTFMorphTarget::NORMAL), type<int>(), "NORMAL", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFMorphTarget>(), member_address(&glTFMorphTarget::TANGENT), type<int>(), "TANGENT", var(int()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFNode>(), [](Ref ref, Ref other) { new(&val<glTFNode>(ref)) glTFNode(val<glTFNode>(other)); } }
            },
            // members
            {
                { type<glTFNode>(), member_address(&glTFNode::name), type<std::string>(), "name", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::mesh), type<int>(), "mesh", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::camera), type<int>(), "camera", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::skin), type<int>(), "skin", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::matrix), type<mud::mat4>(), "matrix", var(mud::mat4()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::translation), type<mud::vec3>(), "translation", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::rotation), type<mud::quat>(), "rotation", var(mud::quat()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::scale), type<mud::vec3>(), "scale", var(mud::vec3()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFNode>(), member_address(&glTFNode::children), type<std::vector<int>>(), "children", var(std::vector<int>()), Member::Flags(Member::Value|Member::Mutable) }
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
    
    
        
    // glTFOrthographic
    {
        static Meta meta = { type<glTFOrthographic>(), &namspc({}), "glTFOrthographic", sizeof(glTFOrthographic), TypeClass::Struct };
        static Class cls = { type<glTFOrthographic>(),
            // bases
            {  },
            {  },
            // constructors
            {
            },
            // copy constructor
            {
                { type<glTFOrthographic>(), [](Ref ref, Ref other) { new(&val<glTFOrthographic>(ref)) glTFOrthographic(val<glTFOrthographic>(other)); } }
            },
            // members
            {
                { type<glTFOrthographic>(), member_address(&glTFOrthographic::xmag), type<float>(), "xmag", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFOrthographic>(), member_address(&glTFOrthographic::ymag), type<float>(), "ymag", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFOrthographic>(), member_address(&glTFOrthographic::zfar), type<float>(), "zfar", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFOrthographic>(), member_address(&glTFOrthographic::znear), type<float>(), "znear", var(float()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFPerspective>(), [](Ref ref, Ref other) { new(&val<glTFPerspective>(ref)) glTFPerspective(val<glTFPerspective>(other)); } }
            },
            // members
            {
                { type<glTFPerspective>(), member_address(&glTFPerspective::yfov), type<float>(), "yfov", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFPerspective>(), member_address(&glTFPerspective::zfar), type<float>(), "zfar", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFPerspective>(), member_address(&glTFPerspective::znear), type<float>(), "znear", var(float()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFPerspective>(), member_address(&glTFPerspective::aspect_ration), type<float>(), "aspect_ration", var(float()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFPrimitive>(), [](Ref ref, Ref other) { new(&val<glTFPrimitive>(ref)) glTFPrimitive(val<glTFPrimitive>(other)); } }
            },
            // members
            {
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::attributes), type<glTFAttributes>(), "attributes", var(glTFAttributes()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::indices), type<int>(), "indices", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::material), type<int>(), "material", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::mode), type<glTFPrimitiveType>(), "mode", var(glTFPrimitiveType()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFPrimitive>(), member_address(&glTFPrimitive::targets), type<std::vector<glTFMorphTarget>>(), "targets", var(std::vector<glTFMorphTarget>()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFSampler>(), [](Ref ref, Ref other) { new(&val<glTFSampler>(ref)) glTFSampler(val<glTFSampler>(other)); } }
            },
            // members
            {
                { type<glTFSampler>(), member_address(&glTFSampler::mag_filter), type<int>(), "mag_filter", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSampler>(), member_address(&glTFSampler::min_filter), type<int>(), "min_filter", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSampler>(), member_address(&glTFSampler::wrap_s), type<int>(), "wrap_s", var(int(10497)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSampler>(), member_address(&glTFSampler::wrap_t), type<int>(), "wrap_t", var(int(10497)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSampler>(), member_address(&glTFSampler::name), type<std::string>(), "name", var(std::string()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFScene>(), [](Ref ref, Ref other) { new(&val<glTFScene>(ref)) glTFScene(val<glTFScene>(other)); } }
            },
            // members
            {
                { type<glTFScene>(), member_address(&glTFScene::name), type<std::string>(), "name", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFScene>(), member_address(&glTFScene::nodes), type<std::vector<int>>(), "nodes", var(std::vector<int>()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFSkin>(), [](Ref ref, Ref other) { new(&val<glTFSkin>(ref)) glTFSkin(val<glTFSkin>(other)); } }
            },
            // members
            {
                { type<glTFSkin>(), member_address(&glTFSkin::name), type<std::string>(), "name", var(std::string()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSkin>(), member_address(&glTFSkin::skeleton), type<int>(), "skeleton", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSkin>(), member_address(&glTFSkin::joints), type<std::vector<int>>(), "joints", var(std::vector<int>()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSkin>(), member_address(&glTFSkin::inverse_bind_matrices), type<int>(), "inverse_bind_matrices", var(int()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFSparse>(), [](Ref ref, Ref other) { new(&val<glTFSparse>(ref)) glTFSparse(val<glTFSparse>(other)); } }
            },
            // members
            {
                { type<glTFSparse>(), member_address(&glTFSparse::count), type<int>(), "count", var(int(0)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSparse>(), member_address(&glTFSparse::indices), type<glTFSparseIndices>(), "indices", var(glTFSparseIndices()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSparse>(), member_address(&glTFSparse::values), type<glTFSparseValues>(), "values", var(glTFSparseValues()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFSparseIndices>(), [](Ref ref, Ref other) { new(&val<glTFSparseIndices>(ref)) glTFSparseIndices(val<glTFSparseIndices>(other)); } }
            },
            // members
            {
                { type<glTFSparseIndices>(), member_address(&glTFSparseIndices::buffer_view), type<int>(), "buffer_view", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSparseIndices>(), member_address(&glTFSparseIndices::byte_offset), type<int>(), "byte_offset", var(int(0)), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSparseIndices>(), member_address(&glTFSparseIndices::component_type), type<glTFComponentType>(), "component_type", var(glTFComponentType()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFSparseValues>(), [](Ref ref, Ref other) { new(&val<glTFSparseValues>(ref)) glTFSparseValues(val<glTFSparseValues>(other)); } }
            },
            // members
            {
                { type<glTFSparseValues>(), member_address(&glTFSparseValues::buffer_view), type<int>(), "buffer_view", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFSparseValues>(), member_address(&glTFSparseValues::byte_offset), type<int>(), "byte_offset", var(int(0)), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFTexture>(), [](Ref ref, Ref other) { new(&val<glTFTexture>(ref)) glTFTexture(val<glTFTexture>(other)); } }
            },
            // members
            {
                { type<glTFTexture>(), member_address(&glTFTexture::source), type<int>(), "source", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFTexture>(), member_address(&glTFTexture::name), type<std::string>(), "name", var(std::string()), Member::Flags(Member::Value|Member::Mutable) }
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
            },
            // copy constructor
            {
                { type<glTFTextureInfo>(), [](Ref ref, Ref other) { new(&val<glTFTextureInfo>(ref)) glTFTextureInfo(val<glTFTextureInfo>(other)); } }
            },
            // members
            {
                { type<glTFTextureInfo>(), member_address(&glTFTextureInfo::index), type<int>(), "index", var(int()), Member::Flags(Member::Value|Member::Mutable) },
                { type<glTFTextureInfo>(), member_address(&glTFTextureInfo::scale), type<float>(), "scale", var(float(1.f)), Member::Flags(Member::Value|Member::Mutable) }
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
        m.m_types.push_back(&type<std::vector<glTFAccessor>>());
        m.m_types.push_back(&type<std::vector<glTFAnimation>>());
        m.m_types.push_back(&type<std::vector<glTFAnimationChannel>>());
        m.m_types.push_back(&type<std::vector<glTFAnimationSampler>>());
        m.m_types.push_back(&type<std::vector<glTFBuffer>>());
        m.m_types.push_back(&type<std::vector<glTFBufferView>>());
        m.m_types.push_back(&type<std::vector<glTFCamera>>());
        m.m_types.push_back(&type<std::vector<glTFImage>>());
        m.m_types.push_back(&type<std::vector<glTFMaterial>>());
        m.m_types.push_back(&type<std::vector<glTFMesh>>());
        m.m_types.push_back(&type<std::vector<glTFMorphTarget>>());
        m.m_types.push_back(&type<std::vector<glTFNode>>());
        m.m_types.push_back(&type<std::vector<glTFPrimitive>>());
        m.m_types.push_back(&type<std::vector<glTFScene>>());
        m.m_types.push_back(&type<std::vector<glTFSkin>>());
        m.m_types.push_back(&type<std::vector<glTFTexture>>());
        m.m_types.push_back(&type<std::vector<int>>());
    
    }
#endif

}
