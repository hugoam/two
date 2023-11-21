module;
#include <infra/Cpp20.h>
module two.gfx.ui.meta;

using namespace two;

void two_ui_OrbitMode__to_string(void* val, string& str) { str = g_enu[type<two::ui::OrbitMode>().m_id]->name(uint32_t((*static_cast<two::ui::OrbitMode*>(val)))); }
void two_ui_OrbitMode__to_value(const string& str, void* val) { (*static_cast<two::ui::OrbitMode*>(val)) = two::ui::OrbitMode(g_enu[type<two::ui::OrbitMode>().m_id]->value(str.c_str())); }
void two_OrbitController_set_eye(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::OrbitController*>(object)).set_eye(*static_cast<two::quat*>(args[0])); }
void two_OrbitController_set_target(void* object, span<void*> args, void*& result) { UNUSED(result); (*static_cast<two::OrbitController*>(object)).set_target(*static_cast<two::vec3*>(args[0])); }
void two_ui_viewer_0(span<void*> args, void*& result) { result = &two::ui::viewer(*static_cast<two::Widget*>(args[0]), *static_cast<two::Scene*>(args[1])); }
void two_ui_scene_viewer_1(span<void*> args, void*& result) { result = &two::ui::scene_viewer(*static_cast<two::Widget*>(args[0]), *static_cast<two::vec2*>(args[1])); }
void two_ui_trackball_controller_2(span<void*> args, void*& result) { result = &two::ui::trackball_controller(*static_cast<two::Viewer*>(args[0])); }
void two_ui_orbit_controls_3(span<void*> args, void*& result) { result = &two::ui::orbit_controls(*static_cast<two::Viewer*>(args[0])); }
void two_ui_orbit_controller_4(span<void*> args, void*& result) { result = &two::ui::orbit_controller(*static_cast<two::Viewer*>(args[0]), *static_cast<float*>(args[1]), *static_cast<float*>(args[2]), *static_cast<float*>(args[3])); }
void two_ui_free_orbit_controller_5(span<void*> args, void*& result) { result = &two::ui::free_orbit_controller(*static_cast<two::Viewer*>(args[0])); }
void two_ui_isometric_controller_6(span<void*> args, void*& result) { result = &two::ui::isometric_controller(*static_cast<two::Viewer*>(args[0]), *static_cast<bool*>(args[1])); }
void two_ui_hybrid_controller_7(span<void*> args, void*& result) { result = &two::ui::hybrid_controller(*static_cast<two::Viewer*>(args[0]), *static_cast<two::ui::OrbitMode*>(args[1]), *static_cast<two::Transform*>(args[2]), *static_cast<bool*>(args[3]), *static_cast<two::vec2*>(args[4]), *static_cast<bool*>(args[5])); }
void two_ui_velocity_controller_8(span<void*> args, void*& result) { UNUSED(result);  two::ui::velocity_controller(*static_cast<two::Viewer*>(args[0]), *static_cast<two::vec3*>(args[1]), *static_cast<two::vec3*>(args[2]), *static_cast<float*>(args[3])); }

