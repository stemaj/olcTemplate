#ifndef __LOADINGRENDER_HPP
#define __LOADINGRENDER_HPP

#include <olcTemplate/game/src/render/render.hpp>
#include <olcTemplate/game/src/render/loadingRender.hpp>

namespace stemaj {

class LoadingRender : public Render
{
public:
  void DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state) override;
  void Fade(olc::PixelGameEngine* pge, State* state) override final;
};

} // namespace stemaj

#endif //__LOADINGRENDER_HPP