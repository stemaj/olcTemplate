#include <game/src/state/exampleWalkLevelState.hpp>
#include <game/src/render/exampleWalkLevelRender.hpp>
#include <game/src/render/levelRender.hpp>
#include <game/animation.hpp>
#include <game/sound.hpp>

olc::utils::Animate2D::AnimationState animationState;

using namespace stemaj;

ExampleWalkLevelState::ExampleWalkLevelState() : _render(std::make_unique<ExampleWalkLevelRender>())
{
  LoadLevelData();
}

ExampleWalkLevelState::~ExampleWalkLevelState()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> ExampleWalkLevelState::ExampleWalkLevelState::Update(
  const Input& input, float fElapsedTime)
{
  auto bikAnim = AN.GetAnimation("bik");

  if (input.aHold)
  {
    if (_currentKind != AnimationKind::IDLE)
    {
      std::cout << "change state to moveleft\n";
      bikAnim.animation.ChangeState(animationState, IDLE);
      _currentKind = AnimationKind::IDLE;
    }
  }
  else
  {
    if (_currentKind != AnimationKind::MOVELEFT)
    {
      std::cout << "change state to idle\n";
      bikAnim.animation.ChangeState(animationState, MOVELEFT);
      _currentKind = AnimationKind::MOVELEFT;
    }
  }

  const auto& frame = bikAnim.animation.GetFrame(animationState);
  bikAnim.animation.UpdateState(animationState, fElapsedTime);

  _drawPos = PT<int>{ 20,20 };
  _decal = frame.GetSourceImage()->Decal();
  _sourceRectPos = {frame.GetSourceRect().pos.x,frame.GetSourceRect().pos.y};
  _sourceRectSize = {frame.GetSourceRect().size.x,frame.GetSourceRect().size.y};
  _scale = PT<float>{0.35f,0.35f};

  // std::cout << "-----\n";
  // std::cout << _sourceRectPos << std::endl;
  // std::cout << _sourceRectSize << std::endl;

  return ChangeLevel(input);
}

Render* ExampleWalkLevelState::GetRender()
{
  return _render.get();
}

void ExampleWalkLevelState::LoadLevelData()
{
  std::cout << "loading" << std::endl;
}

void ExampleWalkLevelState::SaveLevelData()
{
  std::cout << "saving" << std::endl;
}
