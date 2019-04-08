// material_skin.js

// @author alteredq / http://alteredqualia.com/
// Convolution shader
// ported from o3d sample to WebGL / GLSL
// http://o3d.googlecode.com/svn/trunk/samples/convolution.html

var convolution_vertex = `$input a_position, a_texcoord0
    $output v_uv0

    #include <filter.sh>

    uniform vec4 u_blooblur_p0;
    #define u_increment u_blooblur_p0.xy

    void main() {
        v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;
        v_uv0 = v_uv0 - ((float(KERNEL_SIZE) - 1.0) / 2.0) * u_increment;
        gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;

var convolution_fragment = `$input v_uv0

    #include <filter.sh>

    //uniform vec4 u_kernel[KERNEL_SIZE/4];
    uniform vec4 u_kernel[8];

    uniform vec4 u_blooblur_p0;
    #define u_increment u_blooblur_p0.xy

    void main()
    {
        vec2 uv = v_uv0;
        vec4 sum = vec4(0.0, 0.0, 0.0, 0.0);

        for(int i = 0; i < KERNEL_SIZE; i++)
        {
            sum += texture2D(s_source_0, uv) * u_kernel[i/4][i%4];
            uv += u_increment;
        }

        gl_FragColor = sum;
    }`;

var KERNEL_SIZE = 0;

function blur_kernel(sigma) {
    // We lop off the sqrt(2 * pi) * sigma term, since we're going to normalize anyway.

    auto gauss = [](float x, float sigma) { return exp(-sq(x) / (2.0 * sq(sigma))); };

    constexpr int kMaxKernelSize = 25;
    int kernelSize = 2.0 * ceil(sigma * 3.f) + 1;

    if (kernelSize > kMaxKernelSize) kernelSize = kMaxKernelSize;
    float halfWidth = (kernelSize - 1) * 0.5;

    vector<float> values(kernelSize); 
    float sum = 0.0;
    for (int i = 0; i < kernelSize; ++i)
    {
        values[i] = gauss(i - halfWidth, sigma);
        sum += values[i];
    }

    // normalize the kernel
    for (int i = 0; i < kernelSize; ++ i) values[i] /= sum;

    return values;
}

//	Skin shader
//		- Blinn-Phong diffuse term (using normal + diffuse maps)
//		- subsurface scattering approximation by four blur layers
//		- physically based specular term (Kelemen/Szirmay-Kalos specular reflectance)
//
//		- point and directional lights (use with 'lights: true' material option)
//
//		- based on Nvidia Advanced Skin Rendering GDC 2007 presentation
//		  and GPU Gems 3 Chapter 14. Advanced Techniques for Realistic Real-Time Skin Rendering
//
//			http://developer.download.nvidia.com/presentations/2007/gdc/Advanced_Skin.pdf
//			http://http.developer.nvidia.com/GPUGems3/gpugems3_ch14.html

var skin_fragment = `$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal

    #include <encode.sh>
    #include <pbr/pbr.sh>
    #include <pbr/light.sh>
    #include <pbr/light_brdf_three.sh>
    #include <pbr/radiance.sh>

    //uniform vec4 u_skin_p0;
    #define u_roughness u_user_p0.x
    #define u_spec_brightness u_user_p0.y

    #define s_blur1 s_user0
    #define s_blur2 s_user1
    #define s_blur3 s_user2
    #define s_blur4 s_user3

    #define s_beckmann s_user4

    float fresnelReflectance(vec3 H, vec3 V, float F0)
    {
        float base = 1.0 - dot(V, H);
        float exponential = pow(base, 5.0);

        return exponential + F0 * (1.0 - exponential);
    }

    // Kelemen/Szirmay-Kalos specular BRDF

    // Bumped surface normal, Points to light, Points to eye, Roughness, Specular brightness
    float KS_Skin_Specular(vec3 N, vec3 L, vec3 V, float m, float rho_s)
    {
        float result = 0.0;
        float ndotl = dot(N, L);

        if(ndotl > 0.0)
        {
            vec3 h = L + V; // Unnormalized half-way vector
            vec3 H = normalize(h);

            float ndoth = dot(N, H);

            float PH = pow(2.0 * texture2D(s_beckmann, vec2(ndoth, m)).x, 10.0);
            float F = fresnelReflectance(H, V, 0.028);
            float frSpec = max(PH * F / dot(h, h), 0.0);

            result = ndotl * rho_s * frSpec; // BRDF * dot(N,L) * rho_s
        }

        return result;
    }

    void direct_skin(vec3 energy, vec3 l, Fragment fragment, Phongvar material, inout vec3 diffuse, inout vec3 specular)
    {
        float diffuseWeight = max(dot(fragment.normal, l), 0.0);
        diffuse += energy * diffuseWeight;

    #ifndef PASS_DIFFUSE
            float specularWeight = KS_Skin_Specular(fragment.normal, l, fragment.view, u_roughness, u_spec_brightness);
            specular += energy * material.specular * specularWeight;
    #endif
    }

    #define direct_brdf direct_skin

    void main() {

    #include <pbr/fs_fragment.sh>

    #include <pbr/fs_phong_material.sh>
        vec4 texDiffuse = sample_material_texture(s_diffuse, fragment.uv);
        texDiffuse *= texDiffuse;
        vec4 diffuseColor = vec4(material.diffuse, 1.0) * texDiffuse;

    #include <pbr/fs_phong.sh>

    vec3 light = diffuseColor.rgb * (diffuse + specular);

    #ifdef PASS_DIFFUSE
            light = sqrt(light);
    #else
            //#define VERSION1
            #ifdef VERSION1
                vec3 color = sqrt(light);
            #else
                vec3 color = light;
            #endif

            vec3 blur1 = texture2D(s_blur1, v_uv0).xyz;
            vec3 blur2 = texture2D(s_blur2, v_uv0).xyz;
            vec3 blur3 = texture2D(s_blur3, v_uv0).xyz;
            vec3 blur4 = texture2D(s_blur4, v_uv0).xyz;


            //gl_FragColor = vec4(blur1, gl_FragColor.w);

            //gl_FragColor = vec4(vec3(0.22, 0.5, 0.7) * color + vec3(0.2, 0.5, 0.3) * blur1 + vec3(0.58, 0.0, 0.0) * blur2, gl_FragColor.w);

            //gl_FragColor = vec4(vec3(0.25, 0.6, 0.8) * color + vec3(0.15, 0.25, 0.2) * blur1 + vec3(0.15, 0.15, 0.0) * blur2 + vec3(0.45, 0.0, 0.0) * blur3, gl_FragColor.w);


            light = vec3(vec3(0.22,  0.437, 0.635) * color + 
                         vec3(0.101, 0.355, 0.365) * blur1 + 
                         vec3(0.119, 0.208, 0.0)   * blur2 + 
                         vec3(0.114, 0.0,   0.0)   * blur3 + 
                         vec3(0.444, 0.0,   0.0)   * blur4);

            light *= sqrt(texDiffuse.xyz);

            //light += ambientLightColor * diffuse * texDiffuse.xyz + specular;
            vec3 ambient = vec3_splat(0.0); //zone.radiance_color * zone.ambient;
            light += ambient * material.diffuse * texDiffuse.xyz + specular;

            #ifndef VERSION1
                light = sqrt(light);
            #endif
    #endif

        gl_FragColor = vec4(light, diffuseColor.a);
        // TODO, this should be pre-multiplied to allow for bright highlights on very transparent objects

        //#include <pbr/fs_out_pbr.sh>
        //gl_FragColor = LinearToGamma(gl_FragColor, 2.0);

        //THREE.ShaderChunk[fog_fragment],

    }`;

var skin_vertex =
    `#include <geometry_vs.sc>`;


