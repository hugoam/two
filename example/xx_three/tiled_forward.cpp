//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>
#include <ecs/ECS.hpp>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

static string lights_input = 

R"'(
//SAMPLER2D(s_tiles, 7);
//SAMPLER2D(s_lights, 8);
#define s_tiles s_user0
#define s_lights s_user1
)'";

static string lights_fragment =

R"'(
//#define ALL_LIGHTS
#ifndef ALL_LIGHTS
ivec2 iuv = ivec2(gl_FragCoord.xy) / 32;
vec4 tile = texelFetch(s_tiles, iuv, 0);
#endif
for (int i = 0; i < 4; i++)
{
#ifndef ALL_LIGHTS
	float tileVal = tile.x * 255.0;
  	tile.xyzw = tile.yzwx;
	if(tileVal == 0.0) { continue; }
  	float tileDiv = 128.0;
#endif
	for (int j = 0; j < 8; j++)
	{
#ifndef ALL_LIGHTS
  		if (tileVal < tileDiv) { tileDiv *= 0.5; continue; }
		tileVal -= tileDiv;
		tileDiv *= 0.5;
#endif

		int uvx = 8 * i + j;

  		vec4 light_p0 = texelFetch(s_lights, ivec2(uvx, 0), 0);
  		vec3 position = light_p0.xyz;
  		float range = light_p0.w;

  		vec4 light_p1 = texelFetch(s_lights, ivec2(uvx, 1.0), 0);
  		vec3 energy = light_p1.xyz;
  		float decay = light_p1.w;

		vec3 l = position - fragment.position;
		float a = point_light_decay(length(l), range, decay);
		direct_brdf(energy * a, normalize(l), fragment, material, diffuse, specular);
	}
}
)'";

static string tiled_vertex =
	"#include <geometry_vs.sc>";

static string tiled_phong_fragment =
		
	"$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal\n"

	"#include <encode.sh>\n"
	"#include <pbr/pbr.sh>\n"
	"#include <pbr/light.sh>\n"
	"#define BRDF_BLINN_PHONG\n"
	"#include <pbr/light_brdf_three.sh>\n"
	"#include <pbr/radiance.sh>\n"

	+ lights_input + "\n" +

	"void main()\n"
	"{\n"
	"#include <pbr/fs_fragment.sh>\n"
	"#include <pbr/fs_phong_material.sh>\n"
	"#include <pbr/fs_phong.sh>\n"
	+ lights_fragment + "\n" +
	"#include <pbr/fs_out_pbr.sh>\n"
	"}\n";

static string tiled_three_fragment =
		
	"$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal\n"

	"#include <encode.sh>\n"
	"#include <pbr/pbr.sh>\n"
	"#include <pbr/light.sh>\n"
	"#define BRDF_STANDARD\n"
	"#include <pbr/light_brdf_three.sh>\n"
	"#include <pbr/radiance.sh>\n"

	+ lights_input + "\n" +

	"void main()\n"
	"{\n"
	"#include <pbr/fs_fragment.sh>\n"
	"#include <pbr/fs_pbr_material.sh>\n"
	"#include <pbr/fs_pbr.sh>\n"
	+ lights_fragment + "\n" +
	"#include <pbr/fs_out_pbr.sh>\n"
	"}\n";

struct ExLight
{
	Node3* parent;
	Node3* node;
	Colour color;
	float radius = radius;
	float decay = 1.f;
	float sy, sr, sc;
	float py, pr, pc;
	float dir;
};

// Simple form of tiled forward lighting
// using texels as bitmasks of 32 lights

struct Tiled
{
	uvec2 size;
	size_t rows = 0;
	size_t cols = 0;

	Texture tiles;
	Texture lights;
};

void resize_tiles(GfxSystem& gfx, Render& render, Tiled& state)
{
	const vec4 rect = render.m_rect * vec2(render.m_fbo->m_size);

	state.size = uvec2(rect.width, rect.height);
	state.cols = ceil(rect.width / 32);
	state.rows = ceil(rect.height / 32);

	state.tiles = { uvec2(state.cols, state.rows), false, TextureFormat::RGBA8 };
}

