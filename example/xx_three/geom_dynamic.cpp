//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

#define INSTANCING 1
#define DYNAMIC 1
#define PAD 0.f

using namespace mud;

void xx_geom_dynamic(Shell& app, Widget& parent, Dockbar& dockbar, bool init)
{
	UNUSED(dockbar);
	constexpr uint32_t max_particles = 1000;
	constexpr uint32_t max_segments = 10000;
	//constexpr uint32_t max_segments = max_particles * max_particles;


	constexpr uint num_particles = 500;

	const float r = 800.f;
	const float r2 = r / 2.f;

	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controls(viewer);

	Scene& scene = viewer.m_scene;

	struct EffectController
	{
		bool showDots = true;
		bool showLines = true;
		float minDistance = 150.f;
		bool limitConnections = false;
		uint maxConnections = 20;
		uint num_particles = 500;
	};
	
	EffectController controller;

	//var helper = new THREE.BoxHelper(new THREE.Mesh(new THREE.BoxBufferGeometry(r, r, r)));
	//helper.material.color.setHex(0x080808);
	//helper.material.blending = THREE.AdditiveBlending;
	//helper.material.transparent = true;
	//group.add(helper);

	static Program& pointprog = app.m_gfx.programs().fetch("point");
	static Program& lineprog = app.m_gfx.programs().fetch("line");

	struct Particle { vec3 position; vec3 velocity; uint32_t numConnections; };
	static vector<Particle> particles;

	static Mesh* points_mesh = nullptr;
	static Mesh* lines_mesh = nullptr;

#if INSTANCING
	struct Point { vec3 pos; float pad; vec2 scale; float pad1; float pad2; };

	static Batch* points_batch = nullptr;
	static Batch* lines_batch = nullptr;
#endif

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_near = 1.f; camera.m_far = 4000.f;
		camera.m_eye.z = 1750.f;
		
		//Material& material = new THREE.PointsMaterial({ size: 35, sizeAttenuation : false, map : sprite, alphaTest : 0.5, transparent : true });
		Material& pointmat = app.m_gfx.materials().create("point", [&](Material& m) {
			m.m_program = &pointprog;
			m.m_base.m_blend_mode = BlendMode::Add;
			m.m_alpha.m_is_alpha = true;
			m.m_solid.m_colour = rgb(0xffffff);//hsl(1.f, 0.3f, 0.7f);
			m.m_point.m_project = false;
			m.m_point.m_point_size = 3.f;
		});

		Material& linemat = app.m_gfx.materials().create("line", [&](Material& m) {
			m.m_program = &lineprog;
			m.m_base.m_blend_mode = BlendMode::Add;
			m.m_base.m_shader_color = ShaderColor::Vertex;
			m.m_alpha.m_is_alpha = true;
			//m.m_line.m_dashed = true;
		});

#if INSTANCING
		Model& points_model = *app.m_gfx.models().get("point");
#else
		MeshPacker pointgeom;
		pointgeom.m_primitive = PrimitiveType::Points;
#endif

		for(uint32_t i = 0; i < max_particles; i++)
		{
			vec3 p = vec3(randf(), randf(), randf()) * r - r2;
			vec3 v = vec3(randf(), randf(), randf()) * 2.f - 1.f;
#if !INSTANCING
			pointgeom.m_positions.push_back(p);
			pointgeom.m_indices.push_back(i);
#endif
			particles.push_back({ p, v, 0U });
		}

#if !INSTANCING
		Model& model = app.m_gfx.create_model("particles", geometry, false, dynamic = true);
		points_mesh->m_range = { 0U, num_particles };
#endif

		Node3& n = gfx::nodes(scene).add(Node3());
		Item& p = gfx::items(scene).add(Item(n, points_model, 0U, &pointmat));

#if INSTANCING
		points_batch = &gfx::batches(scene).add(Batch(p, sizeof(Point)));
		p.m_batch = points_batch;
#endif

#if DYNAMIC
		Model& lines_model = app.m_gfx.create_model("segments");
		lines_mesh = lines_model.m_items[0].m_mesh;

		GpuMesh gpu_mesh = alloc_mesh(PrimitiveType::Lines, VertexAttribute::Position4 | VertexAttribute::Colour, max_segments * 2, 0);
		gpu_mesh.m_dynamic = true;
		lines_mesh->upload(gpu_mesh);
		lines_mesh->m_range = { 0U, 0U };
#else
		static Model& lines_model = app.m_gfx.create_model("cubes");
		static Mesh& mesh = *lines_model.m_items[0].m_mesh;
		mesh.m_is_direct = true;
		lines_mesh = &mesh;
#endif

		Node3& n1 = gfx::nodes(scene).add(Node3());
		Item& lines = gfx::items(scene).add(Item(n1, lines_model, ItemFlag::Default | ItemFlag::NoCull, &linemat));
		UNUSED(lines);
	}

	uint32_t numConnected = 0;

	for(uint32_t i = 0; i < num_particles; i++)
		particles[i].numConnections = 0;

