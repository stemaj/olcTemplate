#ifndef __EXAMPLECOLLISIONSTATE_HPP
#define __EXAMPLECOLLISIONSTATE_HPP

#include <cstdint>
#include <game/src/state/levelState.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>

class b2World;
class b2BodyDef;
class b2Body;

namespace stemaj {

class ExampleCollisionRender;

class ExampleCollisionState : public LevelState
{
public:
  explicit ExampleCollisionState();
  virtual ~ExampleCollisionState();
  std::optional<std::unique_ptr<State>> Update(const Input& input, float fElapsedTime) override;
  Render* GetRender() override;
  
  // Define a conversion factor between Box2D units and screen pixels
  const float SCALE = 30.0f;
  
  std::unique_ptr<b2BodyDef> thingDef;
  b2Body* thingBody;

  std::unique_ptr<b2World> _world;

private:
  void LoadLevelData() override;
  void SaveLevelData() override;
  sol::state _lua;
  std::unique_ptr<ExampleCollisionRender> _render;

  friend class ExampleCollisionRender;
};

} // namespace stemaj

#endif // __EXAMPLECOLLISIONSTATE_HPP

