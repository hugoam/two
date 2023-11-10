//#include <mud/frame.h>
#include <frame/Api.h>
#include <gfx-pbr/Api.h>

#include <xx_three/xx_three.h>

#include <stl/vector.hpp>

using namespace mud;

var vertex_merged()
{
	var shader =

		'#define SHADER_NAME vertMerged\n'
		'\n'
		'precision highp float;\n'
		'\n'
		'uniform mat4 modelViewMatrix;\n'
		'uniform mat4 projectionMatrix;\n'
		'\n'
		'attribute var position;\n'
		'#ifdef PICKING\n'
		'	attribute var pickingColor;\n'
		'#else\n'
		'	attribute var color;\n'
		'	varying var vPosition;\n'
		'#endif\n'
		'\n'
		'varying var vColor;\n'
		'\n'
		'void main()	{\n'
		'\n'
		'	var positionEye = (modelViewMatrix * new two.vec4(position, 1.0)).xyz;\n'
		'\n'
		'	#ifdef PICKING\n'
		'		vColor = pickingColor;\n'
		'	#else\n'
		'		vColor = color;\n'
		'		vPosition = positionEye;\n'
		'	#endif\n'
		'\n'
		'	gl_Position = projectionMatrix * new two.vec4(positionEye, 1.0);\n'
		'\n'
		'}\n';

	return shader;
}

var fragment_merged()
{
	var shader =

		'#define SHADER_NAME fragMerged\n'
		'\n'
		'#extension GL_OES_standard_derivatives : enable\n'
		'\n'
		'precision highp float;\n'
		'\n'
		'varying var vColor;\n'
		'\n'
		'#ifndef PICKING\n'
		'	varying var vPosition;\n'
		'#endif\n'
		'\n'
		'void main()	{\n'
		'\n'
		'	#ifdef PICKING\n'
		'		gl_FragColor = new two.vec4(vColor, 1.0);\n'
		'	#else\n'
		'		var fdx = dFdx(vPosition);\n'
		'		var fdy = dFdy(vPosition);\n'
		'		var normal = normalize(cross(fdx, fdy));\n'
		'		var diffuse = dot(normal, new two.vec3(0.0, 0.0, 1.0));\n'
		'\n'
		'		gl_FragColor = new two.vec4(diffuse * vColor, 1.0);\n'
		'	#endif\n'
		'\n'
		'}\n';

	return shader;
}

var vertex_instanced()
{
	var shader =

		'#define SHADER_NAME vertInstanced\n'
		'\n'
		'precision highp float;\n'
		'\n'
		'uniform mat4 modelViewMatrix;\n'
		'uniform mat4 projectionMatrix;\n'
		'\n'
		'attribute var position;\n'
		'attribute var mcol0;\n'
		'attribute var mcol1;\n'
		'attribute var mcol2;\n'
		'attribute var mcol3;\n'
		'\n'
		'#ifdef PICKING\n'
		'	attribute var pickingColor;\n'
		'#else\n'
		'	attribute var color;\n'
		'	varying var vPosition;\n'
		'#endif\n'
		'\n'
		'varying var vColor;\n'
		'\n'
		'void main()	{\n'
		'\n'
		'	mat4 matrix = mat4(\n'
		'		new two.vec4(mcol0, 0),\n'
		'		new two.vec4(mcol1, 0),\n'
		'		new two.vec4(mcol2, 0),\n'
		'		new two.vec4(mcol3, 1)\n'
		'	);\n'
		'\n'
		'	var positionEye = (modelViewMatrix * matrix * new two.vec4(position, 1.0)).xyz;\n'
		'\n'
		'	#ifdef PICKING\n'
		'		vColor = pickingColor;\n'
		'	#else\n'
		'		vColor = color;\n'
		'		vPosition = positionEye;\n'
		'	#endif\n'
		'\n'
		'	gl_Position = projectionMatrix * new two.vec4(positionEye, 1.0);\n'
		'\n'
		'}\n';

	return shader;
}

