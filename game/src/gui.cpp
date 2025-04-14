#include <olcTemplate/game/src/engine/olcPGEX_QuickGUI.h>
#include <olcTemplate/game/guiElements.hpp>
#include <olcTemplate/game/gui.hpp>
#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#include <olcTemplate/game/fonts.hpp>
#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/input.hpp>
#include <vector>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>
#include <memory>

using namespace stemaj;

Gui::Gui() : guiManager(std::make_shared<olc::QuickGUI::Manager>(false))
{
}

void Gui::setColNormal(int r, int g, int b, int alpha)
{
  guiManager->colNormal = olc::Pixel(r,g,b,alpha);
}

void Gui::setColHover(int r, int g, int b, int alpha)
{
  guiManager->colHover = olc::Pixel(r,g,b,alpha);
}

void Gui::setColClick(int r, int g, int b, int alpha)
{
  guiManager->colClick = olc::Pixel(r,g,b,alpha);
}

ButtonAction Gui::pressedOn()
{
  std::vector<ButtonAction> ret;
  for (const auto& [key, value] : _controls)
  {
    if (value->bPressed)
    {
      return key;
    }
  }
  return ButtonAction::NO_ACTION;
}

void Gui::prepareTextButton(ButtonAction ba, const std::string& text,
    const std::string& fontName, const FontSize fontSize,
    const MainMenuColor color, PT<int> coord, int buttonDelta)
{
  auto font = FT.Font(fontName, fontSize);
  rends.push_back({ba, FT.Renderable(text, fontName, fontSize,
    olc::Pixel(color[0],color[1],color[2],color[3]).n)});
  _texts[ba] = rends.back().second;

  _controls[ba] = std::make_shared<olc::QuickGUI::ImageButton>(
    *guiManager, *_texts[ba],
    olc::vf2d { (float)coord.x, (float)coord.y },
    olc::vf2d { (float)(_texts[ba]->Sprite()->width+buttonDelta),
      (float)(_texts[ba]->Sprite()->height+buttonDelta)});
}

void Gui::prepareImageButton(ButtonAction ba, const std::string& fileName,
  PT<int> coord, int buttonDelta)
{
  _controls[ba] = std::make_shared<olc::QuickGUI::ImageButton>(
				*guiManager, *AS.Renderable(fileName),
				olc::vf2d{ (float)coord.x, (float)coord.y }, olc::vf2d{
          (float)AS.Renderable(fileName)->Sprite()->width + buttonDelta,
          (float)AS.Renderable(fileName)->Sprite()->height + buttonDelta});
}

void Gui::Update(olc::PixelGameEngine* pge)
{
  guiManager->Update(pge);
  guiManager->DrawDecal(pge);
}
