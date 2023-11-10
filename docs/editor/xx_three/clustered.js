// clustered.js

var viewer = two.ui.scene_viewer(panel);
two.ui.orbit_controls(viewer);

var radius = 75.0;

var viewport = viewer.viewport;

if (!viewport.clustered) {
    // @todo fix clustered
    //viewport.set_clustered(app.gfx);
}

if (init) {
    this.importerOBJ = new two.ImporterOBJ(app.gfx);

    var camera = viewer.camera;
    camera.fov = 40.0; camera.near = 1.0; camera.far = 2000.0;
    camera.eye = new two.vec3(0.0, 0.0, 240.0);
    
    var scene = viewer.scene;

    var env = scene.env;
    env.radiance.ambient = new two.Colour(0.33);

    env.background.colour = two.rgb(0x111111);
    viewport.clear_colour = two.rgb(0x111111);
    
    var solid = app.gfx.programs.file('solid');
    var phong = app.gfx.programs.file('pbr/phong');
    var three = app.gfx.programs.file('pbr/three');

    var m0 = app.gfx.materials.create('m0');
    var m1 = app.gfx.materials.create('m1');
    var m2 = app.gfx.materials.create('m2');
    var m3 = app.gfx.materials.create('m3');
    
    m0.program = three; m0.pbr.albedo.value = two.rgb(0x888888); m0.pbr.metallic.value = 1.0; m0.pbr.roughness.value = 0.66;
    m1.program = three; m1.pbr.albedo.value = two.rgb(0x666666); m1.pbr.metallic.value = 0.1; m1.pbr.roughness.value = 0.33;
    m2.program = phong; m2.phong.diffuse.value = two.rgb(0x777777); m2.phong.shininess.value = 20;
    m3.program = phong; m3.phong.diffuse.value = two.rgb(0x555555); m3.phong.shininess.value = 10; m3.phong.toon = true;
    
    var materials = [m0, m1, m2, m3];

    var model = app.gfx.models.file('WaltHead');
    
    var sphere = app.gfx.shape(new two.Sphere(0.5));
    var big_sphere = app.gfx.shape(new two.Sphere(0.5 * 6.66));

    var transparent = Math.round(Math.random() * 3);
    materials[transparent].alpha.alpha.value = 0.9;

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
            mla.program = solid; mla.solid.colour.value = color; mla.alpha.alpha.value = 0.033;

            var l = scene.nodes().add(new two.Node3());
            var i0 = scene.items().add(new two.Item(l, sphere, 0, ml)); // MaterialSolid(color)));
        
            //var i1 = scene.items().add(new two.Item(l, big_sphere, 0, ma)); // MaterialSolid(color), MaterialAlpha(0.033));
            //l.children[1].scale.set(6.66, 6.66, 6.66);

            var light = scene.lights().add(new two.Light(l, two.LightType.Point, false, color, 1.0, radius));
            
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
            
            this.lights.push(l);
        }
    }
}

var time = app.gfx.time;

for(var i = 0; i < this.lights.length; ++i)
{
    var l = this.lights[i];
    
    var r = 0.8 + 0.2 * Math.sin(l.pr + (0.6 + 0.3 * l.sr) * time);
    var x = (Math.sin(l.pc + (0.8 + 0.2 * l.sc) * time * l.dir)) * r * radius;
    var z = (Math.cos(l.pc + (0.8 + 0.2 * l.sc) * time * l.dir)) * r * radius;
    var y = Math.sin(l.py + (0.8 + 0.2 * l.sy) * time) * r * 32.0;
    
    l.node.derive(l.parent, new two.vec3(x, y, z));
}