var skin_vertex_uv =

    `#define RENDER_UV
    #include <geometry_vs.sc>`;


// Beckmann distribution function
//	- to be used in specular term of skin shader
//	- render a screen-aligned quad to precompute a 512 x 512 texture
//
//		- from http://developer.nvidia.com/node/171

var beckmann_vertex = `$input a_position, a_texcoord0
    $output v_uv0
    
    #include <filter.sh>
    
    void main() {
    	v_uv0 = u_source_crop.xy + a_texcoord0 * u_source_crop.zw;
    	gl_Position = mul(u_modelViewProj, vec4(a_position.xyz, 1.0));
    }`;

var beckmann_fragment = `$input v_uv0

    #include <filter.sh>

    float PHBeckmann(float ndoth, float m)
    {
        float alpha = acos(ndoth);
        float ta = tan(alpha);
        float val = 1.0 / (m * m * pow(ndoth, 4.0)) * exp(-(ta * ta) / (m * m));
        return val;
    }

    float KSTextureCompute(vec2 tex)
    {
        // Scale the value to fit within [0,1]  invert upon lookup.
        return 0.5 * pow(PHBeckmann(tex.x, tex.y), 0.1);
    }

    void main()
    {
        float x = KSTextureCompute(v_uv0);
        gl_FragColor = vec4(x, x, x, 1.0);
    }`;

