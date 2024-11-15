#include <olcTemplate/game/palette.hpp>
#include <olcTemplate/game/loadsave.hpp>
#include <string>

using namespace stemaj;

Palette& Palette::get()
{
  static Palette me;
  return me;
}

int Palette::Init(const std::string& pal)
{
  LS.Init("scripts/settings.lua", false);
  LS.VString(pal);
  return 0;
}

std::array<float,4> Palette::ColF(const int index)
{
  return {};
}

float Palette::R(const int index)
{
  return 0.0f;
}

float Palette::G(const int index)
{
  return 0.0f;
}

float Palette::B(const int index)
{
  return 0.0f;
}

std::array<float, 4> Palette::hexToRGBA(const std::string& hex)
{
  if (hex.length() != 6 && hex.length() != 8) {
        throw std::invalid_argument("Ungültiger Hex-Farbwert");
    }

    int r = std::stoi(hex.substr(0, 2), nullptr, 16);
    int g = std::stoi(hex.substr(2, 4).substr(0, 2), nullptr, 16);
    int b = std::stoi(hex.substr(4, 6).substr(0, 2), nullptr, 16);
    int a = 255;

    if (hex.length() == 8) {
        a = std::stoi(hex.substr(6, 8).substr(0, 2), nullptr, 16);
    }

    return { r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f };
}
