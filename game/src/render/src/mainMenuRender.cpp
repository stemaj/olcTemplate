#include <memory>
#include <olcTemplate/game/src/render/render.hpp>
#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#include "olcTemplate/game/gui.hpp"
#include "olcTemplate/game/input.hpp"
#include "olcTemplate/game/src/engine/olcPGEX_QuickGUI.h"
#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/fonts.hpp>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>

using namespace stemaj;

void MainMenuRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto m = static_cast<MainMenuState*>(state);

	if (_gui == nullptr)
	{
		_gui = std::make_unique<Gui>();

    auto col = m->_colors[m->_buttonNormalColorIndex];
		_gui->setColNormal(col[0],col[1],col[2],col[3]);
		col = m->_colors[m->_buttonHoverColorIndex];
		_gui->setColNormal(col[0],col[1],col[2],col[3]);
		col = m->_colors[m->_buttonClickColorIndex];
		_gui->setColNormal(col[0],col[1],col[2],col[3]);

		for (auto& [key, value] : m->_buttons)
		{
			auto col = m->_colors[value.colorListIndex];
			auto font = FT.Font(m->_font, value.fontSize);
			
			_gui->setText(font, key, value.text, col[0],col[1],col[2],col[3]);

			_gui->setControl(key, (float)value.pos.x, (float)value.pos.y, 10);
		}

		col = m->_colors[m->_backgroundColorIndex];
		pge->Clear(olc::Pixel(col[0],col[1],col[2],col[3]));
	}

	for (const auto& g : m->_graphics)
	{
		pge->DrawDecal({ (float)g.pos.x, (float)g.pos.y }, 
			AS.Decal(g.file), {g.scale, g.scale});
	}

	for (const auto& t : m->_texts)
	{
		olc::Decal* r = nullptr;
		auto col = m->_colors[t.colorListIndex];
		auto font = FT.Font(m->_font, t.fontSize);
		r = font->RenderStringToDecal(
			utf8::utf8to32(std::string(t.text)),
			olc::Pixel(col[0],col[1],col[2],col[3]));
		pge->DrawDecal({(float)t.pos.x, (float)t.pos.y}, r);
	}

	_gui->Update(pge);

	if (_gui->buttonActionPressed(START_GAME)) m->_buttonHit = START_GAME;
	else if (_gui->buttonActionPressed(OPTION_1)) m->_buttonHit = OPTION_1;
	else if (_gui->buttonActionPressed(OPTION_2)) m->_buttonHit = OPTION_2;
	else if (_gui->buttonActionPressed(OPTION_3)) m->_buttonHit = OPTION_3;
	else if (_gui->buttonActionPressed(OPTION_4)) m->_buttonHit = OPTION_4;
	else if (_gui->buttonActionPressed(OPTION_5)) m->_buttonHit = OPTION_5;
	else if (_gui->buttonActionPressed(OPTION_6)) m->_buttonHit = OPTION_6;
	else m->_buttonHit = NO_ACTION;
}
