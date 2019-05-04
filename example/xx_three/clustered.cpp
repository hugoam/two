#include <xx_three/xx_three.h>
#include <gfx-pbr/Api.h>
#include <gfx-obj/Api.h>
#include <ecs/ECS.hpp>

#include <stl/vector.hpp>

#define CLUSTERED 1

EX(xx_clustered)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	static ImporterOBJ obj_importer(app.m_gfx);

#if UI
	ui::orbit_controls(viewer);
	//controls.minDistance = 120;
	//controls.maxDistance = 320;
#endif

	//var bloom = new THREE.UnrealBloomPass(new THREE.Vector2(), 0.8, 0.6, 0.8);
	//bloom.renderToScreen = true;

#if CLUSTERED
	Camera& camera = viewer.m_camera;
	viewer.m_viewport.set_clustered(app.m_gfx);
#endif

	constexpr float radius = 75.f;

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

	static vector<ExLight> lights = {};

	if(init)
	{
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

		auto create_material = [&](const string& name, auto init) -> Material* { return &app.m_gfx.materials().create(name, init); };

		Program& solid = app.m_gfx.programs().fetch("solid");
		Program& phong = app.m_gfx.programs().fetch("pbr/phong");
		Program& three = app.m_gfx.programs().fetch("pbr/three");

		Material* materials[] = {
			create_material("first",  [&](Material& m) { m.m_program = &three; m.m_pbr.m_albedo = rgb(0x888888); m.m_pbr.m_metallic = 1.0f; m.m_pbr.m_roughness = 0.66f; }),
			create_material("second", [&](Material& m) { m.m_program = &three; m.m_pbr.m_albedo = rgb(0x666666); m.m_pbr.m_metallic = 0.1f; m.m_pbr.m_roughness = 0.33f; }),
			create_material("third",  [&](Material& m) { m.m_program = &phong; m.m_phong.m_diffuse = rgb(0x777777); m.m_phong.m_shininess = 20.f; }),
			create_material("fourth", [&](Material& m) { m.m_program = &phong; m.m_phong.m_diffuse = rgb(0x555555); m.m_phong.m_shininess = 10.f; m.m_phong.m_toon = true; }),
		};

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

				Light& light = gfx::lights(scene).add(Light(l, LightType::Point, false, color, 1.f, radius));
				light.m_attenuation = 1.f;

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