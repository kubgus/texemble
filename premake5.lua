outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "texemble"
    configurations { "debug", "release" }
    architecture "x86_64"
    startproject "sandbox"

    include "texemble"
    include "sandbox"

    filter "system:windows"
        defines { "WINDOWS", "TXM_WINDOWS" }
