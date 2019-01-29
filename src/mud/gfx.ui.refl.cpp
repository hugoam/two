#include <mud/tree.refl.h>
#include <mud/geom.refl.h>
#include <mud/ui.refl.h>
#include <mud/gfx.refl.h>
#include <mud/infra.refl.h>
#include <mud/type.refl.h>
#include <mud/ctx.refl.h>
#include <mud/gfx.ui.refl.h>
#include <mud/refl.h>
#include <mud/math.refl.h>
#include <mud/gfx.ui.h>
#include <mud/infra.h>
#include <mud/type.h>

#ifdef MUD_MODULES
module mud.gfx-ui;
#else
#endif


using namespace mud;

void mud_ui_OrbitMode__to_string(void* val, string& str) { str = g_enu[type<mud::ui::OrbitMode>().m_id]->name(uint32_t((*static_cast<mud::ui::OrbitMode*>(val)))); }
void mud_ui_OrbitMode__to_value(const string& str, void* val) { (*static_cast<mud::ui::OrbitMode*>(val)) = mud::ui::OrbitMode(g_enu[type<mud::ui::OrbitMode>().m_id]->value(str.c_str())); }
void mud_OrbitController_set_eye(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::OrbitController*>(object)).set_eye(*static_cast<mud::quat*>(args[0])); }
void mud_OrbitController_set_target(void* object, array<void*> args, void*& result) { UNUSED(result); (*static_cast<mud::OrbitController*>(object)).set_target(*static_cast<mud::vec3*>(args[0])); }
void mud_ui_viewer_0(array<void*> args, void*& result) { result = &mud::ui::viewer(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::Scene*>(args[1])); }
void mud_ui_scene_viewer_1(array<void*> args, void*& result) { result = &mud::ui::scene_viewer(*static_cast<mud::Widget*>(args[0]), *static_cast<mud::vec2*>(args[1])); }
void mud_ui_orbit_controller_2(array<void*> args, void*& result) { result = &mud::ui::orbit_controller(*static_cast<mud::Viewer*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3])); }
void mud_ui_free_orbit_controller_3(array<void*> args, void*& result) { result = &mud::ui::free_orbit_controller(*static_cast<mud::Viewer*>(args[0])); }
void mud_ui_isometric_controller_4(array<void*> args, void*& result) { result = &mud::ui::isometric_controller(*static_cast<mud::Viewer*>(args[0]), *static_cast<bool*>(args[1])); }
void mud_ui_hybrid_controller_5(array<void*> args, void*& result) { result = &mud::ui::hybrid_controller(*static_cast<mud::Viewer*>(args[0]), *static_cast<mud::ui::OrbitMode*>(args[1]), *static_cast<mud::Transform*>(args[2]), *static_cast<bool*>(args[3]), *static_cast<mud::vec2*>(args[4]), *static_cast<bool*>(args[5])); }
void mud_ui_velocity_controller_6(array<void*> args, void*& result) { UNUSED(result);  mud::ui::velocity_controller(*static_cast<mud::Viewer*>(args[0]), *static_cast<mud::vec3*>(args[1]), *static_cast<mud::vec3*>(args[2]), *static_cast<float*>(args[3])); }

