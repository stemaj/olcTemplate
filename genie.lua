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
    flags { "Symbols", "CppLatest" }
  configuration "Test"
    targetdir (path.join(ROOT_DIR,"solution/bin/Test"))
    objdir (path.join(ROOT_DIR,"solution/obj"))
    defines { "RUN_TESTS" }
    flags { "Symbols", "CppLatest" }
  configuration "Release"
    targetdir (path.join(ROOT_DIR,"solution/bin/Release"))
    objdir (path.join(ROOT_DIR,"solution/obj"))
    flags { "OptimizeSpeed", "CppLatest" }
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
    path.join(ROOT_DIR,"src/**.h"),
    path.join(ROOT_DIR,"src/**.hpp"),
    path.join(ROOT_DIR,"src/**.cpp"),
    --path.join(ROOT_DIR,"assets/**.txt"),
  }
  includedirs {
    ".",
    --"soloud/include",
  }

  configuration "windows"
    includedirs {
      --"soloud/include",
      --"freetype-windows-binaries-2.13.1/include",
    }
    libdirs {
      --"freetype-windows-binaries-2.13.1/release static/vs2015-2022/win64",
      --"soloud/lib/windows",
    }
    links {
      --"freetype",
      --"soloud_static_x64"
    }

  configuration "linux"
    includedirs {
      "/usr/include",
      --"/usr/include/freetype2",
    }
    libdirs {
      "/usr/lib",
      --"soloud/lib/linux/Release",
    }
    links {
      --"freetype",
       "X11",
       "GL",
       "pthread",
       "png",
       "stdc++fs",
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
      --"../../../../opt/homebrew/include/freetype2",
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
