outdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

workspace "texemble"
    configurations { "debug", "release" }
    architecture "x86_64"
    startproject "sandbox"

    include "texemble"
    include "sandbox"
