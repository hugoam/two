-- two toolchain
-- actions

function copy_shaders(subpath)
    local fullpath = path.join(TWO_DIR, subpath)
    local destpath = path.join(TWO_DIR, "data/shaders")
    local shaders = os.matchfiles(path.join(fullpath, "**.*"))
    for _, file in ipairs(shaders) do
        local relpath = path.getrelative(fullpath, file)
        local dest = path.join(destpath, relpath)
        print("copying shader " .. relpath)
        os.mkdir(path.getdirectory(dest))
        local success, err = os.copyfile(file, dest)
        if not success then
            print("error: " .. err)
        end
    end
end

function setup_shaders()
    copy_shaders("src/gfx/Shaders")
    copy_shaders("src/gfx-pbr/Shaders")
end

function amalgamate(modules)
    for _, m in ipairs(modules) do
        local dir = os.getcwd()
        os.chdir(m.root)
        local jsonfile = m.path .. "/amalg.json"
        local cmd = path.join(TWO_DIR, "bin/amalg") .. " " .. '"' .. TWO_DIR .. '"'
        os.execute(cmd)
        os.chdir(dir)
    end
end

function write_api(m)
    headers = os.matchfiles(path.join(m.path, "**.h"))
    --table.insert(headers, os.matchfiles(path.join(m.path, "**.hpp")))
    
    local f, err = io.open(path.join(m.path, "Api.h"), "wb")
    io.output(f)
    for _, h in ipairs(headers) do
        if not string.find(h, "Api.h") then
            io.printf("#include <" .. path.getrelative(m.root, h) .. ">")
        end
    end
    io.printf("")
    f:close()
end

function write_module_xx(m)
    local p = io.printf
    p("module;")
    p("#include <infra/Cpp20.h>")
    p("#include <infra/Config.h>")
    p("")
    p("export module " .. m.dotname .. ";")
    p("import std;")
    p("")
    for _, dep in ipairs(m.deps or {}) do
        if dep.cppmodule then
            p("export import " .. dep.dotname .. ";")
        end
    end
    p("")
    p("#include <" .. m.subdir .. "/Api.h>")
    if m.reflect then
        --p("#include <meta/" .. m.name .. ".meta.h>")
    end
    p("")
    
end

function write_ixx(m)
	local f, err = io.open(path.join(m.path, m.dotname2 .. ".ixx"), "wb")
    io.output(f)
    write_module_xx(m)
    f:close()
end

function write_cxxm(m)
	local f, err = io.open(path.join(m.path, m.dotname2 .. ".cxxm"), "wb")
    io.output(f)
    write_module_xx(m)
    f:close()
end

function bootstrap(modules)
    for _, m in ipairs(modules) do
      --write_api(m)
      --write_ixx(m)
        write_cxxm(m)
    end
end

function concat_files(files)
    for _, filepath in ipairs(files) do
        if os.isfile(filepath) then
            local js, jserr = io.open(filepath, "r")
            local content = js:read("*a")
            io.printf(content)
            js:close()
        end
    end
end

function gluejs(modules)
    local glue_path = path.join(BUILD_DIR, "js", "glue.js")
    local f, err = io.open(glue_path, "wb")
    io.output(f)
    
    local files = { path.join(TWO_DIR, "src/clrefl", "Module.js") }
    for _, m in ipairs(modules) do
        if m ~= null then
            table.insert(files, path.join(m.root, "bind", string.gsub(m.name, "-", ".") .. ".js"))
        end
    end
    concat_files(files)
    io.printf("")
    
    f:close()

    linkoptions {
        "--post-js " .. glue_path
    }
end

function reflect(modules)
    local current = {}
    includedirs = function(dirs)
        for _, dir in ipairs(dirs) do
            if not table.contains(current.includedirs, dir) then
                --print("includedir " .. dir)
                table.insert(current.includedirs, dir)
            end
        end
    end
    
    local temp_refl_path = path.join(BUILD_DIR, "refl")
    local jsons = {}
    for _, m in ipairs(modules) do
        if m.meta then
            print('two reflect ' .. m.idname)
            current = {
                namespace = iif(m.namespace, m.namespace, ''),
                name = m.name,
                dotname = m.dotname,
                idname = m.idname,
                root = m.root,
                subdir = m.subdir,
                path = m.path,
                dependencies = {},
                includedirs = {},
            }
            
            for i, dep in ipairs(m.deps or {}) do
                if dep.meta then
                    table.insert(current.dependencies, dep.idname)
                end
            end
            
            -- trick to collect the includes
            if m.lib then
                for i, dep in ipairs(m.lib.deps or {}) do
                    if dep.usage_decl then
                        dep.usage_decl()
                    end
                end
            end
            
            local json_path = path.join(temp_refl_path, m.idname .. "_refl.json")
            local f, err = io.open(json_path, "wb")
            io.output(f)
            io.printf(json.encode(current))
            f:close()
            
            table.insert(jsons, json_path)
        end
    end
    
    print(path.join(TWO_DIR, "bin/clrefl") .. " " .. table.concat(jsons, " "))
    os.execute(path.join(TWO_DIR, "bin/clrefl") .. " " .. table.concat(jsons, " "))
end

newaction {
    trigger     = "bootstrap",
    description = "Bootstrap c++ modules",
    execute     = function()
        bootstrap(MODULES)
    end
}

newaction {
    trigger     = "reflect",
    description = "Generate reflection",
    execute     = function()
        reflect(MODULES)
    end
}

newaction {
    trigger     = "amalgamate",
    description = "Generate amalgamation files",
    execute     = function()
        amalgamate(MODULES)
    end
}

newaction {
    trigger     = "copydata",
    description = "Copy data files",
    execute     = function()
        setup_shaders()
    end
}


