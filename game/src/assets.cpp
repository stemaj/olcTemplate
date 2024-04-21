#include <cstdint>
#include <game/assets.hpp>
#include <filesystem>
#include <memory>

#define OLC_IGNORE_VEC2D
#include <game/src/engine/utilities/olcUTIL_Geometry2D.h>
#include <game/src/engine/olcUTIL_Animate2D.h>
#include <game/src/engine/olcPixelGameEngine.h>

#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>

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

  auto loadSpriteSheet = [&](const std::string& sName, 
    const std::string& sFileName)
  {
    auto spritesheet = std::make_unique<olc::Renderable>();
    spritesheet->Load(sFileName);

    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
    try
    {
      lua.safe_script_file("assets/sheets/" + sName + ".lua");
    }
    catch (const sol::error& e)
    {
      std::cout << std::string(e.what()) << std::endl;
    }


    // Extrahiere Werte aus Lua
    AnimationContainer container;
    container.spriteWidth = lua["spriteWidth"];
    container.spriteHeight = lua["spriteHeight"];
    container.ox = lua["ox"];
    container.oy = lua["oy"];
    for (int i = 0; i < AnimationKind::COUNT; i++)
    {
      sol::table value = lua["details"][i];
      auto e = static_cast<AnimationKind>(i);
      for (const auto& kvp : value)
      {
        container.details[e].singlePics = std::make_pair<int, int>(kvp.first.as<int>(), kvp.second.as<int>());
    


    if (lua["moveright"]) {
      x = AnimationKind::MOVERIGHT;
      // Lade die Werte in y
      sol::table moverightTable = lua["moveright"];
      for (auto& pair : moverightTable) {
        sol::object key = pair.first;
        sol::object value = pair.second;
        if (key.is<int>() && value.is<sol::table>()) {
          float first = value.as<sol::table>()[1];
          float second = value.as<sol::table>()[2];
          y.emplace_back(first, second);
        }
      }
    }


// -- 	std::cout << "[CPP S9] vecPlayers.size() = " << vecPlayers.size() << "\n";
// -- 	lua["CreatePlayer2"](13);
// -- 	std::cout << "[CPP S9] vecPlayers.size() = " << vecPlayers.size() << "\n";

// -- 	for (const auto& p : vecPlayers)
// -- 		std::cout << "[CPP S9] player1 = " << p.title << " " << p.name << " of "
// -- 		<< p.family << " [Lvl: " << p.level << "]\n";







  //   auto arr2 = _lua["grid"].get<std::array<int,2>>();
  // _gridDimension = { arr2[0], arr2[1] };
  // auto farr2 = _lua["start"].get<std::array<float,2>>();
  // _objSource = { farr2[0], farr2[1] };


  //   // load lua file
  //   int animations = 5;
  //   Animation<AnimationKind> animation;

  //   for (int i = 0; i < animations; i++)
  //   {
      
  //     AnimationKind e = IDLE;

  //     // count pro animation
  //     int singlePics = 2;

  //     for (int j = 0; j < singlePics; j++)
  //     {
  //       FrameSequence frameSequence(0.3f);

  //       //pos = x * sprWidht , y * speHeit;
  //       //imaessizr = { sprWif, sprHe }

        
  //       frameSequence.AddFrame({ spritesheet.get(), { pos, imageSize } });
        
        
  //       animation.AddState(e, frameSequence);
        
  //     }
  //   }
  //   _animatedSprites[name] = std::make_pair(std::make_unique<Animation<AnimationKind>>(animation), std::move(spritesheet));


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

AnimationContainer* Assets::AnimatedSprite(const std::string& name)
{
  return nullptr;
}

