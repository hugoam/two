-- two library

solution "two"
	configurations {
		"Debug",
		"Release",
	}

	platforms {
		--"x32",
		"x64"
	}

	language "C++"
    
    
PROJECT_DIR = path.getabsolute("..")
BUILD_DIR = path.join(path.getabsolute(".."), "build")

dofile "toolchain.lua"
dofile "two.lua"

two_libs();

if _OPTIONS["tools"] then
    two_binary("clrefl", { two.clrefl })
        -- the reflect action runs the generator from bin/, next to genie
        configuration { "vs*" }
            postbuildcommands {
                "copy /Y \"$(TargetPath)\" \"" .. path.translate(path.join(TWO_DIR, "bin", "clrefl.exe"), "\\") .. "\"",
            }
        if _ACTION == "ninja" then
            -- ninja doesn't expose the output path to the post-build commands
            for _, cc in ipairs { "gcc", "clang" } do
                for _, cfg in ipairs { { "Debug", "_d" }, { "Release", "" } } do
                    configuration { "linux-" .. cc .. "*", cfg[1] }
                        postbuildcommands {
                            "cp -f \"" .. path.join(BUILD_DIR, "linux64_" .. cc, "bin", "clrefl" .. cfg[2]) .. "\" \"" .. path.join(TWO_DIR, "bin", "clrefl") .. "\"",
                        }
                end
            end
        else
            configuration { "not vs*" }
                postbuildcommands {
                    "cp -f $(TARGET) \"" .. path.join(TWO_DIR, "bin", "clrefl") .. "\"",
                }
        end
        configuration {}
    two_binary("amalg", { two.amalg })
    two_binary("webcl", { two.webcl })
end

if _OPTIONS["webcompile"] then
	two_webcl("webproject")
end

dofile "two_example.lua"
