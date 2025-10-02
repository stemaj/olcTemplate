#ifndef __ROOM_3D
#define __ROOM_3D

#include <cstdint>
#include <olcTemplate/game/coordinates.hpp>

namespace stemaj {

struct WorldPosition
{
  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
};

class Room3d
{
public:
  // Perspektivische Projektion mit Kameraverschiebung
  PT<int> Projected(WorldPosition p) const;

  // Abstand zwischen zwei 3D-Punkten berechnen
  static float Distance(WorldPosition p1, WorldPosition p2);

  WorldPosition MoveObject(const WorldPosition from, const WorldPosition to,
    float speed, float fElapsedTime);

  void MoveCamX(float val);
  void MoveCamY(float val);
  void MoveCamZ(float val);
  float GetCamZ() const { return camZ; }

  bool isBumping = false;
  void StartBumpEffect(const PT<float>& bumpDir);

  void UpdateBumpEffect(float fElapsedTime);

  PT<int> GetBackgroundPosition() const;
  float GetBackgroundScale() const;

  float calculateHeightFactor(float hmin, float hmax, float curvature, float l, float l_max);

  void Debug();
  std::vector<std::pair<PT<float>,PT<float>>> debugLinesX;
  std::vector<std::pair<PT<float>,PT<float>>> debugLinesY;
  std::vector<std::pair<PT<float>,PT<float>>> debugLinesZ;

  uint32_t GetColorXLines() const { 
    return (static_cast<uint32_t>(255) << 24) | // Alpha Volle Deckkraft (kein Transparent) (Bits 24-31)
           (static_cast<uint32_t>(static_cast<uint8_t>(_colorXLines[2] * 255.0f)) << 16) | // Blau   (Bits 16-23)
           (static_cast<uint32_t>(static_cast<uint8_t>(_colorXLines[1] * 255.0f)) << 8)  | // Grün  (Bits 8-15)
           (static_cast<uint32_t>(static_cast<uint8_t>(_colorXLines[0] * 255.0f))); }       // Rot  (Bits 0-7)
  uint32_t GetColorYLines() const {
    return (static_cast<uint32_t>(255) << 24) | // Alpha Volle Deckkraft (kein Transparent) (Bits 24-31)
           (static_cast<uint32_t>(static_cast<uint8_t>(_colorYLines[2] * 255.0f)) << 16) | // Blau   (Bits 16-23)
           (static_cast<uint32_t>(static_cast<uint8_t>(_colorYLines[1] * 255.0f)) << 8)  | // Grün  (Bits 8-15)
           (static_cast<uint32_t>(static_cast<uint8_t>(_colorYLines[0] * 255.0f))); }       // Rot  (Bits 0-7)
  uint32_t GetColorZLines() const {
    return (static_cast<uint32_t>(255) << 24) | // Alpha Volle Deckkraft (kein Transparent) (Bits 24-31)
           (static_cast<uint32_t>(static_cast<uint8_t>(_colorZLines[2] * 255.0f)) << 16) | // Blau   (Bits 16-23)
           (static_cast<uint32_t>(static_cast<uint8_t>(_colorZLines[1] * 255.0f)) << 8)  | // Grün  (Bits 8-15)
           (static_cast<uint32_t>(static_cast<uint8_t>(_colorZLines[0] * 255.0f))); }       // Rot  (Bits 0-7)
            
private:

  // Steuerung der Gitterlinien
  bool drawXLines = true; // Linien in x-Richtung (vertikal)
  bool drawYLines = true; // Linien in y-Richtung (horizontal)
  bool drawZLines = true; // Linien in z-Richtung (Tiefe)
  float _colorZLines[3] = {64/255.f, 64/255.f, 64/255.f};
  float _colorYLines[3] = {128/255.f, 128/255.f, 128/255.f};
  float _colorXLines[3] = {192/255.f, 192/255.f, 192/255.f};

  float fov = 100.0f;   // Brennweite
  float depth = 500.0f; // Maximale Tiefe des Gitters
  float gridSize = 100.0f;  // Abstand der Gitterlinien
  float gridWidth = 2000.0f; // Breite des Gitters (x-Richtung)
  float gridHeight = 500.0f; // Höhe des Gitters (y-Richtung)
  float startZ = -20.0f;  // Starttiefe des Gitters

  // Kamera-Position
  float _cameraMoveSpeed = 300.0f;
  float camX = 0.0f, camY = 0.0f, camZ = 0.0f;
  float baseCamX = camX; // Basis-Kamerahöhe (zum Zurücksetzen)
  float baseCamY = camY; // Basis-Kamerahöhe (zum Zurücksetzen)

  // "Bump"-Effekt
  float bumpTime = 0.0f;
  float bumpDuration = 0.3f; // Gesamtdauer des Bumps
  float currentCamX;
  float currentCamY;
  PT<float> vfBumpDir; // Richtung des Bumps
  float bumpBaseAmplitude = 5.0f; // Maximale Stärke
 
  // Decal-Position im 3D-Raum
  WorldPosition decalPos = { -1000.0f, 380.0f, 100.0f };
};

} // namespace stemaj

#endif // __ROOM_3D