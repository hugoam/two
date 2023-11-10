-- two
-- two example application

--function uses_examples()
--    includedirs {
--        path.join(TWO_DIR, "example"),
--    }
--end

--two.examples = {}
--two.examples.all = module(nil, "example", TWO_DIR, "example", nil, uses_examples, false, {}, true)
        
if _OPTIONS["renderer-bgfx"] then
    --two_binary("two_example", two.examples.all, { two })
end

function add_example_data(name)
    configuration { "wasm*" }
        linkoptions {
            "--preload-file ../../../data/examples/" .. name .. "@data/",
        }
    
    configuration {}
end

function two_example(name, deps, exdeps, ismodule)

    local uses_example = function()
        add_example_data(name)
    end

    _G[name] = module(nil, "_" .. name, path.join(TWO_DIR, "example"), name, nil, uses_example, false, deps, not ismodule)
    
    two_binary(name, table.union({ _G[name] }, exdeps))
end


    two_example("00_ui",                { two.frame },                                     {})
    two_example("00_imgui",             { two.frame },                                     {})
    
if not _OPTIONS["renderer-gl"] then
--              name                    dependencies                                       examples deps
--  two_example("00_tutorial",          { two.frame },                                     {}, true)
    two_example("00_cube",              { two.frame },                                     {})
    two_example("01_shapes",            { two.frame },                                     {})
    two_example("03_materials",         { two.frame, two.gfx.pbr, two.gfx.meta, two.uio }, {})
    two_example("02_camera",            { two.frame, two.gfx.pbr },                        { _G["03_materials"] })
    two_example("04_lights",            { two.frame, two.gfx.pbr },                        { _G["01_shapes"], _G["03_materials"] })
    two_example("04_sponza",            { two.frame, two.gfx.pbr, two.gfx.obj },           { _G["01_shapes"], _G["03_materials"], _G["04_lights"] })
    two_example("05_character",         { two.frame, two.gfx.pbr, two.gfx.gltf, two.gfx.edit, two.uio },          { _G["03_materials"] })
    two_example("06_particles",         { two.frame, two.srlz, two.gfx.meta },             {})
    two_example("07_gltf",              { two.frame, two.gfx.pbr, two.gfx.gltf },          {})
--  two_example("07_prefabs",           { two.frame, two.gfx.pbr },                        { _G["07_gltf"] })
    two_example("08_sky",               { two.frame, two.gfx.pbr },                        { _G["01_shapes"], _G["03_materials"] })
    two_example("09_live_shader",       { two.frame },                                     {})
    two_example("10_post_process",      { two.frame, two.gfx.pbr },                        { _G["01_shapes"], _G["03_materials"] })
    two_example("11_selection",         { two.frame, two.gfx.pbr },                        { _G["01_shapes"], _G["03_materials"] })
--  two_example("12_ui",                { two.frame, two.uio, two.ui.meta },               { _G["01_shapes"], _G["03_materials"] })
    two_example("13_live_ui",           { two.frame, two.lang, two.uio, two.ui.meta },     {})
    two_example("14_live_gfx",          { two.frame, two.lang, two.uio, two.gfx.meta },    {})
    two_example("14_live_gfx_visual",   { two.frame, two.lang, two.uio, two.gfx.meta },    {})
--  two_example("15_script",            { two.frame, two.lang, two.uio },                  { _G["01_shapes"], _G["03_materials"] }, true)
--  two_example("16_visual_script",     { two.frame, two.lang, two.uio, two.noise },       { _G["01_shapes"], _G["03_materials"] })
    two_example("17_wfc",               { two.frame, two.gfx.pbr, two.wfc.gfx },           {})
--  two_example("18_pathfinding",       { two.frame, two.gfx.pbr },                        {})
    two_example("19_multi_viewport",    { two.frame },                                     {})
--  two_example("20_meta",              { two.frame, two.gfx.pbr },                        { _G["01_shapes"], _G["03_materials"] })
    two_example("xx_three",             { two.frame, two.gfx.pbr, two.gfx.obj, two.gfx.gltf }, {})
end

if _OPTIONS["jsbind"] then
    if _OPTIONS["as-libs"] then
        two_js("xx_js", { two.frame, two.gfx.pbr, two.gfx.obj, two.gfx.gltf })
        two_js("two", { two.frame, two.gfx.pbr, two.gfx.obj, two.gfx.gltf })
    else
        two_js("xx_js", two.all)
        two_js("two", two.all)
    end
    --project "two"
    --    add_example_data("xx_three")
end

if _OPTIONS["renderer-bgfx"] then
    --project "09_live_shader"
    --    configuration { "wasm*" }
    --        uses_shaderc()
end

project "xx_three"
    defines { "UI=1" }
