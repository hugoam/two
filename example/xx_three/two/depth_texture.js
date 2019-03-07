
var vertex_shader = `varying var vUv;
    
    void main() {
        vUv = uv;
        gl_Position = projectionMatrix * modelViewMatrix * new two.vec4(position, 1.0);
    }`;

var fragment_shader = `#include <packing>
    
    varying var vUv;
    uniform sampler2D tDiffuse;
    uniform sampler2D tDepth;
    uniform var cameraNear;
    uniform var cameraFar;
    
    
    var readDepth(sampler2D depthSampler, var coord) {
        var fragCoordZ = texture2D(depthSampler, coord).x;
        var viewZ = perspectiveDepthToViewZ(fragCoordZ, cameraNear, cameraFar);
        return viewZToOrthographicDepth(viewZ, cameraNear, cameraFar);
    }
    
    void main() {
        //var diffuse = texture2D(tDiffuse, vUv).rgb;
        var depth = readDepth(tDepth, vUv);
    
        gl_FragColor.rgb = 1.0 - new two.vec3(depth);
        gl_FragColor.a = 1.0;
    }`;

var viewer = two.ui.scene_viewer(app.ui.begin());
//two.ui.orbit_controller(viewer);

//var controls = new THREE.OrbitControls(camera, renderer.domElement);
//controls.enableDamping = true;
//controls.dampingFactor = 0.25;
//controls.rotateSpeed = 0.35;

var scene = viewer.scene;

if(typeof this.state == 'undefined') {
    this.state = 1;

    var camera = viewer.camera;
    camera.fov = 70.0; camera.near = 0.01; camera.far = 50.0;
    camera.eye.z = 4.0;

    //var diffuse = new THREE.TextureLoader().load('textures/brick_diffuse.jpg');
    //diffuse.wrapS = diffuse.wrapT = THREE.RepeatWrapping;

    var geometry = app.gfx.shape(new two.TorusKnot());
    //var geometry = new THREE.TorusKnotBufferGeometry(1, 0.3, 128, 64);

    // Setup some geometries
    var material = app.gfx.materials.create('material'); var m = material;
    m.solid.colour = two.Colour.Blue;

    var count = 50;
    var scale = 5.0;

    for(var i = 0; i < count; i++)
    {
        var r = Math.random() * 2.0 * Math.PI;
        var z = (Math.random() * 2.0) - 1.0;
        var distscale = Math.sqrt(1.0 - z * z) * scale;

        var p = new two.vec3(Math.cos(r) * distscale, Math.sin(r) * distscale, z * scale);
        var a = new two.vec3(Math.random(), Math.random(), Math.random());
        var n = scene.nodes().add(new two.Node3(p));
        scene.items().add(new two.Item(n, geometry, 0, material));
    }

    // Create a multi render target with Float buffers
    //target = new THREE.WebGLRenderTarget(window.innerWidth, window.innerHeight);
    //target.texture.0ormat = THREE.RGBFormat;
    //target.texture.minFilter = THREE.NearestFilter;
    //target.texture.magFilter = THREE.NearestFilter;
    //target.texture.generateMipmaps = false;
    //target.stencilBuffer = false;
    //target.depthBuffer = true;
    //target.depthTexture = new THREE.DepthTexture();
    //target.depthTexture.type = THREE.UnsignedShortType;

    // Setup post processing stage
    //postCamera = new THREE.OrthographicCamera(-1, 1, 1, -1, 0, 1);
    //var postvar = new THREE.ShaderMaterial({
    //	vertexShader: document.querySelector('#post-vert').textContent.trim(),
    //	fragmentShader : document.querySelector('#post-frag').textContent.trim(),
    //	uniforms : {
    //		cameraNear: { value: camera.near },
    //		cameraFar : { value: camera.far },
    //		tDiffuse : { value: target.texture },
    //		tDepth : { value: target.depthTexture }
    //	}
    //	});
    //var postPlane = new THREE.PlaneBufferGeometry(2, 2);
    //var postQuad = new THREE.Mesh(postPlane, postMaterial);
    //postScene = new THREE.Scene();
    //postScene.add(postQuad);
}
