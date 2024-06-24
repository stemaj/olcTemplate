#ifndef __OLC_TEMPLATE_HPP
#define __OLC_TEMPLATE_HPP

#include <olcTemplate/game/game.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#if defined(STEMAJ_DEBUG)
#include <olcTemplate/game/src/engine/imgui_impl_pge.h>
#endif

namespace stemaj {

class OlcTemplate : public olc::PixelGameEngine
{
public:
  bool OnUserCreate() override;
  bool OnUserUpdate(float fElapsedTime) override;
private:
#if defined(STEMAJ_DEBUG)
  olc::imgui::PGE_ImGUI _pgeImgui;
	int _gameLayer;
#endif
  Game _game;
};

} // namespace stemaj

#endif //__OLC_TEMPLATE_HPP