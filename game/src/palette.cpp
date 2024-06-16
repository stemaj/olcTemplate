#include <olcTemplate/game/palette.hpp>

using namespace stemaj;

Palette& Palette::get()
{
  static Palette me;
  return me;
}