function render_beckmann(gfx, size) {
    
    var fbo = new two.FrameBuffer(size, two.TextureFormat.RGBA8);

    var beckmann = gfx.programs.create('beckmann');
    beckmann.set_source(two.ShaderType.Vertex, beckmann_vertex);
    beckmann.set_source(two.ShaderType.Fragment, beckmann_fragment);

    gfx.filter.quad(new two.Pass(), fbo, beckmann, 0, true);

    // @todo should copy it to a normal texture
    return fbo.tex;
}

function pass_bloom(gfx, render, source, fbo, clear = true, strength = 1.0, kernel_size = 25, sigma = 4.0, resolution = 256) {
    
    var targetX = new two.FrameBuffer(new two.uvec2(resolution), two.TextureFormat.RGBA8);
    var targetY = new two.FrameBuffer(new two.uvec2(resolution), two.TextureFormat.RGBA8);

    var blurX = new two.vec2(0.001953125, 0.0);
    var blurY = new two.vec2(0.0, 0.001953125);

    var convolution = convolution_program(gfx);

    var max_kernel = 8;
    vec4 kernel[max_kernel] = {};

    //printf('pass bloom\n');
    const vector<float> kernel_values = blur_kernel(sigma);
    const uint32_t nuvalues = uint32_t(kernel_values.size());
    //assert(nuvalues >= kernel_size);
    for(var i = 0; i < kernel_values.size(); ++i) {
        kernel[i/4][i%4] = kernel_values[i];
    }

    var program = new two.ProgramVersion(convolution);
    program.set_mode(0, KERNEL_SIZE, min(nuvalues, kernel_size));

    function blur_pass(gfx, render, target, source, program, increment)
    {
        var pass = render.next_pass('bloom_blur', two.PassType.PostProcess);

        gfx.filter.uniforms(pass, 'u_kernel', kernel, max_kernel);

        gfx.filter.uniform(pass, 'u_bloom_blur_p0', new two.vec4(increment.x, increment.y, 0.0, 0.0));
        gfx.filter.source0(source);
        //renderer.clear();
        gfx.filter.quad(pass, target, program);
    }

    blur_pass(gfx, render, targetX, source, program, blurX);
    blur_pass(gfx, render, targetY, targetX.tex, program, blurY);

    var pass = render.next_pass('bloom_merge', two.PassType.PostProcess);
    //if(clear) renderer.clear();

    if(strength != 1.0)
    {
        //this.copyUniforms['opacity'].value = strength;
        //transparent: true
        gfx.copy.quad(pass, fbo, targetY.tex, BGFX_STATE_BLEND_ADD);
    }
    else
        gfx.copy.quad(pass, fbo, targetY.tex);
}

var viewer = two.ui.scene_viewer(panel);
//two.ui.orbit_controls(viewer);
viewer.viewport.autorender = false;

var scene = viewer.scene;

var firstPass = true;

