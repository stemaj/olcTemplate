#include <cmath>
#include <iomanip>
#include <iostream>
#include <olcTemplate/game/src/tools/daytime.hpp>

#ifdef RUN_TESTS
#include <olcTemplate/sdk/doctest-2.4.11/doctest.h>
#endif

using namespace stemaj;

static constexpr std::array<int, 4> dayColor = {255, 255, 255, 0};
static constexpr std::array<int, 4> nightColor = {30, 30, 80, 153};
static constexpr std::array<int, 4> dawnEndColor = {255, 223, 186, 0};
static constexpr std::array<int, 4> duskStartColor = {255, 223, 186, 0};

DayTime::DayTime(float scale)
    : scale(scale), currentTime(0.0f),
      dawnBegin(0.15f), dawnEnd(0.3f), duskBegin(0.7f), duskEnd(0.85f) {}

void DayTime::Update(float elapsedTime)
{
  currentTime += elapsedTime * scale;
  if (currentTime > 1.0f)
  {
    currentTime = std::fmod(currentTime, 1.0f);
  }
}

std::string DayTime::GetFormattedTime() const
{
  float hours = currentTime * 24.0f;
  int hh = static_cast<int>(hours);
  int mm = static_cast<int>((hours - hh) * 60);
  std::ostringstream oss;
  oss << std::setfill('0') << std::setw(2) << hh << ":"
      << std::setfill('0') << std::setw(2) << mm;
  return oss.str();
}

std::array<int, 4> DayTime::GetRGBA() const
{
  std::array<float, 4> startColor, endColor;
  auto toFloats = [](std::array<int, 4> f){
    std::array<float, 4> ret;
    ret = { f[0]/255.0f, f[1]/255.0f, f[2]/255.0f, f[3]/255.0f };
    return ret;
  };

  if (currentTime >= dawnBegin && currentTime < dawnEnd)
  {
    // Dawn
    float t = (currentTime - dawnBegin) / (dawnEnd - dawnBegin);
    startColor = toFloats(nightColor);
    endColor = toFloats(dawnEndColor);
    return Interpolate(startColor, endColor, t);
  }
  else if (currentTime >= duskBegin && currentTime < duskEnd)
  {
    // Dusk
    float t = (currentTime - duskBegin) / (duskEnd - duskBegin);
    startColor = toFloats(duskStartColor);
    endColor = toFloats(nightColor);
    return Interpolate(startColor, endColor, t);
  }
  else if (currentTime >= duskEnd || currentTime < dawnBegin)
  {
    // Night
    return nightColor;
  }
  else
  {
    // Daytime
    return dayColor;
  }
}

std::array<int, 4> DayTime::Interpolate(const std::array<float, 4>& start,
    const std::array<float, 4>& end, float t) const
{
  std::array<int, 4> result;
  for (int i = 0; i < 4; ++i)
  {
    result[i] = static_cast<int>((start[i] + t * (end[i] - start[i])) * 255);
  }
  return result;
}


#ifdef RUN_TESTS

TEST_CASE("DayTime class functionality") {
    DayTime dt(0.1f); // Scale factor of 0.1

    SUBCASE("Initial state")
    {
        CHECK(dt.GetFormattedTime() == "00:00");
        std::array<int, 4> rgba = dt.GetRGBA();
        CHECK(rgba == nightColor);
    }

    SUBCASE("Update and time formatting")
    {
        dt.Update(2.5f); // Should be 06:00
        CHECK(dt.GetFormattedTime() == "06:00");

        dt.Update(5.0f); // Should be 18:00
        CHECK(dt.GetFormattedTime() == "18:00");
    }

    SUBCASE("RGBA values during dawn")
    {
        dt.SetDawnBegin(0.0f);
        dt.SetDawnEnd(0.25f);

        dt.Update(1.25f); // Should be halfway through dawn
        std::array<int, 4> rgba = dt.GetRGBA();
        CHECK(rgba == std::array<int, 4>{(nightColor[0]+dawnEndColor[0])/2,
            (nightColor[1]+dawnEndColor[1])/2,
            (nightColor[2]+dawnEndColor[2])/2,
            (nightColor[3]+dawnEndColor[3])/2, });
    }

    SUBCASE("RGBA values during daytime")
    {
        dt.SetDawnBegin(0.0f);
        dt.SetDawnEnd(0.25f);
        dt.SetDuskBegin(0.75f);
        dt.SetDuskEnd(1.0f);

        dt.Update(3.0f); // Should be daytime
        std::array<int, 4> rgba = dt.GetRGBA();
        CHECK(rgba == dayColor);
    }

    SUBCASE("RGBA values during dusk")
    {
        dt.SetDawnBegin(0.0f);
        dt.SetDawnEnd(0.25f);
        dt.SetDuskBegin(0.75f);
        dt.SetDuskEnd(1.0f);

        dt.Update(8.75f); // Should be halfway through dusk
        std::array<int, 4> rgba = dt.GetRGBA();
        CHECK(rgba == std::array<int, 4>{(nightColor[0]+duskStartColor[0])/2,
            (nightColor[1]+duskStartColor[1])/2,
            (nightColor[2]+duskStartColor[2])/2,
            (nightColor[3]+duskStartColor[3])/2, });
    }

    SUBCASE("RGBA values during night")
    {
        dt.SetDawnBegin(0.25f);
        dt.SetDawnEnd(0.35f);
        dt.SetDuskBegin(0.75f);
        dt.SetDuskEnd(0.85f);

        dt.Update(9.0f); // Should be night time
        std::array<int, 4> rgba = dt.GetRGBA();
        CHECK(rgba == nightColor);
    }

    SUBCASE("Transition from end of day to new day")
    {
        dt.Update(10.0f);
        CHECK(dt.GetFormattedTime() == "24:00");

        dt.Update(5.0f);
        CHECK(dt.GetFormattedTime() == "12:00");

        dt.Update(2.5f);
        CHECK(dt.GetFormattedTime() == "18:00");
    }
}

#endif // RUN_TESTS
