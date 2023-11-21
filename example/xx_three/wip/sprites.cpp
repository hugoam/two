module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;

using namespace two;

#define CLUSTERED 1

EX(xx_sprites)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

#if UI
	ui::orbit_controls(viewer);
#endif

	//SceneViewer& overlay = ui::scene_viewer(parent);

	//cameraOrtho = new THREE.OrthographicCamera(- width / 2, width / 2, height / 2, - height / 2, 1, 10);
	//cameraOrtho.position.z = 10;

	// create sprites

	float amount = 200;
	float radius = 500;

	Texture& sprites0 = *app.m_gfx.textures().file("sprite0.png");

	Material& material = app.m_gfx.materials().create("sprite0", [](Material& m) {
		//m.m_program = SpriteMaterial;
		//m.m_sprite.m_color = sprites0;
	}); // new THREE.SpriteMaterial({ map: texture });

	if(init)
	{
		Camera& camera = viewer.m_camera;
		camera.m_fov = 60.f; camera.m_near = 1.f; camera.m_far = 2100.f;
		camera.m_eye.z = 1500.f;

		scene.m_env.m_fog = { true, 1.f, rgb(0x000000), true, 1500.f, 2100.f };

		//
		//var width = material.map.image.width;
		//var height = material.map.image.height;
		//
		//spriteTL = new THREE.Sprite(material);
		//spriteTL.center.set(0.0, 1.0);
		//spriteTL.scale.set(width, height, 1);
		//sceneOrtho.add(spriteTL);
		//
		//spriteTR = new THREE.Sprite(material);
		//spriteTR.center.set(1.0, 1.0);
		//spriteTR.scale.set(width, height, 1);
		//sceneOrtho.add(spriteTR);
		//
		//spriteBL = new THREE.Sprite(material);
		//spriteBL.center.set(0.0, 0.0);
		//spriteBL.scale.set(width, height, 1);
		//sceneOrtho.add(spriteBL);
		//
		//spriteBR = new THREE.Sprite(material);
		//spriteBR.center.set(1.0, 0.0);
		//spriteBR.scale.set(width, height, 1);
		//sceneOrtho.add(spriteBR);
		//
		//spriteC = new THREE.Sprite(material);
		//spriteC.center.set(0.5, 0.5);
		//spriteC.scale.set(width, height, 1);
		//sceneOrtho.add(spriteC);
		//
		//updateHUDSprites();
	}

	Texture& mapB = *app.m_gfx.textures().file("sprite1.png");
	Texture& mapC = *app.m_gfx.textures().file("sprite2.png");

	//group = new THREE.Group();

	Material& materialC = app.m_gfx.materials().create("sprite0", [](Material& m) {
		});
	//new THREE.SpriteMaterial({ map: mapC, color : 0xffffff, fog : true });

	Material& materialB = app.m_gfx.materials().create("sprite0", [](Material& m) {
		});
	//new THREE.SpriteMaterial({ map: mapB, color: 0xffffff, fog: true });

	for(int a = 0; a < amount; a++)
	{
		float x = randf() - 0.5f;
		float y = randf() - 0.5f;
		float z = randf() - 0.5f;

		Material& material = materialB;

		if(z < 0) {

			//material = materialB.clone();

		}
		else {

			//material = materialC.clone();
			material.m_solid.m_colour = hsl(0.5f * randf(), 0.75f, 0.5f);
			material.m_base.m_uv0_offset = { -0.5f, -0.5f };
			material.m_base.m_uv0_scale = { 2.f, 2.f };
		}

		//var sprite = new THREE.Sprite(material);
		//
		//sprite.position.set(x, y, z);
		//sprite.position.normalize();
		//sprite.position.multiplyScalar(radius);
		//
		//group.add(sprite);
	}

	//scene.add(group);


	auto updateHUDSprites = []() {

		//var width = window.innerWidth / 2;
		//var height = window.innerHeight / 2;
		//
		//spriteTL.position.set(-width, height, 1); // top left
		//spriteTR.position.set(width, height, 1); // top right
		//spriteBL.position.set(-width, -height, 1); // bottom left
		//spriteBR.position.set(width, -height, 1); // bottom right
		//spriteC.position.set(0, 0, 1); // center

	};

	float time = app.m_gfx.m_time;

	/*
	for(int i = 0, l = group.children.length; i < l; i++) {

		var sprite = group.children[i];
		var material = sprite.material;
		var scale = sin(time + sprite.position.x * 0.01) * 0.3 + 1.0;

		var imageWidth = 1;
		var imageHeight = 1;

		if(material.map && material.map.image && material.map.image.width) {

			imageWidth = material.map.image.width;
			imageHeight = material.map.image.height;

		}

		sprite.material.rotation += 0.1 * (i / l);
		sprite.scale.set(scale * imageWidth, scale * imageHeight, 1.0);

		if(material.map != = mapC) {

			material.opacity = sin(time + sprite.position.x * 0.01) * 0.4 + 0.6;

		}

	}

	group.rotation.x = time * 0.5;
	group.rotation.y = time * 0.75;
	group.rotation.z = time * 1.0;

	renderer.clear();
	renderer.render(scene, camera);
	renderer.clearDepth();
	renderer.render(sceneOrtho, cameraOrtho);
	*/
}