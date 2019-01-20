-- mud toolchain
-- module

function mud_dep(namespace, name, cppmodule, usage_decl, deps)
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
        mud_modules(m)
    end
    
    return m
end

function mud_module(namespace, name, rootpath, subpath, self_decl, usage_decl, reflect, deps, nomodule)
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
        decl = mud_module_decl,
        self_decl = self_decl,
        usage_decl = usage_decl,
        reflect = reflect,
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
        m.refl = mud_refl(m)
    end
    
    return m
end

function mud_refl(m, force_project)
    deps = { mud.infra, mud.type, mud.pool, mud.refl }
    table.extend(deps, m.deps)
    table.extend(deps, { m })
    for _, m in ipairs(m.deps) do
        if m.refl then
            table.insert(deps, m.refl)
        end
    end
    m.refl = mud_module(m.namespace, m.name .. "-refl", m.root, path.join("meta", m.subdir), nil, m.usage_decl, false, deps, true)
    m.decl = mud_refl_decl
    m.refl.force_project = force_project
    m.refl.reflected = m
    return m.refl
end

function mud_links(lib, dep)
    --print("    links " .. dep.name)
    table.insert(lib.links, dep)
    links(dep.name)
    
    -- binaries don't export anything, and we only export from linked static libs
    if dep.kind == "StaticLib" then
        for _, m in ipairs(dep.modules or {}) do
            if lib.kind == "ConsoleApp" then
                defines { m.idname:upper() .. "_EXPORT=" }
            else
                defines { m.idname:upper() .. "_EXPORT=MUD_EXPORT" }
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

function mud_depend(lib, m)
    --print("    depends on " .. m.dotname)
    if lib.name ~= m.lib.name and not table.contains(lib.links, m.lib) then
        mud_links(lib, m.lib)
    end
    
    if m.usage_decl then
        m.usage_decl()
    end
end

function mud_module_decl(m)
    includedirs {
        m.root,
    }
    
    files {
        path.join(m.path, "**.h"),
        path.join(m.path, "**.cpp"),
    }
    
    local cpps = os.matchfiles(path.join(m.path, "**.cpp"))
    mud_mxx(cpps, m)
    
    defines { m.idname:upper() .. "_LIB" }
    defines { m.idname:upper() .. "_EXPORT=MUD_EXPORT" }
    
    --vpaths { [name] = { "**.h", "**.cpp" } }
    
    mud_modules(m)
    
    if m.self_decl then
        m.self_decl()
    end
    if m.usage_decl then
        m.usage_decl()
    end
    
    if _OPTIONS["gcc"] == "asmjs" and _OPTIONS["jsbind"] and m.reflect then
        files {
            path.join(m.root, "bind", m.subdir, "c.cpp")
        }
    end
end

function mud_refl_decl(m, as_project)
    if as_project and not m.force_project then
        project(m.reflected.idname)
    end
    mud_module_decl(m, as_project or m.force_project)
end

function mud_project(lib, name, modules, libkind, optdeps, norefl)
    print("lib " .. name)
    lib.project = project(name)
    kind(libkind)
    lib.name = name
    lib.kind = libkind
    lib.modules = {}
    lib.links = {}
    
    for k, m in pairs(modules or {}) do
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
            mud_depend(lib, m)
        end
    end
end

function mud_lib(name, modules, libkind, deps, norefl)
    local lib = {}
    mud_project(lib, name, modules, libkind, deps, norefl)
    return lib
end

function mud_libs(modules, libkind, deps)
    for k, m  in pairs(modules) do
        m.lib = mud_lib(m.idname, { m }, libkind, deps, true)
        if m.refl then
            m.refl.lib = mud_lib(m.refl.idname, { m.refl }, libkind, deps)
            table.insert(modules, m.refl)
        end
    end
end
