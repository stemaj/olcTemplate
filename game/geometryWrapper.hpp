#ifndef __GEOMETRY_WRAPPER_HPP
#define __GEOMETRY_WRAPPER_HPP


namespace stemaj {
namespace wrapper {

#include <olcTemplate/game/src/engine/olcUTIL_Geometry2D_v2.h>

namespace geometry {
  using Line = wrapper::olc::utils::geom2d::line<int>;
  using Circle = wrapper::olc::utils::geom2d::circle<int>;
  using Rect = wrapper::olc::utils::geom2d::rect<int>;
  //using Point = wrapper::olc::utils::geom2d::
}

}
}

#endif // __GEOMETRY_WRAPPER_HPP
