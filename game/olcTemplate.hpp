#ifndef __OLC_TEMPLATE_HPP
#define __OLC_TEMPLATE_HPP

#include <game/game.hpp>
#include <game/src/engine/olcPixelGameEngine.h>

namespace stemaj {

class OlcTemplate : public olc::PixelGameEngine
{
public:
  bool OnUserCreate() override;
  bool OnUserUpdate(float fElapsedTime) override;
private:
  Game _game;
};

} // namespace stemaj

#endif //__OLC_TEMPLATE_HPP