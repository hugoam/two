// tiled_forward.js

var viewer = two.ui.scene_viewer(app.ui.begin());
two.ui.orbit_controller(viewer);

//viewer.viewport.comp<Tonemap>().enabled = true;

var camera = viewer.camera;
camera.set_clustered(app.gfx, viewer.viewport);

var radius = 75.0;

if(typeof this.state == 'undefined') {
    this.state = 1;
    
    this.importerOBJ = new two.ImporterOBJ(app.gfx);

    var scene = viewer.scene;

    scene.env.radiance.colour = new two.Colour(1.0);
    scene.env.radiance.energy = 0.066;
    scene.env.radiance.ambient = 0.33;
    //scene.add(new THREE.AmbientLight(0xffffff, 0.33));

    this.solid = app.gfx.programs.file('solid');
    this.pbr = app.gfx.programs.file('pbr/pbr');

    var m0 = app.gfx.materials.create('m0');
    var m1 = app.gfx.materials.create('m1');
    var m2 = app.gfx.materials.create('m2');
    var m3 = app.gfx.materials.create('m3');
    
    m0.program = pbr; m0.pbr.albedo.value = two.rgb(0x888888); m0.pbr.metallic.value = 1.0; m0.pbr.roughness.value = 0.66;
    m1.program = pbr; m1.pbr.albedo.value = two.rgb(0x666666); m1.pbr.metallic.value = 0.1; m1.pbr.roughness.value = 0.33;
    m2.program = pbr; m2.pbr.albedo.value = two.rgb(0x777777); m2.pbr.metallic.value = 0.1; m2.pbr.roughness.value = 0.33;
    m3.program = pbr; m3.pbr.albedo.value = two.rgb(0x555555); m3.pbr.metallic.value = 0.1; m3.pbr.roughness.value = 0.33;
    
    m2.pbr.specular_mode = two.PbrSpecularMode.Phong;
    m3.pbr.diffuse_mode = two.PbrDiffuseMode.Toon; m3.pbr.specular_mode = two.PbrSpecularMode.Toon;
    
    var materials = [m0, m1, m2, m3];
    //{ type: 'physical', uniforms : { 'diffuse': 0x888888, 'metalness' : 1.0, 'roughness' : 0.66 }, defines : {} },
    //{ type: 'standard', uniforms : { 'diffuse': 0x666666, 'metalness' : 0.1, 'roughness' : 0.33 }, defines : {} },
    //{ type: 'phong', uniforms : { 'diffuse': 0x777777, 'shininess' : 20 }, defines : {} },
    //{ type: 'phong', uniforms : { 'diffuse': 0x555555, 'shininess' : 10 }, defines : { TOON: 1 } }

    var model = app.gfx.models.file('WaltHead');
    
    var sphere = app.gfx.shape(new two.Sphere(0.5));
    var big_sphere = app.gfx.shape(new two.Sphere(0.5 * 6.66));

    var transparent = Math.round(Math.random() * 3);
    materials[transparent].alpha.alpha = 0.9;

    //transparent : tIndex == = index ? true : false,
    //mtl.uniforms['opacity'].value = tIndex == = index ? 0.9 : 1;
    //mtl.side = tIndex == = index ? THREE.FrontSide : THREE.DoubleSide;

    this.lights = [];

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

            var ml = app.gfx.materials.create('light' + material.name + j.toString()); 
            ml.program = solid; ml.solid.colour.value = color;

            var mla = app.gfx.materials.create('lightalpha' + material.name + j.toString());
            mla.program = solid; mla.solid.colour.value = color; mla.alpha.alpha = 0.033;

            var l = scene.nodes().add(new two.Node3());
            var i0 = scene.items().add(new two.Item(l, sphere, 0, ml)); // MaterialSolid(color)));
        
            //var i1 = scene.items().add(new two.Item(l, big_sphere, 0, ma)); // MaterialSolid(color), MaterialAlpha(0.033));
            //l.children[1].scale.set(6.66, 6.66, 6.66);

            var light = scene.lights().add(new two.Light(l, two.LightType.Point));
            light.range = 40.0;
            light.colour = color;
            
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

for(var i = 0; i < lights.length; ++i)
{
    var l = lights[i];
    
    var r = 0.8 + 0.2 * Math.sin(l.pr + (0.6 + 0.3 * l.sr) * time);
    var x = (Math.sin(l.pc + (0.8 + 0.2 * l.sc) * time * l.dir)) * r * radius;
    var z = (Math.cos(l.pc + (0.8 + 0.2 * l.sc) * time * l.dir)) * r * radius;
    var y = Math.sin(l.py + (0.8 + 0.2 * l.sy) * time) * r * 32.0;
    
    l.node.derive(l.parent, new two.vec3(x, y, z));
}
