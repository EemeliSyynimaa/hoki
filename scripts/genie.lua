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

project "win32"
    targetname(TARGET_NAME)

    kind "WindowedApp"
        
    flags 
    { 
        "WinMain", 
        "NoIncrementalLink",
        "NoImportLib",
        "NoWinRT",
        "NoEditAndContinue"
    }
    
    links 
    { 
        "opengl32"
    }
    
    files
    {
        path.join(DIR, "source", "win32_*.h"),
        path.join(DIR, "source", "win32_*.c")
    }
    
    includedirs
    {
        path.join(DIR, "source")
    }

project "game"
    targetname(TARGET_NAME)
    
    kind "SharedLib"
    
    configuration { "vs*" }
        flags 
        { 
            "NoIncrementalLink",
            "NoImportLib",
            "NoWinRT",
            "NoEditAndContinue"
        }
        
        links 
        { 
            "opengl32"
        }
    
    files
    {
        path.join(DIR, "source", "**.h"),
        path.join(DIR, "source", "**.c")
    }
    
    removefiles
    {
        path.join(DIR, "source", "win32_*");
    }
    
    includedirs
    {
        path.join(DIR, "source")
    }