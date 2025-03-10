#ifndef __ROOM_3D
#define __ROOM_3D

#include <olcTemplate/game/coordinates.hpp>

namespace stemaj {

class Room3d
{
public:
  // Perspektivische Projektion mit Kameraverschiebung
  PT<int> Project(float x, float y, float z) const;

  // Abstand zwischen zwei 3D-Punkten berechnen
  static float Distance(float x1, float y1, float z1, float x2, float y2, float z2);

  void MoveCamX(float val);
  void MoveCamY(float val);
  void MoveCamZ(float val);
  float GetCamZ() const { return camZ; }

  bool isBumping = false;
  void StartBumpEffect(const PT<float>& bumpDir);

  void UpdateBumpEffect(float fElapsedTime);

  void CalcBackgroundPosition();

  PT<int> GetBackgroundPosition() const;
  float GetBackgroundScale() const;

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

  float _colorZLines[3] = {64/255.f, 64/255.f, 64/255.f};
  float _colorYLines[3] = {128/255.f, 128/255.f, 128/255.f};
  float _colorXLines[3] = {192/255.f, 192/255.f, 192/255.f};

  float _decalPos;

  float _cameraMoveSpeed = 50.0f;

  float fov = 100.0f;   // Brennweite
  float depth = 500.0f; // Maximale Tiefe des Gitters
  float gridSize = 100.0f;  // Abstand der Gitterlinien
  float gridWidth = 2000.0f; // Breite des Gitters (x-Richtung)
  float gridHeight = 500.0f; // Höhe des Gitters (y-Richtung)
  float startZ = -20.0f;  // Starttiefe des Gitters

  // Steuerung der Gitterlinien
  bool drawXLines = true; // Linien in x-Richtung (vertikal)
  bool drawYLines = true; // Linien in y-Richtung (horizontal)
  bool drawZLines = true; // Linien in z-Richtung (Tiefe)

  // Kamera-Position
  float camX = 0.0f, camY = 0.0f, camZ = 0.0f; // Startet leicht nach hinten versetzt
  float baseCamX = camX; // Basis-Kamerahöhe (zum Zurücksetzen)
  float baseCamY = camY; // Basis-Kamerahöhe (zum Zurücksetzen)

  float currentCamX;
  float currentCamY;

  // "Bump"-Effekt
  float bumpTime = 0.0f;
  float bumpDuration = 0.3f; // Gesamtdauer des Bumps
  
  PT<float> vfBumpDir; // Richtung des Bumps
  float bumpBaseAmplitude = 5.0f; // Maximale Stärke
 
  // Decal-Position im 3D-Raum
  float decalX = -50.0f;
  float decalY = -10.0f;
  float decalZ = 200.0f;
};

} // namespace stemaj

#endif // __ROOM_3D