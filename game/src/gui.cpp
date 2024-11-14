#include <olcTemplate/game/guiElements.hpp>
#include <olcTemplate/game/gui.hpp>
#include <olcTemplate/game/src/engine/olcPGEX_QuickGUI.h>
#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#include <olcTemplate/game/fonts.hpp>
#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/input.hpp>
#include <vector>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>
#include <memory>

using namespace stemaj;

using RenderedText = std::unique_ptr<olc::Renderable>;
using RenderedControl = std::unique_ptr<olc::QuickGUI::BaseControl>;

class stemaj::Gui::GuiImpl
{
public:
  GuiImpl()
  {
    guiManager.reset(new olc::QuickGUI::Manager(false));
  }
  ~GuiImpl() {}

  std::unordered_map<ButtonAction, RenderedText> _texts;
  std::unordered_map<ButtonAction, RenderedControl> _controls;

  std::unique_ptr<olc::QuickGUI::Manager> guiManager;
};

Gui::Gui() : _impl(std::make_unique<GuiImpl>())
{
}

Gui::~Gui()
{
}

void Gui::setColNormal(int r, int g, int b, int alpha)
{
  _impl->guiManager->colNormal = olc::Pixel(r,g,b,alpha);
}

void Gui::setColHover(int r, int g, int b, int alpha)
{
  _impl->guiManager->colHover = olc::Pixel(r,g,b,alpha);
}

void Gui::setColClick(int r, int g, int b, int alpha)
{
  _impl->guiManager->colClick = olc::Pixel(r,g,b,alpha);
}

ButtonAction Gui::pressedOn()
{
  std::vector<ButtonAction> ret;
  for (const auto& [key, value] : _impl->_controls)
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
  _impl->_texts[ba] = std::make_unique<olc::Renderable>(font->RenderStringToRenderable(
				utf8::utf8to32(std::string(text)),
        olc::Pixel(color[0],color[1],color[2],color[3])));

  _impl->_controls[ba] = std::make_unique<olc::QuickGUI::ImageButton>(
    *_impl->guiManager, *_impl->_texts[ba],
    olc::vf2d { (float)coord.x, (float)coord.y },
    olc::vf2d { (float)(_impl->_texts[ba]->Sprite()->width+buttonDelta),
      (float)(_impl->_texts[ba]->Sprite()->height+buttonDelta)});
}

void Gui::prepareImageButton(ButtonAction ba, const std::string& fileName,
  PT<int> coord, int buttonDelta)
{
  _impl->_controls[ba] = std::make_unique<olc::QuickGUI::ImageButton>(
				*_impl->guiManager, *AS.Renderable(fileName),
				olc::vf2d{ (float)coord.x, (float)coord.y }, olc::vf2d{
          (float)AS.Renderable(fileName)->Sprite()->width + buttonDelta,
          (float)AS.Renderable(fileName)->Sprite()->height + buttonDelta});
}

void Gui::Update(olc::PixelGameEngine* pge)
{
  _impl->guiManager->Update(pge);
  _impl->guiManager->DrawDecal(pge);
}
