//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

void xx_buffergeometry(Shell& app, Widget& parent, Dockbar& dockbar)
{
	constexpr uint max_particles = 1000;
	constexpr uint num_particles = 500;

	const float r = 800.f;
	const float r2 = r / 2.f;

	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

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

	constexpr uint32_t segments = max_particles * max_particles;

	static Program& pointprog = app.m_gfx_system.programs().fetch("point");
	static Program& lineprog = app.m_gfx_system.programs().fetch("line");

	//Material& material = new THREE.PointsMaterial({ size: 35, sizeAttenuation : false, map : sprite, alphaTest : 0.5, transparent : true });
	static Material& pointmat = app.m_gfx_system.materials().create("point", [&](Material& m) {
		m.m_program = &pointprog;
		m.m_base.m_blend_mode = BlendMode::Add;
		m.m_base.m_geometry_filter = uint32_t(1 << uint(PrimitiveType::Points));
		m.m_alpha.m_is_alpha = true;
		m.m_solid.m_colour = rgb(0xffffff);//hsl(1.f, 0.3f, 0.7f);
		m.m_point.m_project = false;
		m.m_point.m_point_size = 3.f;
	});

	static Material& linemat = app.m_gfx_system.materials().create("line", [&](Material& m) {
		m.m_program = &lineprog;
		m.m_base.m_geometry_filter = uint32_t(1 << uint(PrimitiveType::Lines));
		m.m_base.m_blend_mode = BlendMode::Add;
		m.m_base.m_shader_color = ShaderColor::Vertex;
		m.m_alpha.m_is_alpha = true;
	});

	struct Particle { vec3 position; vec3 velocity; uint32_t numConnections; };
	static vector<Particle> particles;

	static Mesh* points_mesh = nullptr;
	static Mesh* lines_mesh = nullptr;

	static Item* points = nullptr;
	static Item* lines = nullptr;

	static bool once = false;
	if(!once)
	{
		once = true;

		Camera& camera = viewer.m_camera;
		camera.m_near = 1.f; camera.m_far = 4000.f;
		camera.m_eye.z = 1750.f;

		Model& points_model = app.m_gfx_system.models().create("particles");
		points_mesh = &points_model.add_mesh("particles", true);

		MeshPacker pointgeom; // = new THREE.BufferGeometry();
		pointgeom.m_primitive = PrimitiveType::Points;

		for(uint32_t i = 0; i < max_particles; i++)
		{
			vec3 p = vec3(randf(), randf(), randf()) * r - r2;
			vec3 v = vec3(randf(), randf(), randf()) * 2.f - 1.f;
			pointgeom.m_positions.push_back(p);
			pointgeom.m_indices.push_back(i);
			particles.push_back({ p, v, 0U });
		}

		points_mesh->write(pointgeom, false, true);
		points_mesh->m_range = { 0U, num_particles };

		points_model.add_item(*points_mesh, bxidentity());
		points_model.prepare();

		Node3& n = gfx::nodes(scene).add(Node3());
		points = &gfx::items(scene).add(Item(n, points_model, 0U, &pointmat));

		Model& lines_model = app.m_gfx_system.models().create("segments");
		lines_mesh = &lines_model.add_mesh("segments", true);

		GpuMesh gpu_mesh = alloc_mesh(PrimitiveType::Lines, VertexAttribute::Position | VertexAttribute::Colour, segments, segments * 2);
		gpu_mesh.m_dynamic = true;
		lines_mesh->upload(gpu_mesh);
		lines_mesh->m_range = { 0U, 0U };

		//geometry.computeBoundingSphere();

		Node3& n1 = gfx::nodes(scene).add(Node3());
		lines = &gfx::items(scene).add(Item(n1, lines_model, 0U, &linemat));
	}

	uint32_t numConnected = 0;

	for(uint32_t i = 0; i < num_particles; i++)
		particles[i].numConnections = 0;

	GpuMesh gpu_points = points_mesh->begin();
	//GpuMesh gpu_lines = lines_mesh->begin();

	for(uint32_t i = 0; i < num_particles; i++)
	{
		Particle& particle = particles[i];

		vec3& position = particle.position;
		position += particle.velocity;
		gpu_points.m_writer.position(position);
		gpu_points.m_writer.index(i);

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

				//gpu_lines.m_writer.position(particle.position);
				//gpu_lines.m_writer.position(other.position);
				//
				//gpu_lines.m_writer.colour(Colour(alpha));
				//gpu_lines.m_writer.colour(Colour(alpha));

				numConnected++;
			}
		}
	}

	points_mesh->update(gpu_points);

	//lines_mesh->update(gpu_lines);
	//lines_mesh->m_range = { 0U, numConnected * 2U };

	float time = app.m_gfx_system.m_time;
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