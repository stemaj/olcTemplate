#include <game/textbox.hpp>
#include <game/fonts.hpp>
#include <sdk/imgui-1.90.4/imgui.h>
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
		offset.y = -_frameboxSize.y * 2;
	}
	else if (_location == TextBoxLocation::LOWERRIGHT)
	{
		offset.x = _frameboxSize.x / 6;
		offset.y = _frameboxSize.y * 2;
	}

	_frameboxUpperLeft = {
		position.x - _frameboxSize.x / 2 + offset.x,
		position.y - _frameboxSize.y / 2 + offset.y};
	_frameboxUpperLeft = { std::clamp(_frameboxUpperLeft.x, 0, CO.W-_frameboxSize.x),
		std::clamp(_frameboxUpperLeft.y, 0, CO.H-_frameboxSize.y) } ;

	_boxUpperLeft = { _frameboxUpperLeft.x + margin,
		_frameboxUpperLeft.y + margin };
	
	_points = {
		PT<int>{2+_frameboxUpperLeft.x+ _frameboxSize.x/2,
			0+_frameboxUpperLeft.y+ _frameboxSize.y/2},
		PT<int>{0+_frameboxUpperLeft.x+ _frameboxSize.x/2,
			2+_frameboxUpperLeft.y+ _frameboxSize.y/2},
		PT<int>{position.x-2, position.y},
		PT<int>{position.x,   position.y-2}};
	
	
	ImGui::Begin("Screen Elements Debug");
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
