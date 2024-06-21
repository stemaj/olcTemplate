#ifndef __DAYTIME_HPP
#define __DAYTIME_HPP

#include <string>
#include <array>

namespace stemaj
{

class DayTime
{
public:
  DayTime(float scale);

  // Update-Methode zur Aktualisierung der Tageszeit
  void Update(float elapsedTime);

  // Methode zur Rückgabe der formatierten Tageszeit als String
  std::string GetFormattedTime() const;

  // Methode zur Rückgabe der RGBA-Werte der aktuellen Tageszeit
  std::array<int, 4> GetRGBA() const;

  // Methoden zur Einstellung von Dawn- und Dusk-Zeiten
  void SetDawnBegin(float time) { dawnBegin = time; }
  void SetDawnEnd(float time) { dawnEnd = time; }
  void SetDuskBegin(float time) { duskBegin = time; }
  void SetDuskEnd(float time) { duskEnd = time; }

private:
  float scale;
  float currentTime;
  float dawnBegin, dawnEnd, duskBegin, duskEnd;
  std::array<int, 4> Interpolate(const std::array<float, 4>& start, const std::array<float, 4>& end, float t) const;
};

} // namespace

#endif // __DAYTIME_HPP
