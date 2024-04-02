#include <game/olcTemplate.hpp>

int main()
{
  stemaj::OlcTemplate t;
  if (t.Construct(320, 240, 2, 2))
  {
    t.Start();
  }

  return 0;
}
