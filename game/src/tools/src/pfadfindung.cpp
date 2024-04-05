#include <game/src/tools/pfadfindung.hpp>

#include <limits>
#include <vector>

stemaj::Pfadfindung::Pfadfindung(const std::vector<std::vector<int>> &_gitter)
    : gitter(_gitter) {
  hoehe = gitter.size();
  breite = (hoehe > 0) ? gitter[0].size() : 0;
}

std::vector<std::pair<int, int>> stemaj::Pfadfindung::FindePfad(int start_x,
                                                                int start_y,
                                                                int ziel_x,
                                                                int ziel_y) {
  start_x = clamp(start_x, 0, breite - 1);
  start_y = clamp(start_y, 0, hoehe - 1);
  ziel_x = clamp(ziel_x, 0, breite - 1);
  ziel_y = clamp(ziel_y, 0, hoehe - 1);

  if (gitter[start_y][start_x] == 1)
    findeNaechstenGueltigenPunkt(start_x, start_y, true, start_x, start_y);
  if (gitter[ziel_y][ziel_x] == 1)
    findeNaechstenGueltigenPunkt(ziel_x, ziel_y, false, ziel_x, ziel_y);

  offeneListe.clear();
  geschlosseneListe.clear();

  auto startKnoten = std::make_shared<Knoten>(
      start_x, start_y, 0, heuristik(start_x, start_y, ziel_x, ziel_y));
  offeneListe.push_back(startKnoten);

  while (!offeneListe.empty()) {
    auto currentNode = offeneListe.front();
    int currentIndex = 0;

    // Suche Knoten mit niedrigstem f-Wert
    for (int i = 1; i < offeneListe.size(); ++i) {
      if (offeneListe[i]->f() < currentNode->f()) {
        currentNode = offeneListe[i];
        currentIndex = i;
      }
    }

    offeneListe.erase(offeneListe.begin() + currentIndex);
    geschlosseneListe.push_back(currentNode);

    if (currentNode->x == ziel_x && currentNode->y == ziel_y) {
      std::vector<std::pair<int, int>> path;
      while (currentNode != nullptr) {
        path.push_back(std::make_pair(currentNode->x, currentNode->y));
        currentNode = currentNode->eltern;
      }
      return path;
    }

    std::vector<std::pair<int, int>> directions = {
        {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto &dir : directions) {
      int newX = currentNode->x + dir.first;
      int newY = currentNode->y + dir.second;

      if (newX >= 0 && newX < breite && newY >= 0 && newY < hoehe &&
          gitter[newY][newX] == 0) {
        bool inClosed = false;
        for (const auto &node : geschlosseneListe) {
          if (node->x == newX && node->y == newY) {
            inClosed = true;
            break;
          }
        }
        if (inClosed)
          continue;

        double newG = currentNode->g + 1;
        auto successor = findeKnotenInListe(offeneListe, newX, newY);

        if (successor == nullptr || newG < successor->g) {
          if (successor == nullptr) {
            successor = std::make_shared<Knoten>(
                newX, newY, newG, heuristik(newX, newY, ziel_x, ziel_y),
                currentNode);
            offeneListe.push_back(successor);
          } else {
            successor->g = newG;
            successor->eltern = currentNode;
          }
        }
      }
    }
  }

  return std::vector<std::pair<int, int>>();
}

void stemaj::Pfadfindung::findeNaechstenGueltigenPunkt(int x, int y,
                                                     bool istStartpunkt,
                                                     int &gueltiger_x,
                                                     int &gueltiger_y) {
  std::vector<std::pair<int, int>> nachbarn = {
      {-1, 0}, {1, 0}, {0, -1}, {0, 1}};
  double min_dist = std::numeric_limits<double>::max();

  for (const auto &nachbar : nachbarn) {
    int newX = x + nachbar.first;
    int newY = y + nachbar.second;

    if (newX >= 0 && newX < breite && newY >= 0 && newY < hoehe &&
        gitter[newY][newX] == 0) {
      double dist = heuristik(x, y, newX, newY);
      if (dist < min_dist) {
        min_dist = dist;
        gueltiger_x = newX;
        gueltiger_y = newY;
      }
    }
  }

  if (istStartpunkt) {
    gueltiger_x = clamp(gueltiger_x, 0, breite - 1);
    gueltiger_y = clamp(gueltiger_y, 0, hoehe - 1);
  } else {
    gueltiger_x = clamp(gueltiger_x, 0, breite - 1);
    gueltiger_y = clamp(gueltiger_y, 0, hoehe - 1);
  }
}

std::shared_ptr<stemaj::Knoten> stemaj::Pfadfindung::findeNiedrigstenF(
    const std::vector<std::shared_ptr<Knoten>> &liste) {
  auto minElement = std::min_element(
      liste.begin(), liste.end(),
      [](const auto &lhs, const auto &rhs) { return lhs->f() < rhs->f(); });
  return *minElement;
}

std::shared_ptr<stemaj::Knoten> stemaj::Pfadfindung::findeKnotenInListe(
    const std::vector<std::shared_ptr<Knoten>> &nodeList, int x, int y) {
  for (const auto &node : nodeList) {
    if (node->x == x && node->y == y)
      return node;
  }
  return nullptr;
}

bool stemaj::Pfadfindung::istKnotenInListe(
    const std::vector<std::shared_ptr<Knoten>> &nodeList, int x, int y) {
  for (const auto &node : nodeList) {
    if (node->x == x && node->y == y)
      return true;
  }
  return false;
}

std::vector<std::pair<int, int>> stemaj::Pfadfindung::konstruierePfad(
    const std::shared_ptr<Knoten> &zielknoten) {
  std::vector<std::pair<int, int>> pfad;
  auto currentNode = zielknoten;
  while (currentNode != nullptr) {
    pfad.push_back(std::make_pair(currentNode->x, currentNode->y));
    currentNode = currentNode->eltern;
  }
 std::reverse(pfad.begin(), pfad.end());
  return pfad;
}
