-- mud toolchain
-- global configuration

flags {
    "Cpp17",
}

removeflags {
    "StaticRuntime",
    "NoFramePointer",
}

configuration { "Debug" }
    targetsuffix "_d"

configuration { "Release" }
    targetsuffix ""
    
    removeflags {
        "Symbols",
    }

configuration {}

configuration { "asmjs", "Release" }
    --flags { "Optimize" }
    --flags { "OptimizeSize" }
    flags { "OptimizeSpeed" }

configuration { "asmjs", "Debug" }
    --removeflags { "NoExceptions" }
    --buildoptions { "-s SAFE_HEAP=1" }
    --linkoptions { "-s SAFE_HEAP=1" }

configuration { "linux-*" }
    buildoptions {
        "-fPIC",
    }

configuration { "*-gcc* or osx" }
    buildoptions {
        "-Wno-shadow",
        "-Wno-undef",
    }
        
configuration {}

function copyLib()
end

configuration { "windows"}
    libdirs {
        "C:/Program Files (x86)/GLEW/lib/Release/Win32",
        "C:/Program Files/GLEW/lib/Release/Win32",
    }
    
    includedirs {
        "C:/Program Files (x86)/GLEW/include",
        "C:/Program Files/GLEW/include",
    }
    
configuration {} 