var fragment_instanced()
{
	var shader =

		'#define SHADER_NAME fragInstanced\n'
		'\n'
		'#extension GL_OES_standard_derivatives : enable\n'
		'\n'
		'precision highp float;\n'
		'\n'
		'varying var vColor;\n'
		'\n'
		'#ifndef PICKING\n'
		'	varying var vPosition;\n'
		'#endif\n'
		'\n'
		'void main()	{\n'
		'\n'
		'	#ifdef PICKING\n'
		'		gl_FragColor = new two.vec4(vColor, 1.0);\n'
		'	#else\n'
		'		var fdx = dFdx(vPosition);\n'
		'		var fdy = dFdy(vPosition);\n'
		'		var normal = normalize(cross(fdx, fdy));\n'
		'		var diffuse = dot(normal, new two.vec3(0.0, 0.0, 1.0));\n'
		'\n'
		'		gl_FragColor = new two.vec4(diffuse * vColor, 1.0);\n'
		'	#endif\n'
		'\n'
		'}\n';

	return shader;
}

var vertex_material()
{
	var shader =

		'#define SHADER_NAME vertMaterial\n'
		'\n'
		'precision highp float;\n'
		'\n'
		'uniform mat4 modelViewMatrix;\n'
		'uniform mat4 projectionMatrix;\n'
		'\n'
		'attribute var position;\n'
		'\n'
		'#ifndef PICKING\n'
		'	varying var vPosition;\n'
		'#endif\n'
		'\n'
		'void main()	{\n'
		'\n'
		'	var positionEye = (modelViewMatrix * new two.vec4(position, 1.0)).xyz;\n'
		'\n'
		'	#ifndef PICKING\n'
		'		vPosition = positionEye;\n'
		'	#endif\n'
		'\n'
		'	gl_Position = projectionMatrix * new two.vec4(positionEye, 1.0);\n'
		'\n'
		'}\n';

	return shader;
}

var fragment_material()
{
	var shader =

		'#define SHADER_NAME fragMaterial\n'
		'\n'
		'#extension GL_OES_standard_derivatives : enable\n'
		'\n'
		'precision highp float;\n'
		'\n'
		'#ifdef PICKING\n'
		'	uniform var pickingColor;\n'
		'#else\n'
		'	uniform var color;\n'
		'	varying var vPosition;\n'
		'#endif\n'
		'\n'
		'void main()	{\n'
		'\n'
		'	#ifdef PICKING\n'
		'		gl_FragColor = new two.vec4(pickingColor, 1.0);\n'
		'	#else\n'
		'		var fdx = dFdx(vPosition);\n'
		'		var fdy = dFdy(vPosition);\n'
		'		var normal = normalize(cross(fdx, fdy));\n'
		'		var diffuse = dot(normal, new two.vec3(0.0, 0.0, 1.0));\n'
		'\n'
		'		gl_FragColor = new two.vec4(diffuse * color, 1.0);\n'
		'	#endif\n'
		'\n'
		'}\n';

	return shader;
}

#if 0
<div style='display:inline-block;'>
	<span>number of<br/>geometry instances</span>
	<br/>
	<select id='instanceCount'>
		<option>100</option>
		<option>500</option>
		<option selected>1000</option>
		<option>2000</option>
		<option>3000</option>
		<option>5000</option>
		<option>10000</option>
		<option>20000</option>
		<option>30000</option>
		<option>50000</option>
		<option>100000</option>
	</select>
</div>

nbsp;nbsp;nbsp;

<div style='display:inline-block;'>
	<span>method of<br/>construction/rendering</span>
	<br/>
	<select id='method'>
		<option>instanced</option>
		<option>merged</option>
		<option selected>singleMaterial</option>
		<option>multiMaterial</option>
	</select>
</div>

nbsp;nbsp;nbsp;

<div style='display:inline-block;'>
	<span>render continuously<br/>(to get fps reading)</span>
	<br/>
	<input id='animate' type='checkbox' />
</div>

nbsp;nbsp;nbsp;

<div style='display:inline-block;'>
	<span>use override material<br/>(only effects singlevar method)</span>
	<br/>
	<input id='override' type='checkbox' checked/>
</div>

nbsp;nbsp;nbsp;

<div style='display:inline-block;'>
	<span>construct anew<br/>(to get additional timings)</span>
	<br/>
	<button id='construct' type='button'>do it</button>
</div>

<br/>

<div>

	<span>Materials: #<span id='materialCount'></span></span>

	nbsp;nbsp;nbsp;

	<span>Objects: #<span id='objectCount'></span></span>

	nbsp;nbsp;nbsp;

	<span>Drawcalls: #<span id='drawcalls'></span></span>

	nbsp;nbsp;nbsp;

	<span>Construction time: <span id='initTime'></span>nbsp;ms</span>

	nbsp;nbsp;nbsp;

