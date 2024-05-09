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
      int w = 10, h = 1;
      _r.Create(w,h);
      for (int x = 0; x < w; x++)
        for (int y = 0; y < h; y++)
        {
          if (x < 1 || x > w-4)
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

		auto lineEnd = std::abs(t._lineAnchorPoints[0].x-t._lineAnchorPoints[1].x);

    pge->DrawWarpedDecal(_impl->GetLine(), {
       {(float)(screenElementsLevel->_mousePos.x + lineEnd/2.0f), (float)screenElementsLevel->_mousePos.y},
       {(float)(screenElementsLevel->_mousePos.x - lineEnd/2.0f), (float)screenElementsLevel->_mousePos.y},
       {(float)(t._lineAnchorPoints[0].x - lineEnd/2.0f), (float)t._lineAnchorPoints[0].y},
       {(float)(t._lineAnchorPoints[1].x + lineEnd/2.0f), (float)t._lineAnchorPoints[1].y} });
    
    
    
    
    int radius = screenElementsLevel->_circle.radius;
    int offset_x = screenElementsLevel->_circle.pos.x;
    int offset_y = screenElementsLevel->_circle.pos.y;
    
    std::vector<PT<int>> points;
    for(int i=0; i<10; i++)
      points.push_back(PT<int>{offset_x + radius * cos(i * (2*pi/10.0))}, PT<int>{offset_y + radius * sin(i * (2*pi/10.0))});

    std::vector uvs;
    uvs.resize(points.size());
        DrawPolygonDecal(nullptr, points, uvs, olc::Pixel(255, 200, 200));

  
	}
}
