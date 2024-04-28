#include "game/fonts.hpp"
#include <algorithm>
#include <game/src/state/exampleScreenElementsLevelState.hpp>
#include <game/src/render/exampleScreenElementsLevelRender.hpp>
#include <game/src/render/levelRender.hpp>
#include <sdk/imgui-1.90.4/imgui.h>
using namespace stemaj;

ExampleScreenElementsLevelState::ExampleScreenElementsLevelState() : _render(std::make_unique<ExampleScreenElementsLevelRender>())
{
  LoadLevelData();
}

ExampleScreenElementsLevelState::~ExampleScreenElementsLevelState()
{
  SaveLevelData();
}

std::optional<std::unique_ptr<State>> ExampleScreenElementsLevelState::ExampleScreenElementsLevelState::Update(
  const Input& input, float fElapsedTime)
{
  _mousePos = {input.mouseX,input.mouseY };
  _textboxes.clear();

  Textbox t;
  auto boxSize = FT.BoxSize(t._text, FT.Font("CutiePatootie-Rgjv", Fontsize::NORMAL));
  auto margin = std::min(boxSize.x, boxSize.y) / 5;
  t._frameboxSize = { boxSize.x + margin*2, boxSize.y + margin*2 };
	
	PT<int> offset = {0,0};
	if (t.location == 1)
	{
		offset.x = -t._frameboxSize.x / 6;
		offset.y = -t._frameboxSize.y * 2;
	}
  
  t._frameboxUpperLeft = { 
		input.mouseX - t._frameboxSize.x / 2 + offset.x,
		input.mouseY - t._frameboxSize.y / 2 + offset.y};
  t._frameboxUpperLeft = { std::clamp(t._frameboxUpperLeft.x, 0, CO.W-t._frameboxSize.x),
    std::clamp(t._frameboxUpperLeft.y, 0, CO.H-t._frameboxSize.y) } ;

  t._boxUpperLeft = { t._frameboxUpperLeft.x + margin, t._frameboxUpperLeft.y + margin };
	
	t._points = {
		PT<int>{1+t._frameboxUpperLeft.x+ t._frameboxSize.x/2,
			0+t._frameboxUpperLeft.y+ t._frameboxSize.y/2},
		PT<int>{0+t._frameboxUpperLeft.x+ t._frameboxSize.x/2,
			1+t._frameboxUpperLeft.y+ t._frameboxSize.y/2},
		PT<int>{_mousePos.x-1, _mousePos.y},
		PT<int>{_mousePos.x,   _mousePos.y-1}};

  _textboxes.push_back(t);

  ImGui::Begin("Screen Elements Debug");
  ImGui::Text("Mouse Position: (%d, %d)", input.mouseX, input.mouseY);
  ImGui::Text("Box Upper Left: (%d, %d)", t._boxUpperLeft.x, t._boxUpperLeft.y);
  ImGui::Text("Framebox Upper Left: (%d, %d)", t._frameboxUpperLeft.x, t._frameboxUpperLeft.y);
  ImGui::Text("Framebox Size: (%d, %d)", t._frameboxSize.x, t._frameboxSize.y);
  ImGui::End();

  return std::nullopt;
}

Render* ExampleScreenElementsLevelState::GetRender()
{
  return _render.get();
}

void ExampleScreenElementsLevelState::LoadLevelData()
{
  std::cout << "loading" << std::endl;
}

void ExampleScreenElementsLevelState::SaveLevelData()
{
  std::cout << "saving" << std::endl;
}