namespace mud
{
	void mud_gfx_ui_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<mud::ui::OrbitMode>();
		static Meta meta = { t, &namspc({ "mud", "ui" }), "OrbitMode", sizeof(mud::ui::OrbitMode), TypeClass::Enum };
		static cstring ids[] = { "ThirdPerson", "Isometric", "PseudoIsometric" };
		static uint32_t values[] = { 0, 1, 2 };
		static mud::ui::OrbitMode vars[] = { mud::ui::OrbitMode::ThirdPerson, mud::ui::OrbitMode::Isometric, mud::ui::OrbitMode::PseudoIsometric};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { mud_ui_OrbitMode__to_string,
		                           mud_ui_OrbitMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	
	// mud::ViewerController
	{
		Type& t = type<mud::ViewerController>();
		static Meta meta = { t, &namspc({ "mud" }), "ViewerController", sizeof(mud::ViewerController), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// mud::OrbitController
	{
		Type& t = type<mud::OrbitController>();
		static Meta meta = { t, &namspc({ "mud" }), "OrbitController", sizeof(mud::OrbitController), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::ViewerController>() };
		static size_t bases_offsets[] = { base_offset<mud::OrbitController, mud::ViewerController>() };
		// defaults
		static mud::vec3 position_default = Zero3;
		static float yaw_default = 0.f;
		static float pitch_default = 0.f;
		static float distance_default = 1.f;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::OrbitController, m_position), type<mud::vec3>(), "position", &position_default, Member::Value, nullptr },
			{ t, offsetof(mud::OrbitController, m_yaw), type<float>(), "yaw", &yaw_default, Member::Value, nullptr },
			{ t, offsetof(mud::OrbitController, m_pitch), type<float>(), "pitch", &pitch_default, Member::Value, nullptr },
			{ t, offsetof(mud::OrbitController, m_distance), type<float>(), "distance", &distance_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "set_eye", Address(), mud_OrbitController_set_eye, { { "rotation", type<mud::quat>(),  } }, g_qvoid },
			{ t, "set_target", Address(), mud_OrbitController_set_target, { { "position", type<mud::vec3>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, methods, {}, };
	}
	// mud::FreeOrbitController
	{
		Type& t = type<mud::FreeOrbitController>();
		static Meta meta = { t, &namspc({ "mud" }), "FreeOrbitController", sizeof(mud::FreeOrbitController), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::OrbitController>() };
		static size_t bases_offsets[] = { base_offset<mud::FreeOrbitController, mud::OrbitController>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::SpaceSheet
	{
		Type& t = type<mud::SpaceSheet>();
		static Meta meta = { t, &namspc({ "mud" }), "SpaceSheet", sizeof(mud::SpaceSheet), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Ui>() };
		static size_t bases_offsets[] = { base_offset<mud::SpaceSheet, mud::Ui>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// mud::Viewer
	{
		Type& t = type<mud::Viewer>();
		static Meta meta = { t, &namspc({ "mud" }), "Viewer", sizeof(mud::Viewer), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Widget>() };
		static size_t bases_offsets[] = { base_offset<mud::Viewer, mud::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(mud::Viewer, m_scene), type<mud::Scene>(), "scene", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(mud::Viewer, m_viewport), type<mud::Viewport>(), "viewport", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(mud::Viewer, m_position), type<mud::vec2>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(mud::Viewer, m_size), type<mud::vec2>(), "size", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, {}, {}, };
	}
	// mud::SceneViewer
	{
		Type& t = type<mud::SceneViewer>();
		static Meta meta = { t, &namspc({ "mud" }), "SceneViewer", sizeof(mud::SceneViewer), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<mud::Scene>(), &type<mud::Viewer>() };
		static size_t bases_offsets[] = { base_offset<mud::SceneViewer, mud::Scene>(), base_offset<mud::SceneViewer, mud::Viewer>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
		m.m_types.push_back(&type<mud::ui::OrbitMode>());
		m.m_types.push_back(&type<mud::ViewerController>());
		m.m_types.push_back(&type<mud::OrbitController>());
		m.m_types.push_back(&type<mud::FreeOrbitController>());
		m.m_types.push_back(&type<mud::SpaceSheet>());
		m.m_types.push_back(&type<mud::Viewer>());
		m.m_types.push_back(&type<mud::SceneViewer>());
		{
			static Function f = { &namspc({ "mud", "ui" }), "viewer", nullptr, mud_ui_viewer_0, { { "parent", type<mud::Widget>(),  }, { "scene", type<mud::Scene>(),  } }, { &type<mud::Viewer>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "scene_viewer", nullptr, mud_ui_scene_viewer_1, { { "parent", type<mud::Widget>(),  }, { "size", type<mud::vec2>(), Param::Default } }, { &type<mud::SceneViewer>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "orbit_controller", nullptr, mud_ui_orbit_controller_2, { { "viewer", type<mud::Viewer>(),  }, { "yaw", type<float>(),  }, { "pitch", type<float>(),  }, { "distance", type<float>(), Param::Default } }, { &type<mud::OrbitController>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "free_orbit_controller", nullptr, mud_ui_free_orbit_controller_3, { { "viewer", type<mud::Viewer>(),  } }, { &type<mud::FreeOrbitController>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "isometric_controller", nullptr, mud_ui_isometric_controller_4, { { "viewer", type<mud::Viewer>(),  }, { "topdown", type<bool>(), Param::Default } }, { &type<mud::OrbitController>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "hybrid_controller", nullptr, mud_ui_hybrid_controller_5, { { "viewer", type<mud::Viewer>(),  }, { "mode", type<mud::ui::OrbitMode>(),  }, { "entity", type<mud::Transform>(),  }, { "aiming", type<bool>(),  }, { "angles", type<mud::vec2>(),  }, { "modal", type<bool>(), Param::Default } }, { &type<mud::OrbitController>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "mud", "ui" }), "velocity_controller", nullptr, mud_ui_velocity_controller_6, { { "viewer", type<mud::Viewer>(),  }, { "linear", type<mud::vec3>(),  }, { "angular", type<mud::vec3>(),  }, { "speed", type<float>(), Param::Default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace mud
{
	mud_gfx_ui::mud_gfx_ui()
		: Module("mud::gfx-ui", { &mud_infra::m(), &mud_tree::m(), &mud_type::m(), &mud_math::m(), &mud_geom::m(), &mud_ctx::m(), &mud_ui::m(), &mud_gfx::m() })
	{
		// setup reflection meta data
		mud_gfx_ui_meta(*this);
	}
}

#ifdef MUD_GFX_UI_MODULE
extern "C"
Module& getModule()
{
		return mud_gfx_ui::m();
}
#endif
