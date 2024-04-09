// doctest before pge
#ifdef RUN_TESTS
#include <sdk/doctest-2.4.11/doctest.h>
#endif

#include <game/olcTemplate.hpp>

int main()
{
#ifdef RUN_TESTS
	doctest::Context context;
	context.run();
#else
  stemaj::OlcTemplate t;
  if (t.Construct(320, 240, 2, 2))
  {
    t.Start();
  }
#endif
  return 0;
}
