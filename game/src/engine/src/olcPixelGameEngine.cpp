#if defined(__APPLE__)
#include <cassert>
#endif

// doctest before pge(!)
#ifdef RUN_TESTS
#define DOCTEST_CONFIG_IMPLEMENT
#include <olcTemplate/sdk/doctest-2.4.11/doctest.h>
#endif

#if defined(STEMAJ_DEBUG)
//OpenGL 3.3, otherwise OpenGL 2 renderer
#define PGE_GFX_OPENGL33
#define OLC_PGEX_DEAR_IMGUI_IMPLEMENTATION
#include <olcTemplate/game/src/engine/imgui_impl_pge.h>
#endif

#define OLC_PGEX_TTF
#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>

#define OLC_PGEX_TRANSFORMEDVIEW
#include <olcTemplate/game/src/engine/olcPGEX_TransformedView.h>

#define OLC_PGEX_QUICKGUI
#include <olcTemplate/game/src/engine/olcPGEX_QuickGUI.h>

#define OLC_PGE_APPLICATION
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
