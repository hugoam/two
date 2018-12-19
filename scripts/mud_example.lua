-- mud
-- mud example application

function uses_examples()
    includedirs {
        path.join(MUD_DIR, "example"),
    }
end

mud.examples = {}
mud.examples.all = mud_module(nil, "example", MUD_DIR, "example", nil, nil, uses_examples, {}, true)
        
if _OPTIONS["renderer-bgfx"] then
    --mud_shell("mud_example", mud.examples.all, { mud })
end

function mud_example(name, deps, exdeps, ismodule)

    uses_example = function()
        configuration { "asmjs" }
            linkoptions {
                "--preload-file ../../../data/examples/" .. name .. "@data/",
            }
        
        configuration {}
    end

    _G[name] = mud_module(nil, "_" .. name, path.join(MUD_DIR, "example"), name, nil, nil, uses_example, deps, not ismodule)
    
    mud_shell(name, table.union({ _G[name] }, exdeps), {})
end

--mud_example("00_ui",               {})
    
if not _OPTIONS["renderer-gl"] then
--              name                    dependencies                            examples deps
    mud_example("00_tutorial",          { mud.gfx, mud.gfx.ui },                {}, true)
    mud_example("00_cube",              { mud.gfx, mud.gfx.ui },                {})
    mud_example("01_shapes",            { mud.gfx, mud.gfx.ui },                {})
    mud_example("03_materials",         { mud.gfx, mud.gfx.ui, mud.gfx.pbr, mud.uibackend },   {})
    mud_example("02_camera",            { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   { _G["03_materials"] })
    mud_example("04_lights",            { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   { _G["01_shapes"], _G["03_materials"] })
    mud_example("04_sponza",            { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   { _G["01_shapes"], _G["03_materials"], _G["04_lights"] })
    mud_example("05_character",         { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   { _G["03_materials"] })
    mud_example("06_particles",         { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   {})
    mud_example("07_gltf",              { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   {})
    mud_example("07_prefabs",           { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   { _G["07_gltf"] })
    mud_example("08_sky",               { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   { _G["01_shapes"], _G["03_materials"] })
    mud_example("09_live_shader",       { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   {})
    mud_example("10_post_process",      { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   { _G["01_shapes"], _G["03_materials"] })
    mud_example("11_selection",         { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   { _G["01_shapes"], _G["03_materials"] })
    mud_example("12_ui",                { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   { _G["01_shapes"], _G["03_materials"] })
    mud_example("13_live_ui",           { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   {})
    mud_example("14_live_gfx",          { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   {})
    mud_example("14_live_gfx_visual",   { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   {})
    mud_example("15_script",            { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   { _G["01_shapes"], _G["03_materials"] }, true)
    mud_example("16_visual_script",     { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   { _G["01_shapes"], _G["03_materials"] })
    mud_example("17_wfc",               { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   {})
    --mud_example("18_pathfinding",     { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   {})
    mud_example("19_multi_viewport",    { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   {})
    mud_example("20_meta",              { mud.gfx, mud.gfx.ui, mud.gfx.pbr },   { _G["01_shapes"], _G["03_materials"] })
end

if _OPTIONS["renderer-bgfx"] then
    project "09_live_shader"
        configuration { "asmjs" }
            uses_shaderc()
end
