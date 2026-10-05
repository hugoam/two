-- two library
-- std module, built from the sources shipped by the standard library (libc++ for clang, libstdc++ for gcc)

-- the MSVC standard library ships its std module next to its headers, the include directory is found
-- from the search paths of the compiler, so that it's the version the compiler picks
local function msvc_std_module_source()
    local cxx = premake.gcc.cxx
    local output = os.outputof(cxx .. " -x c++ -v -E NUL 2>&1")
    for line in output:gmatch("[^\r\n]+") do
        local include = line:match("^%s*(.-[\\/]MSVC[\\/][^\\/]+[\\/]include)%s*$")
        if include then
            local source = path.join(path.getdirectory(path.translate(include, "/")), "modules/std.ixx")
            if not os.isfile(source) then
                error("std module source " .. source .. " not found")
            end
            return source
        end
    end
    error("MSVC include directory not found in the search paths of " .. cxx)
end

local function std_module_source()
    local cxx = premake.gcc.cxx
    if os.is("windows") then
        return msvc_std_module_source()
    end

    local isclang = string.find(cxx, "clang", 1, true) ~= nil
    local manifest = iif(isclang, "libc++.modules.json", "libstdc++.modules.json")
    local manifest_path = os.outputof("realpath \"$(" .. cxx .. " -print-file-name=" .. manifest .. ")\" 2>/dev/null")
    manifest_path = manifest_path and manifest_path:gsub("%s+$", "")
    if not manifest_path or not os.isfile(manifest_path) then
        error("std module manifest " .. manifest .. " not found for " .. cxx)
    end

    local f = io.open(manifest_path, "r")
    local manifest_json = json.decode(f:read("*a"))
    f:close()

    for _, m in ipairs(manifest_json.modules) do
        if m["logical-name"] == "std" then
            local source = m["source-path"]
            if path.isabsolute(source) then
                return source
            end
            -- the path is relative to the manifest, but some distributions (Debian, Ubuntu) move the manifest
            -- without updating it, so it's also tried relative to the lib directory of the compiler
            local compiler = os.outputof("realpath \"$(command -v " .. cxx .. ")\" 2>/dev/null"):gsub("%s+$", "")
            local bases = {
                path.getdirectory(manifest_path),
                path.join(path.getdirectory(path.getdirectory(compiler)), "lib"),
            }
            for _, base in ipairs(bases) do
                local candidate = path.getabsolute(path.join(base, source))
                if os.isfile(candidate) then
                    return candidate
                end
            end
            error("std module source " .. source .. " from " .. manifest_path .. " not found")
        end
    end
    error("no std module in " .. manifest_path)
end

local source = std_module_source()

-- the build only recognizes module interfaces by their extension, libstdc++ ships it as a .cc file
-- the object file is named after the source path, which is in the Visual Studio directory for MSVC
if not path.iscppmodule(source) or os.is("windows") then
    local copy = path.join(BUILD_DIR, "std", "std.cppm")
    os.mkdir(path.getdirectory(copy))
    local ok, err = os.copyfile(source, copy)
    if not ok then
        error("failed to copy " .. source .. ": " .. err)
    end
    source = copy
end

project("std")
    kind "StaticLib"

    removeflags { "Cpp20" }
    flags { "CppLatest" }

    files { source }

    configuration { "*-clang*" }
        buildoptions {
            "-Wno-reserved-module-identifier",
        }

    -- the MSVC std module includes the standard headers in its purview
    configuration { "windows-clang" }
        buildoptions {
            "-Wno-include-angled-in-module-purview",
        }

    configuration {}

std = dep(nil, "std", false)
