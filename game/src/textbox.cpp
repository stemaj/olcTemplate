#include <olcTemplate/game/textbox.hpp>
#include <olcTemplate/game/fonts.hpp>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>
#include <algorithm>

using namespace stemaj;

TextBox::TextBox(const std::string& text,
								 const PT<int> position,
								 const TextBoxLocation location,
									const std::string& fontName,
									const FontSize fontSize) : _text(text), _location(location), _fontName(fontName), _fontSize(fontSize)
{
	auto boxSize = FT.BoxSize(_text, fontName, fontSize);
	auto margin = std::min(boxSize.x, boxSize.y) / 5;
	_frameboxSize = { boxSize.x + margin*2, boxSize.y + margin*2 };
	
	PT<int> offset = {0,0};
	if (_location == TextBoxLocation::UPPERLEFT)
	{
		offset.x = -_frameboxSize.x / 4;
		offset.y = -_frameboxSize.y * 1.5;
	}
	else if (_location == TextBoxLocation::LOWERRIGHT)
	{
		offset.x = _frameboxSize.x / 8;
		offset.y = _frameboxSize.y * 1.5;
	}

	_frameboxUpperLeft = {
		position.x - _frameboxSize.x / 2 + offset.x,
		position.y - _frameboxSize.y / 2 + offset.y};
	_frameboxUpperLeft = { std::clamp(_frameboxUpperLeft.x, 0, CO.W-_frameboxSize.x),
		std::clamp(_frameboxUpperLeft.y, 0, CO.H-_frameboxSize.y) } ;

	_boxUpperLeft = { _frameboxUpperLeft.x + margin,
		_frameboxUpperLeft.y + margin };

	_lineAnchorPoints[0] = { _frameboxUpperLeft.x + _frameboxSize.x / 2 - std::max(1,_frameboxSize.x / 100), 
													 _frameboxUpperLeft.y + _frameboxSize.y / 2 };
	_lineAnchorPoints[1] = { _frameboxUpperLeft.x + _frameboxSize.x / 2 + std::max(1,_frameboxSize.x / 100), 
													 _frameboxUpperLeft.y + _frameboxSize.y / 2 };
	
	ImGui::Begin("Screen Elements Debug");
	for (int i = 0; i < 2; i++)
		ImGui::Text("LineAnchorPoint (%d): (%d, %d)", i, _lineAnchorPoints[i].x, _lineAnchorPoints[i].y);
		ImGui::Text("Text: (%s)", _text.c_str());
		ImGui::Text("Mouse Position: (%d, %d)", position.x, position.y);
		ImGui::Text("Box Upper Left: (%d, %d)", _boxUpperLeft.x, _boxUpperLeft.y);
		ImGui::Text("Framebox Upper Left: (%d, %d)",
								_frameboxUpperLeft.x, _frameboxUpperLeft.y);
		ImGui::Text("Framebox Size: (%d, %d)", _frameboxSize.x, _frameboxSize.y);
	ImGui::End();
}

olc::Decal* Decal()
{
	return nullptr;
}
