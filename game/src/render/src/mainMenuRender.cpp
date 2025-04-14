#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/fonts.hpp>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>

using namespace stemaj;

void MainMenuRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto m = static_cast<MainMenuState*>(state);

	if (_gui != nullptr)
	{
		_gui->Update(pge);

		m->_buttonHit = _gui->pressedOn();
	}

	if (_gui == nullptr)
	{
		_gui = std::make_shared<Gui>();

    auto col = m->_colors[m->_buttonNormalColorIndex];
		_gui->setColNormal(col[0],col[1],col[2],col[3]);
		col = m->_colors[m->_buttonHoverColorIndex];
		_gui->setColNormal(col[0],col[1],col[2],col[3]);
		col = m->_colors[m->_buttonClickColorIndex];
		_gui->setColNormal(col[0],col[1],col[2],col[3]);

		for (auto& [ba, text] : m->_buttons)
		{
			_gui->prepareTextButton(ba, text.text, m->_font,
				text.fontSize, m->_colors[text.colorListIndex],
				text.pos, text.buttonDelta);
		}

		col = m->_colors[m->_backgroundColorIndex];
		pge->Clear(olc::Pixel(col[0],col[1],col[2],col[3]));
	}

	for (const auto& g : m->_graphics)
	{
		pge->DrawDecal({ (float)g.pos.x, (float)g.pos.y }, 
			AS.Decal(g.file), {g.scale, g.scale});
	}

	//if (!rends.empty()) return;
	for (const auto& t : m->_texts)
	{
		auto col = m->_colors[t.colorListIndex];
		rends.push_back(FT.Renderable(t.text, m->_font, t.fontSize, olc::Pixel(col[0],col[1],col[2],col[3]).n));

		pge->DrawDecal({(float)t.pos.x, (float)t.pos.y}, rends.back()->Decal());
	}
}
