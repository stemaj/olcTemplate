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

  struct SpriteSheet
  {

  };

  auto loadSpriteSheet = [&](const std::string& sName, 
    const std::string& sFileName)
  {
    std::unique_ptr<olc::Renderable> spritesheet;


    // load lua file
    int animations = 5;

    for (int i = 0; i < animations; i++)
    {
      Animation<AnimationKind> animation;

      // count pro animation
      int singlePics = 2;

      for (int j = 0; j < singlePics; j++)
      {
        FrameSequence frameSequence(0.3f);
        
        
        
      }







    }


  };

  directory = "./assets/sheets";
  for (const auto& entry : fs::directory_iterator(directory))
  {
    if (entry.is_regular_file() && entry.path().extension() == ".png")
    {
      loadSpriteSheet(entry.path().stem().string(), entry.path().string());
    }
  }




  //  auto loadSheets = [this]()
  // {
  //   std::unique_ptr<olc::Renderable> spritesheet;
  //   auto charactersFile = DataFile("characters");
  //   int count = charactersFile->GetProperty("count").GetInt();
  //   for (int i = 0; i < count; i++)
  //   {
  //     std::string name = charactersFile->GetIndexedProperty("name", i).GetString();
  //     auto& data = charactersFile->GetProperty(name);
  //     Animation<CharacterState> animation;

  //     std::string sheet = data["sheet"].GetString();

  //     spritesheet.reset(new olc::Renderable());
  //     spritesheet->Load("assets/pics/" + sheet + ".png");

  //     int animationCount = data["animations"].GetInt();
  //     for (int j = 0; j < animationCount; j++)
  //     {
  //       FrameSequence frameSequence(0.3f);
  //       auto& state = data.GetIndexedProperty("animation", j);
  //       auto& name = state.GetProperty("name").GetString();
        
  //       CharacterState e = StateCharacter(name);
  //       int singlePics = state.GetProperty("singlePics").GetInt();
  //       for (int k = 0; k < singlePics; k++)
  //       {
  //           auto& singlePicPos = state.GetIndexedProperty("singlePicPos", k);
  //           olc::vi2d pos = { singlePicPos.GetProperty("x").GetInt() * state.GetProperty("spriteWidth").GetInt(),
  //                             singlePicPos.GetProperty("y").GetInt() * state.GetProperty("spriteHeight").GetInt() };
  //           olc::vi2d imageSize = { state.GetProperty("spriteWidth").GetInt(), 
  //                                   state.GetProperty("spriteHeight").GetInt() };

  //           frameSequence.AddFrame({ spritesheet.get(), { pos, imageSize } });
  //       }
  //       animation.AddState(e, frameSequence);
  //     }
  //     _animatedSprites[name] = std::make_pair(std::make_unique<Animation<CharacterState>>(animation), std::move(spritesheet));
  //   }
  // };
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