namespace two
{
	void two_gfx_ui_meta(Module& m)
	{
	UNUSED(m);
	
	// Base Types
	
	// Enums
	{
		Type& t = type<two::ui::OrbitMode>();
		static Meta meta = { t, &namspc({ "two", "ui" }), "OrbitMode", sizeof(two::ui::OrbitMode), TypeClass::Enum };
		static cstring ids[] = { "ThirdPerson", "Isometric", "PseudoIsometric" };
		static uint32_t values[] = { 0, 1, 2 };
		static two::ui::OrbitMode vars[] = { two::ui::OrbitMode::ThirdPerson, two::ui::OrbitMode::Isometric, two::ui::OrbitMode::PseudoIsometric};
		static void* refs[] = { &vars[0], &vars[1], &vars[2]};
		static Enum enu = { t, true, ids, values, refs };
		static Convert convert = { two_ui_OrbitMode__to_string,
		                           two_ui_OrbitMode__to_value };
		g_convert[t.m_id] = &convert;
	}
	
	// Sequences
	
	// two::SpaceSheet
	{
		Type& t = type<two::SpaceSheet>();
		static Meta meta = { t, &namspc({ "two" }), "SpaceSheet", sizeof(two::SpaceSheet), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Ui>() };
		static size_t bases_offsets[] = { base_offset<two::SpaceSheet, two::Ui>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::ViewerController
	{
		Type& t = type<two::ViewerController>();
		static Meta meta = { t, &namspc({ "two" }), "ViewerController", sizeof(two::ViewerController), TypeClass::Object };
		// bases
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, {}, {}, {}, {}, {}, {}, {}, };
	}
	// two::Viewer
	{
		Type& t = type<two::Viewer>();
		static Meta meta = { t, &namspc({ "two" }), "Viewer", sizeof(two::Viewer), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Widget>() };
		static size_t bases_offsets[] = { base_offset<two::Viewer, two::Widget>() };
		// defaults
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::Viewer, m_scene), type<two::Scene>(), "scene", nullptr, Member::Flags(Member::Pointer|Member::Link), nullptr },
			{ t, offsetof(two::Viewer, m_camera), type<two::Camera>(), "camera", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Viewer, m_viewport), type<two::Viewport>(), "viewport", nullptr, Member::NonMutable, nullptr },
			{ t, offsetof(two::Viewer, m_position), type<two::vec2>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::Viewer, m_size), type<two::vec2>(), "size", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, {}, {}, };
	}
	// two::SceneViewer
	{
		Type& t = type<two::SceneViewer>();
		static Meta meta = { t, &namspc({ "two" }), "SceneViewer", sizeof(two::SceneViewer), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::Viewer>() };
		static size_t bases_offsets[] = { base_offset<two::SceneViewer, two::Viewer>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::OrbitController
	{
		Type& t = type<two::OrbitController>();
		static Meta meta = { t, &namspc({ "two" }), "OrbitController", sizeof(two::OrbitController), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ViewerController>() };
		static size_t bases_offsets[] = { base_offset<two::OrbitController, two::ViewerController>() };
		// defaults
		static float yaw_default = 0.f;
		static float pitch_default = 0.f;
		static float distance_default = 1.f;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::OrbitController, m_position), type<two::vec3>(), "position", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::OrbitController, m_yaw), type<float>(), "yaw", &yaw_default, Member::Value, nullptr },
			{ t, offsetof(two::OrbitController, m_pitch), type<float>(), "pitch", &pitch_default, Member::Value, nullptr },
			{ t, offsetof(two::OrbitController, m_distance), type<float>(), "distance", &distance_default, Member::Value, nullptr }
		};
		// methods
		static Method methods[] = {
			{ t, "set_eye", Address(), two_OrbitController_set_eye, { { "rotation", type<two::quat>(),  } }, g_qvoid },
			{ t, "set_target", Address(), two_OrbitController_set_target, { { "position", type<two::vec3>(),  } }, g_qvoid }
		};
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, methods, {}, };
	}
	// two::TrackballController
	{
		Type& t = type<two::TrackballController>();
		static Meta meta = { t, &namspc({ "two" }), "TrackballController", sizeof(two::TrackballController), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ViewerController>() };
		static size_t bases_offsets[] = { base_offset<two::TrackballController, two::ViewerController>() };
		// defaults
		static float rotateSpeed_default = 1.0f;
		static float zoomSpeed_default = 1.2f;
		static float panSpeed_default = 0.3f;
		static bool staticMoving_default = false;
		static float dynamicDampingFactor_default = 0.2f;
		static float minDistance_default = 0.f;
		// constructors
		// copy constructor
		// members
		static Member members[] = {
			{ t, offsetof(two::TrackballController, m_rotateSpeed), type<float>(), "rotateSpeed", &rotateSpeed_default, Member::Value, nullptr },
			{ t, offsetof(two::TrackballController, m_zoomSpeed), type<float>(), "zoomSpeed", &zoomSpeed_default, Member::Value, nullptr },
			{ t, offsetof(two::TrackballController, m_panSpeed), type<float>(), "panSpeed", &panSpeed_default, Member::Value, nullptr },
			{ t, offsetof(two::TrackballController, m_staticMoving), type<bool>(), "staticMoving", &staticMoving_default, Member::Value, nullptr },
			{ t, offsetof(two::TrackballController, m_dynamicDampingFactor), type<float>(), "dynamicDampingFactor", &dynamicDampingFactor_default, Member::Value, nullptr },
			{ t, offsetof(two::TrackballController, m_minDistance), type<float>(), "minDistance", &minDistance_default, Member::Value, nullptr },
			{ t, offsetof(two::TrackballController, m_maxDistance), type<float>(), "maxDistance", nullptr, Member::Value, nullptr },
			{ t, offsetof(two::TrackballController, m_target), type<two::vec3>(), "target", nullptr, Member::Value, nullptr }
		};
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, members, {}, {}, };
	}
	// two::OrbitControls
	{
		Type& t = type<two::OrbitControls>();
		static Meta meta = { t, &namspc({ "two" }), "OrbitControls", sizeof(two::OrbitControls), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::ViewerController>() };
		static size_t bases_offsets[] = { base_offset<two::OrbitControls, two::ViewerController>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	// two::FreeOrbitController
	{
		Type& t = type<two::FreeOrbitController>();
		static Meta meta = { t, &namspc({ "two" }), "FreeOrbitController", sizeof(two::FreeOrbitController), TypeClass::Object };
		// bases
		static Type* bases[] = { &type<two::OrbitController>() };
		static size_t bases_offsets[] = { base_offset<two::FreeOrbitController, two::OrbitController>() };
		// defaults
		// constructors
		// copy constructor
		// members
		// methods
		// static members
		static Class cls = { t, bases, bases_offsets, {}, {}, {}, {}, {}, };
	}
	
	
		m.m_types.push_back(&type<two::SpaceSheet>());
		m.m_types.push_back(&type<two::ViewerController>());
		m.m_types.push_back(&type<two::Viewer>());
		m.m_types.push_back(&type<two::SceneViewer>());
		m.m_types.push_back(&type<two::OrbitController>());
		m.m_types.push_back(&type<two::TrackballController>());
		m.m_types.push_back(&type<two::OrbitControls>());
		m.m_types.push_back(&type<two::FreeOrbitController>());
		m.m_types.push_back(&type<two::ui::OrbitMode>());
		{
			static Function f = { &namspc({ "two", "ui" }), "viewer", funcptr<two::Viewer&(*)(two::Widget&, two::Scene&)>(two::ui::viewer), two_ui_viewer_0, { { "parent", type<two::Widget>(),  }, { "scene", type<two::Scene>(),  } }, { &type<two::Viewer>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static two::vec2 size_default = vec2(0.f);
			static Function f = { &namspc({ "two", "ui" }), "scene_viewer", funcptr<two::SceneViewer&(*)(two::Widget&, const two::vec2&)>(two::ui::scene_viewer), two_ui_scene_viewer_1, { { "parent", type<two::Widget>(),  }, { "size", type<two::vec2>(), Param::Default, &size_default } }, { &type<two::SceneViewer>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "trackball_controller", funcptr<two::TrackballController&(*)(two::Viewer&)>(two::ui::trackball_controller), two_ui_trackball_controller_2, { { "viewer", type<two::Viewer>(),  } }, { &type<two::TrackballController>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "orbit_controls", funcptr<two::OrbitControls&(*)(two::Viewer&)>(two::ui::orbit_controls), two_ui_orbit_controls_3, { { "viewer", type<two::Viewer>(),  } }, { &type<two::OrbitControls>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float yaw_default = c_pi4;
			static float pitch_default = -c_pi4;
			static float distance_default = 10.f;
			static Function f = { &namspc({ "two", "ui" }), "orbit_controller", funcptr<two::OrbitController&(*)(two::Viewer&, float, float, float)>(two::ui::orbit_controller), two_ui_orbit_controller_4, { { "viewer", type<two::Viewer>(),  }, { "yaw", type<float>(), Param::Default, &yaw_default }, { "pitch", type<float>(), Param::Default, &pitch_default }, { "distance", type<float>(), Param::Default, &distance_default } }, { &type<two::OrbitController>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static Function f = { &namspc({ "two", "ui" }), "free_orbit_controller", funcptr<two::FreeOrbitController&(*)(two::Viewer&)>(two::ui::free_orbit_controller), two_ui_free_orbit_controller_5, { { "viewer", type<two::Viewer>(),  } }, { &type<two::FreeOrbitController>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool topdown_default = false;
			static Function f = { &namspc({ "two", "ui" }), "isometric_controller", funcptr<two::OrbitController&(*)(two::Viewer&, bool)>(two::ui::isometric_controller), two_ui_isometric_controller_6, { { "viewer", type<two::Viewer>(),  }, { "topdown", type<bool>(), Param::Default, &topdown_default } }, { &type<two::OrbitController>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static bool modal_default = false;
			static Function f = { &namspc({ "two", "ui" }), "hybrid_controller", funcptr<two::OrbitController&(*)(two::Viewer&, two::ui::OrbitMode, two::Transform&, bool&, two::vec2&, bool)>(two::ui::hybrid_controller), two_ui_hybrid_controller_7, { { "viewer", type<two::Viewer>(),  }, { "mode", type<two::ui::OrbitMode>(),  }, { "entity", type<two::Transform>(),  }, { "aiming", type<bool>(),  }, { "angles", type<two::vec2>(),  }, { "modal", type<bool>(), Param::Default, &modal_default } }, { &type<two::OrbitController>(), QualType::None } };
			m.m_functions.push_back(&f);
		}
		{
			static float speed_default = 1.f;
			static Function f = { &namspc({ "two", "ui" }), "velocity_controller", funcptr<void(*)(two::Viewer&, two::vec3&, two::vec3&, float)>(two::ui::velocity_controller), two_ui_velocity_controller_8, { { "viewer", type<two::Viewer>(),  }, { "linear", type<two::vec3>(),  }, { "angular", type<two::vec3>(),  }, { "speed", type<float>(), Param::Default, &speed_default } }, g_qvoid };
			m.m_functions.push_back(&f);
		}
	}
}

namespace two
{
	two_gfx_ui::two_gfx_ui()
		: Module("two::gfx-ui", { &two_infra::m(), &two_tree::m(), &two_type::m(), &two_math::m(), &two_geom::m(), &two_ctx::m(), &two_ui::m(), &two_gfx::m() })
	{
		// setup reflection meta data
		two_gfx_ui_meta(*this);
	}
}

#ifdef TWO_GFX_UI_MODULE
extern "C"
Module& getModule()
{
	return two_gfx_ui::m();
}
#endif
