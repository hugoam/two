//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>


void xx_billboards(Shell& app, Widget& parent, Dockbar& dockbar)
{
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	//camera = new THREE.PerspectiveCamera(55, window.innerWidth / window.innerHeight, 2, 2000);
	//camera.position.z = 1000;

	//scene.fog = new THREE.FogExp2(0x000000, 0.001);

	static bool once = false;
	if(!once)
	{
		once = true;

		MeshPacker geometry;

		for(int i = 0; i < 10000; i++)
		{
			float x = 2000.f * random_scalar<float>() - 1000.f;
			float y = 2000.f * random_scalar<float>() - 1000.f;
			float z = 2000.f * random_scalar<float>() - 1000.f;

			geometry.m_positions.push_back({ x, y, z });

		}

		//geometry.addAttribute('position', new THREE.Float32BufferAttribute(vertices, 3));

		Texture& sprite = *app.m_gfx_system.textures().file("textures/sprites/disc.png");

		//Material& material = new THREE.PointsMaterial({ size: 35, sizeAttenuation : false, map : sprite, alphaTest : 0.5, transparent : true });
		//material.color.setHSL(1.0, 0.3, 0.7);
		//
		//var particles = new THREE.Points(geometry, material);
		//scene.add(particles);
	}


	//var gui = new dat.GUI();
	//
	//gui.add(material, 'sizeAttenuation').onChange(function() {
	//	material.needsUpdate = true;
	//});
	//
	//gui.open();

	float time = app.m_gfx_system.m_time;

	float mouseX; float mouseY;
	viewer.m_camera.m_eye.x += (mouseX - viewer.m_camera.m_eye.x) * 0.05f;
	viewer.m_camera.m_eye.y += (-mouseY - viewer.m_camera.m_eye.y) * 0.05f;

	//viewer.m_camera.m_target = scene.position;

	float h = fmod(360.f * (1.f + time), 360.f) / 360.f;
	//material.color.setHSL(h, 0.5f, 0.5f);
}