project "sandbox"
    location "%{wks.location}/%{prj.name}"
    kind "ConsoleApp"
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
        "%{wks.location}/texemble/src",
    }

    links {
        "texemble",
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
