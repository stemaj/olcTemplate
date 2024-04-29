#include <game/src/render/exampleScreenElementsLevelRender.hpp>
#include <game/src/state/exampleScreenElementsLevelState.hpp>
#include <game/textbox.hpp>
#include <game/src/engine/olcPixelGameEngine.h>
#include <game/src/engine/olcPGEX_TTF.h>
#include <game/fonts.hpp>
#define UTF_CPP_CPLUSPLUS 202002L
#include <sdk/utfcpp/utf8.h>

namespace stemaj {
  class ExampleScreenElementsLevelRenderImpl
  {
  private:
    olc::Renderable _r;
  public:
    ExampleScreenElementsLevelRenderImpl()
    {
      int w = 6, h = 1;
      _r.Create(w,h);
      for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
        {
          if (x < 2 || x > w-2)
            _r.Sprite()->SetPixel({x,y},olc::BLANK);
          else 
            _r.Sprite()->SetPixel({x,y},olc::WHITE);
        }
      _r.Decal()->Update();
    }
    olc::Decal* GetLine()
    {
      return _r.Decal();
    }
  };
}

using namespace stemaj;

ExampleScreenElementsLevelRender::ExampleScreenElementsLevelRender() :
  _impl(new ExampleScreenElementsLevelRenderImpl()) {}

ExampleScreenElementsLevelRender::~ExampleScreenElementsLevelRender()
{
  delete _impl;
}

void ExampleScreenElementsLevelRender::DoRender(olc::PixelGameEngine* pge, float fElapsedTime, State* state)
{
  auto screenElementsLevel = static_cast<ExampleScreenElementsLevelState*>(state);

  pge->Clear(olc::DARK_CYAN);

	for (auto& t : screenElementsLevel->_textboxes)
	{
		pge->FillRectDecal( { (float)t._frameboxUpperLeft.x,
			(float)t._frameboxUpperLeft.y },
			{ (float)t._frameboxSize.x,
			(float)t._frameboxSize.y },
			olc::Pixel(235,242,244, 224) );

		pge->DrawDecal({ (float)t._boxUpperLeft.x,
				(float)t._boxUpperLeft.y },
									 FT.Decal(t._text,
														t._fontName, t._fontSize), {1.0f,1.0f});

		pge->DrawWarpedDecal(_impl->GetLine(),
			{{(float)t._points[0].x, (float)t._points[0].y},
			{(float)t._points[1].x, (float)t._points[1].y},
			{(float)t._points[2].x, (float)t._points[2].y},
			{(float)t._points[3].x, (float)t._points[3].y} }
		);
	}
}
