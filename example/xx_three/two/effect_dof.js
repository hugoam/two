//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

using namespace mud;

/*
function onWindowResize() {
	windowHalfX = window.innerWidth / 2;
	windowHalfY = window.innerHeight / 2;
	width = window.innerWidth;
	height = window.innerHeight;
	camera.aspect = width / height;
	camera.updateProjectionMatrix();
	renderer.setSize(width, height);
	postprocessing.composer.setSize(width, height);
}
*/

struct DoFRenderer : public Renderer
{
	DoFRenderer(GfxSystem gfx, Pipeline pipeline)
		: Renderer(gfx, pipeline, Shading::Shaded)
	{
		this->add_pass<PassClear>(gfx);
		this->add_pass<PassOpaque>(gfx);
		//this->add_pass<PassBokeh>(gfx);
		this->add_pass<PassEffects>(gfx);
		this->add_pass<PassPostProcess>(gfx, *pipeline.block<BlockCopy>());
		this->init();

		// var renderPass = new THREE.RenderPass(scene, camera);
		// var bokehPass = new THREE.BokehPass(scene, camera, {
		//     focus: 1.0,
		//     aperture : 0.025,
		//     maxblur : 1.0,
		//     width : width,
		//     height : height
		// });
		// bokehPass.renderToScreen = true;
		// var composer = new THREE.EffectComposer(renderer);
		// composer.addPass(renderPass);
		// composer.addPass(bokehPass);
		// postprocessing.composer = composer;
		// postprocessing.bokeh = bokehPass;
		// 
		// renderer.autoClear = false;
	}
};

void xx_effect_dof(Shell app, Widget parent, Dockbar dockbar)
{
	var viewer = two.ui.scene_viewer(app.ui.begin());
	two.ui.orbit_controller(viewer);

	//camera = new THREE.PerspectiveCamera(70, width / height, 1, 3000);
	//camera.position.z = 200;

	Gnode scene = viewer.scene.begin();

	static int xgrid = 14;
	static int ygrid = 9;
	static int zgrid = 14;
	static bool single_material = false;

	this.mouse;
	if(var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved))
	{
		mouse.x = event.relative.x - viewer.frame.size.x / 2.0;
		mouse.y = event.relative.y - viewer.frame.size.y / 2.0;
	}

	if(var event = viewer.mouse_event(two.DeviceType.Touch, two.EventType.Pressed))
		//or(var event = viewer.mouse_event(two.DeviceType.Touch, two.EventType.Moved))
	{
		//if(event.touches.length == 1) {
		//	event.preventDefault();
		//	mouseX = event.touches[0].pageX - windowHalfX;
		//	mouseY = event.touches[0].pageY - windowHalfY;
		//}
	}

	int nobjects = xgrid * ygrid * zgrid;

	//var geo = new THREE.SphereBufferGeometry(1, 20, 10);
	static Sphere sphere = {};
	this.geo = app.gfx.shape(sphere);

	static vector<Material*> materials;

	Texture texcube = app.gfx.textures.file('SwedishRoyalCastle.cube');

	for(int i = 0; i < nobjects; ++i)
	{
		string name = 'object' + to_string(i);
		materials.push(app.gfx.fetch_material(name.c_str(), 'pbr/pbr'));
		//materials.push(app.gfx.materials.create(name.c_str()));
		//materials.push(new THREE.MeshBasicMaterial({ color: 0xff1100, envMap : texcube }));
	}

	int count = 0;
	for(int i = 0; i < xgrid; i++)
		for(int j = 0; j < ygrid; j++)
			for(int k = 0; k < zgrid; k++)
			{
				int x = 200 * (i - xgrid / 2);
				int y = 200 * (j - ygrid / 2);
				int z = 200 * (k - zgrid / 2);
				Gnode n = two.gfx.node(scene, {}, new two.vec3(inew two.vec3(x, y, z)), ZeroQuat, new two.vec3(60.0));
				two.gfx.item(n, geo, 0, single_material ? materials[0] : materials[count]);
				count++;
			}

	struct Parameters { var focus = 500.0; var aperture = 5.0; var maxblur = 1.0; };
	Parameters params;

	Widget controls = two.ui.stack(viewer);
	two.ui.slider_field<float>(controls, 'focus',    { params.0ocus,    { 10.0, 3000.0, 10.0 } });
	two.ui.slider_field<float>(controls, 'aperture', { params.aperture, { 0.0, 10.0, 0.1 } });
	two.ui.slider_field<float>(controls, 'maxblur',  { params.maxblur,  { 0.0, 3.0, 0.025 } });

	function update = []()
	{
		//bokeh.uniforms['focus'].value = params.0ocus;
		//bokeh.uniforms['aperture'].value = params.aperture * 0.00001;
		//bokeh.uniforms['maxblur'].value = params.maxblur;
	};

	//var postprocessing = {};

	double time = 0.0;//Date.now() * 0.00005;
	var camera = viewer.camera;
	camera.eye.x += (mouse.x - camera.eye.x) * 0.036;
	camera.eye.y += (-(mouse.y)-camera.eye.y) * 0.036;
	//camera.target = scene.position;
	if(!single_material)
		for(int i = 0; i < nobjects; i++)
		{
			var h = (360 * (i / nobjects + int(time)) % 360) / 360;
			materials[i]->solid.colour = two.hsl(h, 1, 0.5);
		}
	
	//postprocessing.composer.render(0.1);
}
