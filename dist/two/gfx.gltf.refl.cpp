#include <two/srlz.refl.h>
#include <two/gfx.gltf.h>
#include <two/geom.refl.h>
#include <two/gfx.gltf.refl.h>
#include <two/gfx.refl.h>
#include <two/infra.refl.h>
#include <two/type.refl.h>
#include <two/refl.refl.h>
#include <two/refl.h>
#include <two/math.refl.h>
#include <two/infra.h>
#include <two/type.h>
#include <two/gltf.refl.h>


#ifdef TWO_MODULES
module two.gfx-gltf;
#else
#include <cstddef>
#include <stl/new.h>
#endif


using namespace two;

void two_ImporterGltf__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ImporterGltf( *static_cast<two::GfxSystem*>(args[0]) ); }
void two_ImporterGltf_import(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ImporterGltf*>(object)).import(*static_cast<two::Import*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::ImportConfig*>(args[2])); }
void two_ImporterGltf_import_model(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ImporterGltf*>(object)).import_model(*static_cast<two::Model*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::ImportConfig*>(args[2])); }
void two_ImporterGltf_import_prefab(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ImporterGltf*>(object)).import_prefab(*static_cast<two::Prefab*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::ImportConfig*>(args[2])); }
void two_ImporterGltf_repack(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ImporterGltf*>(object)).repack(*static_cast<stl::string*>(args[0]), *static_cast<two::ImportConfig*>(args[1])); }

namespace two
{
	void two_gfx_gltf_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// two::ImporterGltf
	{
		Type& t = type<two::ImporterGltf>();
		static Meta meta = { t, &namspc({ "two" }), "ImporterGltf", sizeof(two::ImporterGltf), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ImporterGltf__construct_0, { { "gfx", type<two::GfxSystem>(),  } } }
		};
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "import", Address(), two_ImporterGltf_import, { { "import", type<two::Import>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<two::ImportConfig>(),  } }, g_qvoid },
			{ t, "import_model", Address(), two_ImporterGltf_import_model, { { "model", type<two::Model>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<two::ImportConfig>(),  } }, g_qvoid },
			{ t, "import_prefab", Address(), two_ImporterGltf_import_prefab, { { "prefab", type<two::Prefab>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<two::ImportConfig>(),  } }, g_qvoid },
			{ t, "repack", Address(), two_ImporterGltf_repack, { { "filepath", type<stl::string>(),  }, { "config", type<two::ImportConfig>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, {}, methods, {}, };
	}
	
	
		m.m_types.push_back(&type<two::ImporterGltf>());
	}
}

namespace two
{
	two_gfx_gltf::two_gfx_gltf()
		: Module("two::gfx-gltf", { &two_infra::m(), &two_type::m(), &two_refl::m(), &two_srlz::m(), &two_math::m(), &two_geom::m(), &two_gfx::m(), &two_gltf::m() })
	{
		// setup reflection meta data
		two_gfx_gltf_meta(*this);
	}
}

#ifdef TWO_GFX_GLTF_MODULE
extern "C"
Module& getModule()
{
	return two_gfx_gltf::m();
}
#endif
