// tiled_forward.js

var lights_input =  `#define u_tiles u_user_p0
    #define s_tiles s_user0
    #define s_lights s_user1`;

var lights_fragment = `//#define ALL_LIGHTS
    #ifndef ALL_LIGHTS
    ivec2 iuv = ivec2(gl_FragCoord.xy) / 32;
    vec4 tile = texelFetch(s_tiles, iuv, 0);
    #endif
    for (int i = 0; i < 4; i++)
    {
    #ifndef ALL_LIGHTS
        float tileVal = tile.x * 255.0;
        tile.xyzw = tile.yzwx;
        if(tileVal == 0.0) { continue; }
        float tileDiv = 128.0;
    #endif
        for (int j = 0; j < 8; j++)
        {
    #ifndef ALL_LIGHTS
            if (tileVal < tileDiv) { tileDiv *= 0.5; continue; }
            tileVal -= tileDiv;
            tileDiv *= 0.5;
    #endif

            int uvx = 8 * i + j;

            vec4 light_p0 = texelFetch(s_lights, ivec2(uvx, 0), 0);
            vec3 position = light_p0.xyz;
            float range = light_p0.w;

            vec4 light_p1 = texelFetch(s_lights, ivec2(uvx, 1.0), 0);
            vec3 energy = light_p1.xyz;
            float decay = light_p1.w;

            vec3 l = position - fragment.position;
            float a = point_light_decay(length(l), range, decay);
            direct_brdf(energy * a, normalize(l), fragment, material, diffuse, specular);
        }
    }`;

var tiled_vertex = `#include <geometry_vs.sc>`;

var tiled_phong_fragment = `$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal

    #include <encode.sh>
    #include <pbr/pbr.sh>
    #include <pbr/light.sh>
    #define BRDF_BLINN_PHONG
    #include <pbr/light_brdf_three.sh>
    #include <pbr/radiance.sh>
    
    ` + lights_input + `

    void main()
    {
    #include <pbr/fs_fragment.sh>
    #include <pbr/fs_phong_material.sh>
    #include <pbr/fs_phong.sh>
    ` + lights_fragment + `
    #include <pbr/fs_out_pbr.sh>
    }`;

var tiled_three_fragment = `$input v_view, v_position, v_normal, v_tangent, v_color, v_uv0, v_uv1, v_binormal

    #include <encode.sh>
    #include <pbr/pbr.sh>
    #include <pbr/light.sh>
    #define BRDF_STANDARD
    #include <pbr/light_brdf_three.sh>
    #include <pbr/radiance.sh>
    
    ` + lights_input + `

    void main()
    {
    #include <pbr/fs_fragment.sh>
    #include <pbr/fs_pbr_material.sh>
    #include <pbr/fs_pbr.sh>
    ` + lights_fragment + `
    #include <pbr/fs_out_pbr.sh>
    }`;

// Simple form of tiled forward lighting
// using texels as bitmasks of 32 lights

function resize_tiles(gfx, render, state) {
    
    var width = render.rect.z * render.fbo.size.x;
    var height = render.rect.w * render.fbo.size.y;
    
    state.width = width;
    state.height = height;
    state.cols = Math.ceil(width / 32);
    state.rows = Math.ceil(height / 32);

    state.tiles = new two.Texture(new two.uvec2(state.cols, state.rows), false, two.TextureFormat.RGBA8);
}

// Screen rectangle bounds from light sphere's world AABB
function light_bounds(state, camera, pos, r) {

    var minX = state.width, maxX = 0, minY = state.height, maxY = 0;
    var hw = state.width / 2, hh = state.height / 2;

    for (var i = 0; i < 8; i ++) {

        var px = pos.x + (i & 1 ? r : - r);
        var py = pos.y + (i & 2 ? r : - r);
        var pz = pos.z + (i & 4 ? r : - r);
        var vector = camera.project(new two.vec3(px, py, pz));
        var x = (vector.x * hw) + hw;
        var y = (vector.y * hh) + hh;
        minX = Math.min(minX, x);
        maxX = Math.max(maxX, x);
        minY = Math.min(minY, y);
        maxY = Math.max(maxY, y);
    }

    return [ minX, maxX, minY, maxY ];
}

