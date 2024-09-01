#ifndef __MAINMENURENDER_HPP
#define __MAINMENURENDER_HPP

#include <olcTemplate/game/src/render/render.hpp>
#include <olcTemplate/game/input.hpp>
#include <memory>
#include <unordered_map>

namespace olc {
  class Renderable;
  namespace QuickGUI {
    class BaseControl;
  }
}

namespace stemaj {

using RenderedText = std::unique_ptr<olc::Renderable>;
using RenderedControl = std::unique_ptr<olc::QuickGUI::BaseControl>;


class MainMenuRender : public Render
{
public:
	void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
  void Fade(olc::PixelGameEngine* pge, State* state) override final {}

private:
	std::unordered_map<ButtonAction, RenderedText> _texts;
	std::unordered_map<ButtonAction, RenderedControl> _controls;
};

} // namespace stemaj

#endif //__MAINMENURENDER_HPP
