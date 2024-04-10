#include <array>
#include <game/src/state/examplePathLevelState.hpp>
#include <game/src/render/examplePathLevelRender.hpp>
#include <game/src/render/levelRender.hpp>
#include <game/coordinates.hpp>

using namespace stemaj;

ExamplePathLevelState::ExamplePathLevelState() : _render(std::make_unique<ExamplePathLevelRender>())
{
  LoadLevelData();
  InitValues();
}

ExamplePathLevelState::~ExamplePathLevelState()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> ExamplePathLevelState::ExamplePathLevelState::Update(const Input& input)
{
  if (input.leftMouseClicked)
  {
    // select an endpoint
    

  }


  return std::nullopt;
}

Render* ExamplePathLevelState::GetRender()
{
  return _render.get();
}

void ExamplePathLevelState::LoadLevelData()
{
  std::cout << "loading" << std::endl;

  _lua.open_libraries(sol::lib::base, sol::lib::io, sol::lib::math, sol::lib::table);
	try
	{
		_lua.safe_script_file("scripts/examplePathLevel.lua");
	}
	catch (const sol::error& e)
	{
		std::cout << std::string(e.what()) << std::endl;
	}

  auto arr2 = _lua["grid"].get<std::array<int,2>>();
  _grid = { arr2[0], arr2[1] };
  arr2 = _lua["start"].get<std::array<int,2>>();
  _start = { arr2[0], arr2[1] };

  auto arr4 = _lua["colorBackground"].get<std::array<int,4>>();
  _colorBackground = { arr4[0], arr4[1], arr4[2], arr4[3] };
  arr4 = _lua["colorObject"].get<std::array<int,4>>();
  _colorObject = { arr4[0], arr4[1], arr4[2], arr4[3] };
  arr4 = _lua["colorStart"].get<std::array<int,4>>();
  _colorStart = { arr4[0], arr4[1], arr4[2], arr4[3] };
  arr4 = _lua["colorEnd"].get<std::array<int,4>>();
  _colorEnd = { arr4[0], arr4[1], arr4[2], arr4[3] };
  arr4 = _lua["colorPath"].get<std::array<int,4>>();
  _colorPath = { arr4[0], arr4[1], arr4[2], arr4[3] };
  arr4 = _lua["colorPolygon"].get<std::array<int,4>>();
  _colorPolygon = { arr4[0], arr4[1], arr4[2], arr4[3] };
}

void ExamplePathLevelState::SaveLevelData()
{
  std::cout << "saving" << std::endl;
}

void ExamplePathLevelState::InitValues()
{
  int singleWidth = CO.W / _grid.x;
  int singleHeight = CO.W / _grid.y;

  for (int x = singleWidth/2; x < (singleWidth/2) + _grid.x * singleWidth; x=singleWidth)
    for (int y = 0; y < _grid.y; y++)
    {
      _displayGrid.push_back({ 1, 1});
      
    }

 // y*nMapWidth + x





    
}