// Generate the light bitmasks and store them in the tile texture
function pack_lights(gfx, render, state) {
    
    var d = new Int32Array(state.cols * state.rows);
    var ld = new Float32Array(32 * 2 * 4);

    var width = render.rect.z * render.fbo.size.x;
    var height = render.rect.w * render.fbo.size.y;
    
    var camera = render.camera;

    d.fill(0);
    //d.fill(0xffffffff);

    state.lights.forEach(function (light, index) {

        var vector = light.node.position();

        var bs = light_bounds(state, camera, vector, light.radius);

        vector = camera.transform(vector);

        ld[4 * index + 0] = vector.x;
        ld[4 * index + 1] = vector.y;
        ld[4 * index + 2] = vector.z;
        ld[4 * index + 3] = light.radius;
        ld[32 * 4 + 4 * index + 0] = light.color.r;
        ld[32 * 4 + 4 * index + 1] = light.color.g;
        ld[32 * 4 + 4 * index + 2] = light.color.b;
        ld[32 * 4 + 4 * index + 3] = light.decay;

        if (bs[1] < 0 || bs[0] > width || bs[3] < 0 || bs[2] > height) return;
        if (bs[0] < 0) bs[0] = 0;
        if (bs[1] > width) bs[1] = width;
        if (bs[2] < 0) bs[2] = 0;
        if (bs[3] > height) bs[3] = height;

        var i4 = Math.floor(index / 8);
        var i8 = 7 - (index % 8);
        var shift = i4 * 8 + i8;
        
        for (var i = Math.floor(bs[ 2 ] / 32); i <= Math.ceil(bs[ 3 ] / 32); i ++) {

            for (var j = Math.floor(bs[ 0 ] / 32); j <= Math.ceil(bs[ 1 ] / 32 ); j ++ ) {

                d[(state.cols * i + j)] |= 1 << shift;
            }
        }
    });

    state.tiles.load_rgba(state.tiles.size, d);
    state.texture.load_float(state.texture.size, ld);
}

var viewer = two.ui.scene_viewer(panel);
two.ui.orbit_controls(viewer);
viewer.viewport.autorender = false;

var radius = 75.0;

function update_materials(state) {
    
    for(var i = 0; i < state.materials.length; ++i) {
        
        var m = state.materials[i];
        m.user.tex0 = state.tiles;
        m.user.tex1 = state.texture;
    }
};

function renderer(gfx, render, state) {
    
    two.begin_pbr_render(gfx, render);

    //if(render.fbo.size != state.size)
        resize_tiles(gfx, render, state);

    update_materials(state);

    pack_lights(gfx, render, state);

    two.pass_clear(gfx, render);
    two.pass_opaque(gfx, render);
    two.pass_solid(gfx, render);
    two.pass_post_auto(gfx, render);
};

