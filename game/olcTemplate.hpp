#ifndef __OLC_TEMPLATE_HPP
#define __OLC_TEMPLATE_HPP

#include <game/src/engine/olcPixelGameEngine.h>

namespace stemaj {

class OlcTemplate : public olc::PixelGameEngine
{
public:
  bool OnUserCreate() override;
  bool OnUserUpdate(float fElapsedTime) override;
};

}

#endif //__OLC_TEMPLATE_HPP