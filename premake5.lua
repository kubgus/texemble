workspace "texemble"
    configurations { "debug", "release" }
    architecture "x86_64"

    filter "configurations:debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:release"
        defines { "RELEASE" }
        optimize "Speed"
        flags { "LinkTimeOptimization" }

    filter "system:windows"
        defines { "WINDOWS" }

outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "texemble"
    location "src/texemble"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outdir .. "/%{prj.name}")
    objdir ("obj/" .. outdir .. "/%{prj.name}")

    files {
        "src/%{prj.name}/**.cpp",
        "src/%{prj.name}/**.h",
    }

    includedirs {
        "src/%{prj.name}",
    }

project "sandbox"
    location "src/sandbox"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "on"

    targetdir ("bin/" .. outdir .. "/%{prj.name}")
    objdir ("obj/" .. outdir .. "/%{prj.name}")

    files {
        "src/%{prj.name}/**.cpp",
        "src/%{prj.name}/**.h",
    }

    includedirs {
        "src/%{prj.name}",
        "src/texemble",
    }

    links {
        "texemble",
    }
