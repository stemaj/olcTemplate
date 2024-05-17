#ifndef __OLCHELPER_HPP
#define __OLCHELPER_HPP

#include <game/coordinates.hpp>
#include <game/src/engine/olcPixelGameEngine.h>

namespace stemaj {

class OlcHelper
{
    public:
    static void FillCircleDecal(olc::PixelGameEngine* pge, const int radius, 
        const PT<int> position, const olc::Pixel& color);

    static void CreateOneColorDecal(olc::Renderable* r, const olc::Pixel& color);
};

}

#endif //__OLCHELPER_HPP
