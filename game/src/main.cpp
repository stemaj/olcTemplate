// doctest before pge
#ifdef RUN_TESTS
#include <olcTemplate/sdk/doctest-2.4.11/doctest.h>
#endif

#include <olcTemplate/game/olcTemplate.hpp>
#include <olcTemplate/game/coordinates.hpp>

using namespace stemaj;

int main()
{
#ifdef RUN_TESTS
	doctest::Context context;
	context.run();
#else
  OlcTemplate t;
  
  if (t.Construct(CO.W, CO.H, CO.P, CO.P, CO.F))
  {
    t.Start();
  }
#endif
  return 0;
}
