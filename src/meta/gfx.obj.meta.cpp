#include <infra/Cpp20.h>

#ifdef MUD_MODULES
module mud.gfx-obj;
#else
#include <cstddef>
#include <stl/new.h>
#include <infra/ToString.h>
#include <infra/ToValue.h>
#include <type/Vector.h>
#include <refl/MetaDecl.h>
#include <refl/Module.h>
#include <meta/infra.meta.h>
#include <meta/type.meta.h>
#include <meta/srlz.meta.h>
#include <meta/math.meta.h>
#include <meta/geom.meta.h>
#include <meta/gfx.meta.h>
#include <meta/gfx.obj.meta.h>
#include <meta/gfx.obj.conv.h>
#endif

#include <gfx-obj/Api.h>

using namespace mud;

void mud_ImporterOBJ__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ImporterOBJ( *static_cast<mud::GfxSystem*>(args[0]) ); }
void mud_ImporterOBJ_import(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::ImporterOBJ*>(object)).import(*static_cast<mud::Import*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::ImportConfig*>(args[2])); }
void mud_ImporterOBJ_import_model(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::ImporterOBJ*>(object)).import_model(*static_cast<mud::Model*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::ImportConfig*>(args[2])); }
void mud_ImporterOBJ_import_prefab(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::ImporterOBJ*>(object)).import_prefab(*static_cast<mud::Prefab*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::ImportConfig*>(args[2])); }
void mud_ImporterOBJ_repack(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::ImporterOBJ*>(object)).repack(*static_cast<stl::string*>(args[0]), *static_cast<mud::ImportConfig*>(args[1])); }
void mud_ImporterPLY__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) mud::ImporterPLY( *static_cast<mud::GfxSystem*>(args[0]) ); }
void mud_ImporterPLY_import(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::ImporterPLY*>(object)).import(*static_cast<mud::Import*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::ImportConfig*>(args[2])); }
void mud_ImporterPLY_import_model(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::ImporterPLY*>(object)).import_model(*static_cast<mud::Model*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::ImportConfig*>(args[2])); }
void mud_ImporterPLY_import_prefab(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::ImporterPLY*>(object)).import_prefab(*static_cast<mud::Prefab*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<mud::ImportConfig*>(args[2])); }
void mud_ImporterPLY_repack(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::ImporterPLY*>(object)).repack(*static_cast<stl::string*>(args[0]), *static_cast<mud::ImportConfig*>(args[1])); }

namespace mud
{
	void mud_gfx_obj_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// mud::ImporterOBJ
	{
		Type& t = type<mud::ImporterOBJ>();
		static Meta meta = { t, &namspc({ "mud" }), "ImporterOBJ", sizeof(mud::ImporterOBJ), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ImporterOBJ__construct_0, { { "gfx", type<mud::GfxSystem>(),  } } }
		};
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "import", Address(), mud_ImporterOBJ_import, { { "import", type<mud::Import>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<mud::ImportConfig>(),  } }, g_qvoid },
			{ t, "import_model", Address(), mud_ImporterOBJ_import_model, { { "model", type<mud::Model>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<mud::ImportConfig>(),  } }, g_qvoid },
			{ t, "import_prefab", Address(), mud_ImporterOBJ_import_prefab, { { "prefab", type<mud::Prefab>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<mud::ImportConfig>(),  } }, g_qvoid },
			{ t, "repack", Address(), mud_ImporterOBJ_repack, { { "filepath", type<stl::string>(),  }, { "config", type<mud::ImportConfig>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, {}, methods, {}, };
	}
	// mud::ImporterPLY
	{
		Type& t = type<mud::ImporterPLY>();
		static Meta meta = { t, &namspc({ "mud" }), "ImporterPLY", sizeof(mud::ImporterPLY), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, mud_ImporterPLY__construct_0, { { "gfx", type<mud::GfxSystem>(),  } } }
		};
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "import", Address(), mud_ImporterPLY_import, { { "import", type<mud::Import>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<mud::ImportConfig>(),  } }, g_qvoid },
			{ t, "import_model", Address(), mud_ImporterPLY_import_model, { { "model", type<mud::Model>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<mud::ImportConfig>(),  } }, g_qvoid },
			{ t, "import_prefab", Address(), mud_ImporterPLY_import_prefab, { { "prefab", type<mud::Prefab>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<mud::ImportConfig>(),  } }, g_qvoid },
			{ t, "repack", Address(), mud_ImporterPLY_repack, { { "filepath", type<stl::string>(),  }, { "config", type<mud::ImportConfig>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, {}, methods, {}, };
	}
	
	
		m.m_types.push_back(&type<mud::ImporterOBJ>());
		m.m_types.push_back(&type<mud::ImporterPLY>());
	}
}

namespace mud
{
	mud_gfx_obj::mud_gfx_obj()
		: Module("mud::gfx-obj", { &mud_infra::m(), &mud_type::m(), &mud_srlz::m(), &mud_math::m(), &mud_geom::m(), &mud_gfx::m() })
	{
		// setup reflection meta data
		mud_gfx_obj_meta(*this);
	}
}

#ifdef MUD_GFX_OBJ_MODULE
extern "C"
Module& getModule()
{
	return mud_gfx_obj::m();
}
#endif
