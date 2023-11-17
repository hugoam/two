#include <two/infra.h>

module;
module TWO2(gfx.obj, meta);

using namespace two;

void two_ImporterOBJ__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ImporterOBJ( *static_cast<two::GfxSystem*>(args[0]) ); }
void two_ImporterOBJ_import(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ImporterOBJ*>(object)).import(*static_cast<two::Import*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::ImportConfig*>(args[2])); }
void two_ImporterOBJ_import_model(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ImporterOBJ*>(object)).import_model(*static_cast<two::Model*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::ImportConfig*>(args[2])); }
void two_ImporterOBJ_import_prefab(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ImporterOBJ*>(object)).import_prefab(*static_cast<two::Prefab*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::ImportConfig*>(args[2])); }
void two_ImporterOBJ_repack(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ImporterOBJ*>(object)).repack(*static_cast<stl::string*>(args[0]), *static_cast<two::ImportConfig*>(args[1])); }
void two_ImporterPLY__construct_0(void* ref, span<void*> args) { new(stl::placeholder(), ref) two::ImporterPLY( *static_cast<two::GfxSystem*>(args[0]) ); }
void two_ImporterPLY_import(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ImporterPLY*>(object)).import(*static_cast<two::Import*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::ImportConfig*>(args[2])); }
void two_ImporterPLY_import_model(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ImporterPLY*>(object)).import_model(*static_cast<two::Model*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::ImportConfig*>(args[2])); }
void two_ImporterPLY_import_prefab(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ImporterPLY*>(object)).import_prefab(*static_cast<two::Prefab*>(args[0]), *static_cast<stl::string*>(args[1]), *static_cast<two::ImportConfig*>(args[2])); }
void two_ImporterPLY_repack(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::ImporterPLY*>(object)).repack(*static_cast<stl::string*>(args[0]), *static_cast<two::ImportConfig*>(args[1])); }

namespace two
{
	void two_gfx_obj_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	
	// Sequences
	
	// two::ImporterOBJ
	{
		Type& t = type<two::ImporterOBJ>();
		static Meta meta = { t, &namspc({ "two" }), "ImporterOBJ", sizeof(two::ImporterOBJ), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ImporterOBJ__construct_0, { { "gfx", type<two::GfxSystem>(),  } } }
		};
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "import", Address(), two_ImporterOBJ_import, { { "import", type<two::Import>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<two::ImportConfig>(),  } }, g_qvoid },
			{ t, "import_model", Address(), two_ImporterOBJ_import_model, { { "model", type<two::Model>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<two::ImportConfig>(),  } }, g_qvoid },
			{ t, "import_prefab", Address(), two_ImporterOBJ_import_prefab, { { "prefab", type<two::Prefab>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<two::ImportConfig>(),  } }, g_qvoid },
			{ t, "repack", Address(), two_ImporterOBJ_repack, { { "filepath", type<stl::string>(),  }, { "config", type<two::ImportConfig>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, {}, methods, {}, };
	}
	// two::ImporterPLY
	{
		Type& t = type<two::ImporterPLY>();
		static Meta meta = { t, &namspc({ "two" }), "ImporterPLY", sizeof(two::ImporterPLY), TypeClass::Object };
		// bases
		// defaults
		// constructors
		static Constructor constructors[] = {
			{ t, two_ImporterPLY__construct_0, { { "gfx", type<two::GfxSystem>(),  } } }
		};
		// copy constructor
		// members
		// methods
		static Method methods[] = {
			{ t, "import", Address(), two_ImporterPLY_import, { { "import", type<two::Import>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<two::ImportConfig>(),  } }, g_qvoid },
			{ t, "import_model", Address(), two_ImporterPLY_import_model, { { "model", type<two::Model>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<two::ImportConfig>(),  } }, g_qvoid },
			{ t, "import_prefab", Address(), two_ImporterPLY_import_prefab, { { "prefab", type<two::Prefab>(),  }, { "filepath", type<stl::string>(),  }, { "config", type<two::ImportConfig>(),  } }, g_qvoid },
			{ t, "repack", Address(), two_ImporterPLY_repack, { { "filepath", type<stl::string>(),  }, { "config", type<two::ImportConfig>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, {}, {}, constructors, {}, {}, methods, {}, };
	}
	
	
		m.m_types.push_back(&type<two::ImporterOBJ>());
		m.m_types.push_back(&type<two::ImporterPLY>());
	}
}

namespace two
{
	two_gfx_obj::two_gfx_obj()
		: Module("two::gfx-obj", { &two_infra::m(), &two_type::m(), &two_srlz::m(), &two_math::m(), &two_geom::m(), &two_gfx::m() })
	{
		// setup reflection meta data
		two_gfx_obj_meta(*this);
	}
}

#ifdef TWO_GFX_OBJ_MODULE
extern "C"
Module& getModule()
{
	return two_gfx_obj::m();
}
#endif
