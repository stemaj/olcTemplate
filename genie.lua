ROOT_DIR = path.getabsolute(".")

solution "OlcTemplate"
  basedir (ROOT_DIR)
  location (path.join(ROOT_DIR,"solution"))
  language "C++"
  configurations {
    "Debug",
    "Test",
    "Release",
  }
  configuration "Debug"
    targetdir (path.join(ROOT_DIR,"solution/bin/Debug"))
    objdir (path.join(ROOT_DIR,"solution/obj"))
    flags { "Symbols", "Cpp20" }
  configuration "Test"
    targetdir (path.join(ROOT_DIR,"solution/bin/Test"))
    objdir (path.join(ROOT_DIR,"solution/obj"))
    defines { "RUN_TESTS" }
    flags { "Symbols", "Cpp20" }
  configuration "Release"
    targetdir (path.join(ROOT_DIR,"solution/bin/Release"))
    objdir (path.join(ROOT_DIR,"solution/obj"))
    flags { "OptimizeSpeed", "Cpp20" }
  platforms {
    "Native",
    "x64",
    "Universal64",
  }
  includedirs {
    "."    
  }

project "OlcTemplate"
  kind "ConsoleApp"
  files {
    path.join(ROOT_DIR,"**.h"),
    path.join(ROOT_DIR,"**.hpp"),
    path.join(ROOT_DIR,"**.cpp"),
    path.join(ROOT_DIR,"**.lua"),
    path.join(ROOT_DIR,"**.png"),
    path.join(ROOT_DIR,"**.ttf"),
    path.join(ROOT_DIR,"**.wav"),
  }
  includedirs {
    ".",
    "sdk/box2d/include",
    "sdk/imgui-1.90.4",
    "sdk/imgui-1.90.4/backends",
    "sdk/sol2-3.3.0",
    "sdk/lua-5.4.2/include",
    "sdk/soloud/include",
    "sdk/freetype-2.13.1/include",
  }

  configuration "windows"
    includedirs {
    }
    libdirs {
      "sdk/box2d/windows",
      "sdk/freetype-2.13.1/windows",
      "sdk/lua-5.4.2/windows",
      "sdk/soloud/windows",
    }
    links {
      "box2d",
      "freetype",
      "lua54",
      "soloud_static_x64"
    }
    debugdir ".."

  configuration "linux"
    includedirs {
      "/usr/include",
    }
    libdirs {
      "/usr/lib",
      "sdk/box2d/linux",
      "sdk/lua-5.4.2/linux",
      "sdk/soloud/linux",
    }
    links {
       "freetype",
       "X11",
       "GL",
       "pthread",
       "png",
       "stdc++fs",
       "lua54",
       "dl",
       "soloud_static",
       "asound",
       "box2d"
    }
    debugdir "."
 
  configuration "macosx"
    buildoptions_cpp {
      "-Wall",
    }
    includedirs {
      "/usr/local/Cellar/libpng/1.6.43/include"
    }
    libdirs {
      "/usr/local/Cellar/freetype/2.13.2/lib",
      "/usr/local/Cellar/libpng/1.6.43/lib",
      "sdk/box2d/macos",
      "sdk/lua-5.4.2/macos",
      "sdk/soloud/macos",
    }
    links {
       "box2d",
       "freetype",
       "png",
       "lua",
       "soloud_static",
       "OpenGL.framework",
       "GLUT.framework",
       "Carbon.framework",
       "AudioToolbox.framework",
    }
    xcodecopyframeworks {
      "OpenGL.framework",
      "GLUT.framework",
      "Carbon.framework",
      "AudioToolbox.framework",
    }
    debugdir "."

  configuration {}