if (init) {
    this.importerOBJ = new two.ImporterOBJ(app.gfx);

    this.state = {};
    
    this.state.texture = new two.Texture(new two.uvec2(32, 2), false, two.TextureFormat.RGBA32F);

    var camera = viewer.camera;
    camera.fov = 40.0; camera.near = 1.0; camera.far = 2000.0;
    camera.eye = new two.vec3(0.0, 0.0, 240.0);
    
    var viewport = viewer.viewport;
    //viewport.set_clustered(app.gfx);

    var scene = viewer.scene;

    var env = scene.env;
    env.radiance.colour = two.rgb(0xffffff);
    env.radiance.ambient = 0.33;

    env.background.colour = two.rgb(0x111111);
    viewer.viewport.clear_colour = two.rgb(0x111111);
    
    this.solid = app.gfx.programs.file('solid');
    this.phong = app.gfx.programs.file('pbr/phong');
    this.three = app.gfx.programs.file('pbr/three');

    var tiled_phong = app.gfx.programs.create('tiledphong');
    tiled_phong.set_source(two.ShaderType.Vertex, tiled_vertex);
    tiled_phong.set_source(two.ShaderType.Fragment, tiled_phong_fragment);
    tiled_phong.register_blocks(phong);
    tiled_phong.set_block(two.MaterialBlock.Alpha);
    tiled_phong.set_block(two.MaterialBlock.Lit);
    tiled_phong.set_block(two.MaterialBlock.Phong);
    tiled_phong.set_block(two.MaterialBlock.User);

    var tiled_three = app.gfx.programs.create('tiledthree');
    tiled_three.set_source(two.ShaderType.Vertex, tiled_vertex);
    tiled_three.set_source(two.ShaderType.Fragment, tiled_three_fragment);
    tiled_three.register_blocks(three);
    tiled_three.set_block(two.MaterialBlock.Alpha);
    tiled_three.set_block(two.MaterialBlock.Lit);
    tiled_three.set_block(two.MaterialBlock.Pbr);
    tiled_three.set_block(two.MaterialBlock.User);

    var m0 = app.gfx.materials.create('m0');
    var m1 = app.gfx.materials.create('m1');
    var m2 = app.gfx.materials.create('m2');
    var m3 = app.gfx.materials.create('m3');
    
    m0.program = tiled_three; m0.pbr.albedo.value = two.rgb(0x888888); m0.pbr.metallic.value = 1.0; m0.pbr.roughness.value = 0.66;
    m1.program = tiled_three; m1.pbr.albedo.value = two.rgb(0x666666); m1.pbr.metallic.value = 0.1; m1.pbr.roughness.value = 0.33;
    m2.program = tiled_phong; m2.phong.diffuse.value = two.rgb(0x777777); m2.phong.shininess.value = 20;
    m3.program = tiled_phong; m3.phong.diffuse.value = two.rgb(0x555555); m3.phong.shininess.value = 10; m3.phong.toon = true;
    
    var materials = [m0, m1, m2, m3];
    this.state.materials = materials;

    var model = app.gfx.models.file('WaltHead');
    
    var sphere = app.gfx.shape(new two.Sphere(0.5));
    var big_sphere = app.gfx.shape(new two.Sphere(0.5 * 6.66));

    var transparent = Math.round(Math.random() * 3);
    materials[transparent].alpha.alpha = 0.9;

    //transparent : tIndex == = index ? true : false,
    //mtl.uniforms['opacity'].value = tIndex == = index ? 0.9 : 1;
    //mtl.side = tIndex == = index ? THREE.FrontSide : THREE.DoubleSide;

    var lights = [];
    this.state.lights = lights;

    for(var i = 0; i < materials.length; ++i)
    {
        var material = materials[i];
        var position = new two.vec3(Math.sin(i * Math.PI / 2) * radius, 0.0, Math.cos(i * Math.PI / 2) * radius);
        var rotation = new two.quat(new two.vec3(0.0, i * Math.PI / 2, 0.0));

        var n = scene.nodes().add(new two.Node3(position, rotation));

        var m = scene.nodes().add(new two.Node3());
        m.derive(n, new two.vec3(0.0, -37.0, 0.0));
        
        var it = scene.items().add(new two.Item(m, model, 0, material));

        for(var j = 0; j < 8; j++)
        {
            var color = two.hsl(Math.random(), 1.0, 0.5);
            color = new two.Colour(color.r, color.g, color.b);
            
            var ml = app.gfx.materials.create('light' + material.name + j.toString()); 
            ml.program = solid; ml.solid.colour.value = color;

            var mla = app.gfx.materials.create('lightalpha' + material.name + j.toString());
            mla.program = solid; mla.solid.colour.value = color; mla.alpha.alpha = 0.033;

            var l = scene.nodes().add(new two.Node3());
            var i0 = scene.items().add(new two.Item(l, sphere, 0, ml)); // MaterialSolid(color)));
        
            //var i1 = scene.items().add(new two.Item(l, big_sphere, 0, ma)); // MaterialSolid(color), MaterialAlpha(0.033));
            //l.children[1].scale.set(6.66, 6.66, 6.66);

            //var light = scene.lights().add(new two.Light(l, two.LightType.Point, false, color, 1.0, radius));
            
            var l = {
                parent: n,
                node: l,
                color: color,
                radius: radius,
                decay: 1.0,
                sy: Math.random(),
                sr: Math.random(),
                sc: Math.random(),
                py: Math.random() * Math.PI,
                pr: Math.random() * Math.PI,
                pc: Math.random() * Math.PI,
                dir: Math.random() > 0.5 ? 1.0 : -1.0
            };
            
            lights.push(l);
        }
    }
}

for(var i = 0; i < this.state.lights.length; ++i)
{
    var l = this.state.lights[i];
    
    var r = 0.8 + 0.2 * Math.sin(l.pr + (0.6 + 0.3 * l.sr) * time);
    var x = (Math.sin(l.pc + (0.8 + 0.2 * l.sc) * time * l.dir)) * r * radius;
    var z = (Math.cos(l.pc + (0.8 + 0.2 * l.sc) * time * l.dir)) * r * radius;
    var y = Math.sin(l.py + (0.8 + 0.2 * l.sy) * time) * r * 32.0;
    
    l.node.derive(l.parent, new two.vec3(x, y, z));
}

var render = new two.Render(two.Shading.Shaded, viewer.viewport, app.gfx.main_target(), app.gfx.render_frame);
app.gfx.renderer.gather(render);
app.gfx.renderer.begin(render);
renderer(app.gfx, render, this.state);
app.gfx.renderer.end(render);

