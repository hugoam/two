//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

#define RENDERER 0

static string bokeh_vertex()
{
	string shader =

		"$input a_position, a_texcoord0\n"
		"$output v_uv0\n"
		"\n"
		"#include <filter.sh>\n"
		"\n"
		"void main() {\n"
		"	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;\n"
		"	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));\n"
		"}\n";

	return shader;
}

static string bokeh_fragment()
{
	string shader =

		"$input v_uv0\n"
		"\n"
		"#include <filter.sh>\n"
		"\n"
		"uniform vec4 u_bokeh_p0;\n"
		"#define u_focus    u_bokeh_p0.x\n"
		"#define u_aperture u_bokeh_p0.y\n"  // aperture - bigger values for shallower depth of field
		"#define u_maxblur  u_bokeh_p0.z\n"  // max blur amount
		"\n"
		"float getViewZ(float depth) {\n"
		//"	#if PERSPECTIVE_CAMERA == 1\n"
		"	return perspectiveDepthToViewZ(depth);\n"
		//"	#else\n"
		//"	return orthographicDepthToViewZ(depth);\n"
		//"	#endif\n"
		"}\n"
		"\n"
		"\n"
		"void main() {\n"
		"\n"
		"vec2 aspect = vec2(1.0, u_aspect);\n"
		"\n"
		"float depth = texture2D(s_source_depth, v_uv0).x;\n"
		"float viewZ = getViewZ(depth);\n"
		"\n"
		"float factor = (u_focus + viewZ);\n"  // viewZ is <= 0, so this is a difference equation
		"\n"
		"vec2 dofblur = vec2_splat(clamp(factor * u_aperture, -u_maxblur, u_maxblur));\n"
		"\n"
		"vec2 dofblur9 = dofblur * 0.9;\n"
		"vec2 dofblur7 = dofblur * 0.7;\n"
		"vec2 dofblur4 = dofblur * 0.4;\n"
		"\n"
		"vec4 col = vec4_splat(0.0);\n"
		"\n"
		"col += texture2D(s_source_0, v_uv0);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.0,   0.4 ) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.15,  0.37) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.29,  0.29) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.37,  0.15) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.40,  0.0 ) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.37, -0.15) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.29, -0.29) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.15, -0.37) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.0,  -0.4 ) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.15,  0.37) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.29,  0.29) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.37,  0.15) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.4,   0.0 ) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.37, -0.15) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.29, -0.29) * aspect) * dofblur);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.15, -0.37) * aspect) * dofblur);\n"
		"\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.15,  0.37) * aspect) * dofblur9);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.37,  0.15) * aspect) * dofblur9);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.37, -0.15) * aspect) * dofblur9);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.15, -0.37) * aspect) * dofblur9);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.15,  0.37) * aspect) * dofblur9);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.37,  0.15) * aspect) * dofblur9);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.37, -0.15) * aspect) * dofblur9);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.15, -0.37) * aspect) * dofblur9);\n"
		"\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.29,  0.29) * aspect) * dofblur7);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.40,  0.0 ) * aspect) * dofblur7);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.29, -0.29) * aspect) * dofblur7);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.0,  -0.4 ) * aspect) * dofblur7);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.29,  0.29) * aspect) * dofblur7);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.4,   0.0 ) * aspect) * dofblur7);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.29, -0.29) * aspect) * dofblur7);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.0,   0.4 ) * aspect) * dofblur7);\n"
		"\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.29,  0.29) * aspect) * dofblur4);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.4,   0.0 ) * aspect) * dofblur4);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.29, -0.29) * aspect) * dofblur4);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.0,  -0.4 ) * aspect) * dofblur4);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.29,  0.29) * aspect) * dofblur4);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.4,   0.0 ) * aspect) * dofblur4);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2(-0.29, -0.29) * aspect) * dofblur4);\n"
		"col += texture2D(s_source_0, v_uv0 + (vec2( 0.0,   0.4 ) * aspect) * dofblur4);\n"
		"\n"
		"gl_FragColor = vec4(col.rgb / 41.0, 1.0);\n"
		//"gl_FragColor = vec4(vec3_splat(-viewZ / u_z_far), 1.0);\n"
		//"gl_FragColor = vec4(vec3_splat(1.0 + viewZ / u_z_far), 1.0);\n"
		"\n"
		"}\n";

	return shader;
}

struct Bokeh
{
	float focus = 1.f;
	float aperture = 0.025f;
	float maxblur = 1.f;
	float aspect = 1.f;
};

void pass_bokeh(GfxSystem& gfx, Render& render, const Bokeh& bokeh)
{
	static Program& program = gfx.programs().fetch("bokeh");

	Pass pass = render.next_pass("bokeh", PassType::PostProcess);

	gfx.m_filter->uniform(pass, "u_bokeh_p0", vec4(bokeh.focus, bokeh.aperture * 0.00001f, bokeh.maxblur, 0.f));

	gfx.m_filter->source0(render.m_target->m_diffuse);
	gfx.m_filter->sourcedepth(render.m_target->m_depth);

	gfx.m_filter->quad(pass, render.m_target->m_post_process.swap(), program);

	gfx.m_copy->quad(render.composite_pass("flip"), *render.m_target_fbo, render.m_target->m_post_process.last());
}

