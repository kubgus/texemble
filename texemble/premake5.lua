project "texemble"
    location "%{wks.location}/%{prj.name}"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" .. outdir .. "/%{prj.name}")
    objdir ("%{wks.location}/obj/" .. outdir .. "/%{prj.name}")

    files {
        "src/**.cpp",
        "src/**.h",
    }

    includedirs {
        "src",
    }

    filter "configurations:debug"
        defines { "DEBUG", "TXM_DEBUG" }
        runtime "Debug"
        symbols "on"

    filter "configurations:release"
        defines { "RELEASE", "TXM_RELEASE" }
        runtime "Release"
        optimize "on"

    filter "system:windows"
        defines { "WINDOWS", "TXM_WINDOWS" }

    filter "system:linux"
        defines { "LINUX", "TXM_LINUX" }
        links { "pthread" }
