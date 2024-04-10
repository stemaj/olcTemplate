// doctest before pge
#ifdef RUN_TESTS
#include <sdk/doctest-2.4.11/doctest.h>
#endif

#include <game/olcTemplate.hpp>
#include <game/coordinates.hpp>

using namespace stemaj;

int main()
{
#ifdef RUN_TESTS
	doctest::Context context;
	context.run();
#else
  OlcTemplate t;
  
  if (t.Construct(CO.W, CO.H, 2, 2))
  {
    t.Start();
  }
#endif
  return 0;
}
