#include <olcTemplate/game/src/render/render.hpp>
#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#include "olcTemplate/game/src/engine/olcPGEX_QuickGUI.h"
#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/fonts.hpp>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>

using namespace stemaj;

void MainMenuRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto m = static_cast<MainMenuState*>(state);

  if (m->_guiManager == nullptr)
  {
    m->_guiManager = std::make_unique<olc::QuickGUI::Manager>(false);

    for (auto& [key, value] : m->_buttons)
    {
      if (key == MainMenuState::START_GAME)
      {
        auto col = m->_colors[value.colorListIndex];
        auto font = FT.Font(m->_font, value.fontSize);

        _newGameText = std::make_unique<olc::Renderable>(font->RenderStringToRenderable(
          utf8::utf8to32(std::string(value.text)),
          olc::Pixel(col[0],col[1],col[2],col[3])));

        _newGameButton = std::make_unique<olc::QuickGUI::ImageButton>(
          *m->_guiManager, *_newGameText, 
          olc::vf2d{(float)value.pos.x,(float)value.pos.y}, olc::vf2d{
            (float)_newGameText->Sprite()->width+10,
            (float)_newGameText->Sprite()->height+10});
      }
    }
  }

  pge->Clear(olc::WHITE);

  for (const auto& g : m->_graphics)
  {
    pge->DrawDecal({ (float)g.pos.x, (float)g.pos.y }, 
      AS.Decal(g.file), {g.scale, g.scale});
  }

  for (const auto& t : m->_texts)
  {
    olc::Decal* r = nullptr;
    auto col = m->_colors[t.colorListIndex];
    auto font = FT.Font(m->_font, t.fontSize);
    r = font->RenderStringToDecal(
      utf8::utf8to32(std::string(t.text)),
      olc::Pixel(col[0],col[1],col[2],col[3]));
    pge->DrawDecal({(float)t.pos.x, (float)t.pos.y}, r);
  }

  m->_guiManager->colNormal = olc::Pixel(255,207,131);
  m->_guiManager->colHover = olc::WHITE;
  m->_guiManager->colClick = olc::WHITE;
 
  m->_guiManager->Update(pge);
  m->_guiManager->DrawDecal(pge);

  if (_newGameButton && _newGameButton->bPressed)
  {
    m->_startGame = true;
  }
}
