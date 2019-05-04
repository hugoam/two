-- two toolchain
-- module

function dep(namespace, name, cppmodule, usage_decl, deps)
    local m = {
        project = nil,
        cppmodule = cppmodule,
        namespace = namespace,
        name = name,
        dotname = string.gsub(name, "-", "."),
        idname = string.gsub(name, "-", "_"),
        usage_decl = usage_decl,
        deps = deps,
    }
    
    if namespace then
        m.dotname = namespace .. "." .. m.dotname
        m.idname = namespace .. "_" .. m.idname
    end
    
    m.project = project(m.idname)
    m.lib = {
        name = project().name,
        links = {},
        kind = "StaticLib",
    }
    
    if cppmodule then
        modules(m)
    end
    
    return m
end

function module(namespace, name, rootpath, subpath, self_decl, usage_decl, reflect, deps, nomodule)
    local m = {
        project = nil,
        cppmodule = true,
        namespace = namespace,
        name = name,
        dotname = string.gsub(name, "-", "."),
        idname = string.gsub(name, "-", "_"),
        root = rootpath,
        subdir = subpath,
        path = path.join(rootpath, subpath),
        decl = decl,
        self_decl = self_decl,
        usage_decl = usage_decl,
        reflect = reflect,
        unity = false,
        deps = deps or {},
        nomodule = nomodule,
    }
    
    if namespace then
        m.dotname = namespace .. "." .. m.dotname
        m.idname = namespace .. "_" .. m.idname
    end
    
    if not nomodule then
        table.insert(MODULES, m)
    end
    
    if reflect then
        m.refl = refl(m)
    end
    
    return m
end

function refl(m, force_project)
    deps = { two.infra, two.type, two.pool, two.refl }
    table.extend(deps, m.deps)
    table.extend(deps, { m })
    for _, m in ipairs(m.deps) do
        if m.refl then
            table.insert(deps, m.refl)
        end
    end
    m.refl = module(m.namespace, m.name .. "-refl", m.root, path.join("meta", m.subdir), nil, m.usage_decl, false, deps, true)
    m.refl.headers = { path.join(m.root, "meta", string.gsub(m.name, "-", ".") .. ".meta.h") }
    m.refl.sources = { path.join(m.root, "meta", string.gsub(m.name, "-", ".") .. ".meta.cpp") }
    m.decl = refl_decl
    m.refl.force_project = force_project
    m.refl.reflected = m
    return m.refl
end

function link(lib, dep)
    --print("    links " .. dep.name)
    table.insert(lib.links, dep)
    links(dep.name)
    
    -- binaries don't export anything, and we only export from linked static libs
    if dep.kind == "StaticLib" then
        for _, m in ipairs(dep.modules or {}) do
            if lib.kind == "ConsoleApp" then
                defines { m.idname:upper() .. "_EXPORT=" }
            else
                defines { m.idname:upper() .. "_EXPORT=TWO_EXPORT" }
            end
        end
    end
    
    for _, deplink in ipairs(dep.links) do
        local dyntostatic = dep.kind ~= "StaticLib" and deplink.kind == "StaticLib"
        if dyntostatic and not NO_SHARED_LIBS then
            table.insert(lib.links, deplink)
        end
    end
end

function depend(lib, m)
    --print("    depends on " .. m.dotname)
    if m.header_only then
        defines { m.idname:upper() .. "_EXPORT=" }
        if m.self_decl then
            m.self_decl()
        end
    else
        if lib.name ~= m.lib.name and not table.contains(lib.links, m.lib) then
            link(lib, m.lib)
        end
    end
    
    if m.usage_decl then
        m.usage_decl()
    end
end

function decl(m)
    includedirs {
        m.root,
    }
    
    if m.headers then
        files(m.headers)
    else
        files {
            path.join(m.path, "**.h"),
            path.join(m.path, "**.hpp"),
        }
    end
    
    if m.sources then
        files(m.sources)
    else
        files {
            path.join(m.path, "**.cpp"),
        }
    end
    
    local cpps = os.matchfiles(path.join(m.path, "**.cpp"))
    mxx(cpps, m)
    
    defines { m.idname:upper() .. "_LIB" }
    defines { m.idname:upper() .. "_EXPORT=TWO_EXPORT" }
    
    --vpaths { [name] = { "**.h", "**.cpp" } }
    
    modules(m)
    
    if m.self_decl then
        m.self_decl()
    end
    if m.usage_decl then
        m.usage_decl()
    end
    
    if _OPTIONS["gcc"] == "asmjs" and _OPTIONS["jsbind"] and m.reflect then
        files {
            path.join(m.root, "bind", string.gsub(m.name, "-", ".") .. ".c.cpp")
        }
    end
end

function refl_decl(m, as_project)
    if as_project and not m.force_project then
        project(m.reflected.idname)
    end
    decl(m, as_project or m.force_project)
end

function lib(name, modules, libkind, optdeps, norefl)
    print("lib " .. name)
    local lib = {
        name = name,
        kind = libkind,
        modules = {},
        links = {},
    }
    lib.project = project(name)
    kind(libkind)
    
    for _, m in pairs(modules or {}) do
        --print("    module " .. m.dotname)
        table.insert(lib.modules, m)
        m.lib = lib
        m.decl(m)
        if m.refl and not norefl then
            table.insert(lib.modules, m.refl)
            m.refl.lib = lib
            m.refl.decl(m.refl)
        end
    end
    
    local deps = table.union(modules, optdeps or {})
    lib.deps = table.inverse(sort_topological(deps, 'deps'))
    
    for _, m in ipairs(lib.deps) do
        if m ~= null then
            depend(lib, m)
        end
    end
    return lib
end

function libs(modules, libkind, deps)
    for k, m  in pairs(modules) do
        m.lib = lib(m.idname, { m }, libkind, deps, true)
        if m.refl then
            m.refl.lib = lib(m.refl.idname, { m.refl }, libkind, deps)
            table.insert(modules, m.refl)
        end
    end
end

function unity(m)
    m.headers = { path.join(m.root, m.namespace, string.gsub(m.name, "-", ".") .. ".h") }
    m.sources = { path.join(m.root, m.namespace, string.gsub(m.name, "-", ".") .. ".cpp") }
    m.header_only = true
    if m.refl then
        unity(m.refl)
    end
end
