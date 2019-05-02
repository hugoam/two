//#include <two/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>
#include <srlz/Serial.h>

#include <xx_three/xx_three.h>

#include <stl/array.h>

using namespace two;

// @author daoshengmu / http://dsmu.me/

//	Subsurface Scattering shader
// 		- Base on GDC 2011 – Approximating Translucency for a Fast, Cheap and Convincing Subsurface Scattering Look
// 			https://colinbarrebrisebois.com/2011/03/07/gdc-2011-approximating-translucency-for-a-fast-cheap-and-convincing-subsurface-scattering-look/

struct Phong
{
	attr_ Colour m_color = rgb(0xffffff);
	attr_ Colour m_diffuse = rgb(0xffffff);
	attr_ Colour m_specular = rgb(0xffffff);
	attr_ Colour m_emissive = rgb(0x000000);
	attr_ float m_opacity = 1.f;
	attr_ float m_shininess = 1.f;
};

struct Subsurface
{
	attr_ Texture* m_texture;
	attr_ Colour m_color = rgb(0xffffff);
	attr_ float m_distortion = 0.1f;
	attr_ float m_ambient = 0.0f;
	attr_ float m_attenuation = 0.1f;
	attr_ float m_power = 2.0f;
	attr_ float m_scale = 10.f;
};

static string translucent_fragment =
		
	"$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal\n"

	"#include <encode.sh>\n"
	"#include <pbr/pbr.sh>\n"
	"#include <pbr/light.sh>\n"
	"#include <pbr/light_brdf_three.sh>\n"
	"#include <pbr/radiance.sh>\n"

	"#define s_thickness s_user0\n"

	"struct TranslucentMaterial\n"
	"{\n"
	"	PhongMaterial phong;\n"
	"	UserMaterial scatter;\n"
	"};\n"

	"void direct_scatter(vec3 energy, vec3 l, Fragment fragment, TranslucentMaterial mat, inout vec3 diffuse, inout vec3 specular)\n"
	"{\n"
		"direct_blinn_phong(energy, l, fragment, mat.phong, diffuse, specular);\n"

		"float power       = mat.scatter.p0.x;\n"
		"float scale       = mat.scatter.p0.y;\n"
		"float distortion  = mat.scatter.p0.z;\n"
		"float ambient     = mat.scatter.p0.w;\n"
		"float attenuation = mat.scatter.p1.x;\n"
		"vec3  color       = mat.scatter.p1.yzw;\n"

		"vec3 thickness = color * texture2D(s_thickness, fragment.uv).r;\n"
		"vec3 scatteringHalf = normalize(l + (fragment.normal * distortion));\n"
		"float scatteringDot = pow(saturate(dot(fragment.view, -scatteringHalf)), power) * scale;\n"
		"vec3 scatteringIllu = (scatteringDot + ambient) * thickness;\n"
	
		"diffuse += scatteringIllu * attenuation * energy;\n"
	"}\n"

	"#define direct_brdf direct_scatter\n"

	"void main()\n"
	"{\n"
	"#include <pbr/fs_fragment.sh>\n"
		
	"#include <pbr/fs_phong_material.sh>\n"
		"TranslucentMaterial material;\n"
		"material.phong = matphong;\n"
		"material.scatter = matuser;\n"
		
	"#include <pbr/fs_phong.sh>\n"
	"#include <pbr/fs_out_pbr.sh>\n"
	//"gl_FragColor = vec4(texture2D(s_thickness, fragment.uv).rgb, 1.0);\n"
	"}\n";

	//"	vec3 outgoingLight = reflectedLight.directDiffuse + reflectedLight.indirectDiffuse + reflectedLight.directSpecular + reflectedLight.indirectSpecular + totalEmissiveRadiance;\n"
	//"	gl_FragColor = vec4(outgoingLight, diffuseColor.a);\n"
	// TODO, this should be pre-multiplied to allow for bright highlights on very transparent objects

string translucent_vertex =

	"#include <geometry_vs.sc>\n";
	//"	vNormal = normalize(u_normalModelViewProj * normal);\n"

Program& translucent_program(GfxSystem& gfx)
{
	static Program& pbr = gfx.programs().fetch("pbr/pbr");

	static Program& program = gfx.programs().create("translucent");
	program.register_blocks(pbr.m_registered_blocks);
	program.set_block(MaterialBlock::Lit);
	program.set_block(MaterialBlock::Phong);
	program.set_block(MaterialBlock::User);
	program.set_source(ShaderType::Vertex, translucent_vertex);
	program.set_source(ShaderType::Fragment, translucent_fragment);

	return program;
}

//<script src="js/loaders/FBXLoader.js"></script>

