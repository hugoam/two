#include <mud/srlz.refl.h>
#include <mud/gfx.gltf.h>
#include <mud/geom.refl.h>
#include <mud/gfx.gltf.refl.h>
#include <mud/gfx.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/refl.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/infra.h>
#include <mud/type.h>
#include <mud/gltf.refl.h>


#ifdef MUD_MODULES
module mud.gfx-gltf;
#else
#include <cstddef>
#include <stl/new.h>
#endif


using namespace mud;

void mud_ImporterGltf__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ImporterGltf( *static_cast<mud::GfxSystem*>(args[0]) ); }
void mud_ImporterGltf_import(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::ImporterGltf*>(object)).import(*static_cast<mud::Import*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::ImportConfig*>(args[2])); }
void mud_ImporterGltf_import_model(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::ImporterGltf*>(object)).import_model(*static_cast<mud::Model*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::ImportConfig*>(args[2])); }
void mud_ImporterGltf_import_prefab(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::ImporterGltf*>(object)).import_prefab(*static_cast<mud::Prefab*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::ImportConfig*>(args[2])); }
void mud_ImporterGltf_repack(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::ImporterGltf*>(object)).repack(*static_cast<stl::string*>(args[0]), *static_cast<mud::ImportConfig*>(args[1])); }

namespace mud
{
	void mud_gfx_gltf_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// mud::ImporterGltf
	{
		Type& t = type<mud::ImporterGltf>();
		static Meta meta = { t, &namspc({ "mud" }), "ImporterGltf", sizeof(mud::ImporterGltf), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ImporterGltf__construct_0, { { "gfx", type<mud::GfxSystem>(),  } } }
		};
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "import", Address(), mud_ImporterGltf_import, { { "import", type<mud::Import>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<mud::ImportConfig>(),  } }, g_qvoid },
			{ t, "import_model", Address(), mud_ImporterGltf_import_model, { { "model", type<mud::Model>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<mud::ImportConfig>(),  } }, g_qvoid },
			{ t, "import_prefab", Address(), mud_ImporterGltf_import_prefab, { { "prefab", type<mud::Prefab>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<mud::ImportConfig>(),  } }, g_qvoid },
			{ t, "repack", Address(), mud_ImporterGltf_repack, { { "filepath", type<stl::string>(),  }, { "config", type<mud::ImportConfig>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, {}, methods, {}, };
	}
	
	
		m.m_types.push_back(&type<mud::ImporterGltf>());
	}
}

namespace mud
{
	mud_gfx_gltf::mud_gfx_gltf()
		: Module("mud::gfx-gltf", { &mud_infra::m(), &mud_type::m(), &mud_refl::m(), &mud_srlz::m(), &mud_math::m(), &mud_geom::m(), &mud_gfx::m(), &mud_gltf::m() })
	{
		// setup reflection meta data
		mud_gfx_gltf_meta(*this);
	}
}

#ifdef MUD_GFX_GLTF_MODULE
extern "C"
Module& getModule()
{
	return mud_gfx_gltf::m();
}
#endif