// Generate the light bitmasks and store them in the tile texture
void pack_lights(GfxSystem& gfx, Render& render, Tiled& state, span<ExLight> lights)
{
	vector<uint32_t> d = vector<uint32_t>(state.cols * state.rows);
	vector<float> ld = vector<float>(32 * 2 * 4);

	const vec4 rect = render.m_rect * vec2(render.m_fbo->m_size);
	Camera& camera = *render.m_camera;

	//d.fill(0);

	// Screen rectangle bounds from light sphere's world AABB
	auto lightBounds = [&](Camera& camera, const vec3& pos, float r)
	{
		vec2 lo = vec2(rect.width, rect.height);
		vec2 hi = vec2(0.f, 0.f);
		vec2 half = vec2(rect.width / 2.f, rect.height / 2.f);

		for(int i = 0; i < 8; i++)
		{
			vec3 v = pos;
			v.x += i & 1 ? r : -r;
			v.y += i & 2 ? r : -r;
			v.z += i & 4 ? r : -r;
			vec2 xy = (vec2(camera.project(v)) * half) + half;
			lo = min(lo, xy);
			hi = max(hi, xy);
		}

		return ivec4(lo.x, hi.x, lo.y, hi.y);
	};

	size_t index = 0;
	for(ExLight& light : lights)
	{
		vec3 vector = light.node->position();

		ivec4 bs = lightBounds(camera, vector, light.radius);

		vector = mulp(camera.m_view, vector);

		assert(32 * 4 + 4 * index + 3 < ld.size());

		ld[4 * index + 0] = vector.x;
		ld[4 * index + 1] = vector.y;
		ld[4 * index + 2] = vector.z;
		ld[4 * index + 3] = light.radius;
		ld[32 * 4 + 4 * index + 0] = light.color.r;
		ld[32 * 4 + 4 * index + 1] = light.color.g;
		ld[32 * 4 + 4 * index + 2] = light.color.b;
		ld[32 * 4 + 4 * index + 3] = light.decay;

		if(bs[1] < 0 || bs[0] > rect.width || bs[3] < 0 || bs[2] > rect.height) return;
		if(bs[0] < 0) bs[0] = 0;
		if(bs[1] > rect.width) bs[1] = rect.width;
		if(bs[2] < 0) bs[2] = 0;
		if(bs[3] > rect.height) bs[3] = rect.height;

		const uint32_t i4 = index / 8;
		const uint32_t i8 = 7 - (index % 8);
		const size_t shift = i4 * 8 + i8;

		const size_t maxsize = d.size();
		for(size_t i = bs[2] / 32; i < bs[3] / 32 + 1; i++)
			for(size_t j = bs[0] / 32; j < bs[1] / 32 + 1; j++)
			{
				const size_t index = (state.cols * i + j);
				assert(index < d.size());
				d[index] |= 1 << shift;
			}

		index++;
	}

	state.tiles.load_rgba(state.tiles.m_size, d);
	state.lights.load_float(state.lights.m_size, ld);
}