void xx_material_translucent(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	static ImporterOBJ obj_importer = { app.m_gfx };

	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controls(viewer);

	Scene& scene = viewer.m_scene;

	static Phong phong;
	static Subsurface thickness;

	static Node3* node = nullptr;
	static const vec3 scale = vec3(1.f);
	//static const vec3 scale = vec3(0.01f);

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 40.f; camera.m_near = 1.f; camera.m_far = 5000.f;
		camera.m_eye = vec3(0.f, 300.f, 400.f * 4.f);
		camera.m_eye *= 0.7f; // we are less zoomed in that in three.js somehow ?

		viewer.m_viewport.m_to_gamma = true;

		// Lights

		scene.m_env.m_radiance.m_ambient = rgb(0x888888);

		Node3& dn = gfx::nodes(scene).add(Node3(vec3(0.f), look_dir(normalize(vec3(0.f, -0.5f, -0.5f)))));
		Light& dl = gfx::lights(scene).add(Light(dn, LightType::Direct, false, rgb(0xffffff), 0.03f));

		Node3& pn0 = gfx::nodes(scene).add(Node3(vec3(0.f, -50.f, 350.f)));
		Light& pl0 = gfx::lights(scene).add(Light(pn0, LightType::Point, false, rgb(0x888888), 7.f, 300.f));
		gfx::items(scene).add(Item(pn0, app.m_gfx.shape(Sphere(4.f)), 0U, &gfx::solid_material(app.m_gfx, "l0", rgb(0x888888))));

		Node3& pn1 = gfx::nodes(scene).add(Node3(vec3(-100.f, 20.f, -260.f)));
		Light& pl1 = gfx::lights(scene).add(Light(pn1, LightType::Point, false, rgb(0x888800), 1.f, 500.f));
		gfx::items(scene).add(Item(pn1, app.m_gfx.shape(Sphere(4.f)), 0U, &gfx::solid_material(app.m_gfx, "l1", rgb(0x888800))));

		Texture& white = *app.m_gfx.textures().file("white.jpg");
		Texture& texture = *app.m_gfx.textures().file("bunny_thickness.jpg");

		phong.m_diffuse = Colour(1.0f, 0.2f, 0.2f);
		phong.m_shininess = 500.f;

		thickness.m_texture = &texture;
		thickness.m_color = Colour(0.5f, 0.3f, 0.0f);
		thickness.m_distortion = 0.1f;
		thickness.m_ambient = 0.4f;
		thickness.m_attenuation = 0.8f;
		thickness.m_power = 2.0f;
		thickness.m_scale = 16.0f;

		static Program& pbr = app.m_gfx.programs().fetch("pbr/pbr");

		static Program& program = translucent_program(app.m_gfx);

		Material& material = app.m_gfx.materials().create("translucent", [](Material& m) {
			//m.m_program = &pbr;
			m.m_program = &program;
			// @todo fix obj normals which are fucked up somehow, flat normals as temporary kludge
			//m.m_base.m_flat_shaded = true;
			m.m_pbr.m_albedo = Colour(1.0f, 0.2f, 0.2f);
			m.m_phong.m_diffuse = Colour(1.0f, 0.2f, 0.2f);
			m.m_phong.m_shininess = 500.f;
			m.m_user.m_tex0 = thickness.m_texture;
			m.m_user.m_attr0 = { thickness.m_power, thickness.m_scale, thickness.m_distortion, thickness.m_ambient };
			m.m_user.m_attr1 = { thickness.m_attenuation, to_vec3(thickness.m_color) };
		});

		//Model& bunny = *app.m_gfx.models().file("stanford-bunny");
		Model& bunny = *app.m_gfx.models().file("bunny");
		//Model& bunny = *app.m_gfx.models().file("stanford-bunny.fbx");

		Node3& n = gfx::nodes(scene).add(Node3(vec3(0.f, 0.f, 10.f), ZeroQuat, scale));
		Item& it = gfx::items(scene).add(Item(n, bunny, 0U, &material));
		node = &n;
	}

	if(Widget* dock = ui::dockitem(dockbar, "Game", { 1U }))
	{
		Widget& sheet = ui::sheet(*dock);

		auto panel = [&](const string& name) -> Widget&
		{
			Widget& s = ui::expandbox(sheet, name.c_str());
			return ui::columns(s, { 0.3f, 0.7f });
		};

		Widget& a = panel("Thickness Control");

		ui::slider_field<float>(a, "distortion",  thickness.m_distortion,  { 0.01f, 1.f, 0.01f });
		ui::slider_field<float>(a, "ambient",     thickness.m_ambient,     { 0.01f, 5.f, 0.05f });
		ui::slider_field<float>(a, "attenuation", thickness.m_attenuation, { 0.01f, 5.f, 0.05f });
		ui::slider_field<float>(a, "power",       thickness.m_power,       { 0.01f, 16.f, 0.1f });
		ui::slider_field<float>(a, "scale",       thickness.m_scale,       { 0.01f, 50.f, 0.1f });
	}

	const float y = app.m_gfx.m_time / 5.f;
	node->apply(vec3(0.f, 0.f, 10.f), quat(vec3(0.f, y, 0.f)), scale);
}