void xx_effect_dof(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	//ui::orbit_controls(viewer);
	viewer.m_viewport.m_active = false;

	Scene& scene = viewer.m_scene;

	constexpr int xgrid = 14;
	constexpr int ygrid = 9;
	constexpr int zgrid = 14;
	constexpr int nobjects = xgrid * ygrid * zgrid;

	static Program& program = app.m_gfx.programs().create("bokeh");
	if(init)
	{
		program.m_sources[ShaderType::Vertex] = bokeh_vertex();
		program.m_sources[ShaderType::Fragment] = bokeh_fragment();
	}

	static Bokeh bokeh = { 500.f, 5.f, 1.f };

	//struct Parameters { float focus = 500.f; float aperture = 5.f; float maxblur = 1.f; };

	static vector<Material*> materials;

	auto renderer = [](GfxSystem& gfx, Render& render)
	{
		begin_pbr_render(gfx, render);

		pass_clear(gfx, render);
		pass_opaque(gfx, render);
		pass_bokeh(gfx, render, bokeh);
	};

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 70.f; camera.m_near = 1.f; camera.m_far = 3000.f;
		camera.m_eye.z = 200.f;

		Program& basic = app.m_gfx.programs().fetch("pbr/basic");

		//Texture& texpano = *app.m_gfx.textures().file("radiance/tiber_1_1k.hdr");
		Texture& texcube = *app.m_gfx.textures().file("cube/royal.jpg.cube");
		//scene.m_env.m_radiance.m_texture = &texpano;
		scene.m_env.m_radiance.m_texture = &texcube;
		scene.m_env.m_radiance.m_energy = 1.f;

		materials.clear();
		for(int i = 0; i < nobjects; ++i)
		{
			const string name = "object" + to_string(i);
			Material& m = app.m_gfx.materials().fetch(name);
			m.m_program = &basic;
			m.m_pbr.m_albedo = rgb(0xff1100);
			//m.m_pbr.m_metallic = 1.f;
			materials.push_back(&m);
		}

		Model& geometry = app.m_gfx.shape(Sphere(1.f));
		int count = 0;
		for(int i = 0; i < xgrid; i++)
			for(int j = 0; j < ygrid; j++)
				for(int k = 0; k < zgrid; k++)
				{
					int x = 200 * (i - xgrid / 2);
					int y = 200 * (j - ygrid / 2);
					int z = 200 * (k - zgrid / 2);
					Node3& n = gfx::nodes(scene).add(Node3(vec3(ivec3(x, y, z)), ZeroQuat, vec3(60.f)));
					gfx::items(scene).add(Item(n, geometry, 0U, materials[count]));
					count++;
				}

		//postprocessing.composer.render(0.1);

#if RENDERER
		app.m_gfx.set_renderer(Shading::Shaded, render);
#endif
	}

	static vec2 mouse = vec2(0.f);
	if(MouseEvent event = viewer.mouse_event(DeviceType::Mouse, EventType::Moved))
	{
		mouse.x = event.m_relative.x - viewer.m_frame.m_size.x / 2.f;
		mouse.y = event.m_relative.y - viewer.m_frame.m_size.y / 2.f;
	}

	if(MouseEvent event = viewer.mouse_event(DeviceType::Touch, EventType::Pressed))
	//or(MouseEvent event = viewer.mouse_event(DeviceType::Touch, EventType::Moved))
	{
		//if(event.touches.length == 1) {
		//	event.preventDefault();
		//	mouseX = event.touches[0].pageX - windowHalfX;
		//	mouseY = event.touches[0].pageY - windowHalfY;
		//}
	}

	const float time = app.m_gfx.m_time * 0.05f;

	Camera& camera = viewer.m_camera;
	camera.m_eye.x += (mouse.x - camera.m_eye.x) * 0.036f;
	camera.m_eye.y += (-(mouse.y) - camera.m_eye.y) * 0.036f;
	//camera.m_target = scene.position;

	for(int i = 0; i < nobjects; i++)
	{
		float h = fmod(360.f * (float(i) / float(nobjects) + time), 360.f) / 360.f;
		materials[i]->m_solid.m_colour = hsl(h, 1.f, 0.5f);
		materials[i]->m_pbr.m_albedo = hsl(h, 1.f, 0.5f);
	}

	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		Widget& sheet = ui::sheet(*dock);

		Widget& controls = ui::stack(sheet);
		ui::slider_field<float>(controls, "focus",    { bokeh.focus,    { 10.f, 3000.f, 10.f } });
		ui::slider_field<float>(controls, "aperture", { bokeh.aperture, { 0.f, 10.f, 0.1f } });
		ui::slider_field<float>(controls, "maxblur",  { bokeh.maxblur,  { 0.f, 3.f, 0.025f } });
	}

#if !RENDERER
	Render render = { Shading::Shaded, viewer.m_viewport, app.m_gfx.main_target(), app.m_gfx.m_render_frame };
	app.m_gfx.m_renderer.gather(render);
	app.m_gfx.m_renderer.begin(render);
	renderer(app.m_gfx, render);
	app.m_gfx.m_renderer.end(render);
#endif
}
