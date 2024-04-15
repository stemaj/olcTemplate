#include "game/src/tools/pathfinding.hpp"
#include "game/src/tools/pathfollower.hpp"
#include <array>
#include <game/src/state/examplePathLevelState.hpp>
#include <game/src/render/examplePathLevelRender.hpp>
#include <game/src/render/levelRender.hpp>
#include <game/coordinates.hpp>
#include <vector>

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
    _path.clear();


    //int x = -1, y = 0;
    //int minDistance = INT_MAX;
    //for (const auto& disPt : _grid)
    //{
    //  auto displayPt = disPt.first;
    //  x++;
    //  if (x >= _gridDimension.x) { x = 0; y++; }
    //  int distance = CO.Distance(displayPt, _obj);
    //  if (distance < minDistance)
    //  {
    //    minDistance = distance;
    //    _obj = {x,y};
    //  }
    //}

    std::vector<PT<int>> nonObstaclePoints;
    for (const auto& d : _grid)
    {
      if (!d.second)
      {
        nonObstaclePoints.push_back(d.first);
      }
    }

    _end = CO.ClosestPoint(nonObstaclePoints, { input.mouseX, input.mouseY });


    Pathfinding f;
    f.SetGrid(_gridDimension.x, _gridDimension.y);
    for (const auto& a : _grid)
    {
      if (a.second)
      {
        f.ToggleObstacle(a.first.x, a.first.y);
      }
    }

    //PT<int> end;
    //int row = 0; int col = 0;
    //for (int y = 0; y < _gridDimension.y; y++)
    //  for (int x = 0; x < _gridDimension.x; x++)
    //    if (_grid[y*_gridDimension.x + x].first == _displayEnd)
    //    {
    //      end = {x,y};
    //      //std::cout << "Geklickt auf x = " << x << " und y = " << y << std::endl;
    //    }

    auto gridPath = f.FindPath(_obj, _end);

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
      _pathFollower.SetSpeed(2);
      _pathFollower.MoveTowardsNextPoint();
    }
  }

  if (_pathFollower.IsMoving() && _obj != _end)
  {
    _pathFollower.MoveTowardsNextPoint();
    _obj = _pathFollower.GetCurrentPosition();
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
    _polygon.push_back({v[0],v[1]});
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

  //for (const auto& a : _relPolygon)
  //{
  //  _displayPolygon.push_back(CO.D({ a[0], a[1] }));
  //}

  for (int y = singleHeight/2; y <= CO.H - (singleHeight/2); y=y+singleHeight)
    for (int x = singleWidth/2; x <= CO.W - (singleWidth/2); x=x+singleWidth)
    {
      _grid.push_back(std::make_pair(PT<int>{x,y}, CO.IsInsidePolygon({ x,y }, CO.VD(_polygon))));
      //std::cout << _grid[_grid.size()-1];
    }
  
  _obj = CO.D(_objSource);
  //std::cout << "count: " << _grid.size() << std::endl;

  //_obj = _grid[_gridDimension.x * _obj.y * _obj.x].first;
  //std::cout << "_displayStart: " << _displayStart;
}
