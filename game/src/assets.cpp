#include <game/assets.hpp>
#include <filesystem>

#define OLC_IGNORE_VEC2D
#include <game/src/engine/utilities/olcUTIL_Geometry2D.h>
#include <game/src/engine/olcUTIL_Animate2D.h>
#include <game/src/engine/olcPixelGameEngine.h>

using namespace stemaj;
namespace fs = std::filesystem;
using olc::utils::Animate2D::Animation;
using olc::utils::Animate2D::FrameSequence;

Assets& stemaj::Assets::get()
{
  static Assets me;
  return me;
}

void Assets::Load()
{
  auto loadSprite = [&](const std::string& sName, 
    const std::string& sFileName)
  {
    auto s = std::make_unique<olc::Sprite>(sFileName);
    auto d = std::make_unique<olc::Decal>(s.get());
		_sprites[sName] = std::make_pair(std::move(s),std::move(d));
	};

  std::string directory = "./assets/png";
  for (const auto& entry : fs::directory_iterator(directory))
  {
    if (entry.is_regular_file() && entry.path().extension() == ".png")
    {
      loadSprite(entry.path().stem().string(), entry.path().string());
    }
  }
}

olc::Sprite* Assets::Sprite(const std::string& name)
{
  return _sprites[name].first.get();
}

olc::Decal* Assets::Decal(const std::string& name)
{
  return _sprites[name].second.get();
}

Animation<Assets::AnimationKind>* Assets::AnimatedSprite(const std::string& name)
{
  return nullptr;
}

