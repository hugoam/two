-- two library
-- std module, built from the sources shipped by the standard library (libc++ for clang, libstdc++ for gcc)

local function std_module_source()
    local cxx = premake.gcc.cxx
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
if not path.iscppmodule(source) then
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

    configuration {}

std = dep(nil, "std", false)