if(init) {
    this.importerGltf = new two.ImporterGltf(app.gfx);

    this.uv = new two.FrameBuffer(uvec2(512U), two.TextureFormat.RGBA8);
    this.blur1 = new two.FrameBuffer(uvec2(512U), two.TextureFormat.RGBA8);
    this.blur2 = new two.FrameBuffer(uvec2(512U), two.TextureFormat.RGBA8);
    this.blur3 = new two.FrameBuffer(uvec2(512U), two.TextureFormat.RGBA8);

    this.mouse = new two.vec2(0.0);
    
    var camera = viewer.camera;
    camera.fov = 35.f; camera.near = 1.0; camera.far = 10000.0;
    camera.eye.z = 900.0;

    //scene.background = new THREE.Color(0x050505);

    var ln0 = scene.nodes().add(new two.Node3(vec3(0.0), look_dir(normalize(vec3(-1.0, -0.5, -1.0)))));
    var l0 = scene.lights().add(new two.Light(ln0, two.LightType.Direct, false, two.rgb(0xffeedd), 1.5));

    var ln1 = scene.nodes().add(new two.Node3(vec3(0.0), look_dir(normalize(vec3(1.0, -0.5, 1.0)))));
    var l1 = scene.lights().add(new two.Light(ln0, two.LightType.Direct, false, two.rgb(0xddddff), 0.5));

fu convolution_program(GfxSystem gfx)
{
	var program = gfx.programs.create('convolution');
	program.set_source(two.ShaderType.Vertex, convolution_vertex());
	program.set_source(two.ShaderType.Fragment, convolution_fragment());

	program.register_modes(0, { 'KERNEL_SIZE' });
	return program;
}

    // MATERIALS

    var pbr = app.gfx.programs.fetch('pbr/pbr');
    var phong = app.gfx.programs.fetch('pbr/phong');

    var program = app.gfx.programs.create('skin');
    program.set_block(two.MaterialBlock.Lit);
    program.set_block(two.MaterialBlock.Phong);
    program.set_block(two.MaterialBlock.User);
    program.set_source(two.ShaderType.Vertex, skin_vertex);
    program.set_source(two.ShaderType.Fragment, skin_fragment);
    program.register_blocks(pbr.registered_blocks);

    var program_uv = app.gfx.programs.create('skin_uv');
    program_uv.set_block(two.MaterialBlock.Lit);
    program_uv.set_block(two.MaterialBlock.Phong);
    program_uv.set_block(two.MaterialBlock.User);
    program_uv.set_source(two.ShaderType.Vertex, skin_vertex_uv);
    program_uv.set_source(two.ShaderType.Fragment, skin_fragment);
    program_uv.register_blocks(pbr.registered_blocks);

    // @todo
    //program_uv.defines.push_back({ 'PASS_DIFFUSE', '' });

    this.material = app.gfx.materials.create('skin'); var m = material;
        //m.program = phong;
        m.program = program;
        //m.base.uv0_scale = vec2(1.0, -1.0);
        m.lit.normal.texture = app.gfx.textures.file('LeePerrySmith/Norm.jpg');
        m.lit.normal.value = -1.5;
        m.phong.diffuse.value = app.gfx.textures.file('LeePerrySmith/Diff.jpg');
        m.phong.diffuse.value = two.rgb(0xbbbbbb);
        m.phong.specular.value = two.rgb(0x555555);
        var roughness = 0.185;
        var specular_brightness = 0.7;
        m.user.attr0 = new two.vec4(roughness, specular_brightness, 0.0, 0.0);

    this.material_uv = app.gfx.materials.create('skin_uv'); m = material_uv;
        // @todo
        m = material;
        m.name = 'skin_uv';
        m.program = program_uv;

    var model = app.gfx.models.file('LeePerrySmith'); // .glb

    var n = scene.nodes().add(new two.Node3(vec3(0.0, -50.0, 0.0), ZeroQuat, vec3(100.0)));
    var it = scene.items().add(new two.Item(n, model, 0, material));
    this.mesh = n;
    this.item = it;

    var beckmann = render_beckmann(app.gfx, uvec2(512U));
    material.user.tex4 = beckmann;

    material.user.tex0 = uv.tex;
    material.user.tex1 = blur1.tex;
    material.user.tex2 = blur2.tex;
    material.user.tex3 = blur3.tex;
}

var event = viewer.mouse_event(two.DeviceType.Mouse, two.EventType.Moved)
if(event.valid())
{
    mouse.x = event.relative.x - viewer.frame.size.x / 2.0;
    mouse.y = event.relative.y - viewer.frame.size.y / 2.0;
}

rotation.y += 0.05 * (mouse.x * 0.001 - rotation.y);
rotation.x += 0.05 * (mouse.y * 0.001 - rotation.x);

mesh.apply(new two.vec3(0.0, -50.0, 0.0), new two.quat(rotation), new two.vec3(100.0));

var render = new two.Render(two.Shading.Shaded, viewer.viewport, app.gfx.main_target(), app.gfx.render_frame);
app.gfx.renderer.gather(render);
app.gfx.renderer.begin(render);

var viewport = new two.Viewport(render.camera, render.scene, new two.uvec4(new two.uvec2(0), new two.uvec2(512)));
Render subrender = new two.Render(two.Shading.Shaded, viewport, render.target, uv, app.gfx.render_frame);
subrender.shot = render.shot;

item.material = material_uv;
//var renderModelUV = new THREE.RenderPass(scene, camera, materialUV, new THREE.Color(0x575757));
app.gfx.renderer.subrender(render, subrender, render_pbr_forward);

pass_bloom(app.gfx, render, uv.tex, blur1, true, 1.0, 15, 2.0, 512);
pass_bloom(app.gfx, render, uv.tex, blur2, true, 1.0, 25, 3.f, 512);
pass_bloom(app.gfx, render, uv.tex, blur3, true, 1.0, 25, 4.0, 512);

item.material = material;
render_pbr_forward(app.gfx, render);

app.gfx.renderer.end(render);

