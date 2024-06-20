#include <cmath>
#include <iomanip>
#include <iostream>
#include <olcTemplate/game/src/tools/daytime.hpp>

#ifdef RUN_TESTS
#include <olcTemplate/sdk/doctest-2.4.11/doctest.h>
#endif

using namespace stemaj;

DayTime::DayTime(float scale)
        : scale(scale), currentTime(0.0f), dawnBegin(0.0f), dawnEnd(0.25f), duskBegin(0.75f), duskEnd(1.0f) {}

void DayTime::Update(float elapsedTime) {
        currentTime += elapsedTime * scale;
        if (currentTime > 1.0f) {
            currentTime = std::fmod(currentTime, 1.0f);
        }
    }

std::string DayTime::GetFormattedTime() const {
        float hours = currentTime * 24.0f;
        int hh = static_cast<int>(hours);
        int mm = static_cast<int>((hours - hh) * 60);
        std::ostringstream oss;
        oss << std::setfill('0') << std::setw(2) << hh << ":"
            << std::setfill('0') << std::setw(2) << mm;
        return oss.str();
    }


std::array<int, 4> DayTime::GetRGBA() const {
    // Beispielhafte Farbwerte für Dawn und Dusk
         std::array<float, 4> dawnStartColor = {10/255.0f, 10/255.0f, 50/255.0f, 0.7f};
        std::array<float, 4> dawnEndColor = {255/255.0f, 223/255.0f, 186/255.0f, 0.0f};
        std::array<float, 4> duskStartColor = {255/255.0f, 223/255.0f, 186/255.0f, 0.0f};
        std::array<float, 4> duskEndColor = {255/255.0f, 140/255.0f, 80/255.0f, 0.5f};
        std::array<float, 4> startColor, endColor;

        if (currentTime >= dawnBegin && currentTime < dawnEnd) {
            // Dawn
            float t = (currentTime - dawnBegin) / (dawnEnd - dawnBegin);
            startColor = dawnStartColor;
            endColor = dawnEndColor;
            return Interpolate(startColor, endColor, t);
        } else if (currentTime >= duskBegin && currentTime < duskEnd) {
            // Dusk
            float t = (currentTime - duskBegin) / (duskEnd - duskBegin);
            startColor = duskStartColor;
            endColor = duskEndColor;
            return Interpolate(startColor, endColor, t);
        } else {
            // Daytime
            return {255, 255, 255, 0};
        }
}


std::array<int, 4> DayTime::Interpolate(const std::array<float, 4>& start, const std::array<float, 4>& end, float t) const
{
  std::array<int, 4> result;
        for (int i = 0; i < 4; ++i) {
            result[i] = static_cast<int>((start[i] + t * (end[i] - start[i])) * 255);
        }
        std::cout << "color: " << result[0] << ", " << ", " << result[1] << ", " << result[2] << ", " << result[3] << std::endl;
        return result;
}



#ifdef RUN_TESTS

TEST_CASE("DayTime class functionality") {
    DayTime dt(0.1f); // Scale factor of 0.1

    SUBCASE("Initial state") {
        CHECK(dt.GetFormattedTime() == "00:00");
        std::array<int, 4> rgba = dt.GetRGBA();
        CHECK(rgba == std::array<int, 4>{10, 10, 50, 178});
    }

    SUBCASE("Update and time formatting") {
        dt.Update(2.5f); // Should be 06:00
        CHECK(dt.GetFormattedTime() == "06:00");

        dt.Update(5.0f); // Should be 18:00
        CHECK(dt.GetFormattedTime() == "18:00");
    }

    SUBCASE("RGBA values during dawn") {
        dt.SetDawnBegin(0.0f);
        dt.SetDawnEnd(0.25f);

        dt.Update(1.25f); // Should be halfway through dawn
        std::array<int, 4> rgba = dt.GetRGBA();

        CHECK(rgba == std::array<int, 4>{132, 116, 118, 89});
    }

    SUBCASE("RGBA values during daytime") {
        dt.SetDawnBegin(0.0f);
        dt.SetDawnEnd(0.25f);
        dt.SetDuskBegin(0.75f);
        dt.SetDuskEnd(1.0f);

        dt.Update(3.0f); // Should be daytime
        std::array<int, 4> rgba = dt.GetRGBA();
        CHECK(rgba == std::array<int, 4>{255, 255, 255, 0});
    }

    SUBCASE("RGBA values during dusk") {
        dt.SetDawnBegin(0.0f);
        dt.SetDawnEnd(0.25f);
        dt.SetDuskBegin(0.75f);
        dt.SetDuskEnd(1.0f);

        dt.Update(7.5f); // Should be halfway through dusk
        std::array<int, 4> rgba = dt.GetRGBA();

                std::array<float, 4> duskStartColor = {255/255.0f, 223/255.0f, 186/255.0f, 0.0f};
        std::array<float, 4> duskEndColor = {255/255.0f, 140/255.0f, 80/255.0f, 0.5f};

        CHECK(rgba == std::array<int, 4>{255, 182, 133, 63});
    }

    SUBCASE("Transition from end of day to new day") {
        dt.Update(10.0f);
        CHECK(dt.GetFormattedTime() == "24:00");

        dt.Update(5.0f); // Should be 12:00
        CHECK(dt.GetFormattedTime() == "12:00");
    }
}
#endif // RUN_TESTS