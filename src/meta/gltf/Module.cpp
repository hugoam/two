#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gltf;
#else
#include <type/Vector.h>
#include <type/Any.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra/Module.h>
#include <meta/type/Module.h>
#include <meta/refl/Module.h>
#include <meta/srlz/Module.h>
#include <meta/math/Module.h>
#include <meta/gltf/Module.h>
#include <meta/gltf/Convert.h>
#endif

#include <gltf/Api.h>

namespace mud
{
	void mud_gltf_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<glTFAlphaMode>();
		static Meta meta = { t, &namspc({}), "glTFAlphaMode", sizeof(glTFAlphaMode), TypeClass::Enum };
		static cstring ids[] = { "OPAQUE", "MASK", "BLEND" };
		static uint32_t values[] = { 0, 1, 2 };
		static glTFAlphaMode vars[] = { glTFAlphaMode::OPAQUE, glTFAlphaMode::MASK, glTFAlphaMode::BLEND};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<glTFAlphaMode>();
	}
	{
		Type& t = type<glTFComponentType>();
		static Meta meta = { t, &namspc({}), "glTFComponentType", sizeof(glTFComponentType), TypeClass::Enum };
		static cstring ids[] = { "BYTE", "UNSIGNED_BYTE", "SHORT", "UNSIGNED_SHORT", "INT", "FLOAT" };
		static uint32_t values[] = { 5120, 5121, 5122, 5123, 5125, 5126 };
		static glTFComponentType vars[] = { glTFComponentType::BYTE, glTFComponentType::UNSIGNED_BYTE, glTFComponentType::SHORT, glTFComponentType::UNSIGNED_SHORT, glTFComponentType::INT, glTFComponentType::FLOAT};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<glTFComponentType>();
	}
	{
		Type& t = type<glTFInterpolation>();
		static Meta meta = { t, &namspc({}), "glTFInterpolation", sizeof(glTFInterpolation), TypeClass::Enum };
		static cstring ids[] = { "LINEAR", "STEP", "CATMULLROMSPLINE", "CUBIC_SPLINE" };
		static uint32_t values[] = { 0, 1, 2, 3 };
		static glTFInterpolation vars[] = { glTFInterpolation::LINEAR, glTFInterpolation::STEP, glTFInterpolation::CATMULLROMSPLINE, glTFInterpolation::CUBIC_SPLINE};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<glTFInterpolation>();
	}
	{
		Type& t = type<glTFPrimitiveType>();
		static Meta meta = { t, &namspc({}), "glTFPrimitiveType", sizeof(glTFPrimitiveType), TypeClass::Enum };
		static cstring ids[] = { "POINTS", "LINES", "LINE_LOOP", "LINE_STRIP", "TRIANGLES", "TRIANGLE_STRIP", "TRIANGLE_FAN" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6 };
		static glTFPrimitiveType vars[] = { glTFPrimitiveType::POINTS, glTFPrimitiveType::LINES, glTFPrimitiveType::LINE_LOOP, glTFPrimitiveType::LINE_STRIP, glTFPrimitiveType::TRIANGLES, glTFPrimitiveType::TRIANGLE_STRIP, glTFPrimitiveType::TRIANGLE_FAN};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<glTFPrimitiveType>();
	}
	{
		Type& t = type<glTFType>();
		static Meta meta = { t, &namspc({}), "glTFType", sizeof(glTFType), TypeClass::Enum };
		static cstring ids[] = { "SCALAR", "VEC2", "VEC3", "VEC4", "MAT2", "MAT3", "MAT4", "INVALID" };
		static uint32_t values[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
		static glTFType vars[] = { glTFType::SCALAR, glTFType::VEC2, glTFType::VEC3, glTFType::VEC4, glTFType::MAT2, glTFType::MAT3, glTFType::MAT4, glTFType::INVALID};
		static void* refs[] = { &vars[0], &vars[1], &vars[2], &vars[3], &vars[4], &vars[5], &vars[6], &vars[7]};
		static Enum enu = { t, true, ids, values, refs };
		meta_enum<glTFType>();
	}
	
	// Sequences
	{
		Type& t = type<vector<glTFAccessor>>();
		static Meta meta = { t, &namspc({}), "vector<glTFAccessor>", sizeof(vector<glTFAccessor>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFAccessor>();
		meta_vector<vector<glTFAccessor>, glTFAccessor>();
	}
	{
		Type& t = type<vector<glTFAnimation>>();
		static Meta meta = { t, &namspc({}), "vector<glTFAnimation>", sizeof(vector<glTFAnimation>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFAnimation>();
		meta_vector<vector<glTFAnimation>, glTFAnimation>();
	}
	{
		Type& t = type<vector<glTFAnimationChannel>>();
		static Meta meta = { t, &namspc({}), "vector<glTFAnimationChannel>", sizeof(vector<glTFAnimationChannel>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFAnimationChannel>();
		meta_vector<vector<glTFAnimationChannel>, glTFAnimationChannel>();
	}
	{
		Type& t = type<vector<glTFAnimationSampler>>();
		static Meta meta = { t, &namspc({}), "vector<glTFAnimationSampler>", sizeof(vector<glTFAnimationSampler>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFAnimationSampler>();
		meta_vector<vector<glTFAnimationSampler>, glTFAnimationSampler>();
	}
	{
		Type& t = type<vector<glTFBuffer>>();
		static Meta meta = { t, &namspc({}), "vector<glTFBuffer>", sizeof(vector<glTFBuffer>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFBuffer>();
		meta_vector<vector<glTFBuffer>, glTFBuffer>();
	}
	{
		Type& t = type<vector<glTFBufferView>>();
		static Meta meta = { t, &namspc({}), "vector<glTFBufferView>", sizeof(vector<glTFBufferView>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFBufferView>();
		meta_vector<vector<glTFBufferView>, glTFBufferView>();
	}
	{
		Type& t = type<vector<glTFCamera>>();
		static Meta meta = { t, &namspc({}), "vector<glTFCamera>", sizeof(vector<glTFCamera>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFCamera>();
		meta_vector<vector<glTFCamera>, glTFCamera>();
	}
	{
		Type& t = type<vector<glTFImage>>();
		static Meta meta = { t, &namspc({}), "vector<glTFImage>", sizeof(vector<glTFImage>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFImage>();
		meta_vector<vector<glTFImage>, glTFImage>();
	}
	{
		Type& t = type<vector<glTFMaterial>>();
		static Meta meta = { t, &namspc({}), "vector<glTFMaterial>", sizeof(vector<glTFMaterial>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFMaterial>();
		meta_vector<vector<glTFMaterial>, glTFMaterial>();
	}
	{
		Type& t = type<vector<glTFMesh>>();
		static Meta meta = { t, &namspc({}), "vector<glTFMesh>", sizeof(vector<glTFMesh>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFMesh>();
		meta_vector<vector<glTFMesh>, glTFMesh>();
	}
	{
		Type& t = type<vector<glTFMorphTarget>>();
		static Meta meta = { t, &namspc({}), "vector<glTFMorphTarget>", sizeof(vector<glTFMorphTarget>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFMorphTarget>();
		meta_vector<vector<glTFMorphTarget>, glTFMorphTarget>();
	}
	{
		Type& t = type<vector<glTFNode>>();
		static Meta meta = { t, &namspc({}), "vector<glTFNode>", sizeof(vector<glTFNode>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFNode>();
		meta_vector<vector<glTFNode>, glTFNode>();
	}
	{
		Type& t = type<vector<glTFPrimitive>>();
		static Meta meta = { t, &namspc({}), "vector<glTFPrimitive>", sizeof(vector<glTFPrimitive>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFPrimitive>();
		meta_vector<vector<glTFPrimitive>, glTFPrimitive>();
	}
	{
		Type& t = type<vector<glTFSampler>>();
		static Meta meta = { t, &namspc({}), "vector<glTFSampler>", sizeof(vector<glTFSampler>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFSampler>();
		meta_vector<vector<glTFSampler>, glTFSampler>();
	}
	{
		Type& t = type<vector<glTFScene>>();
		static Meta meta = { t, &namspc({}), "vector<glTFScene>", sizeof(vector<glTFScene>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFScene>();
		meta_vector<vector<glTFScene>, glTFScene>();
	}
	{
		Type& t = type<vector<glTFSkin>>();
		static Meta meta = { t, &namspc({}), "vector<glTFSkin>", sizeof(vector<glTFSkin>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFSkin>();
		meta_vector<vector<glTFSkin>, glTFSkin>();
	}
	{
		Type& t = type<vector<glTFTexture>>();
		static Meta meta = { t, &namspc({}), "vector<glTFTexture>", sizeof(vector<glTFTexture>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<glTFTexture>();
		meta_vector<vector<glTFTexture>, glTFTexture>();
	}
	{
		Type& t = type<vector<int>>();
		static Meta meta = { t, &namspc({}), "vector<int>", sizeof(vector<int>), TypeClass::Sequence };
		static Class cls = { t };
		cls.m_content = &type<int>();
		meta_vector<vector<int>, int>();
	}
	
	// glTF
	{
		Type& t = type<glTF>();
		static Meta meta = { t, &namspc({}), "glTF", sizeof(glTF), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTF>(ref)) glTF(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTF>(ref)) glTF(val<glTF>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTF::m_buffers), type<vector<glTFBuffer>>(), "buffers", var(vector<glTFBuffer>()), Member::Value, nullptr },
				{ t, member_address(&glTF::m_buffer_views), type<vector<glTFBufferView>>(), "buffer_views", var(vector<glTFBufferView>()), Member::Value, nullptr },
				{ t, member_address(&glTF::m_accessors), type<vector<glTFAccessor>>(), "accessors", var(vector<glTFAccessor>()), Member::Value, nullptr },
				{ t, member_address(&glTF::m_images), type<vector<glTFImage>>(), "images", var(vector<glTFImage>()), Member::Value, nullptr },
				{ t, member_address(&glTF::m_textures), type<vector<glTFTexture>>(), "textures", var(vector<glTFTexture>()), Member::Value, nullptr },
				{ t, member_address(&glTF::m_materials), type<vector<glTFMaterial>>(), "materials", var(vector<glTFMaterial>()), Member::Value, nullptr },
				{ t, member_address(&glTF::m_meshes), type<vector<glTFMesh>>(), "meshes", var(vector<glTFMesh>()), Member::Value, nullptr },
				{ t, member_address(&glTF::m_nodes), type<vector<glTFNode>>(), "nodes", var(vector<glTFNode>()), Member::Value, nullptr },
				{ t, member_address(&glTF::m_skins), type<vector<glTFSkin>>(), "skins", var(vector<glTFSkin>()), Member::Value, nullptr },
				{ t, member_address(&glTF::m_animations), type<vector<glTFAnimation>>(), "animations", var(vector<glTFAnimation>()), Member::Value, nullptr },
				{ t, member_address(&glTF::m_cameras), type<vector<glTFCamera>>(), "cameras", var(vector<glTFCamera>()), Member::Value, nullptr },
				{ t, member_address(&glTF::m_samplers), type<vector<glTFSampler>>(), "samplers", var(vector<glTFSampler>()), Member::Value, nullptr },
				{ t, member_address(&glTF::m_scenes), type<vector<glTFScene>>(), "scenes", var(vector<glTFScene>()), Member::Value, nullptr }
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
		Type& t = type<glTFAccessor>();
		static Meta meta = { t, &namspc({}), "glTFAccessor", sizeof(glTFAccessor), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFAccessor>(ref)) glTFAccessor(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFAccessor>(ref)) glTFAccessor(val<glTFAccessor>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFAccessor::name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFAccessor::buffer_view), type<int>(), "buffer_view", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFAccessor::byte_offset), type<int>(), "byte_offset", var(int(0)), Member::Value, nullptr },
				{ t, member_address(&glTFAccessor::component_type), type<glTFComponentType>(), "component_type", var(glTFComponentType()), Member::Value, nullptr },
				{ t, member_address(&glTFAccessor::normalized), type<bool>(), "normalized", var(bool(false)), Member::Value, nullptr },
				{ t, member_address(&glTFAccessor::count), type<int>(), "count", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFAccessor::type), type<glTFType>(), "type", var(glTFType::INVALID), Member::Value, nullptr },
				{ t, member_address(&glTFAccessor::sparse), type<glTFSparse>(), "sparse", var(glTFSparse()), Member::Value, nullptr }
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
		Type& t = type<glTFAnimation>();
		static Meta meta = { t, &namspc({}), "glTFAnimation", sizeof(glTFAnimation), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFAnimation>(ref)) glTFAnimation(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFAnimation>(ref)) glTFAnimation(val<glTFAnimation>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFAnimation::name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFAnimation::samplers), type<vector<glTFAnimationSampler>>(), "samplers", var(vector<glTFAnimationSampler>()), Member::Value, nullptr },
				{ t, member_address(&glTFAnimation::channels), type<vector<glTFAnimationChannel>>(), "channels", var(vector<glTFAnimationChannel>()), Member::Value, nullptr }
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
		Type& t = type<glTFAnimationChannel>();
		static Meta meta = { t, &namspc({}), "glTFAnimationChannel", sizeof(glTFAnimationChannel), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFAnimationChannel>(ref)) glTFAnimationChannel(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFAnimationChannel>(ref)) glTFAnimationChannel(val<glTFAnimationChannel>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFAnimationChannel::sampler), type<int>(), "sampler", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFAnimationChannel::target), type<glTFAnimationTarget>(), "target", var(glTFAnimationTarget()), Member::Value, nullptr }
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
		Type& t = type<glTFAnimationSampler>();
		static Meta meta = { t, &namspc({}), "glTFAnimationSampler", sizeof(glTFAnimationSampler), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFAnimationSampler>(ref)) glTFAnimationSampler(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFAnimationSampler>(ref)) glTFAnimationSampler(val<glTFAnimationSampler>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFAnimationSampler::interpolation), type<glTFInterpolation>(), "interpolation", var(glTFInterpolation()), Member::Value, nullptr },
				{ t, member_address(&glTFAnimationSampler::input), type<int>(), "input", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFAnimationSampler::output), type<int>(), "output", var(int()), Member::Value, nullptr }
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
		Type& t = type<glTFAnimationTarget>();
		static Meta meta = { t, &namspc({}), "glTFAnimationTarget", sizeof(glTFAnimationTarget), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFAnimationTarget>(ref)) glTFAnimationTarget(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFAnimationTarget>(ref)) glTFAnimationTarget(val<glTFAnimationTarget>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFAnimationTarget::node), type<int>(), "node", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFAnimationTarget::path), type<string>(), "path", var(string()), Member::Value, nullptr }
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
		Type& t = type<glTFAttributes>();
		static Meta meta = { t, &namspc({}), "glTFAttributes", sizeof(glTFAttributes), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFAttributes>(ref)) glTFAttributes(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFAttributes>(ref)) glTFAttributes(val<glTFAttributes>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFAttributes::POSITION), type<int>(), "POSITION", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFAttributes::NORMAL), type<int>(), "NORMAL", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFAttributes::TANGENT), type<int>(), "TANGENT", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFAttributes::TEXCOORD_0), type<int>(), "TEXCOORD_0", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFAttributes::TEXCOORD_1), type<int>(), "TEXCOORD_1", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFAttributes::COLOR_0), type<int>(), "COLOR_0", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFAttributes::JOINTS_0), type<int>(), "JOINTS_0", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFAttributes::WEIGHTS_0), type<int>(), "WEIGHTS_0", var(int()), Member::Value, nullptr }
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
		Type& t = type<glTFBuffer>();
		static Meta meta = { t, &namspc({}), "glTFBuffer", sizeof(glTFBuffer), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFBuffer>(ref)) glTFBuffer(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFBuffer>(ref)) glTFBuffer(val<glTFBuffer>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFBuffer::name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFBuffer::mime_type), type<string>(), "mime_type", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFBuffer::uri), type<string>(), "uri", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFBuffer::byte_length), type<size_t>(), "byte_length", var(size_t()), Member::Value, nullptr }
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
		Type& t = type<glTFBufferView>();
		static Meta meta = { t, &namspc({}), "glTFBufferView", sizeof(glTFBufferView), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFBufferView>(ref)) glTFBufferView(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFBufferView>(ref)) glTFBufferView(val<glTFBufferView>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFBufferView::name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFBufferView::buffer), type<int>(), "buffer", var(int(0)), Member::Value, nullptr },
				{ t, member_address(&glTFBufferView::byte_offset), type<size_t>(), "byte_offset", var(size_t(0)), Member::Value, nullptr },
				{ t, member_address(&glTFBufferView::byte_length), type<size_t>(), "byte_length", var(size_t(0)), Member::Value, nullptr },
				{ t, member_address(&glTFBufferView::byte_stride), type<size_t>(), "byte_stride", var(size_t(0)), Member::Value, nullptr },
				{ t, member_address(&glTFBufferView::target), type<int>(), "target", var(int(0)), Member::Value, nullptr }
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
		Type& t = type<glTFCamera>();
		static Meta meta = { t, &namspc({}), "glTFCamera", sizeof(glTFCamera), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFCamera>(ref)) glTFCamera(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFCamera>(ref)) glTFCamera(val<glTFCamera>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFCamera::name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFCamera::type), type<string>(), "type", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFCamera::orthographic), type<glTFOrthographic>(), "orthographic", var(glTFOrthographic()), Member::Value, nullptr },
				{ t, member_address(&glTFCamera::perspective), type<glTFPerspective>(), "perspective", var(glTFPerspective()), Member::Value, nullptr }
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
		Type& t = type<glTFImage>();
		static Meta meta = { t, &namspc({}), "glTFImage", sizeof(glTFImage), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFImage>(ref)) glTFImage(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFImage>(ref)) glTFImage(val<glTFImage>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFImage::name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFImage::mime_type), type<string>(), "mime_type", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFImage::uri), type<string>(), "uri", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFImage::buffer_view), type<int>(), "buffer_view", var(int()), Member::Value, nullptr }
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
		Type& t = type<glTFMaterial>();
		static Meta meta = { t, &namspc({}), "glTFMaterial", sizeof(glTFMaterial), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFMaterial>(ref)) glTFMaterial(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFMaterial>(ref)) glTFMaterial(val<glTFMaterial>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFMaterial::name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFMaterial::normal_texture), type<glTFTextureInfo>(), "normal_texture", var(glTFTextureInfo()), Member::Value, nullptr },
				{ t, member_address(&glTFMaterial::occlusion_texture), type<glTFTextureInfo>(), "occlusion_texture", var(glTFTextureInfo()), Member::Value, nullptr },
				{ t, member_address(&glTFMaterial::emissive_factor), type<mud::vec3>(), "emissive_factor", var(mud::vec3(to_vec3(mud::Colour::Black))), Member::Value, nullptr },
				{ t, member_address(&glTFMaterial::emissive_texture), type<glTFTextureInfo>(), "emissive_texture", var(glTFTextureInfo()), Member::Value, nullptr },
				{ t, member_address(&glTFMaterial::double_sided), type<bool>(), "double_sided", var(bool(false)), Member::Value, nullptr },
				{ t, member_address(&glTFMaterial::alpha_mode), type<glTFAlphaMode>(), "alpha_mode", var(glTFAlphaMode::OPAQUE), Member::Value, nullptr },
				{ t, member_address(&glTFMaterial::pbr_metallic_roughness), type<glTFMaterialPBR>(), "pbr_metallic_roughness", var(glTFMaterialPBR()), Member::Value, nullptr }
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
		Type& t = type<glTFMaterialPBR>();
		static Meta meta = { t, &namspc({}), "glTFMaterialPBR", sizeof(glTFMaterialPBR), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFMaterialPBR>(ref)) glTFMaterialPBR(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFMaterialPBR>(ref)) glTFMaterialPBR(val<glTFMaterialPBR>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFMaterialPBR::base_color_factor), type<mud::vec4>(), "base_color_factor", var(mud::vec4()), Member::Value, nullptr },
				{ t, member_address(&glTFMaterialPBR::base_color_texture), type<glTFTextureInfo>(), "base_color_texture", var(glTFTextureInfo()), Member::Value, nullptr },
				{ t, member_address(&glTFMaterialPBR::metallic_factor), type<float>(), "metallic_factor", var(float(1.f)), Member::Value, nullptr },
				{ t, member_address(&glTFMaterialPBR::roughness_factor), type<float>(), "roughness_factor", var(float(1.f)), Member::Value, nullptr },
				{ t, member_address(&glTFMaterialPBR::metallic_roughness_texture), type<glTFTextureInfo>(), "metallic_roughness_texture", var(glTFTextureInfo()), Member::Value, nullptr }
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
		Type& t = type<glTFMesh>();
		static Meta meta = { t, &namspc({}), "glTFMesh", sizeof(glTFMesh), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFMesh>(ref)) glTFMesh(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFMesh>(ref)) glTFMesh(val<glTFMesh>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFMesh::name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFMesh::primitives), type<vector<glTFPrimitive>>(), "primitives", var(vector<glTFPrimitive>()), Member::Value, nullptr },
				{ t, member_address(&glTFMesh::weights), type<vector<float>>(), "weights", var(vector<float>()), Member::Value, nullptr }
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
		Type& t = type<glTFMorphTarget>();
		static Meta meta = { t, &namspc({}), "glTFMorphTarget", sizeof(glTFMorphTarget), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFMorphTarget>(ref)) glTFMorphTarget(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFMorphTarget>(ref)) glTFMorphTarget(val<glTFMorphTarget>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFMorphTarget::POSITION), type<int>(), "POSITION", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFMorphTarget::NORMAL), type<int>(), "NORMAL", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFMorphTarget::TANGENT), type<int>(), "TANGENT", var(int()), Member::Value, nullptr }
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
		Type& t = type<glTFNode>();
		static Meta meta = { t, &namspc({}), "glTFNode", sizeof(glTFNode), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFNode>(ref)) glTFNode(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFNode>(ref)) glTFNode(val<glTFNode>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFNode::name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFNode::mesh), type<int>(), "mesh", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFNode::camera), type<int>(), "camera", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFNode::skin), type<int>(), "skin", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFNode::matrix), type<mud::mat4>(), "matrix", var(mud::mat4()), Member::Value, nullptr },
				{ t, member_address(&glTFNode::translation), type<mud::vec3>(), "translation", var(mud::vec3(mud::Zero3)), Member::Value, nullptr },
				{ t, member_address(&glTFNode::rotation), type<mud::quat>(), "rotation", var(mud::quat(mud::ZeroQuat)), Member::Value, nullptr },
				{ t, member_address(&glTFNode::scale), type<mud::vec3>(), "scale", var(mud::vec3(mud::Unit3)), Member::Value, nullptr },
				{ t, member_address(&glTFNode::children), type<vector<int>>(), "children", var(vector<int>()), Member::Value, nullptr }
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
		Type& t = type<glTFNodeExtras>();
		static Meta meta = { t, &namspc({}), "glTFNodeExtras", sizeof(glTFNodeExtras), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFNodeExtras>(ref)) glTFNodeExtras(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFNodeExtras>(ref)) glTFNodeExtras(val<glTFNodeExtras>(other)); } }
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
		Type& t = type<glTFOrthographic>();
		static Meta meta = { t, &namspc({}), "glTFOrthographic", sizeof(glTFOrthographic), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFOrthographic>(ref)) glTFOrthographic(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFOrthographic>(ref)) glTFOrthographic(val<glTFOrthographic>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFOrthographic::xmag), type<float>(), "xmag", var(float()), Member::Value, nullptr },
				{ t, member_address(&glTFOrthographic::ymag), type<float>(), "ymag", var(float()), Member::Value, nullptr },
				{ t, member_address(&glTFOrthographic::zfar), type<float>(), "zfar", var(float()), Member::Value, nullptr },
				{ t, member_address(&glTFOrthographic::znear), type<float>(), "znear", var(float()), Member::Value, nullptr }
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
		Type& t = type<glTFPerspective>();
		static Meta meta = { t, &namspc({}), "glTFPerspective", sizeof(glTFPerspective), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFPerspective>(ref)) glTFPerspective(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFPerspective>(ref)) glTFPerspective(val<glTFPerspective>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFPerspective::yfov), type<float>(), "yfov", var(float()), Member::Value, nullptr },
				{ t, member_address(&glTFPerspective::zfar), type<float>(), "zfar", var(float()), Member::Value, nullptr },
				{ t, member_address(&glTFPerspective::znear), type<float>(), "znear", var(float()), Member::Value, nullptr },
				{ t, member_address(&glTFPerspective::aspect_ratio), type<float>(), "aspect_ratio", var(float()), Member::Value, nullptr }
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
		Type& t = type<glTFPrimitive>();
		static Meta meta = { t, &namspc({}), "glTFPrimitive", sizeof(glTFPrimitive), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFPrimitive>(ref)) glTFPrimitive(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFPrimitive>(ref)) glTFPrimitive(val<glTFPrimitive>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFPrimitive::attributes), type<glTFAttributes>(), "attributes", var(glTFAttributes()), Member::Value, nullptr },
				{ t, member_address(&glTFPrimitive::indices), type<int>(), "indices", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFPrimitive::material), type<int>(), "material", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFPrimitive::mode), type<glTFPrimitiveType>(), "mode", var(glTFPrimitiveType::TRIANGLES), Member::Value, nullptr },
				{ t, member_address(&glTFPrimitive::targets), type<vector<glTFMorphTarget>>(), "targets", var(vector<glTFMorphTarget>()), Member::Value, nullptr }
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
		Type& t = type<glTFSampler>();
		static Meta meta = { t, &namspc({}), "glTFSampler", sizeof(glTFSampler), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFSampler>(ref)) glTFSampler(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFSampler>(ref)) glTFSampler(val<glTFSampler>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFSampler::mag_filter), type<int>(), "mag_filter", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFSampler::min_filter), type<int>(), "min_filter", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFSampler::wrap_s), type<int>(), "wrap_s", var(int(10497)), Member::Value, nullptr },
				{ t, member_address(&glTFSampler::wrap_t), type<int>(), "wrap_t", var(int(10497)), Member::Value, nullptr },
				{ t, member_address(&glTFSampler::name), type<string>(), "name", var(string()), Member::Value, nullptr }
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
		Type& t = type<glTFScene>();
		static Meta meta = { t, &namspc({}), "glTFScene", sizeof(glTFScene), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFScene>(ref)) glTFScene(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFScene>(ref)) glTFScene(val<glTFScene>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFScene::name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFScene::nodes), type<vector<int>>(), "nodes", var(vector<int>()), Member::Value, nullptr }
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
		Type& t = type<glTFSkin>();
		static Meta meta = { t, &namspc({}), "glTFSkin", sizeof(glTFSkin), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFSkin>(ref)) glTFSkin(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFSkin>(ref)) glTFSkin(val<glTFSkin>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFSkin::name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFSkin::skeleton), type<int>(), "skeleton", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFSkin::joints), type<vector<int>>(), "joints", var(vector<int>()), Member::Value, nullptr },
				{ t, member_address(&glTFSkin::inverse_bind_matrices), type<int>(), "inverse_bind_matrices", var(int()), Member::Value, nullptr }
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
		Type& t = type<glTFSparse>();
		static Meta meta = { t, &namspc({}), "glTFSparse", sizeof(glTFSparse), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFSparse>(ref)) glTFSparse(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFSparse>(ref)) glTFSparse(val<glTFSparse>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFSparse::count), type<int>(), "count", var(int(0)), Member::Value, nullptr },
				{ t, member_address(&glTFSparse::indices), type<glTFSparseIndices>(), "indices", var(glTFSparseIndices()), Member::Value, nullptr },
				{ t, member_address(&glTFSparse::values), type<glTFSparseValues>(), "values", var(glTFSparseValues()), Member::Value, nullptr }
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
		Type& t = type<glTFSparseIndices>();
		static Meta meta = { t, &namspc({}), "glTFSparseIndices", sizeof(glTFSparseIndices), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFSparseIndices>(ref)) glTFSparseIndices(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFSparseIndices>(ref)) glTFSparseIndices(val<glTFSparseIndices>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFSparseIndices::buffer_view), type<int>(), "buffer_view", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFSparseIndices::byte_offset), type<int>(), "byte_offset", var(int(0)), Member::Value, nullptr },
				{ t, member_address(&glTFSparseIndices::component_type), type<glTFComponentType>(), "component_type", var(glTFComponentType()), Member::Value, nullptr }
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
		Type& t = type<glTFSparseValues>();
		static Meta meta = { t, &namspc({}), "glTFSparseValues", sizeof(glTFSparseValues), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFSparseValues>(ref)) glTFSparseValues(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFSparseValues>(ref)) glTFSparseValues(val<glTFSparseValues>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFSparseValues::buffer_view), type<int>(), "buffer_view", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFSparseValues::byte_offset), type<int>(), "byte_offset", var(int(0)), Member::Value, nullptr }
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
		Type& t = type<glTFTexture>();
		static Meta meta = { t, &namspc({}), "glTFTexture", sizeof(glTFTexture), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFTexture>(ref)) glTFTexture(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFTexture>(ref)) glTFTexture(val<glTFTexture>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFTexture::name), type<string>(), "name", var(string()), Member::Value, nullptr },
				{ t, member_address(&glTFTexture::sampler), type<int>(), "sampler", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFTexture::source), type<int>(), "source", var(int()), Member::Value, nullptr }
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
		Type& t = type<glTFTextureInfo>();
		static Meta meta = { t, &namspc({}), "glTFTextureInfo", sizeof(glTFTextureInfo), TypeClass::Struct };
		static Class cls = { t,
			// bases
			{  },
			{  },
			// constructors
			{
				{ t, [](Ref ref, array<Var> args) { UNUSED(args); new(&val<glTFTextureInfo>(ref)) glTFTextureInfo(  ); }, {} }
			},
			// copy constructor
			{
				{ t, [](Ref ref, Ref other) { new(&val<glTFTextureInfo>(ref)) glTFTextureInfo(val<glTFTextureInfo>(other)); } }
			},
			// members
			{
				{ t, member_address(&glTFTextureInfo::index), type<int>(), "index", var(int()), Member::Value, nullptr },
				{ t, member_address(&glTFTextureInfo::scale), type<float>(), "scale", var(float(1.f)), Member::Value, nullptr }
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

namespace mud
{
	mud_gltf::mud_gltf()
		: Module("mud::gltf", { &mud_infra::m(), &mud_type::m(), &mud_refl::m(), &mud_srlz::m(), &mud_math::m() })
	{
		// setup reflection meta data
		mud_gltf_meta(*this);
	}
}

#ifdef MUD_GLTF_MODULE
extern "C"
Module& getModule()
{
		return mud_gltf::m();
}
#endif
