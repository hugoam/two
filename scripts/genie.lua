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
    two_binary("amalg", { two.amalg })
    two_binary("webcl", { two.webcl })
end

if _OPTIONS["webcompile"] then
	two_webcl("webproject")
end

dofile "two_example.lua"
