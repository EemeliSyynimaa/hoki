DIR = path.getabsolute("..")
BUILD_DIR = path.join(DIR, ".build")
TARGET_NAME = "hoki"

dofile("config.lua")

solution "solution"
    configurations
    {
        "release",
        "debug"
    }
    
    platforms
    {
        "x32",
        "x64"
    }
    
    language "C"

    configuration {}
    
build_config(BUILD_DIR)

project "project"
    targetname(TARGET_NAME)

    configuration { "vs*" }
        kind "WindowedApp"
        flags { "WinMain" }
        
    files
    {
        path.join(DIR, "source", "**.h"),
        path.join(DIR, "source", "**.c")
    }
    
    includedirs
    {
        path.join(DIR, "source")
    }
