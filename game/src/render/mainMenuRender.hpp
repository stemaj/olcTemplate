#ifndef __MAINMENURENDER_HPP
#define __MAINMENURENDER_HPP

#include <olcTemplate/game/src/render/render.hpp>
#include <olcTemplate/game/src/engine/olcPGEX_QuickGUI.h>
#include <memory>


namespace stemaj {

class MainMenuRender : public Render
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
  void Fade(olc::PixelGameEngine* pge, State* state) override final {}

private:
  std::unique_ptr<olc::QuickGUI::Manager> _guiManager;

  std::unique_ptr<olc::Renderable> _newGameText;
  std::unique_ptr<olc::QuickGUI::ImageButton> _newGameButton;
};

} // namespace stemaj

#endif //__MAINMENURENDER_HPP