</div>
#endif

void xx_interact_instances(Shell app, var parent, Dockbar dockbar)
{
#if 0
		var pickingData, pickingRenderTarget, pickingScene;
		var useOverridevar = true;
		var singleMaterial, singlePickingMaterial;
		var highlightBox;
		var materialList = [];
		var geometryList = [];
		var objectCount = 0;
		var geometrySize = new THREE.Vector3();
		var mouse = new THREE.Vector2();
		var scale = 1.03;

		var loader = new THREE.BufferGeometryLoader();

		//create buffer for reading a single pixel
		var pixelBuffer = new Uint8Array(4);

		// gui
		var instanceCount, method, doAnimate;

		//

		gui();
		init();
		initMesh();
		if (doAnimate) animate();

		//

		function gui() {

			var instanceCountElm = document.getElementById('instanceCount');

			instanceCount = parseInt(instanceCountElm.value);

			instanceCountElm.addEventListener('change', function () {

				instanceCount = parseInt(instanceCountElm.value);
				initMesh();

			});

			//

			var methodElm = document.getElementById('method');

			method = methodElm.value;

			methodElm.addEventListener('change', function () {

				method = methodElm.value;
				initMesh();

			});

			//

			var animateElm = document.getElementById('animate');

			doAnimate = animateElm.checked;

			animateElm.addEventListener('click', function () {

				doAnimate = animateElm.checked;
				animate();

			});

			//

			var overrideElm = document.getElementById('override');

			useOverridevar = overrideElm.checked;

			overrideElm.addEventListener('click', function () {

				useOverridevar = overrideElm.checked;
				initMesh();

			});

			//

			var constructElm = document.getElementById('construct');

			constructElm.addEventListener('click', function () {

				initMesh();

			});

		}

		function clean() {

			THREE.Cache.clear();

			materialList.0orEach(function (m) {

				m.dispose();

			});

			geometryList.0orEach(function (g) {

				g.dispose();

			});

			scene = new THREE.Scene();
			scene.background = new THREE.Color(0xffffff);

			scene.add(camera);
			scene.add(highlightBox);

			pickingScene = new THREE.Scene();
			pickingData = {};
			materialList = [];
			geometryList = [];
			objectCount = 0;

			singlevar = undefined;
			singlePickingvar = undefined;

		}

		var randomizeMatrix = function () {

			var position = new THREE.Vector3();
			var rotation = new THREE.Euler();
			var quaternion = new THREE.Quaternion();
			var scale = new THREE.Vector3();

			return function (matrix) {

				position.x = random() * 40 - 20;
				position.y = random() * 40 - 20;
				position.z = random() * 40 - 20;

				rotation.x = random() * 2 * PI;
				rotation.y = random() * 2 * PI;
				rotation.z = random() * 2 * PI;

				quaternion.setFromEuler(rotation, false);

				scale.x = scale.y = scale.z = random() * 1;

				matrix.compose(position, quaternion, scale);

			};

		}();

		function initMesh() {

			clean();

			// make instances
			loader.load('models/json/suzanne_buffergeometry.json', function (geo) {

				geo = geo.toNonIndexed();
				geo.computeBoundingBox();
				geo.boundingBox.getSize(geometrySize);
				geometryList.push(geo);

				var start = window.performance.now();

				switch (method) {

					case 'merged':
						makeMerged(geo);
						break;

					case 'instanced':
						makeInstanced(geo);
						break;

					case 'singleMaterial':
						makeSingleMaterial(geo);
						break;

					case 'multiMaterial':
						makeMultiMaterial(geo);
						break;

				}

				render();

				var end = window.performance.now();

				document.getElementById('materialCount').innerText = materialList.length;
				document.getElementById('objectCount').innerText = objectCount;
				document.getElementById('drawcalls').innerText = renderer.info.render.calls;
				document.getElementById('initTime').innerText = (end - start).toFixed(2);

			});

		}

		function makeMultiMaterial(geo) {

			// material

			var vert = document.getElementById('vertMaterial').textContent;
			var frag = document.getElementById('fragMaterial').textContent;

			var material = new THREE.RawShaderMaterial({
				vertexShader: vert,
				fragmentShader: frag,
				uniforms: {
					color: {
						value: new THREE.Color()
					}
				}
			});

			var pickingvar = new THREE.RawShaderMaterial({
				vertexShader: '#define PICKING\n' + vert,
				fragmentShader: '#define PICKING\n' + frag,
				uniforms: {
					pickingColor: {
						value: new THREE.Color()
					}
				}
			});

			// geometry / mesh

			var matrix = new THREE.Matrix4();

			for (var i = 0; i < instanceCount; i ++) {

				var object = new THREE.Mesh(geo, material);
				objectCount ++;
				randomizeMatrix(matrix);
				object.applyMatrix(matrix);
				var pickingObject = object.clone();
				objectCount ++;

				object.material = material.clone();
				object.material.uniforms['color'].value.setHex(random() * 0xffffff);
				materialList.push(object.material);

				pickingObject.material = pickingMaterial.clone();
				pickingObject.material.uniforms['pickingColor'].value.setHex(i + 1);
				materialList.push(pickingObject.material);

				pickingData[i + 1] = object;

				scene.add(object);
				pickingScene.add(pickingObject);

			}

			material.dispose();
			pickingMaterial.dispose();

		}

		function makeSingleMaterial(geo) {

			// material

			var vert = document.getElementById('vertMaterial').textContent;
			var frag = document.getElementById('fragMaterial').textContent;

			var material = new THREE.RawShaderMaterial({
				vertexShader: vert,
				fragmentShader: frag,
				uniforms: {
					'color': {
						value: new THREE.Color()
					}
				}
			});
			materialList.push(material);

			var pickingvar = new THREE.RawShaderMaterial({
				vertexShader: '#define PICKING\n' + vert,
				fragmentShader: '#define PICKING\n' + frag,
				uniforms: {
					'pickingColor': {
						value: new THREE.Color()
					}
				}
			});
			materialList.push(pickingMaterial);

			if (useOverrideMaterial) {

				// make globally available
				singlevar = material;
				singlePickingvar = pickingMaterial;

			}

			// geometry / mesh

			var matrix = new THREE.Matrix4();

			function onBeforeRender(renderer, scene, camera, geometry, material) {

				var updateList = [];
				var u = material.uniforms;
				var d = userData;

				if (u.pickingColor) {

					u.pickingColor.value.setHex(d.pickingColor);
					updateList.push('pickingColor');

				}

				if (u.color) {

					u.color.value.setHex(d.color);
					updateList.push('color');

				}

				if (updateList.length) {

					var materialProperties = renderer.properties.get(material);

					if (materialProperties.program) {

						var gl = renderer.getContext();
						var p = materialProperties.program;
						gl.useProgram(p.program);
						var pu = p.getUniforms();

						updateList.0orEach(function (name) {

							pu.setValue(gl, name, u[name].value);

						});

					}

				}

			}

			for (var i = 0; i < instanceCount; i ++) {

				var object = new THREE.Mesh(geo, material);
				objectCount ++;
				randomizeMatrix(matrix);
				object.applyMatrix(matrix);

				var pickingObject;
				if (! useOverrideMaterial) {

					pickingObject = object.clone();
					objectCount ++;

				}

				object.material = material;
				object.userData['color'] = random() * 0xffffff;

				if (useOverrideMaterial) {

					object.userData['pickingColor'] = i + 1;
					object.onBeforeRender = onBeforeRender;

				} else {

					pickingObject.material = pickingMaterial;
					pickingObject.userData['pickingColor'] = i + 1;
					pickingObject.onBeforeRender = onBeforeRender;

				}

				pickingData[i + 1] = object;

				scene.add(object);
				if (! useOverrideMaterial) pickingScene.add(pickingObject);

			}

		}

		function makeMerged(geo) {

			// material

			var vert = document.getElementById('vertMerged').textContent;
			var frag = document.getElementById('fragMerged').textContent;

			var material = new THREE.RawShaderMaterial({
				vertexShader: vert,
				fragmentShader: frag
			});
			materialList.push(material);

			var pickingvar = new THREE.RawShaderMaterial({
				vertexShader: '#define PICKING\n' + vert,
				fragmentShader: '#define PICKING\n' + frag
			});
			materialList.push(pickingMaterial);

			// geometry

			var mgeo = new THREE.BufferGeometry();
			geometryList.push(mgeo);

			var pos = geo.attributes.position;
			var posLen = geo.attributes.position.count * 3;
			var vertices = new THREE.BufferAttribute(
				new Float32Array(instanceCount * posLen), 3
			);

			var vertex = new THREE.Vector3();
			var matrix = new THREE.Matrix4();

			for (var i = 0, ul = instanceCount; i < ul; i ++) {

				var offset = i * posLen;

				randomizeMatrix(matrix);
				var object = new THREE.Object3D();
				objectCount ++;
				object.applyMatrix(matrix);
				pickingData[i + 1] = object;
				vertices.set(pos.array, offset);

				for (var k = 0, l = offset; k < posLen; k += 3, l += 3) {

					vertex.0romArray(vertices.array, l);
					vertex.applyMatrix4(matrix);
					vertex.toArray(vertices.array, l);

				}

			}

			mgeo.addAttribute('position', vertices);

			var colCount = posLen / 3;
			var colors = new THREE.BufferAttribute(
				new Float32Array(instanceCount * colCount * 3), 3
			);
			var randCol = function () {

				return random();

			};
			for (var i = 0, ul = instanceCount; i < ul; i ++) {

				var r = randCol(), g = randCol(), b = randCol();
				for (var j = i * colCount, jl = (i + 1) * colCount; j < jl; j ++) {

					colors.setXYZ(j, r, g, b);

				}

			}
			mgeo.addAttribute('color', colors);

			var col = new THREE.Color();
			var pickingColors = new THREE.BufferAttribute(
				new Float32Array(instanceCount * colCount * 3), 3
			);
			for (var i = 0, ul = instanceCount; i < ul; i ++) {

				col.setHex(i + 1);
				for (var j = i * colCount, jl = (i + 1) * colCount; j < jl; j ++) {

					pickingColors.setXYZ(j, col.r, col.g, col.b);

				}

			}
			mgeo.addAttribute('pickingColor', pickingColors);

			// mesh

			var mesh = new THREE.Mesh(mgeo, material);
			scene.add(mesh);

			var pickingMesh = new THREE.Mesh(mgeo, pickingMaterial);
			pickingScene.add(pickingMesh);

		}

		function makeInstanced(geo) {

			// material

			var vert = document.getElementById('vertInstanced').textContent;
			var frag = document.getElementById('fragInstanced').textContent;

			var material = new THREE.RawShaderMaterial({
				vertexShader: vert,
				fragmentShader: frag,
			});
			materialList.push(material);

			var pickingvar = new THREE.RawShaderMaterial({
				vertexShader: '#define PICKING\n' + vert,
				fragmentShader: '#define PICKING\n' + frag
			});
			materialList.push(pickingMaterial);

			// geometry

			var igeo = new THREE.InstancedBufferGeometry();
			geometryList.push(igeo);

			var vertices = geo.attributes.position.clone();
			igeo.addAttribute('position', vertices);

			// var matrices = new THREE.InstancedBufferAttribute(
			// 	new Float32Array(instanceCount * 16), 16
			//);
			var mcol0 = new THREE.InstancedBufferAttribute(
				new Float32Array(instanceCount * 3), 3
			);
			var mcol1 = new THREE.InstancedBufferAttribute(
				new Float32Array(instanceCount * 3), 3
			);
			var mcol2 = new THREE.InstancedBufferAttribute(
				new Float32Array(instanceCount * 3), 3
			);
			var mcol3 = new THREE.InstancedBufferAttribute(
				new Float32Array(instanceCount * 3), 3
			);
			var matrix = new THREE.Matrix4();
			var me = matrix.elements;
			for (var i = 0, ul = mcol0.count; i < ul; i ++) {

				randomizeMatrix(matrix);
				var object = new THREE.Object3D();
				objectCount ++;
				object.applyMatrix(matrix);
				pickingData[i + 1] = object;
				// matrices.set(matrix.elements, i * 16);
				mcol0.setXYZ(i, me[0], me[1], me[2]);
				mcol1.setXYZ(i, me[4], me[5], me[6]);
				mcol2.setXYZ(i, me[8], me[9], me[10]);
				mcol3.setXYZ(i, me[12], me[13], me[14]);

			}
			// igeo.addAttribute('matrix', matrices);
			igeo.addAttribute('mcol0', mcol0);
			igeo.addAttribute('mcol1', mcol1);
			igeo.addAttribute('mcol2', mcol2);
			igeo.addAttribute('mcol3', mcol3);

			var randCol = function () {

				return random();

			};
			var colors = new THREE.InstancedBufferAttribute(
				new Float32Array(instanceCount * 3), 3
			);
			for (var i = 0, ul = colors.count; i < ul; i ++) {

				colors.setXYZ(i, randCol(), randCol(), randCol());

			}
			igeo.addAttribute('color', colors);

			var col = new THREE.Color();
			var pickingColors = new THREE.InstancedBufferAttribute(
				new Float32Array(instanceCount * 3), 3
			);
			for (var i = 0, ul = pickingColors.count; i < ul; i ++) {

				col.setHex(i + 1);
				pickingColors.setXYZ(i, col.r, col.g, col.b);

			}
			igeo.addAttribute('pickingColor', pickingColors);

			// mesh

			var mesh = new THREE.Mesh(igeo, material);
			scene.add(mesh);

			var pickingMesh = new THREE.Mesh(igeo, pickingMaterial);
			pickingScene.add(pickingMesh);

		}

		function init() {

			// camera

			camera = new THREE.PerspectiveCamera(
				70, window.innerWidth / window.innerHeight, 1, 100
			);
			camera.position.z = 40;

			// picking render target

			pickingRenderTarget = new THREE.WebGLRenderTarget(
				window.innerWidth, window.innerHeight
			);
			pickingRenderTarget.texture.generateMipmaps = false;
			pickingRenderTarget.texture.minFilter = THREE.NearestFilter;

			// highlight box

			highlightBox = new THREE.Mesh(
				new THREE.BoxBufferGeometry(1, 1, 1),
				new THREE.MeshLambertMaterial({
					emissive: 0xffff00,
					transparent: true,
					opacity: 0.5
				})
			);

			// renderer

			container = document.getElementById('container');
			renderer = new THREE.WebGLRenderer({
				antialias: true,
				alpha: true
			});
			if (renderer.extensions.get('ANGLE_instanced_arrays') == null) {

				document.getElementById('notSupported').style.display = '';
				return;

			}
			renderer.setPixelRatio(window.devicePixelRatio);
			renderer.setSize(window.innerWidth, window.innerHeight);
			//renderer.sortObjects = false;
			container.appendChild(renderer.domElement);

			if (renderer.extensions.get('ANGLE_instanced_arrays') == null) {

				throw 'ANGLE_instanced_arrays not supported';

			}

			// controls

			controls = new THREE.TrackballControls(
				camera, renderer.domElement
			);
			controls.staticMoving = true;

			// stats

			stats = new Stats();
			container.appendChild(stats.dom);

			// listeners

			renderer.domElement.addEventListener('mousemove', onMouseMove);

			window.addEventListener('resize', onWindowResize, false);

		}

		//

		function onMouseMove(e) {

			mouse.x = e.clientX;
			mouse.y = e.clientY;

			controls.update();
			requestAnimationFrame(render);

		}

		function onWindowResize() {

			camera.aspect = window.innerWidth / window.innerHeight;
			camera.updateProjectionMatrix();

			renderer.setSize(window.innerWidth, window.innerHeight);
			pickingRenderTarget.setSize(window.innerWidth, window.innerHeight);

		}

		function animate() {

			if (doAnimate) {

				requestAnimationFrame(animate);

			}

			controls.update();
			stats.update();

			render();

		}

		function pick() {

			// render the picking scene off-screen

			highlightBox.visible = false;

			if (singlePickingMaterial) {

				scene.overridevar = singlePickingMaterial;
				renderer.render(scene, camera, pickingRenderTarget);
				scene.overridevar = null;

			} else {

				renderer.render(pickingScene, camera, pickingRenderTarget);

			}

			// read the pixel under the mouse from the texture

			renderer.readRenderTargetPixels(
				pickingRenderTarget,
				mouse.x,
				pickingRenderTarget.height - mouse.y,
				1,
				1,
				pixelBuffer
			);

			// interpret the pixel as an ID

			var id =
				(pixelBuffer[0] << 16) |
				(pixelBuffer[1] << 8) |
				(pixelBuffer[2]);

			var object = pickingData[id];

			if (object) {

				// move the highlightBox so that it surrounds the picked object

				if (object.position  object.rotation  object.scale) {

					highlightBox.position.copy(object.position);
					highlightBox.rotation.copy(object.rotation);

					highlightBox.scale.copy(object.scale)
						.multiply(geometrySize)
						.multiplyScalar(scale);

					highlightBox.visible = true;

				}

			} else {

				highlightBox.visible = false;

			}

		}

		function render() {

			pick();
			renderer.render(scene, camera);

		}

	</script>

</body>
</html>
#endif

}
