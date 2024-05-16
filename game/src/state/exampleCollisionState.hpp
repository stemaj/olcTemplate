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
  float SCALE = 0.0f;

  int _velocityIterations = 0;
  int _positionIterations = 0;

  float _gravityY = 0.0f;
  std::unique_ptr<b2World> _world;

  PT<float> _groundCenter = {0.f,0.f};
  PT<float> _groundSize = {0.f,0.f};
  float _groundAngle = 0.0f;
  int _groundType = 0;
  float _groundDensity = 0;

  PT<float> _circleCenter = {0.f,0.f};
  float _circleRadius = 0.0f;
  int _circleType = 0;
  float _circleDensity = 0;

  PT<float> _rectCenter = {0.f,0.f};
  PT<float> _rectSize = {0.f,0.f};
  float _rectAngle = 0.0f;
  int _rectType = 0;
  float _rectDensity = 0;

  PT<float> _triCenter = {0.f,0.f};
  std::array<PT<float>,4> _triPolygon;
  int _triType = 0;
  float _triDensity = 0;

  b2Body* _triBodyPtr = nullptr;

private:
  void LoadLevelData() override;
  void SaveLevelData() override;

  void InitValues();
  sol::state _lua;
  std::unique_ptr<ExampleCollisionRender> _render;

  friend class ExampleCollisionRender;
};

} // namespace stemaj

#endif // __EXAMPLECOLLISIONSTATE_HPP

