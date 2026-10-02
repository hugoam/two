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
        configuration { "not vs*" }
            postbuildcommands {
                "cp -f $(TARGET) \"" .. path.join(TWO_DIR, "bin", "clrefl") .. "\"",
            }
        configuration {}
    two_binary("amalg", { two.amalg })
    two_binary("webcl", { two.webcl })
end

if _OPTIONS["webcompile"] then
	two_webcl("webproject")
end

dofile "two_example.lua"