void xx_tiled_forward(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	static ImporterOBJ obj_importer(app.m_gfx);

	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controls(viewer);
	//controls.minDistance = 120;
	//controls.maxDistance = 320;

	//var bloom = new THREE.UnrealBloomPass(new THREE.Vector2(), 0.8, 0.6, 0.8);
	//bloom.renderToScreen = true;

	constexpr float radius = 75.f;

	Scene& scene = viewer.m_scene;

	static Tiled state;
	static vector<ExLight> lights = {};
	static Material* materials[4] = {};

	static auto update_materials = []()
	{
		for(Material* m : materials)
		{
			m->m_user.m_tex0 = &state.tiles;
			m->m_user.m_tex1 = &state.lights;
			//mtl.uniforms["opacity"].value = tIndex == = index ? 0.9 : 1;
		}
	};

	auto renderer = [](GfxSystem& gfx, Render& render)
	{
		begin_pbr_render(gfx, render);

		update_materials();

		if(render.m_fbo->m_size != state.size)
			resize_tiles(gfx, render, state);

		pack_lights(gfx, render, state, lights);

		pass_clear(gfx, render);
		pass_opaque(gfx, render);
		pass_solid(gfx, render);
		pass_post_auto(gfx, render);
	};

	if(init)
	{
		app.m_gfx.set_renderer(Shading::Shaded, renderer);

		state.lights = { uvec2(32, 2), false, TextureFormat::RGBA32F };

		Camera& camera = viewer.m_camera;
		camera.m_fov = 40.f; camera.m_near = 1.f; camera.m_far = 2000.f;
		camera.m_eye = vec3(0.f, 0.f, 240.f);

		Zone& env = scene.m_env;
		env.m_radiance.m_ambient = rgb(0xffffff) * 0.33f;

		env.m_background.m_colour = rgb(0x111111);
		viewer.m_viewport.m_clear_colour = rgb(0x111111);

		Model& model = *app.m_gfx.models().file("WaltHead");
		
		Model& sphere = app.m_gfx.shape(Sphere(0.5f));
		Model& big_sphere = app.m_gfx.shape(Sphere(0.5f * 6.66f));

		Program& solid = app.m_gfx.programs().fetch("solid");
		Program& phong = app.m_gfx.programs().fetch("pbr/phong");
		Program& three = app.m_gfx.programs().fetch("pbr/three");

		Program& tiled_phong = app.m_gfx.programs().create("tiledphong");
		tiled_phong.set_source(ShaderType::Vertex, tiled_vertex);
		tiled_phong.set_source(ShaderType::Fragment, tiled_phong_fragment);
		tiled_phong.register_blocks(phong);
		tiled_phong.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Lit, MaterialBlock::Phong, MaterialBlock::User });

		Program& tiled_three = app.m_gfx.programs().create("tiledthree");
		tiled_three.set_source(ShaderType::Vertex, tiled_vertex);
		tiled_three.set_source(ShaderType::Fragment, tiled_three_fragment);
		tiled_three.register_blocks(three);
		tiled_three.set_blocks({ MaterialBlock::Alpha, MaterialBlock::Lit, MaterialBlock::Pbr, MaterialBlock::User });

		Material& m0 = app.m_gfx.materials().create("tiled0");
		Material& m1 = app.m_gfx.materials().create("tiled1");
		Material& m2 = app.m_gfx.materials().create("tiled2");
		Material& m3 = app.m_gfx.materials().create("tiled3");

		m0.m_program = &tiled_three; m0.m_pbr.m_albedo = rgb(0x888888); m0.m_pbr.m_metallic = 1.0f; m0.m_pbr.m_roughness = 0.66f;
		m1.m_program = &tiled_three; m1.m_pbr.m_albedo = rgb(0x666666); m1.m_pbr.m_metallic = 0.1f; m1.m_pbr.m_roughness = 0.33f;
		m2.m_program = &tiled_phong; m2.m_phong.m_diffuse = rgb(0x777777); m2.m_phong.m_shininess = 20.f;
		m3.m_program = &tiled_phong; m3.m_phong.m_diffuse = rgb(0x555555); m3.m_phong.m_shininess = 10.f; m3.m_phong.m_toon = true;

		materials[0] = &m0; materials[1] = &m1; materials[2] = &m2; materials[3] = &m3;

		size_t transparent = randi(0, 3);
		materials[transparent]->m_alpha.m_alpha = 0.9f;

		//transparent : tIndex == = index ? true : false,
		//mtl.uniforms["opacity"].value = tIndex == = index ? 0.9 : 1;
		//mtl.side = tIndex == = index ? THREE.FrontSide : THREE.DoubleSide;

		size_t index = 0;
		for(Material* material : materials)
		{
			const float i = float(index++);
			const vec3 position = vec3(sin(i * c_pi2) * radius, 0.f, cos(i * c_pi2) * radius);
			const quat rotation = quat(vec3(0.f, i * c_pi2, 0.f));

			Node3& n = gfx::nodes(scene).add(Node3(position, rotation));

			Node3& m = gfx::nodes(scene).add(Node3(n.m_transform * bxTRS(vec3(1.f), ZeroQuat, vec3(0.f, -37.f, 0.f))));
			Item& it = gfx::items(scene).add(Item(m, model, 0U, material));
			UNUSED(it);


			for(size_t i = 0; i < 8; i++)
			{
				const Colour color = hsl(randf(), 1.0, 0.5f);

				Material& ml = app.m_gfx.materials().create("light" + material->m_name + to_string(i), [&](Material& m) { 
					m.m_program = &solid; m.m_solid.m_colour = color; 
				});

				Material& mla = app.m_gfx.materials().create("lightalpha" + material->m_name + to_string(i), [&](Material& m) {
					m.m_program = &solid; m.m_solid.m_colour = color; m.m_alpha.m_alpha = 0.033f;
				});

				Node3& l = gfx::nodes(scene).add(Node3());
				Item& i0 = gfx::items(scene).add(Item(l, sphere, 0U, &ml)); // MaterialSolid(color)));
			
				//Item& i1 = gfx::items(scene).add(Item(l, big_sphere, 0U, &ma)); // MaterialSolid(color), MaterialAlpha(0.033f));
				//l.children[1].scale.set(6.66, 6.66, 6.66);

				lights.push_back({
					&n,
					&l,
					color,
					radius,
					1.f,
					randf(),
					randf(),
					randf(),
					randf() * c_pi,
					randf() * c_pi,
					randf() * c_pi,
					randf() > 0.5 ? 1.f : -1.f
				});
			}
		}
	}

	float time = app.m_gfx.m_time;

	for(ExLight& l : lights)
	{
		float r = 0.8f + 0.2f * sin(l.pr + (0.6f + 0.3f * l.sr) * time);
		float x = (sin(l.pc + (0.8f + 0.2f * l.sc) * time * l.dir)) * r * radius;
		float z = (cos(l.pc + (0.8f + 0.2f * l.sc) * time * l.dir)) * r * radius;
		float y = sin(l.py + (0.8f + 0.2f * l.sy) * time) * r * 32.f;
		l.node->derive(*l.parent, vec3(x, y, z));
	}
}