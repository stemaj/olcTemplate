#include <cstdint>
#include <memory>
#include <olcTemplate/game/gui.hpp>
#include <olcTemplate/game/src/engine/olcPGEX_QuickGUI.h>
#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/input.hpp>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>

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

  std::unique_ptr<olc::QuickGUI::BaseControl> backButton;
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

void Gui::createImageButton(const std::string& name, float x, float y, int fontDelta)
{
  _impl->backButton = std::make_unique<olc::QuickGUI::ImageButton>(
				*_impl->guiManager, *AS.Renderable(name),
				olc::vf2d{x,y}, olc::vf2d{
          (float)AS.Renderable(name)->Sprite()->width + fontDelta,
          (float)AS.Renderable(name)->Sprite()->height + fontDelta});
}

bool Gui::backButtonPressed()
{
  return _impl->backButton->bPressed;
}

void Gui::setText(olc::Font* font, const ButtonAction key, const std::string& value, int r, int g, int b, int alpha)
{
  _impl->_texts[key] = std::make_unique<olc::Renderable>(font->RenderStringToRenderable(
				utf8::utf8to32(std::string(value)), olc::Pixel(r,g,b,alpha)));

}

void Gui::setControl(ButtonAction key, float x, float y, int fontDelta)
{
  _impl->_controls[key] = std::make_unique<olc::QuickGUI::ImageButton>(
				*_impl->guiManager, *_impl->_texts[key],
				olc::vf2d{x,y}, olc::vf2d{
					(float)_impl->_texts[key]->Sprite()->width+fontDelta,
					(float)_impl->_texts[key]->Sprite()->height+fontDelta});

}

ButtonAction Gui::buttonActionPressed() const
{
  for (uint8_t ba = 0; ba < ButtonAction::NO_ACTION; ba++)
  {
    if (_impl->_controls.contains((ButtonAction)ba)
      && _impl->_controls[(ButtonAction)ba]->bPressed)
    {
      return (ButtonAction)ba;
    }
  }
  return ButtonAction::NO_ACTION;
}


void Gui::Update(olc::PixelGameEngine* pge)
{
  _impl->guiManager->Update(pge);
  _impl->guiManager->DrawDecal(pge);
}
