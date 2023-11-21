module;
#include <infra/Cpp20.h>
#include <xx_three/ex.h>
module two.xxthree;

using namespace two;

static string shader_vertex = 

R"'(
	varying vec2 v_uv0;

	void main()
	{
		v_uv0 = uv;
		vec4 mvPosition = mul(u_modelView, vec4(a_position.xyz, 1.0));
		gl_Position = u_proj * mvPosition;
	}
)'";


static string shader4_fragment =

R"'(
	uniform float time;

	varying vec2 v_uv0;

	void main(void)
	{
		vec2 position = - 1.0 + 2.0 * v_uv0;

		float red = abs(sin(position.x * position.y + time / 5.0));
		float green = abs(sin(position.x * position.y + time / 4.0));
		float blue = abs(sin(position.x * position.y + time / 3.0));
		gl_FragColor = vec4(red, green, blue, 1.0);
	}
)'";

static string shader3_fragment =

R"'(
	uniform float time;

	varying vec2 v_uv0;

	void main(void)
	{
		vec2 position = v_uv0;

		float color = 0.0;
		color += sin(position.x * cos(time / 15.0) * 80.0) + cos(position.y * cos(time / 15.0) * 10.0);
		color += sin(position.y * sin(time / 10.0) * 40.0) + cos(position.x * sin(time / 25.0) * 40.0);
		color += sin(position.x * sin(time / 5.0) * 10.0) + sin(position.y * sin(time / 35.0) * 80.0);
		color *= sin(time / 10.0) * 0.5;

		gl_FragColor = vec4(vec3(color, color * 0.5, sin(color + time / 3.0) * 0.75), 1.0);
	}
)'";


static string shader2_fragment =

R"'(
	uniform float time;

	uniform sampler2D texture;

	varying vec2 v_uv0;

	void main(void) {

		vec2 position = - 1.0 + 2.0 * v_uv0;

		float a = atan(position.y, position.x);
		float r = sqrt(dot(position, position));

		vec2 uv;
		uv.x = cos(a) / r;
		uv.y = sin(a) / r;
		uv /= 10.0;
		uv += time * 0.05;

		vec3 color = texture2D(texture, uv).rgb;

		gl_FragColor = vec4(color * r * 1.5, 1.0);

	}
)'";

static string shader1_fragment =

R"'(
	uniform float time;

	varying vec2 v_uv0;

	void main(void) {

		vec2 p = - 1.0 + 2.0 * v_uv0;
		float a = time * 40.0;
		float d, e, f, g = 1.0 / 40.0 ,h ,i ,r ,q;

		e = 400.0 * (p.x * 0.5 + 0.5);
		f = 400.0 * (p.y * 0.5 + 0.5);
		i = 200.0 + sin(e * g + a / 150.0) * 20.0;
		d = 200.0 + cos(f * g / 2.0) * 18.0 + cos(e * g) * 7.0;
		r = sqrt(pow(abs(i - e), 2.0) + pow(abs(d - f), 2.0));
		q = f / r;
		e = (r * cos(q)) - a / 2.0;
		f = (r * sin(q)) - a / 2.0;
		d = sin(e * g) * 176.0 + sin(e * g) * 164.0 + r;
		h = ((f + d) + a / 2.0) * g;
		i = cos(h + r * p.x / 1.3) * (e + e + a) + cos(q * g * 6.0) * (r + h / 3.0);
		h = sin(f * g) * 144.0 - sin(e * g) * 212.0 * p.x;
		h = (h + (f - e) * q + sin(r - (a + h) / 7.0) * 10.0 + i / 4.0) * g;
		i += cos(h * 2.3 * sin(a / 350.0 - q)) * 184.0 * sin(q - (r * 4.3 + a / 12.0) * g) + tan(r * g + h) * 184.0 * cos(r * g + h);
		i = mod(i / 5.6, 256.0) / 64.0;
		if (i < 0.0) i += 4.0;
		if (i >= 2.0) i = 4.0 - i;
		d = r / 350.0;
		d += sin(d * d * 8.0) * 0.52;
		f = (sin(a * g) + 1.0) / 2.0;
		gl_FragColor = vec4(vec3(f * i / 1.6, i / 2.0 + d / 13.0, i) * d * p.x + vec3(i / 1.3 + d / 8.0, i / 2.0 + d / 18.0, i) * d * (1.0 - p.x), 1.0);
	}
)'";

EX(xx_shader2)
{
#if UI
	UNUSED(dockbar);
	SceneViewer& viewer = ui::scene_viewer(parent);
	Scene& scene = viewer.m_scene;
#else
	static Scene scene = Scene(app.m_gfx);
	static GfxViewer viewer = GfxViewer(window, scene);
#endif

	if(init)
	{
#if 0
		camera = new THREE.PerspectiveCamera(40, window.innerWidth / window.innerHeight, 1, 3000);
		camera.position.z = 4;

		scene = new THREE.Scene();

		clock = new THREE.Clock();

		var geometry = new THREE.BoxBufferGeometry(0.75, 0.75, 0.75);
		
		uniforms1 = {
			"time": { value: 1.0 }
		};

		uniforms2 = {
			"time": { value: 1.0 },
			"texture": { value: new THREE.TextureLoader().load('textures/disturb.jpg') }
		};

		uniforms2["texture"].value.wrapS = uniforms2["texture"].value.wrapT = THREE.RepeatWrapping;

		var params = [
			['fragment_shader1', uniforms1],
			['fragment_shader2', uniforms2],
			['fragment_shader3', uniforms1],
			['fragment_shader4', uniforms1]
		];

		for(var i = 0; i < params.length; i ++) {

			var material = new THREE.ShaderMaterial({

				uniforms: params[i][1],
				vertexShader: document.getElementById('vertexShader').textContent,
				fragmentShader: document.getElementById(params[i][0]).textContent

			});

			var mesh = new THREE.Mesh(geometry, material);
			mesh.position.x = i - (params.length - 1) / 2;
			mesh.position.y = i % 2 - 0.5;
			scene.add(mesh);

		}
#endif
	}
		
#if 0
	var delta = clock.getDelta();

	uniforms1["time"].value += delta * 5;
	uniforms2["time"].value = clock.elapsedTime;

	for(var i = 0; i < scene.children.length; i ++) {

		var object = scene.children[i];

		object.rotation.y += delta * 0.5 * (i % 2 ? 1 : - 1);
		object.rotation.x += delta * 0.5 * (i % 2 ? - 1 : 1);

	}

	renderer.render(scene, camera);
#endif
}