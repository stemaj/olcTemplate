#ifndef __GEOMETRY_WRAPPER_HPP
#define __GEOMETRY_WRAPPER_HPP

namespace wrapper {
  #include <olcTemplate/game/src/engine/olcUTIL_Geometry2D_v2.h>
} 

namespace stemaj
{
using namespace wrapper::olc::utils::geom2d;


  using Line = line<int>;
  using Circle = circle<int>;
  using Rect = rect<int>;
using Point = wrapper::olc::v_2d<int>;
}

#endif // __GEOMETRY_WRAPPER_HPP
