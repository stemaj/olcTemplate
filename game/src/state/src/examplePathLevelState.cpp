#include "game/src/tools/pathfinding.hpp"
#include "game/src/tools/pathfollower.hpp"
#include <array>
#include <game/src/state/examplePathLevelState.hpp>
#include <game/src/render/examplePathLevelRender.hpp>
#include <game/src/render/levelRender.hpp>
#include <game/coordinates.hpp>
#include <vector>
#include <sdk/imgui-1.90.4/imgui.h>

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

std::optional<std::unique_ptr<State>> ExamplePathLevelState::ExamplePathLevelState::Update(
  const Input& input, float fElapsedTime)
{
  if (input.leftMouseClicked)
  {
    _path.clear();
    Pathfinding f;
    f.SetGrid(_gridDimension.x, _gridDimension.y);

    int x = -1, y = 0;
    for (auto& gp : _grid)
    {
      x++;
      if (x >= _gridDimension.x) { x = 0; y++; }
      if (gp.second)
      {
        f.ToggleObstacle(x,y);
      }
    }

    std::vector<PT<int>> nonObstaclePoints;
    for (const auto& d : _grid)
    {
      if (!d.second)
      {
        nonObstaclePoints.push_back(d.first);
      }
    }
    _end = CO.ClosestPoint(nonObstaclePoints, { input.mouseX, input.mouseY });

    auto objGrid = f.ToGridPoint(_gridDimension, {CO.W,CO.H}, _obj);
    auto endGrid = f.ToGridPoint(_gridDimension, {CO.W,CO.H}, _end);
    auto gridPath = f.FindPath(objGrid, endGrid);

    int singleWidth = CO.W / _gridDimension.x;
    int singleHeight = CO.H / _gridDimension.y;

    for (const auto& pt : gridPath)
    {
      _path.push_back( PT<int>{ singleWidth / 2 + pt.x * singleWidth,
        singleHeight / 2 + pt.y * singleHeight } );
    }

    if (!_path.empty())
    {
      _pathFollower.SetPath(_path);
      _pathFollower.SetSpeed(_speed * fElapsedTime);
      _pathFollower.MoveTowardsNextPoint();
    }
  }

  if (_pathFollower.IsMoving() && _obj != _end)
  {
    _pathFollower.MoveTowardsNextPoint();
    _obj = _pathFollower.GetCurrentPosition();
  }

  ImGui::Begin("ExamplePathLevel Debug");
  ImGui::Text("Mouse Position: (%d, %d)", input.mouseX, input.mouseY);
  ImGui::Text("Endpunkt:  (%d, %d)", _end.x, _end.y);
  ImGui::Text("Objekt:  (%d, %d)", _obj.x, _obj.y);
  ImGui::Separator();
  if (ImGui::BeginListBox("Path", ImVec2(0, _path.size() * 25)))
  {
    for (const auto& point : _path)
      ImGui::Text("(%d, %d)", point.x, point.y);
    ImGui::EndListBox();
  }
  ImGui::End();

  return ChangeLevel(input);
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
  _gridDimension = { arr2[0], arr2[1] };
  auto farr2 = _lua["start"].get<std::array<float,2>>();
  _objSource = { farr2[0], farr2[1] };

  auto arr4 = _lua["colorBackground"].get<std::array<uint8_t,4>>();
  _colorBackground = { arr4[0], arr4[1], arr4[2], arr4[3] };
  arr4 = _lua["colorObject"].get<std::array<uint8_t,4>>();
  _colorObject = { arr4[0], arr4[1], arr4[2], arr4[3] };
  arr4 = _lua["colorStart"].get<std::array<uint8_t,4>>();
  _colorStart = { arr4[0], arr4[1], arr4[2], arr4[3] };
  arr4 = _lua["colorEnd"].get<std::array<uint8_t,4>>();
  _colorEnd = { arr4[0], arr4[1], arr4[2], arr4[3] };
  arr4 = _lua["colorPath"].get<std::array<uint8_t,4>>();
  _colorPath = { arr4[0], arr4[1], arr4[2], arr4[3] };
  arr4 = _lua["colorPolygon"].get<std::array<uint8_t,4>>();
  _colorPolygon = { arr4[0], arr4[1], arr4[2], arr4[3] };

  auto vec = _lua["polygon"].get<std::vector<std::array<float,2>>>();
  for (const auto& v : vec)
  {
    _polygonSource.push_back({v[0],v[1]});
  }
}

void ExamplePathLevelState::SaveLevelData()
{
  std::cout << "saving" << std::endl;
}

void ExamplePathLevelState::InitValues()
{
  int singleWidth = CO.W / _gridDimension.x;
  int singleHeight = CO.H / _gridDimension.y;
  for (int y = singleHeight/2; y <= CO.H - (singleHeight/2); y=y+singleHeight)
    for (int x = singleWidth/2; x <= CO.W - (singleWidth/2); x=x+singleWidth)
    {
      _grid.push_back(std::make_pair(PT<int>{x,y},
        CO.IsInsidePolygon({ x,y }, CO.VD(_polygonSource))));
    }
  
  _obj = CO.D(_objSource);
}
