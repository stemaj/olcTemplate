#ifndef __OLC_TEMPLATE_HPP
#define __OLC_TEMPLATE_HPP

#include <olcTemplate/game/game.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/src/engine/imgui_impl_pge.h>

namespace stemaj {

class OlcTemplate : public olc::PixelGameEngine
{
public:
  bool OnUserCreate() override;
  bool OnUserUpdate(float fElapsedTime) override;
private:
  olc::imgui::PGE_ImGUI _pgeImgui;
	int _gameLayer;
  Game _game;
};

} // namespace stemaj

#endif //__OLC_TEMPLATE_HPP