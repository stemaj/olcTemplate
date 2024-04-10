#include <game/coordinates.hpp>
#define SOL_ALL_SAFETIES_ON 1
#include <sdk/sol2-3.3.0/sol.hpp>

using namespace stemaj;

Coordinates& Coordinates::get()
{
  static Coordinates me;
  return me;
}

Coordinates::Coordinates()
{
  
}
