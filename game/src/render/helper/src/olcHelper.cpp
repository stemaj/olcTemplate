#include <cmath>
#include <olcTemplate/game/src/render/helper/olcHelper.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;

void OlcHelper::FillCircleDecal(olc::PixelGameEngine* pge, const int radius, const PT<int> position, const olc::Pixel& color)
{
  const int segments = 32;
  std::vector<olc::vf2d> points;
  for (int i = 0; i < segments; i++)
    points.push_back(olc::vf2d(position.x + radius * cos(i * (2 * M_PI / segments)), 
        position.y + radius * sin(i * (2 * M_PI / segments))));

  std::vector<olc::vf2d> uvs;
  uvs.resize(points.size());
  pge->DrawPolygonDecal(nullptr, points, uvs, color);
}

void OlcHelper::CreateOneColorDecal(olc::Renderable* r, const olc::Pixel& color)
{
  r->Create(1,1);
  r->Sprite()->SetPixel({0,0},color);
  r->Decal()->Update();
}

