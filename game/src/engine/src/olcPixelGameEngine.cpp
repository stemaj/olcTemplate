#if defined(__APPLE__)
#include <cassert>
#endif

// doctest before pge(!)
#ifdef RUN_TESTS
#define DOCTEST_CONFIG_IMPLEMENT
#include <sdk/doctest-2.4.11/doctest.h>
#endif

//OpenGL 3.3, otherwise OpenGL 2 renderer
#define PGE_GFX_OPENGL33
#define OLC_PGEX_DEAR_IMGUI_IMPLEMENTATION
#include <game/src/engine/imgui_impl_pge.h>

#define OLC_PGE_APPLICATION
#include <game/src/engine/olcPixelGameEngine.h>
