#include <mud/mud.h>

using namespace mud;

/*
function onWindowResize() {
	camera.aspect = window.innerWidth / window.innerHeight;
	camera.updateProjectionMatrix();
	renderer.setSize( window.innerWidth, window.innerHeight );
*/

void generateTexture()
{
	var canvas = document.createElement('canvas');
	canvas.width = 2;
	canvas.height = 2;
	var context = canvas.getContext('2d');
	context.fillStyle = 'white';
	context.fillRect(0, 1, 2, 1);
	return canvas;
}

void ex_xx_three_shadow_point(Shell& app, Widget& parent, Dockbar& dockbar)
{
	SceneViewer& viewer = ui::scene_viewer(parent);
	ui::orbit_controller(viewer);

	//camera = new THREE.PerspectiveCamera( 45, window.innerWidth / window.innerHeight, 1, 1000 );
	//camera.position.set( 0, 10, 40 );
	//scene = new THREE.Scene();
	//scene.add( new THREE.AmbientLight( 0x111122 ) );

	//renderer = new THREE.WebGLRenderer({ antialias: true });
	//renderer.setPixelRatio(window.devicePixelRatio);
	//renderer.setSize(window.innerWidth, window.innerHeight);
	//renderer.shadowMap.enabled = true;
	//renderer.shadowMap.type = THREE.BasicShadowMap;
	//document.body.appendChild(renderer.domElement);
	//var controls = new THREE.OrbitControls(camera, renderer.domElement);
	//controls.target.set(0, 10, 0);
	//controls.update();

	//var texture = new THREE.CanvasTexture(generateTexture());
	//texture.magFilter = THREE.NearestFilter;
	//texture.wrapT = THREE.RepeatWrapping;
	//texture.wrapS = THREE.RepeatWrapping;
	//texture.repeat.set(1, 3.5);

	Material material;
	//material.m_base_block.
	//var material = new THREE.MeshPhongMaterial( {
	//	side: THREE.DoubleSide,
	//	alphaMap: texture,
	//	alphaTest: 0.5
	//} );
		
	//var material = new THREE.MeshPhongMaterial( {
	//	color: 0xa0adaf,
	//	shininess: 10,
	//	specular: 0x111111,
	//	side: THREE.BackSide
	//} );

	auto light_source = [](Gnode& parent, Colour color, vec3 pos, quat rot) -> Gnode&
	{
		float intensity = 1.5;
		float range = 20.f;

		Gnode& node = gfx::node(parent, {}, pos, rot);
		Light& light = gfx::light(node, LightType::Point, true, color, range, intensity);
		//pointLight.shadow.camera.near = 1;
		//pointLight.shadow.camera.far = 60;
		//pointLight.shadow.bias = - 0.005; // reduces self-shadowing on double-sided objects
		
		//var geometry = new THREE.SphereBufferGeometry( 0.3, 12, 6 );
		//var material = new THREE.MeshBasicMaterial( { color: color } );
		//material.color.multiplyScalar( intensity );
		Item& inner = gfx::shape(node, Sphere(0.3), Symbol::plain(color * intensity));
		//var sphere = new THREE.Mesh( geometry, material );
		//light.add( sphere );
		
		//var geometry = new THREE.SphereBufferGeometry( 2, 32, 8 );
		Item& outer = gfx::shape(node, Sphere(2.0), Symbol::plain(Colour::White));
		//var sphere = new THREE.Mesh( geometry, material );
		//sphere.castShadow = true;
		//sphere.receiveShadow = true;
		//light.add( sphere );

		// custom distance material
		//var distanceMaterial = new THREE.MeshDistanceMaterial( {
		//	alphaMap: material.alphaMap,
		//	alphaTest: material.alphaTest
		//} );
		//sphere.customDistanceMaterial = distanceMaterial;
		return node;
	};

	auto light_pos = [](float time) -> vec3
	{
		return { sin(time * 0.6) * 9, sin(time * 0.7) * 9 + 5, sin(time * 0.8) * 9 };
	};

	auto light_rot = [](float time) -> vec3
	{
		return { time, 0.f, time };
	};

	Gnode& scene = viewer.m_scene->begin();

	double time = app.m_gfx_system.m_frame_time;//performance.now() * 0.001;
	vec3 pos0 = light_pos(time);
	quat rot0 = light_rot(time);
	Gnode& light0 = light_source(scene, from_rgba(0x0088ff), pos0, rot0);

	time += 10000;
	vec3 pos1 = light_pos(time);
	quat rot1 = light_rot(time);
	Gnode& light1 = light_source(scene, from_rgba(0xff8888), pos1, rot1);

	//renderer.render(scene, camera);

	Box box = Cube(vec3(30.f));
	//var geometry = new THREE.BoxBufferGeometry( 30, 30, 30 );

	Gnode& node = gfx::node(scene, {}, Y3 * 10.f);
	gfx::shape(node, box, Symbol::plain(Colour::White));
	//var mesh = new THREE.Mesh( geometry, material );
	//mesh.position.y = 10;
	//mesh.receiveShadow = true;
	//scene.add( mesh );
}


#ifdef _XX_THREE_EXE
void pump(Shell& app)
{
	edit_context(app.m_ui->begin(), app.m_editor, true);
	ex_xx_three_shadow_point(app, *app.m_editor.m_screen, *app.m_editor.m_dockbar);
}

int main(int argc, char *argv[])
{
	cstring example_path = MUD_RESOURCE_PATH "examples/17_wfc/";
	Shell app(carray<cstring, 2>{ MUD_RESOURCE_PATH, example_path }, argc, argv);
	app.run(pump);
}
#endif
