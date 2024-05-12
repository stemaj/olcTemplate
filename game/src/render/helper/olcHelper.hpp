#ifndef __OLCHELPER_HPP
#define __OLCHELPER_HPP

#include <game/src/engine/olcPixelGameEngine.h>

namespace stemaj {

class OlcHelper
{
    public:
    static void FillCircleDecal(olc::PixelGameEngine* pge, const int radius, 
        const int offset_x, const int offset_y, const olc::Pixel& color);

    static void CreateOneColorDecal(olc::Renderable* r, const olc::Pixel& color);
};

}

#endif //__OLCHELPER_HPP
