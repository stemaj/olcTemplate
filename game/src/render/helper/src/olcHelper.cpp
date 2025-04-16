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

  olc::vf2d center = { (float)position.x, (float)position.y };
  const int segments = 16;
  const float angleStep = 2.0f * 3.14159265f / segments;

  for (int i = 0; i < segments; ++i)
  {
    float angle1 = i * angleStep;
    float angle2 = (i + 1) * angleStep;

    olc::vf2d point1 = center + olc::vf2d(std::cos(angle1), std::sin(angle1)) * radius;
    olc::vf2d point2 = center + olc::vf2d(std::cos(angle2), std::sin(angle2)) * radius;

    pge->DrawLineDecal(point1, point2, color);
  }
}

void OlcHelper::CreateOneColorDecal(olc::Renderable* r, const olc::Pixel& color)
{
  r->Create(1,1);
  r->Sprite()->SetPixel({0,0},color);
  r->Decal()->Update();
}

