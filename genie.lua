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
    --path.join(ROOT_DIR,"assets/**.txt"),
  }
  includedirs {
    ".",
    --"soloud/include",
  }

  configuration "windows"
    includedirs {
      "sdk/imgui-1.90.4",
      "sdk/imgui-1.90.4/backends",
      "sdk/sol2-3.3.0",
      "sdk/lua-5.4.2/include",
      --"soloud/include",
      "sdk/freetype-2.13.1/include",
    }
    libdirs {
      "sdk/lua-5.4.2/windows",
      "sdk/freetype-2.13.1/windows",
      --"soloud/lib/windows",
    }
    links {
      "lua54",
      "freetype",
      --"soloud_static_x64"
    }
    debugdir ".."

  configuration "linux"
    includedirs {
      "/usr/include",
      "sdk/imgui-1.90.4",
      "sdk/imgui-1.90.4/backends",
      "sdk/sol2-3.3.0",
      "sdk/lua-5.4.2/include",
      "sdk/freetype-2.13.1/include",
    }
    libdirs {
      "/usr/lib",
      "sdk/lua-5.4.2/linux",
      --"soloud/lib/linux/Release",
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
       --"soloud_static",
       --"asound"
    }
    debugdir "."
 
  configuration "macosx"
    buildoptions_cpp {
      "-Wall",
    }
    includedirs {
      "../../../../opt/homebrew/include",
      "sdk/imgui-1.90.4",
      "sdk/imgui-1.90.4/backends",
      "sdk/sol2-3.3.0",
      "sdk/lua-5.4.2/include",
      "../../../../opt/homebrew/include/freetype2",
    }
    libdirs {
      "../../../../opt/homebrew/lib",
      --"soloud/lib/macos",
    }
    links {
       "freetype",
       "png",
       --"soloud_static",
       "OpenGL.framework",
       "GLUT.framework",
       "Carbon.framework",
       --"AudioToolbox.framework",
    }
    xcodecopyframeworks {
      "OpenGL.framework",
      "GLUT.framework",
      "Carbon.framework",
      --"AudioToolbox.framework",
    }
    debugdir "."

  configuration {}
