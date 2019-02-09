-- mud
-- mud example application

function uses_examples()
    includedirs {
        path.join(MUD_DIR, "example"),
    }
end

mud.examples = {}
mud.examples.all = mud_module(nil, "example", MUD_DIR, "example", nil, uses_examples, false, {}, true)
        
if _OPTIONS["renderer-bgfx"] then
    --mud_binary("mud_example", mud.examples.all, { mud })
end

function mud_example(name, deps, exdeps, ismodule)

    uses_example = function()
        configuration { "asmjs" }
            linkoptions {
                "--preload-file ../../../data/examples/" .. name .. "@data/",
            }
        
        configuration {}
    end

    _G[name] = mud_module(nil, "_" .. name, path.join(MUD_DIR, "example"), name, nil, uses_example, false, deps, not ismodule)
    
    mud_binary(name, table.union({ _G[name] }, exdeps), {})
end

--mud_example("00_ui",               {})
    
if not _OPTIONS["renderer-gl"] then
--              name                    dependencies                                   examples deps
--  mud_example("00_tutorial",          { mud.frame },                                     {}, true)
    mud_example("00_cube",              { mud.frame },                                     {})
    mud_example("01_shapes",            { mud.frame },                                     {})
    mud_example("03_materials",         { mud.frame, mud.gfx.pbr, mud.gfx.refl, mud.uio }, {})
    mud_example("02_camera",            { mud.frame, mud.gfx.pbr },                        { _G["03_materials"] })
    mud_example("04_lights",            { mud.frame, mud.gfx.pbr },                        { _G["01_shapes"], _G["03_materials"] })
    mud_example("04_sponza",            { mud.frame, mud.gfx.pbr, mud.gfx.obj },           { _G["01_shapes"], _G["03_materials"], _G["04_lights"] })
    mud_example("05_character",         { mud.frame, mud.gfx.pbr, mud.gfx.gltf, mud.gfx.edit, mud.uio },          { _G["03_materials"] })
    mud_example("06_particles",         { mud.frame, mud.srlz, mud.gfx.refl },             {})
    mud_example("07_gltf",              { mud.frame, mud.gfx.pbr, mud.gfx.gltf },          {})
--  mud_example("07_prefabs",           { mud.frame, mud.gfx.pbr },                        { _G["07_gltf"] })
    mud_example("08_sky",               { mud.frame, mud.gfx.pbr },                        { _G["01_shapes"], _G["03_materials"] })
    mud_example("09_live_shader",       { mud.frame },                                     {})
    mud_example("10_post_process",      { mud.frame, mud.gfx.pbr },                        { _G["01_shapes"], _G["03_materials"] })
    mud_example("11_selection",         { mud.frame, mud.gfx.pbr },                        { _G["01_shapes"], _G["03_materials"] })
--  mud_example("12_ui",                { mud.frame, mud.uio, mud.ui.refl },               { _G["01_shapes"], _G["03_materials"] })
    mud_example("13_live_ui",           { mud.frame, mud.lang, mud.uio, mud.ui.refl },     {})
    mud_example("14_live_gfx",          { mud.frame, mud.lang, mud.uio, mud.gfx.refl },    {})
    mud_example("14_live_gfx_visual",   { mud.frame, mud.lang, mud.uio, mud.gfx.refl },    {})
--  mud_example("15_script",            { mud.frame, mud.lang, mud.uio },                  { _G["01_shapes"], _G["03_materials"] }, true)
--  mud_example("16_visual_script",     { mud.frame, mud.lang, mud.uio, mud.noise },       { _G["01_shapes"], _G["03_materials"] })
    mud_example("17_wfc",               { mud.frame, mud.gfx.pbr, mud.wfc.gfx },           {})
--  mud_example("18_pathfinding",       { mud.frame, mud.gfx.pbr },                        {})
    mud_example("19_multi_viewport",    { mud.frame },                                     {})
--  mud_example("20_meta",              { mud.frame, mud.gfx.pbr },                        { _G["01_shapes"], _G["03_materials"] })
--  mud_example("xx_three",             { mud.frame, mud.gfx.pbr },                        {})
end

if _OPTIONS["jsbind"] then
    if _OPTIONS["as-libs"] then
        mud_js("xx_js", { mud.frame })
        mud_js("two", { mud.frame })
    else
        mud_js("xx_js", mud.all)
        mud_js("two", mud.all)
    end
end

if _OPTIONS["renderer-bgfx"] then
    --project "09_live_shader"
    --    configuration { "asmjs" }
    --        uses_shaderc()
end
