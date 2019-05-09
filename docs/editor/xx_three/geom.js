//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

#define INSTANCING 1

using namespace mud;

void xx_geom(Shell app, var parent, Dockbar dockbar)
{
	constexpr uvar max_particles = 1000;
	constexpr uvar nuparticles = 500;

	var r = 800.0;
	var r2 = r / 2.0;

	var viewer = two.ui.scene_viewer(panel);
	two.ui.orbit_controller(viewer);

	var scene = viewer.scene;

	struct EffectController
	{
		bool showDots = true;
		bool showLines = true;
		var minDistance = 150.0;
		bool limitConnections = false;
		uvar maxConnections = 20;
		uvar nuparticles = 500;
	};
	
	EffectController controller;

	//var helper = new THREE.BoxHelper(new THREE.Mesh(new THREE.BoxBufferGeometry(r, r, r)));
	//helper.material.color.setHex(0x080808);
	//helper.material.blending = THREE.AdditiveBlending;
	//helper.material.transparent = true;
	//group.add(helper);

	constexpr uint32_t segments = max_particles * max_particles;

	this.pointprog = app.gfx.programs.fetch('point');
	this.lineprog = app.gfx.programs.fetch('line');

	//var material = new THREE.PointsMaterial({ size: 35, sizeAttenuation : false, map : sprite, alphaTest : 0.5, transparent : true });
	this.pointmat = app.gfx.materials.create('point'); var m = material;
		m.program = pointprog;
		m.base.blend_mode = BlendMode::Add;
#if INSTANCING
		m.base.geometry_filter = uint32_t(1 << uint(PrimitiveType::Triangles));
#else
		m.base.geometry_filter = uint32_t(1 << uint(PrimitiveType::Points));
#endif
		m.alpha.is_alpha = true;
		m.solid.colour = two.rgb(0xffffff);//two.hsl(1.0, 0.3, 0.7);
		m.point.project = false;
		m.point.point_size = 3.0;
	});

	this.linemat = app.gfx.materials.create('line'); var m = material;
		m.program = lineprog;
		m.base.geometry_filter = uint32_t(1 << uint(PrimitiveType::Lines));
		m.base.blend_mode = BlendMode::Add;
		m.base.shader_color = ShaderColor::Vertex;
		m.alpha.is_alpha = true;
	});

	struct Particle { var position; var velocity; uint32_t numConnections; };
	vector<Particle> particles;

	Mesh* points_mesh = nullptr;
	Mesh* lines_mesh = nullptr;

#if INSTANCING
	this.points_batch = nullptr;
	this.lines_batch = nullptr;
#endif

	bool once = false;
	if(!once)
	{
		once = true;

		var camera = viewer.camera;
		camera.near = 1.0; camera.far = 4000.0;
		camera.eye.z = 1750.0;

#if INSTANCING
		var points_model = app.gfx.models.get('point');
#else
		MeshPacker pointgeom; // = new THREE.BufferGeometry();
		pointgeom.primitive = PrimitiveType::Points;
#endif

		for(uint32_t i = 0; i < max_particles; i++)
		{
			var p = new two.vec3(Math.random(), Math.random(), Math.random()) * r - r2;
			var v = new two.vec3(Math.random(), Math.random(), Math.random()) * 2.0 - 1.0;
#if !INSTANCING
			pointgeom.positions.push(p);
			pointgeom.indices.push(i);
#endif
			particles.push({ p, v, 0 });
		}

#if !INSTANCING
		var model = app.gfx.create_model('particles', geometry, false, dynamic = true);
		points_mesh->range = { 0, nuparticles };
#endif

		var n = scene.nodes().add(new two.Node3());
		var p = scene.items().add(new two.Item(n, points_model, 0, pointmat));

#if INSTANCING
		points_batch = two.gfx.batches(scene).add(new two.Batch(p));
		p.batch = points_batch;
#endif

		var lines_model = app.gfx.models.create('segments');
		lines_mesh = lines_model.add_mesh('segments', true);

		GpuMesh gpu_mesh = alloc_mesh(PrimitiveType::Lines, VertexAttribute::Position | VertexAttribute::Colour, segments, segments * 2);
		gpu_mesh.dynamic = true;
		lines_mesh->upload(gpu_mesh);
		lines_mesh->range = { 0, 0 };

		//geometry.computeBoundingnew two.Sphere();

		var n1 = scene.nodes().add(new two.Node3());
		var lines = scene.items().add(new two.Item(n1, lines_model, 0, linemat));
	}

	uint32_t numConnected = 0;

	for(uint32_t i = 0; i < nuparticles; i++)
		particles[i].numConnections = 0;

#if INSTANCING
	struct Povar { vec4 d0; vec4 d1; };
	span<float> memory = points_batch->begin(nuparticles, sizeof(Point));
	span<Point> points = { (Point*)memory.data(), memory.length * sizeof(float) / sizeof(Point) };
#else
	GpuMesh gpu_points = points_mesh->begin();
	GpuMesh gpu_lines = lines_mesh->begin();
#endif

	for(uint32_t i = 0; i < nuparticles; i++)
	{
		Particle particle = particles[i];

		vec3 position = particle.position;
		position += particle.velocity;
#if INSTANCING
		points[i] = { new two.vec4(position, 0.0), new two.vec4(new two.vec2(1.0), new two.vec2(0.0)) };
#else
		gpu_points.writer.position(position);
		gpu_points.writer.index(i);
#endif

		if(position.y < -r2 || position.y > r2)
			particle.velocity.y = -particle.velocity.y;

		if(position.x < -r2 || position.x > r2)
			particle.velocity.x = -particle.velocity.x;

		if(position.z < -r2 || position.z > r2)
			particle.velocity.z = -particle.velocity.z;

		if(controller.limitConnections  particle.numConnections >= controller.maxConnections)
			continue;

		// Check collision
		for(uint32_t j = i + 1; j < nuparticles; j++)
		{
			Particle other = particles[j];
			if(controller.limitConnections  other.numConnections >= controller.maxConnections)
				continue;

			var d = position - other.position;
			var dist = length(d);

			if(dist < controller.minDistance)
			{
				other.numConnections++;
				other.numConnections++;

				var alpha = 1.0 - dist / controller.minDistance;

#if INSTANCING
#else
				gpu_lines.writer.position(particle.position);
				gpu_lines.writer.position(other.position);
				
				gpu_lines.writer.colour(new two.Colour(alpha));
				gpu_lines.writer.colour(new two.Colour(alpha));
#endif

				numConnected++;
			}
		}
	}

#if INSTANCING
#else
	points_mesh->update(gpu_points);

	lines_mesh->update(gpu_lines);
	lines_mesh->range = { 0, numConnected * 2U };
#endif

	var time = app.gfx.time;
	//group.rotation.y = time * 0.1;

	//gui.add(effectController, 'showDots').onChange(function(value) {
	//
	//	pointCloud.visible = value;
	//
	//});
	//gui.add(effectController, 'showLines').onChange(function(value) {
	//
	//	linesMesh.visible = value;
	//
	//});
	//gui.add(effectController, 'minDistance', 10, 300);
	//gui.add(effectController, 'limitConnections');
	//gui.add(effectController, 'maxConnections', 0, 30, 1);
	//gui.add(effectController, 'nuparticles', 0, max_particles, 1).onChange(function(value) {
	//
	//	nuparticles = parseInt(value);
	//	particles.setDrawRange(0, nuparticles);
	//
	//});

}