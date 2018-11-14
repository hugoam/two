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

function mud_example(name, deps, ismodule)

    uses_example = function()
        configuration { "asmjs" }
            linkoptions {
                "--preload-file ../../../data/examples/" .. name .. "@data/",
            }
        
        configuration {}
    end

    _G[name] = mud_module(nil, "_" .. name, path.join(MUD_DIR, "example"), name, nil, nil, uses_example, mud.mud, not ismodule)
    
    mud_shell(name, table.union({ _G[name] }, deps), {})
end

--mud_example("00_ui",               {})
    
if not _OPTIONS["renderer-gl"] then
    mud_example("00_tutorial",          {}, true)
    mud_example("00_cube",              {})
    mud_example("01_shapes",            {})
    mud_example("03_materials",         {})
    mud_example("02_camera",            { _G["03_materials"] })
    mud_example("04_lights",            { _G["01_shapes"], _G["03_materials"] })
    mud_example("04_sponza",            { _G["01_shapes"], _G["03_materials"], _G["04_lights"] })
    mud_example("05_character",         { _G["03_materials"] })
    mud_example("06_particles",         {})
    mud_example("07_gltf",              {})
    mud_example("07_prefabs",           { _G["07_gltf"] })
    mud_example("08_sky",               { _G["01_shapes"], _G["03_materials"] })
    mud_example("09_live_shader",       {})
    mud_example("10_post_process",      { _G["01_shapes"], _G["03_materials"] })
    mud_example("11_selection",         { _G["01_shapes"], _G["03_materials"] })
    mud_example("12_ui",                { _G["01_shapes"], _G["03_materials"] })
    mud_example("13_live_ui",           {})
    mud_example("14_live_gfx",          {})
    mud_example("14_live_gfx_visual",   {})
    mud_example("15_script",            { _G["01_shapes"], _G["03_materials"] }, true)
    mud_example("16_visual_script",     { _G["01_shapes"], _G["03_materials"] })
    mud_example("17_wfc",               {})
    --mud_example("18_pathfinding",     {})
    mud_example("19_multi_viewport",    {})
    mud_example("20_meta",              { _G["01_shapes"], _G["03_materials"] })
end

if _OPTIONS["renderer-bgfx"] then
    project "09_live_shader"
        configuration { "asmjs" }
            uses_shaderc()
end
