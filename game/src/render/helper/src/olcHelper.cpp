#include <cmath>
#include <olcTemplate/game/src/render/helper/olcHelper.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <numbers>

using namespace stemaj;

void OlcHelper::FillCircleDecal(olc::PixelGameEngine* pge, const int radius,
  const PT<int> position, const olc::Pixel& color)
{
  const int segments = 32;
  std::vector<olc::vf2d> points;
  for (int i = 0; i < segments; i++)
    points.push_back(olc::vf2d(
    position.x + radius * cosf(i * (2 * std::numbers::pi / (float)segments)),
    position.y + radius * sinf(i * (2 * std::numbers::pi / (float)segments))));

  std::vector<olc::vf2d> uvs;
  uvs.resize(points.size());
  pge->DrawPolygonDecal(nullptr, points, uvs, color);
}

void OlcHelper::DrawCircleDecal(olc::PixelGameEngine* pge, const int radius,
  const PT<int> position, const olc::Pixel& color)
{
  if (radius < 1)
      return;

  int x = radius;
  int y = 0;
  int decisionOver2 = 1 - x;

  olc::vf2d prevPoint = olc::vi2d(position.x,position.y) + olc::vi2d(x, y);

  while (y <= x)
  {
    olc::vf2d points[8] = {
      olc::vi2d(position.x,position.y) + olc::vi2d(x, y),
      olc::vi2d(position.x,position.y) + olc::vi2d(y, x),
      olc::vi2d(position.x,position.y) + olc::vi2d(-x, y),
      olc::vi2d(position.x,position.y) + olc::vi2d(-y, x),
      olc::vi2d(position.x,position.y) + olc::vi2d(-x, -y),
      olc::vi2d(position.x,position.y) + olc::vi2d(-y, -x),
      olc::vi2d(position.x,position.y) + olc::vi2d(x, -y),
      olc::vi2d(position.x,position.y) + olc::vi2d(y, -x)
    };

    for (int i = 0; i < 8; i++)
    {
      pge->DrawLineDecal(prevPoint, points[i], color);
      prevPoint = points[i];
    }

    y++;
    if (decisionOver2 <= 0)
    {
      decisionOver2 += 2 * y + 1;
    }
    else
    {
      x--;
      decisionOver2 += 2 * (y - x) + 1;
    }
  }
}

void OlcHelper::CreateOneColorDecal(olc::Renderable* r, const olc::Pixel& color)
{
  r->Create(1,1);
  r->Sprite()->SetPixel({0,0},color);
  r->Decal()->Update();
}

