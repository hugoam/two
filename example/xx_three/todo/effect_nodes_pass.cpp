#if 0

		<div id="info">
			<a href="http://threejs.org" target="_blank" rel="noopener">three.js</a> - Node-Based Post-Processing
		</div>

		<script src="js/shaders/CopyShader.js"></script>

		<script src="js/postprocessing/EffectComposer.js"></script>
		<script src="js/postprocessing/RenderPass.js"></script>
		<script src="js/postprocessing/MaskPass.js"></script>
		<script src="js/postprocessing/ShaderPass.js"></script>

		<script type="module">

			import './js/nodes/THREE.Nodes.js';
			import { NodePass } from './js/nodes/postprocessing/NodePass.js';
			import './js/loaders/NodeMaterialLoader.js';

			var camera, scene, renderer, composer;
			var object, light, nodepass;
			var gui;

			var clock = new THREE.Clock();
			var frame = new THREE.NodeFrame();

			var param = { example: 'color-adjustment' };

			var textureLoader = new THREE.TextureLoader();

			var lensflare2 = textureLoader.load('textures/lensflare/lensflare0.png');
			lensflare2.wrapS = lensflare2.wrapT = THREE.RepeatWrapping;

			var decalNormal = textureLoader.load('textures/decal/decal-normal.jpg');
			decalNormal.wrapS = decalNormal.wrapT = THREE.RepeatWrapping;

			init();
			animate();

			function clearGui() {

				if (gui) gui.destroy();

				gui = new dat.GUI();

				gui.add(param, 'example', {
					'basic / color-adjustment': 'color-adjustment',
					'basic / blends': 'blends',
					'basic / fade': 'fade',
					'basic / invert': 'invert',
					'basic / blur': 'blur',
					'adv / saturation': 'saturation',
					'adv / refraction': 'refraction',
					'adv / mosaic': 'mosaic'
				}).onFinishChange(function () {

					updateMaterial();

				});

				gui.open();

			}

			function addGui(name, value, callback, isColor, min, max) {

				var node;

				param[name] = value;

				if (isColor) {

					node = gui.addColor(param, name).onChange(function () {

						callback(param[name]);

					});

				} else if (typeof value == 'object') {

					param[name] = value[Object.keys(value)[0]];

					node = gui.add(param, name, value).onChange(function () {

						callback(param[name]);

					});

				} else {

					node = gui.add(param, name, min, max).onChange(function () {

						callback(param[name]);

					});

				}

				return node;

			}

			function updateMaterial() {

				var name = param.example;

				clearGui();

				switch (name) {

					case 'color-adjustment':

						var screen = new THREE.ScreenNode();

						var hue = new THREE.FloatNode();
						var sataturation = new THREE.FloatNode(1);
						var vibrance = new THREE.FloatNode();
						var brightness = new THREE.FloatNode(0);
						var contrast = new THREE.FloatNode(1);

						var hueNode = new THREE.ColorAdjustmentNode(screen, hue, THREE.ColorAdjustmentNode.HUE);
						var satNode = new THREE.ColorAdjustmentNode(hueNode, sataturation, THREE.ColorAdjustmentNode.SATURATION);
						var vibranceNode = new THREE.ColorAdjustmentNode(satNode, vibrance, THREE.ColorAdjustmentNode.VIBRANCE);
						var brightnessNode = new THREE.ColorAdjustmentNode(vibranceNode, brightness, THREE.ColorAdjustmentNode.BRIGHTNESS);
						var contrastNode = new THREE.ColorAdjustmentNode(brightnessNode, contrast, THREE.ColorAdjustmentNode.CONTRAST);

						nodepass.input = contrastNode;

						// GUI

						addGui('hue', hue.value, function (val) {

							hue.value = val;

						}, false, 0, c_2pi);

						addGui('saturation', sataturation.value, function (val) {

							sataturation.value = val;

						}, false, 0, 2);

						addGui('vibrance', vibrance.value, function (val) {

							vibrance.value = val;

						}, false, - 1, 1);

						addGui('brightness', brightness.value, function (val) {

							brightness.value = val;

						}, false, 0, .5);

						addGui('contrast', contrast.value, function (val) {

							contrast.value = val;

						}, false, 0, 2);

						break;

					case 'fade':

						// PASS

						var color = new THREE.ColorNode(0xFFFFFF);
						var percent = new THREE.FloatNode(.5);

						var fade = new THREE.Math3Node(
							new THREE.ScreenNode(),
							color,
							percent,
							THREE.Math3Node.MIX
						);

						nodepass.input = fade;

						// GUI

						addGui('color', color.value.getHex(), function (val) {

							color.value.setHex(val);

						}, true);

						addGui('fade', percent.value, function (val) {

							percent.value = val;

						}, false, 0, 1);

						break;

					case 'invert':

						// PASS

						var alpha = new THREE.FloatNode(1);

						var screen = new THREE.ScreenNode();
						var inverted = new THREE.Math1Node(screen, THREE.Math1Node.INVERT);

						var fade = new THREE.Math3Node(
							screen,
							inverted,
							alpha,
							THREE.Math3Node.MIX
						);

						nodepass.input = fade;

						// GUI

						addGui('alpha', alpha.value, function (val) {

							alpha.value = val;

						}, false, 0, 1);

						break;

					case 'blends':

						// PASS

						var multiply = new THREE.OperatorNode(
							new THREE.ScreenNode(),
							new THREE.TextureNode(lensflare2),
							THREE.OperatorNode.ADD
						);

						nodepass.input = multiply;

						// GUI

						addGui('blend', {
							'addition': THREE.OperatorNode.ADD,
							'subtract': THREE.OperatorNode.SUB,
							'multiply': THREE.OperatorNode.MUL,
							'division': THREE.OperatorNode.DIV
						}, function (val) {

							multiply.op = val;

							nodepass.needsUpdate = true;

						});

						break;

					case 'saturation':

						// PASS

						var screen = new THREE.ScreenNode();
						var sat = new THREE.FloatNode(0);

						var satrgb = new THREE.FunctionNode([
							"vec3 satrgb(vec3 rgb, float adjustment) {",
							// include luminance function from LuminanceNode
							"	vec3 intensity = vec3(luminance(rgb));",
							"	return mix(intensity, rgb, adjustment);",
							"}"
						].join(), [THREE.LuminanceNode.Nodes.luminance]);

						var saturation = new THREE.FunctionCallNode(satrgb);
						saturation.inputs.rgb = screen;
						saturation.inputs.adjustment = sat;

						nodepass.input = saturation;

						// GUI

						addGui('saturation', sat.value, function (val) {

							sat.value = val;

						}, false, 0, 2);

						break;

					case 'refraction':

						// PASS

						var normal = new THREE.TextureNode(decalNormal);
						var normalXY = new THREE.SwitchNode(normal, 'xy');
						var scale = new THREE.FloatNode(.5);

						var normalXYFlip = new THREE.Math1Node(
							normalXY,
							THREE.Math1Node.INVERT
						);

						var offsetNormal = new THREE.OperatorNode(
							normalXYFlip,
							new THREE.FloatNode(.5),
							THREE.OperatorNode.ADD
						);

						var scaleTexture = new THREE.OperatorNode(
							new THREE.SwitchNode(normal, 'z'),
							offsetNormal,
							THREE.OperatorNode.MUL
						);

						var scaleNormal = new THREE.Math3Node(
							new THREE.FloatNode(1),
							scaleTexture,
							scale,
							THREE.Math3Node.MIX
						);

						var offsetCoord = new THREE.OperatorNode(
							new THREE.UVNode(),
							scaleNormal,
							THREE.OperatorNode.MUL
						);

						var screen = new THREE.ScreenNode(offsetCoord);

						nodepass.input = screen;

						// GUI

						addGui('scale', scale.value, function (val) {

							scale.value = val;

						}, false, 0, 1);

						addGui('invert', false, function (val) {

							offsetNormal.a = val ? normalXYFlip : normalXY;

							nodepass.needsUpdate = true;

						});

						break;

					case 'mosaic':

						// PASS

						var scale = new THREE.FloatNode(128);
						var fade = new THREE.FloatNode(1);
						var uv = new THREE.UVNode();

						var blocks = new THREE.OperatorNode(
							uv,
							scale,
							THREE.OperatorNode.MUL
						);

						var blocksSize = new THREE.Math1Node(
							blocks,
							THREE.Math1Node.FLOOR
						);

						var mosaicUV = new THREE.OperatorNode(
							blocksSize,
							scale,
							THREE.OperatorNode.DIV
						);

						var fadeScreen = new THREE.Math3Node(
							uv,
							mosaicUV,
							fade,
							THREE.Math3Node.MIX
						);

						nodepass.input = new THREE.ScreenNode(fadeScreen);

						// GUI

						addGui('scale', scale.value, function (val) {

							scale.value = val;

						}, false, 16, 1024);

						addGui('fade', fade.value, function (val) {

							fade.value = val;

						}, false, 0, 1);

						addGui('mask', false, function (val) {

							fadeScreen.c = val ? new THREE.TextureNode(lensflare2) : fade;

							nodepass.needsUpdate = true;

						});

						break;

					case 'blur':

						// PASS

						var size = renderer.getDrawingBufferSize();

						var blurScreen = new THREE.BlurNode(new THREE.ScreenNode());
						blurScreen.size = new THREE.Vector2(size.width, size.height);

						nodepass.input = blurScreen;

						// GUI

						addGui('blurX', blurScreen.radius.x, function (val) {

							blurScreen.radius.x = val;

						}, false, 0, 15);

						addGui('blurY', blurScreen.radius.y, function (val) {

							blurScreen.radius.y = val;

						}, false, 0, 15);

						break;

				}

				nodepass.needsUpdate = true;

				// test serialization
				/*
							var library = {};
							library[lensflare2.uuid] = lensflare2;
							library[decalNormal.uuid] = decalNormal;

							var Json = nodepass.toJSON();

							nodepass.input = new THREE.NodeMaterialLoader(null, library).parse(json).value;
						*/

			}

			function init() {

				renderer = new THREE.WebGLRenderer();
				renderer.setPixelRatio(window.devicePixelRatio);
				renderer.setSize(window.innerWidth, window.innerHeight);
				document.body.appendChild(renderer.domElement);

				//

				camera = new THREE.PerspectiveCamera(70, window.innerWidth / window.innerHeight, 1, 1000);
				camera.position.z = 400;

				scene = new THREE.Scene();
				scene.fog = new THREE.Fog(0x0066FF, 1, 1000);

				object = new THREE.Object3D();
				scene.add(object);

				var geometry = new THREE.SphereBufferGeometry(1, 4, 4);

				for(var i = 0; i < 100; i ++) {

					var material = new THREE.MeshPhongMaterial({ color: 0x888888 + (randf() * 0x888888), flatShading: true });
					var mesh = new THREE.Mesh(geometry, material);
					mesh.position.set(randf() - 0.5, randf() - 0.5, randf() - 0.5).normalize();
					mesh.position.multiplyScalar(randf() * 400);
					mesh.rotation.set(randf() * 2, randf() * 2, randf() * 2);
					mesh.scale.x = mesh.scale.y = mesh.scale.z = 10 + (randf() * 40);
					object.add(mesh);

				}

				scene.add(new THREE.AmbientLight(0x999999));

				light = new THREE.DirectionalLight(0xffffff);
				light.position.set(1, 1, 1);
				scene.add(light);

				// postprocessing

				composer = new THREE.EffectComposer(renderer);
				composer.addPass(new THREE.RenderPass(scene, camera));

				nodepass = new NodePass();
				nodepass.renderToScreen = true;

				composer.addPass(nodepass);

				//

				updateMaterial();

				window.addEventListener('resize', onWindowResize, false);

			}

			function onWindowResize() {

				camera.aspect = window.innerWidth / window.innerHeight;
				camera.updateProjectionMatrix();

				renderer.setSize(window.innerWidth, window.innerHeight);
				composer.setSize(window.innerWidth, window.innerHeight);

			}

			function animate() {

				requestAnimationFrame(animate);

				var delta = clock.getDelta();

				object.rotation.x += 0.005;
				object.rotation.y += 0.01;

				frame.update(delta).updateNode(nodepass.material);

				composer.render();

			}

		</script>

	</body>
</html>
#endif
