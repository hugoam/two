//#include <two/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace two;

#define CUSTOM_SHADER 1

#if CUSTOM_SHADER
static const string simple_vertex = R"'(
$input a_position, a_normal
$output v_view, v_normal

#include <common.sh>

void main()
{
    v_view = mul(u_modelView, vec4(a_position.xyz, 1.0)).xyz;

    v_normal = normalize(mul(u_modelView, vec4(a_normal, 0.0)).xyz);
        
    gl_Position = mul(u_proj, vec4(v_view, 1.0));
}
)'";

static const string simple_fragment = R"'(
$input v_view, v_normal

#include <encode.sh>
#include <pbr/pbr.sh>
#include <pbr/light.sh>
#define BRDF_BLINN_PHONG
#include <pbr/light_brdf_three.sh>
#include <pbr/radiance.sh>
#include <fog.sh>

void main()
{
    Fragment fragment;
    fragment.coord = gl_FragCoord;
    fragment.position = v_view.xyz;
    fragment.view = normalize(-v_view.xyz);
    fragment.normal = normalize(v_normal);
#ifdef DOUBLE_SIDED
    fragment.normal = fragment.normal * (float(gl_FrontFacing) * 2.0 - 1.0);
#endif

#include <pbr/fs_phong_material.sh>
    PhongMaterial material = matphong;

    int zone_index = int(u_state_zone);
    Zone zone = read_zone(zone_index);
        
    vec3 diffuse = vec3_splat(0.0);
    vec3 specular = vec3_splat(0.0);

#include <pbr/fs_indirect.sh>
    diffuse += zone.ambient * PI;
    diffuse *= BRDF_Diffuse_Lambert(matphong.diffuse);

    int i = 0;

    for(i = 0; i < int(u_light_counts[LIGHT_POINT]); i++)
    {
        Light light = read_light(int(u_light_indices[i][LIGHT_POINT]));
        vec3 l = light.position - fragment.position;
        float a = omni_attenuation(l, light);
        direct_brdf(light.energy * a, normalize(l), fragment, material, diffuse, specular);
    }

    #include <pbr/fs_phong_ibl.sh>
    #include <pbr/fs_out_pbr.sh>
    #include <fs_fog_simple.sh>
}
)'";
#endif

void xx_perf_twosided(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);

	Camera& camera = viewer.m_camera;
	Scene& scene = viewer.m_scene;

	auto ungamma = [](const Colour& c) { return to_colour(pow(to_vec3(c), vec3(2.f))); };

	Program& phong = app.m_gfx.programs().fetch("pbr/phong");

#if CUSTOM_SHADER
	static Program& program = app.m_gfx.programs().create("twosided");
	if(init)
	{
		program.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Lit, MaterialBlock::Phong });
		program.set_source(ShaderType::Vertex, simple_vertex);
		program.set_source(ShaderType::Fragment, simple_fragment);
		program.register_blocks(phong);
	}
#endif

	if(init)
	{
		camera.m_fov = 50.f; camera.m_near = 1.f; camera.m_far = 20000.f;
		camera.m_eye.z = 3200.f;

		viewer.m_viewport.m_to_gamma = true;

		viewer.m_viewport.m_clear_colour = ungamma(rgb(0x050505));

		Texture& reflection = *app.m_gfx.textures().file("cube/royal.jpg.cube");
		reflection.reload(app.m_gfx, false, true);

		Zone& env = scene.m_env;
		env.m_radiance.m_texture = &reflection;
		env.m_radiance.m_filter = false;
		env.m_radiance.m_ambient = rgb(0x050505);

		Node3& l0 = gfx::nodes(scene).add(Node3(vec3(4000.f, 0.f, 0.f)));
		gfx::lights(scene).add(Light(l0, LightType::Point, false, rgb(0x0011ff), 1.f, 5500.f));

		Node3& l1 = gfx::nodes(scene).add(Node3(vec3(-4000.f, 0.f, 0.f)));
		gfx::lights(scene).add(Light(l1, LightType::Point, false, rgb(0xff1100), 1.f, 5500.f));

		Node3& l2 = gfx::nodes(scene).add(Node3(vec3(0.f)));
		gfx::lights(scene).add(Light(l2, LightType::Point, false, rgb(0xffaa00), 2.f, 3000.f));
		
		Program& phong = *app.m_gfx.programs().file("pbr/phong");

		Material& material = app.m_gfx.materials().create("twosided",  [&](Material& m) {
#if CUSTOM_SHADER
			m.m_program = &program;
#else
			m.m_program = &phong;
#endif
			m.m_base.m_cull_mode = CullMode::None;
			m.m_phong.m_specular = rgb(0x101010);
			m.m_phong.m_shininess = 100.f;
			m.m_phong.m_reflectivity = 0.1f;
			m.m_phong.m_env_blend = PhongEnvBlendMode::Mix;
		});

		Symbol symbol; symbol.m_subdiv = uvec2(32, 16);
		Model& geometry = app.m_gfx.shape(Sphere(1.f, 0.f, c_pi), symbol);

		for(size_t i = 0; i < 5000; ++i)
		{
			vec3 p = vec3(randf(), randf(), randf()) * 10000.f - 5000.f;
			vec3 a = vec3(randf(), randf(), 0.f) * c_2pi;
			vec3 s = vec3(randf()) * 50.f + 100.f;

			constexpr uint32_t flags = 0U; // ItemFlag::Render | ItemFlag::NoCull | ItemFlag::LodAll;
			Node3& n = gfx::nodes(scene).add(Node3(p, quat(a), s));
			gfx::items(scene).add(Item(n, geometry, flags, &material));
		}
	}

	static vec2 mouse = vec2(0.f);
	if(MouseEvent event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		mouse = (event.m_relative - viewer.m_frame.m_size / 2.f) * 10.f;
	}

	camera.m_eye.x += (mouse.x - camera.m_eye.x) * .05f;
	camera.m_eye.y += (-mouse.y - camera.m_eye.y) * .05f;
}