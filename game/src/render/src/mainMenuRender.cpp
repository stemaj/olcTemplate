#include <olcTemplate/game/src/render/render.hpp>
#include <olcTemplate/game/src/render/mainMenuRender.hpp>
#include <olcTemplate/game/src/state/mainMenuState.hpp>
#include <olcTemplate/game/src/engine/olcPixelGameEngine.h>
#include <olcTemplate/game/src/engine/olcPGEX_TTF.h>
#include "olcTemplate/game/src/engine/olcPGEX_QuickGUI.h"
#include <olcTemplate/game/assets.hpp>
#include <olcTemplate/game/fonts.hpp>
#define UTF_CPP_CPLUSPLUS 202002L
#include <olcTemplate/sdk/utfcpp/utf8.h>

using namespace stemaj;

void MainMenuRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto m = static_cast<MainMenuState*>(state);
	
	if (m->_guiManager == nullptr)
	{
		m->_guiManager = std::make_unique<olc::QuickGUI::Manager>(false);

    	auto col = m->_colors[m->_buttonNormalColorIndex];
		m->_guiManager->colNormal = olc::Pixel(col[0],col[1],col[2],col[3]);
		col = m->_colors[m->_buttonHoverColorIndex];
		m->_guiManager->colHover = olc::Pixel(col[0],col[1],col[2],col[3]);
		col = m->_colors[m->_buttonClickColorIndex];
		m->_guiManager->colClick = olc::Pixel(col[0],col[1],col[2],col[3]);


		for (auto& [key, value] : m->_buttons)
		{
			auto col = m->_colors[value.colorListIndex];
			auto font = FT.Font(m->_font, value.fontSize);
			
			_texts[key] = std::make_unique<olc::Renderable>(font->RenderStringToRenderable(
				utf8::utf8to32(std::string(value.text)), olc::Pixel(col[0],col[1],col[2],col[3])));

			_controls[key] =
			std::make_unique<olc::QuickGUI::ImageButton>(
				*m->_guiManager, *_texts[key],
				olc::vf2d{(float)value.pos.x,(float)value.pos.y}, olc::vf2d{
					(float)_texts[key]->Sprite()->width+10,
					(float)_texts[key]->Sprite()->height+10});
		}
  }

  auto col = m->_colors[m->_backgroundColorIndex];
  pge->Clear(olc::Pixel(col[0],col[1],col[2],col[3]));

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

 
  m->_guiManager->Update(pge);
  m->_guiManager->DrawDecal(pge);
	
	for (const auto& [key,value] : _controls)
	{
		switch (key) {
			case START_GAME:
				if (value->bPressed)
					m->_buttonHit = START_GAME;
				break;
			case OPTION_1:
				if (value->bPressed)
					m->_buttonHit = OPTION_1;
				break;
			case OPTION_2:
				if (value->bPressed)
					m->_buttonHit = OPTION_2;
				break;
			case OPTION_3:
				if (value->bPressed)
					m->_buttonHit = OPTION_3;
				break;
			case OPTION_4:
				if (value->bPressed)
					m->_buttonHit = OPTION_4;
				break;
			case OPTION_5:
				if (value->bPressed)
					m->_buttonHit = OPTION_5;
				break;
			case OPTION_6:
				if (value->bPressed)
					m->_buttonHit = OPTION_6;
				break;
			default:
				m->_buttonHit = NO_ACTION;
				break;
		}
	}
}