#if INSTANCING
	span<float> memory = points_batch->begin(num_particles);
	span<Point> points = { (Point*)memory.data(), memory.size() * sizeof(float) / sizeof(Point) };
#else
	GpuMesh gpu_points = points_mesh->begin();
#endif

#if DYNAMIC
	GpuMesh gpu_lines = lines_mesh->begin();
#else
	MeshAdapter& direct = lines_mesh->direct();
#endif

	const float delta = app.m_gfx.m_delta_time;

	for(uint32_t i = 0; i < num_particles; i++)
	{
		Particle& particle = particles[i];

		vec3& position = particle.position;
		position += particle.velocity * delta * 20.f;
#if INSTANCING
		points[i] = { position, PAD, vec2(1.f), PAD, PAD };
#else
		gpu_points.m_writer.position(position);
		gpu_points.m_writer.index(i);
#endif

		if(position.y < -r2 || position.y > r2)
			particle.velocity.y = -particle.velocity.y;

		if(position.x < -r2 || position.x > r2)
			particle.velocity.x = -particle.velocity.x;

		if(position.z < -r2 || position.z > r2)
			particle.velocity.z = -particle.velocity.z;

		if(controller.limitConnections && particle.numConnections >= controller.maxConnections)
			continue;

		// Check collision
		for(uint32_t j = i + 1; j < num_particles; j++)
		{
			Particle& other = particles[j];
			if(controller.limitConnections && other.numConnections >= controller.maxConnections)
				continue;

			vec3 d = position - other.position;
			float dist = length(d);

			if(dist < controller.minDistance)
			{
				other.numConnections++;
				other.numConnections++;

				float alpha = 1.f - dist / controller.minDistance;

				gpu_lines.m_writer.position4(vec4(particle.position, 0.f));
				gpu_lines.m_writer.position4(vec4(other.position, dist));
				
				gpu_lines.m_writer.colour(Colour(alpha));
				gpu_lines.m_writer.colour(Colour(alpha));

				numConnected++;
			}
		}
	}

	lines_mesh->update(gpu_lines);
	lines_mesh->m_range = { 0U, numConnected * 2U };

#if !INSTANCING
	points_mesh->update(gpu_points);
#endif

	//const float time = app.m_gfx.m_time;
	//group.rotation.y = time * 0.1;

	//gui.add(effectController, "showDots").onChange(function(value) {
	//
	//	pointCloud.visible = value;
	//
	//});
	//gui.add(effectController, "showLines").onChange(function(value) {
	//
	//	linesMesh.visible = value;
	//
	//});
	//gui.add(effectController, "minDistance", 10, 300);
	//gui.add(effectController, "limitConnections");
	//gui.add(effectController, "maxConnections", 0, 30, 1);
	//gui.add(effectController, "num_particles", 0, max_particles, 1).onChange(function(value) {
	//
	//	num_particles = parseInt(value);
	//	particles.setDrawRange(0, num_particles);
	//
	//});

}