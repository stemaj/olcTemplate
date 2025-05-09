#include <algorithm>
#include <array>
#include <cmath>
#include <olcTemplate/game/room3d.hpp>
#include <olcTemplate/sdk/imgui-1.90.4/imgui.h>

using namespace stemaj;

PT<int> Room3d::Projected(WorldPosition pos) const
{
  // Relativ zur Kamera berechnen
  float relX = pos.x - camX;
  float relY = pos.y - camY;
  float relZ = pos.z - camZ;

  // Mindest-Z-Wert setzen (verhindert starke Verzögerungen bei z ≈ 0)
  float minZ = 10.0f;  // Setze die Mindesttiefe auf 10
  if (relZ < minZ) relZ = minZ;

  // Projektion auf 2D-Bildschirm
  float scale = fov / (relZ + fov);
  int screenX = int(CO.W / 2.f + relX * scale);
  int screenY = int(CO.H / 2.f - relY * scale);
  return { screenX, screenY };
}

float Room3d::Distance(WorldPosition p1, WorldPosition p2)
{
  return sqrtf((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y) + (p2.z - p1.z) * (p2.z - p1.z));
}

void Room3d::MoveCamX(float val)
{
  camX += _cameraMoveSpeed * val;
}

void Room3d::MoveCamY(float val)
{
  camY += _cameraMoveSpeed * val;
}

void Room3d::MoveCamZ(float val)
{
  camZ += _cameraMoveSpeed * val;
}

void Room3d::StartBumpEffect(const PT<float>& bumpDir)
{
  currentCamX = camX; // Speichere aktuelle Position
  currentCamY = camY;
  
  vfBumpDir = bumpDir;
  isBumping = true;
  bumpTime = 0.0f; 
}

void Room3d::UpdateBumpEffect(float fElapsedTime)
{
  // "Bump"-Animation
  if (!isBumping) return;
  
  bumpTime += fElapsedTime;
  if (bumpTime < bumpDuration)
  {
    // Sinusförmige Bewegung für sanftes Hoch- und Runtergehen
    auto bumpDirection = vfBumpDir.norm() * PT<float>{-1.0f,-1.0f}; // Umkehren der Richtung

    // Begrenzung der Bump-Stärke auf einen sinnvollen Bereich
    float bumpFactor = 1.0f + vfBumpDir.mag();
    float bumpStrength = bumpBaseAmplitude / std::clamp(bumpFactor, 0.1f, 0.2f);

    camX = currentCamX + bumpDirection.x * bumpStrength * sinf((bumpTime / bumpDuration) * 3.14159f);
    camY = currentCamY + bumpDirection.y * bumpStrength * sinf((bumpTime / bumpDuration) * 3.14159f);
  }
  else
  {
    camX = currentCamX;
    camY = currentCamY;
    isBumping = false;
  }
}

PT<int> Room3d::GetBackgroundPosition() const
{
  return Projected({decalPos});
}

float Room3d::GetBackgroundScale() const
{
  return fov / (decalPos.z - camZ + fov); // Skalierung mit Tiefe
}

WorldPosition Room3d::MoveObject(const WorldPosition from, const WorldPosition to,
  float speed, float fElapsedTime)
{
  float distance = Distance(from, to);
  if (std::fabs(distance) < speed/80.f)
  {
    return from;
  }

  float norm = 1.0f / distance;
  float dx = (to.x - from.x) * norm;
  float dy = (to.y - from.y) * norm;
  float dz = (to.z - from.z) * norm;

  return { from.x + dx * speed * fElapsedTime,
           from.y + dy * speed * fElapsedTime,
           from.z + dz * speed * fElapsedTime };
}

float Room3d::calculateHeightFactor(float hmin, float hmax, float curvature, float l, float l_max)
{
  float t = l / l_max; // Normierung der Länge (0 bis 1)
  float ret = hmin + (hmax - hmin) * std::pow(1 - t, curvature);
  return std::max(hmin, std::min(hmax, ret)); // Wertebereich sicherstellen
}

void Room3d::Debug()
{
#if defined(STEMAJ_DEBUG)
  ImGui::Begin("Room3d Debug");
  ImGui::Checkbox("drawXLines", &drawXLines);
  ImGui::Checkbox("drawYLines", &drawYLines);
  ImGui::Checkbox("drawZLines", &drawZLines);
  ImGui::ColorEdit3("colorXLines", &_colorXLines[0]);
  ImGui::ColorEdit3("colorYLines", &_colorYLines[0]);
  ImGui::ColorEdit3("colorZLines", &_colorZLines[0]);
  ImGui::SliderFloat("fov", &fov, 10.0f, 1000.0f);
  ImGui::SliderFloat("depth", &depth, 50.0f, 5000.0f);
  ImGui::SliderFloat("gridWidth", &gridWidth, 200.0f, 20000.0f);
  ImGui::SliderFloat("gridHeight", &gridHeight, 50.0f, 5000.0f);
  ImGui::SliderFloat("startZ", &startZ, -200.0f, 200.0f);
  ImGui::End();

  debugLinesX.clear();
  debugLinesY.clear();
  debugLinesZ.clear();

  // *** Gitter zeichnen mit steuerbaren Linien ***
  for (float z = startZ; z < depth; z += gridSize)
  {
    if (drawXLines)
    {
      // Vertikale Linien in x-Richtung
      for (float x = -gridWidth / 2; x <= gridWidth / 2; x += gridSize)
      {
        auto p1 = Projected({x, -gridHeight / 2, z});
        auto p2 = Projected({x, gridHeight / 2, z});
        debugLinesX.push_back({{p1.x,p1.y},{p2.x,p2.y}});
      }
    }
    if (drawYLines)
    {
      // Horizontale Linien in y-Richtung
      for (float y = -gridHeight / 2; y <= gridHeight / 2; y += gridSize)
      {
        auto p1 = Projected({-gridWidth / 2, y, z});
        auto p2 = Projected({gridWidth / 2, y, z});
        debugLinesY.push_back({{p1.x,p1.y},{p2.x,p2.y}});
      }
    }
  }

  if (drawZLines)
  {
    // Tiefenlinien in z-Richtung
    for (float x = -gridWidth / 2; x <= gridWidth / 2; x += gridSize)
    {
      for (float y = -gridHeight / 2; y <= gridHeight / 2; y += gridSize)
      {
        auto p1 = Projected({x, y, startZ});
        auto p2 = Projected({x, y, depth});
        debugLinesZ.push_back({{p1.x,p1.y},{p2.x,p2.y}});
      }
    }
  }
#endif
}